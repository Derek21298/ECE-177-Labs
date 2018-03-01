/*
 * Lab4Part2.c
 *
 *  Created on: Feb 17, 2017
 *      Author: Derek
 */
#include <stdio.h>
int main(void) {

	int x = 0;
	int y = 0;
	int number = 0;


	for (x = 1; x <= 12; x++) {
		printf("%d\t" , x);

		if (x == 1){
			number = 1;
		}
		else {
			number = x;

			for (y = x-1; y >=1; y--) {
						number *=y;
			}

		}
		printf("%d\n" , number);
	}

	return 0;
}

