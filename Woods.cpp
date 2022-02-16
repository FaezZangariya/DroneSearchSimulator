#include "Woods.h"

using namespace std;

Woods::~Woods(){
	for(int i=0 ; i<poscount ; i++){
		delete positions[i];
	}
	delete positions;
	delete globalBest;
	delete target;
	delete this;
}

int Woods::foundPos(double x,double y) const{
	for(int i=0 ; i<poscount ; i++){
		if(positions[i]->getX()==x && positions[i]->getY()==y)
			return i;
	}
	return -1;
}


int Woods::operator ()(double x,double y){
	if(foundPos(x,y)!=-1)
		return positions[foundPos(x,y)]->getDC();
	return 0;
}
