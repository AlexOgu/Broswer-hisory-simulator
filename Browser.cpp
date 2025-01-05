#include "Browser.h"
#include <iostream>
#include <sstream>
using namespace std;

//This will set m_fileName and m_currentPage to nullpt
Browser::Browser(string filename):
 m_currentPage(nullptr), 
 m_fileName(filename) {}

Browser::~Browser() {
    if (m_currentPage) {
        delete m_currentPage;
        m_currentPage = nullptr;
    }

    // This will clear the stacks 
    while (!m_backStack.IsEmpty()) {
        delete m_backStack.Pop();
    }
    while (!m_forwardStack.IsEmpty()) {
        delete m_forwardStack.Pop();
    }
}

void Browser::StartBrowser() {
    cout << "Welcome to the Browser History Simulator\n"; 
    LoadFile(); 
    Menu();  
}

void Browser::Menu() {
    int choice;
    do {
        cout << "\nCurrent Website:\n" <<*m_currentPage << endl;
        cout << "\nWhat would you like to do?\n";
        cout << "1. Display Browser History\n";
        cout << "2. Go Back\n";
        cout << "3. Go Forward\n";
        cout << "4. Visit Site\n";
        cout << "5. Quit\n";
        cout << "";
        cin >> choice;
        
        // These are the cases for the menu and repeats if not 1-5
        switch (choice) {
            case 1:
                Display();
                break;
            case 2:
                Back(1); 
                break;
            case 3:
                Forward(1); 
                break;
            case 4:
                NewVisit();
                break;
            case 5:
                cout << "Ending Browser History Simulator\n";
                break;
        }
    } while (choice != 5);
}

// This will add a new URL to m_backStack 
void Browser::Visit(const string& url, int timestamp) {
    if (m_currentPage) {
        m_backStack.Push(m_currentPage);
        m_currentPage = nullptr;
    }
    m_currentPage = new NavigationEntry(url, timestamp);
}

void Browser::NewVisit() {
    cout << "Enter the URL of the new site:\n ";
    cin.ignore();
    string url;
    getline(cin, url);

    // This will take the user the new site at specific time
    Visit(url, chrono::system_clock::to_time_t(chrono::system_clock::now()));
}

void Browser::Display() {
    cout << "\n**Back Stack**\n"
         << (m_backStack.IsEmpty() ? "Empty\n" : "");

    // This will display the websites if not empty
    if (!m_backStack.IsEmpty()) {
        for (size_t i = 0; i < m_backStack.GetSize(); i++) {
            cout << (i + 1) << ". " << *m_backStack.At(i) << '\n';
        }
    }

    //This checks whether or not the stack is empty
    cout << "\n**Forward Stack**\n"
         << (m_forwardStack.IsEmpty() ? "Empty\n" : "");
    if (!m_forwardStack.IsEmpty()) {
        for (size_t i = 0; i < m_forwardStack.GetSize(); i++) {
            cout << (i + 1) << ". " << *m_forwardStack.At(i) << '\n';
        }
    }
}

NavigationEntry Browser::Back(int steps) {
    while (steps > 0 && !m_backStack.IsEmpty()) {
        m_forwardStack.Push(m_currentPage);
        m_currentPage = m_backStack.Pop();
        steps--;
    }

    // This will let the user know if the stack is empty or not
    if (steps > 0 && m_backStack.IsEmpty()) {
        cout << "Empty\n";
    }
    return *m_currentPage;
}

NavigationEntry Browser::Forward(int steps) {

    //This will go foward in history until empty
    for (int i = 0; i < steps && !m_forwardStack.IsEmpty(); ++i) {
        m_backStack.Push(m_currentPage);
        m_currentPage = m_forwardStack.Pop();
    }

    // This will let the user know if the stack is empty or not
    if (m_forwardStack.IsEmpty()) {
        cout << "Empty\n";
    }
    return *m_currentPage;
}

NavigationEntry Browser::GetCurrentPage() const {
    return *m_currentPage;
}

void Browser::LoadFile() {
    ifstream file(m_fileName);
    if (!file) { 
        cout << "Failed to open file: " << m_fileName << endl;
        return;
    }

    //This will go through each line one by one and convert the timestamps
    string line;
    while (getline(file, line)) {
        size_t delimiterPos = line.find(DELIMITER);

        //This will use npos to check if the delimiter is located in the line
        //then record the specific times and urls
        if (delimiterPos != string::npos) { 
            string url = line.substr(0, delimiterPos);
            string timestampStr = line.substr(delimiterPos + 1);
            int timestamp = stoi(timestampStr);
            m_backStack.Push(new NavigationEntry(url, timestamp));
        }
    }
    
    //This will check if the stack is empty to set page
    if (!m_backStack.IsEmpty()) {
        m_currentPage = m_backStack.Pop();
    }
}

