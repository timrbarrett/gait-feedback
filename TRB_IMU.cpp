#ifndef TRB_IMU_CPP
#define TRB_IMU_CPP
 
/*
	include any needed include files
*/

/*
	to complete the library creation task
		must compress the folder and add to libaries.
	there might be a problem updating a 
		previously defined library
*/

#include <Arduino.h>
#include <TRB_IMU.h>

/*
	embellish on the definitions in the header file
	[classname]::[methodName]
*/

/*
	where should this code be used?
*/
void updateIntervalParams(BLEDevice central) {
	// read and update the connection interval that peer central device
	static unsigned short interval = 0x60;
	ble_conn_param_t m_conn_param;
	// Get connection interval that peer central device wanted
	//central.getConnParams(m_conn_param);
	Serial.print("min interval = " );
	Serial.println(m_conn_param.interval_min );
	Serial.print("max interval = " );
	Serial.println(m_conn_param.interval_max );
	Serial.print("latency = " );
	Serial.println(m_conn_param.latency );
	Serial.print("timeout = " );
	Serial.println(m_conn_param.timeout );

	//Update connection interval
	Serial.println("set Connection Interval");
	central.setConnectionInterval(interval, interval);

	interval++;
	if (interval < 0x06)
	interval = 0x06;
	if (interval > 0x100)
	interval = 0x06;
}

void TRB_IMU::inSetup(void) {
	
  // start the IMU and filter
  CurieIMU.begin();
  CurieIMU.setGyroRate(1000);
  CurieIMU.setAccelerometerRate(1000);
  //filter.begin(25);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);
  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);

  // use the code below to calibrate accel/gyro offset values
  if (calibrateOffsets == 1) {
    Serial.println("Internal sensor offsets BEFORE calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
    Serial.print("\t"); // -76
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
    Serial.print("\t"); // -235
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
    Serial.print("\t"); // 168
    Serial.print(CurieIMU.getGyroOffset(X_AXIS));
    Serial.print("\t"); // 0
    Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
    Serial.print("\t"); // 0
    Serial.println(CurieIMU.getGyroOffset(Z_AXIS));

    Serial.println("About to calibrate. Make sure your board is stable and upright");
    delay(5000);

    // The board must be resting in a horizontal position for
    // the following calibration procedure to work correctly!
    Serial.print("Starting Gyroscope calibration and enabling offset compensation...");
    CurieIMU.autoCalibrateGyroOffset();
    Serial.println(" Done");

    Serial.print("Starting Acceleration calibration and enabling offset compensation...");
    CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
    CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
    Serial.println(" Done");

    Serial.println("Internal sensor offsets AFTER calibration...");
    Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
    Serial.print("\t"); // -76
    Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
    Serial.print("\t"); // -2359
    Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
    Serial.print("\t"); // 1688
    Serial.print(CurieIMU.getGyroOffset(X_AXIS));
    Serial.print("\t"); // 0
    Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
    Serial.print("\t"); // 0
    Serial.println(CurieIMU.getGyroOffset(Z_AXIS));
  }
  
  aix = 0;
  aiy = 0;
  aiz = 0;
  gix = 0;
  giy = 0;
  giz = 0;
  
}

void TRB_IMU::inLoop(void) {

    // read raw data from CurieIMU
    CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);
	
    /* can be done after capture; off device
        // convert from raw data to gravity and degrees/second units
        ax = convertRawAcceleration(aix);
        ay = convertRawAcceleration(aiy);
        az = convertRawAcceleration(aiz);
        gx = convertRawGyro(gix);
        gy = convertRawGyro(giy);
        gz = convertRawGyro(giz);
    */


} // end inLoop

float TRB_IMU::convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767

  float a = (aRaw * 2.0) / 32768.0;
  return a;
} // end convertRawAcceleration


float TRB_IMU::convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;
  return g;
} // convertRawGyro

void TRB_IMU::output(File myFile) {
	
	myFile.print(outputString());
	
	/*
    myFile.print('a');
    myFile.print(' ');
    myFile.print(aix);
    myFile.print(',');
    myFile.print(' ');
    myFile.print(aiy);
    myFile.print(',');
    myFile.print(' ');
    myFile.print(aiz);

    myFile.print(',');
    myFile.print(' ');

    myFile.print('g');
    myFile.print(' ');
    myFile.print(gix);
    myFile.print(',');
    myFile.print(' ');
    myFile.print(giy);
    myFile.print(',');
    myFile.print(' ');
    myFile.print(giz);
    myFile.print(' ');
	*/
	
} // end output(File myfile)

String TRB_IMU::outputString() {
	
	String 	information  = "a ";
			information.concat(aix);
			information.concat(", ");
			information.concat(aiy);
			information.concat(", ");
			information.concat(aiz);
			information.concat(", ");
			information.concat("g ");
			information.concat(", ");
			information.concat(gix);
			information.concat(", ");
			information.concat(giy);
			information.concat(", ");
			information.concat(giz);
			information.concat(", ");
			
	//information = "a simple test";
	//information = 
	Serial.println(information);
	Serial.println(aix);

	return information;
	
} // end output(File myfile)

#endif
