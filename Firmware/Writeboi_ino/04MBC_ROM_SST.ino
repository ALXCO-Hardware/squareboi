/*
 * Contains functions for interfacing with flash chips from the SST39SF010/20/40 family.
 * These ICs have very short write/erase cycle times, so instead of checking if the operations are complete,
 * we just wait for a set amount of time until they are guaranteed to have ended.
 * 
 * 
 * 
 * 
 * 
 */




bool MBC1WriteSST(unsigned long address, byte data){
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.

  //manually go to bank 0
  setMBC1ROMBank(0);
  //Since we're on MBC1 and using only banks 0 and 1 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0x5555);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  setAddress(0x2AAA);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  setAddress(0x5555);   
  setData(0xA0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Go to the right bank and get the corrected address:
  unsigned long newaddress = setMBC1ROMBank(address);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
    
  //Actually write the data
  setAddress(newaddress);   
  setData(data); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();
  
  delayMicroseconds(20); //Wait for write cycle to finish

  //Set data pins back to input
  setDataPinMode(INPUT);

  byte readback = 0;
  //Manually doing the READ parts of the operation ourselves, since we're already at the correct adress for it
  //Set chip into read mode  
  PM_CRT_RD_N_LOW();
  //Read off bits:
  readback = getData();
  //Turn chip off
  PM_CRT_RD_N_HIGH();

  if (data == readback){
    return 0;
  }
  return 1;
}

bool MBC5WriteSST(unsigned long address, byte data){

  //Since we're on MBC5 and the addresses go past the end of bank 0, we must use address corrections for each command we push.

  //Pushing commands to the cart 
  unsigned long commandaddress;
  
  //First magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  commandaddress = setMBC5ROMBank(0x2AAA);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);    
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress); 
  setData(0xA0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Go to the right bank and get the corrected address:
  unsigned long newaddress = setMBC5ROMBank(address);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
    
  //Actually write the data
  setAddress(newaddress);   
  setData(data); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();
  
  delayMicroseconds(20); //Wait for write cycle to finish

  //Set data pins back to input
  setDataPinMode(INPUT);

  byte readback = 0;
  //Manually doing the READ parts of the operation ourselves, since we're already at the correct adress for it
  //Set chip into read mode  
  PM_CRT_RD_N_LOW();
  //Read off bits:
  readback = getData();
  //Turn chip off
  PM_CRT_RD_N_HIGH();

  if (data == readback){
    return 0;
  }
  return 1;
}

unsigned int MBC1EraseSST(){
  
  //manually go to bank 0
  setMBC1ROMBank(0);
  //Since we're on MBC1 and using only banks 0 and 1 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0x5555);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  setAddress(0x2AAA);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  setAddress(0x5555);   
  setData(0x80); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Fourth magic number
  setAddress(0x5555);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Fifth magic number
  setAddress(0x2AAA);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Sixth magic number
  setAddress(0x5555);   
  setData(0x10); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  delay(1000); //Wait for erase cycle to finish. We can do this because it's guaranteed to be short on the SST.

  //Set data pins back to input
  setDataPinMode(INPUT);

  return 0;
}

unsigned int MBC5EraseSST(){
  
  //Since we're on MBC5 and the addresses go past the end of bank 0, we must use address corrections for each command we push.
  

  //Pushing commands to the cart 
  unsigned long commandaddress;
  
  //First magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  commandaddress = setMBC5ROMBank(0x2AAA);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);    
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);  
  setData(0x80); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Fourth magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Fifth magic number
  commandaddress = setMBC5ROMBank(0x2AAA);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Sixth magic number
  commandaddress = setMBC5ROMBank(0x5555);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(commandaddress);   
  setData(0x10); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  delay(1000); //Wait for erase cycle to finish. We can do this because it's guaranteed to be short on the SST.

  //Set data pins back to input
  setDataPinMode(INPUT);

  return 0;
}
