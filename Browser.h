#ifndef BROWSER_H 
#define BROWSER_H 

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> //For timestamps
#include <chrono> //For timestamps
#include "Stack.cpp"
#include "NavigationEntry.h"

using namespace std;

//Constants
const char DELIMITER = ',';

class Browser {
 public:
  Browser(string filename);
  ~Browser();
  void StartBrowser();
  void Menu();
  void Visit(const string& url, int timestamp);
  void NewVisit();
  void Display();

  NavigationEntry Back(int steps);
  NavigationEntry Forward(int steps);
  NavigationEntry GetCurrentPage() const;
 
  void LoadFile();
 private:
  Stack<NavigationEntry*> m_backStack; //History of sites you have already viewed
  Stack<NavigationEntry*> m_forwardStack; //Sites you viewed but went back from
  NavigationEntry* m_currentPage; //Site you are currently viewing
  string m_fileName; //Name of the input file to import browsing history
};

#endif
