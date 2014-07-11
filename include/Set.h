// necessary includes can go here

#ifndef SET_H
#define SET_H
#include <set>
#include <vector>


template <class T>
class Set : public std::set<T> {
  public: 
    Set ();                     // constructor for an empty set
    Set (const Set<T> & other); // copy constructor, making a deep copy
    ~Set ();                    // destructor

    std::set<T> setIntersection (const Set<T> & other) const;
      /* Returns the intersection of the current set with other.
         That is, returns the set of all items that are both in this
         and in other. */

    std::set<T> setUnion (const Set<T> & other) const;
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

  private:
    std::vector<T> internalStorage;
    // other private variables you think you need.
};

template<typename T>
Set<T>::Set(){
}

template<typename T>
Set<T>::Set (const Set<T> & other){
  internalStorage = other.internalStorage;

}

template<typename T>
Set<T>::~Set(){

}                   

template<typename T>
std::set<T> Set<T>::setIntersection(const Set<T> & other) const{

  std::set<T> temp;


  for(typename std::set<T>::iterator it = this->begin(); it != this->end(); ++it){
     for(typename std::set<T>::iterator it2 = other.begin(); it2 != other.end(); ++it2){
        if(*it == *it2){
          if(temp.find(*it) == -1){
            temp.add(*it);
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
std::set<T> Set<T>::setUnion(const Set<T> & other) const{

  std::set<T> temp;

  for(typename std::set<T>::iterator it = this->begin(); it != this->end(); ++it){
     if(temp.find(*it) == -1){
       temp.add(*it);
     }
   }

   for(typename std::set<T>::iterator it = other.begin(); it != other.end(); ++it){
     if(temp.find(*it) == -1){
       temp.add(*it);
     }
   }

  return temp;

}
  /* Returns the union of the current set with other.
     That is, returns the set of all items that are in this set
     or in other (or both).
     The resulting set should not contain duplicates. */

#endif