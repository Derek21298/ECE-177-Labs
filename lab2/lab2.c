/*
 * lab2.c
 *
 *  Created on: Jan 31, 2017
 *      Author: Derek
 */

#include <stdio.h>

int main(void) {
	double tempF;
	double tempC;

	printf("Enter a value for Fahrenheit: \n");
	fflush(stdout);
	scanf("%lf" , &tempF);

	tempC = (5 * (tempF - 32) / 9);

	printf("Temperature in Fahrenheit is %lf\n" , tempF);
	printf("Temperature in Celsuis is %lf\n" , tempC);
}
