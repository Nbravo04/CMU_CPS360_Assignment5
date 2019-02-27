#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
   void printresult(char *label, int a);
   void halfaddr(int a, int b, int *sum, int *outcary);
   void fulladdr(int a, int b, int incary, int *sum, int *outcary);
   void rcadd4(int a, int b, int incary, int *sum, int *outcary);
   void lacadd4(int a, int b, int incary, int *sum, int *outcary);
   void evenparity3gen(int a, int *paritybit);
   void oddparity4chk(int a, int *checkbit);
   void modulus4bit(int a, int *rslt);
   void mux2by1(int a, int b, int *yout);
   void mux4by1(int a, int b, int *yout);
 
   if (argc < 4)
   {
      void usage(char *progname);
      char str[] = "a3";
      char *strptr = str;
      usage(strptr);
   }
 
   int sum, outcary, ans, *s = &sum, *o = &outcary, *ptrans = &ans;
   int a = strtol(argv[1], NULL, 16);
   int b = strtol(argv[2], NULL, 16);
   int c = strtol(argv[3], NULL, 16);
 
   halfaddr(a, b, s, o);
   printf("%s\n", "HalfAdder");
   printresult("sum:", sum);
   printresult("outcary:", outcary);
 
   printf("%s\n", "FullAdder");
   fulladdr(a, b, c, s, o);
   printresult("sum:", sum);
   printresult("outcary:", outcary);
 
   printf("%s\n", "RCAdder");
   rcadd4(a, b, c, s, o);
   printresult("sum:", sum);
   printresult("outcary:", outcary);
 
   printf("%s\n", "LACAdder");
   lacadd4(a, b, c, s, o);
   printresult("sum:", sum);
   printresult("outcary:", outcary);
 
   printf("%s\n", "Even Parity Gen");
   evenparity3gen(a, ptrans);
   printresult("paritybit:", ans);
 
   printf("%s\n", "Odd Parity Check");
   oddparity4chk(a, ptrans);
   printresult("Checkbit:", ans);
 
   printf("%s\n", "Modulus");
   modulus4bit(a, ptrans);
   printresult("rslt:", ans);
 
   printf("%s\n", "Mux2x1");
   mux2by1(a, b, ptrans);
   printresult("yout:", ans);
 
   printf("%s\n", "Mux4x1");
   mux4by1(a, b, ptrans);
   printresult("yout:", ans);
 
return 0;
}
 
/*Prints usage/hint to stderr, terminates execution using exit()*/
void usage(char *progname)
{
   fprintf(stderr, "./%s <arg-a> <arg-b> <arg-c>\n", progname); exit(1);
}
 
/*Simulates a half adder given two inputs. Using boolean algebra we return bot the sum and outcarry*/
void halfaddr(int a, int b, int *sum, int *outcary)
{
   *outcary = (a & 1) & (b & 1);
   *sum = (a & 1) ^ (b & 1);
}
 
/*Simulates a full adder. We take the two inputs and get the last bit and apply
  boolean algebra inorder to get the sum and outcarry.*/
void fulladdr(int a, int b, int incary, int *sum, int *outcary)
{
   int a0, b0, ci;
   a0 = a & 1; b0 = b & 1; ci = incary & 1;
   *sum = a0 ^ b0 ^ ci;
   *outcary = (a0 & b0) | (ci & (a0 | b0));
}
 
/*Simulates a ripple carry adder. This is done by spliting our inputs, a and b, bits and doing one
  full adder at a time. The outcarry from one full adder is then applied as the incarry for the next
  full adder and this continues for the next two full adders.*/ 
void rcadd4(int a, int b, int incary, int *sum, int *outcary)
{
 
   int sum1, sum2, sum3, sum4;
   int *s1 = &sum1, *s2 = &sum2, *s3 = &sum3, *s4 = &sum4;
/*
   fulladdr(a, b, incary, s1, outcary);
   fulladdr((a >> 1), (b >> 1), *outcary, s2, outcary);
   fulladdr((a >> 2), (b >> 2), *outcary, s3, outcary);
   fulladdr((a >> 3), (b >> 3), *outcary, s4, outcary);*/
 
   fulladdr(a&1,b&1,incary, s1, outcary);
   fulladdr((a>>1)&1,(b>>1)&1,*outcary, s2, outcary);
   fulladdr((a>>2)&1,(b>>2)&1,*outcary, s3, outcary);
   fulladdr((a>>3)&1,(b>>3)&1,*outcary, s4, outcary);
 
   *sum = (sum4 << 3) | (sum3 << 2) | (sum2 << 1) | sum1;
}
 
/*Simulates a look ahead carry adder. This method uses boolean algebra and bitwise ops in order
  to generate all the incarries for each full adder. Once each incarry is generated we apply each 
  to it's specific full adder.*/ 
