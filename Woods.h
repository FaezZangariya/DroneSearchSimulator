#ifndef Woods_H
#define Woods_H
#include "Drone.h"
#include "BinarySearchTree.h"


class Woods{
public:
	Woods():positions(new WPosition*[3024]),poscount(1),globalBest(new Drone()),target(new WPosition()),drones(BinarySearchTree<Drone>()){
	positions[0]--;}

	Woods(const Woods& w){
		this->positions=w.positions;
		this->poscount=w.poscount;
		this->globalBest=w.globalBest;
		this->target=w.target;
	}

	~Woods();

	void setPoscount(int pc){poscount=pc;}

	void addPos(){
		positions[poscount]=new WPosition();
		poscount++;}

	int foundPos(double x,double y) const;

	int getposcount() const{return poscount;}

	Drone* getglobal(){return globalBest;}

	WPosition& getPos(int index){return *positions[index];}

	WPosition* getTarget(){return target;}

	void setGlobal(Drone& wp){*globalBest=wp;}

	void setTarget(WPosition& p){*target=p;
	positions[0]=target;
	positions[0]->operator --();
	}

	void addDrone(Drone& dt){
		drones.insert(&dt,drones.getRoot());
	}

	Drone* getDrone(int id){
		TreeNode<Drone>* rt = drones.getRoot();
		while(rt!=NULL){
			if(id > rt->getElem()->getId())
				rt=rt->getRight();
			else if(id < rt->getElem()->getId())
				rt=rt->getLeft();
			else
				return rt->getElem();
		}
		return drones.getRoot()->getElem();
	}

	BinarySearchTree<Drone>& getDrones(){return drones;}


	int operator() (double x,double y);



private:
	WPosition** positions;
	int poscount;
	Drone* globalBest;
	WPosition* target;
	BinarySearchTree<Drone> drones;
};










#endif /* Woods_H */
