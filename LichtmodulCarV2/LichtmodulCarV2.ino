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

//#define DEBUG

// Prototypen Platine KJK Xray T3 2010
//#define PROTOTYP

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
#else
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
int switch1_timeout = 0;
int switch1_locked = false;

int switch2 = false;
int switch2_timeout = 0;
int switch2_locked = false;

int switch3 = false;
int switch3_timeout = 0;
int switch3_locked = false;

int switch4 = false;
int switch4_timeout = 0;
int switch4_locked = false;

int switch5 = false;
int switch5_timeout = 0;
int switch5_locked = false;


class Switch {
  private:
    int timeout;
    int switch_locked;
    
  public:
    Switch();
    void Update(unsigned long duration);
};


Switch::Switch() {
  this->timeout = 0;
  this->switch_locked = 0;
}

void Switch::Update(unsigned long duration) {
 
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

  pinMode(BRAKE, OUTPUT);
  pinMode(BACKFIRE, OUTPUT);
  pinMode(BACKLIGHT, OUTPUT);
  pinMode(SPOTLIGHT, OUTPUT);
  pinMode(HIGHBEAM, OUTPUT);
  pinMode(LOWBEAM, OUTPUT);

  pinMode(TESTLED, OUTPUT);

  digitalWrite(BRAKE, 0);
  digitalWrite(HIGHBEAM, 0);
  digitalWrite(LOWBEAM, 0);
  digitalWrite(BACKFIRE, 0);
  digitalWrite(SPOTLIGHT, 0);
  digitalWrite(BACKLIGHT, 1);

  delay(1000);
  digitalWrite(BRAKE, 1);
  digitalWrite(HIGHBEAM, 1);
  digitalWrite(LOWBEAM, 1);
  digitalWrite(BACKFIRE, 1);
  digitalWrite(SPOTLIGHT, 1);
  digitalWrite(BACKLIGHT, 0);

  delay(1000);

  randomSeed(analogRead(0));

}

