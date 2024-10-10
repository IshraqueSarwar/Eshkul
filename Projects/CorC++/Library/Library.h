#include <iostream>
#include <string>
#include <fstream>
#include "Book.h"

using namespace std;
#ifndef LIBRARY_H
#define LIBRARY_H

//Constants
const int NUM_BOOKS = 965; //Total number of books in input file
const int MAX_WAIT = 5; //Maximum books on user wait list
const char DELIMETER = '|'; //Symbol between each variable in input file
const int INCR = 10; //Number of books displayed at a time (10 per screen)

class Library{
 public:
  //Name: Library - Default Constructor
  //Precondition: None
  //Postcondition: Creates a new Library
  Library();
  //Name: Library - Overloaded Constructor
  //Precondition: None
  //Postcondition: Creates a new Library and passes the book filename
  Library(string filename);
  //Name: LoadCatalog(string filename)
  //Precondition: Requires filename
  //Postcondition: Loads the file into the m_bookCatalog (as books)
  //Note: You are permitted to use stoi (string to integer) and stod
  // (string to double) to convert during loading of catalog
  void LoadCatalog(string filename);
  //Name: MainMenu
  //Precondition: None
  //Postcondition: Manages the application and the menu
  void MainMenu();
  //Name: DisplayBooks
  //Precondition: Displays the master list of all books in catalog
  //Postcondition: Lists all books (numbered starting at 1)
  //Note: Displays 10 books per screen using constant INCR
  //If the user enters Q or q, the program stops displaying
  //  books and returns to main menu else displays next 10 books
  void DisplayBooks();
  //Name: SearchCatalog()
  //Precondition: Requires m_bookCatalog
  //Postcondition: Searches m_bookCatalog by title
  //Note: Use string function of .find to search for any part of string
  void SearchCatalog();
  //Name: AddBook
  //Precondition: m_bookCatalog is populated
  //Postcondition: Displays the current list and copies a book to m_waitList
  //               Increments m_waitCount and limits capacity to MAX_WAIT
  void AddBook();
  //Name: BookExist(Book)
  //Precondition: m_bookCatalog is populated
  //Postcondition: Helper function to check if passed book exists in m_waitList. Returns true if exists in m_waitList else false
  bool BookExist(Book book);
  //Name: DisplayWaitList
  //Precondition: m_bookCatalog is populated
  //Postcondition: Displays the WaitList using DisplayBook
  void DisplayWaitList();
private:
  Book m_bookCatalog [NUM_BOOKS]; //Holds all books in file
  Book m_waitList [MAX_WAIT]; //Holds all books in wait list
  int m_waitCount; //Keeps track of how many books on wait list
};

#endif
