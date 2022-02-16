/*
 * SingleRotor.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef SINGLEROTOR_H_
#define SINGLEROTOR_H_
#include "Drone.h"

class SingleRotor :virtual public Drone{
public:
	SingleRotor():Drone(),a(0.01),b(-0.1),c(-0.25){}
	virtual ~SingleRotor(){
		this->~Drone();
	}
	virtual string Print(){
		return "S";
	}

	virtual double getA()const{return a;}

	virtual double getB()const{return b;}

	virtual double getC()const{return c;}

private:
	double a,b,c;
};

#endif /* SINGLEROTOR_H_ */
