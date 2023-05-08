 /*************************************************
File:               BM52D5021-1.cpp
Author:             BESTMODULES
Description:        UART communication with BM52D5021_1  
History：     
  V1.00.1   -- initial version；2023-03-08；Arduino IDE :  ≥v1.8.16
**************************************************/
#include <BM52D5021-1.h>

/**********************************************************
Description: Select the hardware serial port you need to use
Parameters:   *theSerial：hardware serial 
             BMduino optional:serial(default) serial1/seria2/seria3/seria4
             UNO optional:serial(default)
Return:      none    
Others:      
**********************************************************/
BM52D5021_1::BM52D5021_1(HardwareSerial*theSerial)
{
  _serial = theSerial;
  _softSerial = NULL;
}

/**********************************************************
Description: Select the software serial port RX TX you need to use
Parameters:   rxPin:RX pin on the development board
             txPin:TX pin on the development board
Return:      none    
Others:      
**********************************************************/
BM52D5021_1::BM52D5021_1(uint8_t rxPin, uint8_t txPin)
{
  _serial = NULL;
  _rxPin = rxPin;
  _txPin = txPin;
  _softSerial = new SoftwareSerial(_rxPin, _txPin);
}
/**********************************************************
Description: Set serial baud rate
Parameters:   uartBaud：9600(default)
Return:      none
Others:
**********************************************************/
void BM52D5021_1::begin(){
  if (_softSerial != NULL)
  {
    _softSerial->begin(9600);
  }
  else{
    _serial->begin(9600);
  }
}
/*************************************************
Description:        雾化模式、時間设置
Parameters:          @param  mode 雾化模式，worktime霧化工作時間，duty PWM duty控制         
Return:             
Others:             
*************************************************/
uint8_t BM52D5021_1::sendCOMMAND(uint8_t mode,uint8_t  worktime,uint8_t  duty){
      unsigned int i;
      uint8_t array_uart_txbuff[8] = {0x55,0x31,0x01,0x03,mode,worktime,duty,0} ;
      for(i=0;i<7;i++)
     {
      array_uart_txbuff[7] += array_uart_txbuff[i] ;      
     }
      writeBytes(array_uart_txbuff,8);
      delay(10); 
      return readCOMMAND();
}
/*************************************************
Description:        發送ID
Parameters:          @param  NULL         
Return:             
Others:             
*************************************************/
uint8_t BM52D5021_1::sendID(){
      unsigned int i;
      uint8_t array_uart_txbuff[8] = {0x55,0x31,0x01,3,ID_bit1,ID_bit2,ID_bit3,0};
      
      for(i=0;i<7;i++)
     {
      array_uart_txbuff[7] += array_uart_txbuff[i] ;      
     }

    writeBytes(array_uart_txbuff,8);
    delay(10);
    
    return readID();
    
}
/*************************************************
Description:        检查接收数据帧帧头、校验和等
Parameters:          @param  null           
Return:             byte 数据帧状态
Others:             
*************************************************/
uint8_t BM52D5021_1::readCOMMAND() {
   delay(10); 
   byte Read_count=1;
  if (_softSerial != NULL)
  {
    if(_softSerial->available()>0) 
   {
      for(Read_count=0;Read_count<8;Read_count++)
     {
         delay(5);
     array_uart_rxbuff[Read_count] =_softSerial->read();
     } 
    
      if((array_uart_rxbuff[0]==0x55)&&(array_uart_rxbuff[7]==(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]+array_uart_rxbuff[4]+array_uart_rxbuff[5]+array_uart_rxbuff[6])))            
     {
    readcommand_flag=0;
     } 
  }
  }
  else
  {
    if(_serial->available()>0) 
   {
      for(Read_count=0;Read_count<8;Read_count++)
     {
         delay(5);
     array_uart_rxbuff[Read_count] =_serial->read(); 
     } 
    
      if((array_uart_rxbuff[0]==0x55)&&(array_uart_rxbuff[7]==(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]+array_uart_rxbuff[4]+array_uart_rxbuff[5]+array_uart_rxbuff[6])))            
     {
    readcommand_flag=0;
     } 
  }
  }
  return readcommand_flag;
} 
/*************************************************
Description:        驗證ID
Parameters:          @param   
Return:             readID_ok
Others:             
*************************************************/
uint8_t BM52D5021_1::readID() {
   delay(10); 
   byte ReadID_count=1;
   if (_softSerial != NULL)
  {
      if(_softSerial->available()>0) 
   {
      for(ReadID_count=0;ReadID_count<8;ReadID_count++)
     {
         delay(5);
        array_uart_rxbuff[ReadID_count] =_softSerial->read();       
     }     
      if((array_uart_rxbuff[0]==0x55)&&(array_uart_rxbuff[7]==(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]+array_uart_rxbuff[4]+array_uart_rxbuff[5]+array_uart_rxbuff[6])))            
     {
          if((array_uart_rxbuff[4]==0x02) && (array_uart_rxbuff[5]==0) && (array_uart_rxbuff[6]==0)) 
      { 
        readID_flag = 0; }
     }      
   } 
  }
  else
  {
    if(_serial->available()>0) 
   {
      for(ReadID_count=0;ReadID_count<8;ReadID_count++)
     {
         delay(5);
        array_uart_rxbuff[ReadID_count] =_serial->read();     
     } 
    
      if((array_uart_rxbuff[0]==0x55)&&(array_uart_rxbuff[7]==(array_uart_rxbuff[0]+array_uart_rxbuff[1]+array_uart_rxbuff[2]+array_uart_rxbuff[3]+array_uart_rxbuff[4]+array_uart_rxbuff[5]+array_uart_rxbuff[6])))            
     {
          if((array_uart_rxbuff[4]==0x02) && (array_uart_rxbuff[5]==0) && (array_uart_rxbuff[6]==0)) 
      { 
        readID_flag = 0; }
     }      
   } 
  }
  return readID_flag;
}
/*************************************************
Description:       writeBytes
Parameters:       wbuf[]：UART   data
                  wlen：lenth
Return:        none
Others:       none       
*************************************************/
void BM52D5021_1::writeBytes(uint8_t wbuf[], uint8_t wlen)
{
  /* Select SoftwareSerial Interface */
  if (_softSerial != NULL)
  {
    while (_softSerial->available() > 0)
    {
      _softSerial->read();
    }
    _softSerial->write(wbuf, wlen);
  }
  /* Select HardwareSerial Interface */
  else
  {
    while (_serial->available() > 0)
    {
      _serial->read();
    }
    _serial->write(wbuf, wlen);
  }
}
