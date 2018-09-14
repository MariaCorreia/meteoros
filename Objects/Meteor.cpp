
#include "objects.h"

Meteor::Meteor(States state, float x, float y, float r){
	
	Color brown = sf::Color::Color (23,66,42,255); //defines brown color for use in draw 	
	
	this->state = state; //start meteor of the type specified

	setPosition(x,y); //sets sf::Transformable position from Entity to x,y
	radius = r;
}

Meteor::~Meteor(){ //deletes meteors
	printf("meteor deleted\n"); 
}

void Meteor::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	
	sf::CircleShape circle (radius); //defines the circle with its minimum radius
	circle.setOrigin(radius,radius); //set the origin of the object to it's exact center
	circle.setPosition (getPosition()); //so that scaling it expands it equally in all directions
	switch(state){
		case COMMON:
			circle.setFillColor(brown);
			break;
		case FAST:
			circle.setFillColor(sf::Color::Red); //sf::Color::White could also work
			
			break;										
		default: 
			return;
	} 
	window.draw (circle);
}

void Meteor::run(sf::Time){
	fall(); //main activity of the meteor is to fall.
	return; 
}

void Meteor::switchState(){ //purpose of this is for meteors that change behavior in the future
return;
}

void Meteor::fall(sf::Time){ //this function makes the meteor go down the screen
	
	//get current position
	//set next position according to dt and angle
	
}
