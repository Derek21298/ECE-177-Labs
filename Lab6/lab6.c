/*
 * lab6.c
 *
 *  Created on: Feb 28, 2017
 *      Author: Derek
 */
#include <stdio.h>

int main () {

	int shape;
	int size;
	int fill;
	int x;
	int i;
	int zig;
	int y;
	int k;


	setvbuf(stdout, NULL, _IONBF, 0);

	while (1) {

		printf("Enter shape (1) Square, (2) Triangle, (3) Zig-zag (4) Quit: ");
		scanf("%d" , &shape);

		if (shape == 4){									// end program
					return 0;
		}

		printf("Enter size: ");
		scanf("%d" , &size);



		if (shape == 1) {
			printf("Enter (0) No fill, (1) Fill: ");
			scanf("%d" , &fill);
			if (fill == 0) {									//square unfilled
				for(i = 1; i <= size; i++) {
					printf("*");
					for (x = 1; x <= (size-2); x++) {
						((i == 1) || (i == size))? printf("*"): printf(" ");     //'*' or space in middle
					}
					printf("*\n");
				}
			}
			else if (fill == 1){								//square filled

				for(i = 1; i <= size; i++){
					for(x = 1; x <= size; x++) {
						printf("*");
					}
					printf("\n");
				}
			}
		}

		if (shape == 2) {											//triangle unfilled
			printf("Enter (0) No fill, (1) Fill: ");
			scanf("%d" , &fill);
			if (fill == 0){
				for(i = 1; i <= size; i++) {
					for(x = 1; x <= i; x++) {
						((x == 1) || (x == i) || (i == size))? printf("*"):printf(" ");
					}
				printf("\n");
				}
				printf("\n");
			}
			else if (fill == 1) {									//triangle filled
				for(i = 1; i <= size; i++) {
					for(x = 1; x <= i; x++) {
						printf("*");

					}
					printf("\n");
				}

			}

		}
		if(shape ==3) {
			printf("Enter number of zigs: ");
			scanf("%d" , &zig);
			for(k = 1; k <= zig; k++) {
				for(i = 1; i <= size; i++) {
					for(x = 1; x <= i; x++) {
						((x == i) || (x == size))? printf("*"): printf(" ");
					}
					printf("\n");
				}
				for(i = size; i >= 1; i--) {
					for(y = 1; y <= i ; y++) {
					((y == i) || (y == size))? printf("*"): printf(" ");
					}
					printf("\n");
				}
			}
		}
	}
}


