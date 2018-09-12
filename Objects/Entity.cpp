#include "objects.h"

void Entity::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	std::cerr << "Warning: Attempted drawing an empty Entity\n";
	return;
}

void Entity::run(sf::Time){
	std::cerr <<"Warning: Attempted running an empty Entity\n";
	return;
}
