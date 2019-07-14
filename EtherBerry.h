#ifndef Industrialberry_EtherBerry
#define Industrialberry_EtherBerry

// LAN9252 Datasheet TABLE 5-1: SYSTEM CONTROL AND STATUS REGISTERS
// 
// //---- access to EtherCAT registers -------------------
//
#define RESET_CTL               0x01F8
#define ECAT_CSR_DATA           0x0300
#define ECAT_CSR_CMD            0x0304     
#define ECAT_PRAM_RD_ADDR_LEN   0x0308      
#define ECAT_PRAM_RD_CMD        0x030C      
#define ECAT_PRAM_WR_ADDR_LEN   0x0310     
#define ECAT_PRAM_WR_CMD        0x0314     

#define ECAT_PRAM_RD_DATA       0x0000     
#define ECAT_PRAM_WR_DATA       0x0020     

#define ID_REV                  0x0050      
#define IRQ_CFG                 0x0054
#define INT_STS                 0x0058
#define INT_EN                  0x005C
#define BYTE_TEST               0x0064
#define HW_CFG                 	0x0074
#define PMT_CTRL                0x0084
#define GPT_CFG                 0x008C
#define GPT_CNT                 0x0090
#define FREE_RUN                0x009C


// LAN9252 Datasheet TABLE 12-15: ETHERCAT CORE CSR REGISTERS

#define TYPE_REG 				0x0000
#define REV_REG  				0x0001
#define BUILD_REG_1 			0x0002
#define BUILD_REG_2 			0x0003
#define FMMU_REG	 			0x0004
#define SYNCMANAGER_REG	 		0x0005
#define RAM_SIZE_REG 			0x0006
#define PORT_DESCR_REG	 		0x0007
#define ESC_FEATUR_REG_1 		0x0008
#define ESC_FEATUR_REG_2		0x0009
#define CONF_STATION_REG_1 		0x0010
#define CONF_STATION_REG_2		0x0011
#define CONF_STATION_ALI_REG_1 	0x0012
#define CONF_STATION_ALI_REG_2	0x0013
// Write Protection Register
#define WD_REG_EN				0x0020
#define WD_REG_PR				0x0021
#define ESC_WD_REG_EN			0x0030
#define ESC_WD_REG_PR			0x0031
// Data Link Layer
#define ESC_RST_REG				0x0040
#define ESC_RST_PDI_REG			0x0041
#define ECL_DL_CTRL_REG_0		0x0100 
#define ECL_DL_CTRL_REG_1		0x0101 
#define ECL_DL_CTRL_REG_2		0x0102 
#define ECL_DL_CTRL_REG_3		0x0103 
#define PHY_R_W_OFF_1			0x0108
#define PHY_R_W_OFF_2			0x0109
#define ECL_DL_STATUS_REG_0		0x0110 
#define ECL_DL_STATUS_REG_1		0x0111
// Application Layer
#define AL_CTRL_REG_0			0x0120 
#define AL_CTRL_REG_1			0x0121
#define AL_STATUS_REG_0			0x0130 
#define AL_STATUS_REG_1			0x0131
#define AL_STATUS_COD_REG_0		0x0134 
#define AL_STATUS_COD_REG_1		0x0135
#define RUN_LED_OVERRIDE_REG 	0x0138
// PDI (Process Data Interface)
#define PID_CTRL_REG 			0x0140
#define ESC_CONF_REG 			0x0141
#define ASIC_CONF_REG_0			0x0142
#define ASIC_CONF_REG_1			0x0143
#define PID_CONF_REG 			0x0150
#define SYNC_PID_CONF_REG 		0x0151
#define EXT_PID_CONF_REG_0		0x0152
#define EXT_PID_CONF_REG_1		0x0153
// Interrupts
#define ECAT_EVENT_MASK_REG_0	0x0200
#define ECAT_EVENT_MASK_REG_1	0x0201
#define AL_EVENT_MASK_REG_0		0x0204
#define AL_EVENT_MASK_REG_1		0x0205
#define AL_EVENT_MASK_REG_2		0x0206
#define AL_EVENT_MASK_REG_3		0x0207
#define ECAT_EVENT_REQ_REG_0 	0x0210
#define ECAT_EVENT_REQ_REG_1 	0x0211
#define AL_EVENT_REQ_REG_0 		0x0220
#define AL_EVENT_REQ_REG_1 		0x0221
#define AL_EVENT_REQ_REG_2 		0x0222
#define AL_EVENT_REQ_REG_3 		0x0223
// Error Counters
#define RX_ERROR_CNT_REG_0 		0x0300
// ....
#define RX_ERROR_CNT_REG_7 		0x0307
#define FWD_RX_ERROR_CNT_REG_0	0x0308
// ....
#define FWD_RX_ERROR_CNT_REG_B	0x030B
#define ECAT_PRO_UNIT_CNT_ERROR	0x030C
#define PID_CNT_ERROR			0x030D
#define PID_CODE_ERROR			0x030E
#define LOST_LINK_CNT_REG_0 	0x0310
// ....
#define LOST_LINK_CNT_REG_3 	0x0313
// EEPROM Interface
#define EEPROM_CONF_REG 		0x0500
#define EEPROM_PDI_STATE_REG 	0x0501
#define EEPROM_CTRL_REG_0 		0x0502
#define EEPROM_CTRL_REG_1 		0x0503
#define EEPROM_ADDR_REG_0 		0x0504
// ....
#define EEPROM_ADDR_REG_4 		0x0507
#define EEPROM_DATA_REG_0 		0x0508
// ....
#define EEPROM_DATA_REG_4 		0x050B
// MII Management Interface
#define MII_MANAGE_CTRL_REG_0	0x0510
#define MII_MANAGE_CTRL_REG_1	0x0511
#define PHY_ADDR_REG			0x0512
#define PHY_REGISTER_ADDR_REG	0x0513
#define PHY_DATA_REG_0			0x0514
#define PHY_DATA_REG_1			0x0515
#define MII_MANAGE_ECAT_REG		0x0516
#define MII_MANAGE_PDI_REG		0x0517


