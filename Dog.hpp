/*
 * Dog.hpp
 *
 *  Created on: Mar 4, 2021
 *      Author: Nafisa Maryam , Camila McCusker
 */

//Dog class declarations
#ifndef DOG_HPP_
#define DOG_HPP_
#include <iostream>
#include <string.h>
using namespace std;

class Dog {

	friend class Board;
	string name;
	int strength;

	int x;
	int y;

public:


Dog(string n);
Dog();
bool changeStrength(int amt);
void die();
void printDog();
void won();
void reset();

};


#endif /* DOG_HPP_ */
