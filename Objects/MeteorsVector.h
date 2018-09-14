
#include "objects.h"

//vector is not an entity and doesn't draw or run

Meteor[] meteorList;
	
	
MeteorsVector::MeteorsVector(){ 

	meteorList = Meteor[50]; //max of 50 meteors on screen

}

MeteorsVector::createMeteor(States state){ //creator randomly assigns values for meteor's creator parameters
	
	//States state,  float x, float y, float r
	
	//if state=COMMON{
	
	//generate random radius between 2 and 10 pixels for size variability
	
	//generate initial x (pick randomly from a number of defined starter positions available) and initial y (always 0)
	//define angle of fall depending on which starter position was picked
	
	//meteorList[first available spot] = Meteor::Meteor(state, x, y, r);
	
	//}
}

MeteorsVector::destroy(int index){
	
	meteorList[]::~Meteor();
}
