#ifndef TWEET_H
#define TWEET_H
#include <iostream>
#include <string>
#include "datetime.h"

/* Forward declaration */
class User;

/**
 * Models a tweet and provide comparison and output operators
 */
class Tweet
{
 public:
  /**
   * Default constructor 
   */
  Tweet();

  /**
   * Constructor 
   */
  Tweet(User* user, DateTime& time, std::string& text);

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & time() const;

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  std::string const & text() const;

  /**
   * Return true if this Tweet's timestamp is less-than other's
   *
   * @return result of less-than comparison of tweet's timestamp
   */
  bool operator<(const Tweet& other){
    return _time < other._time;
  }

  /**
   * Return true if this Tweet's timestamp is greater-than other's
   *
   * @return result of greater-than comparison of tweet's timestamp
   */
  bool operator>(const Tweet& other){
    return _time > other._time;
  }

  /**
   * Outputs the tweet to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS username tweet_text
   *
   * @return the ostream passed in as an argument
   */
  friend std::ostream& operator<<(std::ostream& os, const Tweet& t);

  /* Create any other public or private helper functions you deem 
     necessary */


 private:
  DateTime _time;
  std::string _text;

  /* Add any other data members you need here */


};

/* Leave this alone */
struct TweetComp
{
  bool operator()(Tweet* t1, Tweet* t2)
  {
    return (*t1 > *t2);
  }
};
#endif