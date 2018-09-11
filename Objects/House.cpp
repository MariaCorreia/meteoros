#include "objects.h"

House::House(float w, float h, float x, float y){
	state = INTACT; //start house in intact state

	setPosition(x,y); //sets sf::Transformable position from Entity to x,y
	width = w;
	height = h;
}

House::~House(){ //deconstructors may be useful in the future, will leave it here in preparation for it
	printf("House deleted\n"); 
}

void House::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	sf::RectangleShape rect (sf::Vector2f (width, height));
	rect.setPosition (getPosition()); //getPosition is returned as an sf::Vector2f, since entity inherits it from sf::Transformable
	switch(state){
		case INTACT: //House's color is defined based on it's state, for visibility
			rect.setFillColor(sf::Color(0, 255, 0));
			break;
		case DESTROYED:
			rect.setFillColor(sf::Color(255, 0, 0));
			break;
		default:
			break;
	}
	window.draw (rect);
}

void House::run(sf::Time){
	return; //house does nothing, therefore so does its run
}

void House::switchState(){ //testing function
	state = state==INTACT? DESTROYED : INTACT;
}
