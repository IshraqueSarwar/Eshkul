#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <string.h>
#include <stdint.h>

#define true 1
#define false 0

int ROWS;
int COLS;

void init_world(char *ptr);
void print_world(char *ptr);

int main(int argc, char **argv){
	// This is to grab the dimentions from the terminal
	ROWS =atoi(argv[1])+2; COLS = atoi(argv[2])+2;

	char world[ROWS*COLS];

	char *ptr = &world[0];
	init_world(ptr);
	print_world(ptr);

	
}

void init_world(char *ptr){
	char *end_ptr = ptr+(ROWS*COLS);
	int i = 1;
	for(;ptr!=end_ptr; ptr++){
		
		if(!(i % COLS)){
			*ptr = '|';
		}else{
			*ptr = ' ';
		}

		i++;
	}
}

void print_world(char *ptr){
	char *end_ptr = ptr+(ROWS*COLS);
	int i =1;
	for(;ptr!=end_ptr; ptr++){
		if(!(i%COLS) ){

			printf("%c\n",*ptr);
		}else{

			printf("%c",*ptr);
		}
		i++;
		
	}
}