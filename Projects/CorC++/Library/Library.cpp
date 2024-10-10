#include "Library.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Library::Library(){}


Library::Library(string filename){
    Library::LoadCatalog(filename);
}



//loading books on an array
void Library::LoadCatalog(string filename){
    int count = 0;

    //read the txt file line by line
    // variables for reading the file
    ifstream books(filename);
    

     //checking if file opendd
    if (!books.is_open()){
        cout << "Failed to open the file!" << endl;
        return;
    }

    // this is the indicator of our readings and when it completes.
    string year_from_line;
    while (getline(books, year_from_line, DELIMETER)){
        int year = stoi(year_from_line);

        string title;
        getline(books, title, DELIMETER);

        string author;
        getline(books, author, DELIMETER);


        // the final delimeter is end line character.
        string score_from_line;
        getline(books, score_from_line, '\n');
        double score = stod(score_from_line);

        // making a book object using the informations extracted.
        Book book_to_add;
        book_to_add.SetTitle(title);
        book_to_add.SetAuthor(author);
        book_to_add.SetScore(score);
        book_to_add.SetYear(year);

       
        // finally we add the new book(object) to the library catalog(array)
        Library::m_bookCatalog[count] = book_to_add;

        count++;
    }
    cout<<"Catalog populated with "<<NUM_BOOKS<<" books.\n";
}


// write the display function.
void Library::DisplayBooks(){
    int start_index = 0;
    int index = 0;
    string user_input;
    while(user_input!="Q" && user_input!="q"){
        while(index<start_index+10 && index<NUM_BOOKS){
            cout<<"  "<<index+1<<". "<<m_bookCatalog[index].GetTitle()<<" ("<<m_bookCatalog[index].GetYear()<<") by "<<m_bookCatalog[index].GetAuthor()<<" with a score of "<<m_bookCatalog[index].GetScore()<<endl;
            index++;
        }
        cout<<"N for Next, Q to quit\n";
        getline(cin, user_input);
        // cin>>user_input;
        if(user_input=="N" || user_input == "n"){
            start_index = index;
            // index++;
        }
    }
}


void Library::SearchCatalog(){
    
    string user_input;
    cout<<"What title would you like to search for?\n";
    getline(cin, user_input);

    bool found = false;
    for(int i = 0;i<NUM_BOOKS;i++){
        string book_title = m_bookCatalog[i].GetTitle();
        
        int pos = 0;
        pos = book_title.find(user_input, pos++);
        if(pos!=string::npos){
            cout<<"  "<<i+1<<". "<<m_bookCatalog[i].GetTitle()<<" ("<<m_bookCatalog[i].GetYear()<<") by "<<m_bookCatalog[i].GetAuthor()<<" with a score of "<<m_bookCatalog[i].GetScore()<<endl;
            found = true;
        }
    }
    if(!found){
        cout<<"No books with that title found.\n";
    }

}


bool Library::BookExist(Book book){
    bool book_exists = true;
    for(int i = 0;i<MAX_WAIT;i++){
        if(m_waitList[i].GetTitle()==book.GetTitle()){
            book_exists=false;
            break;
        }
        
    }

    return book_exists;
}



void Library::AddBook(){
    if(m_waitCount == MAX_WAIT){
        cout<<"No additional books can be added to the wait list.\n";
    }else{
        while(true){
            cout<<"Which book would you like to add? (-1 for list)\n";
            // we check if input is -1--> we display books
            // we check if book number within range
            //      |
            //      |--> if in range, we check if book in waiting list or not. if not we add it
            // if not in range, we print Invalid number

            string user_input;
            getline(cin, user_input);
            if(stoi(user_input)>=1 && stoi(user_input)<=NUM_BOOKS){
                
                // we push the book to the wait list if book is available
                int book_index = stoi(user_input)-1;
                if(Library::BookExist(m_bookCatalog[book_index])){    
                    m_waitList[m_waitCount] = m_bookCatalog[book_index];
                    m_waitCount++;
                    break;
                }else{
                    cout<<m_bookCatalog[book_index].GetTitle()<<" already on waitlist.\n";
                }
            
            }else if(stoi(user_input)==-1){
                Library::DisplayBooks();

            }else{
                cout<<"Invalid number!\n";
            }
        
        }
    }
   

}


void Library::DisplayWaitList(){
    cout<<m_waitCount<<endl;
    cout<<"**Current Waitlist**\n";
    for(int i = 0;i<m_waitCount;i++){
        cout<<i+1<<". "<<m_waitList[i].GetTitle()<<" ("<<m_waitList[i].GetYear()<<") by "<<m_waitList[i].GetAuthor()<<" with a score of "<<m_waitList[i].GetScore()<<endl;
    }
}



void Library::MainMenu(){
    m_waitCount=0;
    while(true){
        cout<<"What would you like to do?\n1. Display All Books\n2. Search Catalog for Book Title\n3. Add Book to Waitlist\n4. Display Waitlist\n5. Quit\n";

        string user_input;
        getline(cin, user_input);
        
        // cin>>user_input;
        // we exit if q or Q is pressed
        // TODO: WE NEED USER VALIDATION!!!!
        if(user_input=="q" || user_input == "Q" || stoi(user_input)==5){
            cout<<"Thank you for using the UMBC Library\n";
            break;
        }else if(stoi(user_input)==1){
            Library::DisplayBooks();
        }else if( stoi(user_input)==2){
            Library::SearchCatalog();
        }else if( stoi(user_input)==3){
            Library::AddBook();
        }else if(stoi(user_input)==4){
            Library::DisplayWaitList();
        }
    }

}