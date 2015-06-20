#include<iostream>
#include<fstream>
#include<string.h>
#include<stack>
#include<sstream>
using namespace std;
string grammarlist[30][35];
string first_save[30][20];
string follow_save[30][30];
string lltable[30][40];
string process[30];

void find_first(string grammar[30][35] , int n , int o);
void find_follow(string a , string grammar[30][35] , int o );
void LLtable(string grammar[30][35]);
void find_table(string place , string inputstr , int pos);
void build_tree();
string makeBlank(int);
int Check_s(string word);
int length(string word);

int tree_save[10] = {0};
int status_save[10];
int save_num;
int array_row;
int num;
int var_num;

template<typename T>	class Stack
{
	public:
		Stack(int capacity = 50)
		{
			cap = capacity;
			arrayLength = capacity;
			array = new T[capacity];
			count = 0;
			repeat = 0;	
		}
		~Stack()
		{
			delete[] array;
		}
		void push(T value)
		{
			if(count == arrayLength)
			{
				T* newArray = new T[arrayLength + cap];
				memcpy(newArray , array , arrayLength *sizeof(T));
				arrayLength +=cap;
				delete [] array;
				array = newArray;
			}
			count = count + 1;
			array[count] = value;			
		}
		void pop(T value)
		{
			array[count] = value;
			count = count - 1;
		}
		T top()
		{
			return array[count];
		}
	private:
		int repeat;
		int arrayLength;
		int cap;
		int count;
		T* array;
};

Stack<string> stateStack(20);//記住變數
Stack<int> posStack(20);//記住位置
Stack<string> inputStack(150);//記住輸入

