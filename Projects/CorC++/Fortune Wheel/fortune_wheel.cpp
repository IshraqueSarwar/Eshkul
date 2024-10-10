#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>


// #define NAME_OF_INPUT_FILE "proj1_data.txt"
using namespace std;

const int NUM_LINES = 46;
const char NAME_OF_INPUT_FILE[15] = "proj1_data.txt";



// FUNCTION 1
string get_category_and_puzzle(string category[NUM_LINES/2], string puzzle[NUM_LINES/2]){
	string prompt;

	//randomising the rand seed using the curr time
	srand(time(NULL));


	int random_idx = rand()%(NUM_LINES/2);
	prompt = category[random_idx]+"--"+puzzle[random_idx];

	return prompt;
}



// FUNCTION 2
void print_how_many_characters_found(string puz, char user_input){
	int count = 0;
	for(int i = 0;i<puz.length();i++){
		if(puz[i]==user_input){
			count++;
		}
	}

	if(count){
		cout<<count<<" "<<user_input<<" found in the puzzle.\n";
	}else{
		cout<<"No "<<user_input<<" found in the puzzle.\n";
	}

}




// FUNCTION 3
bool view_puzzle_and_return_if_all_found(string puz, string used_char){
	bool all_found = true;
	for(int i = 0;i<puz.length();i++){
		if(puz[i]==' '){
			cout<<" ";
		}else{
			bool matched = false;
			for(int j = 0;j<used_char.length();j++){
				if(puz[i]==used_char[j]){
					cout<<used_char[j];
					matched = true;
				}
			}
			if(!matched){
				cout<<"_";
				all_found = false;
			}
		}


	}
	cout<<"\n";

	return all_found;
}



// FUNCTION 4
string game_loop(string puz, string used_char){

	// showing the puzzle before taking input
	bool all_found = view_puzzle_and_return_if_all_found(puz, used_char);
	
	if(!all_found){
		bool valid_input = false;
		while(!valid_input){
			char user_input;
			cout<<"What letter would you like to try?\n";
			cin>>user_input;
			// make sure the letters are capital
			if(isupper(user_input)){

				bool char_used = false;

				for(int i=0;i<used_char.length();i++){
					if(used_char[i]==user_input){
						char_used = true;
						break;
					}
				}

				if(!char_used){
					used_char+=user_input;
					valid_input = true;
					print_how_many_characters_found(puz, user_input);

				}else{
					cout<<"That letter was already used!\nEnter something different\n";
				}
			}else{
				cout<<"Enter an upper case letter only\n";
			}

		}

	}

	return used_char;

}




// FUNCTION 5
void read_puzzles_from_file(string category[NUM_LINES/2], string puzzle[NUM_LINES/2]){
	//opening the file
	ifstream File(NAME_OF_INPUT_FILE);
	
	// reading the puzzles and categories into two arrays: category and puzzle
	int lines_remaining = NUM_LINES;
	int idx = 0;
	string s;
	while(lines_remaining){
		int line_no = NUM_LINES-lines_remaining;

		getline(File,s);
		
		if(line_no%2){
			if(idx<(NUM_LINES/2)){
				s.pop_back();
			}//<-- this is to check if the sentence is the last one, in which case, there is no '\n'
			puzzle[idx] = s;
			idx++;
		}else{
			s.pop_back();//<--remove '\n'
			category[idx] = s;
		}

		lines_remaining--;
	}

}

bool update_game_over(string puz, string used_char){
	bool game_over = true;
	for(int i = 0;i<puz.length();i++){
		if(puz[i]!=' '){
			bool matched = false;
			for(int j = 0;j<used_char.length();j++){
				if(puz[i]==used_char[j]){
					matched = true;
				}
			}
			if(!matched){
				game_over = false;
			}
		}

	}
	if(game_over){
		cout<<puz<<"\nYou won!\n";
	}
	return game_over;
}


int main(int argc, char const *argv[])
{

	// reading the puzzles and categories into two array
	string category[NUM_LINES/2]; 
	string puzzle[NUM_LINES/2];
	read_puzzles_from_file(category, puzzle);


	// Introduction text
	cout<<"Welcome to UMBC Fortune Wheel!\n24 puzzles loaded.\n";
	
	// getting the category name and puzzle
	string qs = get_category_and_puzzle(category, puzzle);
	string cat = qs.substr(0, qs.find("--"));
	string puz = qs.substr(qs.find("--")+2, qs.length());

	// Telling the Player what category it is
	cout<<"Category is:"<<cat<<"\n";


	string used_char="";
	bool game_over = false;



	////???NOTE???? USE DO WHILE LOOP>>>
	do{
		// view_puzzle(puz, used_char);// WE MIGHT NEED TO CHANGE THIS PART TO INCORPORATE NO OF MATCHES
		used_char = game_loop(puz, used_char);
		game_over = update_game_over(puz, used_char);
		// run_game();
		// break;
	}while(!game_over);

	return 0;
}