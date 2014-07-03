#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>

/**
 * Models a timestamp in format YYYY-MM-DD HH:MM:SS 
 */
struct DateTime
{
  /**
   * Constructor
   */
  DateTime(){

  }

  /**
   * Another constructor 
   */
  DateTime(int hh, int mm, int ss, int year, int month, int day){
    hour = hh;
    minute = mm;
    second = ss;
    this->year = year;
    this->month = month;
    this->day = day;

  }

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */
  bool operator<(const DateTime& other){
    if(year < other.year){
      return true;
    }

    else if(year > other.year){
      return false;
    }

    else if(year == other.year){
      if(month < other.month){
        return true;
      }
      else if (month > other.month){
        return false;
      }

      else if (month == other.month){
        if(day < other.day){
          return true;
        }
        else if (day > other.day){
          return false;
        }
        else if (day == other.day){
          if(hour < other.day){
            return true;
          }
          else if(hour > other.hour){
            return false;
          }
          else if(hour == other.hour){
            if(minute < other.minute){
              return true;
            }
            else if (minute > other.minute){
              return false;
            }
            else if (minute == other.minute){
              if(second < other.second){
                return true;
              }
              else if(second > other.second){
                return false;
              }
              else if(second == other.second){
                return true;
              }
            }
          }
        }
      }
    }

    return true;
  }

  /**
   * Return true if the timestamp is greater-than other's
   *
   * @return result of greater-than comparison of timestamp
   */
  bool operator>(const DateTime& other){
    if(year < other.year){
      return false;
    }

    else if(year > other.year){
      return true;
    }

    else if(year == other.year){
      if(month < other.month){
        return false;
      }
      else if (month > other.month){
        return true;
      }

      else if (month == other.month){
        if(day < other.day){
          return false;
        }
        else if (day > other.day){
          return true;
        }
        else if (day == other.day){
          if(hour < other.day){
            return false;
          }
          else if(hour > other.hour){
            return true;
          }
          else if(hour == other.hour){
            if(minute < other.minute){
              return false;
            }
            else if (minute > other.minute){
              return true;
            }
            else if (minute == other.minute){
              if(second < other.second){
                return false;
              }
              else if(second > other.second){
                return true;
              }
              else if(second == other.second){
                return true;
              }
            }
          }
        }
      }
    }

    return true;
  }

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS
   *
   * @return the ostream passed in as an argument
   */
  friend std::ostream& operator<<(std::ostream& os, const DateTime& other){

    os << other.year << "-" << other.month << "-" <<other.day << " " <<other.hour <<"::"<<other.minute<<"::"<<other.second;
    
    return os;
  }

  /* Add data members here -- they can all be public 
   * which is why we've made this a struct */

  int hour;
  int minute;
  int second;
  int year;
  int month;
  int day;



};

#endif