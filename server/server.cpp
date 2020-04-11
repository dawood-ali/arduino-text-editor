//Some of these are unused
#include "wdigraph.h"
#include "dijkstra.h"
#include "serialport.h"
#include "keyboardInput.h"
#include "screenInput.h"
#include "fileManager.h"

#include <cassert>
#include <string>
#include <iostream>
#include <unistd.h>


int main() {
  //VERY IMPORTANT THIS IS DONE CORRECTLY TRUE
  //Plug in the key board arudino first to set AMC0
  //Keyboard Serial
  SerialPort keyboardSerial("/dev/ttyACM0");
  //Screen Serial
  SerialPort screenSerial("/dev/ttyACM1");

  //TODO: Initialize file manager object here

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
      //cout<<to_string(numFiles)<<endl;
      // wait for affirmation from the arduino.
      screenRequest = screenSerial.readline(1000);
      cout << to_string(numFiles) <<endl;

      if(screenRequest[0] == 'A'){
        while (getline(fileNames, tempfilename)) {
          //string tempfilename;
          //Readlines and get confirmation
          screenSerial.writeline("F "+tempfilename+" \n");
          screenRequest = screenSerial.readline(1000);
          cout << tempfilename << endl;
          cout << screenRequest << endl;
          if(screenRequest[0]!= 'B'){
            //restart the loop
            // return 0;
          }
        }

        fileNames.close();

        //They are now selecting and all that
        bool selected = false;
        while(!selected){
          screenRequest = screenSerial.readline(1000);
          // cout << screenRequest<<endl;
          if(screenRequest[0] == 'N'){
            /*
            cout << screenRequest<<endl;
            string temp = screenRequest[2];
            int temp2 = stoi(temp);
            cout<<temp2<<endl;
           */ 
            cout << screenRequest<<endl;
            string kmfs = screenRequest.substr(2);
            int kmfs_int = stoi(kmfs);


            cout<<kmfs_int<<endl;
            if(kmfs_int == numFiles){
              //New file
              chosenFileIndex = numFiles;
              screenSerial.writeline("A \n");

              //Accept chars from keyboard to type the textfile name
              //Send those chars to screen, when they hit enter we assume theyre done typing
              //Once theyre done typing send that whole name as one string to screen.
              //Also add that testname to the end of this txt file
              bool testFilling = true;
              string testfilename = "";
              while(testFilling){
                
                keyboardRequest = keyboardSerial.readline(500);
                cout << keyboardRequest << endl;
                if(keyboardRequest.size()>2){
                  if(keyboardRequest[0]=='K' && stoi(keyboardRequest.substr(2)) != 55 ){
                    string keys = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

                    int ind = stoi(keyboardRequest.substr(2));
                    
                    string letter(1, keys[ind]);

                    testfilename+=letter;

                    screenSerial.writeline(letter);

                    keyboardRequest = keyboardSerial.readline(50);


                  }else{
          
                    if(stoi(keyboardRequest.substr(2)) == 55){
                      screenSerial.writeline("0");
                      keyboardRequest = keyboardSerial.readline(500);
                      testFilling = false;
                    }
                  }
                }

              }
          
              file.setFileName("textfiles/" + testfilename + ".txt");
              file.createFile();

              fileNames.open("textfiles/" + testfilename + ".txt");
              file.setFileName("textfiles/" + testfilename + ".txt");
              
              

              selected = true;
              fileSystem = false;

              

            }
            else if(kmfs_int < numFiles){
              //existing file

              cout<<kmfs_int<<endl;

              chosenFileIndex = kmfs_int;
              screenSerial.writeline("A \n");
              selected = true;
            
              // choose and read from existing
              fileNames.open("textfiles/textFileMaster.txt");
              fileNames >> numFiles;
              fileNames.get();

              for (int i = 0;i<=chosenFileIndex;i++) {
                getline(fileNames, tempfilename);
              }
              fileNames.open("textfiles/" + tempfilename);
              file.setFileName(tempfilename);
              cout<<tempfilename<<endl;
              fileContents = file.readContents();
              // screenSerial.writeline(fileContents);
              
              cout << "Hello" << endl;
              // screenSerial.writeline(tempfilename);

              for (auto letter : fileContents) {
                if (letter != '0') {
                  string tempString(1, letter);
                  screenSerial.writeline(tempString);
                  cout << tempString << endl;
                  usleep(50000);
                }else{
                  fileContents = fileContents.substr(0, fileContents.find("0"));
                  file.updateContents(fileContents);
                }
                me.cEnd = me.curIndex = fileContents.length();// ???
              }
              
              selected = true;
              fileSystem = false;
            }
          }
        }
      }
    }else {
      // readstrngs and check for go to filesystem
      keyboardRequest = keyboardSerial.readline(500);
      if(keyboardRequest.size()!=0){
        parseKeyBoardInput(keyboardRequest, screenSerial, keyboardSerial, fileContents, me, file);
        keyboardRequest= keyboardSerial.readline(50); //Empty request when done parsing
      }

      // Parse Screen wiwth 1 second timeout
      screenRequest = screenSerial.readline(500);
      if(screenRequest.size()!=0){
        parseScreenInput(screenRequest, screenSerial, keyboardSerial, fileSystem);
        screenRequest = ""; //Empty request when done parsing
      }
    }

  }

  return 0;
}
