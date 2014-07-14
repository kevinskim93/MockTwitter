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
 * @return set of Users who follow this user
 */
std::set<User*> User::followers(){
  return Followers;
}

/**
 * Gets all the users whom this user follows  
 *
 * @return set of Users whom this user follows
 */
std::set<User*> User::following(){
  return Following;
}

/**
 * Gets all the tweets this user has posted
 * 
 * @return List of tweets this user has posted
 */
std::vector<Tweet*> User::tweets(){
  return Tweets;
}

std::vector<Tweet*> User::mentionstweets(){
  return MentionsTweets;
}

/**
 * Adds a follower to this users set of followers
 * 
 * @param u User to add as a follower
 */
void User::addFollower(User* u){
  Followers.insert(u);
}

/**
 * Adds another user to the set whom this User follows
 * 
 * @param u User that the user will now follow
 */
void User::addFollowing(User* u){
  Following.insert(u);
  u->addFollower(this);

}

/**
 * Adds the given tweet as a post from this user
 * 
 * @param t new Tweet posted by this user
 */
void User::addTweet(Tweet* t){
  Tweets.push_back(t);

}

void User::addMentions(Tweet* t){
  MentionsTweets.push_back(t);
}

void User::addMentioned(Tweet* t){
  MentionedTweets.push_back(t);
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
  typename std::set<User*>::iterator it;
  for(it = Following.begin(); it != Following.end(); ++it){
    for (unsigned int j = 0; j < (*it)->tweets().size(); j++){
      Feed.push_back((*it)->tweets().at(j));
    }
  }

  for (unsigned int m = 0; m < Tweets.size(); m++){
    Feed.push_back(Tweets.at(m));
  }

  for (unsigned int m = 0; m < MentionsTweets.size(); m++){
    Feed.push_back(MentionsTweets.at(m));
  }

  if(Feed.size() > 0){  
    for(unsigned int i = 0; i < Feed.size()-1; i++){
      int min = i; 
      for(unsigned int j = i+1; j < Feed.size(); j++){ 
        if(*((Feed.at(j))) > (*((Feed.at(min)))) ) { 
          //std::cout<<min<<std::endl;
          min = j;
        } 
      } 
      
      Tweet* tempTweet = (Feed.at(min));

      Feed[min] = Feed[i]; 
      Feed[i] = tempTweet;
      
      }
    }
  }

std::vector<Tweet*> User::getFeed(){

  return Feed;


}

void User::makeMentionedFeed(){


  for (unsigned int m = 0; m < MentionedTweets.size(); m++){
    MentionedFeed.push_back(MentionedTweets.at(m));
  }

  if(MentionedTweets.size() > 0){
    for(unsigned int i = 0; i < MentionedFeed.size()-1; i++){
      int min = i; 
      for(unsigned int j = i+1; j < MentionedFeed.size(); j++){ 
        if(*((MentionedFeed.at(j))) > (*((MentionedFeed.at(min)))) ) { 
          //std::cout<<min<<std::endl;
          min = j;
        } 
      } 
      
      Tweet* tempTweet = (MentionedFeed.at(min));

      MentionedFeed[min] = MentionedFeed[i]; 
      MentionedFeed[i] = tempTweet;
      
    }
  }



}

std::vector<Tweet*> User::getMentionedFeed(){

  return MentionedFeed;

}

void User::deleteFeed(){
  Feed.clear();

}

void User::deleteMentionedFeed(){
  MentionedFeed.clear();

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