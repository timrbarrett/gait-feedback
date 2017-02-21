#ifndef TRB_BLE_H
#define TRB_BLE_H

/*
	Include any needed files
*/
#include <CurieBLE.h>

/*
	Define the class
*/

class TRB_BLE {
	
	public:
	
		TRB_BLE(int dummy);
		void inSetup();
		void inLoop();
		
		void transmit(String message);
		
	private:

		/*
			This sets up a transmit and a receive connection to a Genuino 101
		*/
	
		const char* localName = "Steps";
		int BLE_MAX_LENGTH = 20;
		BLEPeripheral blePeripheral;       // BLE of the Genuino101
		BLEService uartService = BLEService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
		BLEDescriptor uartNameDescriptor = BLEDescriptor("2901", localName);
		
		BLECharacteristic rxCharacteristic = BLECharacteristic("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWrite, BLE_MAX_LENGTH);
		static void rxCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic);

		BLEDescriptor rxNameDescriptor = BLEDescriptor("2901", "RX - (Write)");
		BLECharacteristic txCharacteristic = BLECharacteristic("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLEIndicate, BLE_MAX_LENGTH);
		BLEDescriptor txNameDescriptor = BLEDescriptor("2901", "TX - (Indicate)");
  
		BLECentral central = blePeripheral.central();
		
};

#endif