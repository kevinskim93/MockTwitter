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
 * Returns all the strings in the tweet starting with a '#' (removing the # from the word)
 * 
 * @return unique words starting with a '#' symbol
 */
  std::set<std::string> getHashTags(){


  }

  bool Tweet::operator<(const Tweet& other){
    return _time < other._time;
  }

  bool Tweet::operator>(const Tweet& other){
    return _time > other._time;
  }

  std::ostream& operator<<(std::ostream& os, const Tweet& t){

    os << t._time << " " << t._text;
    return os;

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