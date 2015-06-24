#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Llvm {
	public:
		Llvm();
		void create_array();		

      void S(string word);
      void Program(string word);
      void DecList(string word);
      void DecList_(string word);
      string Type(string word);
      void DecList__id(string input , string word);
     	void Decl(string input , string type);
		void VarDecl(string input);
		void VarDecl_id(string input , string type);
      void VarDecl_(string input , string type);
		void FunDecl(string input);
		void VarDeclList(string input);
		void ParamDeclList(string input);
		void ParamDeclListTail(string input);
		void ParamDeclListTail_(string input);
		void ParamDecl(string input);
		void ParamDecl_id(string input , string type);
		void ParamDecl_(string input);
		void Block(string input);
		void StmtList(string input);
		void StmtList_(string input);
		void Stmt(string input);
		void Expr(string input);
		void ExprIdTail(string input , string id);
		void ExprArrayTail(string input);
		void Expr_(string input);
		void ExprList(string input);
		void ExprListTail(string input);
		void ExprListTail_(string input);
		void UnaryOp(string input);
		void BinOp(string input);

		int Check_s(string word);
		int length(string word);

		string type_change(string a);
		void type_checking(string first_type , string type);
/*-------------------------------------------------------------*/


	private:
			int first; //測試用

			//處理symbol_table
			int line_count;	//總參數
         string scope_save[20];
         string symbol_save[20];
         string type_save[20];
         string array_save[20];
         string function_save[20];
	
			//處理function的參數
			string param_type[5];
			string param_symbol[5];
			string param_array[5];
			int param_num;

			//處理stmt的參數
			string stmt_type[5];
			string stmt_symbol[5];
			string stmt_array[5];
			string binop[5];
			int stmt_num;
			int bin_num;

			//function %n
			int total_num;

			int scope;
			string empty[5];
};

template<typename T> class Stack
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
			if(count != 0){
         	array[count] = value;
         	count = count - 1;
			}
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

