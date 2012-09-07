/*
 * playcode.cpp
 * 
 * Copyright 2012 radiohead <radiohead@ubuntu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * http://blog.csdn.net/v_JULY_v/article/details/6234496
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>


using namespace std;
/*
 * 1、有一个整数数组，请求出两两之差绝对值最小的值,
 *	  记住，只要得出最小值即可，不需要求出是哪两个数。
 * 
 */
int MinABSValue(vector<int> &vc)
{
	int i, j;
	int nTmp, nMin = 0x7FFFFFFF;
	
	for (i = 0; i < vc.size(); ++i)
	{
		for (j = i + 1; j < vc.size(); ++j)
		{
			nTmp = abs(vc[i] - vc[j]);
			if (nMin > nTmp) nMin = nTmp;
		}
	}
	
	return nMin;
}

/*
 *2、写一个函数，检查字符是否是整数，如果是，返回其整数值。
 *   （或者：怎样只用4行代码编写出一个从字符串到长整形的函数？） 
 * 
 */
int CheckChar(char *pcStr,int nLen)
{
	int i = 0;
	int nNum = 0;
	
	if (pcStr == NULL) return -1;
	
	for (i = 0; i < nLen; ++i)
	{
		if (pcStr[i] < '0' || pcStr[i] > '9') return -1;
		
		nNum = nNum * 10 + (pcStr[i] - '0');
	}
	
	return nNum;
}
 
 
 /*
 * 3、给出一个函数来输出一个字符串的所有排列。 
 *
 */
 
 void SwapChar(char *p, char *q)
 {
	 char c;
	 
	 c = *p;
	 *p= *q;
	 *q = c;
 }
 
 void Permutation(char *pcStr, char *pcBegin)
 {
	 char *p = NULL;
	 
	 if (pcStr == NULL || pcBegin == NULL) return;
	 
	 if (*pcBegin == '\0')
	 {
		 cout << pcStr << endl;
		 return;
	 }

	for (p = pcBegin; *p != '\0'; ++p)
	{
		SwapChar(p, pcBegin);
		Permutation(pcStr, pcBegin + 1);
		SwapChar(p, pcBegin);
	}
 }
 
/*
 * 4、（a）请编写实现malloc()内存分配函数功能一样的代码。
 * （b）给出一个函数来复制两个字符串A和B。字符串A的后几个字节和字符串B的前几个字节重叠。
 *
 */
 
 void* MyMalloc(int nSize)
 {
	 void *p = NULL;
	 
	 if ((p = malloc(nSize)) == NULL) return NULL;
	 
	 return p;
 }
 
 void CopyStr(char *pcStrA, char *pcStrB)
 {
	 char *pcTmp = NULL;
	 
	 pcTmp = (char *)malloc(strlen(pcStrA) + 1);
	 strcpy(pcTmp, pcStrA);
	 while (pcTmp != NULL && *pcTmp != '\0')
	 {
		  *pcStrB = *pcTmp;
		  ++pcTmp;
		  ++pcStrB;
	  }
	  
	  if (pcTmp != NULL) free(pcTmp);
 }
 
/*
 * 6、怎样从顶部开始逐层打印二叉树结点数据？请编程。
 *
 */
 
typedef struct _BTNode
{
	int nData;
	struct _BTNode *pLeft;
	struct _BTNode *pRight;
	struct _BTNode *pParant;
}BTNode, *LPBTNode, *LPBTree;


typedef struct _BTQNode
{
	LPBTNode pData;
	
	struct _BTQNode *next;
	struct _BTQNode *prev;
	
}BTQNode, *LPBTQNode;

typedef struct _BTQueue
{
	LPBTQNode pHead;
	LPBTQNode pTail; 
}BTQueue, *LPBTQueue;


void InitBTQueue(LPBTQueue pBTQueue)
{
	pBTQueue->pHead = NULL;
	pBTQueue->pTail = NULL;
}

int IsEmpty(LPBTQueue pBTQueue)
{
	if (pBTQueue->pHead == NULL || pBTQueue->pTail == NULL) return 1;
	
	return 0;
}

void EnQueue(LPBTQueue pBTQueue, LPBTNode pBTNode)
{
	LPBTQNode pBTQNode = NULL;
	
	pBTQNode = (LPBTQNode)malloc(sizeof(BTQNode));
	memset(pBTQNode, 0, sizeof(BTQNode));
	pBTQNode->pData = pBTNode;
	
	pBTQNode->next = pBTQueue->pTail;
	pBTQueue->pTail = pBTQNode;
	if (pBTQueue->pHead == NULL) pBTQueue->pHead = pBTQueue->pTail;
}

