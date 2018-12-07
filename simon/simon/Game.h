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

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // bool to control exiting game

	sf::RectangleShape m_redSquare; //red buttom/ light

};

#endif // !GAME

