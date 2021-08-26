#include <Arduino.h>
#include "loramesher.h"

LoraMesher* radio ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio = new LoraMesher();

}

void loop() {
  // put your main code here, to run repeatedly:
  
}