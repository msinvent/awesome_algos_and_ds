//============================================================================
// Name        : maximumAreaOfRectangleFormed.cpp
// Author      : Manish Sharma
// Version     :
// Copyright   : Your copyright notice
// Description : Find the area of maximum rectangle(aligned with x and y) that can be formed by given set of points
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>

// @input sorted vector with non repeated elements with size at-least 2
// @return 0 if no overlaps or length of max distance
int maxOverLappingY(const std::vector<int>& lh, const std::vector<int>& rh){
	bool startFound(false);
	int start(0), end(0);
	for(auto i = 0u, j =0u; i < lh.size() && j < rh.size();){
		if(lh[i] == rh[j]){
			if(!startFound){
				startFound = true;
				start = lh[i];
				end = lh[i];
			}else{
				end = lh[i];
			}
			++i;
			++j;
		}
		else if(lh[i] < rh[j]){
			++i;
		}else{
			++j;
		}
	}
	return end-start;
}

using vecType = std::pair<int, std::vector<int>>;
int maxArea(std::vector<std::pair<int, int>>& points){
	if(points.size() < 4){
		return 0;
	}

	std::sort(points.begin(), points.end());
	std::vector<vecType> info;

	int maxArea = 0;
 	for(auto i = 0u; i < points.size()-1; ++i){
 		// Create y vector
 		std::vector<int> tmp{};
 		while(i < (points.size()-1) && points[i].first == points[i+1].first){
 			if(tmp.empty()){
 				tmp.push_back(points[i].second);
 			}
 			if(tmp.back() != points[i+1].second){
 				tmp.push_back(points[i+1].second);
 			}
			++i;
 		}

 		// Only perform search if 2 separate y points are found
 		if(tmp.size() >= 2){
 			for(std::size_t j = 0; j < info.size(); ++j){
 			 	maxArea = std::max(maxArea, (points[i].first-info[j].first)*maxOverLappingY(info[j].second, tmp));
 			}
 			info.push_back(vecType(points[i].first, std::move(tmp)));
 		}
 	}

	return maxArea;
}

int main() {
	std::vector<std::pair<int,int>> inputPoints{{1,1},{1,7},{1,9},{3,4},{4,1},{4,7},{11,3},{11,100},{0,9},{-5,8},{-7,3},{-7,100}};
	std::cout <<"maximum area of rectangle : " << maxArea(inputPoints);
	return 0;
}
