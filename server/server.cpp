//Some of these are unused
#include "wdigraph.h"
#include "dijkstra.h"
#include "serialport.h"
#include "keyboardInput.h"
#include "screenInput.h"

#include <cassert>
#include <string>

using namespace std;

int main() {
  //VERY IMPORTANT THIS IS DONE CORRECTLY TRUE
  //Keyboard Serial
  SerialPort keyboardSerial("/dev/ttyACM0");
  //Screen Serial
  SerialPort screenSerial("/dev/ttyACM1");

  //TODO: Initialize file manager object here

  //Initialize weighted graph for alphabet storage

  //Load the alphabet data from the file

  /*Line parsing from keyboard or screen
  Note:
    Keyboard sends characters to the server.
    THE NEWLINE CHARACTER IS VERY IMPORTANT 
    Keyboard inputs have the form:
      K char\n

    Server Inputs have the form:
      S command\n
  */
  string keyboardRequest;
  string screenRequest;
  while(true){
    //Server running

    //Parse Keyboard with 1 second timeout
    keyboardRequest = keyboardSerial.readline(1000);
    parseKeyBoardInput(keyboardRequest, screenSerial, keyboardSerial);

    //Parse Screen wiwth 1 second timeout
    screenRequest = screenSerial.readline(1000);
    parseScreenInput(screenRequest, screenSerial, keyboardSerial);
  }

  return 0;
}
