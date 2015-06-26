#Compiler 3

##Environment

```
	ubuntu 14.04.2 LTS
```

##Language

```
	c++
```

##Compile

```
	make -f Makefile
```

##Use

```
	./hw3 (file name)
```

##Contributors

- [HsuTing](https://github.com/HsuTing)
- [peterlu](https://github.com/peterlu14)

##File

> main.cpp

```
	Contorl total class(symbol, check, llvm).
```

> symbol.cpp

```
	class Symbol:

		Check how many type in file.

	class Table:

		Use to store scope, level, symbol, type, array, function about file.

	class SymbolTable.cpp

		First, check type, and set level, symbol, type, array, function.
		Second, use level to add scope.
		Final, scope the table and write in output file.
```

> check.cpp
```
	class Check:
		
		Store scope, level, symbol, type, array, function about file.
		Type checking.
```

>llvm.cpp
```
	class Llvm:
		
		Saving all Non-Terminal functions(30).
		Finished function : type operate , print , func , array operate.
		Unfinished function : while , if , piority operator.

	class Stack:
		
		Build stack to save input.
```

