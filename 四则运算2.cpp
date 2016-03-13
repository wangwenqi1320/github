//王文奇 四则运算2
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>
#include <time.h>
using namespace std;
#define maxN 100 //设置最大缓冲区个数

int MulDlvIsExist; //是否有乘除法
int AddSubIsNeg;//加减是否有负数
int DlvIsRem;//除法是否有余数
int min;  //最小数
int max; //最大数
int N;//输出题目的个数
int first, second;
double result;
stringstream ss; //设置一个算式的缓冲区
string buffer[maxN] ;//设置所有算式的缓冲区
int print;   //打印方式

string oper(string op)
{
	int c;
	c = 1 + rand() % 4;   //产生1~4以内的随机整数
	if (MulDlvIsExist == 1)//有乘除法
	{
		c = 1 + rand() % 4;   //产生1~4以内的随机整数
	}
	else //默认无乘除法
	{
		c = 1 + rand() % 2;   //产生1~2以内的随机整数
	}
	switch (c)
	{
		case 1:op = "＋";break;
		case 2:op = "－"; break;
		case 3:op = "×"; break;
		case 4:op = "÷"; break;
		default:	break;
	}

	return op;
}

void equation()  //生成一个基础算式
{
	string op;
	
	int temp;
	first = min+rand() % (max-min+1);   //产生第一个min~max以内的随机整数
	second = min + rand() % (max - min +1);   //产生第二个min~max以内的随机整数
	op=oper(op);
	if (AddSubIsNeg == 0 && op == "－"&&first<second)//无负数,即不让出现小减大的情况
	{
		temp = first;
		first = second;
		second = temp;//交换
	}
	while (op == "÷"&&second == 0)    //除数不能为0
	{		
		second = min + rand() % (max - min + 1);   //产生第二个min~max以内的随机整数
	}
	if (DlvIsRem == 0)
	{
		while (op == "÷" && (first%second != 0))    //无余数,即第一个与第二个数取余必须为0
		{
			first = min + rand() % (max - min + 1);   //产生第一个min~max以内的随机整数
			second = min + 1 + rand() % (max - min + 1);   //产生第二个min+1~max以内的随机整数		
		}
	}	
	//cout << setw(3) << first << setw(3) <<op<< setw(3) << second << setw(3);
	ss << setw(3) << first << setw(3) << op << setw(3) << second << setw(3);
}

void equationN(int bracketNum)  //递归实现加括号
{
	string op;
    if (bracketNum <= 0)
	{
		equation();
		//cout << "=" << endl;	
		ss << "=" << endl;
	}
	else if (bracketNum > 0)
	{
		//cout << "(";
		ss << "(";
		equation();
		//cout << ")";	
		ss << ")";
		op=oper(op);
		 if (bracketNum >= 1)
		{
			//cout << op;
			ss << op;
		}		
		bracketNum--;
		equationN(bracketNum);		
	}		
}

void equationNo(int bracketNum)  //递归实现无括号
{
	string op;
	if (bracketNum <= 0)
	{
		equation();
		//cout << "=" << endl;
		ss << "=" << endl;
	}
	else if (bracketNum > 0)
	{		
		equation();	
		if (bracketNum >= 1)
		{
			//cout << oper(op);
			ss << oper(op);
		}
		bracketNum--;
		equationNo(bracketNum);
	}
}

bool repeat(string ss1, int i)  //判断是否重复，重复返回true，不重复返回false
{
	bool flag = true;//默认是重复的
	int j;
	for (j = 0; j < i; j++)
	{
		if (ss1 == buffer[j])
		{
			flag = true;
			break;
		}
		else
		{
			flag = false;
		}
	}
	return flag;
}

void main()
{
	int bracket,bracketNum,Num;
	srand((unsigned)time(NULL));  //做一个时间种子
	cout << "请输入是否有乘除法（0、无  1、有）：" << endl;
	cin >> MulDlvIsExist;
	cout << "请输入是否有无括号（0、无  1、有）：" << endl;
	cin >> bracket;
	cout << "请输入数值范围（请先输入最小数，再输入最大数，请保证两个数均为大于等于0的数！）：" << endl;
	cin >> min>>max;
	cout << "请输入加减结果是否有负数（0、无  1、有）：" << endl;
	cin >> AddSubIsNeg;
	if (MulDlvIsExist == 1)
	{
		cout << "请输入乘除结果是否有余数（0、无  1、有）：" << endl;
		cin >> DlvIsRem;
	}	

	cout << "请输入题目的个数：" << endl;
	cin >> N;
	cout << "请选择打印的方式（0、输出到文本  1、屏幕打印）：" << endl;
	cin >> print;
	if (print == 1)
	{
		for (int i = 0; i < N; i++)
		{
			bracketNum = 1 + rand() % 4;   //产生1~4以内的随机整数,作为括号个数
			Num = 0 + rand() % 4;   //产生0~4以内的随机整数，加1乘2作为操作数的个数
			cout << "第" << setw(2) << i + 1 << "题：";
			if (bracket == 1)//有括号
			{
				equationN(bracketNum);
				while (repeat(ss.str(), i) && (i>0))//当他重复时且不是第一个时循环，直到不重复为止
				{
					ss.str("");
					equationN(bracketNum);
				}
				buffer[i] = ss.str();
				cout << ss.str();
				ss.str("");//清空ss的缓冲区
			}
			else//默认无括号
			{
				equationNo(Num);
				while (repeat(ss.str(), i) && (i>0))//当他重复时且不是第一个时循环，直到不重复为止
				{
					ss.str("");
					equationNo(Num);
				}
				buffer[i] = ss.str();
				cout << ss.str();
				ss.str("");//清空ss的缓冲区
			}

		}

	}
	else if (print == 0)
	{
		string file;
		cout << "请输入输出文件格式：（如：D:\\print.txt）" << endl;
		cin >> file;
		ofstream outfile(file, ios::out);
		if (!outfile)
		{
			cerr << "创建失败!" << endl;
			exit(1);
		}

		for (int i = 0; i < N; i++)
		{
			bracketNum = 1 + rand() % 4;   //产生1~4以内的随机整数,作为括号个数
			Num = 0 + rand() % 4;   //产生0~4以内的随机整数，加1乘2作为操作数的个数
			outfile << "第" << setw(2) << i + 1 << "题：";
			if (bracket == 1)//有括号
			{
				equationN(bracketNum);
				while (repeat(ss.str(), i) && (i>0))//当他重复时且不是第一个时循环，直到不重复为止
				{
					ss.str("");
					equationN(bracketNum);
				}
				buffer[i] = ss.str();
				outfile << ss.str();
				ss.str("");//清空ss的缓冲区
			}
			else//默认无括号
			{
				equationNo(Num);
				while (repeat(ss.str(), i) && (i>0))//当他重复时且不是第一个时循环，直到不重复为止
				{
					ss.str("");
					equationNo(Num);
				}
				buffer[i] = ss.str();
				outfile << ss.str();
				ss.str("");//清空ss的缓冲区
			}
		}
		
		outfile.close();

	}

}