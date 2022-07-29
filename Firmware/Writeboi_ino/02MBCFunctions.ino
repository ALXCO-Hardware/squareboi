
//MBC1 register addresses
//written as A15-A14-A13-A12
//Note that A12 does not matter for MBC1, so it will always be X
//So we use AddressShort that ends at A13

//000X - RAM gate register - set to 0xA to enable RAM
//001X - ROM register, lower 5 bits
//010X - ROM/RAM register, upper 2 bits
//011X - MODE register

void setMBC1BankRegister(byte bank, byte contents){
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  setDataPinMode(OUTPUT);
  setData(contents);
  
  if (bank==0){ setMBCAddress(0,0,0,0);} //RAM gate register, set to 0xA to enable RAM
  else if (bank==1){ setMBCAddress(0,0,1,0);} //Lower 5 bits of ROM
  else if (bank==2) {setMBCAddress(0,1,0,0);} //Upper 2 bits of ROM/RAM
  else {setMBCAddress(0,1,1,0);} //MODE register
  
  PM_CRT_WR_N_LOW();
  PM_CRT_WR_N_HIGH(); //Clock in the data, turn off writes

  setDataPinMode(INPUT); //Make sure we're in a safe state as the function ends

}


//MBC5 register addresses
//written as A15-A14-A13-A12

//000X - RAM gate register - set to 0xA to enable RAM
//0010 - ROM register, lower 8 bits
//0011 - ROM register, upper bit
//010X - RAM register

void setMBC5BankRegister(byte bank, byte contents){
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  setDataPinMode(OUTPUT);
  setData(contents);
  
  if (bank==0){ setMBCAddress(0,0,0,0);} //RAM gate register, set to 0xA to enable RAM
  else if (bank==1){ setMBCAddress(0,0,1,0);} //Lower 8 bits of ROM
  else if (bank==2) {setMBCAddress(0,0,1,1);} //Upper bit of ROM
  else {setMBCAddress(0,1,0,0);} //4 bits of RAM
  
  PM_CRT_WR_N_LOW();
  PM_CRT_WR_N_HIGH(); //Clock in the data, turn off writes

  setDataPinMode(INPUT); //Make sure we're in a safe state as the function ends

}
