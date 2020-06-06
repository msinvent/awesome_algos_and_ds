//============================================================================
// Name        : bfs.cpp
// Author      : Manish Sharma
// Version     : 1.0
// Copyright   : Refer to copyright notice of git repo
// Description : Directed graph implementation using std::unordered_map<uid, std::unordered_set<uid>> ds
// Time Complexity :
// Space Complexity :
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <deque>

// Directed graph implementation
template<typename uid>
class graph{
public:
	void insertNode(uid id){
		if(_data.find(id)==_data.end()){
			_data[id] = std::unordered_set<uid>();
		}
	}
	void insertLinks(uid id, uid idneighbor){
		insertNode(id);
		insertNode(idneighbor);
		_data[id].insert(idneighbor);
	}

	void printGraph(){
		std::cout<<"Graph Description : \n";
		for(const auto& elem : _data){
			std::cout<<"elem : "<<elem.first<<", neighbors : ";
			for(const auto& neighbor : elem.second){
				std::cout<<neighbor<<" ";
			}std::cout<<"\n";
		}std::cout<<"\n";
	}

	void BFSTraversal(uid start){
		std::unordered_set<uid> alreadyTraversed{start};
		std::deque<uid> bfsQueue{start};

		std::cout<<"Breadth first traversal V1 starting from "<<start<<" is : ";
		while(!bfsQueue.empty()){
			start = bfsQueue.front();
			bfsQueue.pop_front();
			alreadyTraversed.insert(start);

			// Google mishap, only insert if not already traversed
			for(const auto& neighbor : _data[start]){
				if(alreadyTraversed.find(neighbor)==alreadyTraversed.end()){
					bfsQueue.push_back(neighbor);
					alreadyTraversed.insert(neighbor);
				}
			}
			std::cout<<start<<" ";
		}std::cout<<"\n";
	}

	void BFSTraversalRecursiveImplementation(uid start,
			std::deque<uid> bfsQueue,
			std::vector<uid>& bfsTraversal,
			std::unordered_set<uid>& alreadyTraversed){

		bfsTraversal.push_back(start);
		alreadyTraversed.insert(start);

		for(const auto& neighbor : _data[start]){
			if(alreadyTraversed.find(neighbor)==alreadyTraversed.end()){
				bfsQueue.push_back(neighbor);
				alreadyTraversed.insert(neighbor);
			}
		}

		if(bfsQueue.empty()){
			return;
		}

		start = bfsQueue.front();
		bfsQueue.pop_front();
		alreadyTraversed.insert(start);
		BFSTraversalRecursiveImplementation(start, bfsQueue, bfsTraversal, alreadyTraversed);
	}

	void BFSTraversalR(uid start){
		std::deque<uid> bfsQueue;
		std::unordered_set<uid> alreadyTraversed;
		std::vector<uid> bfsTraversal;
		BFSTraversalRecursiveImplementation(start, bfsQueue, bfsTraversal, alreadyTraversed);

		std::cout<<"Breadth first traversal V2 starting from "<<start<<" is : ";
		for(const auto& elem : bfsTraversal){
			std::cout<<elem<<" ";
		}std::cout<<"\n";
	}
private:
	std::unordered_map<uid, std::unordered_set<uid>> _data;
	// this will also do, but we need to have a mechanism to not insert the same neighbor again,
	// even if we do, it will not be theoretically wrong, but this will lead to some inefficiencies while search
	// though it will be more optimal to just traverse the graph with a vector
	//	std::unordered_map<uid, std::std::vector<uid>> _data;

};

int main() {
	graph<int> mygraph;
	mygraph.insertLinks(1,2);
	mygraph.insertLinks(1,3);
	mygraph.insertLinks(1,4);
	mygraph.insertLinks(4,5);
	mygraph.insertLinks(5,6);
	mygraph.insertLinks(3,6);

	mygraph.printGraph();

	// BFS is a traversal algorithm not a search algorithm, I was initially thinking to print the shortest path using BFS
	// but, I then I realized that BFS is providing a traversal and may be we can print out the sequence of nodes visited
	// while making a search but it is not much of a shortest path kind of thing. On the contrary DFS can provide a shortest path
	mygraph.BFSTraversal(1);
	mygraph.BFSTraversalR(1);
	mygraph.BFSTraversal(2);
	mygraph.BFSTraversalR(2);
	mygraph.BFSTraversal(3);
	mygraph.BFSTraversalR(3);
	mygraph.BFSTraversal(4);
	mygraph.BFSTraversalR(4);

	return 0;
}
