#include<dos.h>
	#ifndef _Time.H
	#define _Time.H
	#include <time.h>
	#endif
#include"Gaming\\SuDraw.cpp"
#include"Gaming\\SuMouse.cpp"
#include"Gaming\\SuLogic.cpp"
/*
-----------------------Mind Game SUDOKU-----------------------------
------------------------by Raj p. Shah------------------------------
------------Date:June,2015
------------Compiler:Turbo c++
------------Languages:c and c++
*/
#define NULL 0
//using namespace std;
struct undo
{
	int lastx;
	int lasty;
	struct undo *next;
};
struct undo *top=NULL;
void addDataForUndo(int a,int b)
{
	struct undo *data=(struct undo *)malloc( sizeof(struct undo) );
	if(data==NULL)
	{
	       //	printf("No Sufficient Space in Stack");
	}
	else
	{
			data->next=top;
			top=data;
			top->lastx=a;
			top->lasty=b;

	}
}

void removeDataFromUndo()
{
	if(top==NULL)
	{
		//Do Nothing
		//Stack is empty
	}
	else
	{
	   top=top->next;
	}
}

time_t startTime,endTime;    //For Timings
int px,py,posx,posy;        //Used as extern in other files
int count=0,wrongentry=0;	//	    lastx,lasty;
long level;
struct REGS in,out;         //Used as extern in other files
extern struct suValue user,comp;

void clickingMenu(int);
void writtingMenu(void);
void initPage(int x=0);
void result(void);
void excecuteUndo(void);

int main()
{
	//clrscr();
	initPage();
	//getch();
    do
    {
	GetMousePos();
	if(posx>=1 && posx<=9)
		writtingMenu();
	else
		clickingMenu(posy);
       //	getch();
    }while(count!=81);
	result();
	getch();
	closegraph();
	//getch();
	return 0;
}


void clickingMenu(int y)
{
	switch(y)
	{
		case 11:
			HideMousePtr();
			cleardevice();
			initPage();
			top=NULL;
			break;
		case 12:
			HideMousePtr();
			//closegraph();
			cleardevice();
			initPage(level);
			top=NULL;
			break;
		case 13:
		     //	HideMousePtr();
			excecuteUndo();
			break;
		case 14:
			HideMousePtr();
			for(int iq=0;iq<25;iq++)
			{	delay(50);
				printf("\n\n\n");
			}
			setcolor(3);
			outtextxy(px,py,"THANK YOU....");
			delay(1000);
			exit(0);
			break;
		default:
			if(y>14)
			{
			setcolor(11);
			outtextxy(px,py*11,"SOMETHING IS GOING WRONG");
			delay(1000);
			setcolor(BLACK);
			outtextxy(px,py*11,"SOMETHING IS GOING WRONG");
			}
			break;
	}
}


void initPage(int x)
{
	count=0;
	wrongentry=0;

	if(x==0)
	{
		while(x<=0||x>=6)
		{       clrscr();

			textmode(C80);
			textcolor(3);
			window(15,5,60,20);
			gotoxy(1,1);
			cputs("*****   SELECT A LEVEL   *****");
			gotoxy(3,2);
			cputs("1. Fresher");
			gotoxy(3,3);
			cputs("2. Easy");
			gotoxy(3,4);
			cputs("3. Medium");
			gotoxy(3,5);
			cputs("4. Hard");
			gotoxy(3,6);
			cputs("5. Evil");
			gotoxy(3,7);
			cputs("Select Level(1/2/3/4/5):");

			level=x=getche()-48;
			getch();
		}
		clrscr();
	}
	fixCompValue(level);
	fixUserValue(level);
	drawGraph();
	px=(int)getmaxx()/16;
	py=(int)getmaxy()/12;
	drawPage(px,py);

	{
		int a,b;
	for(a=1;a<10;a++)
	{
		for(b=1;b<10;b++)
		{
		       //	printf("%d",user.val[a][b]);
			if(user.fix[a][b]==1)
			{	writeValue(a,b,user.val[a][b],BLACK);
				count++;
			}
		}
	}
	}
       //	getch();
	InitMouse();
	ShowMousePtr();
	RestrictMousePtr(px*2+5,py*2+5,px*16-5,py*11-5);
	startTime=time(&startTime);
}

