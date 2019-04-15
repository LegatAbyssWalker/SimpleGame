#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include "Coin.h"

class Player {
	private:
		sf::RectangleShape player;

	public:
		//Constructors/Destructors
		Player(sf::Vector2f size);
		~Player();


		//Functions
		void drawTo(sf::RenderWindow &window);
		void moveTo(sf::Vector2f distance);
		void setPlayerPos(sf::Vector2f newPos);
		int getX();
		int getY();
		bool collisionWithCoin(Coin *coin);
};

#endif