#include "Game.h"

Game::Game() {
	score = 0;
	canLaunchBall = true;
	lifeCount = MAX_PLAYER_LIVES;
	player = Player();
	ball = Ball(sf::Vector2f(player.getRect().left + player.getRect().width, player.getRect().top), INIT_BALL_DIMENSION, sf::Vector2f(0, 0));
	frameTimer = sf::Clock();
	spawnTimer = sf::Clock();
	percentDistribution = std::uniform_real_distribution<float>(0, 1);

	font.loadFromFile(UI_FONT_FILE);
	scoreText = sf::Text();
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::White);
	scoreText.setCharacterSize(200);
	scoreText.setPosition(0, INIT_PLAYER_LOCATION.y + 100 - scoreText.getCharacterSize());

	lifeText = sf::Text();
	lifeText.setFont(font);
	lifeText.setColor(sf::Color::White);
	lifeText.setCharacterSize(50);
	lifeText.setString(std::to_string(lifeCount));
	lifeText.setPosition(0, INIT_PLAYER_LOCATION.y + 100 - scoreText.getCharacterSize());

	livesText = sf::Text();
	livesText.setFont(font);
	livesText.setColor(sf::Color::White);
	livesText.setCharacterSize(lifeText.getCharacterSize() / 2);
	livesText.setString("LIVES:");
	livesText.setPosition(0, INIT_PLAYER_LOCATION.y + 100 - scoreText.getCharacterSize());
}

Game::Game(sf::RenderWindow &window) {
	score = 0;
	level = 0;
	levelMultiplier = 1;
	comboMultiplier = 1;
	brickColor = 0;
	canLaunchBall = true;
	lifeCount = MAX_PLAYER_LIVES;
	player = Player();
	ball = Ball(sf::Vector2f(player.getRect().left + player.getRect().width, player.getRect().top), INIT_BALL_DIMENSION, sf::Vector2f(0, 0));
	frameTimer = sf::Clock();
	spawnTimer = sf::Clock();
	percentDistribution = std::uniform_real_distribution<float>(0, 1);

	std::ifstream saveFile;
	saveFile.open("hiscore.txt");
	if (saveFile.is_open()) {
		std::string line;
		std::getline(saveFile, line);
		hiScore = std::stoi(line);
	}
	else
		hiScore = 0;
	saveFile.close();
	soundManager = SoundManager(5);
	soundManager.setSoundBuffer(SoundID::Bounce, "Sounds/bounce.wav");
	soundManager.setSoundBuffer(SoundID::BallDeath, "Sounds/balldeath.wav");
	soundManager.setSoundBuffer(SoundID::BrickBreak, "Sounds/enemyhit.wav");
	soundManager.setSoundBuffer(SoundID::LaserFire, "Sounds/laser.wav");
	soundManager.setSoundBuffer(SoundID::LevelUp, "Sounds/levelup.wav");

	font.loadFromFile(UI_FONT_FILE);
	scoreText = sf::Text();
	scoreText.setFont(font);
	scoreText.setColor(sf::Color::White);
	scoreText.setCharacterSize(200);
	scoreText.setPosition(0, window.getSize().y - scoreText.getCharacterSize());

	levelMultiplierText = sf::Text();
	levelMultiplierText.setFont(font);
	levelMultiplierText.setColor(sf::Color::White);
	levelMultiplierText.setCharacterSize(250);
	levelMultiplierText.setPosition(0, window.getSize().y - levelMultiplierText.getCharacterSize());

	lifeText = sf::Text();
	lifeText.setFont(font);
	lifeText.setColor(sf::Color::White);
	lifeText.setCharacterSize(100);
	lifeText.setString(std::to_string(lifeCount));
	lifeText.setPosition(window.getSize().x - lifeText.getLocalBounds().width, window.getSize().y - lifeText.getCharacterSize());

	livesText = sf::Text();
	livesText.setFont(font);
	livesText.setColor(sf::Color::White);
	livesText.setCharacterSize(lifeText.getCharacterSize() / 2);
	livesText.setString("LIVES:");
	livesText.setPosition(window.getSize().x - lifeText.getGlobalBounds().width - livesText.getGlobalBounds().width, window.getSize().y - livesText.getCharacterSize());

	gameOverText = sf::Text();
	gameOverText.setFont(font);
	gameOverText.setColor(sf::Color::White);
	gameOverText.setCharacterSize(200);
	gameOverText.setString("GAME OVER\nPress Space\nto Restart");
	gameOverText.setPosition(0, 0 - gameOverText.getGlobalBounds().height / 2);

	hiScoreText = sf::Text();
	hiScoreText.setFont(font);
	hiScoreText.setColor(sf::Color::White);
	hiScoreText.setCharacterSize(200);
	hiScoreText.setString("HISCORE: " + std::to_string(hiScore));
	hiScoreText.setPosition(0, gameOverText.getGlobalBounds().height / 2 + 100);

	comboTexts = TempTextManager(font, 1.0f, 40, sf::Color::White, sf::Vector2f(0, -20));
	levelUpTexts = TempTextManager(font, 3.0f, 300, sf::Color::White, sf::Vector2f(0, -10));

	colorWheel[0] = sf::Color::Red;
	colorWheel[1] = sf::Color::Magenta;
	colorWheel[2] = sf::Color::Blue;
	colorWheel[3] = sf::Color::Green;
	colorWheel[4] = sf::Color::Yellow;
	colorWheel[5] = sf::Color(255, 127, 0);
}

