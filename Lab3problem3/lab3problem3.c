/*
 * lab3problem3.c
 *
 *  Created on: Feb 7, 2017
 *      Author: Derek
 */
#include <stdio.h>

int main (void) {

	int year, month, day;
	int a, b, c, d, e, f, g, h, i, j, k, l, m, n, p;

	printf("enter a year:\n");
	fflush(stdout);
	scanf("%d" , &year);


	a = year % 19;
	b = year / 100;
	c = year % 100;

	d = b / 4;
	e = b % 4;

	f = (b + 8) / 25;
	g = (b - f + 1) / 3;
	h = (19 * a + b - d - g + 15) % 30;

	i = c / 4;
	k = c % 4;

	l = (32 + 2*e + 2*i - h - k) % 7;
	m = (a + 11*h + 22*l) / 451;
	n = (h + l - 7*m + 114) / 31;
	p = (h + l - 7*m + 114) % 31;

	month = n;
	day = p + 1;

	printf("Date of Easter in %d is %d/%d" , year, month, day);



}

