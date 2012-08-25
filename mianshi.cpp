#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <stack>
#include <assert.h>
#include <algorithm>


using namespace std;

//题目：输入一棵二元查找树，将该二元查找树转换成一个排序的双向链表。
// 要求不能创建任何新的结点，只调整指针的指向。


struct BSTreeNode // a node in the binary search tree
{
    int          m_nValue; // value of node
    BSTreeNode  *m_pLeft;  // left child of node
    BSTreeNode  *m_pRight; // right child of node
};


//思路一：当我们到达某一结点准备调整以该结点为根结点的子树时，
//先调整其左子树将左子树转换成一个排好序的左子链表，再调整其右子树转换右子链表。
//最近链接左子链表的最右结点（左子树的最大结点）、当前结点和右子链表的最左结点（右子树的最小结点）。
//从树的根结点开始递归调整所有结点。

BSTreeNode* ConvertNode(BSTreeNode* pNode, bool asRight)
{
      if(!pNode)
            return NULL;

      BSTreeNode *pLeft = NULL;
      BSTreeNode *pRight = NULL;

      if(pNode->m_pLeft)
            pLeft = ConvertNode(pNode->m_pLeft, false);

      if(pLeft)
      {
            pLeft->m_pRight = pNode;
            pNode->m_pLeft = pLeft;
      }

      if(pNode->m_pRight)
            pRight = ConvertNode(pNode->m_pRight, true);

      if(pRight)
      {
            pNode->m_pRight = pRight;
            pRight->m_pLeft = pNode;
      }

      BSTreeNode *pTemp = pNode;

      if(asRight)
      {
            while(pTemp->m_pLeft)
                  pTemp = pTemp->m_pLeft;
      }
      else
      {
            while(pTemp->m_pRight)
                  pTemp = pTemp->m_pRight;
      }
 
      return pTemp;
}

BSTreeNode* Convert(BSTreeNode* pHeadOfTree)
{
      return ConvertNode(pHeadOfTree, true);
}

//思路二：我们可以中序遍历整棵树。按照这个方式遍历树，比较小的结点先访问。
//如果我们每访问一个结点，假设之前访问过的结点已经调整成一个排序双向链表，
//我们再把调整当前结点的指针将其链接到链表的末尾。当所有结点都访问过之后，
//整棵树也就转换成一个排序双向链表了。

void ConvertNode(BSTreeNode* pNode, BSTreeNode*& pLastNodeInList)
{
      if(pNode == NULL)
            return;

      BSTreeNode *pCurrent = pNode;

      // Convert the left sub-tree
      if (pCurrent->m_pLeft != NULL)
            ConvertNode(pCurrent->m_pLeft, pLastNodeInList);

      // Put the current node into the double-linked list
      pCurrent->m_pLeft = pLastNodeInList; 
      if(pLastNodeInList != NULL)
            pLastNodeInList->m_pRight = pCurrent;

      pLastNodeInList = pCurrent;

      // Convert the right sub-tree
      if (pCurrent->m_pRight != NULL)
            ConvertNode(pCurrent->m_pRight, pLastNodeInList);
}

BSTreeNode* Convert_Solution1(BSTreeNode* pHeadOfTree)
{
      BSTreeNode *pLastNodeInList = NULL;
      ConvertNode(pHeadOfTree, pLastNodeInList);

      // Get the head of the double-linked list
      BSTreeNode *pHeadOfList = pLastNodeInList;
      while(pHeadOfList && pHeadOfList->m_pLeft)
            pHeadOfList = pHeadOfList->m_pLeft;

      return pHeadOfList;
}


//题目：定义栈的数据结构，要求添加一个min函数，能够得到栈的最小元素。
//要求函数min、push以及pop的时间复杂度都是O(1)。

template <typename T>
class StackWithMin
{
public:
	StackWithMin(){}
	~StackWithMin(){}

	T& top(void);
	void push(const T &value);
	T& pop(void);

	T& min(void);

private:
	deque<T> m_data;
	deque<int> m_minIndex;
};


template <typename T>
T& top(void)
{
	assert(m_data.size > 0);
	return m_data.back();
}

