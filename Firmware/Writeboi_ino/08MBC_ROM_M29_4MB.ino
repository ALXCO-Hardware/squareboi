/*
 * Functions in this file specifically target the second ROM IC in the bus, when running a 4MB board
 * with two M29F160 chips.
 * 
 * Note that they can only be used in MBC5 mode, since MBC1 cannot hold an address past 2MB.
 * 
 * 
 * 
 */



bool MBC5M29ReadResetChip2(){
  

  unsigned long newaddress = 0;
  //manually go to bank 128 (Start of second chip)
  newaddress=setMBC5ROMBank(2097152UL);
  //Since we're using only banks 0 and 1 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number, reset the thingo
  setAddress(newaddress);   
  setData(0xF0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  


  delayMicroseconds(20); //Wait for write cycle to finish

  //Set data pins back to input
  setDataPinMode(INPUT);



  return 0;
}




bool MBC5EraseM29Chip2(){
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.
  //All command addresses will be altered to target the second chip by setting bit 21
  //This is done by adding them with 2097152 (1 followed by 21 zeros)

  unsigned long newaddress = 0;
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Second magic number
  newaddress = setMBC5ROMBank(0x555UL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Third magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0x80); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fourth magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fifth magic number
  newaddress = setMBC5ROMBank(0x555UL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Sixth magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0x10); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //From this point, erase cycle may take 25-120s to complete.

  //Set data pins back to input
  setDataPinMode(INPUT);

  byte readback = 0;

  while (true){
    //Manually doing the READ parts of the operation ourselves, since the address doesn't actually matter
    //Set chip into read mode  
    PM_CRT_RD_N_LOW();
    //Read off bits:
    readback = getData();
    //Turn chip off
    PM_CRT_RD_N_HIGH();
    
    if (readback == 0xFF){return 0;} //Erase successful
    else if (readback == 0x18 or readback == 0x5C){
        Serial.println(2,HEX); //Let user know we're still working
        delay(1000); //Wait a second before checking again
     }
     else {
      MBC5M29ReadResetChip2(); 
      return 1; //Clear the error, but report it to the user.
     }
  } //End of erase checking loop

  return 0;
}



bool MBC5WriteM29Chip2(unsigned long address, byte data){
  //All command addresses will be altered to target the second chip by setting bit 21
  //This is done by OR'ing them with 2097152 (1 followed by 21 zeros)
  unsigned long newaddress = 0;
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  newaddress = setMBC5ROMBank(0x555UL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  newaddress = setMBC5ROMBank(0xAAAUL+2097152UL);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
  setAddress(newaddress);   
  setData(0xA0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();
  
  //Go to the right bank and get the corrected address:
  newaddress = setMBC5ROMBank(address);
  setDataPinMode(OUTPUT); //Must do this whenever we change bank registers
    
  //Actually write the data
  setAddress(newaddress);   
  setData(data); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();
  
  //Set data pins back to input
  setDataPinMode(INPUT);

  //Check if write cycle was successful:
  byte readback = 0;
  bool datab7 = 0;
  bool readb7 = 0;
  bool readb5 = 0;
  
  while (true){
    //Manually doing the READ parts of the operation ourselves, since we're already at the correct adress for it
    //Set chip into read mode  
    PM_CRT_RD_N_LOW();
    //Read off bits:
    readback = getData();
    //Turn chip off
    PM_CRT_RD_N_HIGH();
    datab7 = (data & 1U<<7)>>7;
    readb7 = (readback & 1U<<7)>>7;
    readb5 = (readback & 1U<<5)>>5;
    
    if (datab7 == readb7){return 0;}
    else if (readb5 == true){
        MBC5M29ReadResetChip2(); 
        return 1; //Clear the error, but report it to the user.
     }
  }
}
