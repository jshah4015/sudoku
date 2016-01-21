#include"Gaming\\SuDraw.h"

void drawGraph(void)
{
	int gdriver=DETECT,gmode,gerror;
	initgraph(&gdriver,&gmode,"c:\\tc\\bgi");
	gerror=graphresult();
	if(gerror!=grOk)
	{
		printf("GRAPHICS ERROR: %s\n",grapherrormsg(gerror));
		printf("PRESS ANY KEY TO EXIT or RESTART THE PROGRAM.");
		getch();
		exit(1);
	}

}

void drawPage(int x16,int y12)
{
	setcolor(BLACK);
	setfillstyle(1,3);
     //	rectangle(x16*2,y12*2,x16*11,y12*11);
	int rect[8]={ x16*2,y12*2, x16*2,y12*11,  x16*11,y12*11, x16*11,y12*2 };
	fillpoly(4,rect	);

	int rect1[8]={ x16*12,y12*2+5, x16*16,y12*2+5,  x16*16,y12*3, x16*12,y12*3 };
	fillpoly(4,rect1	);
	int rect2[8]={ x16*12,y12*3+5, x16*16,y12*3+5,  x16*16,y12*4, x16*12,y12*4 };
	fillpoly(4,rect2	);
	int rect3[8]={ x16*12,y12*4+5, x16*16,y12*4+5,  x16*16,y12*5, x16*12,y12*5 };
	fillpoly(4,rect3	);
	int rect4[8]={ x16*12,y12*5+5, x16*16,y12*5+5,  x16*16,y12*6, x16*12,y12*6 };
	fillpoly(4,rect4);

	settextstyle(/*installuserfont()*/10,0,1);
	outtextxy(x16*12+7,y12*2-2,"New Game");
	outtextxy(x16*12+20,y12*3-2," Restart");
	outtextxy(x16*12+28,y12*4-3,"  Undo ");
	outtextxy(x16*12+28,y12*5-3,"  Exit ");
	for(int i=0;i<10;i++)
	{
		if(i%3==0)
			setlinestyle(0,1,3);
		line(x16*(i+2),y12*(2),x16*(i+2),y12*(11));
		line(x16*(2),y12*(i+2),x16*(11),y12*(i+2));
		setlinestyle(0,1,0);
	}
	settextstyle(1,0,3);
	setcolor(3);
	outtextxy(x16*2-10,5,"Refresh Your Mind With SUDOKU");
	settextstyle(1,0,1);
	outtextxy(x16*2,y12-10,"               - Presented by Raj Shah");
		setcolor(11);
			settextstyle(2,0,8);
			rectangle(x16*12,y12*7,x16*16+10,y12*11);
			outtextxy(x16*12,y12*7,"INSTRICTIONS");
			settextstyle(2,0,0);
			outtextxy(x16*12+5,y12*8,"1. Each Row Should contain");
			outtextxy(x16*12+2,y12*8+14,"  UNIQUE No.s 1 to 9");
			outtextxy(x16*12+5,y12*9,"2. Each Colomn Should ");
			outtextxy(x16*12+2,y12*9+14,"  contain UNIQUE No.s 1 to 9");
			outtextxy(x16*12+5,y12*10,"3. Each 3x3 Block Should ");
			outtextxy(x16*12+2,y12*10+14,"  contain UNIQUE No.s 1 to 9");
}

void writeValue(int x,int y,int v,int color)
{

	if(v<0||v>9)
	      // printf("%d Wrong",v);
	      exit(1);
	else
	{
		int xw=(getmaxx()/16)*(x+1)+12;
		int yw=(getmaxy()/12)*(y+1)-4;
		setcolor(color);
		char val[1];
		sprintf(val,"%d",v);
		settextstyle(2,0,14);
		outtextxy(xw,yw,val);
	}
	settextstyle(1,0,0);
	//setcolor(3);

}
