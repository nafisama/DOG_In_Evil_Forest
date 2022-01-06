
/*
 * Board.cpp
 *
 *  Created on: Mar 4, 2021
 *      Author: Nafisa Maryam , Camila McCusker
 */

//constructors
#include "Board.hpp"
#include <iostream>
using namespace std;


Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}

Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;
	wallStrength = 6;
	InitAll();
}

void Board::InitAll() {
	bool keepPlaying = true;
	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = (rand() % size) ;

		endx1= endx;
		endy = size-1;
		mydog.x = startx;
		mydog.y = starty;
		initial_x=startx;

		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}
}

void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}
}

void Board::addFood() {
/* (5 pts) code for the addFood method goes here */
	int foods=0;
	if(level == 'e'){
	// add field size # of food

		foods= 20; //20

	}
	else if (level == 'm'){
		// add size - 2 food
		foods= 18;
	}
	else if(level == 'h'){
		// add size - 4 food
		foods = 16;
	}else{
		foods=20;
	}
    int x, y,i;
	for (i=0; i< foods; ){

		x=rand() % 20  ; // randomly choose row

		y=rand() % 20 ;  // randomly choose column

		if(board[x][y] == '+'){ //

			board[x][y] = 'F';
			i=i+1;
		}
	}

}

void Board::addTraps() {
/* (5 pts) code for the addTraps method goes here */
	int traps;
	if(level == 'e'){
		//add 6 traps
		traps = size-14;

	}
	else if (level == 'm'){
		//add 8 traps
		//cout << rand()%8 << "T";

		traps = size-12;
	}
	else if(level == 'h'){
		//add 10 traps
		traps = size-10;
	}else{
		traps=6;
	}

	int x,y,i;
	for (i=0; i< traps; ){
		 x=rand()%size;
		 y=rand()%size;

		 if(board[x][y]=='+'){
				board[x][y] = 'T';
				i=i+1;
			}
		}

}

void Board::boardConfig() {
/* (8 pts) code for the boardConfig method goes here */
	for(int i=0; i < 21; i++){ //fills board in with +
		for (int j=0; j<21; j++){
			board[i][j] = '+';
		}

	}


	//now for walls

	int wall_count=0;
	int wall_max;
	if(level =='e'){
		wall_max=10;
	}else if(level=='m'){
		wall_max=13;
	}else{
		wall_max=16;
	}

	for(int i=0; i < 20; i++){  //row
		for (int j=0; j<20; j++){ // col

				if( i %2 !=0){ // checking for odd row

					if(wall_count<wall_max){ //for e at most there are 9 walls in a row

						if( rand()%2 == 0) { //Vertical
							int c= rand()%20;
							if(board[i][c]=='+'){
								board[i][c] = '|'; // odd row, random col
								wall_count++;
							}else {
								c=rand()%20;
								board[i][c] = '|'; // odd row, random col
								wall_count++;
							}

						}else{ // horizontal
							int c= rand()%20;
							if(board[i][c]=='+'){
								board[i][c] = '_'; // odd row, random col
								wall_count++;
							}else {
								c=rand()%20;
								board[i][c] = '_'; // odd row, random col
								wall_count++;
							}
						}

					}
				}


	  }
		wall_count=0; // reset wall_count for next row

	}


 // check why startx and endx are  not working
 	 board[mydog.x][mydog.y]='D';
 	 board[endx1][size-1]='E';

}

void Board::printBoard() {
/* (8 pts) code for the printBoard method goes here */

	for(int r=0; r<=21;r++){
		cout<<endl;
		for(int c=0; c<=21;c++){

			if(r==0 || r==21){// print horizontal border

				cout<< "_";
			}else if(c==0||c==21){
				if(r==initial_x +1  && c==0){
					cout<<'>';
				}else if(r== endx1+1 && c==21){
					cout<<'<';
				}
				else{
					cout<<"|";
				}

			}else if(debug){
				if(board[r-1][c-1]=='+'){
					cout<<' ';
				}else{
					cout<<board[r-1][c-1];
				}
			}else{
				if(board[r-1][c-1]=='T' || board[r-1][c-1]=='+'){
					cout<<' ';
				}else{
					cout<<board[r-1][c-1];
				}
			}

		}
	}


}

