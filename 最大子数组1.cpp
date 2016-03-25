//求一维数组的最大子数组 王文奇 缪金敏 2016/3/23
#include<iostream>
using namespace std;

int max(int a,int b)   //返回a和b中的最大值
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
	    int Array[100];
		int i = 1;
		int dynamic_planning[100][2], j, sum;
	    int start = 0;                   //最大子数组的起始位置  
		int end = 0;                    //最大子数组的终止位置  
		cout << "请输入一组一维数组(回车结束)："<<endl;
		cin >> Array[0];
		while (cin.get() != '\n') //回车结束
		{
			cin >> Array[i++];
		}
		//动态规划数组初始化
		dynamic_planning[0][0] = 0;
		dynamic_planning[0][1] = Array[0];
		for (j = 1; j<i; j++)
		{
			dynamic_planning[j][0] = max(dynamic_planning[j - 1][0], dynamic_planning[j - 1][1]);
			dynamic_planning[j][1] = max(Array[j], (dynamic_planning[j - 1][1] + Array[j]));
			//开始下标的条件：数组第二列的数前一个比现在的小且小于0且第一列的数小于等于第二列
			if (dynamic_planning[j - 1][1] < dynamic_planning[j][1] && dynamic_planning[j - 1][1]<0&&dynamic_planning[j][0]<=dynamic_planning[j][1])
			{ 
				start = j;
				//cout << "start:"<<start << endl;
			}
			//结束下标的条件1：当前的算出的最大子数组+输入的值比下一步的最大值大于或等于
			if (dynamic_planning[j - 1][1] >= dynamic_planning[j][0])
			{
				end = j - 1;
				//cout << "end:" << end << endl;
			}
			//结束下标的条件2：第二列的数大于等于第一列
			if (dynamic_planning[j][1] >= dynamic_planning[j][0])
			{
				end = j;
				//cout << "end:" << end << endl;
			}
			
		}
		//cout << start << " " << end << endl;
		sum = max(dynamic_planning[i - 1][0], dynamic_planning[i - 1][1]);
		cout << "最大的子数组为：" << endl;
		 for (int i = start; i <= end; i++)
		 {
			 cout << Array[i] << " ";
		 } 
		 cout << endl;
		 cout << "最大的子数组的和为：" << sum << endl;
	    return 0;
}