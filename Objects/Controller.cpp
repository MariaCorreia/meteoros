#include "objects.h"

GameController::GameController(int maxMeteors, int startingHouses){
	this->maxMeteors = maxMeteors; //max meteors in screen at the same time
	this->startingHouses = startingHouses;
	this->currentMeteors = 0; //amount of meteors in screen


	totalTime = 0.0;
	kills = 0;
	timer = 0.0;
}

GameController::~GameController(){
	std::cout << "GameController deleted at time" << timer;
}

void GameController::initialize(){
	for (int i = 0; i < 100; ++i){
		meteors.push_back(Meteor());
	} //creates 100 random meteors

	for(int i = 0; i<startingHouses; i++){
		//house positions goes from 100 to 400. 300
		houses.push_back(House((i+1)*(400 / startingHouses+1), 470, 30, 30));
	} //creates the amount of starting houses

	rockets.push_back(Rocket(600,500, 5));
}

void GameController::handleInput(sf::RenderWindow &window){
	sf::Event event;
	while (window.pollEvent(event)){
		if ( (event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) &&
			(event.key.code == sf::Keyboard::Escape)))
			exit(0);

		// if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){}

		if((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)){
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			rockets[0].flyTo(sf::Vector2f(mousePos.x, mousePos.y));
		}
	}
}

void GameController::draw(sf::RenderWindow &window){
	for(int i = 0; i<currentMeteors; i++){
		window.draw(meteors[i]);
	}

	for(int h = 0; h<startingHouses; h++){
		window.draw(houses[h]);
	}

	window.draw(rockets[0]);

	scoreboard(window);
}

void GameController::update(sf::RenderWindow &window, sf::Time dt){
	timer += dt.asSeconds();
	totalTime += dt.asSeconds();
	for(int i = 0; i<currentMeteors; i++){
		meteors[i].run(dt);
	}
	for(int h = 0; h<startingHouses; h++){
		houses[h].run(dt);
	}
	rockets[0].run(dt);

	checkCollision();
}

void GameController::checkCollision(){
	for(int h = 0; h<startingHouses; h++){
		if(houses[h].isDestroyed()) continue; //if house is currently destroyed, do nothing
		
		for(int i = 0; i<currentMeteors; i++){
			if(houses[h].isColliding(&meteors[i], meteors[i].getRadius())){
				removeMeteor(i); //switches to a new meteor, analogous to deletion
			}
		}

		houses[h].isColliding(&rockets[0], rockets[0].getRadius());
	}

	for(int i = 0; i<currentMeteors; i++){
		if(rockets[0].isColliding(&meteors[i])){
			removeMeteor(i);
			kills++;
		}
	}
}

void GameController::removeMeteor(int i){
	Meteor m = meteors[i];
	for(int j = i+1; j<currentMeteors; j++){
		meteors[j-1] = meteors[j]; //sequentialy replaces the vector from the end
	}
	meteors[currentMeteors] = m;
	currentMeteors -= 1;
}

void GameController::spawnMeteor(){
	int replacement = currentMeteors+rand()%90; //decides which random meteor will replace this
	meteors[currentMeteors].randomize(); //randomizes current meteor
	std::swap(meteors[currentMeteors], meteors[replacement]); //switches its position with the new one
	currentMeteors += 1; //increments the amount of existing meteors
}

bool GameController::winCondition(){
	for(int i = 0; i<startingHouses; i++){
		if(!houses[i].isDestroyed()) return true; //more of a lose condition
	}//it checks whether there is at least one standing house, and when there isn't, the game closes
	return false;
}

void GameController::gameLoop(sf::RenderWindow& window, sf::Time dt){
	if(!winCondition()) exit(0);
	handleInput(window);
	manageMeteors();
	update(window, dt);
	draw(window);
}

void GameController::manageMeteors(){
	if(timer > maxMeteors - (maxMeteors -currentMeteors)){
		timer = rand()%5;
		spawnMeteor();
	}

	for(int i = 0; i<currentMeteors; i++){
		if(meteors[i].getPosition().y > 510){
			removeMeteor(i);
		}
		else if(meteors[i].getPosition().x > 550 || 
				meteors[i].getPosition().x < -50){
			removeMeteor(i);
		}
	}
}

void GameController::scoreboard(sf::RenderWindow& window){ //draws the score and time spent
	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text(std::to_string(kills), font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setPosition (10, 10);
	window.draw(text); //draws score

	text.setPosition (10, 40);
	text.setString(std::to_string((int)totalTime)); //i'm actually not sure if it'll display correctly with a Time.inSeconds() type.
	window.draw(text); //redraws time elapsed underneath score

	
	
}




//if (interval between meteors has passed)
			//meteor-vector.createMeteor();
		
		//meteor-vector.update(); //updates meteor position
		//rocket.update(); //updates rocket position
		
		//checkColision(); //checks collision between meteor and rocket, meteor and house, and deletes if necessary
		// updateScoreboard(); //updates passage of time on scoreboard