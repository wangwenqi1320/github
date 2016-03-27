//求一维数组的最大子数组2 王文奇 缪金敏 2016/3/26
#include<iostream>
using namespace std;

int max(int a, int b)   //返回a和b中的最大值
{
	if (a > b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int main()
{
	int Array[10000];
	int i = 1;
	int dynamic_planning[10000][2], j, sum[10000];
	int start[10000] = { 0 };                   //最大子数组的起始位置  
	int end[10000] = { 0 };                    //最大子数组的终止位置  
	cout << "请输入一组一维数组(回车结束)：" << endl;
	cin >> Array[0];
	while (cin.get() != '\n') //回车结束
	{
		cin >> Array[i++];
	}
	for (j = i; j < 2 * i; j++) //数组末尾再生成了一遍
	{
		Array[j] = Array[j - i];
	}
	int n = 0;

	//动态规划数组初始化
	while (true){
		dynamic_planning[0][0] = 0;
		dynamic_planning[0][1] = Array[n];
		for (j = 1; j<i; j++)
		{
			dynamic_planning[j][0] = max(dynamic_planning[j - 1][0], dynamic_planning[j - 1][1]);
			dynamic_planning[j][1] = max(Array[j + n], (dynamic_planning[j - 1][1] + Array[j + n]));
			//开始下标的条件：数组第二列的数前一个比现在的小且小于0且第一列的数小于等于第二列
			if (dynamic_planning[j - 1][1] < dynamic_planning[j][1] && dynamic_planning[j - 1][1]<0 && dynamic_planning[j][0] <= dynamic_planning[j][1])
			{
				start[n] = j + n;
				//cout << "start:"<<start << endl;
			}
			//结束下标的条件1：当前的算出的最大子数组+输入的值比下一步的最大值大于或等于
			if (dynamic_planning[j - 1][1] >= dynamic_planning[j][0])
			{
				end[n] = j - 1 + n;
				//cout << "end:" << end << endl;
			}
			//结束下标的条件2：第二列的数大于等于第一列
			if (dynamic_planning[j][1] >= dynamic_planning[j][0])
			{
				end[n] = j + n;
				//cout << "end:" << end << endl;
			}

		}
		sum[n] = max(dynamic_planning[i - 1][0], dynamic_planning[i - 1][1]);
		n++;
		if (n == i)
		{
			break;
		}
	}
	int max = sum[0];
	n = 0;
	for (j = 0; j < i; j++)
	{
		if (sum[j]>max)
		{
			max = sum[j];
			n = j;
		}
	}
	cout << "最大的子数组为：" << endl;
	if (start[n] <= end[n])
	{
		for (j = start[n]; j <= end[n]; j++)
		{
			cout << Array[j] << " ";
		}
	}
	else
	{
		for (j = start[n]; j < i; j++)
		{
			cout << Array[j] << " ";
		}
		for (j = 0; j <= end[n]; j++)
		{
			cout << Array[j] << " ";
		}
	}
	cout << endl;
	cout << "起始索引： " << start[n];
	if (end[n] >= i)
		cout << "终止索引： " << end[n] - i;
	else
		cout << "终止索引： " << end[n];
	cout << endl;
	//cout << start << " " << end << endl;

	cout << "最大的子数组的和为：" << sum[n] << endl;
	return 0;
}