// author Ben Stynes(Better Ben) and Szymon Piskorz

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Simon" },
	m_exitGame{ false },
	m_redSquare{ sf::Vector2f{200.0f, 200.0f} },
	m_yellowSquare{sf::Vector2f{200,200}},
	m_greenSquare{sf::Vector2f{200,200}},
	m_blueSquare{ sf::Vector2f{200,200} }
{
	setupButtons();
	setupText();
}


Game::~Game()
{
}

/// <summary>
/// @brief setup text, squares and sounds
/// 
/// load font and sound
/// setup the text messages
/// setup the tone (pitch)
/// position and colour of the squares.
/// </summary>
void Game::setupButtons()
{
	m_redSquare.setFillColor(RED);
	m_redSquare.setPosition(sf::Vector2f(570, 30));
	m_greenSquare.setFillColor(GREEN);
	m_greenSquare.setPosition(sf::Vector2f(350, 30));
	m_yellowSquare.setFillColor(YELLOW);
	m_yellowSquare.setPosition(sf::Vector2f(350, 250));
	m_blueSquare.setFillColor(BLUE);
	m_blueSquare.setPosition(sf::Vector2f(570, 250));
}

void Game::setupText()
{
	
	//load the font file
	if (m_imapctFont.loadFromFile("assets/fonts/impact.ttf"))
	{
		std::cout << "Font loaded ok" << std::endl;
	}
	m_titleText.setFont(m_imapctFont);
	m_titleText.setFillColor(WHITE);
	m_titleText.setCharacterSize(64);
	m_titleText.setPosition(50, 30);
	m_titleText.setString("S I M O N");

	//setup green message easy game 8 
	m_instructionTextGreen.setFont(m_imapctFont);
	m_instructionTextGreen.setFillColor(GREEN);
	m_instructionTextGreen.setCharacterSize(32);
	m_instructionTextGreen.setPosition(50, 100);
	m_instructionTextGreen.setString("Press green for \n an easy game");
	//setup red text for medium game 16 
	m_instructionTextRed.setFont(m_imapctFont);
	m_instructionTextRed.setFillColor(RED);
	m_instructionTextRed.setCharacterSize(32);
	m_instructionTextRed.setPosition(50, 200);
	m_instructionTextRed.setString("Press red for \n a medium game");
	//setup yellow text for hard  game 32 
	m_instructionTextYellow.setFont(m_imapctFont);
	m_instructionTextYellow.setFillColor(YELLOW);
	m_instructionTextYellow.setCharacterSize(32);
	m_instructionTextYellow.setPosition(50, 300);
	m_instructionTextYellow.setString("Press yellow for \n a hard game");
	//setup status font 
	m_instructionTextBlue.setFont(m_imapctFont);
	m_instructionTextBlue.setFillColor(BLUE);
	m_instructionTextBlue.setCharacterSize(32);
	m_instructionTextBlue.setPosition(50, 400);
	m_instructionTextBlue.setString("Press blue to \n exit game");

	m_statusText.setFont(m_imapctFont);
	m_statusText.setFillColor(WHITE);
	m_statusText.setCharacterSize(22);
	m_statusText.setPosition(500, 453);
	m_statusText.setString("Test");//no status on menu screen;
		

}



void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_greenSquare);
	m_window.draw(m_redSquare);
	m_window.draw(m_yellowSquare);
	m_window.draw(m_blueSquare);
	m_window.draw(m_titleText);
	m_window.draw(m_instructionTextGreen);
	m_window.draw(m_instructionTextYellow);
	m_window.draw(m_instructionTextBlue);
	m_window.draw(m_instructionTextRed);
	m_window.draw(m_statusText);
	m_window.display();
}

