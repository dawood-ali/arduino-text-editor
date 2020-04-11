#include <string>
#include <iostream>
#include "serialport.h"
#include "fileManager.h"

using namespace std;

int cStart;
int cEnd;
int curIndex;
int endIndex; // Index of the end of the file.

// Holds the contents that you want copied or cut from the string.
string copiedContents;


//Parse request from the keybord
void parseKeyBoardInput(string& request, SerialPort& screenSerial, SerialPort& keyboardSerial, string& contents, contentFunctionality& me, FileManager& file){
    //For now simply reads the character and validates the request
    //Keyboard assumes request in form:
    // K <num>\n


    //Keys array for letters
    string keys = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

    if(request[0]=='K'){
        int val = stoi(request.substr(2));

        // Alphabet
        if(val >= 0 && val <= 25 ){
            string letter(1, keys[val]);
            screenSerial.writeline(letter);
            contents+=letter;

            return;
        }
        
        // caps is 52
        // if()s

        // Space Bar
        else if(val ==53 || val == 54){
            screenSerial.writeline(" ");

            return;
        }

        // Enter word
        if(val == 55){
            screenSerial.writeline("0");
            // do i add \n to the ting?
            return;
        }

        // Delete
        if(val == 56){
            screenSerial.writeline("1");
            if (endIndex > 0) {
              contents.erase(me.endIndex);
              contents.erase(me.endIndex);
              me.endIndex--;
            }
            return;
        }

        // -> arrow, Select
        if(val == 57){
            screenSerial.writeline("rarrow");
            if (me.endIndex > me.curIndex) {
              if (me.toggleSelect && me.endIndex > me.cEnd && me.cEnd == me.curIndex) {
                cEnd++;
              }else if (me.toggleSelect && me.endIndex > me.cStart && me.cStart == me.curIndex) {
                me.cStart++;
              }
              me.curIndex++;
            }
            return;
        }

        // <- arrow, Select
        if(val == 58){
            screenSerial.writeline("larrow");
            if (me.toggleSelect && me.cEnd > 0 && me.cEnd == me.curIndex && me.cEnd != me.cStart) {
              me.cEnd--;
            }else if (me.toggleSelect && me.cStart > 0 && me.cStart == me.curIndex && me.cEnd != me.cStart) {
              me.cStart--;
            }else if (me.toggleSelect && me.cStart > 0 && me.cStart == me.curIndex && me.cEnd == me.cStart) {
              me.cStart--;
            }
            me.curIndex--;
            return;
        }

        // Cut
        if(val == 59){
            // resend all contents yes
            screenSerial.writeline("cut");
            if (me.cStart > me.cEnd) {
              // uhh something went horribly wrong.
            }
            if (me.cEnd >= me.cStart) {
              copiedContents = "";
            }else {
              me.copiedContents = contents.substr(me.cStart,me.cEnd);
              contents.erase(me.cStart,me.cEnd);
            }
            return;
        }

        // Copy
        if(val == 60){
            screenSerial.writeline("copy");
            if (me.cStart > me.cEnd) {
              // uhh something went horribly wrong.
            }
            if (me.cEnd == me.cStart) {
              me.copiedContents = "";
            }else {
              me.copiedContents = contents.substr(me.cStart,me.cEnd);
            }
            return;
        }

        // Paste
        if(val == 61){
            screenSerial.writeline("paste");
            contents.insert(me.curIndex,copiedContents);
            me.curIndex+=copiedContents.length();
            for (auto i : copiedContents) {
              screenSerial.writeline(i+"\n");
            }
            return;
        }

        // Select
        if(val == 62){
            screenSerial.writeline("select");
            if (me.toggleSelect) {
              me.toggleSelect = false;
            }else {
              me.toggleSelect = true;
              me.cEnd = me.cStart = me.curIndex;
            }
            return;
        }

        // Open
        if(val == 63){
            screenSerial.writeline("9");
            contents+="0";
            file.updateContents(contents);
            return;
        }

    }
}
