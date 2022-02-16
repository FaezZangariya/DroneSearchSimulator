#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <math.h>
#include <ctime>
#include <sstream>
using namespace std;

#include "Woods.h"
#include "Hybrid.h"
#include "MultiRotor.h"


void moveDrone(Drone* d, Woods& w,double xleftL,double xrightL,double yleftL,double yrightL){
	double r1,r2,x,y,k,l;
	r1=(((double)rand())/RAND_MAX);
	r2=(((double)rand())/RAND_MAX);
	double xdiffr1=d->getPersonal()->getX() - d->getPos()->getX();
	double xdiffr2=w.getglobal()->getPos()->getX()-d->getPos()->getX();
	double ydiffr1=d->getPersonal()->getY() - d->getPos()->getY();
	double ydiffr2=w.getglobal()->getPos()->getY()-d->getPos()->getY();
	k=d->getA()*d->getSpeed()->getX()+d->getB()*r1*(xdiffr1)+d->getC()*r2*(xdiffr2);   //new x cord for speed
	l=d->getA()*d->getSpeed()->getY()+d->getB()*r1*(ydiffr1)+d->getC()*r2*(ydiffr2);   //new y cord for speed
	x=k+d->getPos()->getX();   //new x cord for position
	y=l+d->getPos()->getY();   //new y cord for position
	d->getSpeed()->setX(k);	   //update x cord for speed
	d->getSpeed()->setY(l);    //update y cord for speed
	if(x<xleftL)
		x=0;
	if(x>xrightL)
		x=72;
	if(y<yleftL)
		y=0;
	if(y>yrightL)
		y=42;
	d->getPos()->operator --();


	//if position has already been created let current drone's position point at it
	if(w.foundPos(x,y)!=-1){
		d->setPosition(w.getPos(w.foundPos(x,y)));
		d->getPos()->operator ++();
	}

	//if position has not been created then create a new position
	else if(w.foundPos(x,y)==-1){
		w.addPos();
		w.getPos(w.getposcount()-1).setX(x);
		w.getPos(w.getposcount()-1).setY(y);
		d->setPosition(w.getPos(w.getposcount()-1));
	}
	double destfromTarget=sqrt(pow(d->getPos()->getX() - w.getTarget()->getX(),2) + pow(d->getPos()->getY() - w.getTarget()->getY(),2));
	double destpersonal=sqrt(pow(d->getPersonal()->getX() - w.getTarget()->getX(),2) + pow(d->getPersonal()->getY() - w.getTarget()->getY(),2));
	double destglobal=sqrt(pow(w.getglobal()->getPos()->getX() - w.getTarget()->getX(),2) + pow(w.getglobal()->getPos()->getY() - w.getTarget()->getY(),2));

	//if drone's distance from target smaller then it's personalbest then update personalbest to be current drone's position
	if(destfromTarget < destpersonal)
		d->setPersonal(*d->getPos());

	//if drone's distance from target smaller than the globalbest then update globalbest to be current drone's position
	if(destfromTarget < destglobal)
		w.setGlobal(*d);
}



void setGlobal(Woods& w,int size){
	int minindex=1;
	for(int i=0 ;i<size;i++){
		double destfromTarget=sqrt(pow(w.getDrone(i+1)->getPos()->getX() - w.getTarget()->getX(),2) + pow(w.getDrone(i+1)->getPos()->getY() - w.getTarget()->getY(),2));
		double destfromTargetindex=sqrt(pow(w.getDrone(minindex)->getPos()->getX() - w.getTarget()->getX(),2) + pow(w.getDrone(minindex)->getPos()->getY() - w.getTarget()->getY(),2));
		if(destfromTarget < destfromTargetindex){
			minindex=i;
		}
	}
	w.setGlobal(*w.getDrone(minindex));
}


bool validX(double xcord,double leftL,double rightL){
	if(xcord>rightL || xcord<leftL)
		return false;
	return true;
}