int main(int argc , char *argv[]){

	string line;
	string line_add;
	string input_array[150];

	int i = -1;
	int n;
	int count = 0;

	fstream file;
	fstream file_1;
	
	file.open("data/set.txt",ios::out);
	file_1.open("data/LLtable.txt",ios::out);
	
	ifstream grammar(argv[1]);//"grammar.txt");
	//ifstream main_c("main.c");

	if(grammar.is_open())
	{
		//一行一行處理grammar.txt
		while(getline(grammar,line))
		{
			if(((line[0] >=65) && (line[0]<=90))||((line[0] >=97) && (line[0]<=122)))
			{
				i = i + 1;
				n = 1;
				grammarlist[i][0] = line;
			}
			else
			{
				if(n != 1)
				{
					grammarlist[i][n] = '|';
					n = n + 1;
				}

				for(int k = 0 ; k < line.length() ; k++)
				{
					//處理文字
					if(((line[k] >=65) && (line[k]<=90))||((line[k] >=97) && (line[k]<=122))||(line[k] == 39)||(line[k] == 59))
					{
						line_add = line_add + line[k];
						if(line[k+1] == 32)
						{	
							grammarlist[i][n] = line_add;
			            line_add = "";
        				   n = n + 1;
			 			}
					}
					//處理括號
					else if((line[k] == 40)||(line[k] == 91)||(line[k] == 123))
					{
						for(k ; k < line.length();k++)
						{
							if(((line[k] >=65) && (line[k]<=90))||((line[k] >=97) && (line[k]<=122))||(line[k] == 39)||(line[k] == 59)||(line[k] == 40)||(line[k] == 41)||(line[k] == 91)||(line[k] == 93)||(line[k] == 123)||(line[k] == 125))
							{
								 line_add = line_add + line[k];
		                   if(line[k+1] == 32)
        		             {
              			       grammarlist[i][n] = line_add;
                    			 line_add = "";
                   			 n = n + 1;
                 			 }
							}
						}	
					}
					//各種符號
					else if((line[k] == 33) ||(line[k] == 45)||(line[k] == 43)||(line[k] == 42)||(line[k] == 47)||
							(line[k] == 61)||(line[k] ==60)||(line[k] == 62)||(line[k]== 38)||(line[k] == 124)||(line[k] == 44)||(line[k] == 36))
					{
						 line_add = line_add + line[k];
						 if(line[k+1] == 32)
                   {
                      grammarlist[i][n] = line_add;
                      line_add = "";
                      n = n + 1;
                   }
					}
				}	
				grammarlist[i][n] = line_add;
            line_add = "";
            n = n + 1;
			}
		}		
	}
	else{
	;
	}

	//處理first
	file << "First" << '\n';
	array_row = i;
	for(int j = 0 ; j <= i ; j++)
	{
		first_save[j][0] = grammarlist[j][0];
		num = 1;
		find_first(grammarlist,j, j);
	}

	for(int i = 0 ; i <=array_row ; i++)
	{
		file << '\n';
		for(int j = 0 ; j < 20 ; j++)
		{
			if(j == 0)
				file << first_save[i][j] << "     : ";
			else 
      		file << first_save[i][j] << " ";
		}
	}

	//處理follow
	file <<'\n';
	file <<"Follow" <<'\n' ;
	for(int j = 0; j <= i ; j++)
	{
			follow_save[j][0] = grammarlist[j][0];
			num = 1;
			find_follow(grammarlist[j][0] , grammarlist , j);
	}
	//加加
	for(int a = 4; a>1 ; a--)
	{
		follow_save[20][a] = follow_save[20][a-1];
		follow_save[21][a] =follow_save[21][a-1];
	}
		follow_save[20][1] = ";";
		follow_save[21][1] = ";";
	
	for(int i = 0 ; i <= array_row ; i++)
	{
		file << '\n';
		for(int j = 0 ; j < 30 ; j++)
      {
			if(j == 0)
				file << follow_save[i][j]<<"     : ";
			else
				file << follow_save[i][j]<<" ";
		}
	}
	file << '\n';

	//處理LLtable
	LLtable(grammarlist);

	//輸出
	file_1 << "S" << '\n';
	
	for( int i = 0 ; i<=(array_row + 1) ; i++)
   {
   	for(int j = 0 ; j <40 ; j++)
      {
      	if(lltable[i][j][0] != '\0' && j!=0 && i!=0)
         {
         	file_1 << lltable[i][0] << "    " << lltable[0][j] << "     " << lltable[i][j] << '\n';
         }
      }
   }

	//處理main
	var_num = 0;
/*	if(main_c.is_open())
	{
		while(getline(main_c , line))
		{
	      for(int k = 0 ; k<line.length() ; k++)
         {
				if(((line[k] >=65) && (line[k]<=90))||((line[k] >=97) && (line[k]<=122))||((line[k] >= 48)&&(line[k] <= 57))||
					(line[k] == 39)||(line[k] == 59)||(line[k] == 40)||(line[k] == 91)||(line[k] == 123)||(line[k] == 33) ||
				   (line[k] == 45)||(line[k] == 43)||(line[k] == 41)||(line[k] == 42)||(line[k] == 47)||(line[k] == 61)||
					(line[k] ==60)||(line[k] == 62)||(line[k]== 38)||(line[k] == 124)||(line[k] == 44)||(line[k] == 36)||
					(line[k] == 93)||(line[k] == 125))
            {
            	line_add = line_add + line[k];
               if(line[k+1] == 32||line[k+1] =='\0')
               {
						input_array[var_num] = line_add;
                  var_num = var_num + 1;
						line_add = "";
               }
            }
			}
		}*/
		
		
		ifstream fin(argv[2]);
   	string new_line = "";
   	while(getline(fin, new_line))
   	{

      stringstream fin_word(new_line);
      string word = "";
      string remain = "";
      int pos = 0;

      while(fin_word >> word) {
         while(word != "") {
            if((pos = Check_s(word)) != -1) {
               if(pos != 0) {
                  remain = word.substr(pos);
                  word = word.substr(0, pos);
               }
               else {
                  remain = word.substr(pos + length(word));
                  word = word.substr(0, length(word));
               }
            }

            //cout << word << endl;
            input_array[var_num] = word;
            var_num = var_num + 1;

            pos = 0;
            word = remain;
            remain = "";
         }
      }
	}


		for(int i = var_num -1 ; i>=0;i--)
			inputStack.push(input_array[i]);

		build_tree();

	return 0;
}


