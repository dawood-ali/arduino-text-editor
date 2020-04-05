#include <cassert>
#include "serialport.h"
#include <iostream>
#include <string>

using namespace std;

String temp1 = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam ac arcu mattis purus luctus ultricies. Proin facilisis egestas quam quis fringilla. Phasellus lacinia quam id neque molestie volutpat. Vestibulum tincidunt blandit fringilla. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi vitae facilisis velit. Vestibulum libero ante, vehicula a viverra ac, congue ut tellus. Sed sit amet urna ac dolor maximus laoreet eu vel urna. Fusce vel molestie felis, quis maximus felis. Donec purus magna, hendrerit a vulputate sed, pulvinar id dui. Suspendisse viverra justo a ligula laoreet, sit amet luctus enim aliquet. Praesent consectetur elit purus, sed gravida lectus ultricies eget. Ut lacus nulla hello.";
String temp2 = "Lorus ipsum dolor sit amet, consectetur adipiscing elit. Aliquam ac arcu mattis purus luctus ultricies. Proin facilisis egestas quam quis fringilla. Phasellus lacinia quam id neque molestie volutpat. Vestibulum tincidunt blandit fringilla. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Morbi vitae facilisis velit. Vestibulum libero ante, vehicula a viverra ac, congue ut tellus. Sed sit amet urna ac dolor maximus laoreet eu vel urna. Fusce vel molestie felis, quis maximus felis. Donec purus magna, hendrerit a vulputate sed, pulvinar id dui. Suspendisse viverra justo a ligula laoreet, sit amet luctus enim aliquet. Praesent consectetur elit purus, sed gravida lectus ultricies eget. Ut lacus nulla hello."

int main{
	while (true) {
	    // establish communication

	    rLine = Serial.readline(1000);
	    //cout<<rLine<<endl;

	    if (rLine[0] == 'N') {
	      cout<<rLine<<endl;
	      string p[2];
	      int at = 0;
	      for (auto c : rLine) {
	        if (c == ' ') {
	          // start new string
	          ++at;
	        }
	        else if (c == '\n') {
	        }
	        else {
	          // append character to the string we are building
	          p[at] += c;
	        }
	      }

	      int page_num = static_cast<int>(stoi(p[1]));
	      if(page_num == 1){
	      	//Next page

	      	Serial.writeline(temp1 + "\n");
	      }
	      else{
	      	//previous page
	      	Serial.writeline(temp2+ "\n");

	      }

	  	}
	}

}