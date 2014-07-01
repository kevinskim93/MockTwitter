#ifndef MAP_H
#define MAP_H
#include "../include/AList.h"


template <class keyType, class valueType>
struct Pair {

    keyType key;
    valueType value;

};


template <typename keyType, typename valueType>
class Map
{
  public:
    Map ();  // constructor for a new empty map

    ~Map (); // destructor

    int size () const; // returns the number of key-value pairs

    void add (const keyType & key, const valueType & value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should simply replace the old value with this given value
      */

    void remove (const keyType & key);
     /* Removes the association for the given key.
        If the key has no association, it should throw an exception */

    valueType const & get (const keyType & key) const;
     /* Returns the value associated with the given key by constant reference.
        If the key has no association, it should throw an exception. */

    valueType& get (const keyType & key);
     /* Returns the value associated with the given key by mutable reference.
        If the key has no association, it should throw an exception. */

    bool contains (const keyType & key) const;
     /* Returns true if the key exists in the map, false, otherwise */

  private:
    AList<Pair<keyType, valueType> > internalStorage;

    int find(const keyType & key);


     /* You should store all of your associations inside one list.
        It is part of your assignment to figure out what types you 
        should store in that list.
        (Hint: you may need to add an additional definition.) */

     /* If you like, you can add further data fields and private
        helper methods.
        In particular, a 'find' function could be useful, which
        will find the index in the list at which a given key sits. */

};


template <typename keyType, typename valueType>
Map<keyType, valueType>::Map(){
  
}

template <typename keyType, typename valueType>
Map<keyType, valueType>::~Map(){

}

template <typename keyType, typename valueType>
int Map<keyType, valueType>::size () const{
  return internalStorage.size();
}


template <typename keyType, typename valueType>
void Map<keyType, valueType>::add (const keyType & key, const valueType & value){

    if(find(key) != -1){
        throw std::invalid_argument("Key already exists");
    }

    Pair<keyType, valueType> temp;
    temp.key = key;
    temp.value = value;

    internalStorage.insert(internalStorage.size(),temp);

}

template <typename keyType, typename valueType>
void Map<keyType, valueType>::remove (const keyType & key){

    if(find(key) == -1){
        throw std::invalid_argument("Key does not exist");
    }

    internalStorage.remove(find(key));

}

  
template <typename keyType, typename valueType>
valueType const& Map<keyType, valueType>::get (const keyType & key) const {

    if(find(key) == -1){
        throw std::invalid_argument("Key does not exist");
    }

    return internalStorage.get(find(key)).value; 

}

template <typename keyType, typename valueType>
valueType& Map<keyType, valueType>::get (const keyType & key){

    if(find(key) == -1){
        throw std::invalid_argument("Key does not exist");
    }

    return internalStorage.get(find(key)).value; 


}

template <typename keyType, typename valueType>
bool Map<keyType, valueType>::contains (const keyType & key) const{

    for(int i = 0; i < size(); i++){
        if (find(key) != -1){
            return true;
        }
    }

    return false;

}

template <typename keyType, typename valueType>
int  Map<keyType, valueType>::find (const keyType & key){

    for(int i = 0; i < size(); i++){
        if(key == internalStorage.get(i).key){
            return i;
        }
    }

    return -1;
    

}

#endif
