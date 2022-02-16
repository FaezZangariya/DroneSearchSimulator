/*
 * Hybrid.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef HYBRID_H_
#define HYBRID_H_
#include "SingleRotor.h"
#include "FixedWing.h"

class Hybrid :public SingleRotor,public FixedWing{
public:
	Hybrid():Drone(),a(0.01),b(-0.1),c(-0.25){}
	virtual ~Hybrid(){
		this->~Drone();
	}
	virtual string Print(){
		return "H";
	}

	double getA()const{return a;}

	double getB()const{return b;}

	double getC()const{return c;}

private:
	double a,b,c;
};

#endif /* HYBRID_H_ */
