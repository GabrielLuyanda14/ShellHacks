#include <SparkFunCCS811.h>

#define button 7
#define GreenLED 2
#define RedLED 4
#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

CCS811 myCCS811(CCS811_ADDR);

String Name;

void setup() {
  // put your setup code here, to run once:
  myCCS811.begin();

  Serial.begin(9600);
  Serial.println("Starting");

  pinMode(button, INPUT_PULLUP);
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);

  Name = "Transmitter A";
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(Name+",");
  if(digitalRead(button) == HIGH){
    if (myCCS811.dataAvailable())
    {
      myCCS811.readAlgorithmResults();
      int tempCO2 = myCCS811.getCO2();
      int tempVOC = myCCS811.getTVOC();
      Serial.print(String(tempCO2)+","+String(tempVOC)+",");
    }
    else if (myCCS811.checkForStatusError())
    {
      //Serial.print("Fuck you");
      //while(1);
    }
  
    Serial.println(((analogRead(A0))));// * (3300/1024))-500)/10);

    digitalWrite(GreenLED, HIGH);
    digitalWrite(RedLED, LOW);
    
  }else{
    Serial.println("255,1024,250");
    digitalWrite(GreenLED, LOW);
    digitalWrite(RedLED, HIGH);
  }
  delay(10000); //Wait for next reading
}
