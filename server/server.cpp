//Some of these are unused
#include "wdigraph.h"
#include "dijkstra.h"
#include "serialport.h"
#include "keyboardInput.h"
#include "screenInput.h"
#include "fileManager.h"

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
  string fileContents = "";
  contentFunctionality me;
  me.toggleSelect = false;

  // whether or not to go to filesystem
  bool fileSystem = true;

  FileManager file;

  while(true) {
    if (fileSystem) {

      int numFiles;
      string tempfilename;
      ifstream fileNames;
      int chosenFileIndex;
      fileNames.open("textfiles/textFileMaster.txt");
      fileNames >> numFiles;
      fileNames.get();
      chosenFileIndex = numFiles + 2;
      // send num to ahmed;
      screenSerial.writeline("N "+to_string(numFiles)+"\n"); // do we need a protocol??

      // wait for affirmation from the arduino.
      screenRequest = screenSerial.readline(50);
      while (getline(fileNames, tempfilename)) {
        screenSerial.writeline(tempfilename+"\n");
      }
      fileNames.close();
      // allow for selection
      while (chosenFileIndex > numFiles + 1) {
        screenRequest = screenSerial.readline(50);
        //string firstletter = screenRequest[0];
        //chosenFileIndex = atoi(firstletter.c_str());
      }
      if (chosenFileIndex > numFiles) {
        // create new file
        // keep gathering characters from the arduino until done, this goes into the following string:
        string testfilename = "AhmedIsGay.txt";
        while (!file.isValidfName(testfilename)) {
          // request other file name
        }
        file.setFileName(testfilename);
        file.createFile();
      }else {
        // choose and read from existing
        fileNames.open("textfiles/textFileMaster.txt");
        fileNames >> numFiles;
        fileNames.get();

        for (int i = 0;i<=chosenFileIndex;i++) {
          getline(fileNames, tempfilename);
        }
        file.setFileName(tempfilename);
        fileContents = file.readContents();
      }
      for (auto letter : fileContents) {
        if (letter != '\n') {
          screenSerial.writeline(letter + "\n");
        }
        me.cEnd = me.curIndex = fileContents.length();
      }
      fileSystem = false;
    }else {
      // readstrngs and check for go to filesystem
      keyboardRequest = keyboardSerial.readline(50);
      if(keyboardRequest.size()!=0){
        parseKeyBoardInput(keyboardRequest, screenSerial, keyboardSerial, fileContents, me);
        keyboardRequest=""; //Empty request when done parsing
      }

      // Parse Screen wiwth 1 second timeout
      screenRequest = screenSerial.readline(50);
      if(screenRequest.size()!=0){
        parseScreenInput(screenRequest, screenSerial, keyboardSerial);
        screenRequest = ""; //Empty request when done parsing
      }
    }
    //Server running

    //Parse Keyboard with 1 second timeout

  }

  return 0;
}
