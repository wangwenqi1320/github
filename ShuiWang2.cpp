//找水王2
//王文奇 20132980 2016/5/26
#include<iostream>
using namespace std;
int main()
{
	int size = 0;
	int num[3] = { 0 };       //分别用于记录三个小水王的发帖数
	int WaterWang[3];
	cout << "请输入ID个数：";
	cin >> size;
	int *ID = new int[size];

	cout << "请输入ID(请保证三个小水王ID个数大于数量的1/4)：" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> *(ID + i);
	}

	
	//寻找小水王
	for (int i = 0; i < size; i++)
	{
		if (num[0] == 0)
		{
			WaterWang[0] = ID[i];
			num[0]++;
			continue;
		}
		if (ID[i] == WaterWang[0])
		{
			num[0]++;
			continue;
		}
		if (num[1] == 0)
		{
			WaterWang[1] = ID[i];
			num[1]++;
			continue;
		}
		if (ID[i] == WaterWang[1])
		{
			num[1]++;
			continue;
		}
		if (num[2] == 0)
		{
			WaterWang[2] = ID[i];
			num[2]++;
			continue;
		}
		if (ID[i] == WaterWang[2])
		{
			num[2]++;
			continue;
		}

		for (int j = 0; j < 3; j++)
			num[j]--;
	}
	cout << "水王id为：";
	for (int j = 0; j < 3; j++)
		cout << WaterWang[j] << "     ";
	
	delete[] ID;

	return 0;
}