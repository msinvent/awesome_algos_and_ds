//============================================================================
// Name        : KMP_substringSearch.cpp
// Author      : Manish Sharma
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of KMP algorithm for pattern finding
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

std::vector<int> constructPI(const std::string& input){
	std::vector<int> ret(input.size(),0);

	int base = 0;
	for(std::size_t i = 1u; i < input.size(); ++i){
		if(input[i] == input[base]){
			ret[i] = ++base;
		}else{
			base = 0;
		}
	}
	return ret;
}

//@ret : return if pattern is found in str
//@str : assume that pattern is not an empty string
bool findPattern(const std::string& str, const std::string& pattern){
	auto retPI = constructPI(pattern);

	unsigned pp = 0;
	for(auto c : str){
		if(pattern[pp] == c){
			++pp;
		}else{
			pp = retPI[pp];
			if(pattern[pp] != c){
				pp = 0;
			}
		}
		if(pp == pattern.size()){
			return true;
		}
	}
	return false;
}

int main() {
	std::string str("aabcdaaadacacaaa");
	std::string pattern("aab");
	std::cout<<findPattern(str, pattern);
	return 0;
}