void writtingMenu(void)
{
	int entry=-1;
	int true;
    while(user.fix[posx][posy]==0 && entry<0)
    {
	HideMousePtr();
	//char en[2];
	setcolor(11);

	writeValue(posx,posy,0);
	fflush(stdin);
	//scanf("%1d",&entry);
	entry=int( getch() )-48;
	fflush(stdin);
	if(entry>=1 && entry<=9)
	{
	     //	sprintf(en,"%1d",entry);
		writeValue(posx,posy,0,CYAN);
		int x16=px;
		int y12=py;

		int *row=new int(0);
		int *col=new int(0);
		int *boxr=new int(0);
		int *boxc=new int(0);

		true=checkPartially(posx,posy,entry,row,col,boxr,boxc);
		if(true!=0)
		{
			wrongentry++;
			writeValue(posx,posy,entry,RED);
			sound(1000*entry);
			delay(250);
			nosound();
			true=1;
					//setcolor(11);
					//settextstyle(2,0,8);
					//rectangle(x16*12,y12*7,x16*16+10,y12*11);
					//outtextxy(x16*12,y12*7,"INSTRICTIONS");
			if(*row>0)
			{
				writeValue(posx,*row,user.val[posx][*row],RED);
				setcolor(RED);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*9,"2. Each Colomn Should ");
				outtextxy(x16*12+2,y12*9+14,"  contain UNIQUE No.s 1 to 9");
				sound(750*entry);
				delay(250);
				nosound();
				true++;

			}
			if(*col>0)
			{
				writeValue(*col,posy,user.val[*col][posy],RED);
				setcolor(RED);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*8,"1. Each Row Should contain");
				outtextxy(x16*12+2,y12*8+14,"  UNIQUE No.s 1 to 9");
				sound(500*entry);
				delay(250);
				nosound();
				true++;
			}
			if(*boxr>0)
			{
				writeValue(*boxr,*boxc,user.val[*boxr][*boxc],RED);
				setcolor(RED);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*10,"3. Each 3x3 Block Should ");
				outtextxy(x16*12+2,y12*10+14,"  contain UNIQUE No.s 1 to 9");
				sound(250*entry);
				delay(250);
				nosound();
				true++;
			}

				//setcolor(RED);
				//rectangle(px*12,py*7,px*16+10,py*11);
			delay(1000-(250*true));
			writeValue(posx,posy,entry,CYAN);
			if(*row>0)
			{
				if(user.fix[posx][*row]==1)
					writeValue(posx,*row,user.val[posx][*row],BLACK);
				else
					writeValue(posx,*row,user.val[posx][*row]);
				setcolor(11);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*9,"2. Each Colomn Should ");
				outtextxy(x16*12+2,y12*9+14,"  contain UNIQUE No.s 1 to 9");

			}
			if(*col>0)
			{
				if(user.fix[*col][posy]==1)
					writeValue(*col,posy,user.val[*col][posy],BLACK);
				else
					writeValue(*col,posy,user.val[*col][posy]);
				setcolor(11);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*8,"1. Each Row Should contain");
				outtextxy(x16*12+2,y12*8+14,"  UNIQUE No.s 1 to 9");

			}
			if(*boxr>0)
			{
				if(user.fix[*boxr][*boxc]==1)
					writeValue(*boxr,*boxc,user.val[*boxr][*boxc],BLACK);
				else
					writeValue(*boxr,*boxc,user.val[*boxr][*boxc]);
				setcolor(11);
				settextstyle(2,0,0);
				outtextxy(x16*12+5,y12*10,"3. Each 3x3 Block Should ");
				outtextxy(x16*12+2,y12*10+14,"  contain UNIQUE No.s 1 to 9");
			}

				 //	writeValue(posx,posy,entry,CYAN);
				//setcolor(11);
				//rectangle(px*12,py*7,px*16+10,py*11);

		}
	      //else
