#include <iostream>


typedef struct _RB_TREE_NODE RB_TREE_NODE;
typedef struct _RB_TREE_NODE* LPRB_TREE_NODE;


struct _RB_TREE_NODE
{
	int color;                   //0--ºìÉ«£¬1--ºÚÉ«
	int key;
	LPRB_TREE_NODE parent;
	LPRB_TREE_NODE left;
	LPRB_TREE_NODE right;
};


void rb_tree_rotate_left(LPRB_TREE_NODE pNode, LPRB_TREE_NODE root)
{
	LPRB_TREE_NODE pRNode = NULL;

	pRNode = pNode->right;

	if ((pNode->right = pRNode->left) != NULL) pRNode->left->parent = pNode;

	pRNode->parent = pNode->parent;
	if (pNode == root)
	{
		root = 	pRNode;
	}
	else (pNode->parent->left == pNode)
	{
		pNode->parent->left = pRNode;
	}
	else
	{
		pNode->parent->right = pRNode;
	}

	pNode->parent = pRNode;
	pRNode->left = pNode;
}


void rb_tree_rotate_right(LPRB_TREE_NODE pNode, LPRB_TREE_NODE root)
{
	LPRB_TREE_NODE pLNode = NULL;

	pLNode = pNode->left;
	if ((pNode->left = pLNode->right) != NULL) pLNode->right->parent = pNode;

	pLNode->parent = pNode->parent;
	if (pNode == root)
	{
	}
	else (pNode->parent->left == pNode)
	{
		pNode->parent->left = pLNode;
	}
	else
	{
		pNode->parent->right = pLNode;
	}

	pNode->parent = pLNode;
	pLNode->right = pNode;
}