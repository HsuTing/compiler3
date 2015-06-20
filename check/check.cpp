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

int Check::type_check(string a)
{
	 for(int i = 0 ; i < 4 ; i++)
   {
      if(a == type[i])
         return i;
   }
   return 4;
}

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

int Check::keyword_check(string a)
{
		string keyword[] = {"return","break","print","if","else","while","break","for"};
		for(int i = 0 ; i < sizeof(keyword)/sizeof(*keyword) ; i++)
		{
			if(a == keyword[i])
			{
					return 1;
			}
		}
		return 0;
}

void Check::create_array()
{
	ifstream fin("symbol_table.txt");
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

	for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
   {
		cout << "scope" << scope_save[i] << " ";
		cout << "var " << var_save[i] << " ";
		cout << "type " << type_save[i] << " ";
		cout << "array" << array_save[i] << " ";
		cout << "function" << function_save[i] <<"\n";
	}
	
}
void Check::type_checking()
{
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

      for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
      {
         //cout << line_save[i] << " ";
         if(line_save[i][0] != '\0')
         {
				if(line_save[i]=="{")
					scope_pos = scope_pos + 1;


            int var_pos = 0;

            string word;
            word = line_save[i];

				stringstream change;
				string scope;

            change << scope_pos;
            change >> scope;
            change.clear();


            //cout << word << " ";

            if(var_check(word , scope) < sizeof(var_save)/sizeof(*var_save))
            {
               var_pos = var_check(word,scope);
               int type_num = type_check(type_save[var_pos]);
					//cout << var_pos <<" " << scope << " " ;

					if(array_save[var_pos] == "true")
						i=i+3;
 
               if(line_save[i + 1] == "=")
               {
                  //cout << type_num ;
						//cout << line_save[i] << line_save[i+1] << line_save[i+2]  ;
                  int start = i+2;
                  int op_num = check_operator(start);
						int fuc_num = check_function(start);
			 			//cout << line_save[start] << fuc_num;
						//cout << op_num ;	
						for(int j=start ; j<sizeof(line_save)/sizeof(*line_save) ; j++)
                  {	
							if(op_num == 0)
							{
								//cout << line_save[j];
                     	if(isdigit(line_save[j][0]) != 0 && fuc_num == sizeof(line_save)/sizeof(*line_save))
                     	{
                        	if(line_save[j].find(".") != -1)
                        	{
                           	if(type_num == 0)
                              	cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << line_save[j] << " " << "double" <<endl;
                        	}
                        	else
                        	{
                           	if(type_num == 2 || type_num ==3)
                              	cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << line_save[j] << " " << "int" <<endl;
                        	}
                     	}
								else if(fuc_num < sizeof(line_save)/sizeof(*line_save) && line_save[j] == var_save[fuc_num])
								{
									if(type_num == 0 && (type_save[fuc_num] == "float" || type_save[fuc_num] == "double"))
										cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << type_save[fuc_num] <<endl;
                           if((type_num == 3 || type_num == 2) && type_save[fuc_num] == "int")
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << "temp" << type_save[fuc_num] <<endl;
								}	
								else if(var_check(line_save[j],scope) < sizeof(var_save)/sizeof(*var_save) && fuc_num == sizeof(line_save)/sizeof(*line_save))
								{
			
									int find_pos = var_check(line_save[j],scope);
    
			                  if(type_num == 0 && (type_save[find_pos] == "float" || type_save[find_pos] == "double"))
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << var_save[find_pos] << " " <<type_save[find_pos] <<endl;
									if((type_num == 3 || type_num == 2) && type_save[find_pos] == "int")
                              cout << "warning " << var_save[var_pos] << " " << type_save[var_pos] << " " << var_save[find_pos] << " " <<type_save[find_pos] <<endl;
								}
							}
							/*else
							{	
							}*/
							
                  }
						i = sizeof(line_save)/sizeof(*line_save);
               }
            }
         }
      }
         order = 0;
         memcpy(line_save,empty,sizeof(line_save));
   }


}
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

int Check::check_operator(int a){
	for(int i = a ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
	{
		if(line_save[i] == "+" || line_save[i] == "-" || line_save[i] == "*" || line_save[i] == "/")
			return 1;
	}
	return 0;
}

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

