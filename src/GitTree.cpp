#include "git-gud.hpp"

#include <vector>

using namespace git_gud;

int GitTree::generateBranchID()
{
	static int ID = 0;
	return ID++;
}

Commit GitTree::getLatest()
{
	return 0;
}

Commit GitTree::getLatest(int branchID)
{
	return Commit(branchID);
}

std::vector<Commit> GitTree::getAllCommits()
{
	return this->commits;
}

int GitTree::getNumBranches()
{
	return this->numBranches;
}

void GitTree::addCommit(int parentID)
{
	return;
}

void GitTree::addCommitNewBranch(int parentID)
{
	return;
}