void find_first(string grammar[30][35] , int n , int o){

 	int count = 0;	
	for(int i = 1; i <30 ; i ++)
	{	
		if(i == 1)//第一項
		{
			for(int j = 0 ; j < 30 ; j++)//搜尋陣列中全部的字串 尋找是否為terminal
			{
				if(grammar[n][i] == grammar[j][0])//true 進入該行去尋找
				{
					count = count + 1;
					find_first(grammar,j,o);
				}
			}

			if(count == 0)//若不是terminal 將其放入first陣列中 o 為原始位置
			{
				first_save[o][num] = grammar[n][i];	
				num = num + 1;
			}
		}
		else if(grammar[n][i] == "|")//尋找放在|之後的第一個字串
		{
				count = 0;
				i = i + 1;
	         for(int j = 0 ; j < 30 ; j++)
   	      {
      	      if(grammar[n][i] == grammar[j][0])//若為nonterminal則recursive尋找
         	   { 
						count = count + 1;
            	   find_first(grammar,j,o);
           		}
            }
				
				if(count == 0)//若為nonterminal加入follow中
				{
					first_save[o][num] = grammar[n][i];
					num = num +1;
				}
		}
	}
}

void find_follow(string a , string grammar[30][35] , int o )
{
		num = 1;
		int wrong = 0;
		int num_save = 0;		
		int count = 0;	

		for(int i = 0; i <30 ; i++)
		{
			for(int j = 1 ; j < 35 ; j++)
			{
				if(grammar[i][j] == a)//於字串矩陣中比對字串a true
				{
					count = 0;
					if((grammar[i][j+1][0]=='\0'||grammar[i][j+1] == "|" )/*&& i != o*/)//若下一項為空字串或是|則找首項的follow而且不是同一行
					{
						num_save = num ;//儲存矩陣存放位置
						if(follow_save[i][1][0] == '\0' && i != o)//如果這個follow還沒有建立則先去尋找此nonterminal的follow
						{
							find_follow(grammar[i][0], grammar,i);
						}
						num = num_save;//還原矩陣存放位置
						
						//將首項的follow放入此nonterminal的follow中
						for(int times = 1 ; times < 30 ; times++)
						{
								wrong = 0;
								for(int repeat = 1; repeat < 30 ; repeat++)//判斷重複
								{ 
									if(follow_save[o][repeat] == follow_save[i][times])
									{	
										wrong = wrong + 1;
									}
								}
								if(wrong == 0 && o != i)
								{
									if(follow_save[i][times][0] !='\0')
									{
										follow_save[o][num] = follow_save[i][times] ;
										num = num + 1;
									}
								}
						}
					}
					else//若下一個字不是空字串或是|則可能為nonterminal或是terminal
					{
						for(int m = 0 ;  m <= array_row ; m++)//尋找是否為nonterminal
						{
							if(first_save[m][0] == grammar[i][j+1])//true
							{
								count = count + 1;
								
								for(int n = 1; n < 20;n++)
								{
									if(first_save[m][n] == "epsilon")//若其first中有epsilon則會繼續尋找下一項的follow
									{
										if(grammar[i][j+2][0] == '\0'||grammar[i][j+2][0] == '|')//下一項撞牆尋找首項follow手法與前面相同
										{
											num_save = num ;
  					                  if(follow_save[i][1][0] == '\0' && i != o)//若無follow先尋找
                				  		{
                     					find_follow(grammar[i][0], grammar,i);
                  					}
                  					num = num_save;
                  					for(int times = 1 ; times < 30 ; times++)//將follow置入自身的follow
                  					{
                     					if(follow_save[i][times][0] != '\0' &&  i!=o)
                     					{
													wrong = 0;
                        					for(int repeat = 1; repeat < 30 ; repeat++)
                        					{
                           					if(follow_save[o][repeat] == follow_save[i][times] && follow_save[o][repeat][0]!='\0' && follow_save[i][times][0]!='\0')
                              				{		
																wrong = wrong + 1;
														}
                        					}
                        					if(wrong == 0 &&follow_save[i][times][0]!='\0')
                        					{
                           					follow_save[o][num] = follow_save[i][times];
                           					num = num + 1;
                        					}
                     					}
                  					}		
										}//若是是terminal丟入迴圈中尋找
										else
											find_follow(grammar[i][j+2] , grammar , o);
									}
									else//若不是epsilon則將其first丟入目標follow中
									{
										wrong = 0;
                              for(int repeat = 0; repeat < 30 ; repeat++)
                              {
                              	if(follow_save[o][repeat] == first_save[m][n])
                                 {
                                 	wrong = wrong + 1;
                                 }
                              }
                              if(wrong == 0 && first_save[m][n][0]!='\0')
                              {
											follow_save[o][num] = first_save[m][n];
											num = num + 1;
										}
									}
								}
							}
						}
					//若沒有找到 為nonterminal 直接置入follow 判斷重複
					if( count == 0 && grammar[i][j+1] != "|" &&grammar[i][j+1][0]!='\0')
					{
						wrong = 0;
                  for(int repeat = 0; repeat < 30 ; repeat++)
                  {
                  	if(follow_save[o][repeat] == grammar[i][j+1])
                     {
                     	wrong = wrong + 1;
                     }
                  }
                  if(wrong == 0)
                  {
                      	follow_save[o][num] = grammar[i][j+1];
                        num = num + 1;
						}
					}
				}
			}
		}
	}			
}

