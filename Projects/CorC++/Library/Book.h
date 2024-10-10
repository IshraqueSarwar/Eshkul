#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#ifndef BOOK_H //Header Guards
#define BOOK_H //Header Guards

class Book{
 public:
  //Name: Book - Default Constructor
  //Precondition: None
  //Postcondition: Creates a default book (0, "default", "default", 0.00)
  Book();
  //Name: Book - Overloaded Constructor
  //Precondition: Requires year, title, author, and their aggregated score (rating)
  //Postcondition: Creates a book based on passed parameters
  Book(int year, string title, string author,  double score);

  //Name: Mutators and Accessors
  //Precondition: None
  //Postcondition: Sets and Gets private member variables
  int GetYear(); //return year
  string GetTitle(); // return title
  string GetAuthor(); // return author(s)
  double GetScore(); // return rating score
  void SetYear(int year); //sets year
  void SetTitle(string title); //sets title
  void SetAuthor(string author); //sets author(s)
  void SetScore(double score); //sets score
  
  //Name: DisplayBook
  //Precondition: Requires book variables to be populated
  //Postcondition: None
  //Desc: Displays the information about the book
  void DisplayBook(); //displays information about book with the format:
  //                  *Title* (*Year*) by *Author(s)* with a score of *Score*
private:
  int m_year; //Year of book
  string m_title; //Title of book
  string m_author; //Author(s) of book
  double m_score; //Aggregated score (rating)
};

#endif
