#include<stdio.h> 
int main() 
{ 
  void halfaddr(int a, int b, int *sum, int *outcary);
  void rcadd4(int a, int b, int incary, int *sum, int *outcary);
} 

void halfaddr(int a, int b, int *sum, int *outcary){
  *outcarry = a & b;
  *sum = a ^ b;
}
 { simulates HA on bit 0 of a and b, returns sum bit and carry bit }
 
 void rcadd4(int a, int b, int incary, int *sum, int *outcary){
  fulladdr(a&1,b&1,incary,*sum,*outcary)
  fulladdr((a>>1)&1,(b>>1)&1,*outcarry,*sum,*outcary)
  fulladdr((a>>2)&1,(b>>2)&1,*outcarry,*sum,*outcary)
  fulladdr((a>>3)&1,(b>>3)&1,*outcarry,*sum,*outcary)
 }
 { uses ripple-carry scheme and 4 FAs to add lower order 4-bits of
 a and b and incarry is in c }

