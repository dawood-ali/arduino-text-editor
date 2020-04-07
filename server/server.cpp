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
  //Plug in the key board arudino first to set AMC0
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
    keyboardRequest = keyboardSerial.readline(50);
    if(keyboardRequest.size()!=0){
      parseKeyBoardInput(keyboardRequest, screenSerial, keyboardSerial);
      keyboardRequest=""; //Empty request when done parsing
    }

    //Parse Screen wiwth 1 second timeout
    screenRequest = screenSerial.readline(50);
    if(screenRequest.size()!=0){
      parseScreenInput(screenRequest, screenSerial, keyboardSerial);
      screenRequest = ""; //Empty request when done parsing
    }
  }

  return 0;
}
