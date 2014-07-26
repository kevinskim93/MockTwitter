#include "../include/datetime.h"

/**
   * Constructor
   */
  DateTime::DateTime(){

  }

  /**
   * Another constructor 
   */
  DateTime::DateTime(int hh, int mm, int s, int year, int month, int day){
    hour = hh;
    minute = mm;
    second = s;
    this->year = year;
    this->month = month;
    this->day = day;

    std::stringstream ss;
    ss << hour;
    ss >> sHour;
    ss.clear();
    ss.str("");

    ss << minute;
    ss >> sMinute;
    ss.clear();
    ss.str("");

    ss << second;
    ss >> sSecond;
    ss.clear();
    ss.str("");

    ss << year;
    ss >> sYear;
    ss.clear();
    ss.str("");

    ss << month;
    ss >> sMonth;
    ss.clear();
    ss.str("");

    ss << day;
    ss >> sDay;
    ss.clear();
    ss.str("");

    dateTime = sYear+"-"+sMonth+"-"+sDay+" "+sHour+":"+sMinute+":"+sSecond;
  }

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */

  const std::string& DateTime::stringTime() const{

    //std::string Time = "yes";
    return dateTime;
  }

  bool DateTime::operator<(const DateTime& other){      

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
          if(hour < other.hour){
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

    return false;
  }

  /**
   * Return true if the timestamp is greater-than other's
   *
   * @return result of greater-than comparison of timestamp
   */
  bool DateTime::operator>(const DateTime& other){
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
          if(hour < other.hour){
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

    return false;
  }

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH::MM::SS
   *
   * @return the ostream passed in as an argument
   */
	std::ostream& operator<<(std::ostream& os, const DateTime& other){

    os << other.year << "-" << other.month << "-" <<other.day << " ";

    if(other.hour == 00){
      os << "00";
    }
    else{
      os << other.hour;
    }
    
    os << ":";

    if(other.minute == 0){
      os << "00";
    }
    else{
      os << other.minute;
    }
    os << ":";

    if(other.second == 0){
      os << "00";
    }
    else{
      os << other.second;
    }
    
    return os;
  }

