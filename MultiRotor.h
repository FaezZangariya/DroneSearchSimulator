/*
 * MultiRotor.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef MULTIROTOR_H_
#define MULTIROTOR_H_
#include "Drone.h"

class MultiRotor :public Drone{
public:
	MultiRotor():Drone(),a(0.05),b(0.1),c(0){}
	virtual ~MultiRotor(){
		this->~Drone();
	}
	virtual string Print(){
		return "M";
	}

	double getA()const{return a;}

	double getB()const{return b;}

	double getC()const{return c;}

private:
	double a,b,c;
};

#endif /* MULTIROTOR_H_ */
