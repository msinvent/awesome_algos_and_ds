//============================================================================
// Name        : moveProgram.cpp
// Author      : Manish Sharma
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <chrono>
#include <string>

class Widget
{
public:
	Widget(int ii, std::string si, int* pii, std::vector<int> myveci):		//constructor
		i(ii),
		s(si),
		pi(pii),
		myvec(myveci){
	}

	Widget(const Widget& w):						//copy constructor
		i(w.i),
		s(w.s),
		pi(new int(*(w.pi))),
		myvec(w.myvec)
	{
	}
	Widget& operator=(const Widget& w) = delete;	//copy assignment operator
	Widget&& operator=(Widget&& w) = delete;		//move assignment operator
	const std::string& stringIs()
	{
		return s;
	}
	~Widget()
	{
		delete pi;
	}

	Widget(Widget&& w): 								//move constructor
		i(std::move(w.i)),
		s(std::move(w.s)),
		pi(std::move(w.pi)),
		myvec(std::move(w.myvec))
	{
		w.pi=nullptr;
	}
private:
	int i;
	std::string s;
	int* pi;
	std::vector<int> myvec;
};
int main() {
	std::string s("Just a super long test string, Just a super long test string, Just a super long test string");

	constexpr std::size_t N(1000000);
	std::vector<Widget> v;
	v.reserve(N);
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();

	for(std::size_t i=0; i<N; ++i)
	{
		std::vector<int> vec{1,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0
			,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0};
		Widget w{1,s,new int(5),vec};
//		v.push_back(std::move_if_noexcept(w));
		v.push_back(std::move(w));

	}
	end = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double> elapsedTime(end-start);
	const double seconds(elapsedTime.count());	std::cout<<std::fixed;
	std::cout<<"Runtime: "<<seconds<<"s\n\n";
	return 0;
}
