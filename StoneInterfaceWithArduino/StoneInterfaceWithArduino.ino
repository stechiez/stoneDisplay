
#include <SoftwareSerial.h>

#define ADC0_DISPLAY_ADDR 0x0000
#define ADC1_DISPLAY_ADDR 0x0004
#define ADC2_DISPLAY_ADDR 0x0008
#define ADC3_DISPLAY_ADDR 0x000C

#define FRAME_ADDR_INDEX_H  4
#define FRAME_ADDR_INDEX_L  5
#define FRAME_VALUE_INDEX_H  6
#define FRAME_VALUE_INDEX_L  7


SoftwareSerial mySerial(2, 3); // RX, TX

int ldr_value;
int pot_value;

unsigned char display_frame[8] = {0xA5,0x5A, 0x05, 0x82, 0x00,0x00, 0x00, 0x00};

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }


  Serial.println("Goodnight moon!");

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
   ldr_value = analogRead(A0);
   pot_value = analogRead(A1);
   Serial.print("A0 Val : ");
   Serial.print(ldr_value);
   Serial.print("& A1 Val : ");
   Serial.println(pot_value);
   
   send_Value_to_display(ADC0_DISPLAY_ADDR,ldr_value);  //Send Value for ADC0
   send_Value_to_display(ADC1_DISPLAY_ADDR,pot_value);       //Send Value for ADC1

   delay(500);
   
}
