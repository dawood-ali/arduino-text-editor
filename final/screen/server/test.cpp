#include "fileManager.h"
#include <string>


int main() {
  FileManager myfile;
  string fileContents;
  myfile.setFileName("kys.txt");
  fileContents = myfile.readContents();
  cout << fileContents << endl;

  return 0;
}
