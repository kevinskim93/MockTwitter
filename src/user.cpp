#include "../include/user.h"
#include <string>

User::User(){
  
}

User::User(std::string name){
  this->Name = name;
}

/**
 * Destructor
 */
User::~User(){

}

/**
 * Gets the name of the user 
 * 
 * @return name of the user 
 */
std::string User::name(){
  return Name;
}

/**
 * Gets all the followers of this user  
 * 
 * @return Set of Users who follow this user
 */
Set<User*> User::followers(){
  return Followers;
}

/**
 * Gets all the users whom this user follows  
 *
 * @return Set of Users whom this user follows
 */
Set<User*> User::following(){
  return Following;
}

/**
 * Gets all the tweets this user has posted
 * 
 * @return List of tweets this user has posted
 */
AList<Tweet*> User::tweets(){
  return Tweets;
}

/**
 * Adds a follower to this users set of followers
 * 
 * @param u User to add as a follower
 */
void User::addFollower(User* u){
  Followers.add(u);
}

/**
 * Adds another user to the set whom this User follows
 * 
 * @param u User that the user will now follow
 */
void User::addFollowing(User* u){
  Following.add(u);
  u->addFollower(this);

}

/**
 * Adds the given tweet as a post from this user
 * 
 * @param t new Tweet posted by this user
 */
void User::addTweet(Tweet* t){
  Tweets.insert(Tweets.size(), t);

}

/**
 * Produces the list of Tweets that represent this users feed/timeline
 *  It should contain in timestamp order all the tweets from
 *  this user and all the tweets from all the users whom this user follows
 *
 * @return vector of pointers to all the tweets from this user
 *         and those they follow in timestamp order
 */
void User::makeFeed(){
  User** u;
  for (u = Following.first(); u != NULL; u = Following.next() ){
    for (unsigned int j = 0; j < (*u)->tweets().size(); j++){
      Feed.insert(Feed.size(), (*u)->tweets().get(j));
    }
  }

  std::cout<<"first size: " << Feed.size() << "second size: ";

  for (unsigned int m = 0; m < Tweets.size(); m++){
    Feed.insert(Feed.size(), Tweets.get(m));
  }

  std::cout<<Feed.size() << std::endl;

  for(unsigned int i = 0; i < Feed.size()-1; i++){
    int min = i; 
    for(int j = i+1; j < Feed.size(); j++){ 
      if(*((Feed.get(j))) < (*((Feed.get(min)))) ) { 
        //std::cout<<min<<std::endl;
        min = j;
      } 
    } 
    
    Tweet* tempTweet = (Feed.get(min));

    Feed.set(min, Feed.get(i)); 
    Feed.set(i, tempTweet);
    
  }
}

AList<Tweet*> User::getFeed(){

  return Feed;


}

/*User& User::operator= (const User & other){
  Name = other.Name;
}

bool User::operator==(const User &other){
  return (Name == other.Name);
  std::cout << this->Name << " " << other.Name<< std::endl;
  std::cout<<"ALLA";
  if(this->Name == other.Name){
    return true;
  }
  else{
    return false;
  }
}*/