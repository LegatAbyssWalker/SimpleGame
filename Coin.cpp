#include "Coin.h"


//Constructors/Destructors
Coin::Coin(sf::Vector2f size) {
	coin.setSize(size);
	coin.setFillColor(sf::Color::Yellow);
}

Coin::~Coin() {
	//
}


//Functions
void Coin::drawTo(sf::RenderWindow& window) {
	window.draw(coin);
}

void Coin::setCoinPos(sf::Vector2f newPos) {
	coin.setPosition(newPos);
}

sf::FloatRect Coin::getGlobalBounds() {
	return coin.getGlobalBounds();
}
