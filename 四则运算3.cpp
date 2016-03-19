#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
#include<fstream>
#define MAX 100
using namespace std;

stringstream formula;   //��ǰ��ʽ
string buffer[MAX];     //����������
int TopNumber;          //����
int BaseNumber;         //����
int IsMulDlvExist;      //�Ƿ��г˳�
int Amount;             //�������ĸ���
int BracketNum;         //���Ÿ���
int LBraket[2];         //�����ŵ�λ��
int RBraket[2];         //�����ŵ�λ��
int IsNeg;              //�Ƿ��и���
int IsRem;              //�Ƿ�������
int IsBra;              //�Ƿ�������
int IsRep;              //�Ƿ��ظ�
float Result[MAX];      //��ȷ�������
char lastOp;            //��¼�ϸ�������Ƿ�Ϊ����

//���ȼ�����
char prior[7][7] = {
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '<', '<', '<', '<', '<', '=', ' ' },
	{ '>', '>', '>', '>', ' ', '>', '>' },
	{ '<', '<', '<', '<', '<', ' ', '=' }
};
//������ջ
typedef struct {
	char *base;
	char *top;
}OperChar;
//������ջ
typedef struct{
	float *base;
	float *top;
}NumberLink;
//��ʼ��ջ
void InitOperStack(OperChar &S)
{
	S.base = new char[MAX];
	if (!S.base)
		exit(1);
	S.top = S.base;
}
void InitNumStack(NumberLink &S)
{
	S.base = new float[MAX];
	if (!S.base)
		exit(1);
	S.top = S.base;
}
//��ջ
void PushOper(OperChar &S, char e){
	if (S.top - S.base == MAX)
		exit(1);
	*S.top++ = e;

}
void PushNum(NumberLink &S, float e){
	if (S.top - S.base == MAX)
		exit(1);
	*S.top++ = e;
}
//��ջ
void PopOper(OperChar &S, char &e)
{
	if (S.top == S.base)
		exit(1);
	e = *--S.top;
}
void PopNum(NumberLink &S, float &e)
{
	if (S.top == S.base)
		exit(1);
	e = *--S.top;
}
//ȡջ��Ԫ��
char GetTopOper(OperChar S)
{
	if (S.top == S.base)
	{
		exit(1);

	}
	return *(S.top - 1);
}
float GetTopNum(NumberLink S)
{
	if (S.top == S.base)
	{
		exit(1);

	}
	return *(S.top - 1);
}
//��������ת��Ϊ���ȼ�������±�
int Change(char Oper)
{
	switch (Oper)
	{
	case '+': return 0; break;
	case '-': return 1; break;
	case '*': return 2; break;
	case '/': return 3; break;
	case '(': return 4; break;
	case ')': return 5; break;
	case '=': return 6; break;
	default:  return 6; break;

	}
}
//�������ȼ��Ĵ�С
char Precede(char Oper, char ch)
{
	return prior[Change(Oper)][Change(ch)];
}
//�����������Ľ��
float Operate(float first, char oper1, float second)
{
	switch (oper1)
	{
	case '+':
	{
				return (first + second);
				break;
	}
	case '-':
	{
				return (first - second);
				break;
	}
	case '*':
	{
				return (first * second);
				break;
	}
	case '/':
	{
				if (second == 0)
				{
					IsRep = 1;
					return 0;
				}
				return (first / second);
				break;

	}
	default:  return 0; break;
	}
}
//���ֵĸ���
void NumberAmount()
{
	Amount = 2 + rand() % 5;
}
//��������   ���ѡ���ڵڼ�������ǰ�������
void AddLbracket(){
	for (int j = 0; j < 2; j++)
		LBraket[j] = 0;
	if (Amount == 2)
	{
		BracketNum = 0;
	}
	if (Amount == 3){
		BracketNum = rand() % 2;
	}
	if (Amount > 3)
	{
		BracketNum = rand() % 3;
	}
	for (int i = 0; i < BracketNum; i++){
		LBraket[i] = 1 + rand() % (Amount - 2);
	}
}
//��������
void AddRbracket(){
	for (int j = 0; j < 2; j++)
		RBraket[j] = 0;
	int choose;
	int trance;
	if (BracketNum == 1){
		RBraket[0] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
	}
	if (BracketNum == 2)

	{
		//������ߵ������ŷ��ڵ�һ��������
		if (LBraket[0] < LBraket[1])
		{
			trance = LBraket[0];
			LBraket[0] = LBraket[1];
			LBraket[1] = trance;
		}
		//������������֮������е�Զʱ��2����������ӷ���
		if (LBraket[0] - LBraket[1]>2){
			choose = rand() % 2;
			if (choose == 0){
				RBraket[0] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
				RBraket[1] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
			}
			if (choose == 1)
			{
				RBraket[0] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
				RBraket[1] = LBraket[1] + 1 + rand() % (LBraket[0] - 2);
			}
		}
		else
		{
			RBraket[0] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
			RBraket[1] = LBraket[0] + 1 + rand() % (Amount - LBraket[0]);
			if (LBraket[0] == LBraket[1] && RBraket[0] == RBraket[1]){
				LBraket[0] = LBraket[1] = 0;
				RBraket[0] = RBraket[1] = 0;
				BracketNum = 0;

			}
			if (LBraket[1] == 1 && (RBraket[0] == Amount || RBraket[1] == Amount))
			{
				LBraket[0] = LBraket[1] = 0;
				RBraket[0] = RBraket[1] = 0;
				BracketNum = 0;
			}

		}
	}
}
//���������������
void Score(){
	int Left, Right;
	Left = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
	Right = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
	while (Left >= Right || Left == 0)
	{
		Left = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
		Right = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
	}
	int max = 1;
	//�����Լ��
	for (int i = 2; i <= Left; i++)
	{
		if (Left%i == 0 && Right%i == 0)
		{
			max = i;
		}
	}
	if (max > 1)
	{
		Left /= max;
		Right /= max;
	}
	formula << '(' << Left << '/' << Right << ')';
}
//������ɲ�����
void Operater()
{
	int choose;
	char op;
	if (IsMulDlvExist == 1)
		choose = 1 + rand() % 4;
	else
		choose = 1 + rand() % 2;

	switch (choose)
	{
	case 1:{op = '+'; lastOp = '+'; break; }
	case 2:{op = '-';  lastOp = '-'; break; }
	case 3:{op = '*';  lastOp = '*'; break; }
	case 4:
	{
			  //��ֹ��������������������
			  op = '/';
			  if (lastOp == '/')
				  IsRep = 1;
			  else
				  lastOp = '/';
			  break;
	}
	}
	formula << op;
}
//�����������
void Integer(){
	int num;
	num = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
	formula << num;
}
//������ʽ
void CreateNumber(){
	for (int k = 1; k <= Amount; k++)
	{

		for (int i = 0; i < 2; i++){
			if (LBraket[i] == k)
				formula << '(';
		}

		int cho;
		cho = rand() % 2;
		if (cho == 0)
		{
			Integer();
		}
		else
			Score();
		for (int j = 0; j < 2; j++){
			if ((RBraket[j] == k) && RBraket[j] != 0)
				formula << ')';
		}
		if (k == Amount)
			formula << '=';
		else
			Operater();
	}
}
//����Ƿ��ظ����ж������Ƿ������ȷ
int Repeat(int time){
	buffer[time] = formula.str();
	int juege = 0;
	int trance;
	for (int i = 0; i < time; i++)
	{
		if (buffer[i] == buffer[time])
		{
			juege = 1;
			break;
		}
	}
	if (IsBra != 1)
	{
		if (BracketNum == 1)
		{
			if (LBraket[0] == 1 && RBraket[0] == Amount)
				juege = 1;
		}
		if (BracketNum == 2)
		{
			if (RBraket[0] < RBraket[1])
			{
				trance = RBraket[0];
				RBraket[0] = RBraket[1];
				RBraket[1] = trance;
			}
			if (LBraket[1] == 1 && RBraket[0] == Amount&&LBraket[0] < RBraket[1])
				juege = 1;
		}
	}
	return juege;

}
//����ջ������      �ο������ݽṹ---C���ԡ�
float EvaluateExpression(){
	OperChar OPTR;
	NumberLink OPND;
	InitOperStack(OPTR);
	PushOper(OPTR, '=');
	InitNumStack(OPND);
	int count = 0;
	float Num = 0, first, second;
	char oper1;
	char bracket1;
	while (true)
	{
		Num = 0;
		//��ȡ����
		while (formula.str()[count] >= '0'&&formula.str()[count] <= '9')
		{
			if (formula.str()[count] == '0')
			{
				if (count == 0)
					PushNum(OPND, 0);
				if (count != 0 && !(formula.str()[count - 1] >= '0'&&formula.str()[count - 1] <= '9'))
					PushNum(OPND, 0);
			}

			Num = Num * 10;
			Num = Num + formula.str()[count] - 48;
			count++;

		}
		if (Num > 0)
		{
			PushNum(OPND, Num);
		}
		if (formula.str()[count] == '='&&GetTopOper(OPTR) == '=')
		{
			break;
		}
		//�ж���������ȼ�
		switch (Precede(GetTopOper(OPTR), formula.str()[count]))
		{
		case '<':
		{
					PushOper(OPTR, formula.str()[count]);
					count++;
					break;
		}
		case '>':
		{
					PopOper(OPTR, oper1);
					PopNum(OPND, second);
					PopNum(OPND, first);
					PushNum(OPND, Operate(first, oper1, second));
					break;
		}
		case '=':
		{
					PopOper(OPTR, bracket1);
					count++;
		}
		}
	}
	return GetTopNum(OPND);
}
int main()
{
	ofstream out("1.txt", ios::out);
	int OutChoose = 0;
	int truenum = 0;
	int choose;
	bool flag = true;
	int range = 0;
	srand((unsigned)time(NULL));
	/*cin >> IsMulDlvExist;
	cin >> BaseNumber;
	cin >> TopNumber;
	cin >> IsNeg;
	cin >> IsRem;
	cin >> IsBra;*/
	cout << "            ��ӭ���������������ϵͳ��" << endl;
	cout << "˵����\n\t����ֻ�мӼ����������޸�����������Ĭ����ֵ��Χ0-5��\n\t�м��г˳��������޸�����������Ĭ�Ϸ�Χ0-20��\n\t�߼��г˳��������и�����������Ĭ�Ϸ�Χ0-100��" << endl;
	while (flag)
	{
		cout << "�����г������м����߼������ֹؿ�����Ҫ��ս��һ�أ�" << endl;
		cout << "1.����  2.�м�  3.�߼�     ��ѡ��";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
				  cout << "�Ƿ��ӡ�Ծ�0����  1����  ��ѡ�� �� ";
				  cin >> OutChoose;
				  cout << "�Ƿ���Ҫ��ֵ���跶Χ��0����  1����  ��ѡ�� �� ";
				  cin >> range;
				  IsMulDlvExist = 0;
				  BaseNumber = 0;
				  TopNumber = 5;
				  if (range == 1){
					  cout << "���������ޣ���������";
					  cin >> BaseNumber;
					  cout << "���������ޣ���������";
					  cin >> TopNumber;
				  }
				  IsNeg = 1;
				  IsRem = 1;
				  IsBra = 1;
				  flag = false;
				  break;
		}
		case 2:
		{
				  cout << "�Ƿ��ӡ�Ծ�0����  1����  ��ѡ�� �� ";
				  cin >> OutChoose;
				  cout << "�Ƿ���Ҫ��ֵ���跶Χ��0����  1����  ��ѡ�� �� ";
				  cin >> range;
				  IsMulDlvExist = 1;
				  BaseNumber = 0;
				  TopNumber = 20;
				  if (range == 1){
					  cout << "���������ޣ���������";
					  cin >> BaseNumber;
					  cout << "���������ޣ���������";
					  cin >> TopNumber;
				  }
				  IsNeg = 1;
				  IsRem = 1;
				  IsBra = 0;
				  flag = false;
				  break;
		}
		case 3:
		{
				  cout << "�Ƿ��ӡ�Ծ�0����  1����  ��ѡ�� �� ";
				  cin >> OutChoose;
				  cout << "�Ƿ���Ҫ��ֵ���跶Χ��0����  1����  ��ѡ�� �� ";
				  cin >> range;
				  IsMulDlvExist = 1;
				  BaseNumber = 0;
				  TopNumber = 100;
				  if (range == 1){
					  cout << "���������ޣ���������";
					  cin >> BaseNumber;
					  cout << "���������ޣ���������";
					  cin >> TopNumber;
				  }
				  IsNeg = 0;
				  IsRem = 0;
				  IsBra = 0;
				  flag = false;
				  break;
		}
		default:
		{
				   cout << "��������������ѡ��" << endl;
				   flag = true;
				   break;
		}
		}

	}


	float sum = 0;
	for (int i = 0; i < 30; i++)
	{
		lastOp = '+';
		IsRep = 0;
		NumberAmount();
		if (IsBra == 0)
		{
			AddLbracket();
			AddRbracket();
		}
		CreateNumber();
		Result[i] = EvaluateExpression();
		while (Repeat(i) == 1 || IsRep == 1 || (IsNeg == 1 && (Result[i] < 0 || Result[i] == -0)) || (IsRem == 1 && (int(Result[i] * 10000)) % 10000 != 0))
		{

			IsRep = 0;
			lastOp = '+';
			formula.str("");
			NumberAmount();
			if (IsBra == 0)
			{
				AddLbracket();
				AddRbracket();
			}
			CreateNumber();
			Result[i] = EvaluateExpression();
		}
		cout << "��" << i + 1 << "�⣺";
		cout << formula.str();

		cin >> sum;
		if (OutChoose == 1)
		{
			out << "��" << i + 1 << "�⣺";
			out << formula.str() << sum;
		}
		if (abs(int(100 * sum) - int(100 * Result[i])) <= 1)
		{
			cout << "С����̫���ˣ��ش���ȷ��\n";
			if (OutChoose == 1)
				out << "С����̫���ˣ��ش���ȷ��\n";
			truenum++;
		}
		else
		{
			cout << "�ش����С���Ѽ�������!��ȷ�𰸣�" << Result[i] << endl;
			if (OutChoose == 1)
				out << "�ش����С���Ѽ�������!��ȷ�𰸣�" << Result[i] << endl;
		}

		formula.str("");
	}
	cout << endl;
	cout << "��һ�������" << truenum << "���⣡" << endl;
	if (OutChoose == 1)
		out << "��һ�������" << truenum << "���⣡" << endl;
	return 0;
}