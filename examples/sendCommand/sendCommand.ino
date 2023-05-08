 /*************************************************
File:             sendCommand.ino
Description:      1.5W Microporous atomization module
Note:               
**************************************************/
#include <BM52D5021-1.h> 
uint8_t Atomize_mode=1;     ///atomizer ID 01 OPEN,00 CLOSE tx_buff[4]
uint8_t Work_Time=2;       ///work time 1=1min   tx_buff[5]
uint8_t PWM_level=1;     ///PWM_level(val=1,2,3)     tx_buff[6]  val 1=50% duty,  val 2=75%duty  valval 3=99%duty
uint8_t Count_flag=0;

BM52D5021_1 myatomizer(2,3);//rxPin 2, txPin 3, Please comment out the line of code if you don't use software Serial
//BM52D5021_1 myatomizer(&Serial1);//Please uncomment out the line of code if you use HW Serial1 on BMduino
//BM52D5021_1 myatomizer(&Serial2);//Please uncomment out the line of code if you use HW Serial2 on BMduino
//BM52D5021_1 myatomizer(&Serial3);//Please uncomment out the line of code if you use HW Serial3 on BMduino
//BM52D5021_1 myatomizer(&Serial4);//Please uncomment out the line of code if you use HW Serial4 on BMduino

 void setup()
{ 
  Serial.begin(9600);   //Serial
  myatomizer.begin();    
  pinMode(LED_BUILTIN, OUTPUT); 
}
void loop()
{ 
   if (myatomizer.sendID()==0&&Count_flag==0)
       {
        myatomizer.sendCOMMAND(Atomize_mode,Work_Time,PWM_level);
        digitalWrite(LED_BUILTIN,HIGH);
        Count_flag=1;
        }   
}
