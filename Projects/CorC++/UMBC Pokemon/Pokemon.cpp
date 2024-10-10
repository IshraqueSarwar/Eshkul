#include <iostream>
#include <string>
#include "Pokemon.h"

using namespace std;

Pokemon::Pokemon(): m_num(0), m_name(""), m_CP(0), m_rarity(0){}

Pokemon::Pokemon(int num, string name, int CP, int rarity){
	m_num = num;
	m_name = name;
	m_CP = CP;
	m_rarity = rarity;
}

int Pokemon::GetCP(){
	return m_CP;
}

int Pokemon::GetRarity(){
	return m_rarity;
}

string Pokemon::GetName(){
	return m_name;
}

int Pokemon::GetNum(){
	return m_num;
}

void Pokemon::SetRarity(int newRarity){
	m_rarity = newRarity;
}

void Pokemon::SetName(string newName){
	m_name = newName;
}


void Pokemon::SetCP(int newCP){
	m_CP = newCP;
}

void Pokemon::Train(int maxCP){
	m_CP+=TRAIN_VALUE;
	m_CP = min(m_CP, maxCP);
}


