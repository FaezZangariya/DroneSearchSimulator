/*
 * FixedWing.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef FIXEDWING_H_
#define FIXEDWING_H_
#include "Drone.h"

class FixedWing :virtual public Drone{
public:
	FixedWing():Drone(),a(0.25),b(1),c(1){}
	virtual ~FixedWing(){
		this->~Drone();
	}
	virtual string Print(){
		return "W";
	}

	virtual double getA()const{return a;}

	virtual double getB()const{return b;}

	virtual double getC()const{return c;}

private:
	double a,b,c;
};

#endif /* FIXEDWING_H_ */
