/*

*/

#include <TRB_IMU.h>
#include <TRB_Time.h>
#include <TRB_BLE.h>

/*
 * create instances of library objects
 */
TRB_IMU               imu;
TRB_Time              timeObject;
TRB_BLE               ble(0);
//TRB_BLE               ble;

File                  myFile;
String                fileName;

unsigned long microsNow;
unsigned long futureTime;
unsigned long microsPerReading, microsPrevious;

void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  //while (!Serial) { ; // wait for serial port to connect. Needed for native USB port only }
  fileName = timeObject.getFilename();
  Serial.println("fileName is " + fileName);
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open(fileName, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    ///Serial.print("Writing to test.txt...");
    ///myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / 100;
  microsPrevious = micros();

  imu.inSetup();
  timeObject.inSetup();
  ble.inSetup();
  /*
     Define the 5000 second delay to take reading after all of the initialisation code has run
  */
  futureTime = millis() + 5000*1000;
}

void loop() {
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    Serial.print("Writing to " + fileName + "...");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening " + fileName);
  }
  
  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    imu.inLoop();
    timeObject.inLoop();
    ble.inLoop();
    ble.transmit(imu.outputString());
    timeObject.output(myFile);
    imu.output(myFile);

    myFile.print('p');
    myFile.print(' ');
    myFile.print(analogRead(A0));
    myFile.print(' ');
    myFile.print(',');
    myFile.println(analogRead(A1));

    myFile.close();
  }
}