void LLtable(string grammar[30][35])
{
		int find = 0;
		int count = 1;
		int repeat = 0;
		int first = 0;

		string non_ter ;
		string inputstr;
		string statement;
		//lltable寫入row[0] 
		for(int i = 1 ; i <= (array_row+1) ; i++)
		{
			lltable[i][0] = grammar[i-1][0];
		}
		//lltable寫入column[0] first
	   for(int i = 0 ; i<30 ; i++)
      {
         for(int j = 1 ; j < 20 ; j++)
         {
            for(int k = 1 ; k < 40 ; k++)
            {
               if(lltable[0][k] == first_save[i][j] )
                  repeat = 1;
            }
               if(repeat ==0 && first_save[i][j]!="" && first_save[i][j] !="epsilon")
               {
                  lltable[0][count] = first_save[i][j] ;
                  count = count + 1;
               }
               repeat = 0;
         }
      }
		//lltable寫入column[0] follow
		for(int i = 0 ; i<30 ; i++)
		{	
			for(int j = 1 ; j < 30 ; j++)
			{
				for(int k = 1 ; k < 40 ; k++)
				{
					if(lltable[0][k] == follow_save[i][j] )
						repeat = 1;
				}
					if(repeat ==0 && follow_save[i][j]!="")
					{
						lltable[0][count] = follow_save[i][j] ;
						count = count + 1;
					}
					repeat = 0;
			}	
		}
		
		//開始判斷填入lltable
		for(int i = 0 ; i <= array_row;i++)
		{	
			non_ter = grammar[i][0];//此迴圈中的nonterminal
			
			////先做第一次
			for(int z = 1 ; z<35 ; z++)//切第一次字串
         {
         	if(grammar[i][z] == "|"||grammar[i][z][0] == '\0')
            	break;
            statement = statement + grammar[i][z] + " ";
         }

         for(int m = 0 ; m < 30 ; m++)//尋找此地一個自為nonterminal還是terminal
         {
         	if(grammar[i][1] == grammar[m][0])//true
            {
            	find = 1;
               for(int k = 1; k<20;k++)//將其first加到lltable中
               {
						if(first_save[m][k] =="epsilon")
                  {
                     if(grammar[i][2][0] == '\0' || grammar[i][2]=="|")
                     {  
                        inputstr = statement;
								for(int y = 1 ;y<20;y++)
								{
									if(follow_save[m][y][0]!='\0')
                        		find_table(follow_save[m][y],inputstr,i+1);
                     	}
							}
                  }

	               if(first_save[m][k][0] !='\0' )
                  { 
                  	inputstr = statement ;//non_ter+"->"
                     find_table(first_save[m][k] , inputstr , i+1);
                  }
             	}
            }
         }
         if(find == 0)//false直接加入lltable
         {
             inputstr = statement ;
             find_table(grammar[i][1] , inputstr , i+1);
         }
         find = 0;
			
			//之後遇到|或是停止
			for(int j = 2 ; j<35 ; j++)
			{	
				statement = "";
				if(grammar[i][j] == "|")
				{
					if(grammar[i][j+1] == "epsilon")//若遇到epsilon則先建立$
					{	
						//find_table("$",non_ter+"->"+"epsilon",i+1);
						
						for(int k = 1; k<30;k++)//在將首項follow加入lltable中
						{
							if(follow_save[i][k][0] !='\0')
							{
								inputstr = "epsilon" ;
								find_table(follow_save[i][k] , inputstr , i+1);
							}
						}
					}
					else//若不是epsilon
					{
						for(int z = j+1 ; z<35 ; z++)//切字串
						{
							if(grammar[i][z] == "|"||grammar[i][z][0] == '\0')
								break;
							statement = statement + grammar[i][z] + " ";
						}				

						for(int m = 0 ; m < 30 ; m++)//判斷是否為nonterminal
						{
							if(grammar[i][j+1] == grammar[m][0])//true
							{
								find = 1;
								for(int k = 1; k<20;k++)
   			            {
            		         if(first_save[m][k][0] !='\0' )
                   			{
                       			inputstr = statement ;
                       			find_table(first_save[m][k] , inputstr , i+1);
                     		}
                  		}
							}
						}
						
						if(find == 0)//false
						{
							inputstr = statement ;
							find_table(grammar[i][j+1] , inputstr , i+1);
						}
						find = 0;
					}
				}
			}
		}
}

