#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Coin.h"

#include <sstream>
#include <iostream>
#include <fstream>

const unsigned int screenWidth = 800;
const unsigned int screenHeight = 900;
std::string screenTitle = "SFML Window";

const float playerSpeed = 0.1;
const float playerJumpSpeed = 0.5;
const int groundHeight = 750;
const float gravitySpeed = 0.2;
bool isJumping = false;

int playerLives = 3;

int main() {
	//Player objects
	Player player({ 40, 40 });
	player.setPlayerPos({ screenWidth / 2, groundHeight });


	//Coin objects
	std::vector<Coin*> coinVector;

	Coin coin1({ 20, 20 });
	Coin coin2({ 20, 20 });
	Coin coin3({ 20, 20 });

	coinVector.push_back(&coin1);
	coinVector.push_back(&coin2);
	coinVector.push_back(&coin3);

	coin1.setCoinPos({ 100, 100 });
	coin2.setCoinPos({ 200, 200 });
	coin3.setCoinPos({ 300, 300 });


	//Variables
	int playerScore = 0;

	sf::RenderWindow window;
	sf::Event sfEvent;

	sf::Font gameFont;
	sf::Text gameScore, gameLives;

	std::ostringstream ssScore, ssLives;

	//Initionalize window
	window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);


	//Text/Font 
	gameFont.loadFromFile("necessities/font/OptimusPrinceps.ttf");
	if (!gameFont.loadFromFile("necessities/font/OptimusPrinceps.ttf")) { EXIT_FAILURE; }

	gameScore.setFont(gameFont);
	gameScore.setCharacterSize(30);
	gameScore.setPosition(screenWidth * 0, screenHeight * 0);
	gameScore.setFillColor(sf::Color::Red);
	ssScore << "Score: " << playerScore;
	gameScore.setString(ssScore.str());

	gameLives.setFont(gameFont);
	gameLives.setCharacterSize(30);
	gameLives.setPosition(screenWidth * 0, 31);
	gameLives.setFillColor(sf::Color::Red);
	ssLives << "Lives: " << playerLives;
	gameLives.setString(ssLives.str());

	//Main game loop
	while (window.isOpen()) {
		while (window.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				isJumping = false;
			}
		}
		//Player logic
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.moveTo({ 0, -playerJumpSpeed });
			isJumping = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player.moveTo({ -playerSpeed, 0 }); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player.moveTo({ playerSpeed, 0 }); }


		//Player bounds
		if (player.getY() + 20 <= 0) {
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			gameLives.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		if (player.getX() <= 0) {
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			gameLives.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		if (player.getX() >= 800) {
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			gameLives.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		//RESET PLAYER POSITION BUTTONS **ADMIN ONLY**
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			player.setPlayerPos({ screenWidth / 2, screenHeight / 2 });
		}

		//Player end screen if lives are 0
		if (playerLives <= 0) {
			window.close();
			std::cout << "Final Score: " << playerScore << '\n';
			std::ofstream playerGameInformation("playerGameInformation.txt");

			playerGameInformation << "Player Final Score: " << playerScore << '\n';
			playerGameInformation.close();
		}


		//Gravity logic
		if (player.getY() < groundHeight && isJumping == false) {
			player.moveTo({ 0, gravitySpeed });
		}


		//Coin logic
		for (int x = 0; x < coinVector.size(); x++) {
			if (player.collisionWithCoin(coinVector[x])) {
				coinVector[x]->setCoinPos({ 10000, 10000 });
				playerScore++;
				ssScore.str("");
				ssScore << "Score: " << playerScore;
				gameScore.setString(ssScore.str());
			}
		}

		//Rendering to window
		window.clear();

		//Render items
		player.drawTo(window);
		coin1.drawTo(window);
		coin2.drawTo(window);
		coin3.drawTo(window);

		window.draw(gameScore);
		window.draw(gameLives);

		window.display();
	}

	return EXIT_SUCCESS;
}