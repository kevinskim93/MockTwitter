// necessary includes can go here
#ifndef ALIST_H
#define ALIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class AList
{
  public:
    AList ();   // constructor

    ~AList ();  // destructor

    int size () const;  // returns the number of elements in the list

    void insert (int position, const T & val);
      /* Inserts val into the list before the given position,
         shifting all later items one position to the right.
         Inserting before 0 (i.e., position = 0) makes it the 
         new first element.
         Inserting before size() (i.e., position = size()) makes 
         it the new last element.
         Your function should throw an exception if position is
         outside the legal range, which would be 0-size() here. */

    void remove (int position);
      /* Removes the item from the given position, shifting all
         later items one position to the left.
         Your function should throw an exception if position is
         outside the legal range. */

    void set (int position, const T & val);
      /* Overwrites the given position with the given value.
         Does not affect any other positions.  
         Your function should throw an exception if position is
         outside the legal range. */

    T& get (int position) ;
      /* Returns a non-const reference to the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */

     T const& get (int position) const;
      /* Returns a const reference to the item at the given position.
         Your function should throw an exception if position is
         outside the legal range. */

      AList(const AList&);
      /* This is a copy constructor and we likely haven't learned how to make
         deep copies of a list yet.  Thus by making it's prototype private, the
         compiler will enforce that no one ever be allowed to make a copy of a AList */

      AList& operator=(const AList&);
      /* This is a copy constructor and we likely haven't learned how to make
         deep copies of a list yet.  Thus by making it's prototype private, the
         compiler will enforce that no one ever be allowed to make a copy of a AList */


    private:

      T* data;

      /* You may add further private data fields or helper methods if 
         you choose. You should not alter the public signature. */

      int capacity;

      int number;


};

template<typename T>
AList<T>::AList(){
  number = 0;
  capacity = 5;
  (data) = new T[5];
  
}

template<typename T>
AList<T>::~AList(){
  delete [] data;
}

template<typename T>
int AList<T>::size () const{
  return number;
}


template<typename T>
void AList<T>::insert (int position, const T & val){

  if(position < 0 || position > size()){
    throw std::out_of_range("Out of range");
  }

  if (size() == capacity){
    int doubleCap = capacity*2;
    T* temp = new T[doubleCap];
    for(int i = 0; i < size(); i++){
      temp[i] = data[i];
    }

    delete [] data;
    data = temp;
    capacity = doubleCap;

  }

  if (position == size()){
    data[position] = val;
  }

  else if (position < size()){
    for(int i = size(); i > position; i--){
      data[i] = data[i-1];
    }
    data[position] = val;

  }

  number++;

}

template<typename T>
void AList<T>::remove (int position){

  if(position < 0 || position+1 > size()){
    throw std::out_of_range("Out of range");
  }

  if(position == size()-1){
    
    data[position] = '\n';
  }

  else if(position < size()-1){
    for(int i = position; i < size()-1; i++){
      data[i] = data[i+1];
    }
  }

  

  number--;
}



template<typename T>
void AList<T>::set (int position, const T & val){

  if(position < 0 || position > size()){
    throw std::out_of_range("Out of range");
  }

  data[position] = val;

 

}

template<typename T>
T& AList<T>::get (int position){

  if(position < 0 || position > size()){
    throw std::out_of_range("Out of range");
  }

  return data[position];

}
  
template<typename T>
T const& AList<T>::get (int position) const {

  if(position < 0 || position > size()){
    throw std::out_of_range("Out of range");
  }

  return data[position];
}



template<typename T>
AList<T>::AList (const AList<T> & other){

  this->number = other.number;
  this->capacity = other.capacity;
  this->data = new T[number];
  for(int i=0; i < number; i++){
     this->data[i] = other.data[i];
  }
}
  // A copy constructor which performs a deep copy.

template<typename T>
AList<T> & AList<T>::operator= (const AList<T> & other){

  if ( this == &other  ){
    return *this;
  }
  // check if the member are already initialized
  if( data != NULL){
    delete [] data;
  }
  this->capacity = other.capacity;
  this->number = other.size();
  // dat already is pointing at a dynamic array
  data = new T[capacity];
  for(int i=0; i < number; i++){
    data[i] = other.data[i];
  }
  return *this;

}
  // An assignment operators.

#endif