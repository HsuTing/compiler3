#include "llvm.h"

Stack<string>inputStack(150);
fstream file;

Llvm::Llvm() {

		//first = 0;//測試用 之後砍
		array_num = 0;
		total_num = 1;
		scope = 0;
		create_array();

		int var_num = 0;
		string input_array[150];

      ifstream fin("main.c");
      string new_line = "";

		file.open("main.ll",ios::out);

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

		file << "@.str = private constant [3 x i8] c\"\%d\\00\"" << endl;
		file << "@.str1 = private constant [3 x i8] c\"\%f\\00\""<< endl;

		S(inputStack.top());


		file << "declare i32 @printf(i8*, ...)" <<endl;
/*		for(int i = 0 ; i < 5;i++)
		{
      cout << "symbol " << stmt_symbol[i] << " ";
      cout << "type " << stmt_type[i] << " ";
      cout << "array" << stmt_array[i] << " ";
		cout << "bin " << binop[i] << " " ;
		cout << endl;
		}*/
/*  		for(int i = 0 ; i < array_num ; i++)
   	{
			cout << array_symbol[i];
			cout << array_len[i];
		}*/
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

/*   for(int i = 0 ; i < line_count ; i++)
   {
      cout << "scope" << scope_save[i] << " ";
      cout << "symbol " << symbol_save[i] << " ";
      cout << "type " << type_save[i] << " ";
      cout << "array" << array_save[i] << " ";
      cout << "function" << function_save[i] <<"\n";
   }*/
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
			file << "@" << input << "= " << "global " ;
		else
			file << "%" << input << "= " << "alloca " ;
	
	   if(type == "int")
		   file << "i32 0" << endl;
   	else if(type == "char")
      	file << "i8 " << endl;
   	else if(type == "float")
      	file << "float " << endl;
   	else if(type == "double")
      	file << "double " << endl;
	}
	else if(inputStack.top() == "(")//function
	{
		file << "define ";

      if(type == "int")
         file << "i32 ";
      else if(type == "char")
         file << "i8 ";
      else if(type == "float")
         file << "float ";
      else if(type == "double")
         file << "double ";
		file << "@" << input ;
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
	
	//存放矩陣長度
	if(array_save[find_pos] == "true")
		array_symbol[array_num] = input;

   file << "%" << input << "= " << "alloca " ;

	if(inputStack.top() == ";"){
   	if(type == "int")
      	file << "i32 " << endl;
   	else if(type == "char")
      	file << "i8 " << endl;
  		else if(type == "float")
      	file << "float " << endl;
   	else if(type == "double")
      	file << "double " << endl;
	}
}


void Llvm::VarDecl_(string input , string type)
{
	string num;
	if(input == ";")
		inputStack.pop("");
	else if(input == "["){
		//[
		file << "[";
		inputStack.pop("");
		//num
		num = inputStack.top();
      if(type == "int")
         file << num << " x i32";
      else if(type == "char")
         file << num << " x i8";
      else if(type == "float")
         file << num << " x float";
      else if(type == "double")
         file << num << " x double";

		array_len[array_num] = num;
		array_num = array_num + 1;

		inputStack.pop("");
		//]
		file << "]" << endl;
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
		file << input ;
		inputStack.pop("");
		//Parameter
		ParamDeclList(inputStack.top());
		//)
		file << ")";
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
		file << " , " ;
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
      file << "i32";
   else if(type == "char")
      file << "i8";
   else if(type == "float")
      file << "float";
   else if(type == "double")
      file << "double";
   
	if(array == "true")
		file << "*";
	file << " %" << input;

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
		file << "[ ";
		inputStack.pop("");
		file << "]";
		inputStack.pop("");
	}
	else{;}
}

