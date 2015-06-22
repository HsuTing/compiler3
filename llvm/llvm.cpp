#include "llvm.h"

Stack<string>inputStack(150);

Llvm::Llvm() {

		first = 0;//測試用 之後砍

		create_array();
		int var_num = 0;
		string input_array[150];

      ifstream fin("main_2.c");
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

		S(inputStack.top());
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
	if(input == "int" || input == "char" || input == "double" || input == "float" || input =="")
		Program(inputStack.top());
}

void Llvm::Program(string input){
	if(input == "int" || input == "char" || input == "double" || input == "float" || input == "")
		DecList(inputStack.top());
}

void Llvm::DecList(string input){
	
	if(input == "int" || input == "char" || input == "double" || input == "float")
	{
		DecList_(inputStack.top());
		if(first == 0)
		{
			DecList(inputStack.top());
			first = 1;
		}
	}
	else if(input == "")
	{
		;//cout << "eplison" << endl;
	}
}

void Llvm::DecList_(string input){
	string	type;

	if(input == "int" || input == "char" || input == "double" || input == "float")
	{
		type = Type(input);
		DecList__id(inputStack.top() , type);
		Decl(inputStack.top(),type);
	}
	else if(input == "");
	{
		;
	}
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

void Llvm::DecList__id(string input , string type)
{
	//id
	inputStack.pop("");
	
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
	
	if(inputStack.top() == ";")
	{
		if(scope == "0")
			cout << "@" << input << "= " << "Common global " ;
		else
			cout << "%" << input << "= " << "alloca " ;
	
	   if(type == "int")
		   cout << "i32 0" << endl;
   	else if(type == "char")
      	cout << "i8 " << endl;
   	else if(type == "float")
      	cout << "float " << endl;
   	else if(type == "double")
      	cout << "double " << endl;
	}
	else if(inputStack.top() == "(")
	{
		cout << "define ";

      if(type == "int")
         cout << "i32 ";
      else if(type == "char")
         cout << "i8 ";
      else if(type == "float")
         cout << "float ";
      else if(type == "double")
         cout << "double ";
		cout << "@" << input ;
	}
	else if(inputStack.top() == "["){;}
	else{;}
}

void Llvm::Decl(string input , string type)
{
	if(input == "(")
		FunDecl(inputStack.top());
	else if(input == ";"||input == "[")
		VarDecl_(inputStack.top() , type);
}

void Llvm::VarDecl(string input)
{
   string   type;

   if(input == "int" || input == "char" || input == "double" || input == "float")
   {
      type = Type(input);
      VarDecl_id(inputStack.top() , type);
      VarDecl_(inputStack.top() , type);
   }

}

void Llvm::VarDecl_id(string input , string type)
{
   inputStack.pop("");

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

   cout << "%" << input << "= " << "alloca " ;

	if(inputStack.top() == ";"){
   	if(type == "int")
      	cout << "i32 " << endl;
   	else if(type == "char")
      	cout << "i8 " << endl;
  		else if(type == "float")
      	cout << "float " << endl;
   	else if(type == "double")
      	cout << "double " << endl;
	}
}


void Llvm::VarDecl_(string input , string type)
{
	string num;
	if(input == ";")
		inputStack.pop("");
	else if(input == "["){
		//[
		cout << "[";
		inputStack.pop("");
		//num
		num = inputStack.top();
      if(type == "int")
         cout << num << " x i32";
      else if(type == "char")
         cout << num << " x i8";
      else if(type == "float")
         cout << num << " x float";
      else if(type == "double")
         cout << num << " x double";
		inputStack.pop("");
		//]
		cout << "]" << endl;
		inputStack.pop("");
		//;
		inputStack.pop("");
	}
}

void Llvm::FunDecl(string input)
{
	if(input == "(")
	{
		//(
		cout << input ;
		inputStack.pop("");
		//Parameter
		ParamDeclList(inputStack.top());
		//)
		cout << ")";
		inputStack.pop("");
		//Block
		Block(inputStack.top());
	}
}

void Llvm::VarDeclList(string input)
{
	if(input == "int" || input == "char" || input == "double" || input == "float")
	{
		VarDecl(inputStack.top());
		VarDeclList(inputStack.top());
	}
	else{;}
}

void Llvm::ParamDeclList(string input)
{;
	//if(input == "int" || input == "char" || input == " double" || input == "float")
		//ParamDeclListTail(inputStack.top());
}

void Llvm::Block(string input)
{
	if(input == "{")
	{
		//{
		cout << "{" << endl;
		inputStack.pop("");
		//VarDeclList
		VarDeclList(inputStack.top());
		//StmtList
		//}
	}
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
