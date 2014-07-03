#ifndef USER_H
#define USER_H

#include "Set.h"
#include "tweet.h"
#include <string>
/* Add appropriate includes for your data structures here */

/* Forward Declaration to avoid #include dependencies */
class Tweet;

class User {
 public:
  /**
   * Constructor 
   */
  User();

  User(std::string name);

  /**
   * Destructor
   */
  ~User();

  /**
   * Gets the name of the user 
   * 
   * @return name of the user 
   */
  std::string name();

  /**
   * Gets all the followers of this user  
   * 
   * @return Set of Users who follow this user
   */
  Set<User*> followers();

  /**
   * Gets all the users whom this user follows  
   * 
   * @return Set of Users whom this user follows
   */
  Set<User*> following();

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  AList<Tweet*> tweets();

  /**
   * Adds a follower to this users set of followers
   * 
   * @param u User to add as a follower
   */
  void addFollower(User* u);

  /**
   * Adds another user to the set whom this User follows
   * 
   * @param u User that the user will now follow
   */
  void addFollowing(User* u);

  /**
   * Adds the given tweet as a post from this user
   * 
   * @param t new Tweet posted by this user
   */
  void addTweet(Tweet* t);

  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  AList<Tweet*> getFeed();

  friend std::ostream& operator<<(std::ostream& os, const User*& u){

    os << u->Name;

    return os;

  }
  

  bool operator==(const User&);

 private:


  std::string Name;

  Set<User*> Followers;
  Set<User*> Following;
  AList<Tweet*> Tweets;
  AList<Tweet*> Feed;

 /* Add appropriate data members here */

};

#endif