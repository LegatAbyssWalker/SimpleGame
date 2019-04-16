#include "Enemy.h"


//Constructors/Destructors
Enemy::Enemy(sf::Vector2f size) {
	enemy.setSize(size);
	enemy.setFillColor(sf::Color::Red);
}


Enemy::~Enemy() {
	//
}


//Functions
void Enemy::drawTo(sf::RenderWindow& window) {
	window.draw(enemy);
}


void Enemy::updateMovement(sf::Vector2f autoDistance) {
	enemy.move(autoDistance);
}

void Enemy::setEnemyPos(sf::Vector2f newPos) {
	enemy.setPosition(newPos);
}

sf::FloatRect Enemy::getGlobalBounds() {
	return enemy.getGlobalBounds();
}

int Enemy::getEnemyX() {
	return enemy.getPosition().x;
}

int Enemy::getEnemyY() {
	return enemy.getPosition().y;
}