bool validY(double ycord,double leftL,double rightL){
	if(ycord>rightL || ycord<leftL)
		return false;
	return true;
}

bool targetreached(Woods& w){
	if(w.getPos(0).getDC()>0)
		return true;
	return false;
}










int main(int argc,  char **argv){
	if(argv[4])
		srand(atoi(argv[4]));
	else
		srand(time(NULL));
	int iterationCNT,dronecount;
	string buffer;
	double targetX,targetY,xleftlimit,yleftlimit,xrightlimit,yrightlimit;
	Woods wood=Woods();
	WPosition* target=new WPosition();
	if( argc != 4 && argc != 5 ) cerr<<"wrong number of arguments";
	std::ifstream infile(argv[1]);
	if(!infile){
		cerr <<"Error; invalid input"<<endl;
		return 0;
	}

	//get woods limits (x & y)
	getline(infile, buffer);
	istringstream limits(buffer);
	limits>>xleftlimit;
	limits>>yleftlimit;
	limits>>xrightlimit;
	limits>>yrightlimit;

	//get target cordinates
	getline(infile, buffer);
	istringstream iss(buffer);
	iss>>targetX;
	iss>>targetY;
	if(!validX(targetX,xleftlimit,xrightlimit) || !validY(targetY,yleftlimit,yrightlimit)){
		cerr <<"Error; invalid input"<<endl;
		return 0;
	}
	target->setX(targetX);
	target->setY(targetY);
	wood.setTarget(*target);


	//get number of iterations to do
	getline(infile, buffer);
	istringstream iter(buffer);
	iter>>iterationCNT;
	std::ifstream infile2(argv[2]);
	if(!infile2){
		cerr <<"Error; invalid input"<<endl;
		return 0;
	}

	//get number of drones
	getline(infile2,buffer);
	istringstream drcnt(buffer);
	drcnt>>dronecount;

	//initialize drones
	for(int i=0 ; i<dronecount ; i++){
		getline(infile2,buffer);
		istringstream cordinate(buffer);
		string type;
		double posX,posY,speedX,speedY;
		cordinate>>type;
		cordinate>>posX;
		cordinate>>posY;
		if(!validX(targetX,xleftlimit,xrightlimit) || !validY(targetY,yleftlimit,yrightlimit)){
			cerr <<"Error; invalid input"<<endl;
			return 0;
		}
		cordinate>>speedX;
		cordinate>>speedY;
		Drone* dr;
		if(type=="S")
			dr=new SingleRotor();
		else if(type=="M")
			dr=new MultiRotor();
		else if(type=="W")
			dr=new FixedWing();
		else if(type=="H")
			dr=new Hybrid();
		dr->setId(i+1);
		dr->getPos()->setX(posX);
		dr->getPos()->setY(posY);
		dr->getSpeed()->setX(speedX);
		dr->getSpeed()->setY(speedY);
		dr->setPersonal(*dr->getPos());
		wood.addPos();
		wood.getPos(wood.getposcount()-1)=*dr->getPos();
		wood.getDrones().setRoot(wood.getDrones().insert(dr,wood.getDrones().getRoot()));
	}
	setGlobal(wood,dronecount);
	int go=0;
	std::ofstream outfile(argv[3]);
	if(!outfile){
		cerr <<"Error; invalid input"<<endl;
		return 0;
	}

	//move all drones until one reaches the target dest or until the number of iterations entered by the user
	while(go<iterationCNT && !targetreached(wood)){
		go++;
		for(int i=0 ;i<dronecount;i++)
			moveDrone(wood.getDrone(i+1),wood,xleftlimit,xrightlimit,yleftlimit,yrightlimit);
	}


	outfile<<go<<endl;
	string output=string();
	wood.getDrones().Print(wood.getDrones().getRoot(),output);
	outfile.precision(2);
	outfile<<output;
}
