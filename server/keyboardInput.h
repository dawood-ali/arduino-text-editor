#include <string>
#include <iostream>
#include "serialport.h"

using namespace std;

//Parse request from the keybord 
void parseKeyBoardInput(string request, SerialPort screenSerial, SerialPort keyboardSerial){
    //For now simply reads the character and validates the request
    //Keyboard assumes request in form:
    // K <num>\n

    //Keys array for letters
    string keys = "qwertyuiopasdfghjklzxcvbnm";
    
    if(request[0]=='K'){
        int val = stoi(request.substr(2));
        
        // Alphabet
        if(val>=0 && val <=25 ){
            string letter = keys[val] + "\n";
            screenSerial.writeline(letter);

            return;
        }

        // Caps
        if(val == 26){
            screenSerial.writeline("caps");

            return;
        }

        // Space Bar
        if(val ==27 || val == 28){
            screenSerial.writeline("space");

            return;
        }

        // Enter word
        if(val == 29){
            screenSerial.writeline("enter"); 

            return;           
        }

        // Delete
        if(val == 30){
            screenSerial.writeline("delete");
        }

        // -> arrow, Select 
        if(val == 31){
            screenSerial.writeline("rarrow");
        }

        // <- arrow, Select 
        if(val == 32){
            screenSerial.writeline("larrow");
        }

        // Cut 
        if(val == 33){
            screenSerial.writeline("cut");
        }

        // Copy 
        if(val == 34){
            screenSerial.writeline("copy");
        }

        // Paste 
        if(val == 35){
            screenSerial.writeline("paste");
        }

        // Select
        if(val == 36){
            screenSerial.writeline("select");
        }

        // Find
        if(val == 37){
            screenSerial.writeline("find");
        }

        // Replace
        if(val == 38){
            screenSerial.writeline("replace");
        }

        // Undo
        if(val == 39){
            screenSerial.writeline("undo");
        }

        // Redo
        if(val == 40){
            screenSerial.writeline("redo");
        }

    }


    request = ""; //Clearing the request after use
}