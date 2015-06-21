#include "llvm.h"

Stack<string>inputStack(150);

Llvm::Llvm() {

		int var_num = 0;
		string input_array[150];

      ifstream fin("main.c");
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
}

void Llvm::create_array()
{
   ifstream fin("data/symbol_table.txt");
   string line;   

	while(getline(fin, line))
   {
      istringstream fin_word(line);
      string word = "";

		int word_count = 0;
      //set information
      string scope = "";
      string symbol = "";
      string type = "";
      string array = "";
      string function = "";
      

		while(fin_word >> word)
      {
          switch(word_count) {
            case 0:
               scope = word;
               break;
            case 1:
               symbol = word;
               break;
            case 2:
               type = word;
               break;
            case 3:
               array = word;
               break;
            case 4:
               function = word;
               break;
         }
         word_count = word_count + 1;
      }
		if(word_count != 0)
		{
			scope_save[line_count] = scope;
      	symbol_save[line_count] = symbol;
			type_save[line_count] = type;
      	array_save[line_count] = array;
      	function_save[line_count] = function;
		
     		line_count = line_count + 1;
		}
   }
   for(int i = 0 ; i < line_count ; i++)
   {
      cout << "scope" << scope_save[i] << " ";
      cout << "symbol " << symbol_save[i] << " ";
      cout << "type " << type_save[i] << " ";
      cout << "array" << array_save[i] << " ";
      cout << "function" << function_save[i] <<"\n";
   }
}


void Llvm::S(string input){
	if(input == "int" || input == "char" || input == " double" || input == "float")
	{
		Program(inputStack.top());
	}
}
void Llvm::Program(string input){
	if(input == "int" || input == "char" || input == " double" || input == "float" || input == "$")
		DecList(inputStack.top());
}
void Llvm::DecList(string input){
	if(input == "int" || input == "char" || input == " double" || input == "float")
		DecList_(inputStack.top());
	//else if(input == "$");
}
void Llvm::DecList_(string input){
	string	type;
	if(input == "int" || input == "char" || input == " double" || input == "float")
	{
		type = Type(input);
		id(inputStack.top() , type);
	}
	//else if(input == "$");
}
string Llvm::Type(string input){
	
	inputStack.pop("");

	if(input == "int")
		return "int";
	else if(input == "char")
		return "char";
	else if(input == "float")
		return "float";
	else if(input == "double")
		return "double";
}
void Llvm::id(string input , string type)
{
	int find_pos;
	string scope;
	
	for(int i = 0 ; i <line_count ;i++)
	{
		if(input == symbol_save[i] && type == type_save[i])
		{
			find_pos = i;
		}
	}
	
	scope = scope_save[find_pos];
	
	/*if(scope == 0)
	{
		cout << "@" << input << "=" << */
}

int Llvm::Check_s(string word) {
   string temp[] = {"{", "}", "[", "]", "(", ")", ";", ",", "=", "!", "+", "-", "*", "/", "==", "!=", "<", ">", "<=", ">=", "&&", "||"};
   int count = -1;

   for(int i = 0; i < (sizeof(temp) / sizeof(temp[0])); i++) {
      if(word.find(temp[i]) != -1 && count > word.find(temp[i])) {
         count = word.find(temp[i]);
      }
   }
   return count;
}

int Llvm::length(string word) {
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
