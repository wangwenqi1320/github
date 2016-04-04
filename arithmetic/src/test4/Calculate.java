package test4;
import java.util.*;
public class Calculate {
		static int MAX=100;
		static String formula = "";         //��ǰ��ʽ
		static String[] buffer = new String[MAX];     //����������
		static int TopNumber;          //����
		static int BaseNumber;         //����
		static int IsMulDlvExist;      //�Ƿ��г˳�
		static int Amount;             //�������ĸ���
		static int BracketNum;         //���Ÿ���
		static int[] LBraket = new int[2];         //�����ŵ�λ��
		static int[] RBraket = new int[2];         //�����ŵ�λ��
		static int IsNeg;              //�Ƿ��и���
		static int IsRem;              //�Ƿ�������
		static int IsBra;              //�Ƿ�������
		static int IsRep;              //�Ƿ��ظ�
		static float[] Result= new float[MAX];      //��ȷ�������
		static char lastOp;            //��¼�ϸ�������Ƿ�Ϊ����
		
		//���ȼ�����
		static char[][] prior = {
			{ '>', '>', '<', '<', '<', '>', '>' },
			{ '>', '>', '<', '<', '<', '>', '>' },
			{ '>', '>', '>', '>', '<', '>', '>' },
			{ '>', '>', '>', '>', '<', '>', '>' },
			{ '<', '<', '<', '<', '<', '=', ' ' },
			{ '>', '>', '>', '>', ' ', '>', '>' },
			{ '<', '<', '<', '<', '<', ' ', '=' }
		};
		
		//��������ת��Ϊ���ȼ�������±�
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
		static //�������ȼ��Ĵ�С
		char Precede(char Oper, char ch)
		{
			return prior[Change(Oper)][Change(ch)];
		}
		
		//�����������Ľ��
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
		
		//���ֵĸ���
		static void NumberAmount()
		{
			Amount = 2 + (int)((Math.random())*3);
		}
		
		//��������   ���ѡ���ڵڼ�������ǰ�������
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
		//��������
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
				//������ߵ������ŷ��ڵ�һ��������
				if (LBraket[0] < LBraket[1])
				{
					trance = LBraket[0];
					LBraket[0] = LBraket[1];
					LBraket[1] = trance;
				}
				//������������֮������е�Զʱ��2����������ӷ���
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
		
		//���������������
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
			formula += "(" + Left + "/" + Right + ")";
		}
		
		//������ɲ�����
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
						  //��ֹ��������������������
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
		
		//�����������
		static void Integer(){
			int num;
			num = BaseNumber + (int)((Math.random())*(TopNumber - BaseNumber + 1));
			formula += num;
		}
		//������ʽ
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
		//����Ƿ��ظ����ж������Ƿ������ȷ
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
				//��ȡ����
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
				//�ж���������ȼ�
				
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
			
			
			/*cout << "            ��ӭ���������������ϵͳ��" << endl;
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
