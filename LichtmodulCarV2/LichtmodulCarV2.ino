//
// 23.01.2013
// V2 11.11.2015

unsigned long nextPrint = 0;

unsigned long duration1;
unsigned long duration2;

char buffer[15];

long randNumber = 0;
long randomNext = 0;
int randomSeq = 0;

//#define DEBUG

// Prototypen Platine KJK Xray T3 2010
//#define PROTOTYP
#define GELAENDE


#ifdef GELAENDE
int PWM1 = 12;
int PWM2 = 11;
 
int BRAKE = 9;
int LOWBEAM = 6;
int BACKLIGHT = 13;
int TURNSIGNAL = 5;
int SPOTLIGHT = 4;
int DAYLIGHT = 7;

int BACKFIRE = 13;
int TESTLED = 13;
int HIGHBEAM = 3;

unsigned long lastTurnSignal = 0;
unsigned long lastDemoSeq = 0;
unsigned long lastDemoSeq1 = 0;
unsigned long lastDemoSeq2 = 0;
unsigned long lastDemoSeq3 = 0;
unsigned long lastDemoSeq4 = 0;

#endif

#ifdef PROTOTYP
int PWM1 = 12;
int PWM2 = 13;

int BRAKE = 2;
int BACKFIRE = 9;
//int BACKFIRE = 10;
int BACKLIGHT = 3;
int SPOTLIGHT = 10;
int LOWBEAM = 8;
int HIGHBEAM = 11;
int TESTLED = 13;
#endif

#ifdef SONST
int PWM1 = 12;
int PWM2 = 11;

int BRAKE = 5;
int LOWBEAM = 6;
int BACKLIGHT = 2;
int SPOTLIGHT = 4;
int HIGHBEAM = 3;

int BACKFIRE = 7;
//int BACKFIRE = 10;
int TESTLED = 13;
#endif


int backFireEnabled = false;

int switch1 = false;
int switch2 = false;
int switch3 = false;
int switch4 = false;
int switch5 = false;
int switch6 = false;

class Switch {
  private:
    int timeout;
    int switch_locked;
    int switched;
    int switch_identifier;
    unsigned long upper_sp;   
    unsigned long lower_sp;     
    
  public:
    Switch(int lower_sp, int upper_sp, int switch_identifier);
    int Update(unsigned long duration);
};


Switch::Switch(int lower_sp, int upper_sp, int switch_identifier) {
  this->timeout = 0;
  this->switch_locked = false;
  this->switched = 0;
  this->upper_sp = upper_sp;
  this->lower_sp = lower_sp;
  this->switch_identifier = switch_identifier;
}

int Switch::Update(unsigned long duration) {
  if (duration > this->lower_sp && duration < this->upper_sp && !this->switch_locked) {
    if (this->timeout == 0) {
      this->timeout = millis() / 1000;
    }
  
    if ((millis() / 1000) > (this->timeout + 1)) {
      if (this->switched == true) {
        Serial.print(this->switch_identifier);
        Serial.println("off");
        this->switched = false;
      }
      else {
        Serial.print(this->switch_identifier);
        Serial.println("on");
        this->switched = true;
      }
      this->timeout = 0;
      this->switch_locked = true;
    }
  }
  if (duration < this->lower_sp || duration > this->upper_sp) {
    this->switch_locked = false;
    this->timeout = millis() / 1000;
  } 
  return(this->switched);
} 

void setup()
{
  //
  //#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Go!");
  Serial.println(PWM1);
  //#endif

  pinMode(PWM1, INPUT);
  pinMode(PWM2, INPUT);

  
  #ifdef GELAENDE
  pinMode(BRAKE, OUTPUT);
  pinMode(BACKFIRE, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT);
  pinMode(SPOTLIGHT, OUTPUT);
  pinMode(HIGHBEAM, OUTPUT);
  pinMode(LOWBEAM, OUTPUT);
  pinMode(DAYLIGHT, OUTPUT);
  pinMode(TURNSIGNAL, OUTPUT);

  pinMode(TESTLED, OUTPUT);
  
  digitalWrite(BRAKE, 0);
  digitalWrite(HIGHBEAM, 0);
  digitalWrite(LOWBEAM, 0);
  digitalWrite(BACKFIRE, 0);
  digitalWrite(SPOTLIGHT, 1);
  digitalWrite(BACKLIGHT, 1);

  delay(1000);
  digitalWrite(BRAKE, 0);
  digitalWrite(HIGHBEAM, 0);
  digitalWrite(LOWBEAM, 0);
  digitalWrite(BACKFIRE, 1);
  digitalWrite(SPOTLIGHT, 0);
  digitalWrite(BACKLIGHT, 0);
  digitalWrite(DAYLIGHT, 1);  
  digitalWrite(TURNSIGNAL, 0);  
  delay(1000);
  #endif

  randomSeed(analogRead(0));

}

