//������ ��������
#include<iostream>
#include<string>
#include<iomanip>
#include <time.h>
using namespace std;

string oper(string op)
{
	int c;	
	c = 1 + rand() % 4;   //����1~4���ڵ��������
	switch (c)
	{
		case 1:op = "��"; break;
		case 2:op = "��"; break;
		case 3:op = "��"; break;
		case 4:op = "��"; break;
	   default:	break;
	}
	return op;
}
void number1()//��������Ϊ����
{
	string op;
	int first, second;
	first = rand() % 99;   //������һ��0~99���ڵ��������
	second = rand() % 99;   //�����ڶ���0~99���ڵ��������
	cout << setw(3) << first << setw(3) << oper(op) << setw(3) << second << setw(3) << " = " << endl;
}
void number2()//��һ��Ϊ��������ڶ���Ϊ����
{
	string op;
	int first1, first2, second,temp;
	first1 = rand() % 99;   //����һ��0~99���ڵ��������
	first2 = 1+rand() % 99;   //����һ��1~99���ڵ��������
	if (first1>first2)
	{
		temp = first1;
		first1 = first2;
		first2 = temp;//��������֤first1<first2,��first2������0
	}
	second = rand() % 99;   //�����ڶ���0~99���ڵ��������
	cout << setw(3) << first1<<"/"<<first2 << setw(3) << oper(op) << setw(3) << second << setw(3) << " = " << endl;
}
void number3()//��һ��Ϊ�������ڶ���Ϊ�����
{
	string op;
	int first, second1, second2, temp;
	first = rand() % 99;   //������һ��0~99���ڵ��������
	second1 = rand() % 99;   //����һ��0~99���ڵ��������
	second2 = 1 + rand() % 99;   //����һ��1~99���ڵ��������
	if (second1>second2)
	{
		temp = second1;
		second1 = second2;
		second2 = temp;//��������֤second1<second2,��second2������0
	}
	cout << setw(3) << first << setw(3) << oper(op) << setw(3) << second1 << "/" << second2 << setw(3) << " = " << endl;
}
void number4()//��������Ϊ�����
{
	string op;
	int  first1, first2, second1, second2, temp;

	first1 = rand() % 99;   //����һ��0~99���ڵ��������
	first2 = 1 + rand() % 99;   //����һ��1~99���ڵ��������
	second1 = rand() % 99;   //����һ��0~99���ڵ��������
	second2 = 1 + rand() % 99;   //����һ��1~99���ڵ��������
	
	if (first1>first2)
	{
		temp = first1;
		first1 = first2;
		first2 = temp;//��������֤first1<first2,��first2������0
	}
	if (second1>second2)
	{
		temp = second1;
		second1 = second2;
		second2 = temp;//��������֤second1<second2,��second2������0
	}
	cout << setw(3) << first1 << "/" << first2 << setw(3) << oper(op) << setw(3) << second1 << "/" << second2 << setw(3) << " = " << endl;
}

void main()
{
	int z,i;	
	srand((unsigned)time(NULL));  //��һ��ʱ������
	for (i = 0; i < 30; i++)
	{	
		z = 1 + rand() % 4;   //����1~4���ڵ��������
		cout << "��" << setw(2)<<i + 1 << "�⣺";
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