/*
 * Lab4part1.c
 *
 *  Created on: Feb 17, 2017
 *      Author: Derek
 */
#include <stdio.h>

int main() {	// Code to compute the date of Easter --- MAKE MINIMAL CHANGES!

	char A, B, C, D, E, F, G, H, I, K, L, M, N, P;	// These work as char
	int year, month, day;
	int startyear, endyear;

	char *monthstring;			// A string to hold the month name
	char *earliestMonthString;
	char *latestMonthString;
	int earliestMonth = 5;
	int latestMonth = 0;
	int earliestDay = 32;
	int latestDay = 0;

	printf("Enter the start year: ");
	fflush(stdout);
	scanf("%d", &startyear);
	printf("Enter the end year: ");
	fflush(stdout);
	scanf("%d", &endyear);
	printf("\n");


	if ((1700 >= startyear) && (startyear < 1800)) {			/* For the heck of it 			*/
		printf("startyear is in 1700s!\n\n");	/* flag startyear in the 1700s	*/
	}

	if ((1800 <= startyear) && (startyear < 1900)) /* also startyear in the 1800s */
		printf("startyear is in 1800s!\n\n");	/* using different test expression */

	if (startyear == 2000){			// and also startyear equal to 2000
		printf("start year ");			// printf broken into multiple lines
		printf("starts in 2000!\n\n");	// (leave it as two lines)
	}
	for (year = startyear; year <= endyear; year++) {
		A = year%19;
		B = year/100;
		C = year%100;
		D = B/4;
		E = B%4;
		F = (B + 8)/25;
		G = (B - F + 1)/3;
		H = (19*A + B - D - G + 15) % 30;
		I = C/4;
		K = C%4;
		L = (32 + 2*E + 2*I - H - K) % 7;
		M = (A + 11*H + 22*L) / 451;
		N = (H + L - 7*M + 114) / 31;
		P = (H + L - 7*M + 114) % 31;

		month = N; 				// (March = 3, April = 4)
		day = P + 1;

		printf("Date of Easter in %d is %s %d\n", year, month==3?"March":"April", day);


		if (month == 3) {			// This is another way to print the month //
			monthstring = "March";
		}
		else {						/* else part of if statement */
			monthstring = "April";

			}
		printf("Date of Easter in %d is %s %d\n\n", year, monthstring, day);

		if (month < earliestMonth) {
			earliestMonth = month;
			earliestMonthString = monthstring;
			earliestDay = day;
			}
		else if (month == earliestMonth){
			if (day < earliestDay){
				earliestDay = day;
			}
		}
		if (month > latestMonth) {
			latestMonth = month;
			latestMonthString = monthstring;
			latestDay = day;
		}
		else if (month == latestMonth) {
			if(day > latestDay){
				latestDay = day;
			}
		}
	}
	printf("The earliest Easter is %s %d and the latest Easter is %s %d\n", earliestMonthString, earliestDay, latestMonthString, latestDay );


	return 0;

}

