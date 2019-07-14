#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#include "EtherBerry.h"                         

#define PIN RPI_GPIO_P1_24

EtherBerry::EtherBerry()
{                                                             
}

void EtherBerry::SPI_Write(unsigned char Data)
{
    bcm2835_spi_transfer(Data);
};


unsigned char EtherBerry::SPI_Read(unsigned char Data)
{
    return bcm2835_spi_transfer(Data);
};



bool EtherBerry::Init()
{
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root ?\n");
      return false;
    }

    //Setup SPI pins
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root ?\n");
      return false;
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);     
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                 
    bcm2835_spi_setClockDivider(16);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

  ULONG TempLong;

  Write_Reg (RESET_CTL, (DIGITAL_RST & ETHERCAT_RST)); // LAN9252 reset
  usleep (100);  // wait 100mS
  TempLong.Long = Read_Reg (BYTE_TEST, 4);             // read test register
  //printf("%04x\n",TempLong.Long);
  if (TempLong.Long == 0x87654321)                                  // if the test register is ok 
  {                                                                 // check also the READY flag
    TempLong.Long = Read_Reg (HW_CFG, 4);              //
     if (TempLong.Long & READY)                                     //
     {                                                              //
        //Return SPI pins to default inputs state
        bcm2835_spi_end();
        return true;                                                // initalization completed
     }
   }
     

  bcm2835_spi_end();
  bcm2835_close();

  return false;                                                     // initialization failed
};  


//---- EtherCAT task ------------------------------------------------------------------------------

unsigned char EtherBerry::MainTask()                           // must be called cyclically by the application

{
  bool WatchDog = 0;
  bool Operational = 0; 
  unsigned char i;
  ULONG TempLong;
  unsigned char Status;  

  //Setup SPI pins
  if (!bcm2835_spi_begin())
  {
    printf("bcm2835_spi_begin failed. Are you running as root ?\n");
    return 0;
  }
  // Set the pin to be an output (CS pin)

  bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

  TempLong.Long = Read_Reg_Wait (WDOG_STATUS, 1); // read watchdog status
  if ((TempLong.Byte[0] & 0x01) == 0x01)                    //
    WatchDog = 0;                                           // set/reset the corrisponding flag
  else                                                      //
    WatchDog = 1;                                           //
    
  TempLong.Long = Read_Reg_Wait (AL_STATUS_REG_0, 1);   // read the EtherCAT State Machine status
  Status = TempLong.Byte[0] & 0x0F;                         //
  if (Status == ESM_OP)                                     // to see if we are in operational state
    Operational = 1;                                        //
  else                                                      // set/reset the corrisponding flag
    Operational = 0;                                        //    

                                                            //--- process data transfert ----------
                                                            //                                                        
  if (WatchDog | !Operational)                              // if watchdog is active or we are 
  {                                                         // not in operational state, reset 
    for (i=0; i< TOT_BYTE_NUM_ROUND_OUT; i++)               // the output buffer
    BufferOut.Byte[i] = 0;                                  //

                                                            // debug
    if (!Operational)                                       //
      printf("Not operational\n");                          //
    if (WatchDog)                                           //    
      printf("WatchDog\n");                                 //  
                                                            //
 
  }
  else                                                      
  {                                                         
    SPIReadProcRamFifo();                                   // otherwise transfer process data from 
  }                                                         // the EtherCAT core to the output buffer  

  SPIWriteProcRamFifo();                                    // we always transfer process data from
                                                            // the input buffer to the EtherCAT core  
                                                            
  //Return SPI pins to default inputs state
  bcm2835_spi_end();

  if (WatchDog)                                             // return the status of the State Machine      
  {                                                         // and of the watchdog
    Status |= 0x80;                                         //
  }                                                         //
  return Status;                                            //  

}

    
//---- read a directly addressable registers  -----------------------------------------------------

unsigned long EtherBerry::Read_Reg (unsigned short Address, unsigned char Len)

                                                   // Address = register to read
                                                   // Len = number of bytes to read (1,2,3,4)
                                                   //
                                                   // a long is returned but only the requested bytes
                                                   // are meaningful, starting from LsByte                                                 
{
  ULONG Result; 
  UWORD Addr;
  Addr.Word = Address; 
  unsigned char i; 
  
  SCS_Low_macro                                             // SPI chip select enable

  SPI_Write(COMM_SPI_READ);                            // SPI read command
  SPI_Write(Addr.Byte[1]);                             // address of the register
  SPI_Write(Addr.Byte[0]);                         // to read, MsByte first
 
  for (i=0; i<Len; i++)                                     // read the requested number of bytes
  {                                                         // LsByte first 
    Result.Byte[i] = SPI_Read(DUMMY_BYTE);            //
  }                                                         //    
  
  SCS_High_macro                                            // SPI chip select disable 
 
  return Result.Long;                                       // return the result
}


//---- write a directly addressable registers  ----------------------------------------------------

void EtherBerry::Write_Reg (unsigned short Address, unsigned long DataOut)

                                                   // Address = register to write
                                                   // DataOut = data to write
{ 
  ULONG Data; 
  UWORD Addr;
  Addr.Word = Address;
  Data.Long = DataOut;    
  SCS_Low_macro                                             // SPI chip select enable  
  SPI_Write(COMM_SPI_WRITE);                           // SPI write command
  SPI_Write(Addr.Byte[1]);                             // address of the register
  SPI_Write(Addr.Byte[0]);                             // to write MsByte first
  SPI_Write(Data.Byte[0]);                             // data to write 
  SPI_Write(Data.Byte[1]);                             // LsByte first
  SPI_Write(Data.Byte[2]);                             //
  SPI_Write(Data.Byte[3]);                         //
  SCS_High_macro                                            // SPI chip select enable   
}


