#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <windows.h>


using namespace std;

void print(int nElem)
{
	cout << nElem << " ";
}



int Partition(vector<int> &vc, int nLow, int nHigh)
{
	int nTmp;

	nTmp = vc[nLow];
	while (nLow < nHigh)
	{
		while (nLow < nHigh && vc[nHigh] >= nTmp) --nHigh;
		vc[nLow] = vc[nHigh];
		while (nLow < nHigh && vc[nLow] <= nTmp) ++nLow;
		vc[nHigh] = vc[nLow];
	}
	vc[nLow] = nTmp;
	return nLow;
}

void QuickSort(vector<int> &vc, int nLow, int nHigh)
{
	int nMid;

	if (nLow < nHigh)
	{
		nMid = Partition(vc, nLow, nHigh);

		QuickSort(vc, nLow, nMid - 1);
		QuickSort(vc, nMid + 1, nHigh);
	}
}


void MaxHeapAdjust(vector<int> &vc, int nPos, int nSize)
{
	int i;
	int nTmp;

	nTmp = vc[nPos];
	for (i = nPos* 2; i < nSize; i *= 2)
	{
		if (i < nSize && vc[i] < vc[i + 1]) ++i;
		if (vc[i] <= nTmp) break;

		vc[nPos] = vc[i];
		nPos = i;
	}

	vc[nPos] = nTmp;
}

void MakeMaxHeap(vector<int> &vc)
{
	int i;

	for (i = (vc.size()-1)/2; i > 0; --i)
	{
		MaxHeapAdjust(vc, i, vc.size()-1);
	}
}

void SortMaxHeap(vector<int> &vc)
{
	int i, nTmp;

	MakeMaxHeap(vc);

	for (i = vc.size() - 1; i > 0; --i)
	{
		nTmp = vc[1];
		vc[1] = vc[i];
		vc[i] = nTmp;

		MaxHeapAdjust(vc, 1, i - 1);
	}
}

void ShowTime()
{
	SYSTEMTIME systime = {0};
	GetLocalTime(&systime);

	cout << "sec: " << systime.wSecond << "usec: " << systime.wMilliseconds <<endl;
}

/*

int main(int argc, char *argv[])
{
	int i;
	const int nMax = 10000000;
	int nBeginTime, nEndTime;
	vector<int> vc;

	srand(time(NULL));
	for (i = 0; i < nMax; ++i)
	{
		vc.push_back(rand()%nMax);
	}


	//for_each(vc.begin(), vc.end(), print);
	//cout << endl;

	ShowTime();
	QuickSort(vc, 0, vc.size() - 1);
	//SortMaxHeap(vc);
	ShowTime();

	//for_each(vc.begin(), vc.end(), print);
	//cout << endl;

	cout << "quicksort(" << nMax << ") time: " << endl;

	return 0;

}

*/