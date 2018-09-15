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



//-----------------------------------------------------------------------
int main(){
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(500, 500), "Meteoros");

	sf::Clock clock;
	sf::Time now = clock.getElapsedTime();
	GameController game = GameController(20, 5);
	game.initialize();
	while (window.isOpen()) {
		now = clock.restart(); //restarts clock every iteraction,stores time since last restart, aka, dt

		window.clear();
		Pause(16); //60 updates per second, aka 60fps

		game.gameLoop(window, now);

		
		window.display(); //plasters everything that has bem .draw()'ed into the screen
	}

	return 0;
}