/*
 * labProblem3.c
 *
 *  Created on: Jan 31, 2017
 *      Author: Derek
 */
#include <stdio.h>
#include <math.h>

int main(void) {

	int x;
	int a;
	int b;
	int c;
	int d;

	printf("Enter a value for a: \n");
	fflush(stdout);
	scanf("%d" , &a);

	printf("Enter a value for b: \n");
	fflush(stdout);
	scanf("%d" , &b);

	printf("Enter a value for c: \n");
	fflush(stdout);
	scanf("%d" , &c);

	d = (b*b) - (4 * a * c);

	x = (-b + sqrt(d)) / (2 * a);

	if (d >= 0) {
		printf("X equals: %d" , x);
		x = (-b - sqrt(d)) / (2 * a);
		printf(" and %d" , x);
	}
	else {
		printf("Complex Result\n");
	}


}