void loop() {

  if (millis() > nextPrint) {

    duration2 = pulseIn(PWM1, HIGH); // Kanal 2 GAS
    duration1 = pulseIn(PWM2, HIGH); // Kanal 3 Schaltkanal

    //duration1 = duration1 - 150;
 
 
     
     #ifdef DEBUG
        Serial.print("1: ");
        Serial.print(duration1);

        Serial.print(" 2: ");
        Serial.println(duration2);

     #endif
        
       
    


    //duration2 = pulseIn(PWM2, HIGH);




    // 1480
    if (duration2 > 1280) { // brake light switch
      if(!switch5) // wenn abblendlicht an
        digitalWrite(BRAKE, 0); // off
      // XXX
      //digitalWrite(TESTLED, 0);
    } else {
      //if(!switch5)
        digitalWrite(BRAKE, 1); // on
      // XXX
      //digitalWrite(TESTLED, 1);
    }
    
   

    //
    if (duration1 > 800 && duration1 < 1200 && !switch1_locked) {
      //   if(duration1 > 800 && !switch1_locked) {
      if (switch1_timeout == 0) {
        switch1_timeout = millis() / 1000;
      }

      if ((millis() / 1000) > (switch1_timeout + 1)) {
        if (switch1 == true) {
          Serial.println("Switch1 aus");
          switch1 = false;
        } else {
          Serial.println("Switch1 an");
          switch1 = true;
        }
          switch1_timeout = 0;
        switch1_locked = true;
      }
    }
    if (duration1 < 800 || duration1 > 1200) {
      //    if(duration1 < 800) {
      switch1_locked = false;
      switch1_timeout = millis() / 1000;
    }

    // 1847-1854
    if (duration1 > 1200 && duration1 < 1400 && !switch2_locked) {
      if (switch2_timeout == 0) {
        switch2_timeout = millis() / 1000;
      }

      if ((millis() / 1000) > (switch2_timeout + 1)) {
        if (switch2 == true) {
          Serial.println("Switch2 aus");
          switch2 = false;
        }
        else {
          Serial.println("Switch2 an");
          switch2 = true;
        }
        switch2_timeout = 0;
        switch2_locked = true;
      }
    }
    if (duration1 < 1200 || duration1 > 1400) {
      switch2_locked = false;
      switch2_timeout = millis() / 1000;
    }

    //
    if (duration1 > 1400 && duration1 < 1600 && !switch3_locked) {
      if (switch3_timeout == 0) {
        switch3_timeout = millis() / 1000;
      }

      if ((millis() / 1000) > (switch3_timeout + 1)) {
        if (switch3 == true) {
          Serial.println("Switch3 aus");
          switch3 = false;
        }
        else {
          Serial.println("Switch3 an");
          switch3 = true;
        }
        switch3_timeout = 0;
        switch3_locked = true;
      }
    }
    if (duration1 < 1400 || duration1 > 1600) {
      switch3_locked = false;
      switch3_timeout = millis() / 1000;
    }

    //
    if (duration1 > 1600 && duration1 < 1800 && !switch4_locked) {
      if (switch4_timeout == 0) {
        switch4_timeout = millis() / 1000;
      }

      if ((millis() / 1000) > (switch4_timeout + 1)) {
        if (switch4 == true) {
          Serial.println("Switch4 aus");
          switch4 = false;
        }
        else {
          Serial.println("Switch4 an");
          switch4 = true;
        }
        switch4_timeout = 0;
        switch4_locked = true;
      }
    }
    if (duration1 < 1600 || duration1 > 1800) {
      switch4_locked = false;
      switch4_timeout = millis() / 1000;
    }

    //
    if (duration1 > 1800 && duration1 < 2200 && !switch5_locked) {
      if (switch5_timeout == 0) {
        switch5_timeout = millis() / 1000;
        Serial.print("Setze Timeout auf: ");
        Serial.println(switch5_timeout);
      }

      if ((millis() / 1000) > (switch5_timeout + 1)) {
        Serial.print(millis() / 1000);
        Serial.print(" ");
        Serial.println(switch5_timeout + 3);
        if (switch5 == true) {
          Serial.println("Switch5 aus");
          switch5 = false;
        }
        else {
          Serial.println("Switch5 an");
          switch5 = true;
        }
        switch5_timeout = 0;
        switch5_locked = true;
      }
    }
    if (duration1 < 1800 || duration1 > 2200) {
      switch5_locked = false;
      switch5_timeout = millis() / 1000;
    }


    if (switch1) {
      // todo
    }

    if (switch2) {
      backFireEnabled = true;
    }
    else {
      backFireEnabled = false;
    }

    if (switch3) {
      digitalWrite(LOWBEAM, 1);
    }
    else {
      if(!switch5)
        digitalWrite(LOWBEAM, 0);
    }


    if (switch4) {
      digitalWrite(HIGHBEAM, 1);
    }
    else {
      digitalWrite(HIGHBEAM, 0);
    }


    if (switch5) {
      if(duration2 > 1280) {
        analogWrite(BRAKE, 32); // low beam back light
      }      
      
      if(!switch3)
        analogWrite(LOWBEAM, 64);
      
      //digitalWrite(LOWBEAM, 1);
      //digitalWrite(BACKLIGHT, 0);

    }
 
    
/*    
    else {
      if(duration2 < 1510) {
        digitalWrite(BRAKE, 0);
      }
      digitalWrite(LOWBEAM, 0);
      //
      //digitalWrite(BACKLIGHT, 1);
    }
    
    */
    
   



    // Backfire aus bei Neutral
    if (duration2 < 1400) {
      backFireEnabled = false;
      //digitalWrite(TESTLED, 0);
    }

    // backfire...
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

    nextPrint = millis () + 10;
    //Serial.println(nextPrint);

  }
}

