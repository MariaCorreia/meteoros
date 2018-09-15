#ifndef HEADEROBJETOS
#define HEADEROBJETOS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm> //std::clamp
#include <vector> //std::vector

#include <math.h> //sqrt, but may use sin or cos in the future
#include <time.h> //for time(NULL)
#include <stdlib.h> //for rand()

//Entity is the base object of all others in the game, useful for virtual functions
class Entity : public sf::Transformable, public sf::Drawable{ //transformable so we can store rotation, position and other things
	public: 													  //Drawable so that the object may be drawn with window.draw(entity)
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
};

class House : public Entity{
	enum States{INTACT, DESTROYED}; //enumerating states helps readability, better than if(state==0) etc
	States state;
	float width, height;

	private:
		void destroy();

	public:
		House(float, float, float, float); //x, y, width, height
		~House();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);

		bool isColliding(Entity*, float); //entity, its radius
		bool isDestroyed(); //returns true if currently DESTROYED
};

class Meteor : public Entity{
	enum States{COMMON, FAST, CRASHING}; //COMMON is standard straight-flying meteor. FAST is faster meteor.
	float radius;
	float minRadius;
	float speed; //amount of pixels crossed in a second
	float explosionDuration; //meteors explode upon impact like rockets
	float explosionMaxDuration; //no minRadius because it doesn't need to be reset.
	
	sf::Vector2f target;
	private:
		void fall(sf::Time);
		void explode(sf::Time);
		void crash(sf::Time);
	public:
		States state;
		Meteor(float, float, float,States); //x,y, radius, state
		Meteor();
		~Meteor();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
		void randomize();

		float getRadius();
};

class Rocket : public Entity{
	enum States{ARMED, FLYING, EXPLODING}; //ARMED means it's waiting to be launched, FLYING is going to target, EXPLODING increases radius
	States state;
	float minRadius; //rockets explode, so we need to store the smallest radius it can have so it will return to it
	float radius;
	float speed; //amount of pixels crossed in a second
	float explosionDuration;
	float explosionMaxDuration;
	sf::Vector2f target;

	private:
		void explode(sf::Time);
		void fly(sf::Time);
	public:
		Rocket(float, float, float); //minRadius, x, y
		~Rocket();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
		bool flyTo(sf::Vector2f); //flies to target

		bool isColliding(Meteor*);
		float getRadius();
};


class GameController{
	std::vector<Meteor> meteors;
	std::vector<House> houses;
	std::vector<Rocket> rockets;

	int kills; //total meteors destroyed
	float timer, totalTime; //timer used for spawning meteors
	int currentMeteors, maxMeteors, startingHouses;

	private:
		void handleInput(sf::RenderWindow&);
		void update(sf::RenderWindow&, sf::Time);
		void draw(sf::RenderWindow&);
		void checkCollision();
		void manageMeteors();
		void removeMeteor(int);
		void spawnMeteor();
		bool winCondition();
		void scoreboard(sf::RenderWindow&);
		// void vectorSwapping(std::vector, int);
	public:
	GameController(int, int); //maxMeteors and startingHouses
	~GameController();
	

	void initialize(); //loads up all base entities
	void gameLoop(sf::RenderWindow&, sf::Time);
};

#endif