// With 'else' Game is Not Looking Interesting,So I Have Removed It
		{	writeValue(posx,posy,entry);
			if(true==0)
			{
				for(int i=0;i<=1000;i+=50)
				{
					sound((1000-i)*entry);
					delay(5);
					nosound();
				}
			}
			user.val[posx][posy]=entry;
			user.fix[posx][posy]=2;
			addDataForUndo(posx,posy);
			count++;
		}
	    //	lastx=posx;
	    //	lasty=posy;
		delete row;
		delete col;
		delete boxr;
		delete boxc;
	}
	else
	{
		writeValue(posx,posy,0,CYAN);
	}
	ShowMousePtr();
    }
}


void result(void)
{
	endTime=time(&endTime);
	int totalTime;
	totalTime=int(difftime(endTime,startTime));
	char entrystring[3];
	char timestring[26];
	sprintf(timestring,"%4d Seconds",totalTime);
	sprintf(entrystring," %03d",wrongentry);
	settextstyle(5,0,0);
 if(checkFinally()==1)
    {
		HideMousePtr();
		for(int iq=0;iq<25;iq++)
		{	delay(50);
			printf("\n\n\n");
		}
		setcolor(CYAN);
		outtextxy(px,py,"Congratulations...");
		for(int iq1=9;iq1>1;iq1--)
		{       setcolor(iq1);
			outtextxy(px,py*3,"Your Mind Got Refreshed...");
			delay(500);
			setcolor(iq1+2);
			outtextxy(px,py*3,"Your Mind Got Refreshed...");

		}
		delay(2000);
		setcolor(BLACK);
		outtextxy(px,py*3,"Your Mind Got Refreshed...");
		setcolor(CYAN);
		outtextxy(px,py*3,"Total Time Taken : ");
		outtextxy(px*10,py*3,timestring);
		outtextxy(px,py*5,"Total Wrong Entries : ");
		outtextxy(px*10,py*5,entrystring);

	     //	getch();
	     //	exit(0);
    }
    else			//This will never Happen
    {
	HideMousePtr();
	for(int iq=0;iq<25;iq++)
	{	delay(50);
		printf("\n\n\n");
	}
	setcolor(RED);
	outtextxy(px,py,"Round Not Cleared...");

	for(int iq1=1;iq1<7;iq1++)
	{
		outtextxy(px,py*3,"Your Mind Needs Rest...");
		delay(700);
		outtextxy(px,py*5,"Come Back Later...");
		setcolor(BLACK);
		outtextxy(px,py*3,"Your Mind Needs Rest...");
		delay(1000);
		outtextxy(px,py*5,"Come Back Later...");
		setcolor(RED);
	}

	outtextxy(px,py*3,"Total Time Taken : ");
	outtextxy(px*10,py*3,timestring);
	outtextxy(px,py*5,"Total Wrong Entries : ");
	outtextxy(px*10,py*5,entrystring);

      //	getch();
      //	exit(0);
    }

       //	setbkcolor(7);
	outtextxy(px,py*7,"Enter Any Key To Exit...");
}

void excecuteUndo()
{
	if(user.val[top->lastx][top->lasty]==0)
				;//do nithing
			       //	break;
	else
	{
		writeValue(top->lastx,top->lasty,user.val[top->lastx][top->lasty],CYAN);
		count--;
		user.val[top->lastx][top->lasty]=0;
		user.fix[top->lastx][top->lasty]=0;
	     //	ShowMousePtr();
		delay(500);            //Not Working Without delay() or delay(<500)
		removeDataFromUndo();
	}
}
