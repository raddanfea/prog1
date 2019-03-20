#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <linux/input.h>
#include <fstream>
#include <cstring>

using namespace std;

	int lvl = 1;
	int x = 1;
	int y = 1;
	int debg1 = 5;
	int debg2 = 25;
	int wait;
	float draw;
	const char* mapdata[20][20]={
 		{"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|"},
		{"|"," ","X"," "," "," ","X","X","X"," ","X"," "," "," "," "," ","X"," "," ","|"},
		{"|"," "," "," ","X"," "," ","X"," "," ","X"," ","X"," ","X"," ","X","X"," ","|"},
		{"|","X","X","X","X","X"," ","X"," "," "," "," ","X"," ","X"," "," ","X"," ","|"},
		{"|"," ","X"," "," ","X"," ","X"," ","X"," "," ","X"," ","X","X"," "," "," ","|"},
		{"|"," ","X"," ","X","X"," ","X"," ","X"," "," "," "," "," ","X"," "," "," ","|"},
		{"|"," "," "," "," "," "," ","X"," ","X","X","X","X"," ","X","X"," ","X"," ","|"},
		{"|"," ","X"," ","X"," "," ","X"," "," "," "," ","X"," "," ","X"," ","X","X","|"},
		{"|"," ","X"," ","X","X"," ","X","X","X","X"," ","X","X"," ","X"," ","X"," ","|"},
		{"|"," ","X"," "," ","X"," ","X"," "," "," "," "," ","X"," ","X"," ","X"," ","|"},
		{"|"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","X"," "," "," ","|"},
		{"|"," "," "," ","X"," "," ","X"," ","X","X","X"," ","X"," ","X"," ","X","X","|"},
		{"|"," ","X"," ","X"," ","X","X"," "," "," ","X"," "," "," ","X","X","X"," ","|"},
		{"|"," ","X"," ","X"," "," "," "," "," "," ","X","X","X"," ","X"," "," "," ","|"},
		{"|"," ","X"," ","X"," ","X","X","X","X"," ","X"," "," "," ","X"," ","X"," ","|"},
		{"|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," "," "," ","X"," ","|"},
		{"|"," ","X","X","X","X"," ","X"," ","X","X","X"," "," ","X","X"," ","X","X","|"},
		{"|"," ","X"," ","X"," "," ","X"," "," "," ","X"," "," "," ","X"," "," "," ","|"},
		{"|"," "," "," ","X","X","X","X"," "," "," ","X"," "," "," ","X"," ","X"," ","|"},
		{"|","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","|"},
		
    	};






void dram ()
{

	if ( x>18) {--x;}
	if ( x<=0 ) {++x;}
        if ( y<=0 ) {++y;}
        if ( y>18) {--y;}

	WINDOW *ablak;
    	ablak = initscr ();
	
	for(int xa = 0; xa < 20; ++xa)
		{
		for(int ya = 0; ya < 20; ++ya)
			{			
				mvprintw (xa, ya, mapdata[xa][ya]);
			}
		}
	mvprintw ( y, x, "O" );
	mvprintw ( debg1, debg2, "X: %i",x );
	mvprintw ( debg1+1, debg2, "Y: %i",y );
	mvprintw ( 2, 30, " ");
        refresh ();
        usleep (2000);
	clear();
}


void inpt ()
{
struct input_event event;

ifstream file("/dev/input/event2");
    
    char data[sizeof(event)];
	dram();
	
    if(file.is_open()) {
        
        //lets loop until esc key
        bool session = true;
        while(session) {
		dram;
            
            //lets get to work
            file.read(data, sizeof(event));
            
            //now copy the data to the struct
            memcpy(&event, data, sizeof(event));
            if(event.type == EV_KEY) {
		if(event.code == KEY_D) {if (mapdata[y][x+1] != "X") {++x;}; usleep (70000); session = false; break;}
		if(event.code == KEY_W) {if (mapdata[y-1][x] != "X") {--y;}; usleep (70000); session = false; break;}
		if(event.code == KEY_S) {if (mapdata[y+1][x] != "X") {++y;}; usleep (70000); session = false; break;}
		if(event.code == KEY_A) {if (mapdata[y][x-1] != "X") {--x;}; usleep (70000); session = false; break;}
		        else 	{ session = false; break; }
	    }
        }
        
        //dont forget to close the file
        file.close();
    }
    else {
        
        cout << "Unable to open file!" << endl;
    }

}


int
main ( void )
{

    for ( ;; ) 
	{
	inpt ();
	}
    return 0;
}


