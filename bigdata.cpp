

//第三部分、提取出某日访问百度次数最多的那个IP

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#define N 32

#define ID(x) (x >> 27)
#define VALUE(x) (x&0x07ffffff)
#define MAKE_IP(x,y) ((x<<27)|y)

#define MEM_SIZE 128*1024*1024

void make_data(const int& n, char *data_path)
{
	ofstream out(data_path, ios::out|ios::binary);
	srand((unsigned int)time(NULL));
	if (out)
	{
		for (int i = 0; i < n; ++i)
		{
			unsigned val = (unsigned)rand();
			val = val<<24|val;
			out.write((char *)&val, sizeof(unsigned));
		}
	}
}


void FindMaxIP(const char *pcFile)
{
	fstream arr[N];
	char tmp_path[256];

	for (int i = 0; i < N; ++i)
	{
		sprintf_s(tmp_path, "E:/test/tmp%d.dat", i);
		arr[i].open(tmp_path, ios::trunc|ios::in|ios::out|ios::binary);

		if (!arr[i]) cout << "open file " << i << "error" << endl;
	}

	ifstream infile(pcFile, ios::in|ios::binary);
	unsigned data;

	while (infile.read((char *)(&data), sizeof(data)))
	{
		unsigned val = VALUE(data);
		int key = ID(data);
		arr[key].write((char*)(&val), sizeof(val));
	}

	for (unsigned i = 0; i < N; ++i) arr[i].seekg(0);

	unsigned max_ip = 0, max_times = 0;

	unsigned *count = new unsigned[MEM_SIZE];

	for (unsigned i = 0; i < N; ++i)
	{
		memset(count, 0, sizeof(unsigned)*MEM_SIZE);

		unsigned data;
		while (arr[i].read((char *)(&data), sizeof(unsigned))) ++count[data];

		for (unsigned j = 0; j < MEM_SIZE; ++j)
		{
			if (max_times < count[j])
			{
				max_times = count[j];
				max_ip = MAKE_IP(i, j);
			}
		}
	}

	delete[] count;
	unsigned char *result = (unsigned char *)(&max_ip);
	printf("出现次数最多的IP为:%d.%d.%d.%d , 出现%d次\n", 
		result[0], result[1], result[2], result[3], max_times);
}


int main(void)
{
	char acIPFile[] = "E:\\test\\ip.dat";

	make_data(100000000, acIPFile);

	FindMaxIP(acIPFile);

	return 0;
}