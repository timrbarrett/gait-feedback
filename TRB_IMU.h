#ifndef TRB_IMU_H
#define TRB_IMU_H

/*
	Include any needed files
*/
	
#include <CurieIMU.h>
#include <SD.h> 			// defines File

/*
	Define the class
*/

class TRB_IMU {

	public:
		
		void inSetup();
		void inLoop();
		void output(File myfile);
		
		float convertRawAcceleration(int aRaw);
		float convertRawGyro(int gRaw);
		
		String outputString();
		
	private:
		
		/* places to store the accelerometer and gyroscope output */
		static const int DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS = 10;
		
		int aix, aiy, aiz;
		int gix, giy, giz;
		
		float ax, ay, az;
		float gx, gy, gz;
		
		float roll, pitch, heading;
		
		float accelScale, gyroScale;
		
		static const int calibrateOffsets = 1;
		
		/* places in memory to generate char* to output */
		char out_ax[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_ay[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_az[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];

		char out_gx[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_gy[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_gz[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];

		char out_mh[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_mp[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];
		char out_mr[DECIMAL_LENGTH_OF_FLOATS_CONVERTED_TO_STRINGS];

	
};

#endif