Game::~Game() { }

void Game::brickCollision(sf::Rect<float> intersection, sf::Rect<float> other) {
	soundManager.playSound(SoundID::BrickBreak);
	if (other.top == intersection.top && ball.getVelocity().y > 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(ball.getRect().left, other.top - ball.getRect().height, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceY();
	}
	else if ((other.top + other.height) == (intersection.top + intersection.height) && ball.getVelocity().y < 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(ball.getRect().left, other.top + other.height, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceY();
	}
	else if (other.left == intersection.left && ball.getVelocity().x > 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(other.left - ball.getRect().width, ball.getRect().top, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceX();
	}
	else if ((other.left + other.width) == (intersection.left + intersection.width) && ball.getVelocity().x < 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(other.left + other.width, ball.getRect().top, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceX();
	}
}

void Game::playerCollision(sf::Rect<float> intersection, sf::Rect<float> other) {
	soundManager.playSound(SoundID::Bounce);
	if (other.top == intersection.top && ball.getVelocity().y > 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(ball.getRect().left, other.top - ball.getRect().height, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceY();
		turnBall(ball.getRect().left + ball.getRect().width / 2, other.left + other.width / 2);
	}
	else if ((other.top + other.height) == (intersection.top + intersection.height) && ball.getVelocity().y < 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(ball.getRect().left, other.top + other.height, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceY();
		turnBall(ball.getRect().left + ball.getRect().width / 2, other.left + other.width / 2);
	}
	else if (other.left == intersection.left && ball.getVelocity().x > 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(other.left - ball.getRect().width, ball.getRect().top, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceX();
	}
	else if ((other.left + other.width) == (intersection.left + intersection.width) && ball.getVelocity().x < 0) {
		sf::Rect<float> newPosition = sf::Rect<float>(other.left + other.width, ball.getRect().top, ball.getRect().width, ball.getRect().height);
		ball.setRect(newPosition);
		ball.bounceX();
	}
}

void Game::turnBall(float ballCenterX, float playerCenterX) {
	float difference = ballCenterX - playerCenterX;
	ball.changeVelocity(sf::Vector2f(difference * BALL_TURN_SPEED, 0));
}

void Game::saveHiScore() {
	std::ofstream saveFile;
	saveFile.open("hiscore.txt");
	hiScore = score;
	saveFile << hiScore;
	saveFile.close();
	hiScoreText.setString("HISCORE: " + std::to_string(hiScore));
}

void Game::levelUp() {
	soundManager.playSound(SoundID::LevelUp);
	level++;
	lifeCount++;
	levelMultiplier = std::pow(2, level);
	levelUpTexts.addText("LEVEL UP" , sf::Vector2f(0, 0 - levelUpTexts.sampleText("A").getGlobalBounds().height / 2));
	lasers.clear();
	respawn();
}

void Game::respawn() {
	ball.isDead = false;
	canLaunchBall = true;
	comboMultiplier = 1;
	ball.setRect(sf::Rect<float>(sf::Vector2f(player.getRect().left + player.getRect().width / 2, player.getRect().top - INIT_BALL_DIMENSION.y), INIT_BALL_DIMENSION));
	ball.changeVelocity(-ball.getVelocity());
}

void Game::restart(sf::RenderWindow &window) {
	lifeCount = MAX_PLAYER_LIVES;
	score = 0;
	level = 0;
	comboMultiplier = 1;
	brickColor = 0;
	bricks.clear();
	for (int i = 0; i < MAX_BRICK_ROWS / 2; i++) {
		pushBricksDown();
		spawnBricks(window);
	}
}

void Game::spawnBricks(sf::RenderWindow &window) {
	spawnTimer.restart();
	int numBricks = window.getSize().x / INIT_BRICK_DIMENSION.x;
	for (int i = 0; i < numBricks; i++) {
		if (percentDistribution(randomEngine) < INIT_BRICK_SPAWN_CHANCE) {
			Brick brick = Brick(sf::Vector2f(INIT_BRICK_DIMENSION.x * i, 0), INIT_BRICK_DIMENSION, colorWheel[brickColor]);
			bricks.push_back(brick);
		}
	}
	brickColor++;
	if (brickColor > 5)
		brickColor = 0;
}

void Game::pushBricksDown() {
	for (int i = 0; i < bricks.size(); i++) {
		sf::Rect<float> newRect = bricks[i].getRect();
		newRect.top += INIT_BRICK_DIMENSION.y;
		bricks[i].setRect(newRect);
	}
}

void Game::fireLasers(sf::RenderWindow &window) {
	soundManager.playSound(SoundID::LaserFire);
	int numLasers = window.getSize().x / INIT_BRICK_DIMENSION.x;
	for (int i = 0; i < numLasers; i++) {
		sf::Vector2f laser = sf::Vector2f(INIT_BRICK_DIMENSION.x * i + INIT_BRICK_DIMENSION.x / 2, window.getSize().y);
		lasers.push_back(laser);
	}
}

void Game::drawLaser(sf::RenderWindow &window, sf::Vector2f laser) {
	sf::VertexArray verts = sf::VertexArray(sf::TrianglesStrip, 5);
	
	verts[0].position = laser;
	verts[1].position = laser + sf::Vector2f(INIT_BRICK_DIMENSION.x / 2, INIT_BRICK_DIMENSION.y);
	verts[2].position = laser + sf::Vector2f(-INIT_BRICK_DIMENSION.x / 2, INIT_BRICK_DIMENSION.y);
	verts[3].position = sf::Vector2f(verts[1].position.x, window.getSize().y);
	verts[4].position = sf::Vector2f(verts[2].position.x, window.getSize().y);

	verts[0].color = sf::Color(255, 20, 147, 127);
	verts[1].color = sf::Color(255, 20, 147, 127);
	verts[2].color = sf::Color(255, 20, 147, 127);
	verts[3].color = sf::Color(255, 20, 147, 127);
	verts[4].color = sf::Color(255, 20, 147, 127);

	window.draw(verts);
}

void Game::start() { }

void Game::update(sf::RenderWindow &window) {
	sf::Event event; // singleton, tracks current event
	float timeSinceLastFrameInSeconds = frameTimer.restart().asSeconds();
	
	// inputs
	while (window.pollEvent(event)) {
		switch (event.type) {
			case sf::Event::Closed: // window close
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) {
					if (canLaunchBall && lifeCount > 0) {
						canLaunchBall = false;
						ball.changeVelocity(sf::Vector2f(INIT_BALL_VELOCITY.x, INIT_BALL_VELOCITY.y * std::pow(1.1f, level)));
					}
					else if (lifeCount < 1) {
						restart(window);
					}
				}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player.moveLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player.moveRight();

	// logic for spawning more bricks
	if (bricks.size() == 0) {
		levelUp();
		for (int i = 0; i < MAX_BRICK_ROWS / 2; i++) {
			pushBricksDown();
			spawnBricks(window);
		}
	}
	else {
		int numBrickRows = 0;
		for (int i = 0; i < bricks.size(); i++) {
			int row = bricks[i].getRect().top / INIT_BRICK_DIMENSION.y;
			if (numBrickRows < row + 1) {
				numBrickRows = row + 1;
			}
		}
		if (numBrickRows < MAX_BRICK_ROWS && spawnTimer.getElapsedTime().asSeconds() > INIT_BRICK_WAVE_TIME * std::pow(.9f, level)) {
			pushBricksDown();
			spawnBricks(window);
		}
	}

	// update individual objects
	for (int i = 0; i < bricks.size(); i++) {
		bricks[i].update(window);
	}
	for (int i = 0; i < lasers.size(); i++) {
		lasers[i].y -= LASER_SPEED * timeSinceLastFrameInSeconds;
	}
	player.update(window, timeSinceLastFrameInSeconds);
	ball.update(window, timeSinceLastFrameInSeconds);
	comboTexts.update(window, timeSinceLastFrameInSeconds);
	levelUpTexts.update(window, timeSinceLastFrameInSeconds);
	if (ball.hitTop) {
		fireLasers(window);
		ball.hitTop = false;
	}
	if (ball.isDead) {
		soundManager.playSound(SoundID::BallDeath);
		lifeCount--;
		respawn();
		if (lifeCount < 1 && score > hiScore)
			saveHiScore();
	}

	// ball is ready to launch
	if (canLaunchBall) {
		ball.setRect(sf::Rect<float>(sf::Vector2f(player.getRect().left + player.getRect().width / 2, player.getRect().top - INIT_BALL_DIMENSION.y), INIT_BALL_DIMENSION));
	}

	//check collisions
	sf::Rect<float> intersection;
	sf::Rect<float> other = player.getRect();
	if (other.intersects(ball.getRect(), intersection)) {// ball collides with player
		playerCollision(intersection, other);
		comboMultiplier = 1; // reset multiplier
	}
	else {
		for (int i = 0; i < bricks.size(); i++) { // check if ball collides with a brick
			other = bricks[i].getRect();
			if (bricks[i].isDying == false && other.intersects(ball.getRect(), intersection)) {
				brickCollision(intersection, other);
				score += bricks[i].getValue() * comboMultiplier * levelMultiplier;
				comboTexts.addText("x" + std::to_string(comboMultiplier), sf::Vector2f(bricks[i].getRect().left, bricks[i].getRect().top));
				comboMultiplier++;
				bricks[i].hit();
			}
		}
	}
	// laser hits brick
	std::vector<int> toBeRemoved;
	for (int j = 0; j < lasers.size(); j++) {
		if (lasers[j].y < 0) {
			toBeRemoved.push_back(j);
			continue;
		}
		for (int i = 0; i < bricks.size(); i++)
			if (bricks[i].getRect().contains(lasers[j])) {
				score += bricks[i].getValue() * levelMultiplier;
				bricks[i].hit();
				toBeRemoved.push_back(j);
			}
	}
	// remove dead lasers
	if (!toBeRemoved.empty()) {
		for (int i = toBeRemoved.size() - 1; i > -1; i--) {
			lasers.erase(lasers.begin() + toBeRemoved[i]);
		}
	}

	// remove dead bricks
	toBeRemoved.clear();
	for (int i = 0; i < bricks.size(); i++) {
		if (bricks[i].isDead) {
			toBeRemoved.push_back(i);
		}
	}
	if (!toBeRemoved.empty()) {
		for (int i = toBeRemoved.size() - 1; i > -1; i--) {
			bricks.erase(bricks.begin() + toBeRemoved[i]);
		}
	}

	window.clear();

	draw(window);

	window.display();
}

void Game::draw(sf::RenderWindow &window) {
	for each (sf::Vector2f laser in lasers) {
		drawLaser(window, laser);
	}
	scoreText.setString(std::to_string(score));
	window.draw(scoreText);
	levelMultiplierText.setString(std::to_string(levelMultiplier) + "x");
	levelMultiplierText.setPosition(scoreText.getGlobalBounds().width + 20, window.getSize().y - levelMultiplierText.getCharacterSize());
	window.draw(levelMultiplierText);

	lifeText.setString(std::to_string(lifeCount));
	lifeText.setPosition(window.getSize().x - lifeText.getLocalBounds().width, window.getSize().y - lifeText.getCharacterSize());
	window.draw(lifeText);
	window.draw(livesText);

	for each (Brick brick in bricks) {
		brick.draw(window);
	}
	comboTexts.draw(window);
	levelUpTexts.draw(window);
	player.draw(window);
	ball.draw(window);

	if (lifeCount < 1) {
		window.draw(gameOverText);
		window.draw(hiScoreText);
	}
}