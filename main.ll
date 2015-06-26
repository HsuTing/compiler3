@.str = private constant [3 x i8] c"%d\00"
@.str1 = private constant [3 x i8] c"%f\00"
@x= global i32 0
define i32 @func(){
%1 = alloca i32
%test= alloca i32 
store i32 12345, i32* %test
%2 = load i32* %test
%3 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str , i32 0, i32 0), i32 %2)
ret i32 0
}
define i32 @main(){
%1 = alloca i32
%a= alloca i32 
%b= alloca i32 
%c= alloca double 
%d= alloca double 
%e= alloca [20 x i32]
%f= alloca [15 x i32]
%g= alloca i32 
%h= alloca [20 x double]
store i32 1, i32* %a
store i32 2, i32* %b
store double 3.3, double* %c
store double 4.0, double* %d
%2 = load i32* %a
%3 = load i32* %b
%4 = add i32 %2 , %3
store i32 %4 , i32* %g
%5 = load i32* %a
%6 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str , i32 0, i32 0), i32 %5)
%7 = load i32* %g
%8 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str , i32 0, i32 0), i32 %7)
%9 = getelementptr inbounds [20 x i32]* %e, i32 0, i64 0
store i32 1, i32* %9
%10 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 2
store i32 3, i32* %10
%11 = getelementptr inbounds [20 x i32]* %e, i32 0, i64 0
%12 = load i32* %11
%13 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 2
%14 = load i32* %13
%15= add i32 %12 , %14
%16 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 4
store i32 %15, i32* %16
%17 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 4
%18 = load i32* %17
store i32 %18, i32* @x
%19 = load i32* @x
%20 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str , i32 0, i32 0), i32 %19)
%21 = call i32 @func()
ret i32 0
}
declare i32 @printf(i8*, ...)
