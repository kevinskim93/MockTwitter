#ifndef HSORT_H
#define HSORT_H

#include <vector>
#include <iostream>


//changeup two values, templated
template <class T>
void changeup(T& one, T& two){

	T temp = one;
	one = two;
	two = temp;
}

//declaration of the function
template <class T, class Comparator>
void heapify (std::vector<T>& myArray, int index, int sortedIndex, Comparator comp){
	//std::cout << "Index: " << index << std::endl;
  	//if the node is a leaf node, then the index*2 (which is the left child node) would be null
  	if(index*2 > sortedIndex) {
  		//std::cout << "noted" << std::endl; 
  		return;
  	}
  	//index value for the left child of the node you are on(assume it is the smaller)
	int smallerchild = 2*index;
	//if the right child of the current node exists
	//this portion ensures that we will use the smaller child in our recursive calls
 	if(smallerchild+1 <= sortedIndex) {
 		//std::cout << (myArray[index*2+1]) << std::endl;
 		int rightchild = smallerchild+1;
 		//rightchild was actually smaller than "smallerchild"
 		if(comp(myArray[rightchild], myArray[smallerchild])){
 			smallerchild = rightchild;
 		}
	}
	//if the index is greater than the smallerchild, need to heapify again
	if(comp(myArray[smallerchild], myArray[index]) && smallerchild < sortedIndex){
 		changeup(myArray[index], myArray[smallerchild]);
 		heapify(myArray, smallerchild, sortedIndex, comp);
	}
}

template <class T, class Comparator>
void heapsort(std::vector<T>& heap, Comparator comp){
	//this will already ensure that it will only run when heap.size() > 1
	for(int i = 1; i < heap.size(); i++){
		changeup(heap[1], heap[heap.size()-i]);
		//std::cout << i << std::endl;
		heapify(heap, 1, heap.size()-i, comp);
	}
}


//pass in the array into this function to make the heap that you will use for the heapsort algorithm
template <class T, class Comparator>
void makeHeap(std::vector<T>& myArray, Comparator comp){

	//if the heap array is 0 or 1, it's both a heap and sorted so only do this if its 2 or greater
	if(myArray.size() > 1){
		myArray.push_back(myArray[0]);
		for(int i = 0; i < myArray.size(); i++){
			myArray[myArray.size()-1-i] = myArray[myArray.size()-1-i-1];
			if(myArray.size()-1-i-1 == 0){
				break;
			}
		}

		//turns the vector into a heap
		for(int i = myArray.size()/2; i > 0; i--){
			heapify(myArray, i, myArray.size()-1, comp);
		}
	}
}






#endif
/*
void heapsort ( ){
	T temp = myArray.top();
	myArray.pop_back();
	heapify(myArray, myArray.size());
}*/

