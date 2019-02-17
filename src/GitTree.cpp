#include "git-gud.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept> // invalid_argument
#include <algorithm> // find

using namespace git_gud;

GitTree::GitTree()
{
	auto firstCommit = std::make_shared<Commit>(nextBranchID++, nextCommitID++);
	this->commits.push_back(firstCommit);
	this->head = firstCommit;
	this->numBranches = 1;
}

std::shared_ptr<Commit> GitTree::getCommit(int ID) const
{
	// Iterate through the commit list
	for (std::shared_ptr<Commit> c_ptr : this->commits)
	{
		if (c_ptr->getID() == ID)
		{
			return c_ptr;
		}
	}

	// The ID didn't exist!
	std::ostringstream msg;
	msg << "ID " << ID << " not found!";
	throw std::invalid_argument(msg.str());
}

std::shared_ptr<Commit> GitTree::getHead() const
{
	return this->head;
}

bool GitTree::isHead(int commitID) const
{
	return this->head->getID() == commitID;
}

std::shared_ptr<Commit> GitTree::getLatest() const
{
	if (this->commits.empty()) {return NULL;}
	return this->commits.back();
}

std::shared_ptr<Commit> GitTree::getLatest(int branchID) const
{
	std::shared_ptr<Commit> latest = NULL;
	for (auto ptr : this->commits)
	{
		if (ptr->getBranch() == branchID)
		{
			latest = ptr;
		}
	}

	if (latest == NULL)
	{
		std::ostringstream msg;
		msg << "Branch " << branchID << " not found!";
		throw std::invalid_argument(msg.str());
	}

	return latest;
}

std::vector<std::shared_ptr<Commit> >& GitTree::getAllCommits()
{
	return this->commits;
}

int GitTree::getNumBranches() const
{
	return this->numBranches;
}

int GitTree::getNumCommits() const
{
	return this->commits.size();
}

std::vector<int> GitTree::getAllBranchIDs() const
{
	std::vector<int> ids;

	// iterate through all commits
	for (auto commit : this->commits)
	{
		// check if the commit's branch is already in the list
		if(std::find(ids.begin(), ids.end(), commit->getBranch()) == ids.end())
		{
    		// ID not already added
    		ids.push_back(commit->getBranch());
		}
	}

	return ids;
}

std::vector<int> GitTree::getAllCommitIDs() const
{
	std::vector<int> ids;
	for (auto commit : this->commits)
	{
		ids.push_back(commit->getID());
	}

	return ids;
}

bool GitTree::isValidBranchID(int id) const
{
	auto ids = getAllBranchIDs();

	// If the id is found, then it is valid
	return std::find(ids.begin(), ids.end(), id) != ids.end();
}

bool GitTree::isValidCommitID(int id) const
{
	auto ids = getAllCommitIDs();

	// If the id is found, then it is valid
	return std::find(ids.begin(), ids.end(), id) != ids.end();
}

std::shared_ptr<Commit> GitTree::addCommit()
{
	int parent = this->head->getID();
	return addCommit(parent);
}

std::shared_ptr<Commit> GitTree::addCommit(int parentID)
{
	// will throw invalid_argument if not found
	auto parent = getCommit(parentID);

	// Parents cannot have more than one child in the same branch!
	for (auto child : parent->getChildren())
	{
		if (child->getID() == parent->getID())
		{
			throw std::invalid_argument("Create a new branch!");
		}
	}

	auto commit = std::make_shared<Commit>(parent->getBranch(), nextCommitID++);

	commit->addParent(parent);
	parent->addChild(commit);


	this->commits.push_back(commit);
	checkoutCommit(commit->getID());

	return commit;
}

std::shared_ptr<Commit> GitTree::addCommitNewBranch()
{
	return addCommitNewBranch(this->head->getID());
}

std::shared_ptr<Commit> GitTree::addCommitNewBranch(int parentID)
{
	// throws invalid_argument if parent not found
	auto parent = getCommit(parentID);
	auto commit = std::make_shared<Commit>(nextBranchID++, nextCommitID++);

	commit->addParent(parent);
	parent->addChild(commit);

	this->commits.push_back(commit);
	this->numBranches++;
	checkoutCommit(commit->getID());

	return commit;
}

std::shared_ptr<Commit> GitTree::merge(int branchID)
{
	// will throw invalid_argument if branchID not found
	return merge(this->head->getID(), getLatest(branchID)->getID());
}

std::shared_ptr<Commit> GitTree::merge(int parent1ID, int parent2ID)
{

	// Cannot merge a commit into itself
	if (parent1ID == parent2ID)
	{
		throw std::invalid_argument("Can't merge into itself!");
	}

	// Connect it to the merging parent
	// getCommit() will throw invalid_argument if not found
	auto primaryParent = getCommit(parent1ID);
	auto otherParent = getCommit(parent2ID);

	auto child = addCommit(primaryParent->getID());

	child->addParent(otherParent);
	otherParent->addChild(child);

	return child;
}

void GitTree::checkout(int branchID)
{
	// getLatest() will throw invalid_argument if not found
	checkoutCommit(getLatest(branchID)->getID());
}

void GitTree::checkoutCommit(int commit)
{
	this->head = getCommit(commit);
}

void GitTree::undo()
{
	// Don't undo the first commit
	if (this->commits.size() <= 1) { return; }

	auto last = getLatest();
	this->commits.pop_back();

	// If the head is at the undone commit, move it to the previous commit
	if (this->head->getID() == last->getID())
	{
		this->head = getLatest();
	}

	// If it's a new branch, the number of branches is reduced by one
	if (last->isNewBranch())
	{
		numBranches--;
		nextBranchID--;
	}

	auto parents = last->getParents();

	for (auto parent : parents)
	{
		parent->removeChild(last->getID());
	}

	nextCommitID--;
}

void GitTree::print() const
{
	std::cout << "...\n";
	std::cout << "GitTree\n";
	std::cout << "Number of branches: " << getNumBranches() << "\n";
	std::cout << "Number of commits: " << getNumCommits() << "\n";
	std::cout << "Next branch ID: " << nextBranchID << "\n";
	std::cout << "Next commit ID: " << nextCommitID << "\n";

	for (auto ptr : this->commits) {

		if (this->head == ptr)
		{
			std::cout << "HEAD\n";
		}
		ptr->print();
	}

	std::cout << "...\n";
}