#ifndef FLAT_NODE_H
#define FLAT_NODE_H

#include <cstddef>

//class for flats
class FlatNode
{
public:
	//flat members
	int id;
	int initial_bandwidth = 0;
	bool is_empty = 0;

	FlatNode* nextP = NULL;
	FlatNode* prevP = NULL;

	//method to get new node of flat based on arguments
	static FlatNode* getnode(int id, int initial_bandwidth);
	//method for deleting flat nodes from heap
	static void freenode(FlatNode* p);
	//constructer for flatnodes
	FlatNode(int id, int initial_bandwidth);
};
#endif
