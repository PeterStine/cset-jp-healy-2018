/*
 *  Shaun Carter    
 *  CST337
 *  11/6/18
 *  Lab 5 - SPI Interface with the 25LC256 Part 1
 */
#include <xc.h>
// PIC32MZ2048ECG144 Configuration Bit Settings
// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // System PLL Input Divider (2x Divider) 12MHz/2 = 6MHz
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_112       // System PLL Multiplier (PLL Multiply by 112) 6MHz * 112 = 672MHz
#pragma config FPLLODIV = DIV_8         // System PLL Output Clock Divider (8x Divider) 672MHz / 8 = 84MHz
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
//#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is disabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Primary Osc (HS,EC))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config POSCMOD = HS             // Primary Oscillator Configuration (HS osc mode)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

 // DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)

#define DUMMY_DATA 0xAA
#define READ_INST 0x03
#define WRITE_INST 0x02
#define WRDI_INST 0x04
#define WREN_INST 0x06
#define RDSR_INST 0x05
#define WRSR_INST 0x01


uint8_t readStatus(void)  //read status function
{
    uint8_t byte = 0;
    //1. Assert CS
    LATFCLR = 0x100; //LATF
    //2. Write a read status to SPI4BUF
    SPI4BUF = RDSR_INST;
    //3. Wait for TBE
    while(!(SPI4STAT & 0x8)) //while transmition buffer is not empty
    {
    }
    //4. Write a dummy byte to SPI4BUF
    SPI4BUF = DUMMY_DATA;
    //5. Wait for RBF
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //6. Read SPI4BUF and discard dummy data
    byte = SPI4BUF;
    
    //7. Wait for RBF
    while(!(SPI4STAT & 0x1))
    {
        
    }
    //8. Read status byte
    byte = SPI4BUF;
    //9. Negate CS
    LATFSET = 0x100;
    return byte;
}


void writeEnable(void)
{
    uint8_t byte = 0;
    //1. Assert CS
    LATFCLR = 0x100; //LATF
    //2. Write a read status to SPI4BUF
    SPI4BUF = WREN_INST;
    //3. Wait for TBE
    while(!(SPI4STAT & 0x1)) //while !rbf
    {
    }
    //4. Read a dummy byte to SPI4BUF
    byte = SPI4BUF;
    
    //5. Negate CS
    LATFSET = 0x100;
}

void writeData(uint16_t addr, uint8_t data) //write status function
{
    uint8_t byte = 0;
    //1. Assert CS
    LATFCLR = 0x100; //LATF
    //2. Write a write to SPI4BUF
    SPI4BUF = WRITE_INST; //write
    //wait for tbe
    while(!(SPI4STAT & 0x8)) //while transmission buffer is not empty
    {
    }
    //write msa
    SPI4BUF = (addr) >> 8; //write most significant address
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy a
    byte = SPI4BUF; //read first dummy
    //write lsa
    SPI4BUF = addr; //write the least significant address
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy b
    byte = SPI4BUF; //read second dummy
    //write data 1
    SPI4BUF = data;  //load the data
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy c
    byte = SPI4BUF;  //read third dummy
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy 1
    byte = SPI4BUF; //read last dummy
    //cs negate
    LATFSET = 0x100;
}

uint8_t readData(uint16_t addr)
{
    uint8_t byte = 0;
    //1. Assert CS
    LATFCLR = 0x100; //LATF
    //2. Write a read to SPI4BUF
    SPI4BUF = READ_INST;
    //wait for tbe
    while(!(SPI4STAT & 0x8)) //while transmition buffer is not empty
    {
    }
    // write msa
    SPI4BUF = (addr) >> 8; //write most significant address
    // wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    // read dummy a
    byte = SPI4BUF;  //read first dummy
    //write lsa
    SPI4BUF = addr; //write the least significant address
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy b
    byte = SPI4BUF; //read second dummy
    //write dummy1
    SPI4BUF = DUMMY_DATA;
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read dummy c
    byte = SPI4BUF; //read third dummy
    //wait for rbf
    while(!(SPI4STAT & 0x1)) //while the Receive Buffer is not full
    {
    }
    //read data...
    byte = SPI4BUF; //reads the data retrieved
    LATFSET = 0x100; //disable cs
    return byte;
}


int main()
{
    uint8_t status = 0x0;
    uint8_t data4 = 0xFA; //data
    uint8_t holder = 0;
    uint16_t addr4 = 0x43; //address test
    ANSELB = 0x0;
    //PB2DIV 84MHz SPI clock at 2MHz
    SYSKEY = 0; // Ensure lock
    SYSKEY = 0xAA996655; // Write Key 1
    SYSKEY = 0x556699AA; // Write Key 2
    PB2DIV = _PB2DIV_ON_MASK | 0 & _PB2DIV_PBDIV_MASK; // PB2CLK = 84MHz
    SYSKEY = 0; // Re lock
    //SPI4BRG = 20;  //BRG = 20 to reach 2MHz 20 + 1 = 21, 21*2 = 42
    SPI4BRG = 8;   //8 + 1 = 9, 9*2 = 18, 84/18 = 4.66666666667
    PRECON = (1 & _PRECON_PFMWS_MASK) | ((2 << _PRECON_PREFEN_POSITION) & _PRECON_PREFEN_MASK); //one wait state and prefetch on
    SDI4R = 0b1000;  //rpb3 needs tris bit set to input, but done POR
    RPF2R = 0b1000;  //SDO4
    //SS4R = 0b1011;   //rpf8 cs connected ss4 if using mssen
    LATFSET = 0x100; //driving the CS on LATF
    TRISFCLR = 0x100;  //off TRISF
    SPI4CON = 0x00000060; // CKP = 1 msten on and on = 1
    SPI4CONSET = 0x8000; //turn on spi
    //first addr
   
        status = readStatus();      //check status first
        holder = readData(addr4); //read current
        
        writeEnable();            //write enable
        status = readStatus();      //make sure wel is set
        writeData(addr4, data4);  //write
        status = readStatus();
        while(status & 0x1)  //checking if wip
        {
            status = readStatus();
        }
        //writeDisable(); // SPI4STAT
        holder = readData(addr4); //read data
    
    return 0;
}