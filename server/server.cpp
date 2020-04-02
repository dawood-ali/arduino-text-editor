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

  if (fexists(fName+".txt")) {
    cout << "fileName already exists" << endl;
  }
  ifstream ifile(fName);
  return ifile.good();
}

void createFile(string fName) {}

// returns a string with all the contents of a text file
// This currently only works with files that are known to be in the folder.
string readContents(string fName) {

  string contents;
  int len = fName.length();
  string extension = fName.substr(len-4,len);
  string addExt = "";
  ifstream file(fName+addExt);

  file.seekg(0, ios::end);
  contents.reserve(file.tellg());
  curIndex = file.tellg();
  curIndex--;
  file.seekg(0, ios::beg);

  contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  return contents;
}

void fillScreen(string fName) {
  //text character limit??
  curContents = readContents(fName);

  /*
  for (auto character : curContents) {
    cout << character;
  }
  cout << endl;*/
}

// decides what to do with given ascii  (copy/paste functionality)
void copyCutPaste(int val) {
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
  string curFileName = "AhmedIsGay.txt";
  string poop = curFileName.substr(13,14);
  cout << curFileName << endl;
  curFileName.insert(14," Poop");
  cout << curFileName << endl;
  curFileName.insert(7,"nt");
  cout << curFileName << endl;

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
