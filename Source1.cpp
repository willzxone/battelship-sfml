#include<iostream>
#include<sstream>
#include<vector>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\Audio.hpp"
#include"SFML\System.hpp"
#include <cstdlib>
#include <time.h>
#include<windows.h>
#include<fstream>
using namespace std;
using namespace sf;

//const int mapSize = 9;
//const int mapSizePlayer2 = 23;

const int carrierSize = 8;
const int battelSize = 5;
const int kruiserSize = 4;
const int subSize = 3;
const int destroyerSize = 2;

//const int easyMapSize = 9;
//const int easyMapSizePlayer2 = 23;easyMapSize

int randomNumberX(int mapSizeX,int initialStarting) {
	srand((unsigned)time(0));

	mapSizeX = mapSizeX - (initialStarting );

	int randomNumber = initialStarting + (rand() % mapSizeX-1)+1 ;
	return randomNumber;
}
int randomNumberY(int mapSizeY) {


	srand((unsigned)time(0));

	int randomNumber = (rand() % mapSizeY) + 1;
	return randomNumber;
}


void hittingSound() {
	SoundBuffer buffer;
	if (!buffer.loadFromFile("sounds/hitting.wav")) {
		cout << "Error";
	}
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Sleep(1000);
}void missingSound() {
	SoundBuffer buffer;
	if (!buffer.loadFromFile("sounds/missing.wav")) {
		cout << "Error";
	}
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Sleep(1000);
}void destroySound() {
	SoundBuffer buffer;
	if (!buffer.loadFromFile("sounds/boatdestroyed.wav")) {
		cout << "Error";
	}
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Sleep(1000);
}void winningSound() {
	SoundBuffer buffer;
	if (!buffer.loadFromFile("sounds/winning.wav")) {
		cout << "Error";
	}
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Sleep(1000);
}

void playersMap(RenderWindow& window, RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], int mapSize, int mapSizePlayer2, int initialStarting,float gridSizeF) {
	for (int x = 1; x < mapSize; x++)
	{
		for (int y = 1; y < mapSize; y++)
		{
			tileMap[x][y].setSize(Vector2f(gridSizeF, gridSizeF));
			tileMap[x][y].setFillColor(Color::White);
			tileMap[x][y].setOutlineThickness(1.f);
			tileMap[x][y].setOutlineColor(Color::Black);
			tileMap[x][y].setPosition(gridSizeF * x, gridSizeF * y);
		}
	}
	for (int x = initialStarting; x < mapSizePlayer2; x++)
	{
		for (int y = 1; y < mapSize; y++)
		{
			tileMapPlayer2[x][y].setSize(Vector2f(gridSizeF, gridSizeF));
			tileMapPlayer2[x][y].setFillColor(Color::White);
			tileMapPlayer2[x][y].setOutlineThickness(1.f);
			tileMapPlayer2[x][y].setOutlineColor(Color::Black);
			tileMapPlayer2[x][y].setPosition(gridSizeF * x, gridSizeF * y);
		}
	}
}


void scoreStore(string str) {
	fstream score;
	score.open("score.txt", ios::app);
	score << str << endl;
	score.close();
}

void output(string outputFile) {
	fstream file;
	file.open(outputFile + ".txt", ios::in);
	string output;
	while (!file.eof()) {
		getline(file, output);
		for (int i = 0; i < 1; i++) {
			Sleep(150);
			cout << output << endl;
		}
	}
}

void updateMousePos(RenderWindow& window, Vector2i& mousePosScreen, Vector2i& mousePosWindow, Vector2u& mousePosGrid, Vector2f& mousePosView, unsigned& gridSizeU) {
	mousePosScreen = Mouse::getPosition();
	mousePosWindow = Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosWindow);

	if (mousePosView.x >= 0.f) {
		mousePosGrid.x = mousePosView.x / gridSizeU;
	}

	if (mousePosView.y >= 0.f) {
		mousePosGrid.y = mousePosView.y / gridSizeU;
	}
}

void drawing(RenderWindow& window, RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], int initialStarting, int mapSize, int mapSizePlayer2) {
	for (int x = 1; x < mapSize; x++)
	{
		for (int y = 1; y < mapSize; y++)
		{
			window.draw(tileMap[x][y]);
		}
	}

	for (int x = initialStarting; x < mapSizePlayer2; x++)
	{
		for (int y = 1; y < mapSize; y++)
		{
			window.draw(tileMapPlayer2[x][y]);
		}
	}
}

