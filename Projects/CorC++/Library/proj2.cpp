#include <iostream>
#include <string>
#include <iomanip>
#include "Library.h"
#include "Book.h"

using namespace std;

//This version of main allows the program to take command-line arguments.
//For example, ./proj2 proj2_books.txt (proj2_books.txt is an argument)
//  The first argument, argc (argument count) is an integer that
//    represents the number of command-line arguments passed to the
//    program when it's executed.
//  The second argument, argv (argument vector) is an array of
//    C-style strings (char*), where each element in the array is
//    one of the command-line arguments passed to the program.
//    These strings represent the arguments as null-terminated
//    character arrays.

//The usage for this is ./proj2 proj2_books.txt where the
//           proj2_books.txt is the name of the input file

int main (int argc, char* argv[]) {
  string bookFile; //Stores the name of the input file
  cout << "Welcome to UMBC Library"<<endl;
  if(argc > 1){ //Checks to make sure that the user passed a file name
    bookFile = argv[1]; //Sets the input file as argv[1]
  } else{
    cout << "One book files required - try again" << endl;
    cout << "./proj2 proj2_books.txt" << endl;
    return 0;
  }
  Library myLibrary(bookFile); //Creates a new Library object

  myLibrary.MainMenu(); //Calls the MainMenu function of the Library

 
  return 0;
}