template <typename T>
void push(const T &value)
{
	m_data.push_back(value);

	if (m_minIndex.size() == 0)
	{
		m_minIndex.push_back(0);
	}
	else
	{
		if (value < m_data[m_minIndex.back()])
		{
			m_minIndex.push_back(m_data.size() - 1);
		}
		else
		{
			m_minIndex.push_back(m_minIndex.back());
		}
	}
}

template <typename T>
T& pop(void)
{
	m_minIndex.pop_back();
	return m_data.pop_back();
}

template <typename T>
T& min(void)
{
	assert(m_data.size() > 0);
	assert(m_minIndex.size() > 0);

	return m_data[m_minIndex.back()];
}


//题目：输入一个整形数组，数组里有正数也有负数。数组中连续的一个或多个整数组成一个子数组，
//每个子数组都有一个和。求所有子数组的和的最大值。要求时间复杂度为O(n)。
//
//例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，和最大的子数组为3, 10, -4, 7, 2，
//因此输出为该子数组的和18。

int FindGreatestSumOfSubArray(vector<int>& vc)
{
	int i, bp, ep;
	int tmpsum = 0, sum = 0;

	for (i = 0; i < vc.size(); ++i)
	{
		if (tmpsum < 0)
		{
			tmpsum = vc[i];
			bp = ep = i;
		}
		else
		{
			tmpsum += vc[i];
			++ep;
		}

		if (sum < tmpsum) sum = tmpsum;
	}

	return sum;
}


//题目：输入一个整数和一棵二元树。从树的根结点开始往下访问一直到叶结点所经过的所有结点形成一条路径。
//打印出和与输入整数相等的所有路径。

void print_1(int value)
{
	cout << value << " ";
}

void FindPath(BSTreeNode *root, vector<int>& vc, int expectSum, int currentSum)
{
	if (root == NULL) return;

	currentSum += root->m_nValue;
	vc.push_back(root->m_nValue);
	bool isLeaf = (root->m_pLeft == NULL && root->m_pRight);

	if (currentSum == expectSum && isLeaf)
	{
		for_each(vc.begin(), vc.end(), print_1);
		cout << endl;
	}

	if (root->m_pLeft != NULL) FindPath(root->m_pLeft, vc, expectSum, currentSum);
	if (root->m_pRight != NULL) FindPath(root->m_pRight, vc, expectSum, currentSum);

	currentSum -= root->m_nValue;
	vc.pop_back();
}


//题目：输入n个整数，输出其中最小的k个。
//
//例如输入1，2，3，4，5，6，7和8这8个数字，则最小的4个数字为1，2，3和4。

int Partial(vector<int> &vc, int begin, int end)
{
	int tmp;

	tmp = vc[begin];
	while (begin < end)
	{
		while (vc[end] >= tmp) --end;
		vc[begin] = vc[end];

		while (vc[begin] <= tmp) ++begin;
		vc[end] = vc[begin];
	}

	vc[begin] = tmp;

	return begin;
}

void FindKLeastNumbers(vector<int> &vc, int k)
{
	if (vc.empty()) return;

	int m, begin, end;
	begin = 0;
	end = vc.size() - 1;
	for (;;)
	{
		m = Partial(vc, begin, end);

		if (m == k) break;
		else if (m < k) begin = m + 1;
		else end = m - 1;
	}
}

//题目：输入一个整数数组，判断该数组是不是某二元查找树的后序遍历的结果。
//如果是返回true，否则返回false。

int verifySquenceOfBST(vector<int> &vc, int begin , int end)
{
	int i, j, root;

	root = vc[end];
	for (i = begin; i < end; ++i)
	{
		if (vc[i] > root)
		{
			for (j = i; j < end; ++j)
			{
				if (vc[j] < root) break;
			}
			if (j >= end) return 0;
			else return -1;
		}
	}

	if (verifySquenceOfBST(vc, begin, i - 1) == 0 
		&& verifySquenceOfBST(vc, i, end - 1) == 0) return 0;
	else return -1;
}

