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
   * @return set of Users who follow this user
   */
  std::set<User*> followers();

  /**
   * Gets all the users whom this user follows  
   * 
   * @return set of Users whom this user follows
   */
  std::set<User*> following();

  /**
   * Gets all the tweets this user has posted
   * 
   * @return List of tweets this user has posted
   */
  std::vector<Tweet*> tweets();

  std::vector<Tweet*> mentionstweets();

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

  void addMentions(Tweet* t);

  void addMentioned(Tweet* t);

  void makeFeed();

  void makeMentionedFeed();

  void deleteFeed();

  void deleteMentionedFeed();


  /**
   * Produces the list of Tweets that represent this users feed/timeline
   *  It should contain in timestamp order all the tweets from
   *  this user and all the tweets from all the users whom this user follows
   *
   * @return vector of pointers to all the tweets from this user
   *         and those they follow in timestamp order
   */
  std::vector<Tweet*> getFeed();
  std::vector<Tweet*> getMentionedFeed();


  friend std::ostream& operator<<(std::ostream& os, const User*& u){

    os << u->Name;

    return os;

  }
  

  bool operator==(const User&);

 private:


  std::string Name;

  std::set<User*> Followers;
  std::set<User*> Following;

  std::vector<Tweet*> Tweets;
  std::vector<Tweet*> MentionsTweets;
  std::vector<Tweet*> MentionedTweets;

  std::vector<Tweet*> Feed;
  std::vector<Tweet*> MentionedFeed;

 /* Add appropriate data members here */

};

#endif