void Llvm::Block(string input)
{
	if(input == "{")
	{
		//{
		file << "{" << endl;
		inputStack.pop("");
		scope = scope + 1;
		// param_assign
		for(int i = 0 ; i <= param_num-1 || i == 0 ; i++)
		{
			//stringstream change;
			//string num;
			//change << total_num;
			//change >> num;

			file << "%" << total_num << " = alloca ";
			
			string type = param_type[i];

			if(param_num == 0)
				type = "int";

		   if(type == "int")
		      file << "i32";
   		else if(type == "char")
      		file << "i8";
   		else if(type == "float")
      		file << "float";
   		else if(type == "double")
      		file << "double";
			
			if(param_array[i] == "true")
				file << "*";
			file << endl;
			
			total_num = total_num + 1;
		}
		//VarDeclList
		VarDeclList(inputStack.top());
		//StmtList
		StmtList(inputStack.top());
		//}
		file << inputStack.top() <<endl;
		inputStack.pop("");
		total_num = 1;
	}
}
void Llvm::StmtList(string input)
{
	string num = "";
	//stmt歸零
	first = 0;
   stmt_num = 0;
	bin_num = 0;
	memcpy(stmt_scope,empty,sizeof(empty));
   memcpy(stmt_type,empty,sizeof(empty));
   memcpy(stmt_symbol,empty,sizeof(empty));
   memcpy(stmt_array,empty,sizeof(empty));
	memcpy(stmt_function,empty,sizeof(empty));
	memcpy(binop,empty,sizeof(empty));

	//Stmt
	Stmt(inputStack.top());
	//處理Stmt
	string first_scope = stmt_scope[0];
	string first_type = stmt_type[0];
	string first_symbol = stmt_symbol[0];
	string first_array = stmt_array[0];
	string first_function = stmt_function[0];
	
	if(first_function == "true" && stmt_num > 0)
	{
		file << "%" << total_num << " = call " << type_change(first_type) << " @" << first_symbol << "()"<<endl;
		total_num = total_num + 1;
	}
	if(first_array == "true" && bin_num == 0)
	{
     for(int i = 0 ; i < array_num ; i++)
     {
     		if(array_symbol[i] == first_symbol)
         	num = array_len[i];
     }

		file << "%" << total_num << " = getelementptr inbounds [" << num << " x " << type_change(first_type) << "]* %" << first_symbol << ", i32 0, i64 " << stmt_symbol[1] << endl;
	}

	for(int i = 1 ; i < stmt_num ; i++)
   {
			if(first_array == "true" && first == 0)
			{
				i = 2;
				first = 1;
			}
			string type = "";
			if(stmt_array[i] == "true")
			{
				for(int j = 0 ; j < array_num ; j++)
				{
					if(array_symbol[j] == stmt_symbol[i])
						num = array_len[j];
				}

				file << "%" << total_num << " = getelementptr inbounds [" << num << " x " << type_change(stmt_type[i]) << "]* %" << stmt_symbol[i] << ", i32 0, i64 " << stmt_symbol[i+1] << endl;
				total_num = total_num + 1;
				file << "%" << total_num << " = load " << type_change(stmt_type[i]) <<"* %" << total_num-1 <<endl; 

				total_num = total_num + 1;
				if(bin_num == 0){
					total_num = total_num - 1;
					file << "store " << type_change(first_type) << " %" << total_num << ", " << type_change(first_type) << "* ";
					if(first_scope == "0")
						file << "@";
					else
						file << "%";
 					file << first_symbol << endl;	
					total_num = total_num + 1;
				}
			}
			else if(isalpha(stmt_symbol[i][0]) != 0)
			{
				file << "%" << total_num << " = load ";
				
         	type = stmt_type[i];
				
				file << type_change(type) << "* "; //%" << stmt_symbol[i] << endl;
				
            if(stmt_scope[i] == "0")
	            file << "@";
            else
               file << "%";
				file << stmt_symbol[i] << endl;

				if(bin_num == 0)
				{	
					type_checking(first_type , type , 0);
				}

				if(bin_num == 0)
				{
					if(stmt_array[i] == "true")
					{
		         	file << "store " << type_change(first_type) << " %" << total_num << ", " << type_change(first_type) << "* %" << total_num  << endl;
					}
					else
					{
						file << "store " << type_change(first_type) << " %" << total_num << ", " << type_change(first_type) << "* %" << first_symbol << endl;
					}
				}
				total_num = total_num + 1;
			}
			else if(isdigit(stmt_symbol[i][0]) != 0)
			{
				if(first_type == "int")
				{
					if(stmt_symbol[i].find(".")!=-1)
					{
						stmt_symbol[i] = stmt_symbol[i].substr(0,stmt_symbol[i].find("."));
					}
				}
				if(bin_num ==0)
				{
					if(first_array == "true")
					{
						file << "store " << type_change(first_type) << " " << stmt_symbol[i] <<", " << type_change(first_type) << "* %" << total_num << endl;
						total_num = total_num + 1;
					}
					else
					{	if(first_type == "double" && stmt_symbol[i].find(".") == -1)
							stmt_symbol[i].append(".0");
            		file << "store " << type_change(first_type) << " " << stmt_symbol[i] <<", " << type_change(first_type) << "* %" << first_symbol << endl;
					}
				}
			}
			if(first_array == "true" && bin_num !=0 && i == stmt_num-2)
			{
			   for(int j = 0 ; j < array_num ; j++)
            {
               if(array_symbol[j] == stmt_symbol[i])
                  num = array_len[j];
            }

				file << "%" << total_num << "= add " << type_change(first_type) << " %" << total_num -3 << " , %" << total_num -1 <<endl;
				total_num = total_num + 1;
		      file << "%" << total_num << " = getelementptr inbounds [" << num << " x " << type_change(first_type) << "]* %" << first_symbol << ", i32 0, i64 " << stmt_symbol[1] << endl;
            file << "store " << type_change(first_type) << " %" << total_num-1 <<", " << type_change(first_type) << "* %" << total_num << endl;
				total_num = total_num + 1;
			}


			
			if(i == 1)
			{
				temp_type = type;
				temp_symbol = stmt_symbol[i];
			}
			else if((i > 1 && bin_num != 0) && first_array !="true" )
			{
				//type_checking(temp_type , type , 1);
				file << "%" << total_num << " = ";
/*
				if(binop[i-2] == "+")
					cout << "add " << type << " %" <<(total_num-2)<< " , %" <<(total_num-1)<<endl;
				else if(binop[i-2] == "-")
               cout << "sub " << type << " %" <<(total_num-2)<< " , %" <<(total_num-1)<<endl;
            else if(binop[i-2] == "*")
               cout << "mul " << type << " %" <<(total_num-2)<< " , %" <<(total_num-1)<<endl;
            else if(binop[i-2] == "/")
               cout << "div " << type << " %" <<(total_num-2)<< " , %" <<(total_num-1)<<endl;
*/
				if(binop[i-2] == "+" || binop[i-2] == "-" || binop[i-2] == "*" || binop[i-2] == "/")
         	{
			   	if(binop[i-2] == "+")
               	file << "add " ;
            	else if(binop[i-2] == "-")
               	file << "sub " ;
            	else if(binop[i-2] == "*")
               	file << "mul " ;
            	else if(binop[i-2] == "/")
               	file << "div " ;
				
					if(isdigit(temp_symbol[0]) != 0)
						file << type_change(type) << " " << temp_symbol;
					else
					{
						if(isdigit(stmt_symbol[i][0]) != 0)
							file << type_change(type) << " %" <<(total_num-1);
						else
                     file << type_change(type) << " %" <<(total_num-2);
					}
					if(isdigit(stmt_symbol[i][0]) !=0 )
						file << ", " << stmt_symbol[i] <<endl;
					else
						file << " , %" <<(total_num-1)<<endl;
				}
	
				//total_num = total_num + 1;
				temp_type = type;
				temp_symbol = stmt_symbol[i];
			}
		
			if(i-1 == bin_num && bin_num != 0 && first_array != "true")
			{
				type_checking(first_type , type , 0);
				file << "store " << type_change(first_type) << " %" << total_num << " , " << type_change(stmt_type[0]) << "* %" << stmt_symbol[0] << endl;
				total_num = total_num + 1;
			}

			if(stmt_array[i] == "true")
				i = i + 1;
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
   string scope_str;
   stringstream change;
   change << scope;
   change >> scope_str;

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
		file << "ret i32 0" << endl;
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
	{	//print
		inputStack.pop("");
		//id
		string id = inputStack.top();
      int find_pos;

      for(int i = 0 ; i <line_count ;i++)
      {
	      if(id == symbol_save[i] && (scope_str == scope_save[i] || scope_save[i] == "0"))
         {
            find_pos = i;
         }
      }
	
		file << "%" << total_num << " = load " << type_change(type_save[find_pos]) << "* ";//%" << symbol_save[find_pos] << endl;
		if(scope_save[find_pos] == "0")
      	file << "@";
      else
         file << "%";
      
      file << symbol_save[find_pos] << endl;

		total_num = total_num + 1;
		file << "%" << total_num << " = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* " ;
		if(type_save[find_pos] == "int")
			file << "@.str " ;
		else if(type_save[find_pos] == "float" || type_save[find_pos] == "double")
			file << "@.str1 ";
		file << ", i32 0, i32 0), ";
		file << type_change(type_save[find_pos]) << " %" << total_num-1 << ")" <<endl;
		total_num = total_num + 1;
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
		   int find_pos = 0  ;

		   for(int i = 0 ; i <line_count ;i++)
  			{
     			if((input == symbol_save[i] && (scope_str == scope_save[i]|| scope_str == "0"))|| (input == symbol_save[i]&& function_save[i] == "true"))
     			{
					//cout << input << endl;
         		find_pos = i;
      		}
   		}
			//cout << input << endl;

			stmt_scope[stmt_num] = scope_save[find_pos];
			stmt_symbol[stmt_num] = symbol_save[find_pos];
			stmt_type[stmt_num] = type_save[find_pos];
			stmt_array[stmt_num] = array_save[find_pos];
			stmt_function[stmt_num] = function_save[find_pos];

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
			else 
			{
				stmt_type[stmt_num] = "double";
				//stmt_symbol[stmt_num].append(".0");
			}
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
	if(input == ";" || input == ")" || input == "]" || input == ","){;}
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
		file << " , " ; 
      inputStack.pop("");
		ExprListTail(inputStack.top());
	}
	else{;}
}

void Llvm::UnaryOp(string input)
{
	file << input ;
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
   	new_type = "i8";
   else if(type == "float")
      new_type = "float";
   else if(type == "double")
      new_type = "double";

	return new_type;
}

void Llvm::type_checking(string temp_type , string type , int assign)
{
	if(temp_type != type)
	{	
		if(assign == 0){
			if(temp_type == "int" && (type == "double" || type == "float"))
			{
				file <<  "%" << total_num << " = fptosi " << type_change(type) << " %" << total_num-1 << " to " << type_change(temp_type) << endl;
				total_num = total_num + 1;
			}
			else if((temp_type == "double" || temp_type == "float") && type == "int")
			{
	      	file <<  "%" << total_num << " = sitofp " << type_change(type) << " %" << total_num-1 << " to " << type_change(temp_type) << endl;
				total_num = total_num  + 1;
			}
		}
		else if(assign == 1){
         if(temp_type == "int" && (type == "double" || type == "float"))
         {
            file <<  "%" << total_num << " = sitofp " << type_change(temp_type) << " %" << total_num-2 << " to " << type_change(type) << endl;
         	total_num = total_num + 1;
			}
         else if((temp_type == "double" || temp_type == "float") && type == "int")
         {
            file <<  "%" << total_num << " = sitofp " << type_change(type) << " %" << total_num-1 << " to " << type_change(temp_type) << endl;
         	total_num = total_num + 1;
			}
		}
	
	}
}