bool Board::moveDog(char c) {
/* (12 pts) code for the moveDog method goes here */
	int new_x,new_y;
	bool gameOver;



	if( c=='u' || c== 'U'){
		new_x=mydog.x-1;
		new_y=mydog.y;

		//check whether next position is empty space
		if(board[new_x][new_y] == ' '){
			// blank space within borders
			board[mydog.x][mydog.y]=' '; //empty the previous spot
			board[new_x][new_y]='D';
			mydog.x=new_x;
			gameOver=mydog.changeStrength(-2); // update & check if all strength is lost


		}else if(board[new_x][new_y]=='F'){
			// Food
			board[mydog.x][mydog.y]=' '; //empty the previous spot
			int food = rand()%16+2; // random number within 2 and 17
			mydog.x=new_x;
			board[mydog.x][mydog.y]='D';
			gameOver=mydog.changeStrength(food); // update & check if all strength is lost


		}else if(board[mydog.x][mydog.y]=='T'){
			//Trap
			board[mydog.x][mydog.y]=' '; //empty the previous spot
			int trap= rand()%16+2;
			mydog.x=new_x;
			board[mydog.x][mydog.y]='D';
			gameOver=mydog.changeStrength(trap*-1); // update & check if all strength is lost

			if(gameOver){
				//Dog has died

			}

		}else if( board[new_x][new_y]=='|' || board[new_x][new_y] =='_'){
			// walls
			if(mydog.strength >=6 ){
				cout << "Do you wanna knock down the wall? " << endl;
				string s = "no";
				cin>>s;
				if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					mydog.x=new_x;
					board[mydog.x][mydog.y]='D';
					gameOver=mydog.changeStrength(-6); // update & check if all strength is lost

				}else {
					gameOver=mydog.changeStrength(-1);
				}
			} // else do nothing
		}else if(board[new_x][new_y]=='E'){
			//PRint won and gameOver
			board[mydog.x][mydog.y]=' '; //empty the previous spot
			mydog.x=new_x;
			board[mydog.x][mydog.y]='D';
			mydog.won();
			return false; //gameOver
		}else{
			//default
			board[mydog.x][mydog.y]=' '; //empty the previous spot
						board[new_x][new_y]='D';
						mydog.x=new_x;
						gameOver=mydog.changeStrength(-2);
		}

	} else if( c=='d' || c=='D'){
		new_x=mydog.x+1;
		new_y=mydog.y;

		//check whether next position is empty space
		if(board[new_x][new_y] == ' '){
					// blank space within borders
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					board[new_x][new_y]='D';
					mydog.x=new_x;
					gameOver=mydog.changeStrength(-2); // update & check if all strength is lost


				}else if(board[new_x][new_y]=='F'){
					// Food
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					int food = rand()%16+2; // random number within 2 and 17
					mydog.x=new_x;
					board[mydog.x][mydog.y]='D';
					gameOver=mydog.changeStrength(food); // update & check if all strength is lost


				}else if(board[mydog.x][mydog.y]=='T'){
					//Trap
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					int trap= rand()%16+2;
					mydog.x=new_x;
					board[mydog.x][mydog.y]='D';
					gameOver=mydog.changeStrength(trap*-1); // update & check if all strength is lost


				}else if( board[new_x][new_y]=='|' || board[new_x][new_y] =='_'){
					// walls
					if(mydog.strength >=6 ){
						cout << "Do you wanna knock down the wall? " << endl;
						string s = "no";
						cin>>s;
						if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
							board[mydog.x][mydog.y]=' '; //empty the previous spot
							mydog.x=new_x;
							board[mydog.x][mydog.y]='D';
							gameOver=mydog.changeStrength(-6); // update & check if all strength is lost

						}else {
							gameOver=mydog.changeStrength(-1);
						}
					} // else do nothing
				}else if(board[new_x][new_y]=='E'){
					//PRint won and gameOver
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					mydog.x=new_x;
					board[mydog.x][mydog.y]='D';
					mydog.won();
					return false; //gameOver
				}else{
					//default
					board[mydog.x][mydog.y]=' '; //empty the previous spot
								board[new_x][new_y]='D';
								mydog.x=new_x;
								gameOver=mydog.changeStrength(-2);
				}
	} else if( c=='l' || c=='L'){
		new_x=mydog.x;
		new_y=mydog.y-1;

		//check whether next position is empty space
		if(board[new_x][new_y] == ' '){
							// blank space within borders
							board[mydog.x][mydog.y]=' '; //empty the previous spot
							board[new_x][new_y]='D';
							mydog.y=new_y;
							gameOver=mydog.changeStrength(-2); // update & check if all strength is lost


						}else if(board[new_x][new_y]=='F'){
							// Food
							board[mydog.x][mydog.y]=' '; //empty the previous spot
							int food = rand()%16+2; // random number within 2 and 17
							mydog.y=new_y;
							board[mydog.x][mydog.y]='D';
							gameOver=mydog.changeStrength(food); // update & check if all strength is lost


						}else if(board[mydog.x][mydog.y]=='T'){
							//Trap
							board[mydog.x][mydog.y]=' '; //empty the previous spot
							int trap= rand()%16+2;
							mydog.y=new_y;
							board[mydog.x][mydog.y]='D';
							gameOver=mydog.changeStrength(trap*-1); // update & check if all strength is lost

							if(gameOver){
								//Dog has died

							}

						}else if( board[new_x][new_y]=='|' || board[new_x][new_y] =='_'){
							// walls
							if(mydog.strength >=6 ){
								cout << "Do you wanna knock down the wall? " << endl;
								string s = "no";
								cin>>s;
								if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
									board[mydog.x][mydog.y]=' '; //empty the previous spot
									mydog.y=new_y;
									board[mydog.x][mydog.y]='D';
									gameOver=mydog.changeStrength(-6); // update & check if all strength is lost

								}else {
									gameOver=mydog.changeStrength(-1);
								}
							} // else do nothing
						}else if(board[new_x][new_y]=='E'){
							//PRint won and gameOver
							board[mydog.x][mydog.y]=' '; //empty the previous spot
							mydog.y=new_y;
							board[mydog.x][mydog.y]='D';
							mydog.won();
							return false; //gameOver
						}else{
							//default
							board[mydog.x][mydog.y]=' '; //empty the previous spot
														board[new_x][new_y]='D';
														mydog.y=new_y;
														gameOver=mydog.changeStrength(-2); // update & check if all strength is lost
						}
	} else if( c=='r' || c=='R'){
		new_x=mydog.x;
		new_y=mydog.y+1;

				//check whether next position is empty space
				if(board[new_x][new_y] == ' '){
					// blank space within borders
					board[mydog.x][mydog.y]=' '; //empty the previous spot
					board[new_x][new_y]='D';
					mydog.y=new_y;
					gameOver=mydog.changeStrength(-2); // update & check if all strength is lost

				}else if(board[new_x][new_y]=='F'){
									// Food
									board[mydog.x][mydog.y]=' '; //empty the previous spot
									int food = rand()%16+2; // random number within 2 and 17
									mydog.y=new_y;
									board[mydog.x][mydog.y]='D';
									gameOver=mydog.changeStrength(food); // update & check if all strength is lost


								}else if(board[mydog.x][mydog.y]=='T'){
									//Trap
									board[mydog.x][mydog.y]=' '; //empty the previous spot
									int trap= rand()%16+2;
									mydog.y=new_y;
									board[mydog.x][mydog.y]='D';
									gameOver=mydog.changeStrength(trap*-1); // update & check if all strength is lost


								}else if( board[new_x][new_y]=='|' || board[new_x][new_y] =='_'){
									// walls
									if(mydog.strength >=6 ){
										cout << "Do you wanna knock down the wall? " << endl;
										string s = "no";
										cin>>s;
										if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
											board[mydog.x][mydog.y]=' '; //empty the previous spot
											mydog.y=new_y;
											board[mydog.x][mydog.y]='D';
											gameOver=mydog.changeStrength(-6); // update & check if all strength is lost

										}else {
											gameOver=mydog.changeStrength(-1);
										}
									} // else do nothing
								}else if(board[new_x][new_y]=='E'){
									//PRint won and gameOver
									board[mydog.x][mydog.y]=' '; //empty the previous spot
									mydog.y=new_y;
									board[mydog.x][mydog.y]='D';
									mydog.won();
									return false; //gameOver
								}else{
									//default
									board[mydog.x][mydog.y]=' '; //empty the previous spot
																board[new_x][new_y]='D';
																mydog.y=new_y;
																gameOver=mydog.changeStrength(-2); // update & check if all strength is lost
								}

	}else{
		//default
		cout<< "stuck in default for u,d,r,l"<<endl;
	}
	if(gameOver == false){
		mydog.die();
	}
	return gameOver;

}






