#include "git-gud.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

using namespace git_gud;

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

std::vector<std::shared_ptr<Commit>>& GitTree::getAllCommits()
{
	return this->commits;
}

int GitTree::getNumBranches() const
{
	return this->numBranches;
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
}