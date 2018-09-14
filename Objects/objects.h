#ifndef HEADEROBJETOS
#define HEADEROBJETOS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

//Entity is the base object of all others in the game, useful for virtual functions
class Entity : public sf::Transformable, public sf::Drawable{ //transformable so we can store rotation, position and other things
	public: 													  //Drawable so that the object may be drawn with window.draw(entity)
		// Entity();
		// ~Entity();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
};

class House : public Entity{
	enum States{INTACT, DESTROYED}; //enumerating states helps readability, better than if(state==0) etc
	States state;
	float width, height;

	public:
		House(float, float, float, float); //x, y, width, height
		~House();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
		void switchState();
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
		void flyTo(sf::Vector2f); //flies to target	
};

class Meteor : public Entity{
	enum States{COMMON, FAST}; //COMMON is standard straight-flying meteor. FAST is faster meteor.
	States state;
	float radius;
	float angle;
	float speed; //amount of pixels crossed in a second
	float x, y; //current position on screen
	
	private:
		void fall(sf::Time);
	public:
		Meteor(States, float, float, float); //state, x, y, radius
		~Meteor();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
};

#endif