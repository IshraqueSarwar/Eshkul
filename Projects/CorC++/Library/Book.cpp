#include "Book.h"

//default costructor
Book::Book() {
    m_title = "";
    m_author = "";
    m_year = 0;
    m_score = 0.0;
}
//overloaded constructor
Book::Book(int year, string title, string author,  double score) {
    m_title  = title;
    m_author = author;
    m_year = year;
    m_score = score;
}

//Accessors

string Book::GetTitle(){
    return m_title;
}

string Book::GetAuthor(){return m_author;}

int Book::GetYear() { return m_year;}

double Book::GetScore(){return m_score;}


// mutators

void Book::SetTitle(string title){
    m_title = title;
}

void Book::SetAuthor(string author){
    m_author = author;
}

void Book::SetYear(int year) { m_year = year;}

void Book::SetScore(double score) {m_score = score;}


