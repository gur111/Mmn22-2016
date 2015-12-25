/*
 * complex.c
 *
 *  Created on: Dec 16, 2015
 *      Author: Gur Telem
 */
#include "compleX.h"
#include <math.h>

/* Reads the given arguments into the given complex pointers. */
void read_comp(params* arg) {
	arg->vals[0].c->a = arg->vals[1].d;
	arg->vals[0].c->b = arg->vals[2].d;
	print_comp(arg); /* Prints the updated complex. (DEBUGGING)*/
}

/****** REMOVE!!!!!!!!!!!!!!!1 ***********/
/* Prints the given complex number to the user. */
void print_comp(params* arg) {
	printf("%."POST_POINT"lf + (%."POST_POINT"lf)I", arg->vals[0].c->a,
			arg->vals[0].c->b);
}

/* Adds the complex(s) values and prints to the user. */
void add_comp(params* arg) {
	complex comp;
	comp.a = arg->vals[0].c->a + arg->vals[1].c->a;
	comp.b = arg->vals[0].c->b + arg->vals[1].c->b;
	arg->vals[0].c = &comp;
	print_comp(arg);
}

/* Subs the complex(s) values and prints to the user. */
void sub_comp(params* arg) {
	complex comp;
	comp.a = arg->vals[0].c->a - arg->vals[1].c->a;
	comp.b = arg->vals[0].c->b - arg->vals[1].c->b;
	arg->vals[0].c = &comp;
	print_comp(arg);
}

/* Multiplies the complex with the real and prints to the user. */
void mult_comp_real(params* arg) {
	complex comp;
	comp.a = arg->vals[0].c->a * arg->vals[1].d;
	comp.b = arg->vals[0].c->b * arg->vals[1].d;
	arg->vals[0].c = &comp;
	print_comp(arg);
}

/* Multiplies the complex with the imaginary and prints to the user. */
void mult_comp_img(params* arg) {
	complex comp;
	comp.a = -arg->vals[0].c->b;
	comp.b = arg->vals[0].c->a;
	arg->vals[0].c = &comp;
	mult_comp_real(arg);
}

/* Multiplies the two complex and prints to the user. */
void mult_comp_comp(params* arg) {
	complex comp;
	comp.a = (arg->vals[0].c->a * arg->vals[1].c->a)
			- (arg->vals[0].c->b * arg->vals[1].c->b);
	comp.b = (arg->vals[0].c->a * arg->vals[1].c->b)
			+ (arg->vals[0].c->b * arg->vals[1].c->a);
	arg->vals[0].c = &comp;
	print_comp(arg);
}

/* Prints the absolute value of the complex. */
void abs_comp(params* arg) {
	printf("%lf", sqrt(pow(arg->vals[0].c->a, 2) + pow(arg->vals[0].c->b, 2)));
}

/* Exits the program. */
void halt(void) {
	printf("Exiting!\n");
	exit(EXIT_SUCCESS);
}
