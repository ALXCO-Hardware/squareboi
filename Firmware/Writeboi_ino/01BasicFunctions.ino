////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//WARNING! Some of the data/address/direction setting functions use direct port manipulation
//And therefore ignore what we set up with the defines
//If you ever change the board layout, or the processor you're using, you'll have to rectify that



void setAddress(unsigned long address){
  //Does not check pin mode, remember to set manually
  //Only writes up to A15, for speed

  //Write to address lines
 
  //PA receives the first 8 bits of the address
  PORTA = address & 0b0000000011111111;

  //PC receives the next 8 bits, inverted
  byte PORTCtemp = address>>8;
  PORTC = (GLB_reverselookup[PORTCtemp&0b1111] << 4) | GLB_reverselookup[PORTCtemp>>4];
  
}

void setAddressFull(unsigned long address){
  //Does not check pin mode, remember to set manually
  //Writes all the way to A18, to be used with the DIP socket.

  //Write to address lines
  
  //PA receives the first 8 bits of the address
  PORTA = address & 0b0000000011111111;

  //PC receives the next 8 bits, inverted
  byte PORTCtemp = address>>8;
  PORTC = (GLB_reverselookup[PORTCtemp&0b1111] << 4) | GLB_reverselookup[PORTCtemp>>4];

  
  //A16:PIN8:PH5
  //A17:PIN9:PH6
  //A18:PIN7:PH4

  //Isolate the relevant bits
  bool add16 = address & (1UL << 16);
  bool add17 = address & (1UL << 17);
  bool add18 = address & (1UL << 18);
  

  byte PORTHtemp = PORTH & 0b10001111; // Zero out bits 6,5,4
  byte combinedaddress = (add17<<6) + (add16<<5) + (add18<<4); //Create a byte that's 0 A17 A16 A18 0000 
  PORTH = PORTHtemp | combinedaddress; //Write it in

  
}



void setData(byte data){
  //Does not check pinmode, remember to set it to OUTPUT if necessary

  //PORTL receives the 8 data bits, inverted
  PORTL = (GLB_reverselookup[data&0b1111] << 4) | GLB_reverselookup[data>>4];
  
}

byte getData(){
  //Dumps PINL into a variable, in reverse order.
  //Does not check pinmode, remember to make sure we're in INPUT

  return (GLB_reverselookup[ PINL & 0b1111] << 4) | GLB_reverselookup[PINL>>4];
  
}

void setDataPinMode(uint8_t mode){
  //Sets the data direction register for port L
  //0 = input
  //1 = output
  
  if (mode == OUTPUT){
    DDRL = 0b11111111;
    }
  else{
    DDRL = 0b00000000;
  }
  
}


void setMBCAddress(bool add15, bool add14, bool add13, bool add12){
  //Write to relevant address lines
  /*
  digitalWrite(GB_A15, add15); 
  digitalWrite(GB_A14, add14);
  digitalWrite(GB_A13, add13);
  digitalWrite(GB_A12, add12);
  */
  //A12:PC3 A13:PC2, A14:PC1, A15:PC0
  
  byte PORTCtemp = PORTC & 0b11110000; // Zero out bits 0,1,2,3
  byte combinedaddress = add15 + (add14<<1) + (add13<<2) + (add12<<3); //Create a byte that's 0000 A12 A13 A14 A15 
  PORTC = PORTCtemp | combinedaddress; //Write it in
  
}

void setMBCAddressShort(bool add15, bool add14, bool add13){
  //Write to relevant address lines
  /*
  digitalWrite(GB_A15, add15); 
  digitalWrite(GB_A14, add14);
  digitalWrite(GB_A13, add13);
  digitalWrite(GB_A12, add12);
  */
  //A12:PC3 A13:PC2, A14:PC1, A15:PC0
  
  byte PORTCtemp = PORTC & 0b11111000; // Zero out bits 0,1,2
  byte combinedaddress = add15 + (add14<<1) + (add13<<2); //Create a byte that's 00000 A13 A14 A15 
  PORTC = PORTCtemp | combinedaddress; //Write it in
  
}


//End of port manipulation block

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setBusy(bool busy){
  digitalWrite(LED_RY, not(busy));
  digitalWrite(LED_BY, busy);

  
}


void initializeByteArray(){
  byte deadbeef[8] = {0xD,0xE,0xA,0xD,0xB,0xE,0xE,0xF};
  byte charpointer = 0;

  for (unsigned long i = 0; i<ARRSIZE; i++){
    GLB_bytearray[i] = deadbeef[charpointer];
    charpointer++;
    if (charpointer>7) {charpointer = 0;}
    }
}


void resetCartridge(){
  //Holds RESET_N low for 1 second, sets all MBC banks back to 0 and marks them as non-valid, forcing a recalculation next time they are accessed
  //Do note: This also allows the CPLD to change between MBC1 and MBC5 mode
  pinMode(CRT_RST_N, OUTPUT);
  GLB_MBCROMBank = 0;
  GLB_MBCRAMBank = 0;
  GLB_MBCROMBankValid = false;
  GLB_MBCRAMBankValid = false;
  
  delay(1000);
  
  pinMode(CRT_RST_N, INPUT);
}
