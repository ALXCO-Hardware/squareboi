unsigned long setMBC1ROMBank(unsigned long address){  
  //Sets the ROM bank to the correct one for a given address
  //Also returns a corrected address, that forces banking, to be used for subsequent operations. This must be used when accessing banks other than 0 and 1.
  //If knowing the current bank is needed, it's possible to read GLB_MBCROMBank
  //But absolutely never write to it outside this function, except at startup
  //This will mess up the current RAM bank, and mark it as invalid.
  
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  unsigned long newbank = address>>14; //Divide by 16K (16384, or 2^14) to figure out the bank we're trying to access
  if ((newbank != GLB_MBCROMBank) or not GLB_MBCROMBankValid){ //Change current bank if needed
    setMBC1BankRegister(1,newbank);  //Lower 5 bits
    setMBC1BankRegister(2,newbank>>5); //Upper 2 bits of the 7-bit address 
    GLB_MBCROMBank = newbank;
    GLB_MBCROMBankValid = true;
    GLB_MBCRAMBankValid = false;
  }
  else{setDataPinMode(INPUT);}
  unsigned long newaddress = address;
  //Since we're writing all the way to A15, we need to manually blank out A15 so that we actually read from the ROM.
  newaddress = newaddress & ~(1UL<<15); //Clears bit 15
  //Manually make sure bit 14 is set so we actually use banking, unless we're at the banks that have the MBC1 bug (0x00, 0x20, 0x40, 0x60)
  if (newbank%0x20 != 0) {newaddress = newaddress | (1UL<<14);} //We're checking for 00 20 40 60 by seeing if it's a multiple of 0x20

  return newaddress;
  
}

unsigned long setMBC5ROMBank(unsigned long address){  
  //Sets the ROM bank to the correct one for a given address
  //Also returns a corrected address, that forces banking, to be used for subsequent operations. This must be used when accessing banks other than 0 and 1.
  //If knowing the current bank is needed, it's possible to read GLB_MBCROMBank
  //But absolutely never write to it outside this function, except at startup
  //This will mess up the current RAM bank, and mark it as invalid.
  
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  unsigned long newbank = address>>14; //Divide by 16K (16384, or 2^14) to figure out the bank we're trying to access
  if ((newbank != GLB_MBCROMBank) or not GLB_MBCROMBankValid){ //Change current bank if needed
    setMBC5BankRegister(1,newbank);  //Lower 8 bits
    setMBC5BankRegister(2,newbank>>8); //Upper bit of 9-bit bank address -- if using preproduction squareboi, comment out this line 
    GLB_MBCROMBank = newbank;
    GLB_MBCROMBankValid = true;
    GLB_MBCRAMBankValid = false;
  }
  else{setDataPinMode(INPUT);}
  unsigned long newaddress = address;
  //Since we're writing all the way to A15, we need to manually blank out A15 so that we actually read from the ROM.
  newaddress = newaddress & ~(1UL<<15); //Clears bit 15
  //Manually make sure bit 14 is set so we actually use banking, unless we're in bank 0
  if (newbank != 0) {newaddress = newaddress | (1UL<<14);}

  return newaddress;
  
}



byte MBC1Read(unsigned long address){
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.

  //Write to address lines
  unsigned long newaddress = setMBC1ROMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections

  //Set chip into read mode  
  PM_CRT_RD_N_LOW();

  //Read off bits:
  byte result = getData();

  //Turn chip off
  PM_CRT_RD_N_HIGH();
  
  return result;

}

byte MBC5Read(unsigned long address){

  //Write to address lines
  unsigned long newaddress = setMBC5ROMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections
  newaddress = setMBC5ROMBank(address);
  
  //Set chip into read mode  
  PM_CRT_RD_N_LOW();

  //Read off bits:
  byte result = getData();

  //Turn chip off
  PM_CRT_RD_N_HIGH();
  
  return result;

}
