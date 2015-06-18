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

int Check::type_check(string a , string b[])
{
   for(int i = 0 ; i < 4 ; i++)
   {
      if(a == b[i])
         return i;
   }
   return 4;
}

int Check::var_check(string a , string b[])
{
   for(int i = 0 ; i < sizeof(b)/sizeof(*b);i++)
   {
         if(a == b[i])
            return 1;
         return 0;
   }
}

void Check::start()
{
	ifstream fin("test.c");

	if(fin.is_open())
	{
		while(getline(fin,line))
		{

			for(int i = 0; i < line.length() ; i++)
			{
				if(isgraph(line[i]) != 0)
				{
					cout << line[i] << '\n';
				}
			}
			
			//cout << word << '\n';			
			//word = "";
			/*for(int i = 0 ; i < sizeof(line_save)/sizeof(*line_save) ; i++)
			{
				cout << line_save[i] << '\n';
				if(line_save[i][0] != '\0')
				{
					int pos = type_check(line_save[i],type);
					if(pos < 4)
					{
						type_save[type_num] = type[pos];
                  type_num = type_num + 1;
                  type_found = 1;
					}
					
					if(type_found == 1 && isalpha(line_save[i][0]) != 0 && type_check(line_save[i],type) == 4 && line_save[i+1] != "(")
					{
						for(int j =0;j<sizeof(type)/sizeof(*type);j++)
						{
							if(line_save[i] == var_save[j])
							{
								var_found = 1;
							}
						}
						if(var_found == 0)
						{
							var_save[var_num] = line_save[i];
							var_num = var_num + 1;
						}
					}
				
				
					
				}
			}

			order = 0;
			type_found = 0;
			var_found = 0;
			memcpy(line_save,empty,sizeof(line_save));*/
		}
	}

	/*for(int i = 0 ; i < 30;i++)//sizeof(line_save)/sizeof(*line_save) ; i++)
   {
		cout << "var " << var_save[i] << " ";
		cout << "type " << type_save[i] << '\n';
	}*/
}
