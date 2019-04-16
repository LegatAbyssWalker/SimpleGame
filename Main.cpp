#include "SFML/Graphics.hpp"

#include "Player.h"
#include "Coin.h"
#include "Enemy.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>


const unsigned int screenWidth = 800;
const unsigned int screenHeight = 900;
std::string screenTitle = "SFML Window";

const float playerSpeed     = 0.1;
const float playerJumpSpeed = 0.5;
const float gravitySpeed    = 0.2;
const int   groundHeight    = 750;
bool        isJumping       = false;

const float enemySpeed      = 0.1;
int         randomEnemyMovement;

int playerScore = 0;
int playerLives = 3;

int borderCount;
int enemyCount;

int main() {
	//Player objects
	Player player({ 40, 40 });
	player.setPlayerPos({ screenWidth / 2, groundHeight });


	//Enemy objects
	std::vector<Enemy*> enemyVector;

	Enemy enemy1({ 25, 25 });
	Enemy enemy2({ 25, 25 });
	Enemy enemy3({ 25, 25 });

	enemyVector.push_back(&enemy1);
	enemyVector.push_back(&enemy2);
	enemyVector.push_back(&enemy3);


	enemy1.setEnemyPos({ screenWidth / 2, screenHeight / 2 });
	enemy2.setEnemyPos({ screenWidth / 2 - 64, 250 });
	enemy3.setEnemyPos({ screenWidth / 2 + 50, 150 });



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
	sf::RenderWindow window;
	sf::Event sfEvent;

	sf::Font gameFont;
	sf::Text playerScoreCounter, playerLivesCounter;

	std::ostringstream ssScore, ssLives;

	//Initionalize window
	window.create(sf::VideoMode(screenWidth, screenHeight), screenTitle);


	//Font and Text
	gameFont.loadFromFile("necessities/font/OptimusPrinceps.ttf");
	if (!gameFont.loadFromFile("necessities/font/OptimusPrinceps.ttf")) { return EXIT_FAILURE; }

	playerScoreCounter.setFont(gameFont);
	playerScoreCounter.setFillColor(sf::Color::Red);
	playerScoreCounter.setCharacterSize(30);
	playerScoreCounter.setPosition(screenWidth * 0, screenHeight * 0);
	ssScore << "Score: " << playerScore;
	playerScoreCounter.setString(ssScore.str());


	playerLivesCounter.setFont(gameFont);
	playerLivesCounter.setFillColor(sf::Color::Red);
	playerLivesCounter.setCharacterSize(30);
	playerLivesCounter.setPosition(screenWidth * 0, 35);
	ssLives << "Lives: " << playerLives;
	playerLivesCounter.setString(ssLives.str());


	//Main game loop
	while (window.isOpen()) {
		while (window.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyReleased:
				isJumping = false;
				break;
			}
		}

		//Player logic
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.moveTo({ 0, -playerJumpSpeed });
			isJumping = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { player.moveTo({ -playerSpeed, 0 }); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { player.moveTo({ playerSpeed, 0 }); }


		//Player loses life logic
		if (player.getY() <= 0) {
			borderCount++;
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			playerLivesCounter.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		if (player.getX() <= 0) {
			borderCount++;
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			playerLivesCounter.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		if (player.getX() >= screenWidth) {
			borderCount++;
			playerLives--;
			ssLives.str("");
			ssLives << "Lives: " << playerLives;
			playerLivesCounter.setString(ssLives.str());
			player.setPlayerPos({ screenWidth / 2, groundHeight });
		}

		for (int y = 0; y < enemyVector.size(); y++) {
			if (player.collisionWithEnemy(enemyVector[y])) {
				enemyCount++;
				playerLives--;
				ssLives.str("");
				ssLives << "Lives: " << playerLives;
				playerLivesCounter.setString(ssLives.str());
				player.setPlayerPos({ screenWidth / 2, groundHeight });
			}
		}



		//Player death / Player win
		if (playerLives <= 0 && playerScore != 3) {
			window.close();
			std::ofstream playerGameInformation("playerGameInformation.txt");
			playerGameInformation << "YOU LOSE!!\n";
			playerGameInformation << "Player Final Score: " << playerScore << '\n';
			playerGameInformation << "Player Lives Left: " << playerLives << '\n';
			playerGameInformation << "Death by Border: " << borderCount << '\n';
			playerGameInformation << "Death by Enemy: " << enemyCount << '\n';
			playerGameInformation.close();
		}

		if (playerScore >= 3 && playerLives != 0) {
			window.close();
			std::ofstream playerGameInformation("playerGameInformation.txt");
			playerGameInformation << "YOU WIN!!\n";
			playerGameInformation << "Player Final Score: " << playerScore << '\n';
			playerGameInformation << "Player Lives Left: " << playerLives << '\n';
			playerGameInformation << "Death by Border: " << borderCount << '\n';
			playerGameInformation << "Death by Enemy: " << enemyCount << '\n';
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
				playerScoreCounter.setString(ssScore.str());
			}
		}


		//Enemy AI movement
		/*---------------------------------------------------------------------------------------------------------------------*/
		srand(time(NULL));
		randomEnemyMovement = 1 + (rand() % 2);

		if (randomEnemyMovement == 1) { //LEFT
			enemy1.updateMovement({-enemySpeed, 0});
			enemy2.updateMovement({ -enemySpeed, 0 });
			enemy3.updateMovement({ -enemySpeed, 0 });

			if (enemy1.getEnemyX() <= 0) {
				enemy1.setEnemyPos({screenWidth/2, screenHeight/2});
			}

			if(enemy1.getEnemyX() >= screenWidth) {
				enemy1.setEnemyPos({ screenWidth / 2, screenHeight / 2 });
			}

			if (enemy2.getEnemyX() <= 0) {
				enemy2.setEnemyPos({ screenWidth / 2 - 64, 250 });
			}

			if (enemy2.getEnemyX() >= screenWidth) {
				enemy2.setEnemyPos({ screenWidth / 2 - 64, 250 });
			}

			if (enemy3.getEnemyX() <= 0) {
				enemy3.setEnemyPos({ screenWidth / 2 + 50, 150 });
			}

			if (enemy3.getEnemyX() >= screenWidth) {
				enemy3.setEnemyPos({ screenWidth / 2 + 50, 150 });
			}
		}
		
		if (randomEnemyMovement == 2) {//RIGHT
			enemy1.updateMovement({ enemySpeed, 0 });
			enemy2.updateMovement({ enemySpeed, 0 });
			enemy3.updateMovement({ enemySpeed, 0 });

			if (enemy1.getEnemyX() <= 0) {
				enemy1.setEnemyPos({ screenWidth / 2, screenHeight / 2 });
			}

			if (enemy1.getEnemyX() >= screenWidth) {
				enemy1.setEnemyPos({ screenWidth / 2, screenHeight / 2 });
			}

			if (enemy2.getEnemyX() <= 0) {
				enemy2.setEnemyPos({ screenWidth / 2 - 64, 250 });
			}

			if (enemy2.getEnemyX() >= screenWidth) {
				enemy2.setEnemyPos({ screenWidth / 2 - 64, 250 });
			}

			if (enemy3.getEnemyX() <= 0) {
				enemy3.setEnemyPos({ screenWidth / 2 + 50, 150 });
			}

			if (enemy3.getEnemyX() >= screenWidth) {
				enemy3.setEnemyPos({ screenWidth / 2 + 50, 150 });
			}
		}

		/*---------------------------------------------------------------------------------------------------------------------*/

		//Rendering to screen
		window.clear();

		//Render items
		player.drawTo(window);

		coin1.drawTo(window);
		coin2.drawTo(window);
		coin3.drawTo(window);

		window.draw(playerScoreCounter);
		window.draw(playerLivesCounter);

		enemy1.drawTo(window);
		enemy2.drawTo(window);
		enemy3.drawTo(window);

		window.display();
	}

	return EXIT_SUCCESS;
}
