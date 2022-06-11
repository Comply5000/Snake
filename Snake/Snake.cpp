#include "Snake.h"

//Private functions
void Snake::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 680;
	this->window = new sf::RenderWindow(this->videoMode, "Snake", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);	
}

void Snake::initBoard()
{
	this->lightGreen.loadFromFile("Textures/light-green.png");
	this->darkGreen.loadFromFile("Textures/dark-green.png");
	this->snakeTexture.loadFromFile("Textures/blue.png");
	this->appleTexture.loadFromFile("textures/apple.png");

	this->reset = new sf::RectangleShape;
	this->youDied = new sf::RectangleShape;

	this->resetTexture.loadFromFile("Textures/reset.png");
	this->deathTexture.loadFromFile("Textures/died.png");

	int x = 0,y;
	for (int i = 0;i < 15;i++)
	{
		y = 0;
		for (int j = 0;j < 17;j++)
		{
			this->box[i][j].setPosition(y, x);
			this->box[i][j].setSize(sf::Vector2f(40.f, 40.f));
			if (i % 2 == 0)
			{
				if (j % 2 == 0)
					this->box[i][j].setTexture(&this->darkGreen);
				else
					this->box[i][j].setTexture(&this->lightGreen);
			}
			else
			{
				if (j % 2 == 1)
					this->box[i][j].setTexture(&this->darkGreen);
				else
					this->box[i][j].setTexture(&this->lightGreen);
			}
			y += 40;
		}
		x += 40;
	}
}

void Snake::drawBoard()
{
	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 17;j++)
		{
			this->window->draw(this->box[i][j]);
		}
	}
}

void Snake::initSnake()
{
	this->headX = 4;
	this->headY = 7;

	this->snakeBodyY.push_back(7);
	this->snakeBodyX.push_back(4);
	this->snakeBodyY.push_back(7);
	this->snakeBodyX.push_back(3);

	this->snake[7][3] = true;
	this->apple[7][12] = true;
	this->dt = this->clock.restart().asSeconds();
}

void Snake::drawSnake()
{
	if (!death)
	{
		//this->snake[headY][headX] = true;

		for (int i = 0;i < 15;i++)
		{
			for (int j = 0;j < 17;j++)
			{
				if (snake[i][j] || (this->headX == j && headY == i))
					this->box[i][j].setTexture(&this->snakeTexture);
				else if (apple[i][j])
					this->box[i][j].setTexture(&this->appleTexture);
				else
				{
					if (i % 2 == 0)
					{
						if (j % 2 == 0)
							this->box[i][j].setTexture(&this->darkGreen);
						else
							this->box[i][j].setTexture(&this->lightGreen);
					}
					else
					{
						if (j % 2 == 1)
							this->box[i][j].setTexture(&this->darkGreen);
						else
							this->box[i][j].setTexture(&this->lightGreen);
					}
				}
			}
		}
	}
	
		
}

void Snake::initText()
{
	this->font.loadFromFile("Fonts/arial.ttf");

	this->text.setFont(this->font);
	this->text.setPosition(sf::Vector2f(5.f, 570.f));
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(24);
}



//Public funtions
Snake::Snake()
{
	this->initWindow();
	this->initBoard();
	this->initSnake();
	this->initText();
}

Snake::~Snake()
{
	this->window->close();
}

const bool Snake::running() const
{
	return this->window->isOpen();
}

void Snake::poolEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Snake::updateMousePosition() //aktualizacja pozycji myszy wzglêcem okna
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void Snake::updateDt()
{
	//update time
	this->dt = this->clock.getElapsedTime().asSeconds();
}

void Snake::snakeMove()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->Y !=1)
	{
		this->Y = -1;
		this->X = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->Y != -1)
	{
		this->Y = 1;
		this->X = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->X != 1)
	{
		this->Y = 0;
		this->X = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->X != -1)
	{
		this->Y = 0;
		this->X = 1;
	}
	int a, b;
	a = headX + X;
	b = headY + Y;

	if (dt >= 0.12 && !death && (X!=0 || Y !=0))
	{
		this->snake[headY][headX] = true;
		this->headX += this->X;
		this->headY += this->Y;

		this->snakeBodyY.insert(snakeBodyY.begin(), this->headY);
		this->snakeBodyX.insert(snakeBodyX.begin(), this->headX);

		if (!this->logic())
		{
			this->snakeBodyY.erase(snakeBodyY.end() - 1, snakeBodyY.end());
			this->snakeBodyX.erase(snakeBodyX.end() - 1, snakeBodyX.end());
		}

		for (int i = 0;i < 15;i++)
			for (int j = 0;j < 17;j++)
				if (snake[i][j])
					snake[i][j] = false;

		for (int i = 1;i < snakeBodyX.size();i++)
		{
			this->snake[snakeBodyY[i]][snakeBodyX[i]] = true;
		}


		this->dt = this->clock.restart().asSeconds();
	}
	

}

bool Snake::logic()
{
	bool getPoint = false;

	for (int i = 0;i < 15;i++)
	{
		for (int j = 0;j < 17;j++)
		{
			if (apple[i][j] && headX == j && headY == i)
			{
				this->points++;
				apple[i][j] = false;
				this->appleResp();
				getPoint = true;
			}
		}
	}
	std::string t = "Points: " + std::to_string(this->points);
	this->text.setString(t);

	if (getPoint) return true;
	else return false;
}

void Snake::appleResp()
{
	while (true)
	{
		int a = rand()%15;
		int b = rand() % 17;

		if (!snake[a][b] && a!=headY && b!=headX)
		{
			this->apple[a][b] = true;
			break;
		}
	}
}

void Snake::gameEnd()
{
	bool crash = false;
	for (int i = 0;i < 15;i++)
		for (int j = 0;j < 17;j++)
			if (snake[i][j] && i == headY && j == headX)
				crash = true;

	if (headX > 16 || headY > 14 || headX < 0 || headY < 0 || crash)
	{
		this->death = true;
		this->reset->setPosition(240.f, 300.f);
		this->reset->setSize(sf::Vector2f(200.f, 100.f));
		this->reset->setTexture(&this->resetTexture);

		this->youDied->setPosition(160.f, 150.f);
		this->youDied->setSize(sf::Vector2f(360.f, 105.f));
		this->youDied->setTexture(&this->deathTexture);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->reset->getGlobalBounds().contains(this->mousePosition))
		{
			delete this->reset;
			delete this->youDied;
			this->reset = new sf::RectangleShape;
			this->youDied = new sf::RectangleShape;
			this->death = false;

			for (int i = 0;i < 15;i++)
			{
				for (int j = 0;j < 17;j++)
				{
					if (apple[i][j])
						apple[i][j] = false;
					if (snake[i][j])
						snake[i][j] = false;
				}
			}

			this->snakeBodyY.clear();
			this->snakeBodyX.clear();
			this->snakeBodyY.shrink_to_fit();
			this->snakeBodyX.shrink_to_fit();
			this->initSnake();
			this->X = 0;
			this->Y = 0;
			this->points = 0;
		}
	}
}

void Snake::update()
{
	this->running();
	this->poolEvent();
	this->updateMousePosition();
	this->snakeMove();
	this->updateDt();
	this->gameEnd();
}

void Snake::render()
{
	this->window->clear();
	this->drawBoard();
	this->drawSnake();
	this->window->draw(*this->reset);
	this->window->draw(*this->youDied);
	this->window->draw(this->text);
	this->window->display();
}
