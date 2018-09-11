#ifndef HEADEROBJETOS
#define HEADEROBJETOS


#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		House(float, float, float, float); //width, height, x, y
		~House();
		virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
		virtual void run(sf::Time);
		void switchState();
};

#endif