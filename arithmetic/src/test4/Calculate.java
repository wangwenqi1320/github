package test4;
import java.util.*;
public class Calculate {
		static int MAX=100;
		static String formula = "";         //当前算式
		static String[] buffer = new String[MAX];     //缓冲区数组
		static int TopNumber;          //上限
		static int BaseNumber;         //下限
		static int IsMulDlvExist;      //是否有乘除
		static int Amount;             //操作数的个数
		static int BracketNum;         //括号个数
		static int[] LBraket = new int[2];         //左括号的位置
		static int[] RBraket = new int[2];         //右括号的位置
		static int IsNeg;              //是否有负数
		static int IsRem;              //是否有余数
		static int IsBra;              //是否有括号
		static int IsRep;              //是否重复
		static float[] Result= new float[MAX];      //正确结果数组
		static char lastOp;            //记录上个运算符是否为除号
		
		//优先级数组
		static char[][] prior = {
			{ '>', '>', '<', '<', '<', '>', '>' },
			{ '>', '>', '<', '<', '<', '>', '>' },
			{ '>', '>', '>', '>', '<', '>', '>' },
			{ '>', '>', '>', '>', '<', '>', '>' },
			{ '<', '<', '<', '<', '<', '=', ' ' },
			{ '>', '>', '>', '>', ' ', '>', '>' },
			{ '<', '<', '<', '<', '<', ' ', '=' }
		};
		
		//将操作符转化为优先级数组的下标
		static int Change(String Oper)
		{
			switch (Oper.charAt(0))
			{
				case '+': return 0;
	            case '-': return 1; 
				case '*': return 2; 
				case '/': return 3; 
				case '(': return 4; 
				case ')': return 5;
				case '=': return 6; 
				default:  return 6; 
			}
		}
		static int Change(char Oper)
		{
			switch (Oper)
			{
				case '+': return 0;
	            case '-': return 1; 
				case '*': return 2; 
				case '/': return 3; 
				case '(': return 4; 
				case ')': return 5;
				case '=': return 6; 
				default:  return 6; 
			}
		}
		static //返回优先级的大小
		char Precede(char Oper, char ch)
		{
			return prior[Change(Oper)][Change(ch)];
		}
		
		//计算两个数的结果
		static float Operate(float first, char oper1, float second)
		{
			switch (oper1)
			{
			case '+':
			{
						return (first + second);
			}
			case '-':
			{
				if (first-second<0)
				{
					IsRep = 1;
					return 0;
				}
						return (first - second);					
			}
			case '*':
			{
						return (first * second);					
			}
			case '/':
			{
						if (second == 0)
						{
							IsRep = 1;
							return 0;
						}
						return (first / second);
			}
			default:  return 0; 
			}
		}
		
		//数字的个数
		static void NumberAmount()
		{
			Amount = 2 + (int)((Math.random())*3);
		}
		