LPBTNode DeQueue(LPBTQueue pBTQueue)
{
	LPBTNode pBTNode = NULL;
	LPBTQNode pBTQNode = NULL;
	
	if (IsEmpty(pBTQueue)) return NULL;
	pBTQNode = pBTQueue->pHead;
	pBTQueue->pHead = pBTQNode->prev;
	if (pBTQueue->pHead != NULL) pBTQueue->pHead->next = NULL;
	else pBTQueue->pTail = NULL;
	
	pBTNode = pBTQNode->pData;
	free(pBTQNode);
	return pBTNode;
}

void TraversalTreeByScope(LPBTree pBTree)
{
	LPBTNode pBTHead, pBTNode;
	BTQueue BtQueue;
	
	pBTHead = pBTree;
	InitBTQueue(&BtQueue);
	EnQueue(&BtQueue, pBTHead);
	while (!IsEmpty(&BtQueue))
	{
		pBTNode = DeQueue(&BtQueue);
		cout << pBTNode->nData << " ";
		
		if (pBTNode->pLeft != NULL) EnQueue(&BtQueue, pBTNode->pLeft);
		if (pBTNode->pRight != NULL) EnQueue(&BtQueue, pBTNode->pRight);
	}	
}

/**
 * 7、怎样把一个链表掉个顺序（也就是反序，注意链表的边界条件并考虑空链表）？
 * 
 */
 
 typedef struct _LNode
 {
	 int data;
	 struct _LNode *next;
 }LNode, *LPLNode;
 
 
 void ListReverseOrder(LPLNode pLNode)
 {
	 LPLNode pNode = NULL, pNextNode = NULL;
	 
	 if (pLNode->next == NULL) return;
	 pNode = pLNode->next;
	 pLNode->next = NULL;
	 while (pNode != NULL)
	 {
		 pNextNode = pNode->next;
		 
		 pNode->next = pLNode->next;
		 pLNode->next = pNode;
		 
		 pNode = pNextNode; 
	 }
 }
 
 /**
  * 8、请编写能直接实现int atoi(const char * pstr)函数功能的代码。
  * 
  */
 int MyAtoi(const char *pcStr)
 {
	 int num = 0, sym = 1;
	 
	 if (*pcStr == '+')
	 {
		 ++pcStr;
	 }
	 else if (*pcStr == '-')
	 {
		 ++pcStr;
		 sym = -1;
	 }
	 
	 while (*pcStr != '\0')
	 {
		 num = num * 10 + (*pcStr - '0');
		 ++pcStr;
	 }
	 
	 return sym * num;
 }
 
 
 /**
  * 9.编程实现两个正整数的除法，当然不能用除法操作符。
  * 
  */
int div_int(const int x, const int y)  
{  
    int left_num, result;  
    int multi;  
    left_num = x;  
    result = 0;  
    multi = 0;  
      
    while(left_num>=y)  
    {  
        multi = 1;  
        while(y*multi <= (left_num>>1))  
            multi = multi<<1;  
        result += multi;  
        left_num -= y*multi;
    }  
    return result;  
}  

void devide(int val1, int val2, int& res, int &rev)  
{  
    int maxv = max(val1, val2);  
    int minv = min(val1, val2);  
    res = 0;  
    rev = 0;  
    if(maxv == minv){  
        res = 1;  
        rev = 0;  
        return;  
    }else{  
        while(maxv > minv){  
            maxv = maxv - minv;  
            res += 1;  
        }  
        rev = maxv;  
        return;  
    }  
  
}  

/**
 * 10、在排序数组中，找出给定数字的出现次数
 * 
 */
 
