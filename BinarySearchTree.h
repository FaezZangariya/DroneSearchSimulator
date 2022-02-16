/*
 * BinarySearchTree.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <iostream>
using namespace std;
#include"TreeNode.h"


template<class T>
class BinarySearchTree {
public:
	BinarySearchTree():root(),min(),max(){
		min=NULL;
		max=NULL;
		root=NULL;}

	virtual ~BinarySearchTree(){
		Clear(root);
		delete this;
	}

	void setRoot(TreeNode<T>* r){root=r;}

	TreeNode<T>* getRoot(){return root;}

	bool search(T* newelem){
		TreeNode<T>* rt=root;
		while(rt!=NULL){
			if(rt->getElem()==newelem)
				return true;
			else if(rt->getElem()>newelem)
				rt=rt->getLeft();
			else if(rt->getElem()<newelem)
				rt=rt->getRight();
		}
		return false;
	}


	TreeNode<T>* insert(T* newelem,TreeNode<T>* rt){
		if (rt==NULL){
			rt=new TreeNode<T>();
			rt->setElem(newelem);
			return rt;
	    }
		if (newelem->getId() > rt->getElem()->getId())
			rt->setRight(insert(newelem,rt->getRight()));
		else
			rt->setLeft(insert(newelem,rt->getLeft()));
		return rt;
	}

	TreeNode<T>* getMax(TreeNode<T>* rt)
	{
		TreeNode<T>* max = rt;
		while (max && max->getLeft() != NULL)
			max = max->getLeft();
		return max;
	}

	TreeNode<T>* getMin(TreeNode<T>* rt)
	{
	    TreeNode<T>* min = rt;
	    while (min && min->getLeft() != NULL)
	        min = min->getLeft();
	    return min;
	}

	TreeNode<T>* remove(struct TreeNode<T>* rt, T todelete)
	{
	    if (rt == NULL)
	        return rt;
	    if (todelete < rt->getElem())
	        rt->setLeft(remove(rt->getLeft(), todelete));
	    else if (todelete > rt->getElem())
	        rt->setRight(remove(rt->getRight(), todelete));
	    else {
	        if (rt->getLeft() == NULL) {
	        	TreeNode<T>* temp = rt->getRight();
	            free(rt);
	            return temp;
	        }
	        else if (rt->right == NULL) {
	        	TreeNode<T>* temp = rt->getLeft();
	            free(rt);
	            return temp;
	        }
	        TreeNode<T>* temp = getMin;
	        rt->setElem(temp->getElem());
	        rt->setRight(remove(rt->getRight(), temp->getElem()));
	    }
	    return rt;
	}

	void Clear(TreeNode<T>* rt)
	{
	    if (rt == NULL) return;
	    Clear(rt->getLeft());
	    Clear(rt->getRight());
	    delete rt;
	}


	void Print(TreeNode<T>* rt,string& out)
	{
	    if (rt == NULL)
	        return;
	    Print(rt->getLeft(),out);
	    out+=rt->getElem()->PrintDrone();
	    Print(rt->getRight(),out);
	}


	int size(TreeNode<T>* rt)
	{
	    if (rt == NULL)
	        return 0;
	    else
	        return(size(rt->getLeft()) + 1 + size(rt->getRight()));
	}



private:
	TreeNode<T>* root;
	TreeNode<T>* min;
	TreeNode<T>* max;
};

#endif /* BINARYSEARCHTREE_H_ */
