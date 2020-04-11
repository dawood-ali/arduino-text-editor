#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_

#include <fstream>
#include <string>
#include <iostream>
#include <streambuf>
//FILE MANAGER CLASS DEFINITION
using namespace std;

// returns true if a given filename already exists
bool fexists(string fName) {
  ifstream ifile("textfiles/"+fName);
  return ifile.good();
}

class FileManager{
    public:
      bool isValidfName(string fName) {
        bool invalidChars = false;
        for (auto i : forbiddenChars) {
          if (fName.find(i) != string::npos) {
            invalidChars = true;
            break;
          }
        }
        // invalid chars
        if (invalidChars) {
          //
        }
        // invalid filename, file already exists
        if (fexists(fName)) {
          return false;
        }
        return true;
      }

      void setFileName(string fName) {
        filename = fName;
      }

      // if it can create the file, returns true otherwise does not work
      bool createFile() {
        if (filename != "") {
          ofstream outfile(filename);
          outfile.close();
          newFile = true;
          return true;
        }else {
          return false;
        }
      }

      string readContents() {
        ifstream file("textfiles/" + filename);

        file.seekg(0, ios::end);
        contents.reserve(file.tellg());
        file.seekg(0, ios::beg);

        contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        return contents;
      }

      void updateContents(string updatedContents) {
        contents = updatedContents;
        ofstream fileObject;
        fileObject.open(filename, ofstream::out | ofstream::trunc);
        // fileObject.write(curContents.c_str(),curContents.size());
        fileObject << contents;
        fileObject.close();
        newFile = false;
      }

      int getIndex() {
        return curIndex;
      }

      bool isNew() {
        return newFile;
      }

    private:
      string contents;
      // Current filename, to be changed when dealing with other files.
      string filename = "";

      // fobidden characters for naming a file
      string forbiddenChars = ".<>:\"/\\|?*";
      int curIndex;

      bool newFile = false;
};

struct contentFunctionality {
  int cStart;
  int cEnd;
  int curIndex;
  int endIndex; // Index of the end of the file.
  bool toggleSelect;

  // Holds the contents that you want copied or cut from the string.
  string copiedContents;
};

#endif
