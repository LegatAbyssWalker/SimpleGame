#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"


class Enemy {
	private:
		sf::RectangleShape enemy;


	public:
		//Constructors/Destructors
		Enemy(sf::Vector2f size);
		~Enemy();


		//Functions
		void drawTo(sf::RenderWindow &window);
		void updateMovement(sf::Vector2f autoDistance);
		void setEnemyPos(sf::Vector2f newPos);
		sf::FloatRect getGlobalBounds();

		int getEnemyX();
		int getEnemyY();
};

#endif