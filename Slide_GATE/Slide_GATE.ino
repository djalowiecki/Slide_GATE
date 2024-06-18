#include "Gate.h"

int triggerButton = 7;
int StateLed = 13;
int Current_sensor = 5;
int Optical_sensor = 4;

int stopGate;

int powerEnable = 9;
bool powerState = false;

unsigned long prevTimeLed = 0;

unsigned long prevTimeButton = 50;

unsigned long prevTimeOpt = 0;

unsigned long polling = 0;

//unsigned long prevTimePowerOn = 0;

unsigned int ton = 5;

unsigned int ledTime = 300;

unsigned int cyclicPolling = 500;

unsigned int optSensTime = 100;

//int powerOn = 5000;

bool triggerButtonState = LOW;

int counter = 0;

Gate gate1(11,12,2,3,8,200,2000);
void setup() {
  pinMode(triggerButton, INPUT_PULLUP);
  pinMode(StateLed, OUTPUT);
  pinMode(Current_sensor, INPUT);
  pinMode(Optical_sensor, INPUT);
  pinMode(powerEnable, OUTPUT);
//  digitalWrite(powerEnable, LOW);
  //Serial.begin(9600);

  //attachInterrupt(digitalPinToInterrupt(triggerButton), blink, RISING);
}

void loop() {
  unsigned long currentTime = millis();

 
  if(currentTime - prevTimeLed >= ledTime){
    prevTimeLed = currentTime;
    if((gate1.openState == HIGH)||(gate1.closeState == HIGH)){
      gate1.LedFlashing();
    }
  }
  if (digitalRead(triggerButton) == LOW){
      
      if (currentTime - prevTimeButton >= ton)
      {
        prevTimeButton = currentTime;
        while (digitalRead(triggerButton) == LOW){
          //if(digitalRead(triggerButton) == HIGH){
              //triggerButtonState = !triggerButtonState; 
              triggerButtonState = HIGH;
        }
      }
  }
  if (digitalRead(Optical_sensor) == HIGH){
      
      if (currentTime - prevTimeOpt >= optSensTime)
      {
        prevTimeOpt = currentTime;
          while (digitalRead(Optical_sensor) == HIGH){
              gate1.StopCmd(); 
          }
      }
  }

  if (triggerButtonState == HIGH){ //załączenie bramy gdy otwarta całkowicie lub zamknięta całkowicie
    
    if(gate1.OpenedSens() == HIGH){
      triggerButtonState = LOW;
      gate1.CloseCmd();
      
    }
    if(gate1.ClosedSens() == HIGH){
      triggerButtonState = LOW;
      gate1.OpenCmd();
      
    }  
  }
  if ((gate1.openState == HIGH)&&(gate1.OpenedSens() == HIGH)){ //warunek wyłączenia w przypadku zadziałania czujnika otwarcia
    gate1.GateOpened();
  }
  if ((gate1.closeState == HIGH)&&(gate1.ClosedSens() == HIGH)){ //warunek wyłączenia w przypadku zadziałania czujnika zamknięcia
    gate1.GateClosed();
  }
  if ((gate1.openState == HIGH)&&(triggerButtonState == HIGH)){ //zatrzymanie w trakcie ruchu otwierającego
    triggerButtonState = LOW;
    gate1.StopCmd();
    stopGate = 1;
    delay(1000);
    //stopGate = HIGH;
    
  }
  if ((gate1.closeState == HIGH)&&(triggerButtonState == HIGH)){ // zatrzymanie w trakcie ruchu zamykającego
    triggerButtonState = LOW;
    gate1.StopCmd();
    stopGate = 2;
    delay(1000);
    //stopGate = HIGH;
    
  }
  if ((stopGate == 1)&&(triggerButtonState == HIGH)){
    triggerButtonState = LOW;
    gate1.CloseCmd();
    stopGate = 0;
    
  }
  if ((stopGate == 2)&&(triggerButtonState == HIGH)){
    triggerButtonState = LOW;
    gate1.OpenCmd();
    stopGate = 0;
    
  }
//  if ((gate1.OpenedSens() == LOW)&&(gate1.ClosedSens() == LOW)&&(triggerButtonState == HIGH)){
// //   if (stopGate == LOW){
//      triggerButtonState = LOW;
//      gate1.CloseCmd();
//      //Serial.println("Zamykanie");
//      
//    }
//    if (stopGate == HIGH){
//      gate1.OpenCmd();
//      triggerButtonState = LOW;
//    }
//    stopGate = LOW;
//  }

  if((digitalRead(Current_sensor) == HIGH)&&(currentTime - polling >= cyclicPolling)){
     counter++;
     if (counter >= 4){
          
          counter = 0;
          //Serial.println("prad");
          gate1.CurrentStop();
        }
      } else counter = 0;
      
  if(triggerButtonState == LOW) digitalWrite(StateLed, LOW);

}
//void blink() {
  //triggerButtonState = !triggerButtonState;
  //triggerButtonState = HIGH;
//}
