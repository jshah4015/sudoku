#include"Gaming\\SuLogic.h"

struct suValue
{
	int val[10][10];		//0-Unknown   1-9=Fixed
	int fix[10][10];		//1-FixedByComp 2=FixedByUser and 0-Unknown  //99-ForProgrammerOnly
}
user,comp;
long FILE_SIZE;
long filesize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}
void fixCompValue(long level)
{
	FILE *fp;
	 if((fp=fopen("Gaming\\SuData.txt","r"))==NULL)
	 {//     exit(1);
		fprintf(stderr,"(DATA NOT FOUND) OR Can NOT OPEN file.");
		puts("Enter Any Key And Exit.");
		getch();
		exit(1);
	 }
	 FILE_SIZE=filesize(fp);
	 level=(long)(level-1)*204;
	 if((level+100)>FILE_SIZE)
	 {
		puts("Wrong Entry(Data Not Found With Given Level)...\nTry Again!");
		return;
	 }
	 fseek(fp,level,SEEK_SET);
	 for(int j,i=0;i<10;i++)
	 {
		for(j=0;j<10;j++)
		{
			comp.val[i][j]=fgetc(fp)-48;
			comp.fix[i][j]=1;
		}
	 }
	 fclose(fp);
}

void fixUserValue(long level)
{
	 FILE *fp;
	 if((fp=fopen("Gaming\\SuData.txt","r"))==NULL)
	 {	//exit(1);
		fprintf(stderr,"(DATA NOT FOUND) OR Can NOT OPEN file.");
		puts("Enter Any Key And Exit.");
		getch();
		exit(1);
	 }
	 FILE_SIZE=filesize(fp);
	 level=(long)(level-1)*204+102;
	 if((level+100)>FILE_SIZE)
	 {
		puts("Wrong Entry(Data Not Found With Given Level)...\nTry Again!");
		return;
	 }
	 fseek(fp,level,SEEK_SET);
	 for(int j,x,i=0;i<10;i++)
	 {
		for(j=0;j<10;j++)
		{
			x=fgetc(fp)-48;
			user.val[i][j]=x;
			if(i==0||j==0)
				user.fix[i][j]=99;
			else if(x==0)
				user.fix[i][j]=0;
			else
				user.fix[i][j]=1;
		}
	 }
	 fclose(fp);
}

int checkFinally(void)
{       int a,b;
	for(a=1;a<10;a++)
	{
		for(b=1;b<10;b++)
		{
			if(comp.val[a][b]!=user.val[a][b] )
			{
				return 0;
			}
		}
	}
	return 1;
}

int checkRows(int row,int entry)
{
      for(int i=1;i<10;i++)
      {
	if(user.val[row][i]==entry)
		return i;
      }
      return 0;
}
int checkColomns(int col,int entry)
{     for(int i=1;i<10;i++)
      {
	if(user.val[i][col]==entry)
		return i;
      }
      return 0;
}
void checkBoxes(int row,int col,int entry,int *br,int *bc)
{   
	int R=row%3;
	int C=col%3;
	if(R==0)
		row=row-2;
	else if(R==1)
		;
	else //if(R==2)
		row=row-1;
		
	if(C==0)
		col=col-2;
	else if(C==1)
		;
	else
		col=col-1;
	
	int temp;
	for(R=1;R<4;R++,row++)
	{
		for(C=1,temp=col;C<4;C++,temp++)
		{
			if(user.val[row][temp]==entry)
			{
				*br=row;
				*bc=temp;
				break;
			}
		}
	}
		
}

int checkPartially(int row,int col,int entry,int *r,int *c,int *br,int *bc)
{
      *r=checkRows(row,entry);
      *c=checkColomns(col,entry);
      checkBoxes(row,col,entry,br,bc);

      return ((*r)+(*c)+(*br));
}