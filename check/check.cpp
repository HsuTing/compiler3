#include "check.h"

Check::Check(string file_name) {
	
 	type[0] = "int";
	type[1] = "char";
	type[2] = "float";
	type[3] = "double"; 	

	order = 0;
   type_found = 0;
   var_found = 0;

   type_num = 0;
   var_num = 0;
   value_num = 0;
	
	file = file_name;	
}

int Check::type_check(string a , int b)
{
	 for(int i = 0 ; i < 4 ; i++)
   {
      if(a == type[i] && line_save[b+2] != "(")
         return i;
   }
   return 4;
}

int Check::var_check(string a)
{
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

void Check::start()
{
	ifstream fin(file.c_str());
	string line;
	while(getline(fin, line))
	{
		istringstream fin_word(line);
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
			cout << line_save[i] << " ";
			if(line_save[i][0] != '\0')
			{
				int array_pos = type_check(line_save[i] , i);
				if(array_pos < 4)
				{
					type_save[type_num] = line_save[i];
               type_num = type_num + 1;
               type_found = 1;
					i = i + 1;
				}
				
				
					
				if(type_found == 1 && isalpha(line_save[i][0]) != 0 && line_save[i+1] != "(" && keyword_check(line_save[i]) == 0)
				{
						if(line_save[i+1] == "[")
						{
							int len = 0;
							string input;
							string array_pos;
							stringstream change;
							change << line_save[i+2];

							change >> len;
							change.clear();
							int first = 0;
							for(int j =0 ; j <len ; j++)
							{
								change << j;
								change >> array_pos;
								change.clear();
								input = line_save[i] + line_save[i+1] + array_pos + line_save[i+3];
								if(first == 0)
								{
									var_save[var_num] = input;
									var_num = var_num + 1;
									first = 1;
								}
								else
								{
									type_save[type_num] = type_save[type_num-1];
									type_num = type_num + 1;
                           var_save[var_num] = input;
                           var_num = var_num + 1;
								}		
							}
					}
					else{	
						var_save[var_num] = line_save[i];
						var_num = var_num + 1;
						i = i + 1;
					}
				}

				int save_pos = 0;
				string word;
				word = line_save[i];
				if(line_save[i+1] == "[")
				{
					word = line_save[i] + line_save[i+1] + line_save[i+2] + line_save[i+3];
					i = i + 3;
				}
				cout << word << " ";
				
				if(var_check(word) < sizeof(var_save)/sizeof(*var_save))
				{
					cout << "find " << word << " "  << line_save[i];
					save_pos = var_check(word);
					if(line_save[i + 1] == "=")
					{
						if(isdigit(line_save[i+2][0]) != 0)
						{
							value_save[save_pos] = line_save[i+2];
						}
					}
				}	
			}
		}

			cout << endl;
			order = 0;
			type_found = 0;
			var_found = 0;
			memcpy(line_save,empty,sizeof(line_save));
	}

	for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
   {
		cout << "var " << var_save[i] << " ";
		cout << "type " << type_save[i] << " ";
		cout << "value" << value_save[i] << "\n";
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
