#include "git-gud.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

using namespace git_gud;

GitTree::GitTree()
{
	auto firstCommit = std::make_shared<Commit>(generateBranchID());
	this->commits.push_back(firstCommit);
	this->head = firstCommit;
	this->numBranches = 1;
}

int GitTree::generateBranchID()
{
	static int ID = 0;
	return ID++;
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
	throw std::invalid_argument("ID not found!");
}

std::shared_ptr<Commit> GitTree::getHead() const
{
	return this->head;
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
		throw std::invalid_argument("Branch does not exist!");
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

	auto commit = std::make_shared<Commit>(parent->getBranch());

	commit->addParent(parent);
	parent->addChild(commit);

	checkout(commit);
	this->commits.push_back(commit);

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
	auto commit = std::make_shared<Commit>(generateBranchID());

	commit->addParent(parent);
	parent->addChild(commit);

	checkout(commit);
	this->commits.push_back(commit);
	this->numBranches++;

	return commit;
}

std::shared_ptr<Commit> GitTree::merge(int otherID)
{
	// will throw invalid_argument if otherID not found
	return merge(this->head->getID(), otherID);
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

void GitTree::checkout(int commitID)
{
	// getCommit() will throw invalid_argument if not found
	checkout(getCommit(commitID));
}

void GitTree::checkout(std::shared_ptr<Commit> commit)
{
	this->head = commit;
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
	if (last->isNewBranch()) {numBranches--;}

	auto parents = last->getParents();

	for (auto parent : parents)
	{
		parent->removeChild(last->getID());
	}
}

void GitTree::print() const
{
	std::cout << "...\n";
	std::cout << "GitTree\n";
	std::cout << "Number of branches: " << getNumBranches() << "\n";
	std::cout << "Number of commits: " << getNumCommits() << "\n";

	for (auto ptr : this->commits) {

		if (this->head == ptr)
		{
			std::cout << "HEAD\n";
		}
		ptr->print();
	}

	std::cout << "...\n";
}