void backfire() {
  
  if (millis() > randomNext && backFireEnabled) {

    randomSeq = random(1, 4);

    if (randomSeq == 1) {
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(50);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(50);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(50);
    }
    else if (randomSeq == 2) {
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(80);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
    }
    else if (randomSeq == 3) {
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
    }
    else if (randomSeq == 4) {
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(80);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(80);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(80);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
      digitalWrite(BACKFIRE, !digitalRead(BACKFIRE));
      delay(20);
    }
    else {
      // huh?
    }

    digitalWrite(BACKFIRE, 1);
    randomNext = millis() + random(1000, 4000);

    Serial.print(millis());
    Serial.print(" ");
    Serial.print(random(1000, 3000));
    Serial.print(" ");
    Serial.println(randomNext);
  }
 
}

#ifdef GELAENDE
Switch sw6(700, 1200, 6);
Switch sw1(1200, 1300, 1);
Switch sw2(1300, 1420, 2);
Switch sw4(1600, 1700, 4);
Switch sw3(1700, 1800, 3);
Switch sw5(1800, 1900, 5);
#endif

#ifndef GELAENDE
Switch sw1(700, 1200, 1);
Switch sw2(1200, 1400, 2);
Switch sw3(1400, 1600, 3);
Switch sw4(1600, 1800, 4);
Switch sw5(1800, 2300, 5);
#endif

void loop() {

  if (millis() > nextPrint) {
    
    #ifdef DEBUG
      Serial.print("1: ");
      Serial.print(duration1);
      Serial.print(" 2: ");
      Serial.println(duration2);
    #endif    

    duration2 = pulseIn(PWM1, HIGH); // channel two throttle
    duration1 = pulseIn(PWM2, HIGH); // channel three switch
 


    // ###########################################################################
    #ifndef GELAENDE
    // brake
    if (duration2 > 1450) { // brake light switch
      if(!switch3) // wenn abblendlicht an
        digitalWrite(BRAKE, 1); // off
    } else {
      //if(!switch5)
        digitalWrite(BRAKE, 0); // on
    }

   
    // backfire off at neutral
    if (duration2 < 1500) {
      backFireEnabled = false;
      //digitalWrite(TESTLED, 0);
    }

    backfire();
    #endif

    
    // ###########################################################################
    #ifdef GELAENDE
   
    switch6 = sw6.Update(duration1);
    if(!switch6) {
      switch1 = sw1.Update(duration1);
      switch2 = sw2.Update(duration1);
      switch3 = sw3.Update(duration1);
      switch4 = sw4.Update(duration1);
      switch5 = sw5.Update(duration1);
    }     

    // demo
    if(switch6) {
      if((millis() - lastDemoSeq) > 10000) {
        digitalWrite(SPOTLIGHT, !digitalRead(SPOTLIGHT));
        delay(100);
        digitalWrite(SPOTLIGHT, !digitalRead(SPOTLIGHT));
        delay(50);
        digitalWrite(SPOTLIGHT, !digitalRead(SPOTLIGHT));
        delay(100);
        digitalWrite(SPOTLIGHT, !digitalRead(SPOTLIGHT));        
        lastDemoSeq = millis();
      }
      
      if((millis() - lastDemoSeq1) > 10000) {
        lastDemoSeq1 = millis();
        switch2 = !switch2;
      }

      if((millis() - lastDemoSeq2) > 20000) {
        lastDemoSeq2 = millis();
        switch3 = !switch3;  
        Serial.println(switch3);            
      }

      if((millis() - lastDemoSeq3) > 5000) {
        lastDemoSeq3 = millis();
        switch5 = !switch5;                           
      }   
      
      if((millis() - lastDemoSeq4) > 7500) {
        lastDemoSeq4 = millis();
        switch4 = !switch4;                           
      }         
    } 
    
    // brake
    if (duration2 > 1550) { // off
      //Serial.println("Bremse aus");
      if(!switch3) { // wenn abblendlicht an
        //Serial.println("LIcht an, Bremse aus");
        digitalWrite(BRAKE, 0); // off        
      } else { 
        analogWrite(BRAKE, 32);
      }
    } else {
        digitalWrite(BRAKE, 1); // on
    }

    // dachbeleuchtung
    if(switch1 == true) {  
      digitalWrite(SPOTLIGHT, 1);
    } else {
      digitalWrite(SPOTLIGHT, 0);
    }

    // turn signal
    if(switch2 == true) {
      backFireEnabled = true;
    } else {
      backFireEnabled = false;
    }    

    if(backFireEnabled == true) {
      //Serial.println("Blinker");
      if((millis() - lastTurnSignal) > 550) {
        digitalWrite(TURNSIGNAL, !digitalRead(TURNSIGNAL));
        lastTurnSignal = millis();
      }
      //delay(550);
    } else {
      digitalWrite(TURNSIGNAL, 0);
    }
     
    // abblendlicht
    if(switch3 == true) { // low beam      
      analogWrite(LOWBEAM, 64);
      //digitalWrite(LOWBEAM, 1);
    } else {
      digitalWrite(LOWBEAM, 0);
    }

    // tagfahrlicht
    if(switch4 == true) {
      digitalWrite(DAYLIGHT, 0);
    } else {
      digitalWrite(DAYLIGHT, 1);
    }

    // fernlicht
    if(switch5 && switch3) {
      digitalWrite(LOWBEAM, 1);
    } 
 
    #endif
    
    nextPrint = millis () + 10;
  }
}

