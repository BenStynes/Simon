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

	const int NUM_OF_APPLES = 500;

	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "First Graphics in C++");

	srand(time(NULL));
	float randomNum;
	// generate  number between 1 and 10

	randomNum = rand() % 750 + 0;


	// setup any shapes or variables.
	sf::RectangleShape apples[NUM_OF_APPLES];
	sf::RectangleShape player;


	player.setSize(sf::Vector2f(20 , 20));

	
	for (int i = 0; i < NUM_OF_APPLES; i++)
	{
		apples[i].setSize(sf::Vector2f(20,20));
		
	}

	player.setFillColor(sf::Color::Red);

	player.setPosition(rand() % 780, rand() % 580);



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
				player.move(-5, 0);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.move(5, 0); 
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				player.move(0,-5);

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				player.move(0,5);
			}

			for (int i = 0;  i < NUM_OF_APPLES;  i++)
			{
				if (apples[i].getPosition().x > player.getPosition().x)
				{
					apples[i].move(-rand() % 40 / 10.0, 0);

				}
				else if (apples[i].getPosition().x < player.getPosition().x)
				{
					apples[i].move(rand() % 40 / 10.0 , 0);
				}
				if (apples[i].getPosition().y > player.getPosition().y)
				{
					apples[i].move(0, -rand() % 40 / 10.0);

				}
				else if (apples[i].getPosition().y < player.getPosition().y)
				{
					apples[i].move(0, rand() % 40 / 10.0 );
				}
				
				if (apples[i].getGlobalBounds().intersects(player.getGlobalBounds()))
				{

					apples[i].setPosition(rand() %  1000, 0);
				}
				if (apples[i].getGlobalBounds().intersects(apples[i-1].getGlobalBounds()) || apples[i].getGlobalBounds().intersects(apples[i - 1].getGlobalBounds()))
				{
					apples[i].setPosition(rand() % 1000, rand() % 1000);
				}
			}
		
			//if (apple.getGlobalBounds().intersects(player.getGlobalBounds()))
			//{

			//	player.setFillColor(sf::Color::Blue);
			//}
			window.clear();

			window.draw(player);

			for (int i = 0; i < NUM_OF_APPLES; i++)
			{
				window.draw(apples[i]);
			}
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}


