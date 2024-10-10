#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "Game.h"
#include "Pokemon.h"

using namespace std;

Game::Game(string filename){
	m_filename = filename;
}

void Game::Start(){
	LoadFile();
	int option_input;
	while(option_input!=6){
		MainMenu();
		cin>>option_input;

		if(option_input == 1){
			DisplayPokeDex();
		}else if(option_input ==2){
			DisplayTeam();
		}else if(option_input == 3){
			CatchPokemon();
		}else if(option_input == 4){
			BattlePokemon();
		}else if(option_input == 5){
			TrainPokemon();
		}
	}


}

void Game::MainMenu(){
	cout<<"What would you like to do?:\n1. Display Complete PokeDex\n2. Display your Team\n3. Search for a new Pokemon\n4. Battle your Pokemon\n5. Train your Pokemon\n6. Exit\n";
}

void Game::LoadFile(){
	ifstream fin(m_filename);

	int lines_remaining = TOTAL_POKEMON;
	int i = 0;
	int num, cp, rarity;
	string name;
	while(lines_remaining){
		int index = TOTAL_POKEMON-lines_remaining;

		string s;
		fin>>s;
		if(i==0){
			num = stoi(s);
			i++;
		}else if(i==1){
			name = s;
			i++;
		}else if(i==2){
			cp = stoi(s);
			i++;
		}else{
			rarity = stoi(s);
			i = 0;
			lines_remaining--;
			Pokemon p(num, name, cp, rarity);
			m_pokeDex[index] = p;
		}

	}

}



void Game::DisplayPokeDex(){
	for(int i = 0;i<5;i++){
		cout<<setw(NUM_WIDTH)<<m_pokeDex[i].GetNum()<<"."
			<<setw(NAME_WIDTH) <<m_pokeDex[i].GetName()<<'\n';
	}
	cout<<"**6-149 Omitted for space**"<<'\n';
	for(int i = 149;i<TOTAL_POKEMON;i++){
		cout<<setw(NUM_WIDTH)<<m_pokeDex[i].GetNum()<<"."
			<<setw(NAME_WIDTH) <<m_pokeDex[i].GetName()<<'\n';
	}
}

int Game::TeamSize(){
	int team_size = 0;
	for(int i =0;i<NUM_TEAM;i++){
		if(m_team[i].GetName()!=""){
			team_size = i+1;
		}
	}
	return team_size;
}


void Game::DisplayTeam(){
	int t_size = TeamSize();
	if (t_size){
		for(int i = 0;i<t_size;i++){
			//NOTE: NEED TO FORMAT WITH WIDTH
			cout<<setw(NUM_WIDTH)<<i+1<<"."
				<<setw(NAME_WIDTH)<<m_team[i].GetName()
				<<setw(NUM_WIDTH)<<m_team[i].GetCP()<<'\n';
		}
	}else{
		cout<<"You have no team yet. Maybe search for a Pokemon?!\n";
	}
}


void Game::CatchPokemon(){
	int rarity_selected = CatchMenu();
	int rand_num = rand()%99;
	

	cout<<"You start a search.\n";
	if((rarity_selected==1 && rand_num<COMMON) || (rarity_selected ==2 && rand_num<UNCOMMON) || (rarity_selected==3 && rand_num<ULTRA)){
		
		Pokemon poke_found = FoundPokemon(rarity_selected);
		cout<<"You found a "+poke_found.GetName()+"."<<endl;
		bool poke_exists = false;
		for(int i =0;i<NUM_TEAM;i++){
			if(m_team[i].GetName()!="" && m_team[i].GetName()==poke_found.GetName()){
				poke_exists = true;
				break;
			}
		}

		if(!poke_exists){
			// reduce pokemon cp by 30-50%
			// generating random reduction factor (0.3-0.5)
			// calculating the reduced CP using (1-cp_recudtion_factor)*ORIGINAL_CP
			// setting the new_CP to the newly found pokemon CP
			double cp_reduction_factor = ((double)MIN_FIND/100)+( ( (double)(rand()%(MAX_FIND-MIN_FIND)) )/100);
			int newCP = (int)((1-cp_reduction_factor)*poke_found.GetCP());
			poke_found.SetCP(newCP);

			// Finally add the new poke to team
			AddPokemon(poke_found);
		}


	}else{
		cout<<"Couldn't find a Pokemon. You can search again\n";
	}

	
}

