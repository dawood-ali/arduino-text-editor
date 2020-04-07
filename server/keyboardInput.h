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
    string keys = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

    if(request[0]=='K'){
        int val = stoi(request.substr(2));

        // Alphabet
        if(val >= 0 && val <= 51 ){
            string letter(1, keys[val]);
            screenSerial.writeline(letter + "\n");

            return;
        }

        // Space Bar
        else if(val == 52 || val == 53){
            screenSerial.writeline(" \n");

            return;
        }

        // Enter word
        else if(val == 54){
            screenSerial.writeline("enter\n");

            return;
        }

        // Delete
        else if(val == 55){
            screenSerial.writeline("delete\n");

            return;
        }

        // -> arrow, Select
        else if(val == 54){
            screenSerial.writeline("rarrow\n");

            return;
        }

        // <- arrow, Select
        else if(val == 55){
            screenSerial.writeline("larrow\n");

            return;
        }

        // Cut
        else if(val == 56){
            screenSerial.writeline("cut\n");

            return;
        }

        // Copy
        else if(val == 57){
            screenSerial.writeline("copy\n");

            return;
        }

        // Paste
        else if(val == 58){
            screenSerial.writeline("paste\n");

            return;
        }

        // Select
        else if(val == 59){
            screenSerial.writeline("select\n");

            return;
        }

        // Find
        else if(val == 60){
            screenSerial.writeline("find\n");

            return;
        }

        // Replace
        else if(val == 61){
            screenSerial.writeline("replace\n");

            return;
        }

        // Undo
        else if(val == 62){
            screenSerial.writeline("undo\n");

            return;
        }

        // Redo
        else if(val == 63){
            screenSerial.writeline("redo\n");

            return;
        }

    }
}
