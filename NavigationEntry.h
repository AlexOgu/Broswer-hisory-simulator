#ifndef NAVIGATION_ENTRY_H 
#define NAVIGATION_ENTRY_H 

#include <string> 
#include <chrono>  // for timestamps
using namespace std;

//Constants

class NavigationEntry {
 public:
  NavigationEntry();
  NavigationEntry(const string& url, const int& timestamp);

  // Accessors (Getters)
  string GetURL() const; //Returns the m_url
  int GetTimeStamp() const; //Returns m_timeStamp
  
  // Mutators (Setters)
  void SetURL(const string& url); //Used to set m_url
  void SetTimeStamp(const int& time); //Used to set m_timeStamp

  bool IsEmpty() const;
  string DisplayTimeStamp(int64_t timestamp){
    // Convert integer timestamp to time_t
    time_t time = static_cast<time_t>(timestamp);
    // Convert time_t to tm structure for local time
    tm* localTime = localtime(&time);
    char buffer[80];
    // Format the date and time
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);
    // Cast formatted output as string and return
    return string(buffer);
  }

  friend ostream& operator<<(ostream&, NavigationEntry&);
 private:
  string m_url;    // URL of the visited website
  int m_timeStamp; // Timestamp of the visit
};

#endif 
