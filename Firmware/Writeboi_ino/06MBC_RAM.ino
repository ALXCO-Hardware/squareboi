unsigned long MBC1SetRAMBank(unsigned long address){  
  //Sets the RAM bank to the correct one for a given address
  //Also returns a corrected address, offset to hit the RAM address space on the appropriate bank
  //If knowing the current bank is needed, it's possible to read GLB_MBC1RAMBank
  //But absolutely never write to it outside this function, except at startup
  //This will mess up the current ROM bank, and mark it as invalid.
  
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  unsigned long newbank = address>>13; //Divide by 8K (8192, or 2^13) to figure out the bank we're trying to access
  if ((newbank != GLB_MBCRAMBank) or not GLB_MBCRAMBankValid){ //Change current bank if needed
    setMBC1BankRegister(2,newbank);
    GLB_MBCRAMBank = newbank;
    GLB_MBCRAMBankValid = true;
    GLB_MBCROMBankValid = false;
  }
  
  unsigned long newaddress = (address % 0x2000UL); //Wrap address around 8Kbyte banks
  newaddress = newaddress + 0xA000UL; //Add the correct offset so we actually access the RAM range (A000-BFFF)

  return newaddress;
  
}

unsigned long MBC5SetRAMBank(unsigned long address){  
  //Sets the RAM bank to the correct one for a given address
  //Also returns a corrected address, offset to hit the RAM address space on the appropriate bank
  //If knowing the current bank is needed, it's possible to read GLB_MBC1RAMBank
  //But absolutely never write to it outside this function, except at startup
  //This will mess up the current ROM bank, and mark it as invalid.
  
  //THIS WILL LEAVE THE DATA PINS AS INPUTS
  //MAKE SURE TO SET AS OUTPUTS (if necessary) AFTER USING
  
  unsigned long newbank = address>>13; //Divide by 8K (8192, or 2^13) to figure out the bank we're trying to access
  if ((newbank != GLB_MBCRAMBank) or not GLB_MBCRAMBankValid){ //Change current bank if needed
    setMBC5BankRegister(3,newbank);
    GLB_MBCRAMBank = newbank;
    GLB_MBCRAMBankValid = true;
    GLB_MBCROMBankValid = false;
  }
  
  unsigned long newaddress = (address % 0x2000UL); //Wrap address around 8Kbyte banks
  newaddress = newaddress + 0xA000UL; //Add the correct offset so we actually access the RAM range (A000-BFFF)

  return newaddress;
  
}



byte MBC1ReadRAM(unsigned long address){
  //This function assumes RAM has been previously enabled, and that we are in memory access mode 1!

  //Write to address lines
  unsigned long newaddress = MBC1SetRAMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections

  //Set chip into read mode  
  PM_CRT_RD_N_LOW();
  PM_CRT_CS_N_LOW();

  //Read off bits:
  byte result = getData();

  //Turn chip off
  PM_CRT_RD_N_HIGH();
  PM_CRT_CS_N_HIGH();
  
  return result;

}


byte MBC5ReadRAM(unsigned long address){
  //This function assumes RAM has been previously enabled!

  //Write to address lines
  unsigned long newaddress = MBC5SetRAMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections

  //Set chip into read mode  
  PM_CRT_RD_N_LOW();
  PM_CRT_CS_N_LOW();

  //Read off bits:
  byte result = getData();

  //Turn chip off
  PM_CRT_RD_N_HIGH();
  PM_CRT_CS_N_HIGH();
  
  return result;

}

byte MBC1WriteRAM(unsigned long address, byte data){
  //This function assumes RAM has been previously enabled, and that we are in memory access mode 1!

  //Write to address lines
  unsigned long newaddress = MBC1SetRAMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections 
  setDataPinMode(OUTPUT);
  setData(data);

  
  PM_CRT_CS_N_LOW();//Turn chip on
  PM_CRT_WR_N_LOW();//Set chip into write mode  
  
  PM_CRT_WR_N_HIGH(); //Clock in the data
  
  setDataPinMode(INPUT); //Set pins back to input

  PM_CRT_WR_N_LOW(); //Since we're already at the correct address, do a manual read
  byte readback = getData();
  PM_CRT_WR_N_HIGH(); 
  
  PM_CRT_CS_N_HIGH(); //Turn chip off
  
  if (data == readback){
    return 0;
  }
  return 1;

}


byte MBC5WriteRAM(unsigned long address, byte data){
  //This function assumes RAM has been previously enabled, and that we are in memory access mode 1!

  //Write to address lines
  unsigned long newaddress = MBC5SetRAMBank(address);
  setAddress(newaddress); //Once we're in the right bank, set the appropriate address, with corrections 
  setDataPinMode(OUTPUT);
  setData(data);

  PM_CRT_CS_N_LOW();//Turn chip on
  PM_CRT_WR_N_LOW();//Set chip into write mode  
  
  PM_CRT_WR_N_HIGH(); //Clock in the data
  
  setDataPinMode(INPUT); //Set pins back to input

  PM_CRT_WR_N_LOW(); //Since we're already at the correct address, do a manual read
  byte readback = getData();
  PM_CRT_WR_N_HIGH(); 
  
  PM_CRT_CS_N_HIGH(); //Turn chip off
  
  if (data == readback){
    return 0;
  }
  return 1;

}
