#include "llvm.h"

Stack<string>inputStack(150);

Llvm::Llvm() {

		//first = 0;//測試用 之後砍
		total_num = 1;
		scope = 0;
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

		for(int i = 0 ; i < 5;i++)
		{
      cout << "symbol " << stmt_symbol[i] << " ";
      cout << "type " << stmt_type[i] << " ";
      cout << "array" << stmt_array[i] << " ";
		cout << "bin " << binop[i] << " " ;
		cout << endl;
		}
	
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
		DecList(inputStack.top());	
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
	
	if(inputStack.top() == ";")//一般宣告
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
	else if(inputStack.top() == "(")//function
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
   string scope_str;
	stringstream change;
	change << scope;
	change >> scope_str;

   for(int i = 0 ; i <line_count ;i++)
   {
      if(input == symbol_save[i] && type == type_save[i] && scope_save[i] == scope_str)
      {
         find_pos = i;
      }
   }

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
		//遇到function param_num歸零
			param_num = 0;
			memcpy(param_type,empty,sizeof(empty));
         memcpy(param_symbol,empty,sizeof(empty));
         memcpy(param_array,empty,sizeof(empty));		
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
{
	if(input == "int" || input == "char" || input == "double" || input == "float")
		ParamDeclListTail(inputStack.top());
}

void Llvm::ParamDeclListTail(string input)
{
	if(input == "int" || input == "char" || input == "double" || input == "float")
   {
	   ParamDecl(inputStack.top());
		ParamDeclListTail_(inputStack.top());
	}
}

void Llvm::ParamDeclListTail_(string input)
{
	if(input == ","){
		cout << " , " ;
		inputStack.pop("");
		ParamDeclListTail(inputStack.top());
	}
	else if(input == ")"){;}
}		

void Llvm::ParamDecl(string input)
{
	string type;
	 if(input == "int" || input == "char" || input == "double" || input == "float")
   {	
		//type
      type = Type(input);
		//id
      ParamDecl_id(inputStack.top() , type);
		//ParamDecl'
      ParamDecl_(inputStack.top());
   }
}

void Llvm::ParamDecl_id(string input , string type)
{
   inputStack.pop("");

   int find_pos;
   string scope_str;
   stringstream change;
   change << scope;
   change >> scope_str;
  
   for(int i = 0 ; i <line_count ;i++)
   {
      if(input == symbol_save[i] && type == type_save[i] && scope_save[i] == scope_str)
      {
         find_pos = i;
      }
   }

	string array = array_save[find_pos];

   if(type == "int")
      cout << "i32";
   else if(type == "char")
      cout << "i8";
   else if(type == "float")
      cout << "float";
   else if(type == "double")
      cout << "double";
   
	if(array == "true")
		cout << "*";
	cout << " %" << input;

	param_type[param_num] = type;
	param_symbol[param_num] = input;
	param_array[param_num] = array;
	param_num = param_num + 1;
	total_num = total_num + 1;
}

void Llvm::ParamDecl_(string input)
{
	if(input == "[")
	{
		cout << "[ ";
		inputStack.pop("");
		cout << "]";
		inputStack.pop("");
	}
	else{;}
}

void Llvm::Block(string input)
{
	if(input == "{")
	{
		//{
		cout << "{" << endl;
		inputStack.pop("");
		scope = scope + 1;
		// param_assign
		for(int i = 0 ; i <= param_num-1 || i == 0 ; i++)
		{
			stringstream change;
			string num;
			change << total_num;
			change >> num;

			cout << "%" << num << " = alloca ";
			
			string type = param_type[i];

			if(param_num == 0)
				type = "int";

		   if(type == "int")
		      cout << "i32";
   		else if(type == "char")
      		cout << "i8";
   		else if(type == "float")
      		cout << "float";
   		else if(type == "double")
      		cout << "double";
			
			if(param_array[i] == "true")
				cout << "*";
			cout << endl;
			
			total_num = total_num + 1;
		}
		//VarDeclList
		VarDeclList(inputStack.top());
		//StmtList
		StmtList(inputStack.top());
		//}
		cout << inputStack.top() <<endl;
		inputStack.pop("");
		total_num = 0;
	}
}
void Llvm::StmtList(string input)
{
	//stmt歸零
   stmt_num = 0;
	bin_num = 0;
   memcpy(stmt_type,empty,sizeof(empty));
   memcpy(stmt_symbol,empty,sizeof(empty));
   memcpy(stmt_array,empty,sizeof(empty));
	memcpy(binop,empty,sizeof(empty));

	//Stmt
	Stmt(inputStack.top());
	//處理Stmt
	string first_type = stmt_type[0];
	string first_symbol = stmt_symbol[0];
	string first_array = stmt_array[0];
	
//	if(bin_num == 0)
//	{
		for(int i = 1 ; i < stmt_num ; i++)
      {
			//cout << stmt_symbol[i] << " " ;
         stringstream change;
         string num;
         change << total_num;
         change >> num;
			change.clear();

			if(isalpha(stmt_symbol[i][0]) != 0)
			{
				cout << "%" << num << " = load ";

         	string type = stmt_type[i];
				
				cout << type_change(type) << " %" << stmt_symbol[i] << endl;
			
				type_checking(first_type , type);
				
	         change << total_num;
	         change >> num;
   	      change.clear();

				if(bin_num == 0)
				{
					cout << "store " << type_change(first_type) << " %" << num << ", " << type_change(first_type) << "* %" << first_symbol << endl;
				}


				total_num = total_num + 1;
			}
			else if(isdigit(stmt_symbol[i][0]) != 0)
			{
            change << total_num;
            change >> num;
            change.clear();
				if(first_type == "int")
				{
					if(stmt_symbol[i].find(".")!=-1)
					{
						stmt_symbol[i] = stmt_symbol[i].substr(0,stmt_symbol[i].find("."));
					}
				}
				if(bin_num ==0)
				{
            	cout << "store " << type_change(first_type) << " " << stmt_symbol[i] <<", " << type_change(first_type) << "* %" << first_symbol << endl;
				}
			}
      }
	//}			

	//StmtList'
	StmtList_(inputStack.top());
}

void Llvm::StmtList_(string input)
{
	if(input == "}"){;}
	else
		StmtList(inputStack.top());
}

void Llvm::Stmt(string input)
{
	if(input == ";"){	
		//;
		inputStack.pop("");
	}
	else if(input == "break"){
		//break
		inputStack.pop("");
		//;
		inputStack.pop("");
	}
	else if(input == "return"){	
		//return
		cout << "ret ";
		inputStack.pop("");
		//Expr
		Expr(inputStack.top());
		//;
		inputStack.pop("");
	}
	else if(input == "if"){
		int check_if = 1;
		//if
		inputStack.pop("");
		//(
		inputStack.pop("");
		//Expr
		Expr(inputStack.top());
		//)
		inputStack.pop("");
		//Stmt
		Stmt(inputStack.top());
		//else
		inputStack.pop("");
		//Stmt
		Stmt(inputStack.top());
	}
	else if(input == "while")
	{
		int check_while = 1;
		//while
		inputStack.pop("");
		//(
		inputStack.pop("");
      //Expr
      Expr(inputStack.top());
      //)
      inputStack.pop("");
      //Stmt
      Stmt(inputStack.top());
	}
	else if(input == "print")
	{
		cout << "print" ;
		inputStack.pop("");
		cout << inputStack.top();
		inputStack.pop("");
		//;
		inputStack.pop("");
	}
	else if(input == "{")
		Block(inputStack.top());
	else
	{		
		//Expr
		Expr(inputStack.top());
		//;
		inputStack.pop("");
	}
}

void Llvm::Expr(string input)
{
   string scope_str;
   stringstream change;
   change << scope;
   change >> scope_str;

	if(input == "!" || input == "-"){
		UnaryOp(inputStack.top());
		Expr(inputStack.top());
	}
	else if(input == "("){
		inputStack.pop("");
		Expr(inputStack.top());
      inputStack.pop("");
		Expr_(inputStack.top());
	}
	else
	{
		if(isalpha(input[0]) != 0)
		{	
			//id
			string id = inputStack.top();
			inputStack.pop("");

			//處理id
		   int find_pos;

		   for(int i = 0 ; i <line_count ;i++)
  			{
     			if(input == symbol_save[i] && scope_str == scope_save[i])
     			{
         		find_pos = i;
      		}
   		}

			stmt_symbol[stmt_num] = symbol_save[find_pos];
			stmt_type[stmt_num] = type_save[find_pos];
			stmt_array[stmt_num] = array_save[find_pos];

			stmt_num = stmt_num + 1;

			//ExprIdTail
			ExprIdTail(inputStack.top() , id);
		}
		else if(isdigit(input[0]) != 0)
		{
			//num
			string num = inputStack.top();
			inputStack.pop("");
			//處理num
         stmt_symbol[stmt_num] = num;
			if(input.find(".") == -1)
         	stmt_type[stmt_num] = "int";
			else stmt_type[stmt_num] = "double";
         stmt_array[stmt_num] = "false";

         stmt_num = stmt_num + 1;
			//Expr'
			Expr_(inputStack.top());
		}
	}
}

void Llvm::ExprIdTail(string input , string id)
{
	if(input == "=")
	{
		inputStack.pop("");
		Expr(inputStack.top());
	}
	else if(input == "(")
	{
      inputStack.pop("");
		ExprList(inputStack.top());
      inputStack.pop("");
		Expr_(inputStack.top());
	}
	else if(input == "[")
	{
      inputStack.pop("");
		Expr(inputStack.top());
      inputStack.pop("");
		ExprArrayTail(inputStack.top());
	}
	else
		Expr_(inputStack.top());
}

void Llvm::ExprArrayTail(string input)
{
	if(input == "=")
	{
		inputStack.pop("");
		Expr(inputStack.top());
	}
	else
		Expr_(inputStack.top());
}

void Llvm::Expr_(string input)
{
	if(input == ";" || input == ")" || input == "]"){;}
	else{
		BinOp(inputStack.top());
		Expr(inputStack.top());
	}	
}

void Llvm::ExprList(string input)
{
	if(input == ")"){;}
	else
		ExprListTail(inputStack.top());
}

void Llvm::ExprListTail(string input)
{
	Expr(inputStack.top());
	ExprListTail_(inputStack.top());
}

void Llvm::ExprListTail_(string input)
{
	if(input == ","){
		//,
		cout << " , " ; 
      inputStack.pop("");
		ExprListTail(inputStack.top());
	}
	else{;}
}

void Llvm::UnaryOp(string input)
{
	cout << input ;
	inputStack.pop("");
}
		
void Llvm::BinOp(string input)
{
	binop[bin_num] = input;
	bin_num = bin_num + 1;
	inputStack.pop("");
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

string Llvm::type_change(string type)
{
	string new_type = "";
	if(type == "int")
   	new_type = "i32";
   else if(type == "char")
   	new_type = "i8 ";
   else if(type == "float")
      new_type = "float ";
   else if(type == "double")
      new_type = "double ";

	return new_type;
}

void Llvm::type_checking(string first_type , string type)
{
	if(first_type != type)
	{
		stringstream change;
		string previous_num;
		string num;
		change << total_num;
		change >> previous_num;
		change.clear();

		total_num = total_num + 1;
	
		change << total_num;
		change>>num;
		
		if(first_type == "int" && (type == "double" || type == "float"))
		{
			cout <<  "%" << num << " = fptosi" << type_change(type) << " %" << previous_num << " to " << type_change(first_type) << endl;
		}
		else if((first_type == "double" || first_type == "float") && type == "int")
		{
	      cout <<  "%" << num << " = sitofp" << type_change(type) << " %" << previous_num << " to " << type_change(first_type) << endl;
		}
	}
}

