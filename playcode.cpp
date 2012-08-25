/**
*程序员编程艺术第一~二十七章集锦与总结（教你如何编程)
*
*
*
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <algorithm>
#include <time.h>

using namespace std;

/**
*第一章.左旋字符串
*
*/

void ReverseOrder(char *pcStr, int nLen)
{
	char c = NULL;
	int nLow, nHigh;

	nLow = 0;
	nHigh = nLen - 1;
	while (nLow < nHigh)
	{
		c = pcStr[nLow];
		pcStr[nLow] = pcStr[nHigh];
		pcStr[nHigh] = c;
		++nLow;
		--nHigh;
	}
}
//三次逆序
void RotateString1(char *pcStr, int k, int nSize)
{
	ReverseOrder(pcStr, k);
	ReverseOrder(pcStr + k, 4);
	ReverseOrder(pcStr, nSize);
}

int gcd(int n, int m)
{
	int r;

	if (n < m)
	{
		r = n;
		n = m;
		m = r;
	}

	while ((r = m%n) != 0)
	{
		m = n;
		n = r;
	}

	return n;
}

//运用(j + i*m)%n (j = 0-gcd(n,m), i = 0-(n/gcd(n,m) - 1))
void RotateString2(string &str, int m)
{
	int nStrLen, nGcd, nElemInSub, j, i;

	nStrLen = str.length();
	nGcd = gcd(nStrLen, m);
	nElemInSub = nStrLen/nGcd;

	for (j = 0; j < nGcd; ++j)
	{
		char Tmp = str[j];

		for (i = 0; i < nElemInSub - 1; ++i)
		{
			str[(j + i*m)%nStrLen] = str[(j + (i+1)*m)%nStrLen];
		}

		str[(j + i*m)%nStrLen] = Tmp;
	}
}

/**
*第二张.字符串是否包含及相关问题扩展 
*
*/

/*
*假设这有一个各种字母组成的字符串，假设这还有另外一个字符串，
*而且这个字符串里的字母数相对少一些。从算法是讲，
*什么方法能最快的查出所有小字符串里的字母在大字符串里都有？
*
*/

int  IsExistEveryChar1(string &ls, string &ss)
{
	int i, index, nums = 0;
	int nArray[26] = {0};

	for (i = 0; i < ss.length(); ++i)
	{
		index = ss[i] - 'A';
		if (nArray[index] == 0)
		{
			nArray[index] = 1;
			++nums;
		}
	}

	for (i = 0; i < ls.length(); ++i)
	{
		index = ls[i] - 'A';
		if (nArray[index] == 1)
		{
			if (--nums == 0) break;
		}
	}

	return (i < ls.length()) ?0:-1;	
}