int Game::CatchMenu(){
	int user_input;
	while(user_input<1 || user_input>3){
		cout<<"What rarity of Pokemon would you like catch?:\n1. Common (High Probability)\n2. Uncommon (Normal Probability)\n3. Ultra Rare (Extremely Low Probability)\n";
		cin>>user_input;
	}
	return user_input;
	
}	


Pokemon Game::FoundPokemon(int rarity){
	while(true){
		int rand_i = rand()%TOTAL_POKEMON;
		if(m_pokeDex[rand_i].GetRarity()==rarity){
			return m_pokeDex[rand_i];
		}
	}
}


void Game::AddPokemon(Pokemon newPoke){
	int lowest_CP = 99999;
	int lowest_CP_index = -1;
	for(int i = 0;i<NUM_TEAM;i++){
		if(m_team[i].GetName()==""){
			m_team[i] = newPoke;
			cout<<newPoke.GetName()+" added to your team!\n";
			return;
		}else{
			if(m_team[i].GetCP()<lowest_CP){
				lowest_CP = m_team[i].GetCP();
				lowest_CP_index = i;
			}
		}
	}

	if(lowest_CP_index!=-1 && lowest_CP<newPoke.GetCP()){
		m_team[lowest_CP_index] = newPoke;
		cout<<newPoke.GetName()+" added to your team!\n";
			
	}
}


int Game::FindPokemon(string name){
	for(int i = 0;i<TOTAL_POKEMON;i++){
		if(m_pokeDex[i].GetName()==name){
			return i;
		}
	}
	return -1;
}


void Game::TrainPokemon(){
	int t_size = TeamSize();
	if(t_size){
		

		int user_input=0;
		while(user_input<1 || user_input>t_size){
			cout<<"Which of your pokemon would you like to use?:\n";
			DisplayTeam();
			cin>>user_input;
		}


		Pokemon poke_selected = m_team[user_input-1];
		int max_trainable_cp = m_pokeDex[FindPokemon(poke_selected.GetName())].GetCP();
		
		if(m_team[user_input-1].GetCP() >= max_trainable_cp){
			cout<<"Your "+ m_team[user_input-1].GetName()+" is already maxed out!\n";
		}else{
			m_team[user_input-1].Train(max_trainable_cp);
			cout<<"Your "+m_team[user_input-1].GetName()+"'s CP goes up!\n";
		}

	}else{
		cout<<"You've no Pokemon in your team to train.\nTry searching for Pokemons first.\n";
	}
}


void Game::BattlePokemon(){
	int t_size = TeamSize();
	if(t_size){
		// getting the random enemy
		// setting its CP to 0-max_cp+200
		int rand_enemy_index = rand()%TOTAL_POKEMON;
		Pokemon random_enemy = m_pokeDex[rand_enemy_index];
		int rand_enemy_cp =  0+ ( rand()%(random_enemy.GetCP()+ENEMY_ADD) );
		cout<<"You are going to fight a "+random_enemy.GetName()+"\nThe enemy has a CP of "<<rand_enemy_cp<<"\n";
		// random_enemy.SetCP(rand_enemy_cp); //We prolly dont need to set the cp for enemy



		// ask user to select a pokemon from their team
		// keep prompting until valid value is given
		int user_input=0;
		while(user_input<1 || user_input>t_size){
			cout<<"Which of your pokemon would you like to use?:\n";
			DisplayTeam();
			cin>>user_input;
		}


		// We battle!
		// Compare the enemy CP and team Poke CP
		if(rand_enemy_cp<m_team[user_input-1].GetCP()){
			// We won the match
			cout<<"Congratultions! You have won the battle!\n";
		}else{
			// WE lose the match
			// Set the team member CP to 0
			cout<<"You lost.\n"+m_team[user_input-1].GetName()+" can't list his head.\nYou should replace it.\n";
			m_team[user_input-1].SetCP(0);

		}

	}else{
		cout<<"You've no Pokemon on your team to battle.\nTry searching for Pokemons first.\n";
	}
}