//题目：输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。句子中单词以空格符隔开。
//为简单起见，标点符号和普通字母一样处理。
//
//例如输入“I am a student.”，则输出“student. a am I”。


void Reverse(char *pcBegin, char *pcEnd)
{
	char tmp;

	while (pcBegin < pcEnd)
	{
		tmp = *pcBegin;
		*pcBegin = *pcEnd;
		*pcEnd = tmp;
		++pcBegin;
		--pcEnd;
	}
}

void ReverseSentence(char *pcStr)
{
	char *pEnd = NULL;

	Reverse(pcStr, pcStr + strlen(pcStr) - 1);

	while (*pcStr != '\0')
	{
		if (*pcStr == ' ')
		{
			++pcStr;
			continue;
		}

		pEnd = pcStr;
		while (*pEnd != ' ' && *pEnd != '\0') ++pEnd;
		Reverse(pcStr, pEnd - 1);	

		pcStr = pEnd;
	}
}

//题目：输入一个已经按升序排序过的数组和一个数字，在数组中查找两个数，
//使得它们的和正好是输入的那个数字。要求时间复杂度是O(n)。如果有多对数字的和等于输入的数字，
//输出任意一对即可。

void FindTwoNumbersWithSum(vector<int> &vc, int n)
{
	int begin, end, sum;

	begin = 0;
	end = vc.size() -1;
	while (begin < end)
	{
		sum = vc[begin] + vc[end];
		if (sum == n)
		{
			cout << vc[begin] << " " << vc[end] << endl;
			++begin;
		}
		else if (sum < n)
		{
			++begin;
		}
		else
		{
			--end;
		}
	}
}


//题目：输入一颗二元查找树，将该树转换为它的镜像，即在转换后的二元查找树中，
//左子树的结点都大于右子树的结点。用递归和循环两种方法完成树的镜像转换。
//递归
void MirrorRecursively(BSTreeNode *pNode)
{
	BSTreeNode *pL = NULL, *pR = NULL;
	
	pL = pNode->m_pLeft;
	pR = pNode->m_pRight;


	if (pL == NULL && pR == NULL) return;

	if (pL != NULL) MirrorRecursively(pL);
	if (pR != NULL) MirrorRecursively(pR);

	if (pL != NULL && pR != NULL)
	{
		pNode->m_pLeft = pR;
		pNode->m_pRight = pL;
	}
	else if (pR == NULL)
	{
		pNode->m_pRight = pL;
	}
	else if (pL == NULL)
	{
		pNode->m_pLeft = pR;
	}
}

