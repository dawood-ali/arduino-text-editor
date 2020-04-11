#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>

#include "fileManager.h"

using namespace std;

int cStart;
int cEnd;
int curIndex;
int endIndex; // Index of the end of the file.

// Holds the contents that you want copied or cut from the string.
string copiedContents;

bool toggleSelect = false;

// Current filename, to be changed when dealing with other files.
string curFileName;

string masterTextFile = "TextFileMaster.txt";

/*
Naming Scheme:
  cur: current (curFileName)
  c: copy/cut

Handshake Scheme:
  1: cut
  2: copy
  3: paste

Define ascii functionalities:
  254: paste
  253: cut
  252: copy
  251: shift cursor right
  250: shift cursor left
  249: toggle select
*/

// returns true if a given filename already exists
bool fexists(string fName) {

  ifstream ifile(fName);
  return ifile.good();
}

/*
What it does:
  Checks whether a given filename is valid.
  checks for invalid characters, will cout the general error

To do:
  integrate with server, so that it displays these messages on the screen during file naming

Input:
  name of a file in string format

Outputs:
  whether the given filename is valid given the conditions
*/

// decides what to do with given ascii  (copy/paste functionality)
void copy_paste_index_functionality(int val) {
  if (val == 254) // Paste
  {
    curContents.insert(curIndex,copiedContents);
    // if selection is active, delete current selection from text file and paste to given index
  }else if (val == 253) // cut
  {
    if (cStart > cEnd) {
      // uhh something went horribly wrong.
    }
    if (cEnd == cStart) {
      copiedContents = "";
    }else {
      copiedContents = curContents.substr(cStart,cEnd);
      curContents.erase(cStart,cEnd);
    }
  }else if (val == 252) // copy
  {
    if (cStart > cEnd) {
      // uhh something went horribly wrong.
    }
    if (cEnd == cStart) {
      copiedContents = "";
    }else {
      copiedContents = curContents.substr(cStart,cEnd);
    }
  }else if (val == 251) // shift right
  {
    if (endIndex > curIndex) {
      if (toggleSelect && endIndex > cEnd && cEnd == curIndex) {
        cEnd++;
      }else if (toggleSelect && endIndex > cStart && cStart == curIndex) {
        cStart++;
      }
      curIndex++;
    }
  }else if (val == 250) // shift left
  {
    if (toggleSelect && cEnd > 0 && cEnd == curIndex && cEnd != cStart) {
      cEnd--;
    }else if (toggleSelect && cStart > 0 && cStart == curIndex && cEnd != cStart) {
      cStart--;
    }else if (toggleSelect && cStart > 0 && cStart == curIndex && cEnd == cStart) {
      cStart--;
    }
    curIndex--;
  }else if (val == 249) // toggle select
  {
    if (toggleSelect) {
      toggleSelect = false;
    }else {
      toggleSelect = true;
      cEnd = curIndex + 1;
      cStart = curIndex + 1;
    }
  }else if (val == 249) // redo
  {

  }
}

int main() {
  curFileName = "AhmedIsGay.txt";
  FileManager curFile;
  if (curFile.isValidfName(curFileName)) {
    curFile.setFileName(curFileName);
  }else {
    curFileName = "AhmedIsGay";
    if (curFile.isValidfName(curFileName)) {
      curFile.setFileName(curFileName);
    }
  }
  int endIndex = curFileName.length();
  cout << "before: " << curFileName << endl;
  endIndex--;
  curFileName.erase(endIndex);
  cout << "after: " << curFileName << endl;




}
