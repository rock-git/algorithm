
/*
#include <iostream>
#include <string>
#include "binarytree.h"


using namespace std;


BinaryTree::BinaryTree():m_pRoot(NULL)
{
}

BinaryTree::~BinaryTree()
{
	if (this->m_pRoot != NULL) DestroyTree();
	this->m_pRoot = NULL;
}

int BinaryTree::CreateTree()
{
	return 0;
}

int BinaryTree::DestroyTheTree(LPBinaryTree_S pBTNode)
{
	if (pBTNode == NULL) return 0;

	if (pBTNode->pLchild != NULL) DestroyTheTree(pBTNode->pLchild);
	if (pBTNode->pRchild != NULL) DestroyTheTree(pBTNode->pRchild);
	delete pBTNode;

	return 0;
}

int BinaryTree::DestroyTree()
{
	DestroyTheTree(this->m_pRoot);

	return 0;
}

int BinaryTree::TreeEmpty()
{
	return (this->m_pRoot == NULL)? 0: -1;
}

int BinaryTree::TreeDepth()
{

	return TreeDepth(this->m_pRoot);
}

int BinaryTree::TreeDepth(LPBinaryTree_S pBTNode)
{
	int nLDepth, nRDepth;

	if (pBTNode == NULL) return 0;

	nLDepth = TreeDepth(pBTNode->pLchild);
	nRDepth = TreeDepth(pBTNode->pRchild);
	
	return (nLDepth >= nRDepth)? nLDepth+1: nRDepth+1;
}

LPBinaryTree_S BinaryTree::GetRoot()
{
	return this->m_pRoot;
}


int BinaryTree::PreOrderTraverseTree()
{

	return 0;
}


int BinaryTree::InOrderTraverseTree()
{

	return 0;
}


int BinaryTree::PostOrderTraverseTree()
{

	return 0;
}


int main(int argc, char *argv[])
{
	return 0;
}
*/