#define AL_STATUS               0x0130      
#define WDOG_STATUS             0x0440    




// LAN9252 flags
#define PRAM_ABORT        0x40000000
#define ECAT_CSR_BUSY     0x80
#define PRAM_READ_BUSY    0x80
#define PRAM_READ_AVAIL   0x01
#define PRAM_WRITE_AVAIL  0x01
#define READY             0x08000000
#define DIGITAL_RST       0x00000001
#define ETHERCAT_RST      0x00000040

// EtherCAT flags 

#define ESM_INIT                0x01                  // init
#define ESM_PREOP               0x02                  // pre-operational
#define ESM_BOOT                0x03                  // bootstrap
#define ESM_SAFEOP              0x04                  // safe-operational
#define ESM_OP                  0x08                  // operational


// ESC commands 

#define ESC_WRITE 		   0x80
#define ESC_READ 		     0xC0

// SPI 

#define COMM_SPI_READ    0x03
#define COMM_SPI_WRITE   0x02
#define DUMMY_BYTE       0xFF

//typedef 
#define CUSTOM
#define CUST_BYTE_NUM_OUT	15
#define CUST_BYTE_NUM_IN	5

//*************************************************************************************
 
 
 
//-- the preprocessor calculates the parameters necessary to transfer out data --- 

                                                   // define TOT_BYTE_NUM_OUT as the total
                                                   // number of byte you need to
                                                   // transfer in output (between 0 and 128)
                                                   // this must match your ESI XML
                                                   
#define TOT_BYTE_NUM_OUT  CUST_BYTE_NUM_OUT       // any number between 0 and 128



#if ((TOT_BYTE_NUM_OUT & 0x03) != 0x00)             // number of bytes in output
  #define TOT_BYTE_NUM_ROUND_OUT  ((TOT_BYTE_NUM_OUT | 0x03) + 1)  
#else                                               // rounded to 4 (long)
  #define TOT_BYTE_NUM_ROUND_OUT  TOT_BYTE_NUM_OUT  //
#endif                                              //

