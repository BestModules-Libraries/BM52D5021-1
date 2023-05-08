 /*************************************************
File:             BM52D5021-1.h
Author:           BESTMODULES
Description:      Define classes and required variables
History：     
  V1.00.1   -- initial version；2023-03-08；Arduino IDE :  ≥v1.8.16
**************************************************/
#ifndef BM52D5021_1_H_
#define BM52D5021_1_H_

#include <Arduino.h>
#include <SoftwareSerial.h>  

#define HARDSERIAL 0
#define SOFTSERIAL 1

#define ID_bit1 0x02
#define ID_bit2 0 
#define ID_bit3 0
class BM52D5021_1{
  public:
  BM52D5021_1(HardwareSerial *theSerial=&Serial);
  BM52D5021_1(uint8_t rxPin, uint8_t txPin);
  void begin();
  uint8_t sendCOMMAND(uint8_t mode,uint8_t worktime,uint8_t duty);
  uint8_t sendID(); 
  
  private:
    uint8_t _rxPin;
    uint8_t _txPin;
    HardwareSerial*_serial =NULL;
    SoftwareSerial*_softSerial =NULL;
    uint8_t array_uart_txbuff[8];
    uint8_t array_uart_rxbuff[8];
    uint8_t readID_flag;
    uint8_t readcommand_flag;
	  uint8_t Read_count;
    uint8_t readCOMMAND();
    uint8_t readID();
    void writeBytes(uint8_t wbuf[], uint8_t wlen);
};


#endif
