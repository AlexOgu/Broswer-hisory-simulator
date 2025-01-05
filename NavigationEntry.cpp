#include "NavigationEntry.h"
#include <iostream>
#include <iomanip>
using namespace std;

NavigationEntry::NavigationEntry() : 
m_url(""), 
m_timeStamp(0) {}


NavigationEntry::NavigationEntry(const string& url, const int& timestamp) : 
m_url(url), 
m_timeStamp(timestamp) {}

string NavigationEntry::GetURL() const {
    return m_url;
}

int NavigationEntry::GetTimeStamp() const {
    return m_timeStamp;
}

void NavigationEntry::SetURL(const string& url) {
    m_url = url;
}

void NavigationEntry::SetTimeStamp(const int& time) {
    m_timeStamp = time;
}

bool NavigationEntry::IsEmpty() const {
    return m_url.empty();
}

ostream& operator<<(ostream& os, NavigationEntry& entry) {
    os << "URL: " << entry.GetURL() << " Visited On: " 
       << entry.DisplayTimeStamp(entry.GetTimeStamp());
    return os;
}


































