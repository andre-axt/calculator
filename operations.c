#include <stdio.h>
#include "operations.h"

int add(int a, int b){return a + b;}
int sub(int a, int b){return a - b;}
int div(int a, int b){return b != 0 ? a / b : 0;}
int mul(int a, int b){return a * b;}

typedef struct {
	char *name;
	int (*func_ptr)(int, int);

}Operation;

Operation ops[4]={
	{"Add", add},
	{"Sub", sub},
	{"Div", div},
	{"Mul", mul}

};

void compute (int a, int b, int (*func_ptr)(int, int), int x){
	printf("Result:%s %d", ops[x].name, func_ptr(a, b)); 
}

