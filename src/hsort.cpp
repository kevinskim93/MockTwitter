#include "../include/hsort.h"
#include <string>
#include <iostream>

using namespace std;

struct AlphaStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs < rhs; 
    }
  };

  struct LengthStrComp {
    bool operator()(const string& lhs, const string& rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs.size() < rhs.size(); 
    }
  };


int main(){

	AlphaStrComp comp1;
	LengthStrComp comp2;


	vector<string> ints1;
	//note, the 0th value of the array will always be ignored by this implementation
	//ints1.push_back("FAKE");
	ints1.push_back("ABCD");
	ints1.push_back("EF");
	ints1.push_back("GHIJKL");
	ints1.push_back("YZ");
	ints1.push_back("VWX");
	ints1.push_back("NOPQRSTU");
	ints1.push_back("M");

	//turns the vector into a valid heap
	makeHeap(ints1, comp1);

	//cout << "Heaping" << endl;

	//turns the heap into a sorted heap
	heapsort(ints1, comp1);

	//cout << "Sort based on the alpha value of the string: " << endl;
	for(unsigned int i = 1; i < ints1.size(); i++){
		cout <<ints1[i] << endl;
	}
	
	
}