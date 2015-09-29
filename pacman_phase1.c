#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<ctype.h>
void initialise(void);
void writechar(char,int,int,int);
void readchar(int,int,unsigned char*);
void startscreen(void);
void main(void)
{
	char ans ;
	startscreen();
	while (1){
		initialise();
		if(ans== 'N')
			break;
	}
}

void initialise() {
	int j, row, col, score, bugnumber, liveslost;
	int r[5], c[5], dir[5];
	char charbelow[5];
	row = 12;
	col = 40;
	r[0] = 3;
	c[0] = 76;
	r[1] = 3;
	c[1] = 12;
	r[2] = 12;
	c[2] = 4;
	r[3] = 14;
	c[3] = 62;
	score = 0;
	liveslost = 0;
	bugnumber = 0;
	for(j = 0; j < 4; j++) {
		dir[j] = 0;
		charbelow[j] = 250;
	}
}
void readchar(int r,int c,unsigned char *ch)
{
	char *v;
	v = vid_mem + (r*160) + c*2;
	*ch = *v;
}
void writechar(char ch,int r,int c,int attr)
{
	char *v ;
	v=vid_mem+(r*160)+c*2;
	*v=ch;
	v++;
	*v=attr;
}

void startscreen(void)
{
	char ch;
	int i;
	int loop;
	initgraph (&gd,&gm,"d:\tc\bgi");
	maxx = getmaxx();
	maxy= getmaxy();
	midx= maxx/2;
	midy=maxy/2;
	setcolor(GREEN);
	rectangle (0,0,maxx,midy);
	setcolor(BLUE);
	rectangle (2,2,maxx-2,maxy-2);
	setcolor(YELLOW);
	line (55,1,55,maxy-2);
	line (maxx-55,1,maxx-55,maxy-2);
	setcolor(6);
	settextjustify (CENTER_TEXT,CENTER_TEXT);
	settextstyle (4,HORIZ_DIR,8);
	outtextxy (midx,midy,"The PacMan");
	randomize();
	for(loop=0; loop<40;loop++){
		gotoxy(rand() % 80,rand()%25);
		printf("%c",2);
	}
	setviewport (0,0,maxx,maxy,1);
	clearviewport();
	setcolor(BLUE);
	rectangle(30,0,maxx-33,maxy);

	setcolor(YELLOW);
	for (i=15;i<=maxy-15;i+=15){
		ellipse(15,i,0,360,6,3);
		ellipse(maxx-15,i,0,360,6,3);
	}
	setcolor(5);
	settextjustify (CENTER_TEXT,TOP_TEXT);

	settextstyle(4,HORIZ_DIR,5);
	outtextxy (midx,60,"INSTRUCTION");
	settextstyle(2,HORIZ_DIR,5);
	outtextxy(midx,110,"You goal:- To eatup all the CRUNCHY MUNCHY      ");
	outtextxy(midx,130,"           UNDAY scattered throughtout the BHOOL
	BHULLYIAN   ");
	outtextxy(midx,170,"Your task is not a HALWA! There are 5 Rascals ch0asingyou");
	outtextxy(midx,210,"The Eater.You have to watch out for the bugs");
	outtextxy(midx,250,"To help you ,we have bestowed the PacMan with Janums");
	outtextxy(midx,290,"You can move around the BHOOL BHULLYIAN  using arrow keys       ");
	outtextxy(midx,330,"If you are ready to start, press any  key");
	setcolor(GREEN);
	settextstyle (DEFAULT_FONT,HORIZ_DIR,3);
	outtextxy(midx,400,"We wish you Best of luck");
	setviewport (0,0,maxx,maxy,1);
	clearviewport();
	rectangle(midx-200,midy-60,midx+200,midy+60);

	settextstyle (DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(midx,60,"Select Speed");

	settextstyle (DEFAULT_FONT,HORIZ_DIR,1);
	outtextxy(midx,90,"Slow(S)");
	outtextxy(midx,105,"Medium(M)");
	outtextxy(midx,120,"Fast(F)");

	if ((ch=getc()==0)
		scanf();
}
