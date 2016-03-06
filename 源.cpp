//王文奇 四则运算
#include<iostream>
#include<string>
#include<iomanip>
#include <time.h>
using namespace std;

string oper(string op)
{
	int c;	
	c = 1 + rand() % 4;   //产生1~4以内的随机整数
	switch (c)
	{
		case 1:op = "＋"; break;
		case 2:op = "－"; break;
		case 3:op = "×"; break;
		case 4:op = "÷"; break;
	   default:	break;
	}
	return op;
}
void number1()//两个数均为整数
{
	string op;
	int first, second;
	first = rand() % 99;   //产生第一个0~99以内的随机整数
	second = rand() % 99;   //产生第二个0~99以内的随机整数
	cout << setw(3) << first << setw(3) << oper(op) << setw(3) << second << setw(3) << " = " << endl;
}
void number2()//第一个为真分数，第二个为整数
{
	string op;
	int first1, first2, second,temp;
	first1 = rand() % 99;   //产生一个0~99以内的随机整数
	first2 = 1+rand() % 99;   //产生一个1~99以内的随机整数
	if (first1>first2)
	{
		temp = first1;
		first1 = first2;
		first2 = temp;//交换，保证first1<first2,且first2不等于0
	}
	second = rand() % 99;   //产生第二个0~99以内的随机整数
	cout << setw(3) << first1<<"/"<<first2 << setw(3) << oper(op) << setw(3) << second << setw(3) << " = " << endl;
}
void number3()//第一个为整数，第二个为真分数
{
	string op;
	int first, second1, second2, temp;
	first = rand() % 99;   //产生第一个0~99以内的随机整数
	second1 = rand() % 99;   //产生一个0~99以内的随机整数
	second2 = 1 + rand() % 99;   //产生一个1~99以内的随机整数
	if (second1>second2)
	{
		temp = second1;
		second1 = second2;
		second2 = temp;//交换，保证second1<second2,且second2不等于0
	}
	cout << setw(3) << first << setw(3) << oper(op) << setw(3) << second1 << "/" << second2 << setw(3) << " = " << endl;
}
void number4()//两个数均为真分数
{
	string op;
	int  first1, first2, second1, second2, temp;

	first1 = rand() % 99;   //产生一个0~99以内的随机整数
	first2 = 1 + rand() % 99;   //产生一个1~99以内的随机整数
	second1 = rand() % 99;   //产生一个0~99以内的随机整数
	second2 = 1 + rand() % 99;   //产生一个1~99以内的随机整数
	
	if (first1>first2)
	{
		temp = first1;
		first1 = first2;
		first2 = temp;//交换，保证first1<first2,且first2不等于0
	}
	if (second1>second2)
	{
		temp = second1;
		second1 = second2;
		second2 = temp;//交换，保证second1<second2,且second2不等于0
	}
	cout << setw(3) << first1 << "/" << first2 << setw(3) << oper(op) << setw(3) << second1 << "/" << second2 << setw(3) << " = " << endl;
}

void main()
{
	int z,i;	
	srand((unsigned)time(NULL));  //做一个时间种子
	for (i = 0; i < 30; i++)
	{	
		z = 1 + rand() % 4;   //产生1~4以内的随机整数
		cout << "第" << setw(2)<<i + 1 << "题：";
		switch (z)
		{
		    case 1:number1(); break;
			case 2:number2(); break;
			case 3:number3(); break;
			case 4:number4(); break;
			default:	break;
		}		
	}
	
}