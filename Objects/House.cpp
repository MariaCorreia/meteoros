#include "objects.h"

House::House(float x, float y, float w, float h){
	state = INTACT; //start house in intact state

	setPosition(x,y); //sets sf::Transformable position from Entity to x,y
	width = w;
	height = h;
}

House::~House(){ //deconstructors may be useful in the future, will leave it here in preparation for it
	std::cout << "House deleted\n"; 
}

void House::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	sf::RectangleShape rect (sf::Vector2f (width, height));
	rect.setOrigin(width/2, height/2); //so that the house is drawn centralized in its transform position
	rect.setPosition (getPosition()); //getPosition is returned as an sf::Vector2f, since entity inherits it from sf::Transformable
	switch(state){
		case INTACT: //House's color is defined based on it's state, for visibility
			rect.setFillColor(sf::Color::Green);
			break;
		case DESTROYED:
			rect.setFillColor(sf::Color::Red);
			break;
		default:
			break;
	}
	window.draw (rect);
}

void House::run(sf::Time dt){
	return; //house does nothing, therefore so does its run
}

void House::destroy(){
	state = DESTROYED;
}

bool House::isColliding(Entity* a, float r){ //entity that will collide, its radius
	float closestx = std::clamp(a->getPosition().x, getPosition().x-width/2, getPosition().x + width/2); //finds the closest point to the sphere
	float closesty = std::clamp(a->getPosition().y, getPosition().y-height/2, getPosition().y + height/2);//in the rectangle

	sf::Vector2f v = sf::Vector2f(closestx, closesty);
	v = a->getPosition() - v; //vector from the closest point to the center of the circle
	float distanceToCircle = sqrt((v.x*v.x) + (v.y*v.y)); //gets the length of this vector

	if(distanceToCircle < r) {
		destroy();
		return true;
	}
	return false;
}


bool House::isDestroyed(){return state==DESTROYED? 1 : 0;}