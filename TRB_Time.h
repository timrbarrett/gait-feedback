#ifndef TRB_Time_H
#define TRB_Time_H

/*
	Include any needed files
*/
#include <SD.h> 		// defines File
#include <RTClib.h> 	// defines rtc

/*
	Define the class
*/

class TRB_Time {
	
	public:
	
		void output(File myFile);
		void inSetup();
		void inLoop();
		String getFilename();
		
	private:
	
		RTC_DS1307 _rtc;
		char _daysOfTheWeek[7][12] = {
			"Sun", 
			"Mon", 
			"Tue", 
			"Wed", 
			"Thu", 
			"Fri", 
			"Sat"
			};
		DateTime  _now;
		
};

#endif