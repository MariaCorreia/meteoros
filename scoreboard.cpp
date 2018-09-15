
//this scoreboard method goes in Control. i'm putting it in a separate file to add it later.


//char score = '0';  //this is declared in the initialization. 
//this char starts at ascii value 0 and whenever a rocket explodes a meteor it's updated to score++

//this method should be called at the point in the main loop where it's drawing the rest of the entities.
void scoreboard(char score){ //draws the score and time spent

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text text(score, font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setPosition (10, 10);
	window->draw(text); //draws score

	sf::Time now = clock.getElapsedTime();
	text.setPosition (10, 30);
	text.setString(now.inSeconds()); //i'm actually not sure if it'll display correctly with a Time.inSeconds() type.
	window->draw(text); //redraws time elapsed underneath score

	
	
}