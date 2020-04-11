//Some of these are unused
#include "wdigraph.h"
#include "dijkstra.h"
#include "serialport.h"
#include "keyboardInput.h"
#include "screenInput.h"
#include "fileManager.h"

#include <cassert>
#include <string>
//#include <iostream>
using namespace std;

bool kys(){
  //Screen Serial
  SerialPort screenSerial("/dev/ttyACM0");

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
      //cout<<to_string(numFiles)<<endl;
      // wait for affirmation from the arduino.
      screenRequest = screenSerial.readline(1000);
      cout << screenRequest<<endl;
      if(screenRequest[0] == 'A'){
        while (getline(fileNames, tempfilename)) {
          //string tempfilename;
          //Readlines and get confirmation
          screenSerial.writeline("F "+tempfilename+" \n");
          screenRequest = screenSerial.readline(1000);
          cout << screenRequest<<endl;
          if(screenRequest[0]!= 'B'){
            //restart the loop
            return 0;
          }
        }

        fileNames.close();

        //They are now selecting and all that
        bool selected = false;
        while(!selected){
          screenRequest = screenSerial.readline(1000);
          cout << screenRequest<<endl;
          if(screenRequest[0] == 'N'){
            /*
            cout << screenRequest<<endl;
            string temp = screenRequest[2];
            int temp2 = stoi(temp);
            cout<<temp2<<endl;
           */ 
            string kmfs = screenRequest.substr(2);
            int kmfs_int = stoi(kmfs);
            cout<<kmfs_int<<endl;
            if(kmfs_int == numFiles){
              //New file
              chosenFileIndex = numFiles;
              screenSerial.writeline("A");

              //Accept chars from keyboard to type the textfile name
              //Send those chars to screen, when they hit enter we assume theyre done typing
              //Once theyre done typing send that whole name as one string to screen.
              //Also add that testname to the end of this txt file
              string testfilename = "WaltzisWhite.txt";
              /*
              while (!file.isValidfName(testfilename)) {
                // request other file name
              }*/
              file.setFileName(testfilename);
              file.createFile();

             
              selected = true;

            }
            else if(kmfs_int < numFiles){
              //existing file

              cout<<kmfs_int<<endl;

              chosenFileIndex = kmfs_int;
              screenSerial.writeline("A \n");
              selected = true;
              cout<<"Ive spent 3 hours debugging this fucking shit"<<endl;

              // choose and read from existing
              fileNames.open("textfiles/textFileMaster.txt");
              fileNames >> numFiles;
              fileNames.get();

              for (int i = 0;i<=chosenFileIndex;i++) {
                cout<<"Ive spent 3 hours debugging this fucking shit"<<endl;
                getline(fileNames, tempfilename);
              }
              fileNames.open("textfiles/" + tempfilename);
              //file.setFileName(tempfilename);
              cout<<tempfilename<<endl;
              cout<<"Ive spent 3 hours debugging this fucking shit"<<endl;
              fileContents = file.readContents();
              cout<<"Ive spent 3 hours debugging this fucking shit"<<endl;

              screenSerial.writeline(fileContents);
              
              /*
              for (auto letter : fileContents) {
                if (letter != '\n') {
                  screenSerial.writeline(letter + "\n");
                }
                me.cEnd = me.curIndex = fileContents.length();// ???
              }
              */
              fileSystem = false;
              return 1;
            }

          }
        }

      }
    }
  }

}

int main() {
  //VERY IMPORTANT THIS IS DONE CORRECTLY TRUE
  //Plug in the key board arudino first to set AMC0
  //Keyboard Serial
  //SerialPort keyboardSerial("/dev/ttyACM0");
  while(!kys());
  
}