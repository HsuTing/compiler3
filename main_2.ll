; ModuleID = 'main_2.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@x = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca double, align 8
  %d = alloca double, align 8
  %e = alloca [20 x i32], align 16
  %f = alloca [15 x i32], align 16
  %g = alloca i32, align 4
  store i32 0, i32* %1
  store i32 1, i32* %a, align 4
  store i32 2, i32* %b, align 4
  store double 3.300000e+00, double* %c, align 8
  store double 4.000000e+00, double* %d, align 8
  %2 = load i32* %a, align 4
  %3 = sitofp i32 %2 to double
  %4 = load double* %c, align 8
  %5 = fadd double %3, %4
  %6 = fptosi double %5 to i32
  store i32 %6, i32* %g, align 4
  %7 = load i32* %b, align 4
  %8 = load i32* %a, align 4
  %9 = icmp sgt i32 %7, %8
  br i1 %9, label %10, label %15

; <label>:10                                      ; preds = %0
  %11 = load i32* %a, align 4
  %12 = add nsw i32 5, %11
  store i32 %12, i32* %a, align 4
  %13 = load i32* %a, align 4
  %14 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %13)
  br label %20

; <label>:15                                      ; preds = %0
  %16 = load i32* %b, align 4
  %17 = add nsw i32 %16, 6
  store i32 %17, i32* %b, align 4
  %18 = load i32* %b, align 4
  %19 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %18)
  br label %20

; <label>:20                                      ; preds = %15, %10
  br label %21

; <label>:21                                      ; preds = %24, %20
  %22 = load double* %c, align 8
  %23 = fcmp olt double %22, 1.000000e+01
  br i1 %23, label %24, label %29

; <label>:24                                      ; preds = %21
  %25 = load i32* %a, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %a, align 4
  %27 = load double* %c, align 8
  %28 = fadd double %27, 1.000000e+00
  store double %28, double* %c, align 8
  br label %21

; <label>:29                                      ; preds = %21
  %30 = load i32* %a, align 4
  %31 = call i32 (i8*, i32, ...)* bitcast (i32 (...)* @print to i32 (i8*, i32, ...)*)(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %30)
  %32 = getelementptr inbounds [20 x i32]* %e, i32 0, i64 0
  store i32 1, i32* %32, align 4
  %33 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 2
  store i32 3, i32* %33, align 4
  %34 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 4
  store i32 5, i32* %34, align 4
  %35 = getelementptr inbounds [20 x i32]* %e, i32 0, i64 0
  %36 = load i32* %35, align 4
  %37 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 2
  %38 = load i32* %37, align 4
  %39 = add nsw i32 %36, %38
  %40 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 4
  store i32 %39, i32* %40, align 4
  %41 = getelementptr inbounds [15 x i32]* %f, i32 0, i64 4
  %42 = load i32* %41, align 4
  store i32 %42, i32* @x, align 4
  %43 = load i32* @x, align 4
  %44 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %43)
  %45 = call i32 @func()
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

declare i32 @print(...) #1

; Function Attrs: nounwind uwtable
define i32 @func() #0 {
  %test = alloca i32, align 4
  store i32 12345, i32* %test, align 4
  %1 = load i32* %test, align 4
  %2 = call i32 (i8*, i32, ...)* bitcast (i32 (...)* @print to i32 (i8*, i32, ...)*)(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %1)
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"}
