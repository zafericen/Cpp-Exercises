#include "FlatNode.h"

FlatNode* FlatNode::getnode(int id, int initial_bandwidth)
{
    FlatNode* p = new FlatNode(id, initial_bandwidth);
    return p;
}

void FlatNode::freenode(FlatNode* p)
{
    delete p;
}

FlatNode::FlatNode(int id, int initial_bandwidth)
{
    this->id = id;
    this->initial_bandwidth = initial_bandwidth;
}
