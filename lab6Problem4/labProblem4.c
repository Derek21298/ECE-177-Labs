/*
 * labProblem4.c
 *
 *  Created on: Jan 31, 2017
 *      Author: Derek
 */
#include <stdio.h>
#include <math.h>

int main(void) {

	float a = 32.2;
	double s;
	int v;
	int t = 0;
	int Si;



	printf("What is the initial velocity? \n");
	fflush(stdout);
	scanf("%d", &v);

	printf("What is the initial position? \n");
	fflush(stdout);
	scanf("%d" , &Si);

	for (t=0; t < 101; t = t + 5) {

		s = Si + (v * t) + (0.5 * a * t * t);
		printf("Distance fallen is %lf\n\n", s); }




}
