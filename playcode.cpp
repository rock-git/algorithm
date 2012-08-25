/**
*����Ա���������һ~��ʮ���¼������ܽᣨ������α��)
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
*��һ��.�����ַ���
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
//��������
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

//����(j + i*m)%n (j = 0-gcd(n,m), i = 0-(n/gcd(n,m) - 1))
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
*�ڶ���.�ַ����Ƿ���������������չ 
*
*/

/*
*��������һ��������ĸ��ɵ��ַ����������⻹������һ���ַ�����
*��������ַ��������ĸ�������һЩ�����㷨�ǽ���
*ʲô���������Ĳ������С�ַ��������ĸ�ڴ��ַ����ﶼ�У�
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

//ÿ���ַ���Ӧһ������
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
*�ַ���ƥ��e.g: ABCDE--CD
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
*�ַ�������
*/

char* mystrcpy(char *pcDest, const char *pcSrc)
{
	if (pcSrc == NULL || pcDest == NULL) return NULL;

	char *pcAddr = pcDest;
	while ((*pcDest++ = *pcSrc++) != '\0');

	return pcAddr;
}

/**
*�ַ���ȫ����
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
*�ַ������������
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
*������.topk����
*
*/


//���������һ�λ���(ѡ���һ��Ԫ����Ϊ����ֵ)
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

//�������
int RandomizedPartition(int *pnArray, int nBegin, int nEnd)
{
	int nRand;

	srand(time(NULL));
	nRand = (rand()%(nEnd - nBegin)) + nBegin;

	SwapInt(pnArray, pnArray + nRand);

	return Partition(pnArray, nBegin, nEnd);
}


//���ѡ���KС��Ԫ��

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


//�ö�����õ���С��K����
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
*������.��500w�ڵ��׺���
*�׺���: m��nΪ�׺�������m��������֮��Ϊn, n��������֮��Ϊm;
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
*������.�����������������
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
*�ڰ���.̽���麯��
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
*�ھ���.��������
*1.�ж������Ƿ��л�������������ָ��
*2.�ж������Ƿ��ཻ
*3.�ҳ��ཻ�ĵ�һ����
*
*/

//��ʮ�� ~ʮ���£���ǩ���ʣ� IP ���ʴ��������ĵ�
//�ڶ����֡����� n��Ԫ��ȡ���� �������ȡ������֮һԪ��

//α���� 
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

     S1 = *_S;       // h�׺�׺����
     S2 = *_T1;      // 2h�׺�׺����
     R = *_R;        // h��Rank����
     B = *_T2;       // ĳ��Ͱ����ռ�β��������������2h��Rank����

     // ��O(n)��ʱ���h = 1���м�������
     for(i = 0; i < 256; i++) B = 0;
     for(i = 0; i < L; i++) B[szText]++;
     for(i = 1; i < 256; i++) B += B[i - 1];
     for(i = 0; i < L; i++) S1[--B[szText]] = i;

    // ����Rank(1)����Ϊ������1�׵�Rank�������в��е�
     for(R[S1[0]] = 0, i = 1; i < L; i++)
    {
       if(szText[S1] == szText[S1[i - 1]])
            R[S1] = R[S1[i - 1]];
        else
            R[S1] = R[S1[i - 1]] + 1;
    }

    // log(n)��O(n)�ı�������
    // SA(h) => Rank(h) => SA(2h) => Rank(2h) => ��
32
33     for(h = 1; h < L && R[S1[L - 1]] < L - 1; h <<= 1)
34     {
35         // ����Rank(h)��ͬ�ĺ�׺�γɵ�hͰβ��������
36         // ���ж��ٸ���׺��hǰ׺��ͬ�����Ǳ�����һ��Ͱ��
37         for(i = 0; i < L; i++)
38             B[R[S1]] = i;
39
40         // ��SA(2h)
41         // ��ͬһ��hͰ�У����еĺ�׺��hǰ׺�϶���ͬ��
42         // ��ô�Ƚ����ǵ�2hǰ׺��ֻҪ�Ƚ���2hǰ׺����
43         // ����Ϊh�Ĵ����ɣ��������ǡǡ�Ǻ���ĳ����׺��
44         // hǰ׺����������������������SA(h)��
45         // ��S1 �C h��ǰ׺�ŵ�������Ͱ�����һ����λ�ã�
46         // ͬʱ��Ͱβǰ��һ��λ�ã��������γ���2hͰ����
47         for(i = L �C 1; i >= 0; i�C)
48             if(h <= S1)
49                 S2[B[R[S1 - h]]�C] = S1 �C h;
50
51         // ���ڳ��Ȳ�����h����󼸸���׺��������h�׶�
52         // ����ÿ��ʵ���϶��Ѿ�������Ͱ��(����Ϊh��Ҳ��)
53         // �������ǵ�Ͱ�����ҽ���һ��Ԫ�أ�
54         // ����ֻҪֱ�Ӹ�������h�׶ε�SAֵ�Ϳ�����
55         // ͬʱ�����ڲ��ù������飬����S2�С���������
56         // h/2����Ч�����ݣ�������������ֻ�踴��h/2������
57         for(i = L �C h, h2 = L �C (h >> 1); i < h2; i++)
58             S2[B[R]] = i;
59
60         T = S1; S1 = S2; S2 = T;
61
62         // ����Rank(2h)
63         // 2h�׶��Ƿ�Ҫ��Ͱֻ�迴��������2hǰ׺ǰ������
64         // hǰ׺�Ƿ�ȫ��h�����
65         for(B[S1[0]] = 0, i = 1; i < L; i++)
66         {
67             // ���ﲻ�ÿ���S1 + h��Խ��
68             // ���i�ﵽ��S1 + hԽ�����ֵ��
69             // ��ôǰ��һ��������Ȼ����������
70             // ��Ϊ��ʱiǰ׺�϶��Ѿ�������Ͱ��
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



const int N = 20005;//��A����󳤶�  
const int MAX = 1000100;//��A�����ֵ  
//int n,m,k;  
int SA[N], rank[N], height[N], key[N];  
int A[N], C[MAX], t1[N+1], t2[N+1];  
  
//��������sa[]-----��������ַ�������r �����У�r[]Ϊ��������, ��r[0]��r[n-1]������Ϊn�������ֵС��m  
//Լ����r[n-1]�����е�r[i]������0, r[n-1]=0  
//�������sa �����У���sa[0]��sa[n-1]  
//�ȶ����к�׺�ĵ�һ���ַ���������(�����ڿ�ʽ�Ļ�������,��ͳ��ÿ���ַ��ĸ���,�Ա���ɨ��ʱ���ܽ��ַ�������ʵ�λ��),����sa��  

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
  
//height[i]:suffix(sa[i-1])��suffix(sa[i])�������ǰ׺�����������ڵ�������׺�������ǰ׺  
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
	//��A[0]...A[n-1]

	for (i = 0; i < 10; ++i)
	{
		A[i] = 'a' + i;
	}

	A[3] = 'f';

	da(10,1000001);  //m�����ֵ������1,000,000  

	for (i = 0; i < 10; ++i)
	{
		printf("%d ", SA[i]);
	}

	printf("\n");

	calheight(10);  
}

*/