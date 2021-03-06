// necessary includes can go here

#ifndef SET_H
#define SET_H
#include "AList.h"


template <class T>
class Set {
  public: 
    Set ();                     // constructor for an empty set
    Set (const Set<T> & other); // copy constructor, making a deep copy
    ~Set ();                    // destructor

    void add (const T & item); 
      /* Adds the item to the set. 
         Throws an exception if the set already contains the item. */

    void remove (const T & item);
      /* Removes the item from the set.
         Throws an exception if the set does not contain the item. */

    bool contains (const T & item) const;
      /* Returns true if the set contains the item, and false otherwise. */

    int size () const;
      /* Returns the number of elements in the set. */

    bool isEmpty () const;
      /* Returns true if the set is empty, and false otherwise. */

    Set<T> setIntersection (const Set<T> & other) const;
      /* Returns the intersection of the current set with other.
         That is, returns the set of all items that are both in this
         and in other. */

    Set<T> setUnion (const Set<T> & other) const;
      /* Returns the union of the current set with other.
         That is, returns the set of all items that are in this set
         or in other (or both).
         The resulting set should not contain duplicates. */

    /* The next two functions together implement a suboptimal version
       of what is called an "iterator".
       Together, they should give you a way to loop through all elements
       of the set. The function "first" starts the loop, and the function
       "next" moves on to the next element.
       You will want to keep the state of the loop inside a private variable.
       We will learn the correct way to implement iterators soon, at 
       which point you will replace this.
       For now, we want to keep it simple. */

    T* first ();
      /* Returns the pointer to some element of the set, 
         which you may consider the "first" element.
         Should return NULL if the set is empty. */

    T* next ();
      /* Returns the pointer to an element of the set different from all 
         the ones that "first" and "next" have returned so far. 
         Should return NULL if there are no more element. */

  private:
    AList <T> internalStorage;
    // other private variables you think you need.

    int find(const T & finder);

    int state;
};

template<typename T>
Set<T>::Set(){
  state = 0;
}

template<typename T>
Set<T>::Set (const Set<T> & other){
  internalStorage = other.internalStorage;
  state = 0;

}

template<typename T>
Set<T>::~Set(){

}                   

template<typename T>
void Set<T>::add (const T & item){

  if(contains(item)){
    throw std::invalid_argument("item already exists");
  }

  internalStorage.insert(internalStorage.size(),item);


} 
  /* Adds the item to the set. 
     Throws an exception if the set already contains the item. */

template<typename T>
void Set<T>::remove(const T & item){

  if(!contains(item)){
    throw std::invalid_argument("item does not exist");
  }

  internalStorage.remove(find(item));
}
  /* Removes the item from the set.
     Throws an exception if the set does not contain the item. */

template<typename T>
bool Set<T>::contains(const T & item) const{

  for(int i = 0; i < size(); i++){
        if(item == internalStorage.get(i)){
            return true;
        }
    }

    return false;

}
  /* Returns true if the set contains the item, and false otherwise. */

template<typename T>
int Set<T>::size() const{
  return internalStorage.size();
}
  /* Returns the number of elements in the set. */

template<typename T>
bool Set<T>::isEmpty () const{
  if (internalStorage.size() == 0){
    return true;
  }
  else{
    return false;
  }
}
  /* Returns true if the set is empty, and false otherwise. */

template<typename T>
Set<T> Set<T>::setIntersection(const Set<T> & other) const{

  Set<T> temp;


  for(T* first = this->first(); first != NULL; first = this->next()){
    for(T* second = other.first(); second != NULL; second = other.next()){
      if(second == first){
        if(temp.find(first) == -1){
          temp.add(first);
        }
      }
    }
  }
  return temp;
}


  /* Returns the intersection of the current set with other.
     That is, returns the set of all items that are both in this
     and in other. */
     //mySet.setIntersection(otherSet);

template<typename T>
Set<T> Set<T>::setUnion(const Set<T> & other) const{

  Set<T> temp;

  for(T* first = this->first(); first != NULL; first = this->next()){
    if(temp.find(first) == -1){
      temp.add(first);
    }
  }

  for(T* first = other.first(); first != NULL; first = other.next()){
    if(temp.find(first) == -1){
      temp.add(first);
    }
  }

  return temp;

}
  /* Returns the union of the current set with other.
     That is, returns the set of all items that are in this set
     or in other (or both).
     The resulting set should not contain duplicates. */

/* The next two functions together implement a suboptimal version
   of what is called an "iterator".
   Together, they should give you a way to loop through all elements
   of the set. The function "first" starts the loop, and the function
   "next" moves on to the next element.
   You will want to keep the state of the loop inside a private variable.
   We will learn the correct way to implement iterators soon, at 
   which point you will replace this.
   For now, we want to keep it simple. */

template<typename T>
T* Set<T>::first(){

  if(internalStorage.size() > 0){
    return &internalStorage.get(0);
  }

  else{
    return NULL;
  }

}
  /* Returns the pointer to some element of the set, 
     which you may consider the "first" element.
     Should return NULL if the set is empty. */

template<typename T>
T* Set<T>::next(){

  if(internalStorage.size() < 1){
    state = 0;
    return NULL;
  }

  else{

    state++;
    if(state == size()){
      state = 0;
      return NULL;
    }

    return &internalStorage.get(state);
  }

}
  /* Returns the pointer to an element of the set different from all 
     the ones that "first" and "next" have returned so far. 
     Should return NULL if there are no more element. */

template <typename T>
int Set<T>::find(const T & finder){
    for(int i = 0; i < size(); i++){
        if(finder == internalStorage.get(i)){
          return i;
        }
    }

    return -1;
    

}
#endif