//g++ SFML1.cpp -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
//libraries for compiling this

#include "Objects/objects.h"


//sprite and bitmap sf::Sprite
//scoring sf::Text
//ambient sound? sf::Sound

void Pause (int milliseconds) {
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = (milliseconds % 1000) * 1000000; //max of 999ms as pause
	nanosleep(&ts, NULL);
}


//-----------------------------------------------------------------------
Rocket rocket = Rocket(250, 450, 5);
void input(sf::RenderWindow &window){
	sf::Event event;
	while (window.pollEvent(event)){
			if ( (event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) &&
				(event.key.code == sf::Keyboard::Escape)))
				exit(0);

			if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){
			}

			if((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)){
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				rocket.flyTo(sf::Vector2f(mousePos.x, mousePos.y));
			}
		}
}
void show (sf::RenderWindow &window) { //that which will be drawn in the screen
	window.draw(rocket);
	//all objects, scores, etc
}

void update(sf::RenderWindow &window, sf::Time dt){
	rocket.run(dt);
	//.run() all objects on the screen
}

void checkColision(){
	
	//meteor-vector.getMeteorPositions(); 
	//rocket.getPositions();
	//house.getPositions();	

	//for every meteor in meteor-vector
		//if (rocket collides with meteor)
			//meteor-vector.delete(meteor index)
			//rocket.delete()
		
		//if (meteor collides with house) {
			//house.delete();
			//meteor-vector.delete(meteor index)
			//scoreboard++;
		//}
		
		
			
	
}

//-----------------------------------------------------------------------
int main() {
	sf::RenderWindow window(sf::VideoMode(500, 500), "Meteoros");

	//initialization
	
	//initializes meteor-vector
	//initializes houses
	//initializes rocket launcher
	
	sf::Clock clock;
	sf::Time now = clock.getElapsedTime();
	while (window.isOpen()) {
		now = clock.restart(); //restarts clock every iteraction,stores time since last restart, aka, dt

		window.clear();

		//if (interval between meteors has passed)
			//meteor-vector.createMeteor();
		
		//meteor-vector.update(); //updates meteor position
		//rocket.update(); //updates rocket position
		
		//checkColision(); //checks collision between meteor and rocket, meteor and house, and deletes if necessary
		// updateScoreboard(); //updates passage of time on scoreboard
		
		input(window);
		show (window);
		update(window, now);

		
		window.display(); //plasters everything that has bem .draw()'ed into the screen
		Pause(16); //60 updates per second, aka 60fps

	
	}

	return 0;
}