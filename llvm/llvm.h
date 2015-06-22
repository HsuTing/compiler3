#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
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
		void Block(string input);

		int Check_s(string word);
		int length(string word);

/*-------------------------------------------------------------*/


	private:
			int first; //測試用

			int line_count;	
		
         string scope_save[20];
         string symbol_save[20];
         string type_save[20];
         string array_save[20];
         string function_save[20];
	
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

