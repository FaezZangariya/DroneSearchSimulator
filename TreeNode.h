/*
 * TreeNode.h
 *
 *  Created on: 12 Jan 2021
 *      Author: faez zangariya
 */

#ifndef TREENODE_H_
#define TREENODE_H_



template <class T>
class TreeNode{
public:
	TreeNode():left(),right(),elem(){
		left=NULL;
		right=NULL;
		elem=NULL;
	}
	virtual ~TreeNode(){
		delete left;
		delete right;
	}
	void setLeft(TreeNode* leftnode){left=leftnode;}
	TreeNode* getLeft(){return left;}
	void setRight(TreeNode* rightnode){right=rightnode;}
	TreeNode* getRight(){return right;}
	void setElem(T* e){elem=e;}
	T* getElem(){return elem;}

private:
	TreeNode* left;
	TreeNode* right;
	T* elem;
};

#endif /* TREENODE_H_ */
