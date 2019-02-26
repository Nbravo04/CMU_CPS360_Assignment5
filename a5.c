#include<stdio.h> 
int main() 
{ 
  void halfaddr(int a, int b, int *sum, int *outcary);
  void rcadd4(int a, int b, int incary, int *sum, int *outcary);
} 

/*Simulates a half adder using bitwise operators on our inputs a and b that results in our
  outcarry and sum variables.*/
void halfaddr(int a, int b, int *sum, int *outcary){
  *outcarry = a & b;
  *sum = a ^ b;
}
 
/*Simulates a 4-bit ripple carry adder by using four full adders and using the last outcarry
  from the previous full adder as the incarry for the nxt full adder.*/
 void rcadd4(int a, int b, int incary, int *sum, int *outcary){
  fulladdr(a&1,b&1,incary,*sum,*outcary)
  fulladdr((a>>1)&1,(b>>1)&1,*outcarry,*sum,*outcary)
  fulladdr((a>>2)&1,(b>>2)&1,*outcarry,*sum,*outcary)
  fulladdr((a>>3)&1,(b>>3)&1,*outcarry,*sum,*outcary)
 }

