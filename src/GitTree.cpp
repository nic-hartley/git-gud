#include "git-gud.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

using namespace git_gud;

GitTree::GitTree()
{
	addCommit();
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

void GitTree::addCommit()
{
	auto commit = std::make_shared<Commit>(generateBranchID());

	this->commits.push_back(commit);
	this->numBranches++;
}

void GitTree::addCommit(int parentID)
{
	auto parent = getCommit(parentID);
	auto commit = std::make_shared<Commit>(parent->getBranch());

	commit->addParent(parent);
	parent->addChild(commit);

	this->commits.push_back(commit);
}

void GitTree::addCommitNewBranch(int parentID)
{
	auto parent = getCommit(parentID);
	auto commit = std::make_shared<Commit>(generateBranchID());

	commit->addParent(parent);
	parent->addChild(commit);

	this->commits.push_back(commit);
	this->numBranches++;
}

void GitTree::undo()
{
	if (this->commits.size() <= 1) { return; }

	auto last = getLatest();
	auto parents = last->getParents();

	for (auto parent : parents)
	{
		parent->removeChild(last->getID());
	}

	this->commits.pop_back();
}

void GitTree::print() const
{
	for (auto ptr : this->commits) {ptr->print();}
}