#if TOT_BYTE_NUM_OUT > 64                           // if we have more then  64 bytes
                                                    // we have to split the transfer in two

  #define SEC_BYTE_NUM_OUT  (TOT_BYTE_NUM_OUT - 64) // number of bytes of the second transfer

  #if ((SEC_BYTE_NUM_OUT & 0x03) != 0x00)           // number of bytes of the second transfer
    #define SEC_BYTE_NUM_ROUND_OUT  ((SEC_BYTE_NUM_OUT | 0x03) + 1)
  #else                                             // rounded to 4 (long)
    #define SEC_BYTE_NUM_ROUND_OUT  SEC_BYTE_NUM_OUT//
  #endif                                            //

  #define SEC_LONG_NUM_OUT  SEC_BYTE_NUM_ROUND_OUT/4// number of long of the second transfer

  #define FST_BYTE_NUM_OUT  64                      // number of bytes of the first transfer
  #define FST_BYTE_NUM_ROUND_OUT  64                // number of bytes of the first transfer
                                                    // rounded to 4 (long)
  #define FST_LONG_NUM_OUT  16                      // number of long of the second transfer

  
#else                                               // if we have 64 bytes max we tranfert
                                                    // them in just one round
                                                        
  #define FST_BYTE_NUM_OUT  TOT_BYTE_NUM_OUT        // number of bytes of the first and only transfer

  #if ((FST_BYTE_NUM_OUT & 0x03) != 0x00)           // number of bytes of the first and only transfer
    #define FST_BYTE_NUM_ROUND_OUT ((FST_BYTE_NUM_OUT | 0x03) + 1)
  #else                                             // rounded to 4 (long)
    #define FST_BYTE_NUM_ROUND_OUT  FST_BYTE_NUM_OUT
  #endif

  #define FST_LONG_NUM_OUT  FST_BYTE_NUM_ROUND_OUT/4// number of long of the first and only transfer

  #define SEC_BYTE_NUM_OUT  0                       // we don't use the second round
  #define SEC_BYTE_NUM_ROUND_OUT  0                 //
  #define SEC_LONG_NUM_OUT  0                       //
  
#endif


//-- the preprocessor calculates the parameters necessary to transfer in data --- 

                                                   // define TOT_BYTE_NUM_IN the total
                                                   // number of byte you need to
                                                   // transfer in input (between 0 and 128)
 
#ifdef  BYTE_NUM
  #define TOT_BYTE_NUM_IN  BYTE_NUM                // bytes in input
#else  
  #define TOT_BYTE_NUM_IN  CUST_BYTE_NUM_IN       // any number between 0 and 128  
#endif

    
#if ((TOT_BYTE_NUM_IN & 0x03) != 0x00)              // number of bytes in output
  #define TOT_BYTE_NUM_ROUND_IN  ((TOT_BYTE_NUM_IN | 0x03) + 1)  
#else                                               // rounded to 4 (long)
  #define TOT_BYTE_NUM_ROUND_IN  TOT_BYTE_NUM_IN    //
#endif                                              //

#if TOT_BYTE_NUM_IN > 64                            // if we have more then  64 bytes
                                                    // we have to split the transfer in two
                                                        
  #define SEC_BYTE_NUM_IN  (TOT_BYTE_NUM_IN - 64)   // number of bytes of the second transfer
  
  #if ((SEC_BYTE_NUM_IN & 0x03) != 0x00)            // number of bytes of the second transfer
    #define SEC_BYTE_NUM_ROUND_IN  ((SEC_BYTE_NUM_IN | 0x03) + 1)  
  #else                                             // rounded to 4 (long)
    #define SEC_BYTE_NUM_ROUND_IN  SEC_BYTE_NUM_IN  //
  #endif                                            //

  #define SEC_LONG_NUM_IN  SEC_BYTE_NUM_ROUND_IN/4  // number of long of the second transfer

  #define FST_BYTE_NUM_IN  64                       // number of bytes of the first transfer     
  #define FST_BYTE_NUM_ROUND_IN  64                 // number of bytes of the first transfer
                                                    // rounded to 4 (long)
  #define FST_LONG_NUM_IN  16                       // number of long of the second transfer

  
#else                                               // if we have 64 bytes max we tranfert
                                                    // them in just one round
                                                        
  #define FST_BYTE_NUM_IN  TOT_BYTE_NUM_IN          // number of bytes of the first and only transfer  

  #if ((FST_BYTE_NUM_IN & 0x03) != 0x00)            // number of bytes of the first and only transfer
    #define FST_BYTE_NUM_ROUND_IN ((FST_BYTE_NUM_IN | 0x03) + 1)
  #else                                             // rounded to 4 (long)
    #define FST_BYTE_NUM_ROUND_IN  FST_BYTE_NUM_IN   
  #endif

  #define FST_LONG_NUM_IN  FST_BYTE_NUM_ROUND_IN/4  // number of long of the first and only transfer
  
  #define SEC_BYTE_NUM_IN  0                        // we don't use the second round
  #define SEC_BYTE_NUM_ROUND_IN  0                  //
  #define SEC_LONG_NUM_IN  0                        //

