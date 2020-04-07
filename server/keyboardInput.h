#include <string>
#include <iostream>
#include "serialport.h"

using namespace std;

//Parse request from the keybord 
void parseKeyBoardInput(string& request, SerialPort& screenSerial, SerialPort& keyboardSerial){
    //For now simply reads the character and validates the request
    //Keyboard assumes request in form:
    // K <num>\n

    //Keys array for letters
    string keys = "qwertyuiopasdfghjklzxcvbnm";
    
    if(request[0]=='K'){
        int val = stoi(request.substr(2));
        
        // Alphabet
        if(val>=0 && val <=25 ){
            string letter(1, keys[val]);
            screenSerial.writeline(letter + "\n");

            return;
        }

        // Caps
        if(val == 26){
            screenSerial.writeline("caps\n");

            return;
        }

        // Space Bar
        if(val ==27 || val == 28){
            screenSerial.writeline(" \n");

            return;
        }

        // Enter word
        if(val == 29){
            screenSerial.writeline("enter\n"); 

            return;           
        }

        // Delete
        if(val == 30){
            screenSerial.writeline("delete\n");

            return;
        }

        // -> arrow, Select 
        if(val == 31){
            screenSerial.writeline("rarrow\n");

            return;
        }

        // <- arrow, Select 
        if(val == 32){
            screenSerial.writeline("larrow\n");

            return;
        }

        // Cut 
        if(val == 33){
            screenSerial.writeline("cut\n");

            return;
        }

        // Copy 
        if(val == 34){
            screenSerial.writeline("copy\n");

            return;
        }

        // Paste 
        if(val == 35){
            screenSerial.writeline("paste\n");

            return;
        }

        // Select
        if(val == 36){
            screenSerial.writeline("select\n");

            return;
        }

        // Find
        if(val == 37){
            screenSerial.writeline("find\n");

            return;
        }

        // Replace
        if(val == 38){
            screenSerial.writeline("replace\n");

            return;
        }

        // Undo
        if(val == 39){
            screenSerial.writeline("undo\n");

            return;
        }

        // Redo
        if(val == 40){
            screenSerial.writeline("redo\n");

            return;
        }

    }
}