/*
 * labProblem2.c
 *
 *  Created on: Jan 31, 2017
 *      Author: Derek
 */
#include <stdio.h>

int main(void) {

	int x;
	int y;

	printf("Enter a value of X: \n");
	fflush(stdout);
	scanf("%d" , &x);

	y = (x * x * x) + (5 * (x * x)) + (10 * x) + 15;

	printf("f(x) equals: %d\n" , y);
}

