#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
// #include <string>

#define HYPHEN "-"
#define QUIT "quit"
#define SWITCH_CONNECT "switch-connect"
#define SWITCH_ADD "switch-add"
#define PHONE_ADD "phone-add"
#define NETWORK_SAVE "network-save"
#define NETWORK_LOAD "network-load"
#define START_CALL "start-call"
#define END_CALL "end_call"
#define DISPLAY "display"


using namespace std;



char* strip(char* s){
 	
} 


int main(int argv, char **argc){
    // areacode_trunk unordered_map<int, vector<int>>
	// areacode_phone unordered_map<int, unordered_map<int, int>>
	
	char s[40];
	// cout<<"Enter Command: ";
	// cin>>s;

	while(s!=QUIT){

		cout<<"Enter Command: ";
		cin.getline(s, sizeof(s));
		cout<<s<<endl;
	}

	return 0;
}