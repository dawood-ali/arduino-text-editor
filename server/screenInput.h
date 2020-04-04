#include <string>
#include "serialport.h"

using namespace std;


//Parse request from the keybord 
void parseScreenInput(string request, SerialPort screenSerial, SerialPort keyboardSerial){
    //Right now I'm not sure wtf this nigga is supposed to be sending back.
    //But using Serial.readline(1000); you can read from the serial.
    //Use whatever method you want to send a valid request from the arduino.
    // Just make sure it matches the scheme in server.cpp file

    //Simple test to validate request
    if(request[0]=='S'){
        cout << "Server request valid" << endl;
    }



    request = ""; // Clear request after use.
}