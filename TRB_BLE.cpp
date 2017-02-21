#ifndef TRB_BLE_CPP
#define TRB_BLE_CPP

/*
	Include any needed files
*/
#include <TRB_BLE.h>


TRB_BLE::TRB_BLE(int dummy) {
	  // listen for BLE peripherals to connect:
  central = blePeripheral.central();
}


void TRB_BLE::inSetup() {
	
 /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet 
 */
  blePeripheral.setLocalName(localName);
  blePeripheral.setAdvertisedServiceUuid(uartService.uuid());  		// add the service UUID
  blePeripheral.addAttribute(uartService);   						// Add the uart service
  blePeripheral.addAttribute(txCharacteristic); 					// add the transmit characteristic
  blePeripheral.addAttribute(rxCharacteristic); 					// the the receive characteristic

  rxCharacteristic.setEventHandler(BLEWritten, TRB_BLE::rxCharacteristicWritten);
  // & worked
  /* Now activate the BLE device.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */
  blePeripheral.begin();
  
  if (Serial) {
	Serial.println("Bluetooth device active, waiting for connections...");
  }
	
}

void TRB_BLE::inLoop(){
	
	// listen for BLE peripherals to connect:
	central = blePeripheral.central();
	
	/* 
		if (central)
			
		while (central.connected())
			
	*/
	if (central) {
	    blePeripheral.poll();
	}
}

void TRB_BLE::rxCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic) {
	
  // central wrote new value to characteristic
  Serial.print("Characteristic event, written: ");

  if (characteristic.value()) {
	  
    int characteristiclength = characteristic.valueLength();
    Serial.println(characteristic.valueLength());
	
    for( int idx = 0 ; idx < characteristiclength ; ++idx ){
        Serial.print( (char)characteristic[ idx ] );
    }
    
  }
}

void TRB_BLE::transmit(String message) {
	
	unsigned int transmittedUntilByte =0;
	
	while ((message.length()-transmittedUntilByte) > BLE_MAX_LENGTH) {
		// message needs sending in smaller chunks 
		
		int str_len = BLE_MAX_LENGTH;
		char char_array[str_len];
		message.substring(transmittedUntilByte,BLE_MAX_LENGTH).toCharArray(char_array,str_len);
		txCharacteristic.setValue((unsigned char*)char_array, str_len);
		
		Serial.print("compound from:");
		Serial.print(transmittedUntilByte);
		Serial.print(" to:");
		Serial.print(transmittedUntilByte);
		Serial.print(BLE_MAX_LENGTH);
		Serial.print(" message sent:");
		blePeripheral.poll();
		
		transmittedUntilByte+=BLE_MAX_LENGTH;
		/*
			// Length (with one extra character for the null terminator)
			int str_len = message.length() + 1; 
			// Prepare the character array (the buffer) 
			char char_array[str_len];
			// Copy it over 
			message.toCharArray(char_array, str_len);
	
			txCharacteristic.setValue((unsigned char*)char_array, str_len);
	
			Serial.println("message sent:");
			blePeripheral.poll();
		*/
	}
	
	int str_len = message.length() - transmittedUntilByte;
	char char_array[str_len];
	message.substring(transmittedUntilByte,transmittedUntilByte+str_len).toCharArray(char_array,str_len);
	txCharacteristic.setValue((unsigned char*)char_array, str_len);
	
	Serial.print("simple from:");
	Serial.print(transmittedUntilByte);
	Serial.print(" to:");
	Serial.print((transmittedUntilByte+str_len));
	////Serial.print(" message sent:");
	blePeripheral.poll();
	
}

#endif