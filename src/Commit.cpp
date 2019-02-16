#include "git-gud.hpp"

#include <vector>

using namespace git_gud;

Commit::Commit(int branchID, int commitID)
{
	this->commitID = commitID;
	this->branchID = branchID;
}

Commit::Commit(int branchID)
{
	this->commitID = generateID();
	this->branchID = branchID;
}

int Commit::generateID()
{
	static int id = 0;
	return id++;
}

int Commit::getID() {return this->commitID;}
int Commit::getBranch() {return this->branchID;}

std::vector<Commit> Commit::getParents() {return this->parents;}
std::vector<Commit> Commit::getChildren() {return this->children;}

void Commit::addParent(Commit parent) {this->parents.push_back(parent);}
void Commit::addChild(Commit child) {this->children.push_back(child);}