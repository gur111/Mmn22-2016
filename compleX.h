/*
 * complex.h
 *
 *  Created on: Dec 16, 2015
 *      Author: Gur Telem
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define POST_POINT "3"

typedef struct {
	double a, b;
} complex;

typedef struct {
	union singleParam{
		complex* c;
		double d;
	} vals[3];
} params;

void read_comp(params*);
void print_comp(params*);
void add_comp(params*);
void sub_comp(params*);
void mult_comp_real(params*);
void mult_comp_img(params*);
void mult_comp_comp(params*);
void abs_comp(params*);
void halt(void);