//填入lltable
void find_table(string place , string inputstr , int pos)
{
	for(int i = 1 ; i <40 ; i++)
	{
		if(lltable[0][i] == place)
		{
			lltable[pos][i] = inputstr;
		}
	}
}

//建立樹
void build_tree()
{
	//建立初始值
	stateStack.push("S");
	posStack.push(1);
	
	fstream file_2;
   file_2.open("data/tree.txt",ios::out);

	string blank;//空白格
	string line;
	string line_add;
	int pro_num = 0;
	int now_pos_x;//
	int now_pos_y;
	int order = 1;//序列
	int variable = 0;//是否為terminal

	while(stateStack.top()!="")
	{	
			now_pos_x = -1;	
			variable = 0;
			pro_num = 0; //要處理的字串數

			for(int m = 1 ; m <30 ; m++)//判斷non-terminal
			{
				if(lltable[m][0] == stateStack.top())//若找到
				{
					//pop 序列
					order = posStack.top();
					posStack.pop(0);
					blank = makeBlank(order);

					file_2 << blank << order << " " << stateStack.top() <<'\n';;	//輸出變數
					
					order = order+1; //序列 +1
					now_pos_x = m;	//判斷現在處理那一列
					stateStack.pop("");	//pop掉
		
					break;
				}
			}
			for(int m = 1; m<40; m++)//判斷是否為terminal
			{
				if(inputStack.top() == lltable[0][m])
					variable = 1;
			}

			string a = inputStack.top();

			for(int j = 1 ; j <40 ; j++)
			{	
				//若inputStack在terminal中找的到,而且在處理的列的交集中的矩陣內容不為NULL,而且now_pos_x!=-1
				//以及判斷id跟num因為他的input是在矩陣中找不到的
				if((inputStack.top() == lltable[0][j] && lltable[now_pos_x][j][0] !='\0' && now_pos_x != -1)||
					(lltable[0][j] == "id" && lltable[now_pos_x][j][0] !='\0' && variable == 0 &&(((a[0] >= 65)&&(a[0] <=90)) || ((a[0] >=97)&&(a[0] <=122))))||
					(lltable[0][j] == "num" && lltable[now_pos_x][j][0] !='\0' && ((a[0] >= 48)&&(a[0] <=57))))
				{
					now_pos_y = j;//處理的行
					
					//字串分割
					line = lltable[now_pos_x][j];
					
					for(int k = 0 ; k < lltable[now_pos_x][j].length();k++)
					{
		            if(((line[k] >=65) && (line[k]<=90))||((line[k] >=97) && (line[k]<=122))||((line[k] >= 48)&&(line[k] <= 57))||
      		         (line[k] == 39)||(line[k] == 59)||(line[k] == 40)||(line[k] == 91)||(line[k] == 123)||(line[k] == 33) ||
            		   (line[k] == 45)||(line[k] == 43)||(line[k] == 41)||(line[k] == 42)||(line[k] == 47)||(line[k] == 61)||
               		(line[k] ==60)||(line[k] == 62)||(line[k]== 38)||(line[k] == 124)||(line[k] == 44)||(line[k] == 36)||
               		(line[k] == 93)||(line[k] == 125))
               	{
                  	line_add = line_add + line[k];
                  	if(line[k+1] == 32 || line[k+1] == '\n' || line[k+1] == '\0')
                  	{
                     	process[pro_num] = line_add;
                     	line_add = "";
								pro_num = pro_num + 1;
                  	}
               	}
					}
               
					for(int z = (pro_num -1); z >=0 ; z--)
               {
						if(process[z] == "epsilon")//遇到epsilon
						{
							blank = makeBlank(order);
							file_2 << blank << order << " " << "epsilon" <<'\n';
						}
						else if(process[z] != "")//遇到terminal,non-terminal都push進stateStack中
						{
   	               stateStack.push(process[z]);
							process[z] = "";
							posStack.push(order);
						}
               }
				}
			}

			//如果input沒了而且Stack.top()=$
			if(a == "" && stateStack.top() == "$")
			{
				blank = makeBlank(order);
				file_2 << blank << order << " " << "epsilon" << '\n';
			}
			
			//如果stateStack.top 為 ID 或 num
			if(stateStack.top() == "id" || stateStack.top() == "num")
			{
				order = posStack.top();
				blank = makeBlank(order);

				file_2 << blank << order << " " <<stateStack.top()<<'\n';

				order = order + 1;
				blank = makeBlank(order);

				file_2 << blank << order << " " <<inputStack.top()<<'\n';

				//全部pop掉
				order = posStack.top();
				posStack.pop(0);
				inputStack.pop("");
				stateStack.pop("");
			}

			//若遇到stateStack.top()==nonterminal
			else if(stateStack.top() =="int"||stateStack.top() =="while"||stateStack.top()=="if"||stateStack.top()=="print"||
						stateStack.top()=="break"||stateStack.top()=="char"||stateStack.top()=="float"||stateStack.top()=="double"||
						stateStack.top()=="else"||stateStack.top() ==";"||stateStack.top() =="("||stateStack.top()==")"||
						stateStack.top()=="{"||stateStack.top()=="}"||stateStack.top()=="="||stateStack.top()=="+"||stateStack.top()=="return"||
						stateStack.top()=="-"||stateStack.top()=="*"||stateStack.top()=="["||stateStack.top()=="]"||stateStack.top()=="/"||
						stateStack.top()==">"||stateStack.top()=="<"||stateStack.top()=="!"||stateStack.top()=="!="||stateStack.top()=="&&"||
						stateStack.top()=="<="||stateStack.top()==">="||stateStack.top()=="=="||stateStack.top()=="||"||stateStack.top()==",")
			{
				//處理順序
				order = posStack.top();
				posStack.pop(0);
				blank = makeBlank(order);

				file_2 << blank << order << " " << stateStack.top() <<'\n';
				
				//pop掉
				stateStack.pop("");
				inputStack.pop("");
			}
			//遇到 $
			else if(stateStack.top() =="$")
			{
            order = posStack.top();
            posStack.pop(0);
				blank = makeBlank(order);

				file_2 << blank << order << " " << stateStack.top() <<'\n';
				stateStack.pop("");
			}			
	}
}
//製造空白
string makeBlank(int n)
{
	string blank = "";
	for(int i = 1 ; i < n ; i++)
		blank = blank + "  ";
	return blank;
}
int Check_s(string word) {
   string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
   int count = -1;

   for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
      if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
         count = word.find(temp[i]);
      }
   }
   return count;
}

int length(string word) {
   string temp[] = {"==", "!=", "<=", ">=", "&&", "||"};
   int count = -1;

   for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
      if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
         count = word.find(temp[i]);
      }
   }

   if(count != -1) {
      return 2;
   }
   else {
      return 1;
   }
}
 
