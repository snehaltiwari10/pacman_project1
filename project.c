
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
#include<graphics.h>
#include<time.h>
#include "project.h"

int maze[25][80], score, row, col, ascii, scan, liveslost, delayfactor;
int gd = DETECT, gm, midx, midy, maxx, maxy;
int bugnumber , r[5], c[5], dir[5];
char charbelow[5];
char far *vid_mem= (char far *) 0xB8000000L; 

int main() {
	char cont;
	startscreen();
	while(1) {
		//initializing the variables at the start of each game.
		initialize();
		
		//poping-up the gamescreen.
		gamescreen();
		
		//Monitor the movements of the Bug and Eater.
		monitor();
		
		//Creating the Endscreen.
		cont = endscreen();
		if(cont == 'N')
			break;
	}
	return 0;
}
void startscreen() {
	char ch;
	int i;
	
	//The graphics system is initialized.
	initgraph(&gd, &gm, "d: \t c \b gi");
	
	//The maximum x and y co-ordinates are fetched.
	maxx = getmaxx();
	maxy = getmaxy();

	midx = maxx / 2;
	midy = maxy / 2;
	
	//draw a box.
	setcolor(BLUE);
	rectangle(0, 0, maxx - 1, maxy - 1);
	
	//draw two vertical lines.
	setcolor(GREEN);
	line (55,1,55,maxy-2);
        line (maxx-55,1,maxx-55,maxy-2);

	//The Pacman is displayed horizontally.
	setcolor(6);
	settextjustify (CENTER_TEXT, CENTER_TEXT);
	settextstyle (4, HORIZ_DIR, 8);
	outtextxy (midx, midy, "The PacMan");

	//Pacman is placed randomly on the screen.
	int x;
	randomize();
	for(x = 0; x < 40; x++) {
		gotoxy( rand() % 80, rand() % 25);
	}
	
	// Clear the area enclosed by the double-lined boundry.

	setviewport (0,0,maxx,maxy,1);

	clearviewport();
	
	//Screen to display instructions.
	setcolor(BLUE);
	rectangle(30, 0, maxx - 30, maxy);
	
	setcolor(YELLOW);
	for(i = 15; i < maxy - 15; i += 15) {
		ellipse(15, i, 0, 360, 6, 3);
		ellipse(maxx-15, i, 0, 360, 6, 3);	
	}
	setcolor(5);
	settextjustify (CENTER_TEXT,TOP_TEXT);
	settextstyle(4,HORIZ_DIR,5);
	outtextxy (midx,60,"INSTRUCTION");

	//Display the instructions.
	outtextxy(midx, 110, "Your Motive: Eat up all the crunchies");
	outtextxy(midx, 130, "Bugs are spread all over the Hurdles");
	outtextxy(midx, 150, "You can move around using the arrow keys");
	outtextxy(midx, 200, "Whenever you are ready, press any key");
	outtextxy(midx, 230, "ALL THE BEST!!!");

	//Wait for the Key.

	while(!kbhit());	
		if(getch() == 0)
			getch();
	//Drawing the screen for Level.
	setviewport (0, 0, maxx, maxy,1);
	clearviewport();
	rectangle(midx-200, midy-60, midx+200, midy+60);

	settextstyle (DEFAULT_FONT, HORIZ_DIR, 2);
	outtextxy(midx, 60, "Select Speed");

	settextstyle (DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(midx, 90, "Slow(S)");
	outtextxy(midx, 105, "Medium(M)");
	outtextxy(midx, 120, "Fast(F)");
						
	//Get user level.
	if((ch = getch()) == 0)
		getch();
		
	switch(toupper(ch)) {
		case 'S':
		delayfactor = 100;
		break;
		case 'M':
		delayfactor = 50;
		break;
		case 'F':
		delayfactor = 20;
		break;
		default:
		dealyfactor = 100;
		break;
	}
	if(delayfactor == 100)
		outtextxy(midx, midy, "Slow(S)");
	if(delayfactor == 50)
		outtextxy(midx, midy, "Medium(M)");
	if(delayfactor == 20)
		outtextxy(midx, midy, "Fast(F)");
	
	while(!kbhit());
	
	closegraph();
	restorecrtmode();
}

char endscreen() {
	char ans;
	initgraph(&gd, &gm, "d:\tc\bgi");
	rectangle(0, 0, maxx, maxy);
	rectangle(2, 2, maxx-2, maxy-2);	
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
	if(liveslost == 3) {
		outtextxy(midx, midy - 30, "BAD LUCK!");
	}
	else {
		outtextxy(midx, midy, "GENIUS!!");
	}
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
	outtextxy(midx, midy+midy/2, "Another game(Y?N)...");
	 while(!(ans=='Y'||ans=='N')) {
	fflush(stdin);
	ans = getch();
	ans = toupper(ans);
	}
	closegraph();
	restorecrtmode();
	
	return(ans);
}

void initialize() {
	int j;
	
	//Initialize the location of the Pacman.
	row = 12;
	column = 40;
	r[0]=3;
	c[0]=76;
	r[1]=3;
	c[1]=12;
	r[2]=12;
	c[2]=4;
	r[3]=14;
	c[3]=62; 

	score = 0;
	liveslost = 0;
	bugnumber = 0;
	
	for(j = 0; j < 4; j++) {
		dir[j] = 0;
		charbelow[j] = 250;
	}
}

void gamescreen() {
	int i;
	int vlin;
	size(32, 0);
	
	drawbox(0, 0, 16, 80, 12);
	
	//Draw the Hurdles.
	//horizontal.
	hline(205, 1, 0, 0, 79);
	hline(205, 1, 2, 2, 20);
	hline(205, 1, 2, 22, 38);
	hline(205, 1, 2, 42, 61);
	hline(205, 1, 2, 63, 77);
	hline(205, 1, 4, 2, 20);
	hline(205, 1, 4, 22, 61);
	hline(205, 1, 4, 63, 77);
	hline(205, 1, 17, 0, 79);
	hline(205, 1, 15, 2, 38);
	hline(205, 1, 15, 42, 77);
	hline(205, 1, 13, 0, 12);
	hline(205, 1, 13, 65, 78);
	hline(205, 1, 13, 16, 61);
	hline(205, 1, 11, 2, 14);
	hline(205, 1, 11, 62, 77);
	hline(205, 1, 8, 16, 61);
	hline(205, 1, 6, 2, 38);
	hline(205, 1, 6, 42, 77);
	hline(205, 1, 7, 63, 77);
	hline(205, 1, 9, 63, 78);
	hline(205, 1, 7, 2, 14);
	hline(205, 1, 9, 1, 14);

	//Columns.
	vline(186, 1, 0, 0, 16);
	vline(186, 1, 79, 0, 16);
	vline(186, 1, 40, 0, 2);
	vline(186, 1, 40, 4, 6);
	vline(186, 1, 14, 12, 14);
	vline(186, 1, 40, 13, 15);
	vline(186, 1, 63, 12, 14);
	vline(186, 1, 40, 9, 11);
	vline(202, 1, 14, 15, 15);
	vline(202, 1, 63, 15, 15);
	vline(203, 1, 40, 0, 0);
	vline(203, 1, 40, 4, 4);
	vline(203, 1, 40, 8, 8);
	vline(203, 1, 40, 13, 13);
	vline(187, 1, 79, 0, 0);
	vline(201, 1, 0, 0, 0);
	vline(188, 1, 79, 17, 17);
	vline(200, 1, 0, 17, 17);
	vline(204, 1, 0, 9, 9);
	vline(204, 1, 0, 13, 13);
	vline(185, 1, 79, 9, 9);
	vline(185, 1, 79, 13, 13);
	vline(186, 1, 16, 10, 11);
	vline(186, 1, 18, 10, 11);
	vline(186, 1, 20, 10, 11);
	vline(186, 1, 22, 10, 11);
	vline(186, 1, 24, 10, 11);
	vline(186, 1, 26, 10, 11);
	vline(186, 1, 28, 10, 11);
	vline(186, 1, 30, 10, 11);
	vline(186, 1, 32, 10, 11);
	vline(186, 1, 34, 10, 11);
	vline(186, 1, 36, 10, 11);
	vline(186, 1, 38, 10, 11);	
	vline(186, 1, 40, 10, 11);
	vline(186, 1, 42, 10, 11);
	vline(186, 1, 44, 10, 11);
	vline(186, 1, 46, 10, 11);
	vline(186, 1, 48, 10, 11);
	vline(186, 1, 50, 10, 11);
	vline(186, 1, 52, 10, 11);
	vline(186, 1, 54, 10, 11);
	vline(186, 1, 56, 10, 11);
	vline(186, 1, 58, 10, 11);
	vline(186, 1, 60, 10, 11);

	gotoxy(51, 24);
	printf("Press Esc to stop the game");
	gotoxy(2,24);
	printf("Point: %5d",score);
	
	//Place the bugs at the strategic ends.
	writechar(2, 3, 76, 15);
	writechar(2, 3, 12, 15);
	writechar(2, 12, 4, 15);
	writechar(2, 14, 62, 15);

}

//Drawing a box for filling the required area.

void drawbox (int sr, int sc, int er, int ec, char attr) {
	int i;
	int r, c;
	char far *v;
	
	//Calculate the address.
	for(r = sr; r <= er; r++) {
		for(c = sc; c <= ec; c++) {
			v = vid_mem + (r * 160) + (c * 2);
			*v = 250;
			v++;
			*v = attr;
		}
	}
}

// Reading the characters at the row r and column c.
void readchar(int r, int c, char *ch) {
	char far *v;

	/*calculate addresss*/
	v = vid_mem + (r * 160) + (c * 2);
	*ch = *v;
}



//Writing the character and it's attributes into the memory.

void writechar(char ch, int r, int c, int attr) {
	char far *v;

	//Calculate the address.
	 v = vid_mem + (r * 160) + (c * 2);

	//Store the ascii code.
	*v = ch;

	//Store the attribute.
	v++;
	*v = attr;
}

//Code for the Horizontal Hurdles.

void hline(char ch, int attr, int r, int c1, int c2) {
	int c;
	for(c = c1; c < (c2 + 1); c++) {
		writechar (ch, r, c, attr);
		maze[r][c] = 1;
		// The corresponding element of the array is set to 1.
	}
}

//Code for the Vertical Hurdles.
void vline(char ch, int attr, int c, int r1, int r2) {
	int r;
	for(r = r1; r < (r2 + 1); r++) {
		writechar(ch, r, c, attr);	
		maze[r][c] = 1;
		// The corresponding element of the array is set to 1.
	}
}

void monitor() {
	int key;
	char ch;

	while(1) {
		writechar(1,row,col,14);
		
		//move the Eater until the key is pressed.
		getkeyhit();

		//If all the lives are lost.
		if(liveslost == 3)
		break;

		// Leave a space at the place occupied by the Eater.
		writechar(' ', row, col, 1);
		
		//update the position of the Eater.
		key = testkeys();
		if(key == 0) {
			writechar(1, row, col, 14);
		}
		else {
			readchar(row, col, &ch);
			if(ch == 250)
				score++;
			if(ch == 2)
				killeater();
			if(liveslost == 3)
				break;
			
			// print the score.
			gotoxy(2, 24);
			printf("points : %5d", score);
			
			if(score >= 692) {
				writechar(' ', row, col, 1);
				break;
			}
		}
	}
}

// Code for moving the bug until a key is entered.

 /* void getkeyhit() {
	
	*/
// Identifies the key that has been Hit.
int testkeys() {
	switch(scan) {
	}
}	










		























