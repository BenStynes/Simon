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




	
		
		
	
class Particle
{
	
public:
	sf::Vector2f velocity;
	int framesToLive;
	
	sf::CircleShape shape;
	void Update()
	{

		framesToLive--;

		if (framesToLive > 0)
		{

			shape.move(velocity);

		}
	}
	
	
};
	
		
		



class ParticleSystem
{
	static const int numParticles = 30;
	
	int maxSpeed;
	sf::Vector2f center;
public:
	
	Particle particles[numParticles];
	ParticleSystem()
	{
		
	}
	void Update()
	{
		for (int i = 0; i < numParticles; i++)
		{


			particles[i].Update();
			
			
		}
	}
	void Draw(sf::RenderWindow &window)
	{
		for (int i = 0; i < numParticles; i++)
		{
			if (particles[i].framesToLive > 0)
			{

				window.draw(particles[i].shape);
			}

		}
    }
	void Init(sf::Vector2f pos)
	{
		maxSpeed = 20;
		center = pos;

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setFillColor(sf::Color{ static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255) });
			particles[i].framesToLive = rand() % 1000;
			particles[i].shape.setPointCount(rand() % 12);
			particles[i].shape.setRadius(10);
			particles[i].velocity.x = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
			particles[i].shape.setPosition(center);
			particles[i].velocity.y = rand() / double(RAND_MAX) * maxSpeed * 2 - maxSpeed;
		}
	
	}
	void Init(sf::Vector2f pos, bool rain)
	{
		maxSpeed = 20;
		center = pos;

		for (int i = 0; i < numParticles; i++)
		{
			particles[i].shape.setFillColor(sf::Color{ static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255),static_cast<unsigned int>(rand() % 255) });
			particles[i].framesToLive = rand() % 1000;
			particles[i].shape.setPointCount(rand() % 12);
			particles[i].shape.setRadius(10);
			particles[i].velocity.x = 15;
			particles[i].shape.setPosition(center);
			particles[i].velocity.y = 15;
		}
	}
};
class Player
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f lookDirection;
	int waitToFireCounter;
};

class Bullet
{
public:
	sf::RectangleShape shape;
	sf::Vector2f velocity;

};

int main()
{
	//create Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

	srand(time(NULL));
	

	const int numOfApples = 20;
	sf::RectangleShape apples[numOfApples];
	Player player;
	const int MAX_EXPLOIONS = 50;
	ParticleSystem explosions[MAX_EXPLOIONS];
	ParticleSystem rain[MAX_EXPLOIONS];
	player.waitToFireCounter = 10;
	player.velocity = { 0,0 };
	player.lookDirection = { 0,-1 };


	const int numBullets = 10;

	sf::RectangleShape onScreenArea;
	onScreenArea.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));

	Bullet bullets[numBullets];
	for (int i = 0; i < numBullets; i++)
	{
		bullets[i].shape.setSize(sf::Vector2f(10, 10));
		bullets[i].shape.setPosition(-2000, -2000);
		bullets[i].shape.setFillColor(sf::Color::Yellow);

		bullets[i].velocity.x = 0;
		bullets[i].velocity.y = 0;
	}


	for (int i = 0; i < numOfApples; i++)
	{
		apples[i].setSize(sf::Vector2f(20, 20));
		apples[i].setPosition(rand() % 780, rand() % 580);
	}

	player.shape.setSize(sf::Vector2f(20, 20));
	player.shape.setFillColor(sf::Color::Red);
	player.shape.setPosition(rand() % 780, rand() % 580);


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

			player.velocity.x = 0;
			player.velocity.y = 0;

			// get keyboard input.
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.velocity.x = -5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.velocity.x = 5;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.velocity.y = -5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.velocity.y = 5;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (player.waitToFireCounter == 0)
				{
					for (int i = 0; i < numBullets; i++)
					{
						if (bullets[i].shape.getPosition().x == -2000)
						{
							bullets[i].shape.setPosition(player.shape.getPosition());
							bullets[i].velocity = player.lookDirection;
							bullets[i].velocity.x *= 2;
							bullets[i].velocity.y *= 2;

							player.waitToFireCounter = 10;
							break;
						}

					}
				}

			}
			if (player.velocity.x != 0)
			{
				player.lookDirection = player.velocity;
			}
			else if (player.velocity.y != 0)
			{
				player.lookDirection = player.velocity;
			}
			player.shape.move(player.velocity);

			for (int i = 0; i < numBullets; i++)
			{
				if (bullets[i].shape.getPosition().x != -2000)
				{
					bullets[i].shape.move(bullets[i].velocity);
					if (!onScreenArea.getGlobalBounds().intersects(bullets[i].shape.getGlobalBounds()))
					{
						bullets[i].shape.setPosition(-2000, -2000);
						bullets[i].velocity.x = 0;
						bullets[i].velocity.y = 0;

					}
				}
			}
			


			if (player.waitToFireCounter > 0)
			{
				player.waitToFireCounter--;

			}

			for (int i = 0; i < numOfApples; i++)
			{
				if (apples[i].getPosition().x != -1000)
				{
					apples[i].move(rand() % 7 - 3, rand() % 7 - 3);
				}
			}

			//collision detection
			for (int appleIndex = 0; appleIndex < numOfApples; appleIndex++)
			{
				if (apples[appleIndex].getGlobalBounds().intersects(player.shape.getGlobalBounds()))
				{

					apples[appleIndex].setPosition(-1000, -1000);
				}
				for (int bulletIndex = 0; bulletIndex < numBullets; bulletIndex++)
				{
					if (apples[appleIndex].getGlobalBounds().intersects(bullets[bulletIndex].shape.getGlobalBounds()))
					{
						for (int explosionsIndex = 0; explosionsIndex < MAX_EXPLOIONS; explosionsIndex++)
						{
							explosions[explosionsIndex].Init(apples[appleIndex].getPosition());
							bullets[bulletIndex].shape.setPosition(-2000, -2000);
							bullets[bulletIndex].velocity.x = 0;
							bullets[bulletIndex].velocity.y = 0;
							apples[appleIndex].setPosition(-1000, -1000);
						}
					}
				}


			}
			
			for (int i = 0; i < MAX_EXPLOIONS; i++)
			{

			
				rain[i].Update();
				explosions[i].Update();
			}
			window.clear();


			for (int i = 0; i < numOfApples; i++)
			{
				window.draw(apples[i]);
			}

			for (int i = 0; i < numBullets; i++)
			{
				window.draw(bullets[i].shape);
			}
			for (int i = 0; i < MAX_EXPLOIONS; i++)
			{
				explosions[i].Draw(window);
				rain[i].Draw(window);
			}
			window.draw(player.shape);
			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

