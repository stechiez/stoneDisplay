#include <SoftwareSerial.h>

#define ADC0_DISPLAY_ADDR 0x0108  //memory address for Slider and Guage

#define FRAME_ADDR_INDEX_H    4
#define FRAME_ADDR_INDEX_L    5
#define FRAME_VALUE_INDEX_H   6
#define FRAME_VALUE_INDEX_L   7


SoftwareSerial mySerial(2, 3); // RX, TX

int Slider_Guage_Value;

unsigned char display_frame[8] = {0xA5,0x5A, 0x05, 0x82, 0x00,0x00, 0x00, 0x00};

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);  
}

void send_Value_to_display(int addr,int value)
{
  display_frame[FRAME_ADDR_INDEX_H] = (addr & 0xFF00) >> 8;
  display_frame[FRAME_ADDR_INDEX_L] = (addr & 0x00FF);
  display_frame[FRAME_VALUE_INDEX_H] = (value & 0xFF00) >> 8;
  display_frame[FRAME_VALUE_INDEX_L] = (value & 0x00FF);
  mySerial.write(display_frame,8);
}

void loop() // run over and over
{
   Slider_Guage_Value = analogRead(A0);

   Serial.print("A0 Val : ");
   Serial.println(Slider_Guage_Value);

   send_Value_to_display(ADC0_DISPLAY_ADDR,Slider_Guage_Value);  //Send Value for ADC0

   delay(500);   
}
