//#define DEBUG_MODE
 #include <LiquidCrystal.h>
 /*
 * Connect following pins from your LCD to arduino as following
 * LCD RS pin -> pin 7
 * LCD E  pin -> pin 6
 * LCD D4 pin -> pin 5 
 * LCD D5 pin -> pin 4
 * LCD D6 pin -> pin 3
 * LCD D7 pin -> pin 2
 * and reset of pins as you do usually !
 */
 LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
void setup() {
  // Open serial communications and wait for port to open:
  lcd.begin(16, 2);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Serial.println("Goodnight moon!");
  //Serial.setTimeout(10000);

}

// LEDs pin numbers 
enum colors{green=9,
            blue=10,
            red=11
};

// Turn on green LED
void turnGreen(int value){
    analogWrite(green,value);
  }

// Turn on red LED
void turnRed(int value){
    analogWrite(red,value);
  }
  
// Turn on blue LED
void turnBlue(int value){
    analogWrite(blue,value);
  }  

void loop() { // run over and over
//Serial.flush();

  String raw_input = Serial.readString(); // get serial input
  raw_input.trim(); // clear all spaces,new lines from raw serial input 
  int str_len = raw_input.length(); // get lenth of raw input 
#ifdef DEBUG_MODE
  //Serial.println(str_len);
#endif  

   // remove all unnecessary text from raw input
   // data length must be 6 charaters length
   raw_input.remove(0,(str_len-6)); 
  
#ifdef DEBUG_MODE
  Serial.println(raw_input.length());
  Serial.println(raw_input);
#endif
  
  /* contains color name + value
  *  I only use 3 letters to represent color name 
  *  Ex. red=red ,gre=green ,blu=blue
  *  and use number its max value is 255 
  *  Ex. gre123 -> color name is green and its value is 123
  */
  String all_color=raw_input;
  
  String color = all_color; // contains color name only 
  color.remove(3);
  if(str_len != 0 ){
    all_color.remove(0,3); // keep only color value 
    if(!(all_color.toInt() > 255 )){
       if(color.equals("red")){
#ifdef DEBUG_MODE      
            Serial.println("Red!");
            Serial.println(all_color);
#endif          
            lcd.clear();
            lcd.print("Red -> ");
            lcd.print(all_color.toInt());
            turnRed(all_color.toInt());
      }else if(color.equals("blu")){
#ifdef DEBUG_MODE      
            Serial.println("Blue!");
            Serial.println(all_color);
#endif
            lcd.clear();
            lcd.print("Blue -> ");
            lcd.print(all_color.toInt());
            turnBlue(all_color.toInt());
      }else if(color.equals("gre")){
#ifdef DEBUG_MODE      
            Serial.println("Green!");
            Serial.println(all_color);
#endif
            lcd.clear();
            lcd.print("Green -> ");
            lcd.print(all_color.toInt());  
            turnGreen(all_color.toInt());
      }
    }
  }
  /**/
//delay(300);
//Serial.flush();
  
}

