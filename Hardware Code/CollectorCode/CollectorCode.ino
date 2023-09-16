#include <SparkFunCCS811.h>
#include <Wire.h>

#define esp 0
#define debug 0

#if esp
#define button 12
#define GreenLED 5
#define RedLED 4
#else
#define button 7
#define GreenLED 2
#define RedLED 4
#endif

#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 myCCS811(CCS811_ADDR);

String Name;
String Packet;
long PrevTime = 0;
int WaitTime = 10000;
bool spoof = false;
float lattitude, longitude;

void setup() {
  // put your setup code here, to run once:
#if esp
  Name = "Transmitter B";
  lattitude = 46.73;
  longitude = -92.08;
#else
  Name = "Transmitter A";
  myCCS811.begin();
  lattitude = 41.57;
  longitude = -84.05;
#endif
  
  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(button, INPUT_PULLUP);
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(button) == HIGH && !spoof) {
    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
  } else {
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
    spoof = true;
  }

  if (millis() - PrevTime > WaitTime) {
    if (spoof) {
      Packet = Name+",255,1024,250"+","+String(lattitude)+","+String(longitude);
      spoof = false;
    } else {
#if esp || debug
      Packet = Name+",100,500,50"+","+String(lattitude)+","+String(longitude);
#else
      SetData();
#endif
    }
    Serial.println(Packet);
    PrevTime = millis();
  }
  delay(10);
}

void SetData() {
  Packet = Name + ",";
  if (myCCS811.dataAvailable())
  {
    myCCS811.readAlgorithmResults();
    int tempCO2 = myCCS811.getCO2();
    int tempVOC = myCCS811.getTVOC();
    Packet += (String(tempCO2) + "," + String(tempVOC) + ",");
  }
  else if (myCCS811.checkForStatusError())
  {
    Serial.print("ERROR");
    //while(1);
  }
  Packet += (analogRead(A0))+","+String(lattitude)+","+String(longitude);
}
