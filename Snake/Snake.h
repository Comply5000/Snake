#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

class Snake
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Object
	sf::RectangleShape box[15][17];
	sf::RectangleShape* reset;
	sf::RectangleShape* youDied;

	//Textures
	sf::Texture lightGreen;
	sf::Texture darkGreen;
	sf::Texture snakeTexture;
	sf::Texture appleTexture;
	sf::Texture resetTexture;
	sf::Texture deathTexture;

	//Logic
	bool snake[15][17];
	bool apple[15][17];
	std::vector<int>snakeBodyX;
	std::vector<int>snakeBodyY;
	int Y, X;
	int headX, headY;
	int points;
	bool death;

	//Clock
	sf::Clock clock;
	float dt;

	//Text
	sf::Font font;
	sf::Text text;

	//Mouse position
	sf::Vector2f mousePosition;

	//Private functions
	void initWindow();
	void initBoard();
	void drawBoard();
	void initSnake();
	void drawSnake();
	void initText();

public:
	//Public functions
	Snake();
	~Snake();

	const bool running() const;
	void poolEvent();
	void updateMousePosition();
	void updateDt();

	void snakeMove();
	bool logic();
	void appleResp();
	void gameEnd();

	void update();
	void render();

};