int FindNumTimes(int *pnArray, int size, int n)
{
	int i, count = 0;
	
	for (i = 0; i < size; ++i)
	{
		if (pnArray[i] == n) break;
	}
	
	while (i < size)
	{
		if (pnArray[i++] == n) ++count;
		else break;
	}
	
	return count;	
}
 
 /**
  * 13、设计一个算法，找出二叉树上任意两个结点的最近共同父结点。
  * 
  */
 
 LPBTNode FindTheParant(LPBTree pBTree, LPBTNode pBTNode1, LPBTNode pBTNode2)
 {
	 int i = 0, j = 0;
	 LPBTNode aNode1[32] = {0}, aNode2[32] = {0};
	 
	 while (pBTNode1 != pBTree)
	 {
		 aNode1[i++] = pBTNode1;
		 pBTNode1 = pBTNode1->pParant;
	 }
	 
	 while (pBTNode2 != pBTree)
	 {
		 aNode2[j++] = pBTNode2;
		 pBTNode2 = pBTNode2->pParant;
	 }
	 
	 if (aNode1[i] != aNode2[j]) return pBTree;
	 while (aNode1[i] == aNode2[j]) --i, --j;
	 
	return aNode1[++i]; 
 }
 
  /**
  *  14、一棵排序二叉树，令 f=(最大值+最小值)/2，
  *	设计一个算法，找出距离f值最近、大于f值的结点。
  * 
  */
 LPBTNode FindTheNode(LPBTree pBTree, int f)
 {
	/*	 
	 * int f, max, min;
	 * LPBTNode pBTNode;
	 * 
	 pBTNode = pBTree;
	 while (pBTNode->pLeft != NULL) pBTNode = pBTNode->pLeft;
	 max = pBTNode->data;
	 pBTNode = pBTree;
	 while (pBTNode->pRight != NULL) pBTNode = pBTNode->pRight;
	 min = pBTNode->data;
	 
	 f = (max + min)/2;
	 */;
	 
	 if (f >= pBTree->nData && f < pBTree->pLeft->nData) return pBTree;
	 else if (f < pBTree->nData && f >= pBTree->pRight->nData) return pBTree->pRight;
	 else if (f >= pBTree->pLeft->nData) FindTheNode(pBTree->pLeft, f);
	 else if (f < pBTree->pRight->nData) FindTheNode(pBTree->pRight, f);
	 else return NULL;	 
 }
 

 
 void PrintMatrixCircle(int **num,int sX,int sY,int eX,int eY);
 
 //给定矩阵，给定行列，由外向内顺时针打印数字
 void PrintMatrixClockwisely(int **matrix,int rows,int columns)
 {
     if(matrix == NULL || rows < 0 || columns < 0)
         return;
 
     int startX = 0;
     int startY = 0;
     int endX = rows - 1;
     int endY = columns - 1;
     while(1)
     {
         if(startX > endX && startY > endY)
             break;
         if(startX == endX && startY > endY)
             break;
         if(startX > endX && startY == endY)
             break;
         
         PrintMatrixCircle(matrix,startX,startY,endX,endY);
         
         ++startX;
         ++startY;
         --endX;
         --endY;
     }
 }
 
 //对于给定矩阵，给定对角线上两点，打印这一周的元素
 void PrintMatrixCircle(int **num,int sX,int sY,int eX,int eY)
 {
     //只有一行的情况，直接打印，返回。
     if(sX == eX)
     {
         for(int j = sY;j <= eY;++j)
         {
             cout<<*(*(num+sX)+j)<<"\t";
         }
 
         return;
     }
     //只有一列的情况，直接打印，返回。
     if(sY == eY)
     {
         for(int i = sX;i <= eX;++i)
         {
             cout<<*(*(num+i)+sY)<<"\t";
         }
         return;
     }
     
     //一般的情况打印四行
     for(int p = sY;p < eY;++p)
     {
         cout<<*(*(num+sX)+p)<<"\t";
     }
 
     for(int q = sX;q < eX;++q)
     {
         cout<<*(*(num+q)+eY)<<"\t";
     }
 
     for(int m = eY;m > sY;--m)
     {
         cout<<*(*(num+eX)+m)<<"\t";
     }
     
     for(int n = eX;n > sX;--n)
     {
         cout<<*(*(num+n)+sY)<<"\t";
     }
 
 }
 
 
void knuth(int n, int m)
{
	int i;
	srand((unsigned int)time(0));
	
	for (i = 0; i < n; ++i)
	{
		if (rand()%(n - i) < m)
		{
			cout << i << " ";
			--m;
		}
	}
	cout << endl;
}
 
 
int main(int argc, char **argv)
{
	//char acStr[] = "123";
	
	//cout << CheckChar(acStr, strlen(acStr)) << endl;
	
	//Permutation(acStr, acStr);
	
	//int n = atoi("+123");
	
	//cout << n <<endl;
	

	int a[][5] = {{1, 2, 3, 4, 5}, 
				 {6, 7, 8, 9, 10}, 
				 {11, 12, 13, 14, 15},
				 {16, 17, 18, 19, 20},
				 {21, 22, 23, 24, 25}};
				 
	int *a1[5] = {a[0], a[1], a[2], a[3], a[4]};
	int **a2 = a1;
				 
	
	//PrintArray(a, 5, 5);
	PrintMatrixClockwisely(a2, 5, 5);
	
	cout << endl;

	
	//knuth(100, 30);
	
	
	return 0;
}