		//加左括号   随机选择在第几个数字前面加括号
		static void AddLbracket(){
			for (int j = 0; j < 2; j++)
				LBraket[j] = 0;
			if (Amount == 2)
			{
				BracketNum = 0;
			}
			if (Amount == 3){
				BracketNum = (int)((Math.random())*2);
			}
			if (Amount > 3)
			{
				BracketNum = (int)((Math.random())*3);
			}
			for (int i = 0; i < BracketNum; i++){
				LBraket[i] = 1 + (int)((Math.random())*(Amount - 2));
			}
		}
		//加右括号
		static void AddRbracket(){
			for (int j = 0; j < 2; j++)
				RBraket[j] = 0;
			int choose;
			int trance;
			if (BracketNum == 1){
				RBraket[0] = LBraket[0] + 1 +(int)((Math.random())* (Amount - LBraket[0]));
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
					choose = (int)((Math.random())*2);
					if (choose == 0){
						RBraket[0] = LBraket[0] + 1 + (int)((Math.random())*(Amount - LBraket[0]));
						RBraket[1] = LBraket[0] + 1 + (int)((Math.random())*(Amount - LBraket[0]));
					}
					if (choose == 1)
					{
						RBraket[0] = LBraket[0] + 1 + (int)((Math.random())*(Amount - LBraket[0]));
						RBraket[1] = LBraket[1] + 1 + (int)((Math.random())*(LBraket[0] - 2));
					}
				}
				else
				{
					RBraket[0] = LBraket[0] + 1 + (int)((Math.random())*(Amount - LBraket[0]));
					RBraket[1] = LBraket[0] + 1 + (int)((Math.random())*(Amount - LBraket[0]));
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
		static void Score(){
			int Left, Right;
			Left = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
			Right = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
			while (Left >= Right || Left == 0)
			{
				Left = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
				Right = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
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
			formula += "(" + Left + "/" + Right + ")";
		}
		
		//随机生成操作符
		static void Operater()
		{
			int choose;
			char op='+';
			if (IsMulDlvExist == 1)
				choose = 1 + (int)((Math.random())* 4);
			else
				choose = 1 + (int)((Math.random())*2);

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
			formula += op;
		}
		
		//随机生成整数
		static void Integer(){
			int num;
			num = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
			formula += num;
		}
		//创建算式
		static void CreateNumber(){
			for (int k = 1; k <= Amount; k++)
			{

				for (int i = 0; i < 2; i++){
					if (LBraket[i] == k)
						formula += "(";
				}

				int cho;
				cho = (int)((Math.random())*2);
				if (cho == 0)
				{
					Integer();
				}
				else
					Score();
				for (int j = 0; j < 2; j++){
					if ((RBraket[j] == k) && RBraket[j] != 0)
						formula += ")";
				}
				if (k == Amount)
					formula += "=";
				else
					Operater();
			}
		}
		//检查是否重复及判断括号是否添加正确
		static int Repeat(int time){
			buffer[time] = formula;
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
		static float EvaluateExpression(){
			//Stack OPTR=new Stack();
			//Stack OPND=new Stack();
			float[] OPND=new float[MAX];
			char[] OPTR =new char[MAX];
			int Ntop=0;
			int Ctop=0;
			//InitOperStack(OPTR);
			//OPTR.push("=");
			OPTR[Ctop++]='=';
			//PushOper(OPTR, '=');
			//InitNumStack(OPND);
			int count = 0;
			float Num = 0, first, second;
			char oper1;
			char bracket1;
			while (true)
			{
				Num = 0;
				//读取数字
				while (formula.charAt(count) >= '0'&&formula.charAt(count) <= '9')
				{
					if (formula.charAt(count) == '0')
					{
						if (count == 0)
							//OPND.push(new Float(0));
							OPND[Ntop++]=0;
						if (count != 0 && !(formula.charAt(count-1) >= '0'&&formula.charAt(count-1) <= '9'))
							//OPND.push(new Float(0));
							OPND[Ntop++]=0;
					}
						
					Num = Num * 10;
					Num = Num + formula.charAt(count) - 48;
					count++;
					
				}
				if (Num > 0)
				{
					//OPND.push(new Float(Num));
					//PushNum(OPND, Num);
					OPND[Ntop++]=Num;
				}
				if (formula.charAt(count) == '='&&OPTR[Ctop-1] == '=')
				{
					break;
				}
				//判断运算符优先级
				
				switch (Precede(OPTR[Ctop-1], formula.charAt(count)))
				{
					case '<':
					{
						//OPTR.push(formula.charAt(count));
						OPTR[Ctop++]=formula.charAt(count);
							//PushOper(OPTR, formula.str()[count]);
							count++;
							break;
					}
					case '>':
					{
							//PopOper(OPTR, oper1);
						//oper1=(char) OPTR.pop();
						oper1=OPTR[--Ctop];
							//PopNum(OPND, second);
						//second=(float) OPND.pop();
						second=OPND[--Ntop];
							//PopNum(OPND, first);
						//first=(float)OPND.pop();
						first=OPND[--Ntop];
							//PushNum(OPND, Operate(first, oper1, second));
						//OPND.push(Operate(first, oper1, second));
						OPND[Ntop++]=Operate(first, oper1, second);
							break;
					}
					case '=':
					{
								//PopOper(OPTR, bracket1);
						//bracket1=(char) OPTR.pop();
						bracket1=OPTR[--Ctop];
								count++;
					}
				}
			}
			return OPND[Ntop-1];
		}
		
		public static void SetValue(int IsMulDlvExist1,int IsRem1,int IsBra1,int TopNumber1,int BaseNumber1)
		{
			IsMulDlvExist=0;
			BaseNumber=0;
			TopNumber=10;
			IsNeg=0;
			IsRem=0;
			IsBra=1;
			
			
			
			IsMulDlvExist=IsMulDlvExist1;
			TopNumber=TopNumber1;
			BaseNumber=BaseNumber1;
			IsRem=IsRem1;
			IsBra=IsBra1;
		}
		public static void SetValue1(int IMDE)
		{
			IsMulDlvExist=IMDE;
		}
		public static void SetValue2(int Rem)
		{
			IsRem=Rem;
		}
		public static void SetValue3(int Bra)
		{
			IsBra=Bra;
		}
		public static void SetValue(int TopNumber1,int BaseNumber1){
			IsMulDlvExist=0;
			BaseNumber=0;
			TopNumber=10;
			IsNeg=0;
			IsRem=0;
			IsBra=1;
			TopNumber=TopNumber1;
			BaseNumber=BaseNumber1;
			
		}
		
		public static int StrToNum(String x)
		{
			  int num=0;
			   for(int i=0;i<x.length();i++)
			   {
			   		num=num*10+x.charAt(i)-48;
			   }
			   return num;
		}
		public static float StrToFloat(String x)
		{
			float num=0;
			int doat=0;
			int mi=-1;
			for(int i=0;i<x.length();i++)
			{
				if(x.charAt(i)=='.')
				{
					doat=1;
					continue;
				}
				if(doat==1)
				{
					num=(float) (num+(x.charAt(i)-48)*Math.pow(10,mi));
					mi--;
				}else{
					num=num*10+x.charAt(i)-48;
				}
			}
			return num;
		
		}
		public static float StrToFloat1(String x)
		{
			float first=0;
			float second=0;
			int point=0;
			for(int i=0;i<x.length();i++)
			{
				if(x.charAt(i)=='/')
				{
					point=1;
					continue;
				}
				if(point==1)
				{
					second=second*10+x.charAt(i)-48;
				}else
				{
					first=first*10+x.charAt(i)-48;
				}
			}
			return (first/second);
		}
		static int ma()
		{
			int OutChoose = 0;
			int truenum = 0;
			int choose;
			boolean flag = true;                       
			int range = 0;
			
			//IsMulDlvExist=1;
			//BaseNumber=0;
			//TopNumber=10;
			//IsNeg=0;
			//IsRem=0;
			//IsBra=0;
			
			
			/*cout << "            欢迎来到四则运算答题系统！" << endl;
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
			*/


			//float sum = 0;
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
				while (Repeat(i) == 1 || IsRep == 1 || (IsNeg == 1 && (Result[i] < 0 || Result[i] == -0)) || (IsRem == 1 && ((int)(Result[i]*10000))%10000!=0))
				{

					IsRep = 0;
					lastOp = '+';
					formula="";
					NumberAmount();
					if (IsBra == 0)
					{
						AddLbracket();
						AddRbracket();
					}
					CreateNumber();
					Result[i] = EvaluateExpression();					
				}
				buffer[i]=formula;
				formula="";
			}

			return 0;
		}
		public static float css(int number){
			return Result[number];
		}
		public static String cs(int number){
			return buffer[number];
		}
	public static void main()
	{
		int a;
		a=ma();
		for (int i = 0; i < 30; i++)
		{
			System.out.println(buffer[i]+Result[i]);
		}
		
	}
}