//每个字符对应一个素数
int  IsExistEveryChar2(string &ls, string &ss)
{
	int i, index;
	int primeNumber[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

	long long product = 1;

	for (i = 0; i < ls.length(); ++i)
	{
		index = ls[i] - 'A';
		product *= primeNumber[index];
	}

	for (i = 0; i < ss.length(); ++i)
	{
		index = ss[i] - 'A';
		if (product % primeNumber[index] != 0) return -1;
	}
	return 0;
}

/**
*字符串匹配e.g: ABCDE--CD
*/
char* MyStrStr(char *pcStr, char *pcSubStr)
{
	char *p = NULL, *pSub = NULL;

	p = pcStr;
	pSub = pcSubStr;
	while (*p != '\0' && *pSub != '\0')
	{
		if (*p == *pSub)
		{
			++p;
			++pSub;
		}
		else
		{
			p -= (pSub - pcSubStr - 1);
			pSub = pcSubStr;
		}
	}
	return (*pSub == '\0')? p - strlen(pcSubStr): NULL;
}

/**
*字符串拷贝
*/

char* mystrcpy(char *pcDest, const char *pcSrc)
{
	if (pcSrc == NULL || pcDest == NULL) return NULL;

	char *pcAddr = pcDest;
	while ((*pcDest++ = *pcSrc++) != '\0');

	return pcAddr;
}

/**
*字符串全排列
*
*/

void SwapChar(char *pcDest, char *pcSrc)
{
	char tmp;

	if (pcDest == NULL || pcSrc == NULL) return;
	tmp = *pcSrc;
	*pcSrc = *pcDest;
	*pcDest = tmp;
}

void StrArrange(char *pcStr, char *pcBegin)
{
	if (*pcBegin == '\0')
	{
		cout << pcStr << " ";
		return;
	}

	for (char *pcPos = pcBegin; *pcPos != '\0'; ++pcPos)
	{
		SwapChar(pcBegin, pcPos);
		StrArrange(pcStr, pcBegin + 1);
		SwapChar(pcBegin, pcPos);
	}
}

/**
*字符串的所有组合
*/
void StrCombination(char *pcStr, char *pcDest)
{
	char acDest1[32] = {0}, acDest2[32] = {0};

	if (*pcStr == '\0')
	{
		cout << pcDest << " ";
		return;
	}

	strcpy_s(acDest1, pcDest);
	strcpy_s(acDest2, pcDest);
	acDest1[strlen(acDest1)] = *pcStr;

	StrCombination(pcStr+1, acDest1);
	StrCombination(pcStr+1, acDest2);
}

/**
*第三章.topk问题
*
*/


//快速排序的一次划分(选择第一个元素作为划分值)
int Partition(int *pnArray, int nBegin, int nEnd)
{
	int nValue;

	nValue = pnArray[nBegin];
	while (nBegin < nEnd)
	{
		while (pnArray[nEnd] >= nValue) --nEnd;
		pnArray[nBegin] = pnArray[nEnd];
		while (pnArray[nBegin] <= nValue) ++nBegin;
		pnArray[nEnd] = pnArray[nBegin];
	}

	pnArray[nBegin] = nValue;
	return nBegin;
}

int SwapInt(int *p, int *q)
{
	int tmp;

	if (p == NULL || q == NULL) return -1;
	tmp = *p;
	*p = *q;
	*q = tmp;

	return 0;
}

//随机划分
int RandomizedPartition(int *pnArray, int nBegin, int nEnd)
{
	int nRand;

	srand(time(NULL));
	nRand = (rand()%(nEnd - nBegin)) + nBegin;

	SwapInt(pnArray, pnArray + nRand);

	return Partition(pnArray, nBegin, nEnd);
}


//随机选择第K小的元素

int RandomizedSelect(int *pnArray, int nBegin, int nEnd, int k)
{
	int q;

	if (nBegin > nEnd) return -1;
	if (nBegin == nEnd) return pnArray[nBegin];
	q = RandomizedPartition(pnArray, nBegin, nEnd);
	if (k == q) return pnArray[q];
	else if (k < q) return RandomizedSelect(pnArray, nBegin, q - 1, k);
	else if (k > q) return RandomizedSelect(pnArray, q + 1, nEnd, k - q);

	return -1;
}


void printarray(int *pnArray, int size)
{
	int i;

	for (i = 0; i < size; ++i)
	{
		cout << pnArray[i] << " ";
	}
	cout << endl;
}


//用堆排序得到最小的K个数
void HeapAdjust(int *pnArray, int i, int size)
{
	int child, tmp;

	for (tmp = pnArray[i]; 2*i + 1 < size; i = child)
	{
		child = 2 * i + 1;
		if (child < size-1 && pnArray[child] > pnArray[child + 1]) ++child;

		if (tmp > pnArray[child]) pnArray[i] = pnArray[child];
		else break;

		pnArray[child] = tmp;
	}
}

void MakeMinHeap(int *pnArray, int size)
{
	int i;

	for (i = size/2; i >= 0; --i)
	{
		HeapAdjust(pnArray, i, size);
	}
}

int GetHeapMin(int *pnArray, int size, int k)
{
	int i, h, min, tmp, child;

	min = pnArray[0];
	SwapInt(pnArray, pnArray + size - 1);

	h = k - 1;
	i = 0;
	for (tmp = pnArray[0];h > 0 && 2*i + 1 < size; --h, i = child)
	{
		child = 2 * i + 1;
		if (child >= size-1) break;
		if (pnArray[child] > pnArray[child + 1]) ++child;

		if (tmp > pnArray[child]) pnArray[i] = pnArray[child];
		else break;

		pnArray[child] = tmp;
	}

	return min;
}

void GetKMin(int *pnArray, int size, int k)
{
	int i;

	MakeMinHeap(pnArray, size);

	for (i = 0; i < k; ++i)
	{
		int min = GetHeapMin(pnArray, size - i, k - i);

		cout << min << " ";
	}

	cout << endl;
}

/**
*第六章.求500w内的亲和数
*亲和数: m和n为亲和数，则m的真因子之和为n, n的真因子之和为m;
*/

void QinNum(unsigned int n)
{
	int i, j;
	int *sum = NULL;

	if ((sum = (int *)malloc(n*sizeof(int))) == NULL) return;
	for (i = 0; i < n; ++i) sum[i] = 1;

	for (i = 2; i*2 < n; ++i)
	{
		j = 2*i;
		while (j < n)
		{
			sum[j] += i;
			j += i;
		}
	}

	for (i = 2; i < n; ++i)
	{
		if (sum[i] > i && sum[i] < n && sum[sum[i]] == i)
		{
			cout << sum[i] << " " << i << endl;
		}
	}
	free(sum);
}
/**
*第七章.求连续子数组的最大和
*
*/
int MaxSum(int *a, int size)
{
	int i, sum, tmp;

	sum = 0;
	tmp = 0;
	for (i = 0; i < size; ++i)
	{
		if (tmp < 0) tmp = a[i];
		else tmp += a[i];

		if (sum < tmp) sum = tmp;
	}

	return 0;
}


/**
*第八章.探讨虚函数
*/

class Base 
{ 
private: 
	virtual void f() 
	{
		cout << "Base::f" << endl; 
	} 
};
class Derive : public Base
{
}; 

typedef void(*Fun)(void);


/**
*第九章.链表问题
*1.判断链表是否有环——快慢链表指针
*2.判断链表是否相交
*3.找出相交的第一个点
*
*/

//第十二 ~十五章：中签概率， IP 访问次数，回文等
//第二部分、遍历 n个元素取出等 概率随机取出其中之一元素

//伪代码 
//Element RandomPick(file): 
//	Int length = 1; 
//	While( length <= file.size )
//	{
//		If( rand() % length == 0) 
//			Picked = File[length];
//		Length++;
//	}
//	Return picked















/*
int main(int argc, char *argv[])
{
	//int anArray[] = {2, 3, 5, 8, 7, 6, 1, 4, 9};

	//GetKMin(anArray, 9, 5);

	//cout << endl;

//	QinNum(5000000);

	Derive d;
	Fun pFun = (Fun)*((int*)*(int*)(&d)+0);

	pFun();
	return 0;
}

*/

/*

void CreateSuffixArray(uchar* szText, int L, int** _S, int** _R, int** _T1, int** _T2)
{
     int i, h, h2, *T, *S1, *S2, *R, *B;

     S1 = *_S;       // h阶后缀数组
     S2 = *_T1;      // 2h阶后缀数组
     R = *_R;        // h阶Rank数组
     B = *_T2;       // 某个桶空余空间尾部的索引，兼任2h阶Rank数组

     // 花O(n)的时间对h = 1进行计数排序
     for(i = 0; i < 256; i++) B = 0;
     for(i = 0; i < L; i++) B[szText]++;
     for(i = 1; i < 256; i++) B += B[i - 1];
     for(i = 0; i < L; i++) S1[--B[szText]] = i;

    // 计算Rank(1)，因为仅仅是1阶的Rank，所有有并列的
     for(R[S1[0]] = 0, i = 1; i < L; i++)
    {
       if(szText[S1] == szText[S1[i - 1]])
            R[S1] = R[S1[i - 1]];
        else
            R[S1] = R[S1[i - 1]] + 1;
    }

    // log(n)趟O(n)的倍增排序
    // SA(h) => Rank(h) => SA(2h) => Rank(2h) => …
32
33     for(h = 1; h < L && R[S1[L - 1]] < L - 1; h <<= 1)
34     {
35         // 计算Rank(h)相同的后缀形成的h桶尾部的索引
36         // 即有多少个后缀的h前缀相同，它们被放在一个桶中
37         for(i = 0; i < L; i++)
38             B[R[S1]] = i;
39
40         // 求SA(2h)
41         // 在同一个h桶中，所有的后缀的h前缀肯定相同，
42         // 那么比较他们的2h前缀，只要比较其2h前缀后半的
43         // 长度为h的串即可，而这个串恰恰是后面某个后缀的
44         // h前缀，所以我们逆向遍历有序的SA(h)，
45         // 将S1 – h号前缀放到它所在桶的最后一个空位置，
46         // 同时，桶尾前进一个位置，这样即形成了2h桶排序
47         for(i = L – 1; i >= 0; i–)
48             if(h <= S1)
49                 S2[B[R[S1 - h]]–] = S1 – h;
50
51         // 对于长度不超过h的最后几个后缀，由于在h阶段
52         // 它们每个实际上都已经独立分桶了(长度为h的也是)
53         // 而且他们的桶中有且仅有一个元素，
54         // 所以只要直接复制他们h阶段的SA值就可以了
55         // 同时，由于采用滚动数组，所以S2中“残留”了
56         // h/2个有效的数据，所以最终我们只需复制h/2个数据
57         for(i = L – h, h2 = L – (h >> 1); i < h2; i++)
58             S2[B[R]] = i;
59
60         T = S1; S1 = S2; S2 = T;
61
62         // 计算Rank(2h)
63         // 2h阶段是否要分桶只需看相邻两个2h前缀前后两半
64         // h前缀是否全部h阶相等
65         for(B[S1[0]] = 0, i = 1; i < L; i++)
66         {
67             // 这里不用考虑S1 + h会越界
68             // 如果i达到了S1 + h越界的数值，
69             // 那么前面一个条件显然不会满足了
70             // 因为此时i前缀肯定已经独立分桶了
71             if(R[S1] != R[S1[i - 1]] ||
72                 R[S1 + h] != R[S1[i - 1] + h])
73             {
74                 B[S1] = B[S1[i - 1]] + 1;
75             }
76             else
77                 B[S1] = B[S1[i - 1]];
78         }
79
80         T = B; B = R; R = T;
81     }
82
83     if(*_S != S1)
84         *_S = S1, *_T1 = S2;
85     if(*_R != R)
86         *_R = R, *_T2 = B;
87 }



const int N = 20005;//串A的最大长度  
const int MAX = 1000100;//串A的最大值  
//int n,m,k;  
int SA[N], rank[N], height[N], key[N];  
int A[N], C[MAX], t1[N+1], t2[N+1];  
  
//倍增法求sa[]-----待排序的字符串放在r 数组中，r[]为整型数组, 从r[0]到r[n-1]，长度为n，且最大值小于m  
//约定除r[n-1]外所有的r[i]都大于0, r[n-1]=0  
//结果放在sa 数组中，从sa[0]到sa[n-1]  
//先对所有后缀的第一个字符进行排序(采用挖坑式的基数排序,即统计每个字符的个数,以便在扫描时总能将字符放入合适的位置),放入sa中  

void da(int n, int m)  
{  
    int i, j, l, s,*t;  
    int *X = t1, *Y = t2;

    memset(C, 0, sizeof(C));

    for (i=0; i < n; i++) C[X[i] = A[i]]++;
    for (i=1; i < m; i++) C[i] += C[i-1];
    for (i=n-1; i >= 0; i--) SA[--C[X[i]]] = i;

    for (l=1; l<n; l<<=1)
    {  
        for (i=n-l,j=0;i<n;i++) Y[j++] = i;
        for (i=0;i<n;i++) if (SA[i] >= l) Y[j++] = SA[i] - l;
        for (i=0;i<n;i++) key[i] = X[Y[i]];
        memset(C, 0, sizeof(C));
        for (i=0;i<n;i++) C[key[i]]++;
        for (i=1;i<m;i++) C[i] += C[i-1];
        for (i=n-1;i>=0;i--) SA[--C[key[i]]] = Y[i];
        t = X;
        X = Y;
        Y = t;
        X[SA[0]] = j = 0;
        for (i=1;i<n;i++)
        {
            if (Y[SA[i]] != Y[SA[i-1]] || Y[SA[i]+l] != Y[SA[i-1]+l])
                j++;
            X[SA[i]] = j;
        }
        m = j + 1;
        if (m==n) break;
    }

    for (i=0;i<n;i++)
        rank[SA[i]] = i;
    return;
}
  
//height[i]:suffix(sa[i-1])与suffix(sa[i])的最长公共前缀，即排名相邻的两个后缀的最长公共前缀  
void calheight(int n)  
{  
    int i,j,k=0;  
    for(i=0; i<n; i++)  
    {  
        if (k > 0)  
            --k;  
        if(rank[i] == 0)  
            height[0] = 0;  
        else  
        {  
            j = SA[rank[i] - 1];  
            while(A[i+k] == A[j+k])  
                k++;  
            height[rank[i]] = k;  
        }  
    }  
} 


void main(void)
{
	int i;
	//串A[0]...A[n-1]

	for (i = 0; i < 10; ++i)
	{
		A[i] = 'a' + i;
	}

	A[3] = 'f';

	da(10,1000001);  //m的最大值不超过1,000,000  

	for (i = 0; i < 10; ++i)
	{
		printf("%d ", SA[i]);
	}

	printf("\n");

	calheight(10);  
}

*/