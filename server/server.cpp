#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>

using namespace std;

int cStart;
int cEnd;
int curIndex;
int endIndex; // Index of the end of the file.

// Holds the contents that you want copied or cut from the string.
string copiedContents;
string curContents;

bool toggleSelect = false;

// Current filename, to be changed when dealing with other files.
string curFileName;

// fobidden characters for naming a file
string forbiddenChars = ".<>:\"/\\|?*";



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
bool isValidfName(string fName) {
  bool invalidChars = false;
  for (auto i : forbiddenChars) {
    if (fName.find(i) != string::npos) {
      invalidChars = true;
      break;
    }
  }
  if (invalidChars) {
    cout << "there are invalid Characters, please do not use any of the following characters when naming a file: " << forbiddenChars << endl;
    return false;
  }
  if (fexists(fName)) {
    cout << "dis is error, filename exists" << endl;
    return false;
  }
  return true;
}

// given all the above functions hold true, we can create the file
void createFile() {
  ofstream outfile(curFileName);
  outfile.close();
}

// returns a string with all the contents of a text file
// This currently only works with files that are known to be in the folder.
string readContents() {
  string contents;

  ifstream file(curFileName);

  file.seekg(0, ios::end);
  contents.reserve(file.tellg());
  curIndex = file.tellg();
  curIndex--;
  file.seekg(0, ios::beg);

  contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return contents;
}

// This function, Will save the contents of the string to a .txt file.
void updateContents() {
  ofstream fileObject;
  fileObject.open(curFileName, ofstream::out | ofstream::trunc);
  // fileObject.write(curContents.c_str(),curContents.size());
  fileObject << curContents;
  fileObject.close();
}

/*
This function does currently nothing
*/
// discuss with ahmed the best way of sending each character.
void sendText() {
  //text character limit??

  /*
  for (auto character : curContents) {
    cout << character;
  }
  cout << endl;*/
}

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
  }
}



int main() {
  curFileName = "AhmedIsGay";
  // cout << curFileName << endl;
  if (isValidfName(curFileName)) {
    cout << "we good" << endl;
    curFileName+=".txt";
  }else{
    cout << "we aint so good" << endl;
    return 0;
  }
  createFile();
  curContents = "poop";
  updateContents();






  //fillScreen(curFileName);



  /*
  fstream curFile;
  char charToAdd = 'A';
  curFile.open(curFileName);
  if (curFile.is_open()) {
    curFile.put(charToAdd);
  }
  curFile.close();
  ofstream outfile;
  outfile.open(curFileName,ios_base::app);
  outfile << 'w';
  outfile.close();
  */

  return 0;
}
