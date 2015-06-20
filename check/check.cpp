#include "check.h"

Check::Check(string file_name) {
	
 	type[0] = "int";
	type[1] = "char";
	type[2] = "float";
	type[3] = "double"; 	

	order = 0;
	total_num = 0;
	scope_pos = 0;	

	file = file_name;	
}

//檢查型態
int Check::type_check(string a)
{
	 for(int i = 0 ; i < 4 ; i++)
   {
      if(a == type[i])
         return i;
   }
   return 4;
}
//檢查變數
int Check::var_check(string a , string b)
{
   for(int i = 0 ; i < sizeof(var_save)/sizeof(*var_save);i++)
   {
         if(a == var_save[i] && b == scope_save[i])
            return i;
   }
	for(int i = 0 ; i < sizeof(var_save)/sizeof(*var_save);i++)
   {
         if(a == var_save[i])
            return i;
   }

	return sizeof(var_save)/sizeof(*var_save);
}
//切割字串
int Check::Check_s(string word) {
   string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
   int count = -1;

   for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
      if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
         count = word.find(temp[i]);
      }
   }
   return count;
}
//切割字串
int Check::length(string word) {
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
//檢查運算元
int Check::check_operator(int a){
   for(int i = a ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
   {
      if(line_save[i] == "+" || line_save[i] == "-" || line_save[i] == "*" || line_save[i] == "/")
         return 1;
   }
   return 0;
}
//檢查函式
int Check::check_function(int a){
   for(int i = a ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
   {
      for(int j = 0 ; j < sizeof(line_save)/sizeof(*line_save) ; j++)
      {
         if(line_save[i] == var_save[j] &&  function_save[j] == "true")
            return j;
      }
   }

   return sizeof(line_save)/sizeof(*line_save);
}


//將symbol_table 放入scope type var array function矩陣中
void Check::create_array()
{
	ifstream fin("data/symbol_table.txt");
	string line;
	int find = 0;
	while(getline(fin, line))
	{
		istringstream fin_word(line);
		string word = "";

		while(fin_word >> word) 
		{
         while(word != "")
			{
				find = 1;
            line_save[order] = word;
            order = order + 1;
            word = "";
         }
      }

		
		for(int i = 0 ; i < 5; i++)
   	{
      	if(i == 0)
				scope_save[total_num] = line_save[i];
			else if(i==1)
            var_save[total_num] = line_save[i];
         else if(i==2)
            type_save[total_num] = line_save[i];
         else if(i==3)
            array_save[total_num] = line_save[i];
         else if(i==4)
            function_save[total_num] = line_save[i];
   	}
		if(find == 1)
			total_num = total_num + 1;
		find = 0;
		memcpy(line_save,empty,sizeof(line_save));
		order = 0;
	}
/*
	for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
   {
		cout << "scope" << scope_save[i] << " ";
		cout << "var " << var_save[i] << " ";
		cout << "type " << type_save[i] << " ";
		cout << "array" << array_save[i] << " ";
		cout << "function" << function_save[i] <<"\n";
	}
*/	
}

//檢查型態錯誤
void Check::type_warning()
{
   int one_pos = 0;
   int two_pos = 0;
   int one_type = 0;
   int two_type = 0;
   int first = 0;

	//處理.c檔
   ifstream fin(file.c_str());
   string line;
   while(getline(fin, line))
   {
      stringstream fin_word(line);
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
            line_save[order] = word;
            order = order + 1;

            pos = 0;
            word = remain;
            remain = "";
         }
      }

		//一行一行判斷
      for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
      {
         //cout << line_save[i] << " ";
         if(line_save[i][0] != '\0')
         {
				//算scope
				if(line_save[i]=="{")
					scope_pos = scope_pos + 1;

            int var_pos = 0;

            string word;
            word = line_save[i];

				//將int轉成string
				stringstream change;
				string scope;

            change << scope_pos;
            change >> scope;
            change.clear();

				//若word在存放變數的矩陣中找的到
            if(var_check(word , scope) < sizeof(var_save)/sizeof(*var_save))
            {
               var_pos = var_check(word,scope);//紀錄矩陣位置
               int type_num = type_check(type_save[var_pos]);//紀錄型態

					if(array_save[var_pos] == "true")
						i=i+3;
 
               if(line_save[i + 1] == "=")//遇到等號
               {	
                  int start = i+2;//建立起點
                  int op_num = check_operator(start);//運算符號數量
						int fuc_num = check_function(start);//function位置
						
						for(int j=start ; j<sizeof(line_save)/sizeof(*line_save) ; j++)
                  {	
							if(op_num == 0)//若無運算子
							{
								//判斷數字
                     	if(isdigit(line_save[j][0]) != 0 && fuc_num == sizeof(line_save)/sizeof(*line_save))
                     	{
                        	if(line_save[j].find(".") != -1)//小數
                        	{
                           	if(type_num == 0)
                              	cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << line_save[j] << " " << "double" <<endl;
                        	}
                        	else
                        	{
                           	if(type_num == 2 || type_num ==3)//整數
                              	cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << line_save[j] << " " << "int" <<endl;
                        	}
                     	}
								//判斷函式
								else if(fuc_num < sizeof(line_save)/sizeof(*line_save) && line_save[j] == var_save[fuc_num])
								{
									if(type_num == 0 && (type_save[fuc_num] == "float" || type_save[fuc_num] == "double"))
										cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << " " << type_save[fuc_num] <<endl;
                           if((type_num == 3 || type_num == 2) && type_save[fuc_num] == "int")
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << " " << type_save[fuc_num] <<endl;
								}	
								//判斷變數
								else if(var_check(line_save[j],scope) < sizeof(var_save)/sizeof(*var_save) && fuc_num == sizeof(line_save)/sizeof(*line_save))
								{
			
									int find_pos = var_check(line_save[j],scope);
    
			                  if(type_num == 0 && (type_save[find_pos] == "float" || type_save[find_pos] == "double"))
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << var_save[find_pos] << " " <<type_save[find_pos] <<endl;
									if((type_num == 3 || type_num == 2) && type_save[find_pos] == "int")
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << var_save[find_pos] << " " <<type_save[find_pos] <<endl;
								}
							}
							else//若有運算子
							{
								if(line_save[j] == "+" || line_save[j] == "-" ||line_save[j] == "*" ||line_save[j] == "/")
								{
									if(first == 0)
									{
										//左邊
										one_pos = var_check(line_save[j-1] , scope);								
										one_type = type_check(type_save[one_pos]);
										
										//右邊
	                        	two_pos = var_check(line_save[j+1] , scope);
										two_type = type_check(type_save[two_pos]);
						
										if(one_type == 0 && (two_type == 2||two_type == 3)){
                              	cout << "warning " << var_save[one_pos] << " " << type_save[one_pos] << " " << var_save[two_pos] << " " <<type_save[two_pos] <<endl;
											one_type = two_type;
										}
										if((one_type == 2||one_type == 3) && two_type == 0)
                              	cout << "warning " << var_save[one_pos] << " " << type_save[one_pos] << " " << var_save[two_pos] << " " <<type_save[two_pos] <<endl;
										first = 1;
									}
									else
									{
                              two_pos = var_check(line_save[j+1] , scope);
                              two_type = type_check(type_save[two_pos]);

                              if(one_type == 0 && (two_type == 2||two_type == 3)){
                                 cout << "warning " << "temp" << " " << type[one_type] << " " << var_save[two_pos] << " " <<type_save[two_pos] <<endl;
                                 one_type = two_type;
										}
                              if((one_type == 2||one_type == 3) && two_type == 0)
                                 cout << "warning " << "temp" << " " << type[one_type] << " " << var_save[two_pos] << " " <<type_save[two_pos] <<endl;
									}
								}
								else if(line_save[j] == ";" && first == 1)//結束比對等號前變數
								{
	                           if(type_num == 0 && (one_type == 2||one_type==3))
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << " " <<type[one_type] <<endl;
                              if((type_num == 2 || type_num == 3) && one_type==0)
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << " " <<type[one_type] <<endl;
								}
							}	
                  }
						i = sizeof(line_save)/sizeof(*line_save);//此行跑完
						first = 0;
               }
            }
         }
      }
         order = 0;
         memcpy(line_save,empty,sizeof(line_save));
   }
}
