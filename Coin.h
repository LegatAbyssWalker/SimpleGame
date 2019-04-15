#ifndef COIN_H
#define COIN_H

#include "SFML/Graphics.hpp"


class Coin {
	private:
		sf::RectangleShape coin;

	public:
		//Constructors/Destructors
		Coin(sf::Vector2f size);
		~Coin();


		//Functions
		void drawTo(sf::RenderWindow &window);
		void setCoinPos(sf::Vector2f newPos);
		sf::FloatRect getGlobalBounds();
};

#endif