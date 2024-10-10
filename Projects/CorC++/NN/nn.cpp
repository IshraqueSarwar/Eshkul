#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;


int main(){
	vector<float>inputs = {1f,2f,3f,2.5f};
	vector<vector<float>>weights = {{0.2f, 0.8f, -0.5f, 1f},
									{0.5f, -0.91f, 0.26f, -0.5f},
									{-0.26f, -0.27f, 0.17f, 0.87f}};
	vector<float>biases = {2,3,0.5};

	vector<float>output_layers;

	for(int i = 0;i<biases.size();i++){
		cout<<biases;

	}


	return 0;
}