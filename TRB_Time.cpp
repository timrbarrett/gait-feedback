#ifndef TRB_Time_CPP
#define TRB_Time_CPP

#include <SD.h> // File
#include <RTClib.h> //rtc
#include <TRB_Time.h>

void TRB_Time::output(File myFile) {
	
    myFile.print(_now.year(), DEC);
    myFile.print('/');
    myFile.print(_now.month(), DEC);
    myFile.print('/');
    myFile.print(_now.day(), DEC);
    myFile.print(" (");
    myFile.print(_daysOfTheWeek[_now.dayOfTheWeek()]);
    myFile.print(") ");
    myFile.print(_now.hour(), DEC);
    myFile.print(':');
    myFile.print(_now.minute(), DEC);
    myFile.print(':');
    myFile.print(_now.second(), DEC);
    myFile.print(' ');

    myFile.print( (byte) (millis() >> 24));
    myFile.print(',');
    myFile.print(' ');
    myFile.print( (byte) (millis() >> 16) );
    myFile.print(',');
    myFile.print(' ');
    myFile.print( (byte) (millis() >> 8));
    myFile.print(',');
    myFile.print(' ');

    myFile.print( (byte) millis()  );
    myFile.print(',');
    myFile.print(' ');
	
}

void TRB_Time::inSetup() {
	
	// stop if we have no real time clock
	
	if (! _rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}
  
	 _now = _rtc.now();
}

void TRB_Time::inLoop() {
	
	_now = _rtc.now();

}

String TRB_Time::getFilename() {
	
	_now = _rtc.now();
	
	String filename = "s" +_now.hour() + _now.minute() + _now.second();
	return "21stFeb.txt";//filename;
}
	
#endif