void lacadd4(int a, int b, int incary, int *sum, int *outcary)
{
  /*int outcary1 = (a^b)*outcary | a*b;
   int outcary2 = ((a>>1)^(b>>1))*outcary1 | (a>>1)*(b>>2);
   int outcary3 = ((a>>2)^(b>>2))*outcary2 | (a>>2)*(b>>2);
   int outcary4 = ((a>>3)^(b>>3))*outcary3 | (a>>3)*(b>>3);*/
 
   int c1 = ((a & 1) & (b & 1)) | (((a & 1) | (b & 1)) & (incary & 1));
   int c2 = (((a >> 1) & 1) & ((b >> 1) & 1)) | ((((a >> 1) & 1) | ((b >> 1) & 1)) & c1);
   int c3 = (((a >> 1) & 1) & ((b >> 1) & 1)) | ((((a >> 1) & 1) | ((b >> 1) & 1)) & c2);
   int c4 = (((a >> 1) & 1) & ((b >> 1) & 1)) | ((((a >> 1) & 1) | ((b >> 1) & 1)) & c3);
 
   int sum1, sum2, sum3, sum4;
   int *s1 = &sum1, *s2 = &sum2, *s3 = &sum3, *s4 = &sum4;
 
   fulladdr(a, b, incary, s1, outcary);
   fulladdr(a>>1, b>>1, c1, s2, outcary);
   fulladdr(a>>2, b>>2, c2, s3, outcary);
   fulladdr(a>>3, b>>3, c3, s4, outcary);
   *sum = (sum4 << 3) | (sum3 << 2) | (sum2 << 1) | sum1;
 
   *outcary = c4;
}
 
/*Generates the even parity bit for lower order three bits in our input, a. This is done by
  seperating our input into 3 bits and applying boolean algebra on it.*/
void evenparity3gen(int a, int *paritybit)
{
   int x = (a >> 2) & 1;
   int y = (a >> 1) & 1;
   int z = a & 1;
 
   *paritybit = (x ^ y) | z;
}

/*Checks the odd parity bit for lower order 4 bits in our input, a, using a checkbit pointer. This is done by
  seperating our input into 4 bits and applying boolean algebra on it then checking if it is equal to the value
  pointed at from our check bit.*/
void oddparity4chk(int a, int *checkbit)
{
   int w = (a >> 3) & 1;
   int x = (a >> 2) & 1;
   int y = (a >> 1) & 1;
   int z = a & 1;
   *checkbit = ((w ^ x) ^ (y ^ z)) ^ 1;
}
 
/*Finds the modulus of a 4 bit 2's complement number using a rcadd4() and 4 xor gates.*/
void modulus4bit(int a, int *rslt)
{
   int a3 = ((a >> 3) & 1);
   int na0 = (a & 1) ^ a3;
   int na1 = ((a >> 1) & 1) ^ a3;
   int na2 = ((a >> 2) & 1) ^ a3;
   int na3 = ((a >> 3) & 1) ^ a3;
 
   int na = (na3 << 3) | (na2 << 2) | (na1 << 1) | na0;
   int out, *ptro = &out;
   rcadd4(na, 0, a3, rslt, ptro);
}
 
/*Simulated 2x1 multiplexer. This is done by using boolean algebra and bitwise operators on
  our inputs, a and b.*/
void mux2by1(int a, int b, int *yout)
{
   int i0 = a & 1;
   int i1 = (a >> 1) & 1;
   int s = b & 1;
 
   *yout = (i0 & (s ^ 1)) | (i1 & s);
}
 
/*Simulated 4x1 multiplexer. This is done by using boolean algebra and bitwise operators on
  our inputs, a and b.*/
void mux4by1(int a, int b, int *yout)
{
   int i0 = a & 1;
   int i1 = (a >> 1) & 1;
   int i2 = (a >> 2) & 1;
   int i3 = (a >> 3) & 1;
 
   int b0 = b & 1;
   int b1 = (b >> 1) & 1;
 
   *yout = ((b0 & (~1)) & i0 & (b1 & (~1))) | (b0 & i1  & (b1 & (~1))) | ((b0 & (~1)) & i2 & b1) | (b0 & i3 & b1);
}
 
/*Prints the results of the label and its value, a. This then calls printbits() in order to print out a in bits.*/
void printresult(char *label, int a)
{
   void printbits(int x);
 
   printf("%-16s", label);
   printbits(a);
}
 
/*Prints out the bits of x*/
void printbits(int x)
{
    int i, j;
    for(i = 31, j = 0; i >= 0; i--, j++) {
        if ((j & 0x7)  == 0) putchar(' ');
        (x & (1 << i)) ? putchar('1') : putchar('0');
    }
    printf("\n");
}
