#include "objects.h"

void Entity::draw(sf::RenderTarget &window, sf::RenderStates states) const{
	printf("Warning: Attempted drawing an empty Entity\n");
	return;
}

void Entity::run(sf::Time){
	printf("Warning: Attempted running an empty Entity\n");
	return;
}
