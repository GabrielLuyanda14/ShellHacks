#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    lcd.begin(16, 2);
    Serial.begin(9600);

}

void loop() {
    if (Serial.available()) {
        delay(100);
        lcd.clear();
        while (Serial.available() > 0) {
            // format string string,rrr,ggg,bbb
            String in = Serial.readString();
            int index = in.indexOf(',');
            String out = in.substring(0,index);

            int r = in.substring(index+1,index+4).toInt();
            int g = in.substring(index+5,index+8).toInt();
            int b = in.substring(index+9,index+12).toInt();
            //Serial.println(in.substring(index+1,index+4)+", "+in.substring(index+5,index+8)+", "+in.substring(index+9,index+12));
            lcd.write(out.c_str());
            lcd.setRGB(r,g,b);
        }
    }
}
