/*

#include <iostream>

typedef struct _BinaryTree BinaryTree_S;
typedef struct _BinaryTree* LPBinaryTree_S;


struct _BinaryTree
{
	int data;

	LPBinaryTree_S pLchild;
	LPBinaryTree_S pRchild;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();


	int CreateTree();
	int DestroyTree();
	int DestroyTheTree(LPBinaryTree_S pBTNode);

	int TreeEmpty();
	int TreeDepth();
	int TreeDepth(LPBinaryTree_S pBTNode);
	
	LPBinaryTree_S GetRoot();

	int InsertChild(int data);
	int InsertChild(LPBinaryTree_S pBTNode);
	int DeleteChild(int data);
	int DeleteChild(LPBinaryTree_S pBTNode);
	

	int PreOrderTraverseTree(LPBinaryTree_S pBTNode);
	int PreOrderTraverseTree();
	int InOrderTraverseTree(LPBinaryTree_S pBTNode);
	int InOrderTraverseTree();
	int PostOrderTraverseTree(LPBinaryTree_S pBTNode);
	int PostOrderTraverseTree();


private:

	LPBinaryTree_S m_pRoot;
};

*/