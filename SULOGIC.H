	#ifndef Graphics_H
	#define Graphics_H
	#include<graphics.h>
	#endif

	#ifndef Conio_H
	#define Conio_H
	#include<conio.h>
	#endif

	#ifndef Stdio_H
	#define Stdio_H
	#include<stdio.h>
	#endif

	#ifndef Stdlib_H
	#define Stdlib_H
	#include<stdlib.h>
	#endif
#ifndef SuLogic_H
#define SuLogic_H

void fixCompValue(long);
void fixUserValue(long);
int checkFinally(void);
//void checkRows(void);
//void checkColomns(void);
//void checkBoxes(void);
int checkPartially(int,int,int,int *,int *,int *,int *);

#endif
