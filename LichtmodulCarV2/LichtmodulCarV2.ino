//
// 23.01.2013
// V2 11.11.2015
/*
1577-1583

 1667-1673

 1758-1768

 1847-1854

 1936-1942

 */

unsigned long nextPrint = 0;

unsigned long duration1;
unsigned long duration2;

char buffer[15];

long randNumber = 0;
long randomNext = 0;
int randomSeq = 0;

#define DEBUG

// Prototypen Platine KJK Xray T3 2010
//#define PROTOTYP
#define GELAENDE


#ifdef GELAENDE
int PWM1 = 12;
int PWM2 = 11;

int BRAKE = 2;
int LOWBEAM = 6;
int BACKLIGHT = 13;
int TURNSIGNAL = 5;
int SPOTLIGHT = 4;
int DAYLIGHT = 7;

int BACKFIRE = 13;
int TESTLED = 13;
int HIGHBEAM = 3;

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

class Switch {
  private:
    int timeout;
    int switch_locked;
    int switched;
    unsigned long upper_sp;   
    unsigned long lower_sp;     
    
  public:
    Switch(int lower_sp, int upper_sp);
    int Update(unsigned long duration);
};


Switch::Switch(int lower_sp, int upper_sp) {
  this->timeout = 0;
  this->switch_locked = false;
  this->switched = 0;
  this->upper_sp = upper_sp;
  this->lower_sp = lower_sp;
}

int Switch::Update(unsigned long duration) {
  if (duration > this->lower_sp && duration < this->upper_sp && !this->switch_locked) {
    if (this->timeout == 0) {
      this->timeout = millis() / 1000;
    }
  
    if ((millis() / 1000) > (this->timeout + 1)) {
      if (this->switched == true) {
        Serial.println("class Switch aus");
        this->switched = false;
      }
      else {
        Serial.println("class Switch an");
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
  digitalWrite(SPOTLIGHT, 0);
  digitalWrite(BACKLIGHT, 1);

  delay(1000);
  digitalWrite(BRAKE, 0);
  digitalWrite(HIGHBEAM, 0);
  digitalWrite(LOWBEAM, 0);
  digitalWrite(BACKFIRE, 1);
  digitalWrite(SPOTLIGHT, 1);
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

Switch sw1(700, 1200);
Switch sw2(1200, 1400);
Switch sw3(1400, 1600);
Switch sw4(1600, 1800);
Switch sw5(1800, 2300);

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
 
    switch1 = sw1.Update(duration1);
    switch2 = sw2.Update(duration1);
    switch3 = sw3.Update(duration1);
    switch4 = sw4.Update(duration1);
    switch5 = sw5.Update(duration1);
         
    if(switch1 == true) {   
   
    }


    if(switch2 == true) {
      backFireEnabled = true;
    } else {
      backFireEnabled = false;
    }  

    if(switch3 == true) { // low beam
      //if(!switch5)
        analogWrite(LOWBEAM, 64);
      //digitalWrite(LOWBEAM, 0);
      //analogWrite(BRAKE, 192);
    } else {
      digitalWrite(LOWBEAM, 0);
      //if(!switch5)
      //  digitalWrite(LOWBEAM, 1);
      //  digitalWrite(BRAKE, 1);
    } 
       

    
    if(switch4 == true) {
      digitalWrite(DAYLIGHT, 0);
    } else {
      digitalWrite(DAYLIGHT, 1);
    }

    
    

    if(switch5 && switch3) {
      digitalWrite(LOWBEAM, 1);
      //if(duration2 > 1450) {
      //  analogWrite(BRAKE, 192); // low beam back light
      //}      
      //if(!switch3)
      //  analogWrite(LOWBEAM, 192);
    }   


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

    #ifdef GELAENDE
    if(backFireEnabled == true) {
      digitalWrite(TURNSIGNAL, !digitalRead(TURNSIGNAL));
      delay(550);
    }
    
    // brake
    if (duration2 > 1550) { // brake light switch
      if(!switch3) // wenn abblendlicht an
        digitalWrite(BRAKE, 0); // off
    } else {
      //if(!switch5)
        digitalWrite(BRAKE, 1); // on
    }
    
    #endif
    
    nextPrint = millis () + 10;
  }
}

