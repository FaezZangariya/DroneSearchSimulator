#ifndef Drone_H
#define Drone_H
#include <iostream>
#include <sstream>
#include "WPosition.h"
using namespace std;

class Drone{
public:
	Drone():id(0),pos(new WPosition()),personalBest(new WPosition()),speed(new WPosition()),a(1),b(1),c(1){}

	Drone(const Drone& d){
		this->id=d.id;
		this->pos=d.pos;
		this->personalBest=d.personalBest;
		this->speed=d.speed;
		this->a=a;
		this->b=b;
		this->c=c;
	}

	virtual ~Drone(){
		delete pos;
		delete personalBest;
		delete speed;
		delete this;
	}

	void setId(int identity){id=identity;}

	void setPosition(WPosition& position){*pos=position;}

	WPosition* getPos(){return pos;}

	WPosition* getPersonal(){return personalBest;}

	WPosition* getSpeed(){return speed;}

	int getId() const{return id;}

	void setPersonal(WPosition& position){*personalBest=position;}

	virtual string Print(){
		return NULL;
	}

	virtual double getA()const{return a;}

	virtual double getB()const{return b;}

	virtual double getC()const{return c;}

	ostream& operator<<(ostream& os){
		os << Print() << getPos()->getX() << getPos()->getY() <<endl;
		return os;
	}

	string PrintDrone(){
		ostringstream x,y;
		x<<getPos()->getX();
		y<<getPos()->getY();
		string out=string();
		out+=Print();
		out+=" ";
		out+=x.str();
		out+=" ";
		out+=y.str();
		out+='\n';
		return out;
	}

	bool operator <(const Drone& d) {
		return getId() < d.getId();
	}

	bool operator ==(const Drone& d) {
		return getId()==d.getId();
	}



private:
	int id;
	WPosition* pos;
	WPosition* personalBest;
	WPosition* speed;
	int a,b,c;
};




#endif /* Drone_H */
