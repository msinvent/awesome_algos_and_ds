//============================================================================
// Name        : ms_disjointSet.cpp
// Author      : Manish Sharma
// Version     : 1.0
// Copyright   : Follows common github repository copyright
// Description : A simple implementation of disjoint-set with union by rank and path compression
//============================================================================

#include <iostream>
#include <unordered_map>

// What is the constraint on type T to templatize disjointSet ?
// It should have '==' and '=' operators defined,
// showData is imposing extra constraints for it to be ostream compatible, but if you don't use this method
// then you need not to worry about them
// If element is already present, then makeSet leaves the djSet in previous valid state
// If element is not present, then Union leaves the djSet in previous valid state
template<typename T>
class disjointSet{
public:

	struct Node{
		T parent;
		uint32_t rank;
	};

	void makeSet(T elem){
		if(_data.find(elem) == _data.end()){
			_data[elem] = Node{elem,0};
			// _data[elem] = Node{elem,0}; // how to perform simple initialization, i am performing uniform initialization above, may be I should use typename
		}
	}
	void Union(T elem1,T elem2){
		std::cout<<"merging "<<elem1<<" and "<<elem2<<"\n";
		if(_data.find(elem1) != _data.end() && _data.find(elem2) != _data.end())
		{
			auto n1 = findSet(elem1);
			auto n2 = findSet(elem2);

			// if not already a single set
			if(n1.parent != n2.parent){
				// union by rank logic
				// only the rank of the representative element maintains a valid state in the _data
				if(n1.rank < n2.rank){
					_data[n1.parent] = _data[n2.parent];
				}else if(n2.rank < n1.rank){
					_data[n2.parent] = _data[n1.parent];
				}else{
					_data[n2.parent] = n1;
					_data[n1.parent].rank++;
				}
			}
		}
	}
	Node findSet(T elem){
		T looper(elem);
		while(looper != _data[looper].parent)
		{
			looper = _data[looper].parent;
		}

		// path compression
		T compressor(elem);
		while(compressor != _data[compressor].parent)
		{
			_data[compressor] = _data[looper];
			compressor = _data[compressor].parent;
		}
		return _data[looper];
	}
	void showData(){
		for(const auto& elem : _data){
			std::cout<<"Elem : "<<elem.first<<", (Patent, Rank) : "
					<<elem.second.parent<<", "
					<<elem.second.rank<<"\n";
		}std::cout<<"\n";
	}
private:
	std::unordered_map<T, Node> _data; //map of every element to its set
};

int main()
{
	std::cout<<"Demonstration of disjoint Set :\n";
	disjointSet<int> mydjSet;

	mydjSet.makeSet(1);
	mydjSet.makeSet(2);
	mydjSet.makeSet(3);
	mydjSet.makeSet(4);
	mydjSet.makeSet(5);
	mydjSet.makeSet(6);
	mydjSet.makeSet(7);


	mydjSet.Union(1,2);
	mydjSet.showData();

	mydjSet.Union(2,3);
	mydjSet.showData();

	mydjSet.Union(4,5);
	mydjSet.showData();

	mydjSet.Union(6,7);
	mydjSet.showData();

	mydjSet.Union(5,6);
	mydjSet.showData();

	mydjSet.Union(3,7);
	mydjSet.showData();

	mydjSet.findSet(3);
	mydjSet.findSet(2);
	mydjSet.showData();

	return 0;
}
