/*
*	Author: Corey Farnsworth
*   Start Date: 12/14/15
*		Resume Date: 6/27/17
*
*	Description:
*		Text Based Adventure game
*/

#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

#include "actor.h"
#include "inventory.h"
#include "item.h"
#include "player.h"
#include "room.h"

using namespace std;

int chaLevel = 1;  //this will be a global known value.
									//Change to variable once level up system is in

void getName(string &name);	//gets name of character
void start(string name); //asks if they are ready to start the adventure
void actI();
void combat(double chaHealth, double monHealth, double attack, double monAttack, string monName, int monLevel); //runs combat between player and any creature
int chaDamage();
int monDamage();
void time();
void gameover();

int main(){
	srand(time(NULL));
	double chaHealth, monHealth, attack, monAttack;
	string name, monName;
	int monLevel;

	getName(name);
	start(name);
	actI();
	combat(10, 20, attack, monAttack, "Rat", 5);

	return EXIT_SUCCESS;
}

void commandtime(){
		std::this_thread::sleep_for(std::chrono::milliseconds(3000)); //This works!!
}

void getName(string &name){
	cout << "Please enter the name of your character: \n";
	getline(cin,name);
	cout << "Greetings " << name << "." << endl <<endl;
}

void start(string name){
	string startingChoice;
	do{
	cout << "Well, " << name << " are you ready to begin your adventure? (y/n) \n";
	cin >> startingChoice;
		if(startingChoice == "y"){	//yes to adventure
			cout << "Then let us begin.\n";
		}
		else if(startingChoice == "n"){	//no loop
			cout << "Allow me to ask again... I've got all day.\n\n";
			commandtime();

		}
		else{	//input error loop
			cout << "Please enter a valid response.. I haven't much patience.\n";
		}
	}while(startingChoice != "y");

	commandtime();

	cout << "----------ACT I----------" << endl;
}

void actI(){

}

void gameover(){
	cout << "Oh no! Your health has reached 0!\n";
	commandtime();
	cout << "Game Over\n";
	 //add this later with a restart option
}

int chaDamage(){
	int attack;

	switch(chaLevel){
		case 1: attack = rand() % 3 + 1; //1 - 3
			return(attack);
			break;
		case 2: attack = rand() % 4 + 1; //1 - 4
			return(attack);
			break;
		case 3: attack = rand() % 5 + 1; //1 - 5
			return(attack);
			break;
		case 4: attack = rand() % 6 + 1; //1 - 6
			return(attack);
			break;
		case 5: attack = rand() % 7 + 1; //1 - 7
			return(attack);
			break;
		default:
			cout << "ERROR. REACHED END OF CHARACTER DAMAGE LOOP\n";
			return(0);
			break;

	}
}

int monDamage(int monLevel){
	int attack;

	switch(monLevel){
		case 1: attack = rand() % 2 + 1; //1 - 2
			return(attack);
			break;
		case 2: attack = rand() % 3 + 1; //1 - 3
			return(attack);
			break;
		case 3: attack = rand() % 4 + 1; //1 - 4
			return(attack);
			break;
		case 4: attack = rand() % 5 + 1; //1 - 5
			return(attack);
			break;
		case 5: attack = rand() % 6 + 1; //1 - 6
			return(attack);
			break;
		default:
			cout << "ERROR. REACHED END OF MONSTER DAMAGE LOOP\n";
			return(0);
			break;
	}
}

//combat is currently only ever dealing 2 damage
//it proabably has something to do with "attack" variable not being passed
void combat(double chaHealth, double monHealth, double attack, double monAttack, string monName, int monLevel){
//Maybe in future add a high and low level monster warning

	cout << "----------ENTERING COMBAT----------" << endl;
	cout << "Fighting a " << monName << "!\n\n";

	for(int i = 1; i < 100; ++i){

		attack = chaDamage();
		monAttack = monDamage(monLevel);

		monHealth -= attack;
		cout << "You deal " << attack << " damage to " << monName << "!\n";
		cout << "It's current health is " << monHealth << ".\n\n";
		commandtime();

		if(monHealth <= 0){
			cout << "You've defeated " << monName << "!\n";
			break;
		}

		chaHealth -= monAttack;
		cout << "It deals " << monAttack << " damage to you!\n";
		cout << "Your current health is " << chaHealth << ".\n\n";
		commandtime();

		if(chaHealth <= 0){
			gameover();
			break;
		}
	}
	cout << "----------LEAVING COMBAT----------" << endl;
}
