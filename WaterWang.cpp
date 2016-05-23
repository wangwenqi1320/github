//找水王
//王文奇 20132980 2016/5/16
#include<iostream>
using namespace std;
int main()
{
	int size = 0;
	int num = 1; //当前判定为水王ID重复的次数
	int WaterWang;
	cout << "请输入ID个数：";  
	cin >> size;
	int *ID = new int[size];

	cout << "请输入ID(请保证水王ID个数大于数量的一半)：" << endl;
	for (int i = 0; i < size; i++)
	{
		cin >> *(ID + i);
	}

	WaterWang = ID[0]; //一开始默认为数组中的第一个数为水王
	for (int i = 1; i<size; i++)
	{
		if (WaterWang != ID[i])     //两两不同时舍弃
		{
			num = num - 1;   //水王次数减一
			if (num <= 0)    //当水王次数降至0以下时
			{
				WaterWang = ID[i + 1];   //暂定下一个数为新水王
				num = 1;  //水王次数重新赋为一
				i++;   //跳过ID[i]的判断
			}
		}
		else                     //两两相同时暂定为水王
		{
			WaterWang = ID[i];
			num = num + 1;   //水王次数加一
		}
	}	
	cout << "水王id为：" << WaterWang << endl;	
	delete[] ID;

	return 0;
}