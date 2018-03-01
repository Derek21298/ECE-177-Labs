/*
 * lab5.c
 *
 *  Created on: Feb 21, 2017
 *      Author: Derek
 */
#include <stdio.h>

int main(void) {

	int hour;
	int minute;
	int second;
	int x;
	int Thour;
	int Ohour;
	int Tminute;
	int Ominute;
	int Tsecond;
	int Osecond;

	setvbuf(stdout, NULL, _IONBF, 0);

	while (1) {

			int maskHour = 0b100000;
			int maskMinute = 0b100000;
			int maskSecond = 0b100000;
			int maskOHour = 0b100000;
			int maskOMinute = 0b100000;
			int maskOSecond = 0b100000;

	printf("Enter hours, min, sec:");						//Enter the time
	scanf("%d %d %d" , &hour, &minute, &second);

	if ((hour >= 0) && (hour <= 24)) {						//Test to see if hour is between 0-24

		for (x = 1; x <= 6; x++) {							//loop for 6 bit binary for hour

			Thour = hour / 10;
			Ohour = hour % 10;

			if ((Thour & maskHour) == 0) {
				printf("_");
			}
			else printf("*");
			maskHour >>= 1;
		}

		printf("\n");

		for(x = 1; x <= 6; x++) {

			if ((Ohour & maskOHour) == 0) {
				printf("_");
			}
			else printf("*");
			maskOHour >>= 1;

		}
	}
	else printf("ERROR: %d" , hour);

	printf("\n");

	if ((minute >= 0) && (minute <= 59)) {

		for (x = 1; x <= 6; x++) {
			Tminute = minute / 10;
			Ominute = minute % 10;

			if ((Tminute & maskMinute) == 0) {
				printf("_");
			}
			else printf("*");
			maskMinute >>= 1;
		}
		printf("\n");

		for(x = 1; x <= 6; x++) {
			if ((Ominute & maskOMinute) == 0) {
				printf("_");
			}
			else printf("*");
			maskOMinute >>= 1;
		}
	}
	else printf("ERROR: %d", minute);

	printf("\n");

	if ((second >=0) && (second <=60)) {

		for (x = 1; x <= 6; x++) {
			Tsecond = second / 10;
			Osecond = second % 10;

			if ((Tsecond & maskSecond) == 0) {
				printf("_");
			}
			else printf("*");
			maskSecond >>= 1;
		}
		printf("\n");

		for(x = 1; x <= 6; x++) {
			if ((Osecond & maskOSecond) == 0) {
				printf("_");
			}
			else printf("*");
			maskOSecond >>= 1;
		}
	}
	else printf("ERROR: %d" , second);

	printf("\n");

		if ((hour == 0) && (minute == 0) && (second ==0)){
			break;
		}
	}
	return 0;
}



