#include <iostream>
#include <string>
#include "Airport.h"


using namespace std;

// Default constructor
Airport::Airport(): m_code(""), m_name(""), m_city(""), m_country(""), m_north(0.0), m_west(0.0){}

// Overloaded constructor
Airport::Airport(string code, string name, string city, string country, double north, double west)
{
	Airport::m_code = code;
	Airport::m_name = name;
	Airport::m_city = city;
	Airport::m_country = country;
	Airport::m_north = north;
	Airport::m_west = west;
}






// Airport::~Airport(){

// }

void Airport::SetNext(Airport*){
	*m_next = Airport;
}

string Airport::GetCode(){
	return m_code;
}

string Airport::GetName(){
	return m_name;
}

Airport* Airport::GetNext(){
	return m_next;
}


double Airport::GetNorth(){
	return m_north;
}	


double Airport::GetWest(){
	return m_west;
}

string Airport::GetCity(){
	return m_city;
}


string Airport::GetCountry(){
	return m_country;
}

// int main(){
// 	return 0;
// }