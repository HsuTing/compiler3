int x;
int func ( )
{
   int test ;
   test = 12345 ;
   print test ;
   return 0 ;
}
int main ( )
{
   int a ;
   int b ;
   double c ;
   double d ;
   int e [ 20 ] ;
   int f [ 15 ] ;
   int g ;
   double h [20] ;
   a = 1 ;
   b = 2.2 ;
   c = 3.3 ;
   d = 4 ;
   g = a + b ;

	print a;
	print g;
	
   e[0] = 1;
   f[2] = 3;
   f[4] = e[0] + f[2];
	x = f[4];

   print x;

   func ( ) ;
   return 0 ;
}
