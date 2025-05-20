
#include "MegaJoy.h"

void setup(){
  setupPins();
  setupMegaJoy();
}

void loop(){
  // Always be getting fresh data
  megaJoyControllerData_t controllerData = getControllerData();
  setControllerData(controllerData);
}

void setupPins(void){
  // Set all the digital pins as inputs
  // with the pull-up enabled, except for the 
  // two serial line pins
  for (int i = 2; i <= 54; i++){
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
}

int pinMapToDS(int i){
  // Using this mapping, the pin number should correspond to the same numbered button.
  // i.e. Pin 2 -> Button 2.
  // This has the side effect of there being no intuitive input for button 1 since pin 1 is used for serial communication, however I think that's a fair tradeoff
  // for simpler implementation.
  switch(i) {
    case 2: return 5;
    case 3: return 3;
    case 4: return 2;
    case 5: return 6;
    case 6: return 9;
    case 7: return 7;
    case 8: return 10;
    case 9: return 12;
    case 10: return 13;
    case 11: return 8;
    case 12: return 11;
    case 13: return 14;
    default: return i;
  }
}

megaJoyControllerData_t getControllerData(void){
  
  // Set up a place for our controller data
  //  Use the getBlankDataForController() function, since
  //  just declaring a fresh dataForController_t tends
  //  to get you one filled with junk from other, random
  //  values that were in those memory locations before
  megaJoyControllerData_t controllerData = getBlankDataForMegaController();
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  for (int i = 2; i < 54; i++){
    controllerData.buttonArray[(pinMapToDS(i) - 2) / 8] |= (!digitalRead(i)) << ((pinMapToDS(i) - 2) % 8);
  }
  
  // Set the analog sticks
  //  Unlike UnoJoy, which has 8-bit analog axes for PS3 compatibilty,
  //  MegaJoy uses 10-bit analog values, to fully use the Arduino analogRead range
  controllerData.analogAxisArray[0] = analogRead(A0);
  controllerData.analogAxisArray[1] = analogRead(A1);
  controllerData.analogAxisArray[2] = analogRead(A2); 
  controllerData.analogAxisArray[3] = analogRead(A3); 
  controllerData.analogAxisArray[4] = analogRead(A4); 
  controllerData.analogAxisArray[5] = analogRead(A5); 
  controllerData.analogAxisArray[6] = analogRead(A6); 
  controllerData.analogAxisArray[7] = analogRead(A7); 
  controllerData.analogAxisArray[8] = analogRead(A8); 
  controllerData.analogAxisArray[9] = analogRead(A9); 
  controllerData.analogAxisArray[10] = analogRead(A10); 
  controllerData.analogAxisArray[11] = analogRead(A11); 
  
  // And return the data!
  return controllerData;
}
