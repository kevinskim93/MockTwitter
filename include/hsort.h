#ifndef HSORT_H
#define HSORT_H

#include <vector>
#include <iostream>

//declaration of the function
template <class T, class Comparator>
void heapify(std::vector<T>& myArray, int index, int sortedIndex, Comparator comp);

//swap two values, templated
template <class T>
void swap(T& one, T& two){

	T temp = one;
	one = two;
	two = temp;
}

//pass in the array into this function to make the heap that you will use for the heapsort algorithm
template <class T, class Comparator>
void makeHeap(std::vector<T>& myArray, Comparator comp){

	for(int i = myArray.size()-1; i > 0; i--){
		heapify(myArray, i, myArray.size(), comp);
	}
}



template <class T, class Comparator>
void heapify (std::vector<T>& myArray, int index, int sortedIndex, Comparator comp){
	//std::cout << "Index: " << index << std::endl;
  	//if the node is a leaf node, then the index*2 (which is the left child node) would be null
  	if(&(myArray[index*2]) == NULL) {
  		//std::cout << "noted" << std::endl; 
  		return;
  	}
  	//index value for the left child of the node you are on(assume it is the smaller)
	int smallerchild = 2*index;
	//if the right child of the current node exists
	//this portion ensures that we will use the smaller child in our recursive calls
 	if(&(myArray[index*2+1]) != NULL) {
 		int rightchild = smallerchild+1;
 		//rightchild was actually smaller than "smallerchild"
 		if(comp(myArray[rightchild], myArray[smallerchild])){
 			smallerchild = rightchild;
 		}
	}
	//if the index is greater than the smallerchild, need to heapify again
	if(comp(myArray[smallerchild], myArray[index]) && smallerchild < sortedIndex){
 		swap(myArray[index], myArray[smallerchild]);
 		heapify(myArray, smallerchild, sortedIndex, comp);
	}
}

template <class T, class Comparator>
void heapsort(std::vector<T>& heap, Comparator comp){
	for(int i = 1; i < heap.size(); i++){
		swap(heap[1], heap[heap.size()-i]);
		//std::cout << i << std::endl;
		heapify(heap, 1, heap.size()-i, comp);
	}
}


#endif
/*
void heapsort ( ){
	T temp = myArray.top();
	myArray.pop_back();
	heapify(myArray, myArray.size());
}*/

