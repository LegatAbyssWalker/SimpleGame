#include "Player.h"


//Constructors/Destructors
Player::Player(sf::Vector2f size) {
	player.setSize(size);
	player.setFillColor(sf::Color::Green);
}


Player::~Player() {
	//
}


//Functions
void Player::drawTo(sf::RenderWindow& window) {
	window.draw(player);
}

void Player::moveTo(sf::Vector2f distance) {
	player.move(distance);
}

void Player::setPlayerPos(sf::Vector2f newPos) {
	player.setPosition(newPos);
}

int Player::getX() {
	return player.getPosition().x;
}

int Player::getY() {
	return player.getPosition().y;
}

bool Player::collisionWithCoin(Coin* coin) {
	if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
		return true;
	}
	return false;
}

bool Player::collisionWithEnemy(Enemy* enemy) {
	if (player.getGlobalBounds().intersects(enemy->getGlobalBounds())) {
		return true;
	}
	return false;
}
