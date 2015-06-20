#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

class Check {
	public:
		Check(string file_name);
		int type_check(string a);
		int var_check(string a , string b);
		int keyword_check(string a);
		void create_array();
		void type_checking();
		int Check_s(string word);
		int length(string word);
		int check_operator(int a);
		int check_function(int a);
	private:
		   string type[4];

   		string line_save[20];
			string scope_save[20];
   		string var_save[20];
   		string type_save[20];
   		string array_save[20];
			string function_save[20];
			string empty[20];
			
			string file;
			int scope_pos;

   		int order;	
			int total_num;
};
