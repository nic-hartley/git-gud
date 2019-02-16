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
	auto parent = getCommit(parentID);
	auto commit = std::make_shared<Commit>(parent->getBranch());

	commit->addParent(parent);
	parent->addChild(commit);

	checkout(commit);
	this->commits.push_back(commit);

	return commit;
}

std::shared_ptr<Commit> GitTree::addCommitNewBranch(int parentID)
{
	auto parent = getCommit(parentID);
	auto commit = std::make_shared<Commit>(generateBranchID());

	commit->addParent(parent);
	parent->addChild(commit);

	checkout(commit);
	this->commits.push_back(commit);
	this->numBranches++;

	return commit;
}

void GitTree::checkout(int commitID)
{
	for (auto ptr : this->commits)
	{
		if (ptr->getID() == commitID)
		{
			checkout(ptr);
		}
	}

	throw std::invalid_argument("Invalid head!");
}

void GitTree::checkout(std::shared_ptr<Commit> commit)
{
	this->head = commit;
}

void GitTree::undo()
{
	if (this->commits.size() <= 1) { return; }

	auto last = getLatest();
	this->commits.pop_back();

	if (this->head = last)
	{
		this->head = getLatest();
	}

	auto parents = last->getParents();

	for (auto parent : parents)
	{
		parent->removeChild(last->getID());
	}

	this->commits.pop_back();
}

void GitTree::print() const
{
	for (auto ptr : this->commits) {

		if (this->head == ptr)
		{
			std::cout << "HEAD\n";
		}
		ptr->print();
	}
}