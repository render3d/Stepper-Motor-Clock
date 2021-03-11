//Include the Arduino Libraries
#include <Wire.h>
#include <RTClib.h>
#include <Stepper.h>

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

Stepper stepper(STEPS, 8, 10, 9, 11);

float spm = 12.5;

float tic;
float toc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initialising...");
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time.");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("RTC found, setting time.");

    // Current time
    DateTime now = rtc.now();
    tic = now.second();
    
    Serial.println("Current Date & Time: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  
    // calculate a time 60 seconds into the future
    DateTime future (now + TimeSpan(0,0,0,60));
    toc = future.second();
    
    Serial.println("Future Date & Time (Now + 60s): ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();

    Serial.println(future.second(), DEC);
    delay(2000); // wait for two second
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  tic = now.second();
  Serial.print("TIC:");
  Serial.print(now.second(), DEC);
  Serial.println();

  if (tic == toc) {
    stepper.setSpeed(6); // 6 rpm
    stepper.step(spm); // do 12.5 steps 
    delay(2000); // wait for two second
    Serial.print("TOC:");
    Serial.print(String(toc));
    Serial.println();
    }
}
