// author Ben Stynes(Better Ben) and Szymon Piskorz
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupButtons(); //set up button properties
	//colors for our buttons and text 

	const sf::Color RED{ 180,0,0,255 };
	const sf::Color GREEN{ 0,180,0,255 };
	const sf::Color BLUE{ 0,0,180,255 };
	const sf::Color YELLOW{ 180,180,0,255 };
	const sf::Color WHITE{ 255,255,255,255 };



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // bool to control exiting game

	sf::RectangleShape m_redSquare; //red button/ light
	sf::RectangleShape m_yellowSquare;//yellow button/ light
	sf::RectangleShape m_blueSquare;//blue button/ light
	sf::RectangleShape m_greenSquare;//green button/ light
};

#endif // !GAME