//---- read an undirectly addressable registers  --------------------------------------------------

unsigned long EtherBerry::Read_Reg_Wait (unsigned short Address, unsigned char Len)                                                 
{
  ULONG TempLong;
  UWORD Addr;
  Addr.Word = Address;
                                                            // compose the command
                                                            //
  TempLong.Byte[0] = Addr.Byte[0];                          // address of the register
  TempLong.Byte[1] = Addr.Byte[1];                          // to read, LsByte first
  TempLong.Byte[2] = Len;                                   // number of bytes to read
  TempLong.Byte[3] = ESC_READ;                              // ESC read 

  Write_Reg (ECAT_CSR_CMD, TempLong.Long);     // write the command

  do
  {                                                         // wait for command execution
    TempLong.Long = Read_Reg(ECAT_CSR_CMD,4);  //
  }                                                         //
  while(TempLong.Byte[3] & ECAT_CSR_BUSY);                  //
                                                             
                                                              
  TempLong.Long = Read_Reg(ECAT_CSR_DATA,Len); // read the requested register
  return TempLong.Long;                                     //
}


//---- write an undirectly addressable registers  -------------------------------------------------

void  EtherBerry::Write_Reg_Wait (unsigned short Address, unsigned long DataOut)                                                    
{
  ULONG TempLong;
  UWORD Addr;
  Addr.Word = Address;


  Write_Reg (ECAT_CSR_DATA, DataOut);            // write the data

                                                              // compose the command
                                                              //                                
  TempLong.Byte[0] = Addr.Byte[0];                            // address of the register  
  TempLong.Byte[1] = Addr.Byte[1];                            // to write, LsByte first
  TempLong.Byte[2] = 4;                                       // we write always 4 bytes
  TempLong.Byte[3] = ESC_WRITE;                               // ESC write

  Write_Reg (ECAT_CSR_CMD, TempLong.Long);       // write the command

  do                                                          // wait for command execution
  {                                                           //
    TempLong.Long = Read_Reg (ECAT_CSR_CMD, 4);  //  
  }                                                           //  
  while (TempLong.Byte[3] & ECAT_CSR_BUSY);                   //
  
}


//---- read from process ram fifo ----------------------------------------------------------------

void EtherBerry::SPIReadProcRamFifo()  
{
  //ULONG TempLong;
  unsigned char i;
  uint32_t rxTmp;

  Write_Reg (ECAT_PRAM_RD_CMD, PRAM_ABORT);        // abort any possible pending transfer
  Write_Reg (ECAT_PRAM_RD_ADDR_LEN, (0x00001000 | (((uint32_t)TOT_BYTE_NUM_OUT) << 16)));
  Write_Reg (ECAT_PRAM_RD_CMD, 0x80000000);        // start command                                                                  
                                                                                                                               
  do                                                            // wait for data to be transferred      
  {                                                             // from the output process ram 
    rxTmp = Read_Reg (ECAT_PRAM_RD_CMD,2); // to the read fifo 
  }                                                             //    
  while (((rxTmp >> 8) & 0xff) != FST_LONG_NUM_OUT);

 
  SCS_Low_macro                                                 // SPI chip select enable  
  
  SPI_Write(COMM_SPI_READ);                                // SPI read command
  SPI_Write(0x00);                                         // address of the read  
  SPI_Write(0x00);                                     // fifo MsByte first
  

  for (i=0; i<TOT_BYTE_NUM_ROUND_OUT; i++)                      // read loop 
  {                                                             // 
    BufferOut.Byte[i] = SPI_Read(DUMMY_BYTE);             //
  }                                                             //
    
  SCS_High_macro                                                // SPI chip select disable    
}


//---- write to the process ram fifo --------------------------------------------------------------

void EtherBerry::SPIWriteProcRamFifo()    // write 32 bytes to the input process ram, through the fifo
                                       //    
                                       // these are the bytes that we have read from the inputs of our                   
                                       // application and that will be sent to the EtherCAT master
{
  //ULONG TempLong;
  unsigned char i;
  uint32_t rxTmp;
  Write_Reg (ECAT_PRAM_RD_CMD, PRAM_ABORT);        // abort any possible pending transfer
  Write_Reg (ECAT_PRAM_WR_ADDR_LEN, (0x00001200 | (((uint32_t)TOT_BYTE_NUM_IN) << 16)));
                                                                // input process ram offset 0x----1200
  Write_Reg (ECAT_PRAM_WR_CMD, 0x80000000);        // start command  

  do                                                            // check fifo has available space     
  {                                                             // for data to be written
    rxTmp = Read_Reg (ECAT_PRAM_WR_CMD,2); //  
  }                                                             //    
  while (((rxTmp >> 8) & 0xff) < FST_LONG_NUM_IN);  
  
  SCS_Low_macro                                                 // enable SPI chip select
  SPI_Write(COMM_SPI_WRITE);                               // SPI write command
  SPI_Write(0x00);                                         // address of the write fifo 
  SPI_Write(0x20);                                         // MsByte first 
  for (i=0; i<TOT_BYTE_NUM_ROUND_IN; i++)                  // bytes write loop
  {                                                        //
    SPI_Write (BufferIn.Byte[i]);                          // 
  }                                                       //
                                                                //  
  SCS_High_macro                                                // disable SPI chip select      
} 
