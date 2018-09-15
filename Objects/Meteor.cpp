#include "objects.h"

int startPosition;

Meteor::Meteor(){
	this->state = rand()%2? COMMON : FAST; //start meteor of the type specified
	radius = (rand() % 9) +2; //generate random radius between 2 and 10 pixels for size variability
	minRadius = radius;
	
	startPosition = (rand()%10); //generates one out of 5 starter positions
	target = sf::Vector2f(rand()%500, 500); //creates vector with random location on the bottom of the street as target
	setPosition((50*startPosition),(0)); //from random startPosition, x has possible values of 0 50 100 150 200 250 300 350 400 450
	
	explosionDuration = 0.0; //tracks the duration of the explosion
	explosionMaxDuration = 1; //when the rocket has been exploding for 1 second, the entire cycle restarts
	
	switch (state){
		case COMMON:
			speed = 150 * (2/radius);
			break;
		case FAST:
			speed = 200 * (2/radius);
			break;
			//CRASHING meteors aren't generated at construction.
		default:
			return;
	}
}

Meteor::~Meteor(){ //deletes meteors
	printf("meteor deleted\n"); 
}

void Meteor::randomize(){
	radius = 2+rand() % 9; //generate random radius between 2 and 10 pixels for size variability	
	minRadius = radius;
	startPosition = (rand()%10); //generates one out of 5 starter positions
	target = sf::Vector2f((rand()%500), 500); //creates vector with random location on the bottom of the street as target
	setPosition(50*startPosition,-50);

	explosionDuration = 0.0;
}

void Meteor::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	
	sf::CircleShape circle (radius); //defines the circle with its minimum radius
	circle.setOrigin(radius,radius); //set the origin of the object to it's exact center
	circle.setPosition (getPosition()); //so that scaling it expands it equally in all directions
	switch(state){
		case COMMON:
			circle.setFillColor(sf::Color(23,66,42,255));
			break;
		case FAST:
			circle.setFillColor(sf::Color::Red); //sf::Color::White could also work
			break;	
		case CRASHING:
			circle.setScale(radius/minRadius, radius/minRadius); //set the scale as the proportion between the current radius and minRadius
			circle.setFillColor(sf::Color::Transparent); 
			circle.setOutlineColor(sf::Color::White);
			circle.setOutlineThickness(minRadius/radius); //scale the outlineThickness by the INVERSE, so that it's size remain constant
			break;				
		default: 
			return;
	} 
	window.draw (circle);
}

void Meteor::run(sf::Time dt){
	switch(state){ //finite-state-machine responsible for directing the missile behavior
		case COMMON:
			fall(dt); //main activity of the meteor is to fall.
			break;
		case FAST:
			fall(dt); //common and fast have no difference in fall method for speed 
			break;
		case CRASHING:
			crash(dt);
		default:
			return;
	}
	
	return; 
}

// void Meteor::switchState(){ //purpose of this is for meteors that change behavior in the future
// return;
// }

void Meteor::fall(sf::Time dt){ //this function makes the meteor go down the screen
	
	sf::Vector2f v = target - getPosition(); //vector AB = B - A
	float modulo = sqrt((v.x*v.x) + (v.y*v.y)); //gets the magnitude or size of AB
	v = (v/modulo) * speed; //transforms v into an unit vector then multiplies by speed to correctly translate by the speed 
	move(v * dt.asSeconds()); //move comes from transformable, is equal to getPosition() + vector2f

	if(modulo < 2.0){ //if the distance from the target is smaller than 5, begins crashing
		state = CRASHING; 
	}
	
}

void Meteor::crash(sf::Time dt){ //similar to Rocket::explode
	radius +=(minRadius*1) * dt.asSeconds(); //increases to five times its original radius each second
	explosionDuration += dt.asSeconds(); 

	if(explosionDuration > explosionMaxDuration){
		randomize();
	}
}

float Meteor::getRadius(){return radius;}



