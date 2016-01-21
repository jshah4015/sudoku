#ifndef Dos_H
#define Dos_H
#include<dos.h>
#endif

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
#ifndef SuMouse_H
#define SuMouse_H
	
void InitMouse(void);
void ShowMousePtr(void);
void HideMousePtr(void);
void RestrictMousePtr(int,int,int,int);
void GetMousePos(void);

#endif
