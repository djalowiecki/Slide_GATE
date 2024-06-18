class Gate
{
  int OpenPin; //wyjście otwierania bramy
  int ClosePin; //wyjście zamykania bramy
  
  int LedPin; // wyjście sygnalizujące otwieranie/zamykanie bramy

  int DeadTime; //czas przełączania kierunków obrotów
  int DelayTime; //czas opóźnienia załączania otwierania/zamykania bramy


  
  public:
    int Opened_sensor; //czujnik całkowitego otwarcia
    int Closed_sensor; //czujnik całkowitego zamknięcia
    

    bool openState = LOW;
    bool closeState = LOW;
    bool stopState = LOW;

    bool ledState = LOW;

    unsigned long getTime;
    
    Gate(int openPin, int closePin, int o_sens, int c_sens, int led_pin, int dead_time, int dalay_time)
    {
      OpenPin = openPin;
      ClosePin = closePin;
      Opened_sensor = o_sens;
      Closed_sensor = c_sens;
      LedPin = led_pin;
      DeadTime = dead_time;
      DelayTime = dalay_time;
      pinMode(OpenPin, OUTPUT);
      pinMode(ClosePin, OUTPUT);
      pinMode(Opened_sensor, INPUT_PULLUP);
      pinMode(Closed_sensor, INPUT_PULLUP);
      
      pinMode(LedPin, OUTPUT);   

      digitalWrite(OpenPin,LOW);
      digitalWrite(ClosePin,LOW);
      digitalWrite(LedPin,LOW);

    }  
     void OpenCmd(){
      if(closeState == LOW){
        digitalWrite(OpenPin, HIGH);
        openState = HIGH;
      }
    }
    void CloseCmd(){
      if(openState == LOW){
        digitalWrite(ClosePin, HIGH);
        closeState = HIGH;
      }
    }
    void StopCmd(){
      if((openState == HIGH)||(closeState == HIGH)){
        digitalWrite(OpenPin, LOW);
        digitalWrite(ClosePin, LOW);
        stopState = HIGH;
        openState = LOW;
        closeState = LOW;
        digitalWrite(LedPin,LOW);
      }
    }
    void LedFlashing(){
      ledState= !ledState;
      digitalWrite(LedPin, ledState);      
    }
    void CurrentStop(){
      StopCmd();
    }
    bool OpenedSens(){
      if(digitalRead(Opened_sensor)== HIGH) return 1;
      else return 0;
    }
    bool ClosedSens(){
      if(digitalRead(Closed_sensor)== HIGH) return 1;
      else return 0;
    }
    void GateOpened(){
       StopCmd();
    }
    void GateClosed(){
       StopCmd();
    }
    
};