//非递归
void MirrorRecursively_2(BSTreeNode *pRoot)
{
	deque<BSTreeNode*> dq;
	BSTreeNode *pNode = NULL, *pTmpNode = NULL;

	dq.push_back(pNode);
	while (!dq.empty())
	{
		pNode = (BSTreeNode *)dq.back();
		dq.pop_back();
		if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL)
		{
			continue;
		}
		else if (pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
		{
			pNode->m_pRight = pNode->m_pLeft;
			dq.push_back(pNode->m_pLeft);
			pNode->m_pLeft = NULL;
		}
		else if (pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
		{
			pNode->m_pLeft = pNode->m_pRight;
			dq.push_back(pNode->m_pRight);
			pNode->m_pRight = NULL;
		}
		else
		{
			dq.push_back(pNode->m_pLeft);
			dq.push_back(pNode->m_pRight);
			pTmpNode = pNode->m_pLeft;
			pNode->m_pLeft = pNode->m_pRight;
			pNode->m_pRight = pTmpNode;
		}
	}
}


//题目：输入一颗二元树，从上往下按层打印树的每个结点，同一层中按照从左往右的顺序打印.

void PrintFromTopToBottom(BSTreeNode *pTreeRoot)
{
	deque<BSTreeNode*> dq;
	BSTreeNode *pNode = NULL;

	dq.push_back(pTreeRoot);
	while (!dq.empty())
	{
		pNode = (BSTreeNode*)dq.back();
		dq.pop_back();
		cout << pNode->m_nValue << " ";
		if (pNode->m_pLeft != NULL) dq.push_back(pNode->m_pLeft);
		if (pNode->m_pRight != NULL) dq.push_back(pNode->m_pRight);
	}
}


//题目：在一个字符串中找到第一个只出现一次的字符。如输入abaccdeff，则输出b。

char FirstNotRepeatingChar(char* pString)
{
	int a[256] = {0};
	char *p = pString;

	while (*p != '\0')
	{
		++a[*p];
		++p;
	}

	p = pString;
	while (*p != '\0')
	{
		if (a[*p] == 1) return *p;
		++p;
	}
	return 0;
}

//题目：n个数字（0,1,…,n-1）形成一个圆圈，从数字0开始，
//每次从这个圆圈中删除第m个数字（第一个为当前数字本身，第二个为当前数字的下一个数字）。
//当一个数字删除后，从被删除数字的下一个继续删除第m个数字。求出在这个圆圈中剩下的最后一个数字。
//本题就是有名的约瑟夫环问题

//思路一:用链表实现
int LastRemaining_Solution1(unsigned int n, unsigned int m)
{
      // invalid input
      if(n < 1 || m < 1)
            return -1;

      unsigned int i = 0;

      // initiate a list with n integers (0, 1, ... n - 1)
      list<int> integers;
      for(i = 0; i < n; ++ i)
            integers.push_back(i);

      list<int>::iterator curinteger = integers.begin();
      while(integers.size() > 1)
      {
            // find the mth integer. Note that std::list is not a circle
            // so we should handle it manually
            for(int i = 1; i < m; ++ i)
            {
                  curinteger ++;
                  if(curinteger == integers.end())
                        curinteger = integers.begin();
            }

            // remove the mth integer. Note that std::list is not a circle
            // so we should handle it manually
            list<int>::iterator nextinteger = ++ curinteger;
            if(nextinteger == integers.end())
                  nextinteger = integers.begin();

            -- curinteger;
            integers.erase(curinteger);
            curinteger = nextinteger;
      }

      return *(curinteger);
}

//思路二: 
//f(n, m) = 0                   (n = 1)
//f(n, m) = [f(n-1, m) + m] % n (n > 1)
int LastRemaining_Solution2(int n, unsigned int m)
{
      if(n <= 0 || m < 0)
            return -1;

      int lastinteger = 0;

      for (int i = 2; i <= n; i ++) 
            lastinteger = (lastinteger + m) % i;

      return lastinteger;
}

//题目: O(logn)求Fibonacci数列[算法]  
long long Fibonacci_Solution1(unsigned int n)
{
      int result[2] = {0, 1};
      if(n < 2)
            return result[n];

      return Fibonacci_Solution1(n - 1) + Fibonacci_Solution1(n - 2);
}

long long Fibonacci_Solution2(unsigned int n)
{
	int i;
	long long f1, f2, fn;

	f1 = 0;
	f2 = 1;
	for (i = 2; i <= n; ++i)
	{
		fn = f1 + f2;
		f1 = f2;
		f2 = fn;
	}

	return fn;
}


//题目：输入两个整数序列。其中一个序列表示栈的push顺序，判断另一个序列有没有可能是对应的pop顺序。
//为了简单起见，我们假设push序列的任意两个整数都是不相等的。
bool IsPossiblePopOrder(const int* pPush, const int* pPop, int nLength)
{
	int i, j, pos = 0;
	bool bPossible = false;

	if (pPush == NULL || pPop == NULL || nLength <= 0) return bPossible;

	stack<int> stackData;

	for (i = 0; i < nLength; ++i)
	{
		while (stackData.empty() || pPop[i] != stackData.top())
		{
			if (pos >= nLength) break;

			stackData.push(pPush[pos]);
			++pos;
		}

		if (pPop[i] != stackData.top()) stackData.pop();
	}

	if (stackData.empty()) bPossible = true;

	return bPossible;
}

//题目：输入一个正数n，输出所有和为n连续正数序列。
//
//例如输入15，由于1+2+3+4+5=4+5+6=7+8=15，所以输出3个连续序列1-5、4-6和7-8。

//思路一: n = (2x + k - 1)*k/2
void print_2(int x, int k)
{
	int i;
	for (i = 0; i < k; ++i)
	{
		cout << x + i << " ";
	}

	cout << endl;
}

void FindContinuousSequence_1(int n)
{
	double x, k;
	double tmp;

	k = 2;
	
	while ((tmp = ((2*n - (k-1)*k)/(2*k))) > 0)
	{
		x = (int)tmp;
		if (x == tmp) print_2(x, k);
		++k;
	}
}

//思路二: 我们用两个数small和big分别表示序列的最小值和最大值。
//首先把small初始化为1，big初始化为2。如果从small到big的序列的和大于n的话，
//我们向右移动small，相当于从序列中去掉较小的数字。如果从small到big的序列的和小于n的话，
//我们向右移动big，相当于向序列中添加big的下一个数字。一直到small等于(1+n)/2，因为序列至少要有两个数字。
void PrintContinuousSequence(int small, int big)
{
      for(int i = small; i <= big; ++ i)
            printf("%d ", i);

      printf("\n");
}

void FindContinuousSequence_2(int n)
{
      if(n < 3)
            return;

      int small = 1; 
      int big = 2;
      int middle = (1 + n) / 2;
      int sum = small + big;

      while(small < middle)
      {
            // we are lucky and find the sequence
            if(sum == n)
                  PrintContinuousSequence(small, big);

            // if the current sum is greater than n, 
            // move small forward
            while(sum > n)
            {
                  sum -= small;
                  small ++;

                  // we are lucky and find the sequence
                  if(sum == n)
                        PrintContinuousSequence(small, big);
            }

            // move big forward
            big ++;
            sum += big;
      }
}

//题目：用C++设计一个不能被继承的类。
//虚拟继承让Try()直接调用MakeFinal
template <typename T> class MakeFinal
{
      friend T;
 
private:
      MakeFinal() {}
      ~MakeFinal() {}
};
 
class FinalClass2 : virtual public MakeFinal<FinalClass2>
{
public:
      FinalClass2() {}
      ~FinalClass2() {}
};

//class Try : public FinalClass2
//{
//public:
//      Try() {}
//      ~Try() {}
//};
 

//题目：输入一个字符串，打印出该字符串中字符的所有排列。
//例如输入字符串abc，则输出由字符a、b、c所能排列出来的所有字符串abc、acb、bac、bca、cab和cba。

void swapchar(char *pStr1, char *pStr2)
{
	char c;

	c = *pStr1;
	*pStr1 = *pStr2;
	*pStr2 = c;
}

void Permutation(char* pStr, char* pBegin)
{
	if (pStr == NULL || pBegin == NULL) return;

	if (*pBegin == '\0')
	{
		cout << pStr << " ";
		return;
	}

	for (char *pPos = pBegin; *pPos != '\0'; ++pPos)
	{
		swapchar(pBegin, pPos);
		Permutation(pStr, pBegin+1);
		swapchar(pBegin, pPos);
	}
}

/*
int main(void)
{
	//int a[] = {5, 7, 6, 9, 4, 10, 8};
	//vector<int> vc(a, a+7);

	//FindKLeastNumbers(vc, 3);

	//for_each(vc.begin(), vc.end(), print_1);

	//if (verifySquenceOfBST(vc, 0 , vc.size() - 1) == 0)
	//{
	//	cout << "true" << endl;
	//}
	//else
	//{
	//	cout << "false" << endl;
	//}

	//char acStr[] = "I'm a creep , I'm a wiredo ... I don't belong here";
	//cout << acStr << endl;
	//ReverseSentence(acStr);

	//cout << acStr << endl;

	//int a[] = {1, 2, 4, 5, 7, 10, 11, 15};
	//vector<int> vc(a, a+8);

	//FindTwoNumbersWithSum(vc, 15);

	//cout << FirstNotRepeatingChar("abaccdeff") << endl;

	//cout << Fibonacci_Solution2(100) << endl;
	//cout << Fibonacci_Solution1(100) << endl;

	//FindContinuousSequence_1(112355);

	char a[] = "abc";
	Permutation(a, a);

	cout << endl;
	return 0;
}

*/