#include <string>
#include <iostream>
#include "serialport.h"

using namespace std;

//Parse request from the keybord 
void parseKeyBoardInput(string request, SerialPort screenSerial, SerialPort keyboardSerial){
    //For now simply reads the character and validates the request

    if(request[0]=='K'){
        cout << "Keyboard Request Valid" << endl;
    }


    request = ""; //Clearing the request after use
}