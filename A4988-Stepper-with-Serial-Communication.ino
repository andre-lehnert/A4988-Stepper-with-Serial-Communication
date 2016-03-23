
#include <Stepper-A4988.h>

A4988 stepper_1(26, 24, 22); // step, direction, enable pin
A4988 stepper_2(25, 23, 27); // step, direction, enable pin
A4988 stepper_3(30, 32, 28); // step, direction, enable pin

const int stepsPerRound = 200;
const int fullLength = 7;

String in = "";
String stepper = "-1";
String dir = "none";
String mode = "s";

void setup() {
  stepper_1.disable();
  stepper_2.disable();  
  stepper_3.disable();
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {

    in = Serial.readString();

    stepper = in.substring(0,1);
    dir = in.substring(2,3);
    mode = in.substring(4,5);

    String myString ="Stepper: " + stepper + ", Direction: " + dir + ", Mode: " + mode + "\r\n";
    char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
    myString.toCharArray(buf, myString.length()+1);  
    Serial.println(buf);
    free(buf);

    if (stepper == "0") {
      
      stepper_1.enable();
      
      if (dir == "u") { // up
        stepper_1.up();
      } else {
        stepper_1.down();
      }
      
      delay(10);

      int steps = 0;
      
      if (mode == "f") {
        steps = stepsPerRound * fullLength;
      } else if (mode == "s") {
        steps = stepsPerRound;
      }
      for (int i = 0; i < steps; i++) {
        stepper_1.doStep();
      }

      delay(10);

      stepper_1.disable();

      delay(10);
      
    } else if (stepper == "1") {
      
      stepper_2.enable();
      
      if (dir == "u") { // up
        stepper_2.up();
      } else if (mode == "s") {
        stepper_2.down();
      }
      
      delay(10);

      int steps = 0;
      
      if (mode == "f") {
        steps = stepsPerRound * fullLength;
      } else {
        steps = stepsPerRound;
      }
      for (int i = 0; i < steps; i++) {
        stepper_2.doStep();
      }

      delay(10);

      stepper_2.disable();

      delay(10);
      
    } else if (stepper == "2") {
      
      stepper_3.enable();
      
      if (dir == "u") { // up
        stepper_3.up();
      } else if (mode == "s") {
        stepper_3.down();
      }
      
      delay(10);

      int steps = 0;
      
      if (mode == "f") {
        steps = stepsPerRound * fullLength;
      } else {
        steps = stepsPerRound;
      }
      for (int i = 0; i < steps; i++) {
        stepper_3.doStep();
      }

      delay(10);

      stepper_3.disable();

      delay(10);
      
    }



  }

}
