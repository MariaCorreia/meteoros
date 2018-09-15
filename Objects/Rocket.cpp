#include "objects.h"

Rocket::Rocket(float x, float y, float r){ //not quite sure on these arguments, yet. May want more things on constructors for testing.
	state = ARMED; //rocket starts loaded

	setPosition(x,y); //sets sf::Transformable position from Entity to x,y
	speed = 200.0; //moves 200 pixels per second
	target = sf::Vector2f(0,0); //initialize target to 0
	minRadius = r;
	radius = minRadius;
	explosionDuration = 0.0; //tracks the duration of the explosion
	explosionMaxDuration = 1.5; //when the rocket has been exploding for 1.5 seconds, the entire cycle restarts
} //Good to have a variable for this should we want to implement any powerups.

Rocket::~Rocket(){ //deconstructors may be useful in the future, will leave it here in preparation for it
	std::cout << "Rocket deleted\n"; 
}

void Rocket::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	if(state == ARMED) return; //if the rocket is loaded, it's not drawn
	sf::CircleShape circle (minRadius); //defines the circle with its minimun radius
	circle.setOrigin(minRadius,minRadius); //set the origin of the object to it's exact center
	circle.setPosition (getPosition()); //so that scaling it expands it equally in all directions
	switch(state){
		case FLYING:
			circle.setFillColor(sf::Color::Yellow);
			break;
		case EXPLODING:
			circle.setScale(radius/minRadius, radius/minRadius); //set the scale as the proportion between the current radius and minRadius
			circle.setFillColor(sf::Color::Transparent); //sf::Color::White could also work
			circle.setOutlineColor(sf::Color::Yellow);
			circle.setOutlineThickness(minRadius/radius); //scale the outlineThickness by the INVERSE, so that it's size remain constant
			break;										 //as the explosion grows. It's better aesthetically.
		default: //removes a warning, even though state==ARMED will never reach this
			return;
	}
	window.draw (circle);
}

void Rocket::run(sf::Time dt){
	switch(state){ //finite-state-machine responsible for directing the missile behavior
		case FLYING:
			fly(dt);
			break;
		case EXPLODING:
			explode(dt);
			break;
		default:
			return;
	}
}

bool Rocket::flyTo(sf::Vector2f t){ //receives a target and sends the rocket on its merry way
	if(state != ARMED)return false; //returns false if unable to launch
	setPosition(250,430);
	target = t;
	state = FLYING;
	return true; //return true if correctly launched
}

void Rocket::fly(sf::Time dt){
	sf::Vector2f v = target - getPosition(); //vector AB = B - A
	float modulo = sqrt((v.x*v.x) + (v.y*v.y)); //gets the magnitude or size of AB
	v = (v/modulo) * speed; //transforms v into an unit vector then multiplies by speed to correctly translate by the speed 
	move(v * dt.asSeconds()); //move comes from transformable, is equal to getPosition() + vector2f

	if(modulo < 2.0){ //if the distance from the target is smaller than 5, begins exploding
		state = EXPLODING;
	}
}

void Rocket::explode(sf::Time dt){
	radius +=(minRadius*5) * dt.asSeconds(); //increases to five times its original radius each second
	explosionDuration += dt.asSeconds(); //5 could be replaced for another variable, so that the explosion expands faster when powered up

	if(explosionDuration > explosionMaxDuration){
		state = ARMED; //Has finished exploding, restart its cycle once more
		setPosition(600,500); //also set its position back to the middle. May want a better way of keeping track of these values.
		radius = minRadius; //restarts the radius proportions
		explosionDuration = 0.0; //restarts the timer
	}
}

bool Rocket::isColliding(Meteor *m){
	sf::Vector2f v = m->getPosition()-getPosition();
	float distance = sqrt((v.x*v.x) + (v.y*v.y));

	if(distance < getRadius() + m->getRadius()) return true;
	return false;
}

float Rocket::getRadius(){return radius;}