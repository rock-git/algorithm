#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <stack>
#include <assert.h>
#include <algorithm>


using namespace std;

//��Ŀ������һ�ö�Ԫ�����������ö�Ԫ������ת����һ�������˫������
// Ҫ���ܴ����κ��µĽ�㣬ֻ����ָ���ָ��


struct BSTreeNode // a node in the binary search tree
{
    int          m_nValue; // value of node
    BSTreeNode  *m_pLeft;  // left child of node
    BSTreeNode  *m_pRight; // right child of node
};


//˼·һ�������ǵ���ĳһ���׼�������Ըý��Ϊ����������ʱ��
//�ȵ�������������������ת����һ���ź�������������ٵ�����������ת����������
//�������������������ҽ�㣨������������㣩����ǰ������������������㣨����������С��㣩��
//�����ĸ���㿪ʼ�ݹ�������н�㡣

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

//˼·�������ǿ���������������������������ʽ���������Ƚ�С�Ľ���ȷ��ʡ�
//�������ÿ����һ����㣬����֮ǰ���ʹ��Ľ���Ѿ�������һ������˫������
//�����ٰѵ�����ǰ����ָ�뽫�����ӵ������ĩβ�������н�㶼���ʹ�֮��
//������Ҳ��ת����һ������˫�������ˡ�

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


//��Ŀ������ջ�����ݽṹ��Ҫ�����һ��min�������ܹ��õ�ջ����СԪ�ء�
//Ҫ����min��push�Լ�pop��ʱ�临�Ӷȶ���O(1)��

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


//��Ŀ������һ���������飬������������Ҳ�и�����������������һ�������������һ�������飬
//ÿ�������鶼��һ���͡�������������ĺ͵����ֵ��Ҫ��ʱ�临�Ӷ�ΪO(n)��
//
//�������������Ϊ1, -2, 3, 10, -4, 7, 2, -5��������������Ϊ3, 10, -4, 7, 2��
//������Ϊ��������ĺ�18��

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


//��Ŀ������һ��������һ�ö�Ԫ���������ĸ���㿪ʼ���·���һֱ��Ҷ��������������н���γ�һ��·����
//��ӡ����������������ȵ�����·����

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


//��Ŀ������n�����������������С��k����
//
//��������1��2��3��4��5��6��7��8��8�����֣�����С��4������Ϊ1��2��3��4��

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

//��Ŀ������һ���������飬�жϸ������ǲ���ĳ��Ԫ�������ĺ�������Ľ����
//����Ƿ���true�����򷵻�false��

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

//��Ŀ������һ��Ӣ�ľ��ӣ���ת�����е��ʵ�˳�򣬵��������ַ���˳�򲻱䡣�����е����Կո��������
//Ϊ������������ź���ͨ��ĸһ������
//
//�������롰I am a student.�����������student. a am I����


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

//��Ŀ������һ���Ѿ�������������������һ�����֣��������в�����������
//ʹ�����ǵĺ�������������Ǹ����֡�Ҫ��ʱ�临�Ӷ���O(n)������ж�����ֵĺ͵�����������֣�
//�������һ�Լ��ɡ�

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


//��Ŀ������һ�Ŷ�Ԫ��������������ת��Ϊ���ľ��񣬼���ת����Ķ�Ԫ�������У�
//�������Ľ�㶼�����������Ľ�㡣�õݹ��ѭ�����ַ���������ľ���ת����
//�ݹ�
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

//�ǵݹ�
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


//��Ŀ������һ�Ŷ�Ԫ�����������°����ӡ����ÿ����㣬ͬһ���а��մ������ҵ�˳���ӡ.

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


//��Ŀ����һ���ַ������ҵ���һ��ֻ����һ�ε��ַ���������abaccdeff�������b��

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

//��Ŀ��n�����֣�0,1,��,n-1���γ�һ��ԲȦ��������0��ʼ��
//ÿ�δ����ԲȦ��ɾ����m�����֣���һ��Ϊ��ǰ���ֱ����ڶ���Ϊ��ǰ���ֵ���һ�����֣���
//��һ������ɾ���󣬴ӱ�ɾ�����ֵ���һ������ɾ����m�����֡���������ԲȦ��ʣ�µ����һ�����֡�
//�������������Լɪ������

//˼·һ:������ʵ��
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

//˼·��: 
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

//��Ŀ: O(logn)��Fibonacci����[�㷨]  
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


//��Ŀ�����������������С�����һ�����б�ʾջ��push˳���ж���һ��������û�п����Ƕ�Ӧ��pop˳��
//Ϊ�˼���������Ǽ���push���е����������������ǲ���ȵġ�
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

//��Ŀ������һ������n��������к�Ϊn�����������С�
//
//��������15������1+2+3+4+5=4+5+6=7+8=15���������3����������1-5��4-6��7-8��

//˼·һ: n = (2x + k - 1)*k/2
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

//˼·��: ������������small��big�ֱ��ʾ���е���Сֵ�����ֵ��
//���Ȱ�small��ʼ��Ϊ1��big��ʼ��Ϊ2�������small��big�����еĺʹ���n�Ļ���
//���������ƶ�small���൱�ڴ�������ȥ����С�����֡������small��big�����еĺ�С��n�Ļ���
//���������ƶ�big���൱�������������big����һ�����֡�һֱ��small����(1+n)/2����Ϊ��������Ҫ���������֡�
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

//��Ŀ����C++���һ�����ܱ��̳е��ࡣ
//����̳���Try()ֱ�ӵ���MakeFinal
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
 

//��Ŀ������һ���ַ�������ӡ�����ַ������ַ����������С�
//���������ַ���abc����������ַ�a��b��c�������г����������ַ���abc��acb��bac��bca��cab��cba��

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