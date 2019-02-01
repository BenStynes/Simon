// catchGame.cpp : Defines the entry point for the console application.
//

// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
int main()
{
	//create Window
	sf::RenderWindow window(sf::VideoMode(400, 400), "First Graphics in C++");
	srand(time(NULL));
	
	sf::Texture platformTexture;
	platformTexture.loadFromFile("platform.png");
	sf::Texture playerTexture;
	playerTexture.loadFromFile("doodlejumper.png");
	sf::Sprite platforms[10];
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	float playerX = 100, playerY = 100;
	float velocityX = 0, velocityY = 0, gravity = 0.3;


	for (int i = 0; i < 10; i++)
	{
		float randomX = rand() % 400;
		float randomY = rand() % 400;
		platforms[i].setTexture(platformTexture);
		platforms[i].setPosition(randomX, randomY);
	}
	
	// set timePerFrame to 1 60th of a second. 60 frames per second

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{


			// get keyboard input.

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerX -= 4;


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerX += 4;
			}

			velocityY = velocityY + gravity;
			playerY = playerY + velocityY;

			playerSprite.setPosition(playerX, playerY);
			if (playerY > 400 - 40)
			{
				velocityY = -10;
			}
			if (velocityY > 0)
			{
				for (int i = 0; i < 10; i++)
				{

					if (playerSprite.getGlobalBounds().intersects(platforms[i].getGlobalBounds()))
					{
						velocityY = -10;
					}
				}
			}
		
			window.clear();

			for (int i = 0; i < 10; i++)
			{
				window.draw(platforms[i]);

			}
			window.draw(playerSprite);
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}


