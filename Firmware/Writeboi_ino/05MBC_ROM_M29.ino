/*
 * Contains functions for interfacing with flash chips from the M29F200/400/800/160 family
 * 
 * 
 * 
 */




bool MBC1M29ReadReset(){
  //Clears errors from the status register of the IC, returns it to a known "read" state
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.

  //manually go to bank 0
  setMBC1ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number, reset the thingo
  setAddress(0x0);   
  setData(0xF0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  delayMicroseconds(20); //Wait for write cycle to finish

  //Set data pins back to input
  setDataPinMode(INPUT);

  return 0;
}

bool MBC5M29ReadReset(){
  //Clears errors from the status register of the IC, returns it to a known "read" state
  
  //manually go to bank 0
  setMBC5ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number, reset the thingo
  setAddress(0x0);   
  setData(0xF0); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Set data pins back to input
  setDataPinMode(INPUT);

  return 0;
}


bool MBC1EraseM29(){
  //Will print return code "2" to the serial console every second while erasing
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.

  //manually go to bank 0
  setMBC1ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Second magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Third magic number
  setAddress(0xAAA);   
  setData(0x80); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fourth magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fifth magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Sixth magic number
  setAddress(0xAAA);   
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
      MBC1M29ReadReset(); 
      return 1; //Clear the error, but report it to the user.
     }
  } //End of erase checking loop

  return 0;
}

bool MBC5EraseM29(){
  //Will print return code "2" to the serial console every second while erasing

  //manually go to bank 0
  setMBC5ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Second magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Third magic number
  setAddress(0xAAA);   
  setData(0x80); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fourth magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Fifth magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();  

  //Sixth magic number
  setAddress(0xAAA);   
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
      MBC5M29ReadReset(); 
      return 1; //Clear the error, but report it to the user.
     }
  } //End of erase checking loop

  return 0;
}




bool MBC1WriteM29(unsigned long address, byte data){
  //This function assumes we are in MBC memory access mode 1, ie that the upper bank register is always mapped to memory. Make sure to do so after a reset.

  //manually go to bank 0
  setMBC1ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  setAddress(0xAAA);   
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
        MBC1M29ReadReset(); 
        return 1; //Clear the error, but report it to the user.
     }
  }
}


bool MBC5WriteM29(unsigned long address, byte data){

  //manually go to bank 0
  setMBC5ROMBank(0);
  //Since we're using only bank 0 for the commands, we don't need to apply address corrections
  
  //Set data lines to output
  setDataPinMode(OUTPUT);

  //Pushing commands to the cart 

  //First magic number
  setAddress(0xAAA);   
  setData(0xAA); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Second magic number
  setAddress(0x555);   
  setData(0x55); 
  PM_CRT_PG_N_LOW();
  PM_CRT_PG_N_HIGH();

  //Third magic number
  setAddress(0xAAA);   
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
        MBC5M29ReadReset(); 
        return 1; //Clear the error, but report it to the user.
     }
  }


}