void rotatingFunc(Event& event, Vector2u& mousePosGrid, RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], RectangleShape& shipDeployer, char arr1[16][16], char arr2[16][16],bool& inputCheck,bool& ship, float& gridSizeF, bool& player1, bool& player2, bool& rotateFlag,int shipSize, int mapSize,int mapSizePlayer2,bool &wait, bool& compPlay,int initialStarting, Vector2f randomPosShip, bool& compPlayCheck,bool &randomFlag) {
	if (wait == true) {
	
		/////////////////Rotating Horizontally//////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Key::R)) {
			Vector2f posShip(mousePosGrid);
			for (int i = posShip.x ; i < posShip.x + shipSize; i++) {

				////////////////////////PLAYER 1/////////////////////////////
				if ((posShip.x + shipSize <= mapSize && player1)) {
					if (shipSize == 5) {
						if (tileMap[i][int(posShip.y)].getFillColor() != Color::Blue && arr1[int(posShip.y) + 1][i] != 'B' && arr1[int(posShip.y) - 1][i] != 'B' && arr1[int(posShip.y)][int(posShip.x) - 1] != 'B' && arr1[ int(posShip.y)][i] != 'B') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 8) {
						if (tileMap[i][int(posShip.y)].getFillColor() != Color::Blue && arr1[int(posShip.y) + 1][i] != 'C' && arr1[int(posShip.y) - 1][i] != 'C' && arr1[int(posShip.y)][int(posShip.x) - 1] != 'C' && arr1[int(posShip.y)][i] != 'C') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 4) {
						if (tileMap[i][int(posShip.y)].getFillColor() != Color::Blue && arr1[int(posShip.y) + 1][i] != 'K' && arr1[int(posShip.y) - 1][i] != 'K' && arr1[int(posShip.y)][int(posShip.x) - 1] != 'K' && arr1[int(posShip.y)][i] != 'K') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 3) {
						if (tileMap[i][int(posShip.y)].getFillColor() != Color::Blue && arr1[int(posShip.y) + 1][i] != 'S' && arr1[int(posShip.y) - 1][i] != 'S' && arr1[int(posShip.y)][int(posShip.x) - 1] != 'S' && arr1[int(posShip.y)][i] != 'S') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 2) {
						if (tileMap[i][int(posShip.y)].getFillColor() != Color::Blue && arr1[int(posShip.y) + 1][i] != 'D' && arr1[int(posShip.y) - 1][i] != 'D' && arr1[int(posShip.y)][int(posShip.x) - 1] != 'D' && arr1[int(posShip.y)][i] != 'D') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					

				}
				////////////////////////PLAYER 2/////////////////////////////

				else if (posShip.x + shipSize <= mapSizePlayer2 && player2) {
					if (shipSize == 5) {
						if (tileMapPlayer2[i][int(posShip.y)].getFillColor() != Color::Blue && arr2[int(posShip.y) + 1][i - (initialStarting-1)] != 'B' && arr2[int(posShip.y) - 1][i - (initialStarting-1)] != 'B' && arr2[int(posShip.y)][int(posShip.x)-(initialStarting-1) - 1] != 'B' && arr2[int(posShip.y)][i - (initialStarting-1)] != 'B') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 8) {
						if (tileMapPlayer2[i][int(posShip.y)].getFillColor() != Color::Blue && arr2[int(posShip.y) + 1][i-(initialStarting-1)] != 'C' && arr2[int(posShip.y) - 1][i-(initialStarting-1)] != 'C' && arr2[int(posShip.y)][int(posShip.x)-(initialStarting-1) - 1] != 'C' && arr2[int(posShip.y)][i-(initialStarting-1)] != 'C') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 4) {
						if (tileMapPlayer2[i][int(posShip.y)].getFillColor() != Color::Blue && arr2[int(posShip.y) + 1][i-(initialStarting-1)] != 'K' && arr2[int(posShip.y) - 1][i-(initialStarting-1)] != 'K' && arr2[int(posShip.y)][int(posShip.x)-(initialStarting-1) - 1] != 'K' && arr2[int(posShip.y)][i - (initialStarting-1)] != 'K') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 3) {
						if (tileMapPlayer2[i][int(posShip.y)].getFillColor() != Color::Blue && arr2[int(posShip.y) + 1][i-(initialStarting-1)] != 'S' && arr2[int(posShip.y) - 1][i-(initialStarting-1)] != 'S' && arr2[int(posShip.y)][int(posShip.x)-(initialStarting-1) - 1] != 'S' && arr2[int(posShip.y)][i - (initialStarting-1)] != 'S') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 2) {
						if (tileMapPlayer2[i][int(posShip.y)].getFillColor() != Color::Blue && arr2[int(posShip.y) + 1][i-(initialStarting-1)] != 'D' && arr2[int(posShip.y) - 1][i-(initialStarting-1)] != 'D' && arr2[int(posShip.y)][int(posShip.x)-(initialStarting-1) - 1] != 'D' && arr2[int(posShip.y)][i - (initialStarting-1)] != 'D') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
				}
			}

			if ((inputCheck == false && posShip.x + shipSize <= mapSize && player1)) {
				shipDeployer.setSize(Vector2f(gridSizeF * shipSize, gridSizeF));
				shipDeployer.setPosition(posShip.x * gridSizeF, posShip.y * gridSizeF);
				rotateFlag = true;
			}
			if ((inputCheck == false && posShip.x + shipSize <= mapSizePlayer2 && player2)) {
				shipDeployer.setSize(Vector2f(gridSizeF * shipSize, gridSizeF));
				shipDeployer.setPosition(posShip.x * gridSizeF, posShip.y * gridSizeF);
				rotateFlag = true;
			}

		}

		/////////////////Rotating Vertically//////////////////////
		if (Mouse::isButtonPressed(Mouse::Left) || compPlay) {
			//Cheking for collison and setting red box
			rotateFlag = false;
			Vector2f posShip(mousePosGrid);

			for (int i = posShip.y; i < posShip.y + shipSize; i++) {

				///////////////////PLAYER 1//////////////////////
				if ((posShip.y + shipSize <= mapSize && player1)) {
					if (shipSize == 5) {
						if (tileMap[int(posShip.x)][i].getFillColor() != Color::Blue && arr1[i][int(posShip.x)+1] != 'B' && arr1[i][int(posShip.x) - 1] != 'B' && arr1[int(posShip.y)-1][int(posShip.x)] != 'B' && arr1[i+1][int(posShip.x)] != 'B') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}else if (shipSize == 8) {
						if (tileMap[int(posShip.x)][i].getFillColor() != Color::Blue && arr1[i][int(posShip.x) + 1] != 'C' && arr1[i][int(posShip.x) - 1] != 'C' && arr1[int(posShip.y) - 1][int(posShip.x)] != 'C' && arr1[i + 1][int(posShip.x)] != 'C') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}else if (shipSize == 4) {
						if (tileMap[int(posShip.x)][i].getFillColor() != Color::Blue && arr1[i][int(posShip.x) + 1] != 'K' && arr1[i][int(posShip.x) - 1] != 'K' && arr1[int(posShip.y) - 1][int(posShip.x)] != 'K' && arr1[i + 1][int(posShip.x)] != 'K') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 3) {
						if (tileMap[int(posShip.x)][i].getFillColor() != Color::Blue && arr1[i][int(posShip.x) + 1] != 'S' && arr1[i][int(posShip.x) - 1] != 'S' && arr1[int(posShip.y) - 1][int(posShip.x)] != 'S' && arr1[i + 1][int(posShip.x)] != 'S') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 2) {
						if (tileMap[int(posShip.x)][i].getFillColor() != Color::Blue && arr1[i][int(posShip.x) + 1] != 'D' && arr1[i][int(posShip.x) - 1] != 'D' && arr1[int(posShip.y) - 1][int(posShip.x)] != 'D' && arr1[i + 1][int(posShip.x)] != 'D') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}

				
				}
				//////////////////////PLAYER 2/////////////////////
				else if ((posShip.y + shipSize <= mapSize && player2)) {

					if (shipSize == 5) {
						if (tileMapPlayer2[int(posShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(posShip.x)-(initialStarting-1) + 1] != 'B' && arr2[i][int(posShip.x)-(initialStarting-1) - 1] != 'B' && arr2[int(posShip.y) - 1][int(posShip.x)-(initialStarting-1)] != 'B' && arr2[i + 1][int(posShip.x)-(initialStarting-1)] != 'B') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 8) {
						if (tileMapPlayer2[int(posShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(posShip.x) - (initialStarting-1) + 1] != 'C' && arr2[i][int(posShip.x) - (initialStarting-1) - 1] != 'C' && arr2[int(posShip.y) - 1][int(posShip.x) - (initialStarting-1)] != 'C' && arr2[i + 1][int(posShip.x) - (initialStarting-1)] != 'C') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 4) {
						if (tileMapPlayer2[int(posShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(posShip.x) - (initialStarting-1) + 1] != 'K' && arr2[i][int(posShip.x) - (initialStarting-1) - 1] != 'K' && arr2[int(posShip.y) - 1][int(posShip.x) - (initialStarting-1)] != 'K' && arr2[i + 1][int(posShip.x) - (initialStarting-1)] != 'K') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 3) {
						if (tileMapPlayer2[int(posShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(posShip.x) - (initialStarting-1) + 1] != 'S' && arr2[i][int(posShip.x) - (initialStarting-1) - 1] != 'S' && arr2[int(posShip.y) - 1][int(posShip.x) - (initialStarting-1)] != 'S' && arr2[i + 1][int(posShip.x) - (initialStarting-1)] != 'S') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
					else if (shipSize == 2) {
						if (tileMapPlayer2[int(posShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(posShip.x) - (initialStarting-1) + 1] != 'D' && arr2[i][int(posShip.x) - (initialStarting-1) - 1] != 'D' && arr2[int(posShip.y) - 1][int(posShip.x) - (initialStarting-1)] != 'D' && arr2[i + 1][int(posShip.x) - (initialStarting-1)] != 'D') {
							ship = true;
							inputCheck = false;
						}
						else {
							inputCheck = true;
							break;
						}
					}
				}
			}

			if (compPlay) {
				for (int i = randomPosShip.y; i < randomPosShip.y + shipSize; i++) {
					if ((randomPosShip.y + shipSize <= mapSize && compPlay==true)) {
						if (shipSize == 5) {
							if (tileMapPlayer2[int(randomPosShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(randomPosShip.x) - (initialStarting-1) + 1] != 'B' && arr2[i][int(randomPosShip.x) - (initialStarting-1) - 1] != 'B' && arr2[int(randomPosShip.y) - 1][int(randomPosShip.x) - (initialStarting-1)] != 'B' && arr2[i + 1][int(randomPosShip.x) - (initialStarting-1)] != 'B') {
								ship = true;
								inputCheck = false;
								compPlayCheck = true;

							}
							else {
								inputCheck = true;
								compPlayCheck = false;
								break;
							}
						}
						else if (shipSize == 8) {
							if (tileMapPlayer2[int(randomPosShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(randomPosShip.x) - (initialStarting-1) + 1] != 'C' && arr2[i][int(randomPosShip.x) - (initialStarting-1) - 1] != 'C' && arr2[int(randomPosShip.y) - 1][int(randomPosShip.x) - (initialStarting-1)] != 'C' && arr2[i + 1][int(randomPosShip.x) - (initialStarting-1)] != 'C') {
								ship = true;
								inputCheck = false;
								compPlayCheck = true;

							}
							else {
								inputCheck = true;
								compPlayCheck = false;
								break;
							}
						}
						else if (shipSize == 4) {
							if (tileMapPlayer2[int(randomPosShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(randomPosShip.x) - (initialStarting-1) + 1] != 'K' && arr2[i][int(randomPosShip.x) - (initialStarting-1) - 1] != 'K' && arr2[int(randomPosShip.y) - 1][int(randomPosShip.x) - (initialStarting-1)] != 'K' && arr2[i + 1][int(randomPosShip.x) - (initialStarting-1)] != 'K') {
								ship = true;
								inputCheck = false;
								compPlayCheck = true;

							}
							else {
								inputCheck = true;
								compPlayCheck = false;

								break;
							}
						}
						else if (shipSize == 3) {
							if (tileMapPlayer2[int(randomPosShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(randomPosShip.x) - (initialStarting-1) + 1] != 'S' && arr2[i][int(randomPosShip.x) - (initialStarting-1) - 1] != 'S' && arr2[int(randomPosShip.y) - 1][int(randomPosShip.x) - (initialStarting-1)] != 'S' && arr2[i + 1][int(randomPosShip.x) - (initialStarting-1)] != 'S') {
								ship = true;
								inputCheck = false;
								compPlayCheck = true;

							}
							else {
								inputCheck = true;
								compPlayCheck = false;

								break;
							}
						}
						else if (shipSize == 2) {
							if (tileMapPlayer2[int(randomPosShip.x)][i].getFillColor() != Color::Blue && arr2[i][int(randomPosShip.x) - (initialStarting-1) + 1] != 'D' && arr2[i][int(randomPosShip.x) - (initialStarting-1) - 1] != 'D' && arr2[int(randomPosShip.y) - 1][int(randomPosShip.x) - (initialStarting-1)] != 'D' && arr2[i + 1][int(randomPosShip.x) - (initialStarting-1)] != 'D') {
								ship = true;
								inputCheck = false;
								compPlayCheck = true;

							}
							else {
								inputCheck = true;
								compPlayCheck = false;
								break;
							}
						}
					}
				}
				
				if ((inputCheck == false && randomPosShip.y + shipSize <= mapSize && compPlayCheck == true && tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].getFillColor() != Color::Blue) ){
					compPlayCheck = false;

					randomFlag = false;
					shipDeployer.setSize(Vector2f(gridSizeF, gridSizeF * shipSize));
					shipDeployer.setPosition(randomPosShip.x * gridSizeF, randomPosShip.y * gridSizeF);
				}

			}


			if ((inputCheck == false && posShip.y + shipSize <= mapSize && player1)) {
				shipDeployer.setSize(Vector2f(gridSizeF, gridSizeF * shipSize));
				shipDeployer.setPosition(posShip.x * gridSizeF, posShip.y * gridSizeF);
			}
			if ((inputCheck == false && posShip.y + shipSize <= mapSize && player2)) {
				shipDeployer.setSize(Vector2f(gridSizeF, gridSizeF * shipSize));
				shipDeployer.setPosition(posShip.x * gridSizeF, posShip.y * gridSizeF);
			}
		}
	}

}

void fillingFunc(Event &event, Vector2u& mousePosGrid, RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], RectangleShape& shipDeployer, RectangleShape& tileSelector, bool& inputCheck, bool& ship, float& gridSizeF, bool& player1, bool& player2, bool& rotateFlag, int& shipSize, int mapSize, char arr1[16][16], char arr2[16][16],bool &wait, bool& compPlay, Vector2f& randomPosShip, bool& compPlayCheck,int initialStarting) {
	/////////////////Mouse Click LEFT Boxes Fill/////////////////

	if (Keyboard::isKeyPressed(Keyboard::Key::K)) {
		Vector2f posShip(mousePosGrid);
		compPlayCheck = true;
		////////Left Click X Axis Fillll////////////////////////
		if (rotateFlag == false) {
			if ((shipDeployer.getPosition() == tileSelector.getPosition()) ) {
				inputCheck = true;
				for (int i = posShip.y; i < posShip.y + shipSize; i++)
				{
					if (player1) {
						wait = false;
						tileMap[int(posShip.x)][i].setFillColor(Color::Blue);
						if (shipSize == 8) {
							arr1[i][int(posShip.x)] = 'C';
						}
						else if (shipSize == 5) {
							arr1[i][int(posShip.x)] = 'B';
						}
						else if (shipSize == 4) {
							
							arr1[i][int(posShip.x)] = 'K';
						}
						else if (shipSize == 3) {
							
							arr1[i][int(posShip.x)] = 'S';
						}
						else if (shipSize == 2) {

							arr1[i][int(posShip.x)] = 'D';
						}
					}
					else if (player2) {
						wait = false;

						tileMapPlayer2[int(posShip.x)][i].setFillColor(Color::Blue);
						if (shipSize == 8) {
							arr2[i][int(posShip.x)-(initialStarting-1)] = 'C';
						}
						else if (shipSize == 5) {
							arr2[i][int(posShip.x)-(initialStarting-1)] = 'B';
						}
						else if (shipSize == 4) {
							arr2[i][int(posShip.x) - (initialStarting-1)] = 'K';
						}
						else if (shipSize == 3) {
							arr2[i][int(posShip.x) - (initialStarting-1)] = 'S';
						}
						else if (shipSize == 2) {
							arr2[i][int(posShip.x) - (initialStarting-1)] = 'D';
						}
					}
					
				}

				if (compPlayCheck == true && compPlay == true) {
					for (int i = randomPosShip.y; i < randomPosShip.y + shipSize; i++)
					{
						wait = false;
						tileMapPlayer2[int(randomPosShip.x)][i].setFillColor(Color::Blue);
						if (shipSize == 8) {
							arr2[i][int(randomPosShip.x) - (initialStarting-1)] = 'C';
						}
						else if (shipSize == 5) {
							arr2[i][int(randomPosShip.x) - (initialStarting-1)] = 'B';
						}
						else if (shipSize == 4) {
							arr2[i][int(randomPosShip.x) - (initialStarting-1)] = 'K';
						}
						else if (shipSize == 3) {
							arr2[i][int(randomPosShip.x) - (initialStarting-1)] = 'S';
						}
						else if (shipSize == 2) {
							arr2[i][int(randomPosShip.x) - (initialStarting-1)] = 'D';
						}

					}
				}

			}
		}
		////////R Button Y Axis Fillll////////////////////////

		if (rotateFlag == true) {
			if (shipDeployer.getPosition() == tileSelector.getPosition()) {
				inputCheck = true;

				for (int i = posShip.x; i < posShip.x + shipSize; i++) {
					/////////PLAYER 1///////////

					if (player1) {
						wait = false;

						tileMap[i][int(posShip.y)].setFillColor(Color::Blue);
						if (shipSize == 8) {
							arr1[int(posShip.y)][i] = 'C';
						}
						else if (shipSize == 5) {
							arr1[int(posShip.y)][i] = 'B';
						}
						else if (shipSize == 4) {
							arr1[int(posShip.y)][i] = 'K';
						}
						else if (shipSize == 3) {
							arr1[int(posShip.y)][i] = 'S';
						}
						else if (shipSize == 2) {
							arr1[int(posShip.y)][i] = 'D';
						}
					}
					/////////PLAYER 2///////////
					else if (player2) {
						wait = false;

						tileMapPlayer2[i][int(posShip.y)].setFillColor(Color::Blue);
						if (shipSize == 8) {
							arr2[int(posShip.y)][i-(initialStarting-1)] = 'C';
						}else if(shipSize == 5) {
							arr2[int(posShip.y)][i-(initialStarting-1)] = 'B';
						}
						else if (shipSize == 4) {
							arr2[int(posShip.y)][i-(initialStarting-1)] = 'K';
						}
						else if (shipSize == 3) {
							arr2[int(posShip.y)][i-(initialStarting-1)] = 'S';
						}
						else if (shipSize == 2) {
							arr2[int(posShip.y)][i-(initialStarting-1)] = 'D';
						}
					}
				}
			}

		}
	}
}

void nextSelect(Event& event, bool& inputCheck, bool& ship, int& shipNum, int shipSize,int &shipCountPlayer1, int& shipCountPlayer2,bool &player1,bool& player2,bool &wait,bool &compPlay,bool& compPlayCheck, bool& randomFlag) {
	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {

		if (inputCheck == true) {
			wait = true;
			ship = false;
			inputCheck = false;
			shipNum -= 1;
			if (player1) {
				shipCountPlayer1 += shipSize;
			}
			if (player2 || compPlay==true) {
				shipCountPlayer2 += shipSize;
				randomFlag = true;
			}
			Sleep(250);
		}
	}
}

void playerTurn(Event& event, Vector2u& mousePosGrid, RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], RectangleShape& shipDeployer, RectangleShape& tileSelector, bool& inputCheck, bool& ship, float& gridSizeF, bool& player1,bool &player2, bool& rotateFlag, int shipSize, char arr1[16][16], char arr2[16][16],int &shipNum, int& shipCountPlayer1, int& shipCountPlayer2, bool& player1Flag, bool& player2Flag,bool&wait,bool& compPlay,int initialStarting, bool& compPlayCheck,bool& randomFlag, Vector2f& randomPosShip,Text &shipDeploy,int mapSize,int mapSizePlayer2) {
	
	
	if (randomFlag == true && compPlay==true) {
		randomPosShip.x = randomNumberX(mapSizePlayer2, initialStarting);
		if (randomPosShip.x < initialStarting) { randomPosShip.x = initialStarting; }
		randomPosShip.y = randomNumberY(mapSize);
		if(shipSize==8){ randomPosShip.y = 1; }
	}	
	rotatingFunc(event,mousePosGrid, tileMap, tileMapPlayer2, shipDeployer,arr1,arr2, inputCheck, ship, gridSizeF, player1, player2,rotateFlag, shipSize, mapSize,mapSizePlayer2, wait,compPlay, initialStarting, randomPosShip, compPlayCheck,randomFlag);
	fillingFunc(event, mousePosGrid, tileMap,tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, shipSize, mapSize, arr1, arr2, wait,compPlay, randomPosShip, compPlayCheck,initialStarting);
	nextSelect(event, inputCheck, ship, shipNum,shipSize,shipCountPlayer1, shipCountPlayer2, player1, player2,wait,compPlay, compPlayCheck,randomFlag);
}

void hittingCheck(RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], Vector2f& posShip, bool& player1, bool& player2, bool& player1Flag, bool& player2Flag, char arr1[16][16], char arr2[16][16],int initialStarting,int carrierNum, int battelNum, int destroyerNum, int kruiserNum, int subNum,int &globalCount,bool &compInput,Vector2f &randomPosShip,bool& outputWinning,Text &text, Text& shipDeploy,int mapSize,int mapSizePlayer2) {
	static char shotChar;
	static int player1WinCount=0,player2WinCount=0;
	static bool carrierFlag = false, battelFlag = false, kruiserFlag = false, destroyerFlag = false, subFlag = false,player1Win=false,player2Win=false,winningCheck=true,compHit=false;
	
	static Vector2i checkPlayer1Ships[5];
	static Vector2i checkPlayer2Ships[5];

	static Vector2i previousCountPlayer1[5];
	static Vector2i previousCountPlayer2[5];

	static int countsPlayer1[5] = {0};
	static int countsPlayer2[5] = {0};

	static int shipCheck[5] = { 0 };
	static int shipCheck2[5] = { 0 };


	///////////////////////////PLAYER 1//////////////////////////
	if (player1 && tileMap[int(posShip.x)][int(posShip.y)].getFillColor() == Color::White) {

		player1Flag = false;
		player1 = false;

		if (compInput) {
			player2Flag = false;
			compHit = true;
		}
		else {
			player2Flag = true;
		}
		shotChar = arr1[int(posShip.y)][int(posShip.x)];

		/////////////////COLORING BLOCKS ON COLISION/////////////////////////
		if (shotChar == 'C') {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Red);
			hittingSound();

		}
		else if (shotChar == 'B') {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Yellow);
			hittingSound();

		}
		else if (shotChar == 'D') {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Green);
			hittingSound();

		}
		else if (shotChar == 'K') {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Cyan);
			hittingSound();

		}
		else if (shotChar == 'S') {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Magenta);
			hittingSound();

		}
		else {
			tileMap[int(posShip.x)][int(posShip.y)].setFillColor(Color::Color(92, 64, 51, 255));
			missingSound();

		}	
	}

	///////////////////////////////////CHECKING IN X DIRECTION//////////////////////////////
	for (int j = 1; j < mapSize; j++) {
		for (int k = 0; k < 5; k++) {
			countsPlayer1[k] = 0;
		}
		int i = 1;
		for (i = 1; i < mapSize; i++)
		{
			if (tileMap[i][j].getFillColor() == Color::Red && countsPlayer1[0] != carrierSize) {
				countsPlayer1[0]++;
				carrierFlag = true;
				checkPlayer1Ships[0].x = i - (carrierSize - 1);
				checkPlayer1Ships[0].y = j;
				continue;
			}
			else if (countsPlayer1[0] != carrierSize) {
				carrierFlag = false;
				countsPlayer1[0] = 0;

			}
			else if (carrierFlag == true && previousCountPlayer1[0].x == checkPlayer1Ships[0].x && previousCountPlayer1[0].y == checkPlayer1Ships[0].y) {
				countsPlayer1[0] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Yellow && countsPlayer1[1] != battelSize) {
				countsPlayer1[1]++;
				battelFlag = true;
				checkPlayer1Ships[1].x = i - (battelSize - 1);
				checkPlayer1Ships[1].y = j;
				continue;
			}
			else if (countsPlayer1[1] != battelSize) {
				battelFlag = false;
				countsPlayer1[1] = 0;

			}
			else if (battelFlag == true && previousCountPlayer1[1].x == checkPlayer1Ships[1].x && previousCountPlayer1[1].y == checkPlayer1Ships[1].y) {
				countsPlayer1[1] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Cyan && countsPlayer1[2] != kruiserSize) {
				countsPlayer1[2]++;
				kruiserFlag = true;
				checkPlayer1Ships[2].x = i - (kruiserSize - 1);
				checkPlayer1Ships[2].y = j;
				continue;
			}
			else if (countsPlayer1[2] != kruiserSize) {
				kruiserFlag = false;
				countsPlayer1[2] = 0;

			}
			else if (kruiserFlag == true && previousCountPlayer1[2].x == checkPlayer1Ships[2].x && previousCountPlayer1[2].y == checkPlayer1Ships[2].y) {
				countsPlayer1[2] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Green && countsPlayer1[3] != destroyerSize) {
				countsPlayer1[3]++;
				destroyerFlag = true;
				checkPlayer1Ships[3].x = i - (destroyerSize - 1);
				checkPlayer1Ships[3].y = j;
				continue;
			}
			else if (countsPlayer1[3] != destroyerSize) {
				destroyerFlag = false;
				countsPlayer1[3]=0;

			}
			else if (destroyerFlag == true && previousCountPlayer1[3].x == checkPlayer1Ships[3].x && previousCountPlayer1[3].y == checkPlayer1Ships[3].y) {
				countsPlayer1[3] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Magenta && countsPlayer1[4] != subSize) {
				countsPlayer1[4]++;
				subFlag = true;
				checkPlayer1Ships[4].x = i - (subSize - 1);
				checkPlayer1Ships[4].y = j;
				continue;
			}
			else if (countsPlayer1[4] != subSize) {
				subFlag = false;
				countsPlayer1[4]=0;

			}
			else if (subFlag == true && previousCountPlayer1[4].x == checkPlayer1Ships[4].x && previousCountPlayer1[3].y == checkPlayer1Ships[3].y) {
				countsPlayer1[4] = 0;
			}

		}
		if (countsPlayer1[0] == carrierSize && carrierFlag == true) {
			if ((previousCountPlayer1[0].x != checkPlayer1Ships[0].x || previousCountPlayer1[0].y != checkPlayer1Ships[0].y) && shipCheck[0] != carrierNum) {

				previousCountPlayer1[0].y = checkPlayer1Ships[0].y;
				previousCountPlayer1[0].x = checkPlayer1Ships[0].x;
				shipCheck[0]++;
				shipDeploy.setString("Carrier Ship Destroyed");
				//cout << "\nCarrier Ship Destroyed";
				destroySound();
			}
		}
		if (countsPlayer1[1] == battelSize && battelFlag == true) {
			if ((previousCountPlayer1[1].x != checkPlayer1Ships[1].x || previousCountPlayer1[1].y != checkPlayer1Ships[1].y) && shipCheck[1] != battelNum) {

				previousCountPlayer1[1].y = checkPlayer1Ships[1].y;
				previousCountPlayer1[1].x = checkPlayer1Ships[1].x;
				shipCheck[1]++;
				//cout << "\nBattel Ship Destroyed";
				shipDeploy.setString("Battel Ship Destroyed");

				destroySound();


			}
		}
		if (countsPlayer1[2] == kruiserSize && kruiserFlag == true) {
			if ((previousCountPlayer1[2].x != checkPlayer1Ships[2].x || previousCountPlayer1[2].y != checkPlayer1Ships[2].y) && shipCheck[2] != kruiserNum) {
				previousCountPlayer1[2].y = checkPlayer1Ships[2].y;
				previousCountPlayer1[2].x = checkPlayer1Ships[2].x;
				shipCheck[2]++;
				//cout << "\nCruiser Ship Destroyed";
				shipDeploy.setString("Cruiser Ship Destroyed");

				destroySound();


			}

		}
		if (countsPlayer1[3] == destroyerSize && destroyerFlag == true) {
			if ((previousCountPlayer1[3].x != checkPlayer1Ships[3].x || previousCountPlayer1[3].y != checkPlayer1Ships[3].y) && shipCheck[3] != destroyerNum) {
				previousCountPlayer1[3].y = checkPlayer1Ships[3].y;
				previousCountPlayer1[3].x = checkPlayer1Ships[3].x;
				shipCheck[3]++;
				//cout << "\nDestroyer Ship Destroyed";
				//X
				shipDeploy.setString("Destroyer Ship Destroyed");

				destroySound();


			}

		}
		if (countsPlayer1[4] == subSize && subFlag == true) {
			if ((previousCountPlayer1[4].x != checkPlayer1Ships[4].x || previousCountPlayer1[4].y != checkPlayer1Ships[4].y) && shipCheck[4] != subNum) {
				previousCountPlayer1[4].y = checkPlayer1Ships[4].y;
				previousCountPlayer1[4].x = checkPlayer1Ships[4].x;
				shipCheck[4]++;
				//cout << "\nSubmarine Ship Destroyed";
				shipDeploy.setString("Submarine Ship Destroyed");
				destroySound();


			}

		}
		
		if (j == mapSize - 1) {
			for (int i = 0; i < 4; i++)
			{
				checkPlayer1Ships[i].x = 0;
				checkPlayer1Ships[i].y = 0;
			}
		}
			
		
	}

	//////////////////////////////////CHECKING IN Y DIRECTION///////////////////////////////

	for (int i = 1; i < mapSize; i++) {

		for (int k = 0; k < 5; k++) {
			countsPlayer1[k] = 0;
		}

		int j = 1;
		for (j = 1; j < mapSize; j++)
		{
			if (tileMap[i][j].getFillColor() == Color::Red && countsPlayer1[0] != carrierSize) {
				countsPlayer1[0]++;
				carrierFlag = true;
				checkPlayer1Ships[0].y = j - (carrierSize - 1);
				checkPlayer1Ships[0].x = i;

				continue;
			}
			else if (countsPlayer1[0] != carrierSize) {
				carrierFlag = false;
				countsPlayer1[0]=0;

			}
			else if (carrierFlag == true && previousCountPlayer1[0].y == checkPlayer1Ships[0].y && previousCountPlayer1[0].x == checkPlayer1Ships[0].x) {
				countsPlayer1[0] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Yellow && countsPlayer1[1] != battelSize) {
				countsPlayer1[1]++;
				battelFlag = true;
				checkPlayer1Ships[1].y = j - (battelSize - 1);
				checkPlayer1Ships[1].x = i;
				continue;
			}
			else if (countsPlayer1[1] != battelSize) {
				battelFlag = false;
				countsPlayer1[1]=0;

			}
			else if (battelFlag == true && previousCountPlayer1[1].y == checkPlayer1Ships[1].y && previousCountPlayer1[1].x == checkPlayer1Ships[1].x) {
				countsPlayer1[1] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Cyan && countsPlayer1[2] != kruiserSize) {
				countsPlayer1[2]++;
				kruiserFlag = true;
				checkPlayer1Ships[2].y = j - (kruiserSize - 1);
				checkPlayer1Ships[2].x = i;

				continue;
			}
			else if (countsPlayer1[2] != kruiserSize) {
				countsPlayer1[2]=0;
				kruiserFlag = false;
			}
			else if (kruiserFlag == true && previousCountPlayer1[2].y == checkPlayer1Ships[2].y && previousCountPlayer1[2].x == checkPlayer1Ships[2].x) {
				countsPlayer1[2] = 0;
			}


			if ((tileMap[i][j].getFillColor() == Color::Green && countsPlayer1[3] != destroyerSize)) {
				countsPlayer1[3]++;
				destroyerFlag = true;
				checkPlayer1Ships[3].y = j - (destroyerSize - 1);
				checkPlayer1Ships[3].x = i;
				continue;
			}
			else if (countsPlayer1[3] != destroyerSize ) {
				destroyerFlag = false;
				countsPlayer1[3]=0;

			}
			else if (destroyerFlag == true && previousCountPlayer1[3].y == checkPlayer1Ships[3].y && previousCountPlayer1[3].x == checkPlayer1Ships[3].x) {
				countsPlayer1[3] = 0;
			}

			if (tileMap[i][j].getFillColor() == Color::Magenta && countsPlayer1[4] != subSize) {
				countsPlayer1[4]++;
				subFlag = true;
				checkPlayer1Ships[4].y = j - (subSize - 1);
				checkPlayer1Ships[4].x = i;

				continue;
			}
			else if (countsPlayer1[4] != subSize) {
				subFlag = false;
				countsPlayer1[4]=0;

			}
			else if (subFlag == true && previousCountPlayer1[4].y == checkPlayer1Ships[4].y && previousCountPlayer1[4].x == checkPlayer1Ships[4].x) {
				countsPlayer1[4] = 0;
			}

		}
		if (countsPlayer1[0] == carrierSize && carrierFlag == true) {
			if ((previousCountPlayer1[0].x != checkPlayer1Ships[0].x || previousCountPlayer1[0].y != checkPlayer1Ships[0].y) && shipCheck[0] != carrierNum) {
				previousCountPlayer1[0].y = checkPlayer1Ships[0].y;
				previousCountPlayer1[0].x = checkPlayer1Ships[0].x;
				shipCheck[0]++;
				//cout << "\nCarrier Ship Destroyed";
				shipDeploy.setString("Carrier Ship Destroyed");
				destroySound();

			}
		}
		if (countsPlayer1[1] == battelSize && battelFlag == true) {
			if ((previousCountPlayer1[1].x != checkPlayer1Ships[1].x || previousCountPlayer1[1].y != checkPlayer1Ships[1].y) && shipCheck[1] != battelNum) {

				shipCheck[1]++;
				previousCountPlayer1[1].y = checkPlayer1Ships[1].y;
				previousCountPlayer1[1].x = checkPlayer1Ships[1].x;

				//cout << "\nBattel Ship Destroyed";
				shipDeploy.setString("Battel Ship Destroyed");

				destroySound();


			}
		}
		if (countsPlayer1[2] == kruiserSize && kruiserFlag == true) {
			if ((previousCountPlayer1[2].x != checkPlayer1Ships[2].x || previousCountPlayer1[2].y != checkPlayer1Ships[2].y) && shipCheck[2] != kruiserNum) {
				previousCountPlayer1[2].y = checkPlayer1Ships[2].y;
				previousCountPlayer1[2].x = checkPlayer1Ships[2].x;
				shipCheck[2]++;
				//cout << "\nCruiser Ship Destroyed";
				shipDeploy.setString("Cruiser Ship Destroyed");

				destroySound();
			}

		}
		if (countsPlayer1[3] == destroyerSize && destroyerFlag == true) {
			if ((previousCountPlayer1[3].x != checkPlayer1Ships[3].x || previousCountPlayer1[3].y != checkPlayer1Ships[3].y) && shipCheck[3] != destroyerNum) {
				previousCountPlayer1[3].y = checkPlayer1Ships[3].y;
				previousCountPlayer1[3].x = checkPlayer1Ships[3].x;
				shipCheck[3]++;
				//Y
				shipDeploy.setString("Destroyer Ship Destroyed");

				destroySound();

			}

		}
		if (countsPlayer1[4] == subSize && subFlag == true) {
			if ((previousCountPlayer1[4].x != checkPlayer1Ships[4].x || previousCountPlayer1[4].y != checkPlayer1Ships[4].y) && shipCheck[4] != subNum) {
				previousCountPlayer1[4].y = checkPlayer1Ships[4].y;
				previousCountPlayer1[4].x = checkPlayer1Ships[4].x;
				shipCheck[4]++;
				//cout << "\nSubmarine Ship Destroyed";
				shipDeploy.setString("Submarine Ship Destroyed");

				destroySound();


			}

		}
		if (i == mapSize - 1) {
			for (int i = 0; i < 4; i++)
			{
				checkPlayer1Ships[i].x = 0;
				checkPlayer1Ships[i].y = 0;
			}
		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	///////////////////////////Player 2////////////////////
	if (player2 && tileMapPlayer2[int(posShip.x)][int(posShip.y)].getFillColor() == Color::White) {



		player2Flag = false;
		player2 = false;
		player1Flag = true;
		shotChar = arr2[int(posShip.y)][int(posShip.x) - (initialStarting-1)];

		if (shotChar == 'C') {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Red);
			hittingSound();

		}
		else if (shotChar == 'B') {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Yellow);
			hittingSound();

		}
		else if (shotChar == 'D') {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Green);
			hittingSound();

		}
		else if (shotChar == 'K') {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Cyan);
			hittingSound();

		}
		else if (shotChar == 'S') {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Magenta);
			hittingSound();

		}
		else {
			tileMapPlayer2[int(posShip.x)][int(posShip.y)].setFillColor(Color::Color(92, 64, 51, 255));
			missingSound();

		}
	}

	//////////////////////////////////////COMPUTER PLAY/////////////////////////////////////
	if (compInput && tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].getFillColor() == Color::White && compHit) {

		//compInput = false;
		player1Flag = true;
		compHit = false;
		shotChar = arr2[int(randomPosShip.y)][int(randomPosShip.x) - (initialStarting - 1)];

		if (shotChar == 'C') {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Red);
			hittingSound();

		}
		else if (shotChar == 'B') {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Yellow);
			hittingSound();

		}
		else if (shotChar == 'D') {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Green);
			hittingSound();

		}
		else if (shotChar == 'K') {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Cyan);
			hittingSound();

		}
		else if (shotChar == 'S') {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Magenta);
			hittingSound();

		}
		else {
			tileMapPlayer2[int(randomPosShip.x)][int(randomPosShip.y)].setFillColor(Color::Color(92, 64, 51,255));
			missingSound();

		}
	}


	
	//////////////////////////////////CHECKING IN X DIRECTION///////////////////////////////
	for (int j = 1; j < mapSize; j++) {
		for (int k = 0; k < 5; k++) {
			countsPlayer2[k] = 0;
		}
		int i = initialStarting;
		for (int i = initialStarting; i < mapSizePlayer2; i++)
		{
			if (tileMapPlayer2[i][j].getFillColor() == Color::Red && countsPlayer2[0] != carrierSize) {
				countsPlayer2[0]++;
				carrierFlag = true;

				checkPlayer2Ships[0].x = i - (carrierSize - 1);
				checkPlayer2Ships[0].y = j;

				continue;
			}
			else if (countsPlayer2[0] != carrierSize) {
				carrierFlag = false;
				countsPlayer2[0] = 0;

			}
			else if (carrierFlag == true && previousCountPlayer2[0].x == checkPlayer2Ships[0].x && previousCountPlayer2[0].y == checkPlayer2Ships[0].y) {
				countsPlayer2[0] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Yellow && countsPlayer2[1] != battelSize) {
				countsPlayer2[1]++;
				battelFlag = true;
				checkPlayer2Ships[1].x = i - (battelSize - 1);
				checkPlayer2Ships[1].y = j;

				continue;
			}
			else if (countsPlayer2[1] != battelSize) {
				battelFlag = false;
				countsPlayer2[1] = 0;

			}
			else if (battelFlag == true && previousCountPlayer2[1].x == checkPlayer2Ships[1].x&& previousCountPlayer2[1].y == checkPlayer2Ships[1].y) {
				countsPlayer2[1] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Cyan && countsPlayer2[2] != kruiserSize) {
				countsPlayer2[2]++;
				kruiserFlag = true;
				checkPlayer2Ships[2].x = i - (kruiserSize - 1);
				checkPlayer2Ships[2].y = j;

				continue;
			}
			else if (countsPlayer2[2] != kruiserSize) {
				kruiserFlag = false;
				countsPlayer2[2] = 0;

			}
			else if (kruiserFlag == true && previousCountPlayer2[2].x == checkPlayer2Ships[2].x&& previousCountPlayer2[2].y == checkPlayer2Ships[2].y) {
				countsPlayer2[2] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Green && countsPlayer2[3] != destroyerSize) {
				countsPlayer2[3]++;
				destroyerFlag = true;
				checkPlayer2Ships[3].x = i - (destroyerSize - 1);
				checkPlayer2Ships[3].y = j;

				continue;
			}
			else if (countsPlayer2[3] != destroyerSize) {
				destroyerFlag = false;
				countsPlayer2[3] = 0;

			}
			else if (destroyerFlag == true && previousCountPlayer2[3].x == checkPlayer2Ships[3].x && previousCountPlayer2[3].y == checkPlayer2Ships[3].y) {
				countsPlayer2[3] = 0;
			}
			if (tileMapPlayer2[i][j].getFillColor() == Color::Magenta && countsPlayer2[4] != subSize) {
				countsPlayer2[4]++;
				subFlag = true;
				checkPlayer2Ships[4].y = j;

				checkPlayer2Ships[4].x = i - (subSize - 1);

				continue;
			}
			else if (countsPlayer2[4] != subSize) {
				subFlag = false;
				countsPlayer2[4] = 0;

			}
			else if (subFlag == true && previousCountPlayer2[3].x == checkPlayer2Ships[4].x && previousCountPlayer2[3].y == checkPlayer2Ships[4].y) {
				countsPlayer2[4] = 0;
			}

		}
		if (countsPlayer2[0] == carrierSize && carrierFlag == true) {
			if ((previousCountPlayer2[0].x != checkPlayer2Ships[0].x || previousCountPlayer2[0].y != checkPlayer2Ships[0].y) && shipCheck2[0] != carrierNum) {

				shipCheck2[0]++;
				previousCountPlayer2[0].y = checkPlayer2Ships[0].y;
				previousCountPlayer2[0].x = checkPlayer2Ships[0].x;
				//cout << "\nCarrier Ship Destroyed Player 2";
				shipDeploy.setString("Carrier Ship Destroyed Player 2");

				destroySound();

			}
		}
		if (countsPlayer2[1] == battelSize && battelFlag == true) {
			if ((previousCountPlayer2[1].x != checkPlayer2Ships[1].x || previousCountPlayer2[1].y != checkPlayer2Ships[1].y) && shipCheck2[1] != battelNum) {

				shipCheck2[1]++;
				previousCountPlayer2[1].y = checkPlayer2Ships[1].y;
				previousCountPlayer2[1].x = checkPlayer2Ships[1].x;
				shipDeploy.setString("Battel Ship Destroyed Player 2");
				destroySound();

			}
		}
		if (countsPlayer2[2] == kruiserSize && kruiserFlag == true) {
			if ((previousCountPlayer2[2].x != checkPlayer2Ships[2].x || previousCountPlayer2[2].y != checkPlayer2Ships[2].y) && shipCheck2[2] != kruiserNum) {

				shipCheck2[2]++;
				previousCountPlayer2[2].y = checkPlayer2Ships[2].y;
				previousCountPlayer2[2].x = checkPlayer2Ships[2].x;
				//cout << "\nCruiser Ship Destroyed Player 2";
				shipDeploy.setString("Cruiser Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (countsPlayer2[3] == destroyerSize && destroyerFlag == true) {
			if ((previousCountPlayer2[3].x != checkPlayer2Ships[3].x || previousCountPlayer2[3].y != checkPlayer2Ships[3].y) && shipCheck2[3] != destroyerNum) {

				shipCheck2[3]++;
				previousCountPlayer2[3].y = checkPlayer2Ships[3].y;
				previousCountPlayer2[3].x = checkPlayer2Ships[3].x;
				//cout << "\nDestroyer Ship Destroyed Player 2";
				shipDeploy.setString("Destroyer Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (countsPlayer2[4] == subSize && subFlag == true) {
			if ((previousCountPlayer2[4].x != checkPlayer2Ships[4].x || previousCountPlayer2[4].y != checkPlayer2Ships[4].y) && shipCheck2[4] != subNum) {

				shipCheck2[4]++;
				previousCountPlayer2[4].y = checkPlayer2Ships[4].y;
				previousCountPlayer2[4].x = checkPlayer2Ships[4].x;
				//cout << "\nSubmarine Ship Destroyed Player 2";
				shipDeploy.setString("Submarine Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (j == mapSize - 1) {
			for (int i = 0; i < 4; i++)
			{
				checkPlayer2Ships[i].x = 0;
				checkPlayer2Ships[i].y = 0;
			}
		}
	}

	//////////////////////////////////CHECKING IN Y DIRECTION///////////////////////////////
	for (int i = initialStarting; i < mapSizePlayer2; i++) {
		for (int k = 0; k < 5; k++) {
			countsPlayer2[k] = 0;
		}
		int j = 1;
		for (j = 1; j < mapSize; j++)
		{
			if (tileMapPlayer2[i][j].getFillColor() == Color::Red && countsPlayer2[0] != carrierSize) {
				countsPlayer2[0]++;
				carrierFlag = true;

				checkPlayer2Ships[0].y = j - (destroyerSize - 1);
				checkPlayer2Ships[0].x = i;

				continue;
			}
			else if (countsPlayer2[0] != carrierSize) {
				carrierFlag = false;
				countsPlayer2[0] = 0;

			}
			else if (carrierFlag == true && previousCountPlayer2[0].y == checkPlayer2Ships[0].y && previousCountPlayer2[0].x == checkPlayer2Ships[0].x) {
				countsPlayer2[0] = 0;
			}


			if (tileMapPlayer2[i][j].getFillColor() == Color::Yellow && countsPlayer2[1] != battelSize) {
				countsPlayer2[1]++;
				battelFlag = true;
				checkPlayer2Ships[1].y = j - (battelSize - 1);
				checkPlayer2Ships[1].x = i;

				continue;
			}
			else if (countsPlayer2[1] != battelSize) {
				battelFlag = false;
				countsPlayer2[1] = 0;

			}
			else if (battelFlag == true && previousCountPlayer2[1].y == checkPlayer2Ships[1].y&& previousCountPlayer2[1].x == checkPlayer2Ships[1].x) {
				countsPlayer2[1] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Cyan && countsPlayer2[2] != kruiserSize) {
				countsPlayer2[2]++;
				kruiserFlag = true;

				checkPlayer2Ships[2].y = j - (kruiserSize - 1);
				checkPlayer2Ships[2].x = i;


				continue;
			}
			else if (countsPlayer2[2] != kruiserSize) {
				kruiserFlag = false;
				countsPlayer2[2] = 0;

			}
			else if (kruiserFlag == true && previousCountPlayer2[2].y == checkPlayer2Ships[2].y && previousCountPlayer2[2].x == checkPlayer2Ships[2].x) {
				countsPlayer2[2] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Green && countsPlayer2[3] != destroyerSize) {
				countsPlayer2[3]++;
				destroyerFlag = true;
				checkPlayer2Ships[3].y = j - (destroyerSize - 1);
				checkPlayer2Ships[3].x = i;
				continue;
			}
			else if (countsPlayer2[3] != destroyerSize) {
				destroyerFlag = false;
				countsPlayer2[3] = 0;

			}
			else if (destroyerFlag == true && previousCountPlayer2[3].y == checkPlayer2Ships[3].y&& previousCountPlayer2[3].x == checkPlayer2Ships[3].x) {
				countsPlayer2[3] = 0;
			}

			if (tileMapPlayer2[i][j].getFillColor() == Color::Magenta && countsPlayer2[4] != subSize) {
				countsPlayer2[4]++;
				subFlag = true;
				checkPlayer2Ships[4].y = j - (subSize - 1);
				checkPlayer2Ships[4].x = i;
				continue;
			}
			else if (countsPlayer2[4] != subSize) {
				subFlag = false;
				countsPlayer2[4] = 0;

			}
			else if (subFlag == true && previousCountPlayer2[4].y == checkPlayer2Ships[4].y && previousCountPlayer2[4].x == checkPlayer2Ships[4].x) {
				countsPlayer2[4] = 0;
			}

		}


		if (countsPlayer2[0] == carrierSize && carrierFlag == true) {
			if ((previousCountPlayer2[0].x != checkPlayer2Ships[0].x || previousCountPlayer2[0].y != checkPlayer2Ships[0].y) && shipCheck2[0] != carrierNum) {
				previousCountPlayer2[0].y = checkPlayer2Ships[0].y;
				previousCountPlayer2[0].x = checkPlayer2Ships[0].x;
				shipCheck2[0]++;
				//cout << "\nCarrier Ship Destroyed Player 2";
				shipDeploy.setString("Carrier Ship Destroyed Player 2");

				destroySound();

			}
		}
		if (countsPlayer2[1] == battelSize && battelFlag == true) {
			if ((previousCountPlayer2[1].x != checkPlayer2Ships[1].x || previousCountPlayer2[1].y != checkPlayer2Ships[1].y) && shipCheck2[1] != battelNum) {
				previousCountPlayer2[1].y = checkPlayer2Ships[1].y;
				previousCountPlayer2[1].x = checkPlayer2Ships[1].x;
				shipCheck2[1]++;
				//cout << "\nBattel Ship Destroyed Player 2";
				shipDeploy.setString("Battel Ship Destroyed Player 2");


				destroySound();

			}
		}
		if (countsPlayer2[2] == kruiserSize && kruiserFlag == true) {
			if ((previousCountPlayer2[2].x != checkPlayer2Ships[2].x || previousCountPlayer2[2].y != checkPlayer2Ships[2].y) && shipCheck2[2] != kruiserNum) {
				previousCountPlayer2[2].y = checkPlayer2Ships[2].y;
				previousCountPlayer2[2].x = checkPlayer2Ships[2].x;
				shipCheck2[2]++;
				//cout << "\nCruiser Ship Destroyed Player 2";
				shipDeploy.setString("Cruiser Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (countsPlayer2[3] == destroyerSize && destroyerFlag == true) {
			if ((previousCountPlayer2[3].x != checkPlayer2Ships[3].x || previousCountPlayer2[3].y != checkPlayer2Ships[3].y) && shipCheck2[3] != destroyerNum) {
				previousCountPlayer2[3].y = checkPlayer2Ships[3].y;
				previousCountPlayer2[3].x = checkPlayer2Ships[3].x;

				shipCheck2[3]++;
				//cout << "\nDestroyer Ship Destroyed Player 2";
				shipDeploy.setString("Destroyer Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (countsPlayer2[4] == subSize && subFlag == true) {
			if ((previousCountPlayer2[4].x != checkPlayer2Ships[4].x || previousCountPlayer2[4].y != checkPlayer2Ships[4].y) && shipCheck2[4] != subNum) {
				previousCountPlayer2[4].y = checkPlayer2Ships[4].y;
				previousCountPlayer2[4].x = checkPlayer2Ships[4].x;
				shipCheck2[4]++;
				//cout << "\nSubmarine Ship Destroyed Player 2";
				shipDeploy.setString("Submarine Ship Destroyed Player 2");

				destroySound();

			}

		}
		if (i == mapSizePlayer2 - 1) {
			for (int i = 0; i < 4; i++)
			{
				checkPlayer2Ships[i].x = 0;
				checkPlayer2Ships[i].y = 0;
			}
		}
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	/////////////////////////////Winning Condition////////////////////////////////////


	if (winningCheck) {
		player1WinCount = 0;
		player2WinCount = 0;

		for (int l = 0; l < 5; l++)
		{
			if (shipCheck[l] == 2) {
				player1Win = true;
				player1WinCount++;
			}
			else {
				player1WinCount = 0;
				player1Win = false;

			}
			if (shipCheck2[l] == 2) {
				player2Win = true;
				player2WinCount++;
			}
			else {
				player2Win = false;
				player2WinCount = 0;

			}
		}
	}
	if (player1WinCount==5&& player1Win == true) {

		scoreStore("Player1Wins");
		winningCheck = false;
		player1Win = false;
		player1Flag = false;
		player2Flag = false;
		globalCount = -1;
		text.setString("Player 1 Wins");
		outputWinning = true;
		winningSound();
	}
	else if (player2WinCount == 5 && player2Win==true) {

		scoreStore("Player2Wins");
		winningCheck = false;
		player2Win = false;
		player1Flag = false;
		player2Flag = false;
		outputWinning = true;
		text.setString("Player 2 Wins");
		winningSound();


		globalCount = -1;
	}
	else if (player2WinCount == 5 && player2Win == true && player1WinCount == 5 && player1Win == true) {
		cout << "Game Draw";
		text.setString("Game Draw");
		winningCheck = false;
		player1Flag = false;
		player2Flag = false;
		outputWinning = true;
		globalCount = -1;
	}

}




void easyMode(RenderWindow &window,RectangleShape& shipDeployer, RectangleShape& tileSelector, Vector2f& posShip, Vector2i &mousePosScreen, Vector2i &mousePosWindow, Vector2u &mousePosGrid, Vector2f& mousePosView, bool& inputCheck, bool& ship, bool& player1, bool& player2, bool& axisCheck, float& gridSizeF, unsigned& gridSizeU,Text &text, Text& shipDeploy, char arr1[16][16], char arr2[16][16], RectangleShape tileMap[16][16], RectangleShape tileMapPlayer2[34][16], bool &easyMod, bool& mediumMod , bool& hardMod) {
	static int globalCount = 1, count = 0, shipCountPlayer1 = 0, shipCountPlayer2 = 0;
	static Vector2f randomPosShip;

	static bool rotateFlag = true, player1Flag = true, player2Flag = false, wait = true, compPlay = false, compPlayCheck = false, randomFlag = true, compInput = false, compOutput = true, outputWinning = false, furtherOutput = false;

	static int carrierNum = 2;
	static int battelNum = 2;
	static int kruiserNum = 2;
	static int subNum = 2;
	static int destroyerNum = 2;
	static int easyMapSize = 9;
	static int easyMapSizePlayer2 = 26;
	static int easyGrid = 44;

	if (mediumMod) {
		carrierNum = 3;
		battelNum = 3;
		kruiserNum = 3;
		subNum = 3;
		destroyerNum = 3;
		easyGrid = 66;
		easyMapSize = 13;
		easyMapSizePlayer2 = 30;
		mediumMod = false;
	}
	else if (hardMod) {
		carrierNum = 4;
		battelNum = 4;
		kruiserNum = 4;
		subNum = 4;
		destroyerNum = 4;
		easyGrid = 88;
		easyMapSize = 16;
		easyMapSizePlayer2 = 33;
		hardMod = false;
	}
	
	/*if (compOutput) {
		cout << "Would you like to play with computer?";
		cin >> compInput;
		compOutput = false;
	}*/

	int initialStarting = 18;
	
	playersMap(window, tileMap, tileMapPlayer2, easyMapSize, easyMapSizePlayer2, initialStarting, gridSizeF);
	
	while (window.isOpen())
	{	
		

		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed) {
				window.close();
			}

			//Update mouse positions
			updateMousePos(window, mousePosScreen, mousePosWindow, mousePosGrid, mousePosView, gridSizeU);
			
			//Update game elements
			tileSelector.setPosition(mousePosGrid.x * gridSizeF, mousePosGrid.y * gridSizeF);
			tileSelector.setSize(Vector2f(gridSizeF, gridSizeF));

			//PLAYER 1 & PLAYER 2 POSITION CHECK
			if (player1Flag == true) {
				player1 = (mousePosGrid.x >= 1 && mousePosGrid.x <= easyMapSize - 1 && mousePosGrid.y >= 1 && mousePosGrid.y <= easyMapSize - 1);
			}
			if (player2Flag == true) {
				player2 = (mousePosGrid.x >= initialStarting && mousePosGrid.x <= easyMapSizePlayer2 - 1 && mousePosGrid.y >= 1 && mousePosGrid.y <= easyMapSize - 1);
			}
			
			/////////////////////Select Ship Size///////////////////
			switch (globalCount) {
				case 0: {

					if (Mouse::isButtonPressed(Mouse::Left)) {
						Vector2f posShip(mousePosGrid);

						////////////////////////////////RANDOM HIT////////////////////////////
						randomPosShip.x = randomNumberX(easyMapSizePlayer2, initialStarting);
						if (randomPosShip.x < initialStarting) { randomPosShip.x = initialStarting; }
						randomPosShip.y = randomNumberY(easyMapSize);

						hittingCheck(tileMap, tileMapPlayer2, posShip, player1, player2, player1Flag, player2Flag, arr1, arr2, initialStarting, 2, 2, 2,  2, 2,globalCount, compInput,randomPosShip,outputWinning,text,shipDeploy,easyMapSize,easyMapSizePlayer2);
					}
					break;
				}

				case 1: {
					if (battelNum > count) {

						playerTurn(event, mousePosGrid, tileMap, tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, battelSize, arr1, arr2, battelNum, shipCountPlayer1, shipCountPlayer2,player1Flag,player2Flag,wait, compPlay,initialStarting,compPlayCheck, randomFlag, randomPosShip, shipDeploy, easyMapSize, easyMapSizePlayer2);

					}
					else {
						globalCount++;
					}
					break;

				}
				case 2: {
					if (carrierNum > count) {
						playerTurn(event, mousePosGrid, tileMap, tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, carrierSize, arr1, arr2, carrierNum, shipCountPlayer1, shipCountPlayer2,player1Flag,player2Flag, wait, compPlay, initialStarting, compPlayCheck, randomFlag, randomPosShip, shipDeploy, easyMapSize, easyMapSizePlayer2);
					}
					else {
						globalCount++;
					}
					break;

				}
				case 3: {
					if (kruiserNum > count) {
						playerTurn(event, mousePosGrid, tileMap, tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, kruiserSize, arr1, arr2, kruiserNum, shipCountPlayer1, shipCountPlayer2, player1Flag, player2Flag, wait, compPlay, initialStarting, compPlayCheck, randomFlag, randomPosShip, shipDeploy, easyMapSize, easyMapSizePlayer2);
					}
					else {
						globalCount++;

					}
					break;

				}
				case 4: {
					if (subNum > count) {
						playerTurn(event, mousePosGrid, tileMap, tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, subSize, arr1, arr2, subNum, shipCountPlayer1, shipCountPlayer2, player1Flag, player2Flag, wait, compPlay, initialStarting, compPlayCheck, randomFlag, randomPosShip, shipDeploy, easyMapSize, easyMapSizePlayer2);
					}
					else {
						globalCount++;
					}
					break;

				}
				case 5: {
					if (destroyerNum > count) {
						playerTurn(event, mousePosGrid, tileMap, tileMapPlayer2, shipDeployer, tileSelector, inputCheck, ship, gridSizeF, player1, player2, rotateFlag, destroyerSize, arr1, arr2, destroyerNum, shipCountPlayer1, shipCountPlayer2, player1Flag, player2Flag, wait, compPlay, initialStarting, compPlayCheck, randomFlag, randomPosShip, shipDeploy, easyMapSize, easyMapSizePlayer2);
					}
					else {
						break;
					}
				}
			}
			//Render
			window.clear();

			//Render game elements

			if (compOutput) {
				Font font;
				font.loadFromFile("Fonts/SourceSansPro-SemiBold.ttf");
				Text comp;
				comp.setCharacterSize(70);
				comp.setFillColor(sf::Color::White);
				comp.setFont(font);
				comp.setPosition(400, 400);
				comp.setString("Would you like to play with computer?.\n        Press Y For Yes. Press N For No");
				
				window.draw(comp);
				window.display();

				if (Keyboard::isKeyPressed(Keyboard::Y)) {
					compInput = true;
					compOutput = false;
					furtherOutput = true;
					window.clear();
					Sleep(250);

				}
				else if (Keyboard::isKeyPressed(Keyboard::N)) {
					compInput=false;
					furtherOutput = true;
					compOutput = false;
					window.clear();
					Sleep(250);
				}
			}


			////////////////////////////////Play wiht computer/////////////////////////////
			


			if (furtherOutput) {

				if (outputWinning == false) {
					drawing(window, tileMap, tileMapPlayer2, initialStarting,easyMapSize,easyMapSizePlayer2);
				}
				else {
					window.draw(text);
				}


				if (player1) {
					window.draw(tileSelector);
				}
				if(player2){
					window.draw(tileSelector);
				}
				if (ship) {
					window.draw(shipDeployer);
				}
				window.draw(shipDeploy);
				//Done drawing
				window.display();

			}


			if (shipCountPlayer1 == easyGrid) {
				player1Flag = false;
				player1 = false;
				if (compInput) {
					compPlay = true;
				}
				else {
					player2Flag = true;
				}
				if (easyMod) {
					carrierNum = 2;
					battelNum = 2;
					kruiserNum = 2;
					subNum = 2;
					destroyerNum = 2;
				}
				else if(easyGrid==66){
					carrierNum = 3;
					battelNum = 3;
					kruiserNum = 3;
					subNum = 3;
					destroyerNum = 3;
				}
				else if (easyGrid == 88) {
					carrierNum = 4;
					battelNum = 4;
					kruiserNum = 4;
					subNum = 4;
					destroyerNum = 4;
				}


				globalCount = 1;
				shipCountPlayer1 = 0;
			}
			if (shipCountPlayer2 == easyGrid) {
				cout << "Both players selected their ships";
				Sleep(500);
				playersMap(window, tileMap, tileMapPlayer2, easyMapSize, easyMapSizePlayer2, initialStarting, gridSizeF);

				globalCount = 0;
				shipCountPlayer2 = 0;
				player2 = false;
				player2Flag = false;
				if (compInput) {
					compPlay = false;
				}

				player1Flag = true;
			}

		}
	}


}


int main()
{
	//Init game
	static float gridSizeF = 50.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2u mousePosGrid;
	Vector2f posShip;

	static bool easyMod = false, mediumMod = false, hardMod = false,scoreCheck=false;
	//Player 1 Map
	char arr1[16][16];
	RectangleShape tileMap[16][16];

	//PLayer 2 Map
	char arr2[16][16];
	RectangleShape tileMapPlayer2[34][16];


	/////////////////////////TEXT///////////////////////////////
	Font font;
	font.loadFromFile("Fonts/SourceSansPro-SemiBold.ttf");
	Text text;
	text.setCharacterSize(72);
	text.setFillColor(sf::Color::White);
	text.setFont(font);
	text.setPosition(650+120, 360+100);
	text.setOrigin((650)/2, (360/2));

	Text shipDeploy;
	shipDeploy.setCharacterSize(20);
	shipDeploy.setFillColor(sf::Color::White);
	shipDeploy.setFont(font);
	shipDeploy.setPosition(1*gridSizeF, 10*gridSizeF);

	
	Text gameName;
	gameName.setCharacterSize(130);
	gameName.setFillColor(sf::Color::Red);
	gameName.setFont(font);
	gameName.setStyle(Text::Bold);
	gameName.setPosition(220, 1);
	gameName.setString("B A T T E L - S H I P");

	Text mainText;
	mainText.setCharacterSize(70);
	mainText.setFillColor(sf::Color::White);
	mainText.setFont(font);
	mainText.setPosition(560, 230);
	mainText.setString("Main Menu");


	Text mainOptions;
	mainOptions.setCharacterSize(30);
	mainOptions.setFillColor(sf::Color::Yellow);
	mainOptions.setStyle(Text::Italic);
	mainOptions.setFont(font);
	mainOptions.setPosition(560,350);
	mainOptions.setString("1. Easy");

	Text mainOptionsMedium;
	mainOptionsMedium.setCharacterSize(30);
	mainOptionsMedium.setFillColor(sf::Color::Yellow);
	mainOptionsMedium.setStyle(Text::Italic);
	mainOptionsMedium.setFont(font);
	mainOptionsMedium.setPosition(560, 400);
	mainOptionsMedium.setString("2. Medium");

	Text mainOptionsHard;
	mainOptionsHard.setCharacterSize(30);
	mainOptionsHard.setFillColor(sf::Color::Yellow);
	mainOptionsHard.setStyle(Text::Italic);
	mainOptionsHard.setFont(font);
	mainOptionsHard.setPosition(560, 450);
	mainOptionsHard.setString("3. Hard");

	Text scoresPlayer;
	scoresPlayer.setCharacterSize(30);
	scoresPlayer.setFillColor(sf::Color::Yellow);
	scoresPlayer.setStyle(Text::Italic);
	scoresPlayer.setFont(font);
	scoresPlayer.setPosition(560, 500);
	scoresPlayer.setString("4. Scores");

	Text scoreShow;	Text scoreShow2;


	bool player1, player2=false, ship = false, inputCheck = true, axisCheck = false;

	//Init window
	RenderWindow window(VideoMode(1920, 1080), "BattelShip");
	window.setFramerateLimit(120);

	RenderWindow mainMenu(VideoMode(1450, 720), "BattelShip | Main Menu");
	window.setFramerateLimit(120);

	//Tile Selector
	RectangleShape tileSelector(Vector2f(gridSizeF, gridSizeF));
	tileSelector.setFillColor(Color::Transparent);
	tileSelector.setOutlineThickness(1.f);
	tileSelector.setOutlineColor(Color::Green);

	//Deploying Ships
	RectangleShape shipDeployer(Vector2f(gridSizeF, gridSizeF));
	shipDeployer.setFillColor(Color::Transparent);
	shipDeployer.setOutlineThickness(3.f);
	shipDeployer.setOutlineColor(Color::Red);

	while (mainMenu.isOpen())
	{

		Event event;
		while (mainMenu.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				mainMenu.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Num1)) {
				easyMod = true;
				mainMenu.close();
			}if (Keyboard::isKeyPressed(Keyboard::Num2)) {
				mediumMod = true;
				shipDeploy.setPosition(1 * gridSizeF, 14 * gridSizeF);
				mainMenu.close();

			}if (Keyboard::isKeyPressed(Keyboard::Num3)) {
				hardMod = true;
				shipDeploy.setPosition(1 * gridSizeF, 17 * gridSizeF);

				mainMenu.close();

			}
			if (Keyboard::isKeyPressed(Keyboard::Num4)) {

				int p1Score = 0, p2Score = 0;
				fstream score;
				score.open("score.txt", ios::in);

				string playerScore, str;
				while (!score.eof()) {
					getline(score, playerScore);
					if (playerScore == "") {
						score.get();
						break;
					}
					if (playerScore[6] == '1') {
						p1Score++;
					}
					else if (playerScore[6] == '2') {
						p2Score++;
					}
				}
				score.close();

				scoreShow.setCharacterSize(30);
				scoreShow.setFillColor(sf::Color::Yellow);
				scoreShow.setStyle(Text::Italic);
				scoreShow.setFont(font);
				scoreShow.setPosition(20, 50);
				
				scoreShow.setString("Player 1 total winning score : " + to_string(p1Score));

				scoreShow2.setCharacterSize(30);
				scoreShow2.setFillColor(sf::Color::Yellow);
				scoreShow2.setStyle(Text::Italic);
				scoreShow2.setFont(font);
				scoreShow2.setPosition(20, 100);
				scoreShow2.setString("Player 2 total winning score : " + to_string(p2Score));

				scoreCheck = true;
			}
		}

		mainMenu.clear();

		if (scoreCheck == false) {
			mainMenu.draw(gameName);
			mainMenu.draw(mainText);
			mainMenu.draw(mainOptions);
			mainMenu.draw(mainOptionsMedium);
			mainMenu.draw(mainOptionsHard);
			mainMenu.draw(scoresPlayer);
		}
		else if (scoreCheck==true) {
			mainMenu.draw(scoreShow);
			mainMenu.draw(scoreShow2);

		}

		mainMenu.display();
	}

	easyMode(window, shipDeployer, tileSelector, posShip, mousePosScreen, mousePosWindow, mousePosGrid, mousePosView, inputCheck, ship, player1, player2, axisCheck, gridSizeF, gridSizeU,text,shipDeploy,arr1,arr2,tileMap,tileMapPlayer2,easyMod,mediumMod,hardMod);

	return 0;
}