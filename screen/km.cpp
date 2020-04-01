#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>
#include <TouchScreen.h>
#include <time.h>

#define SD_CS 10

// physical dimensions of the tft display (# of pixels)
#define DISPLAY_WIDTH  480
#define DISPLAY_HEIGHT 320

// touch screen pins, obtained from the documentaion
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// dimensions of the part allocated to the map display
#define MAP_DISP_WIDTH (DISPLAY_WIDTH - 60)
#define MAP_DISP_HEIGHT DISPLAY_HEIGHT

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 940
#define TS_MAXY 920

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

//These are the colours in Hexadecimal
#define BLACK 0x0000
#define WHITE 0xFFFF
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0

MCUFRIEND_kbv tft;


// a multimeter reading says there are 300 ohms of resistance across the plate,
// so initialize with this to get more accurate readings
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// different than SD
Sd2Card card;
// prints a message to the bottom part of the tft screen

int cursor_x = 0; int cursor_y = 0;

/*
TODO:
Once server-side file IO is completed:
 implement Screen scrolling efficiently
	Should I just maintain the same up to date string of the whole file on this end?
 implement the mode 2, based heavily on the restaurant scrollable list we can deal with this.

Merge server side code with mine in terms of special chars.


*/


void status_message(const char* msg) {
  tft.fillRect(
    0, 0, DISPLAY_WIDTH,
    24, TFT_WHITE
  );

  tft.setTextColor(TFT_BLACK);
  tft.setCursor(5, 4);
  tft.setTextSize(2);

  tft.println(msg);
}

//opening_mode(){
//}


void setup() {
	

	init();
	Serial.begin(9600);
	Serial.flush();
	uint16_t ID= tft.readID();
	tft.begin(ID);
	// initialize serial port
	
	//the main menu
	tft.setRotation(1);
	//tft.setCursor(0,320/3);
	tft.setTextSize(2);
	tft.fillScreen(BLACK);
	status_message("Screen Side: No File Selected");
	cursor_y = 24;
	tft.setCursor(cursor_x,cursor_y);

	//tft.println("Select Mode:");
	//tft.setTextSize(1);
	
	
}
void receiving_mode(){
	/*This mode is responsible for receiving text and displaying it onto the screen.
	Note: It assumes that it should begin writing where cursor_x and cursor_y indicates.

	*/

	//Built-in ez way to make font-size variable if we want.
	int text_size = 2;
	tft.setTextColor(TFT_WHITE);
	//tft.setTextWrap(true);
	tft.setTextSize(text_size);
	int x_increment = text_size*6; int y_increment = text_size*8;


	//Continuously read chars from Serial until we need to break outta here.
	bool breakout = false;
	while(!breakout){
		if(Serial.available()){
			// read the incoming byte:
			int in_ascii = Serial.read();


			//String temp(in_ascii);
			//tft.print(temp);

			//WARNING: ASCII on arduino is not normal.
			if(in_ascii < 48 && in_ascii != 32 ){//temp comment: change to >123 for max letter (?). 
				//you got yourself a special character indicating an operation. 

				if(in_ascii == 33){ //example this is !
					//This could be where I call the function to goto mode two and get that file 
					breakout = true;
				}

				if(in_ascii == 8){//backspace

					//Wraparound back around the line, dont ruin the header.
					if(cursor_x == 0){
						if(cursor_y >24){ 
							cursor_y -= y_increment;
						}
						else cursor_x+=x_increment;
					}
					cursor_x = (cursor_x- x_increment)%DISPLAY_WIDTH;
					cursor_x = (cursor_x + DISPLAY_WIDTH)%DISPLAY_WIDTH;
					tft.fillRect(cursor_x,cursor_y,x_increment,y_increment,TFT_BLACK);					

				}
			}
      		else{
      			//Received a char. Now print to screen being mindful of cursor location
      			tft.setCursor(cursor_x,cursor_y);
      			char in_char = in_ascii;
      			tft.print(in_char);

      			//UPDATING CURSOR LOCATION.
      			cursor_x += x_increment;
      			if(cursor_x +x_increment > DISPLAY_WIDTH){
      				//if the next char will fall off the screen
      				cursor_x = 0; cursor_y += y_increment;
      			}
			}
		}
	}
}





int main() {

	setup();



	//Start receiving chars from the server
	while(true){
		receiving_mode();
	}
	return 0;
}