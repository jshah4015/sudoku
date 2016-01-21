#include"Gaming\\SuMouse.h"

extern struct REGS in,out;
extern int px,py;
extern int posx,posy;
//-------------------------------------------------------------------------
//-------------------------Mouse Initialization----------------------------
void InitMouse(void)
{
	in.x.ax=0;
	int86(0x33,&in,&out);
	if(out.x.ax==0)
	{
		closegraph();
		printf("Mouse Driver Not Found...");
		getch();
		exit(1);
	}
			//To Set Mouse Pointer a Perticulor Location
	in.x.ax=4;
	in.x.cx=10;
	in.x.dx=10;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------------Mouse ShowingPtr----------------------------
void ShowMousePtr(void)
{
	in.x.ax=1;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//-----------------------------Mouse HidingPtr----------------------------
void HideMousePtr(void)
{
	in.x.ax=2;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------
//-------------------------Mouse Restriction----------------------------
void RestrictMousePtr(int x1,int y1,int x2,int y2)
{
	in.x.ax=7;
	in.x.cx=x1;
	in.x.dx=x2;
	int86(0x33,&in,&out);

	in.x.ax=8;
	in.x.cx=y1;
	in.x.dx=y2;
	int86(0x33,&in,&out);
}
//-------------------------------------------------------------------------


int getWrittingPos(int x,int y)
{
	int i;
	for(i=2;i<11;i++)
	{
		if(y>py*i+5 && y<py*(i+1))
		{
			posy=i-1;
			break;
		}
	}
	for(i=2;i<11;i++)
	{
		if(x>px*i+5 && x<px*(i+1))
		{
			posx=i-1;
			break;
		}
	}
	if(posx>0&&posy<10&&posy>0&&posy<10)
		return 1;
 return 0;
}

int getClickingPos(int y)
{
	for(int i=2;i<6;i++)
	{
		if(y>py*i+5 && y<py*(i+1))
		{
			posx=12;
			posy=i+9;
			return 1;
		}
	}
	return 0;
}
//-------------------------------------------------------------------------
//-------------------------Geting Mouse Position---------------------------
void GetMousePos(void)
{       int button=0,graphx,graphy;
	int ready=0;

	do
	{
	//	delay(50);
	in.x.ax=3;
	int86(0x33,&in,&out);
	button=out.x.bx;
	graphx=out.x.cx;
	graphy=out.x.dx;

		if(graphx>px*2 && graphx<px*11)
			ready=getWrittingPos(graphx,graphy);
		else if(graphx>px*12 && graphx<px*16)
			ready=getClickingPos(graphy);

	}while(button==0 || ready==0);
//	delete area;

}
//-------------------------------------------------------------------------