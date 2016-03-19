#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
#include<fstream>
#define MAX 100
using namespace std;

stringstream formula;   //当前算式
string buffer[MAX];     //缓冲区数组
int TopNumber;          //上限
int BaseNumber;         //下限
int IsMulDlvExist;      //是否有乘除
int Amount;             //操作数的个数
int BracketNum;         //括号个数
int LBraket[2];         //左括号的位置
int RBraket[2];         //右括号的位置
int IsNeg;              //是否有负数
int IsRem;              //是否有余数
int IsBra;              //是否有括号
int IsRep;              //是否重复
float Result[MAX];      //正确结果数组
char lastOp;            //记录上个运算符是否为除号

//优先级数组
char prior[7][7] = {
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '<', '<', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '>', '>', '>', '>', '<', '>', '>' },
	{ '<', '<', '<', '<', '<', '=', ' ' },
	{ '>', '>', '>', '>', ' ', '>', '>' },
	{ '<', '<', '<', '<', '<', ' ', '=' }
};
//操作符栈
typedef struct {
	char *base;
	char *top;
}OperChar;
//操作数栈
typedef struct{
	float *base;
	float *top;
}NumberLink;
//初始化栈
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
//进栈
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
//出栈
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
//取栈顶元素
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
//将操作符转化为优先级数组的下标
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
//返回优先级的大小
char Precede(char Oper, char ch)
{
	return prior[Change(Oper)][Change(ch)];
}
//计算两个数的结果
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
//数字的个数
void NumberAmount()
{
	Amount = 2 + rand() % 5;
}
//加左括号   随机选择在第几个数字前面加括号
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
//加右括号
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
		//把最左边的左括号放在第一个数组中
		if (LBraket[0] < LBraket[1])
		{
			trance = LBraket[0];
			LBraket[0] = LBraket[1];
			LBraket[1] = trance;
		}
		//当两个左括号之间相差有点远时有2中右括号添加方法
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
//随机产生最简真分数
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
	//求最大公约数
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
//随机生成操作符
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
			  //防止连续除法产生运算误区
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
//随机生成整数
void Integer(){
	int num;
	num = BaseNumber + rand() % (TopNumber - BaseNumber + 1);
	formula << num;
}
//创建算式
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
//检查是否重复及判断括号是否添加正确
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
//利用栈计算结果      参考《数据结构---C语言》
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
		//读取数字
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
		//判断运算符优先级
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
	cout << "            欢迎来到四则运算答题系统！" << endl;
	cout << "说明：\n\t初级只有加减法无括号无负数无余数（默认数值范围0-5）\n\t中级有乘除有括号无负数无余数（默认范围0-20）\n\t高级有乘除有括号有负数有余数（默认范围0-100）" << endl;
	while (flag)
	{
		cout << "现在有初级，中级，高级，三种关卡，你要挑战哪一关？" << endl;
		cout << "1.初级  2.中级  3.高级     请选择：";
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
				  cout << "是否打印试卷？0、否  1、是  请选择 ： ";
				  cin >> OutChoose;
				  cout << "是否需要数值重设范围？0、否  1、是  请选择 ： ";
				  cin >> range;
				  IsMulDlvExist = 0;
				  BaseNumber = 0;
				  TopNumber = 5;
				  if (range == 1){
					  cout << "请输入下限（正数）：";
					  cin >> BaseNumber;
					  cout << "请输入上限（正数）：";
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
				  cout << "是否打印试卷？0、否  1、是  请选择 ： ";
				  cin >> OutChoose;
				  cout << "是否需要数值重设范围？0、否  1、是  请选择 ： ";
				  cin >> range;
				  IsMulDlvExist = 1;
				  BaseNumber = 0;
				  TopNumber = 20;
				  if (range == 1){
					  cout << "请输入下限（正数）：";
					  cin >> BaseNumber;
					  cout << "请输入上限（正数）：";
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
				  cout << "是否打印试卷？0、否  1、是  请选择 ： ";
				  cin >> OutChoose;
				  cout << "是否需要数值重设范围？0、否  1、是  请选择 ： ";
				  cin >> range;
				  IsMulDlvExist = 1;
				  BaseNumber = 0;
				  TopNumber = 100;
				  if (range == 1){
					  cout << "请输入下限（正数）：";
					  cin >> BaseNumber;
					  cout << "请输入上限（正数）：";
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
				   cout << "输入有误，请重新选择：" << endl;
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
		cout << "第" << i + 1 << "题：";
		cout << formula.str();

		cin >> sum;
		if (OutChoose == 1)
		{
			out << "第" << i + 1 << "题：";
			out << formula.str() << sum;
		}
		if (abs(int(100 * sum) - int(100 * Result[i])) <= 1)
		{
			cout << "小朋友太棒了，回答正确！\n";
			if (OutChoose == 1)
				out << "小朋友太棒了，回答正确！\n";
			truenum++;
		}
		else
		{
			cout << "回答错误，小朋友继续加油!正确答案：" << Result[i] << endl;
			if (OutChoose == 1)
				out << "回答错误，小朋友继续加油!正确答案：" << Result[i] << endl;
		}

		formula.str("");
	}
	cout << endl;
	cout << "你一共答对了" << truenum << "道题！" << endl;
	if (OutChoose == 1)
		out << "你一共答对了" << truenum << "道题！" << endl;
	return 0;
}