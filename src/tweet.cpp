#include "../include/tweet.h"
#include <string> 

  /**
   * Default constructor 
   */
  Tweet::Tweet(){

  }

  /**
   * Constructor 
   */
  Tweet::Tweet(User* user, DateTime& time, std::string& text){
    _time = time;
    _text = text;
    _user = user;

  }

  /**
   * Gets the timestamp of this tweet
   *
   * @return timestamp of the tweet
   */
  DateTime const & Tweet::time() const{
    return _time;

  }

  /**
   * Gets the actual text of this tweet
   *
   * @return text of the tweet
   */
  std::string const & Tweet::text() const{
    return _text;

  }