#endif
 
 
//---------------------------------------------------------------------------------

//----------------- sanity check -------------------------------------------------------                                 
      

#ifdef BYTE_NUM                     // STANDARD MODE and CUSTOM MODE
                                    // cannot be defined at the same time
  #ifdef CUST_BYTE_NUM_OUT 
    #error "BYTE_NUM and CUST_BYTE_NUM_OUT cannot be defined at the same time !!!!"
    #error "define them correctly in file EasyCAT.h"
    #endif
  
  #ifdef CUST_BYTE_NUM_IN 
    #error "BYTE_NUM and CUST_BYTE_NUM_IN cannot be defined at the same time !!!!"
    #error "define them correctly in file EasyCAT.h"
  #endif
#endif 
      
#ifdef BYTE_NUM                     //--- for BYTE_NUM we accept only 16  32  64  128 --
                                  
  #if ((BYTE_NUM !=16) && (BYTE_NUM !=32) && (BYTE_NUM !=64)  && (BYTE_NUM !=128))
    #error "BYTE_NUM must be 16, 32, 64 or 128 !!! define it correctly in file EasyCAT.h"
  #endif 
  
#else
                                   //--- CUST_BYTE_NUM_OUT and CUST_BYTE_NUM_IN --------
                                   //    must be max 128
  #if (CUST_BYTE_NUM_OUT > 128)
    #error "CUST_BYTE_NUM_OUT must be max 128 !!! define it correctly in file EasyCAT.h"
  #endif 
  
  #if (CUST_BYTE_NUM_IN > 128)
    #error "CUST_BYTE_NUM_IN must be max 128 !!! define it correctly in file EasyCAT.h"
  #endif 
  
#endif 


typedef union
{
    unsigned short  Word;
    unsigned char   Byte[2];

} UWORD;

typedef union
{
    unsigned long   Long;
    unsigned short  Word[2];
    unsigned char   Byte[4];

} ULONG;



typedef union												//---- output buffer ----
{
	uint8_t  Byte [TOT_BYTE_NUM_ROUND_OUT];
	struct
	{
		uint16_t    sound1_nb;
		uint16_t    sound2_nb;
		uint16_t    sound3_nb;
		uint16_t    sound4_nb;
		uint16_t    sound5_nb;
		uint8_t     sound3_cmd;
		uint8_t     sound2_cmd;
		uint8_t     sound4_cmd;
		uint8_t     sound1_cmd;
		uint8_t     sound5_cmd;
	}Cust;
} PROCBUFFER_OUT;

typedef union												//---- input buffer ----
{
	uint8_t  Byte [TOT_BYTE_NUM_ROUND_IN];
	struct
	{
		uint8_t     sound1_status;
		uint8_t     sound2_status;
		uint8_t     sound3_status;
		uint8_t     sound4_status;
		uint8_t     sound5_status;
	}Cust;
} PROCBUFFER_IN;

class EtherBerry 
{
  public:
    EtherBerry();                              
    unsigned char MainTask();              
    bool Init();                            
    PROCBUFFER_OUT BufferOut;                  
    PROCBUFFER_IN BufferIn;                    
   private:

    void          Write_Reg  (unsigned short Address, unsigned long DataOut);
    unsigned long Read_Reg    (unsigned short Address, unsigned char Len);
    void          Write_Reg_Wait (unsigned short Address, unsigned long  DataOut);
    unsigned long Read_Reg_Wait  (unsigned short Address, unsigned char Len); 
    void          SPIReadProcRamFifo();    
    void          SPIWriteProcRamFifo();   

 // standard SPI chip select management 

      #define SCS_Low_macro     bcm2835_gpio_write(PIN, LOW);
      #define SCS_High_macro    bcm2835_gpio_write(PIN, HIGH);
   




// standard SPI transfert 


      void SPI_Write(unsigned char Data);
      unsigned char SPI_Read(unsigned char Data);

 


};
#endif

