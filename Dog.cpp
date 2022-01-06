/*
 * Dog.cpp
 *
 *  Created on: Mar 4, 2021
 *      Author: Nafisa Maryam, Camila McCusker
 */

//constructors
#include <iostream>
#include "Dog.hpp"

using namespace std;

#ifndef DOG_CPP_
#define DOG_CPP_

Dog::Dog(string n){
	name = n;
	strength = 50;
	x = 0;
	y = 0;
}

Dog::Dog(){
	name = 'fluffy';
	strength = 50;
	x = 0;
	y = 0;
}

bool Dog::changeStrength(int amt){
	strength = amt + strength;
	printDog();
	if( strength > 0){
		return true;
	}
	else{
		return false;
	}
	if(strength <= 0){
		die();
	}

}

void Dog::die(){
	cout << "death has fallen upon your poor pup, do better!" << endl;
}

void Dog::printDog(){
	cout << "Fluffy has " << strength << " strength currently" << endl;
}

void Dog::won(){
	cout << "You helped fluffy get through the forest, great job!" << endl;
}

void Dog::reset(){
	strength = 50;
	x = 0;
	y = 0;
}


#endif /* DOG_CPP_ */
