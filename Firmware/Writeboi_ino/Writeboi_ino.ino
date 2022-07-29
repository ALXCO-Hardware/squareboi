//Writeboi firmware
//V1.00
//For use with Writeboi board V2.01

//ALXCO 2022


//Global build ID:
byte GLB_buildID = 0x01;


//PINOUTS!

#define GB_A0 22
#define GB_A1 23
#define GB_A2 24
#define GB_A3 25
#define GB_A4 26
#define GB_A5 27
#define GB_A6 28
#define GB_A7 29
#define GB_A8 30
#define GB_A9 31
#define GB_A10 32
#define GB_A11 33
#define GB_A12 34
#define GB_A13 35
#define GB_A14 36
#define GB_A15 37

#define DIP_A16 8
#define DIP_A17 9
#define DIP_A18 7

#define GB_D0 42
#define GB_D1 43
#define GB_D2 44
#define GB_D3 45
#define GB_D4 46
#define GB_D5 47
#define GB_D6 48
#define GB_D7 49

#define DIP_CE_N 12
#define DIP_OE_N 11
#define DIP_WE_N 10

#define CRT_CS_N 53
#define CRT_RD_N 52
#define CRT_WR_N A15
#define CRT_PG_N A13
#define CRT_RST_N 50
#define CRT_CLK A14

#define LED_BY 19
#define LED_RY 18

//Compile-time definitions!

#define ARRSIZE 1024

//Globals!
unsigned long GLB_MBCROMBank = 0;
bool GLB_MBCROMBankValid = false;
unsigned long GLB_MBCRAMBank = 0;
bool GLB_MBCRAMBankValid = false;



byte GLB_bytearray[ARRSIZE] = {};

//Lookup table for inverting a byte
//Use with the following code to reverse a variable X:
//X = (GLB_reverselookup[ X & 0b1111] << 4) | GLB_reverselookup[X>>4];
byte GLB_reverselookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf, };


//Port manip pin-setting macros!


//CRT_CS_N:PIN53:PB0
#define PM_CRT_CS_N_HIGH() PORTB=PORTB|0b00000001
#define PM_CRT_CS_N_LOW()  PORTB=PORTB&0b11111110

//CRT_RD_N:PIN52:PB1

#define PM_CRT_RD_N_HIGH() PORTB=PORTB|0b00000010
#define PM_CRT_RD_N_LOW()  PORTB=PORTB&0b11111101

//CRT_WR_N:PINA15:PK7
#define PM_CRT_WR_N_HIGH() PORTK=PORTK|0b10000000
#define PM_CRT_WR_N_LOW()  PORTK=PORTK&0b01111111


//CRT_PG_N:PINA13:PK5
#define PM_CRT_PG_N_HIGH() PORTK=PORTK|0b00100000
#define PM_CRT_PG_N_LOW()  PORTK=PORTK&0b11011111



//DIP_CE_N:PIN12:PB6
#define PM_DIP_CE_N_HIGH() PORTB=PORTB|0b01000000
#define PM_DIP_CE_N_LOW()  PORTB=PORTB&0b10111111

//DIP_OE_N:PIN11:PB5
#define PM_DIP_OE_N_HIGH() PORTB=PORTB|0b00100000
#define PM_DIP_OE_N_LOW()  PORTB=PORTB&0b11011111

//DIP_WE_N:PIN10:PB4
#define PM_DIP_WE_N_HIGH() PORTB=PORTB|0b00010000
#define PM_DIP_WE_N_LOW()  PORTB=PORTB&0b11101111





void setup() {
  // Set all control lines to an inactive state
  digitalWrite(DIP_CE_N, HIGH);
  digitalWrite(DIP_OE_N, HIGH);
  digitalWrite(DIP_WE_N, HIGH);
  pinMode(DIP_CE_N, OUTPUT);
  pinMode(DIP_OE_N, OUTPUT);
  pinMode(DIP_WE_N, OUTPUT);

  digitalWrite(CRT_CS_N, HIGH);
  digitalWrite(CRT_RD_N, HIGH);
  digitalWrite(CRT_WR_N, HIGH);
  digitalWrite(CRT_PG_N, HIGH);
  digitalWrite(CRT_CLK, LOW);

  pinMode(CRT_CS_N, OUTPUT);
  pinMode(CRT_RD_N, OUTPUT);
  pinMode(CRT_WR_N, OUTPUT);
  pinMode(CRT_PG_N, OUTPUT);
  pinMode(CRT_CLK, OUTPUT);

  setDataPinMode(INPUT);


  pinMode(GB_A0, OUTPUT);
  pinMode(GB_A1, OUTPUT);
  pinMode(GB_A2, OUTPUT);
  pinMode(GB_A3, OUTPUT);
  pinMode(GB_A4, OUTPUT);
  pinMode(GB_A5, OUTPUT);
  pinMode(GB_A6, OUTPUT);
  pinMode(GB_A7, OUTPUT);
  pinMode(GB_A8, OUTPUT);
  pinMode(GB_A9, OUTPUT);
  pinMode(GB_A10, OUTPUT);
  pinMode(GB_A11, OUTPUT);
  pinMode(GB_A12, OUTPUT);
  pinMode(GB_A13, OUTPUT);
  pinMode(GB_A14, OUTPUT);
  pinMode(GB_A15, OUTPUT);
  
  pinMode(DIP_A16, OUTPUT);
  pinMode(DIP_A17, OUTPUT);
  pinMode(DIP_A18, OUTPUT);

  //LED test, reset cartridge
  digitalWrite(LED_RY, HIGH);
  digitalWrite(LED_BY, HIGH);
  pinMode(LED_BY, OUTPUT);
  pinMode(LED_RY, OUTPUT);
  digitalWrite(CRT_RST_N, LOW);
  pinMode(CRT_RST_N, OUTPUT);


  delay(1500);

  digitalWrite(LED_RY, LOW);
  digitalWrite(LED_BY, LOW);
  pinMode(CRT_RST_N, INPUT);

  initializeByteArray();
  
  delay(50);

  GLB_MBCROMBank = 0;
  GLB_MBCRAMBank = 0;
  GLB_MBCROMBankValid = false;
  GLB_MBCRAMBankValid = false;  

  delay(500);


  
  Serial.begin(115200);
  setBusy(false);





}

void loop() {
  // put your main code here, to run repeatedly:
  serialManager();
}
