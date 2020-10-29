#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthreadUtils.h>
#include <Pipes.h>
#include <pipeHandler.h>
#include <stdbool.h>

//typedef bool uint1_t;
//registers

#define blocksize 0x04
#define blockcount 0x06
#define argument 0x08
#define transfer 0x0c
#define command 0x0e
#define resp0 0x10
#define resp2 0x14
#define resp4 0x18
#define resp6 0x1c
#define bufferdata 0x20
#define present 0x24
#define hostcontrol 0x28
#define powercontrol 0x29
#define blockgapcontrol 0x2A
#define wakeupcontrol 0x2B
#define clockcontrol 0x2C
#define timeoutcontrol 0x2E
#define swreset 0x2F
#define nintrstatus 0x30
#define eintrstatus 0x32
#define nintrstatusen 0x34
#define eintrstatusen 0x36
#define nintrsignalen 0x38
#define eintrsignalen 0x3A
#define autocmderror 0x3C
#define hostcontrol2 0x3E
#define capa 0x40
#define maxIcap 0x48
#define HCversion 0xFE


#define SD_Base 0x00//SD base address
  
long int lockbit=0;
long int r/w = 0;
long int bytemask;
long int PhyAdd;
int data;

void SendRequestToSDHC()
{
	/*Bit 73: lock bit
          Bit 72: read/write-bar
          Bits 71-68: Byte-mask
	  Bits 67-32: Physical address
          Bits 31- 0: Write-data*/
	uint64_t write_data0;
	uint16_t write_data1;
	
	write_data0 = (lockbit<<63)|(r/w<<62)|(bytemask<<58)|(PhyAdd<<22)|(data>>10);
	write_data1 = (data<<6);

	write_uint64 ("in_data_0",write_data0);
	write_uint16 ("in_data_1",write_data1);
}


DEFINE_THREAD(SendRequestToSDHC);

void GetResponseFromSDHC()
{
	
	//int response_pipe_read_data[read_data_length];
	/*Bits 32: Error-bit
	  Bits 31-0: Read-Data*/
	uint64_t read_data;
	read_uint64("out_data",read_data);


}
DEFINE_THREAD(GetResponseFromSDHC);


void Initialization()
{
 	SendCMD(0);
        SendCMD(8);
        SendCMD(55);
        SendACMD(41);//with S18R(bit 24)=0
        SendCMD(2);
        SendCMD(3);

}

void UHSInitialisation()
{
	SendCMD(0);
	SendCMD(8);
	SendCMD(55);
	SendACMD(41);//HCS(bit 30) and S18R(bit 24)=1
	SendCMD(11);
	SendCMD(2);
	SendCMD(3);
	SendCMD(7);
	SendCMD(42);
	SendCMD(55);
	SendACMD(6);
	SendCMD(19);
}
void Blockwrite()
//CMD7
//ACMD6
//CMD6
//CMD19
//CMD24
//CMD15
{
	SendCMD(7);
	SendCMD(55);
	SendACMD(6);
	SendCMD(6);
	SendCMD(19);
	SendCMD(24);
	SendCMD(15);
}

void BlockRead()
{
	SendCMD(7);
        SendCMD(55);
        SendACMD(6);
        SendCMD(6);
	SendCMD(19);
        SendCMD(17);
        SendCMD(15);	
}

void SendCMD(int n)
{
	switch(n)
	{
		case 0: PhyAdd =argument;
			data = 0;
			SendRequestToSDHC();
			PhyAdd = command;
			data = GenerateCMD(n);
			SendRequestToSDHC();
			GetResponseFromSDHC();
			break;

		case 2: PhyAdd =argument;
                        data = 0;
                        SendRequestToSDHC();
                        PhyAdd = command;
                        data = GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
			break;

		case 3: PhyAdd =argument;
                        data = 0;
                        SendRequestToSDHC();
                        PhyAdd = command;
                        data = GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
			break;

		case 6:	PhyAdd=argument;
                        data =;
                        SendRequestToSDHC();
                        PhyAdd=command;
                        data=GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
                        break;

		case 7: PhyAdd=argument;
                        data=0;
                        SendRequestToSDHC();
                        PhyAdd=command;
                        data=GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
                        break;
		
		case 11:PhyAdd=argument;
			data=0;
			SendRequestToSDHC();
			PhyAdd=command;
			data=GenerateCMD(n);
			SendRequestToSDHC();
			GetResponseFromSDHC();
			break;

		case 19:PhyAdd=argument;
			data=0;
			SendRequestToSDHC();
			PhyAdd=command;
			data=GenerateCMD(n);
			SendRequestToSDHC();
			GetResponseFromSDHC();
			break;

		case 15:PhyAdd=argument;
                        data=0;
                        SendRequestToSDHC();
                        PhyAdd=command;
                        data=GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
                        break;

		case 17:PhyAdd=argument;
                        data=;
                        SendRequestToSDHC();
                        PhyAdd=command;
                        data=GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
                        break;

		case 24:PhyAdd=argument;
                        data =;
                        SendRequestToSDHC();
                        PhyAdd=command;
                        data=GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
                        break;

		case 8: PhyAdd = argument;
                        data = 0x1AA;
                        SendRequestToSDHC();
                        PhyAdd = command;
                        data = GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
			break;

		case 55:PhyAdd = argument;
                        data = 0;
                        SendRequestToSDHC();
                        PhyAdd = command;
                        data = GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
			break;
	}

void sendACMD(int n)
{
	switch(n)
	{
		case 6: PhyAdd=argument;
			data =0x2;
			SendRequestToSDHC();
			PhyAdd=command;
			data=GenerateCMD(n);
			SendRequestToSDHC();
			GetResponseFromSDHC();
			break;
		case 41:PhyAdd = argument;
                        data = 0;
                        SendRequestToSDHC();
                        PhyAdd = command;
                        data = GenerateCMD(n);
                        SendRequestToSDHC();
                        GetResponseFromSDHC();
			break;
	}
}


int GenerateCMD(int n)
{
	int cmd;
	if( n== (0||2||9||10))//R2
	{
		cmd = (n<<8)|(0<<6)|(0<<5)|(0<<4)|(1<<3)|(0<<2)|1;
		/*(13:08)Index 
		  (7:6)cmd Type 
		  5 Data present 
		  4 Command check enable 
		  3 crc check enable 
		  (1:0) Response type*/

	}
	else if (n == 41) //R3
	{
		cmd = (n<<8)|(0<<6)|(0<<5)|(0<<4)|(0<<3)|(0<<2)|2;
	}
	else if( n== (55||3||8))
	{
		cmd = (n<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<3)|(0<<2)|2;
	}
	else
	{
		cmd = (n<<8)|(0<<6)|(0<<5)|(1<<4)|(1<<3)|(0<<2)|3;
	}
	return cmd;

}


int main()
{

	//Test initialization-T1
		// CMD0 Arguement 0x0000
		// CMD0 Command  0x001A
		// CMD8 Arguement 
		// CMD8 Command
		// CMD55 Arguement
		// CMD55 Command
		// ACMD41 Arguement
		// ACMD41 Command
		// CMD2 Arguement
		// CMD2 Command
		// CMD3 Arguement
		// CMD3 Command	
	//Test single block write-T2
	//Test single block read-T3
	//Test multiple block write-T4
	//Test multiple block read-T5
	
	while(1)
	{
		Initialization();
		Blockwrite();
		BlockRead();

	}

	return 0;
}
