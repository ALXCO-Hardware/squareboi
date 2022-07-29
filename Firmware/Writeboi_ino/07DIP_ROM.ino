void DIPPushData(unsigned long address,byte data){
  //Requires the data pins to be set as OUTPUT
  setAddressFull(address);
  setData(data);
  PM_DIP_WE_N_LOW();
  PM_DIP_WE_N_HIGH();
}


byte DIPReadSST(unsigned long address){

  //Sanity check, make sure data lines are inputs 
  setDataPinMode(INPUT);

  //Turn chip on
  digitalWrite(DIP_CE_N, LOW);

  //Write to address lines
  setAddressFull(address);

  //Set chip into read mode
  digitalWrite(DIP_OE_N, LOW);  
  

  //Read off bits:
  byte result = getData();


  //Turn chip off
  digitalWrite(DIP_OE_N, HIGH);
  digitalWrite(DIP_CE_N, HIGH);
  
  return result;

}



bool DIPWriteSST(unsigned long address, byte data){

  //activate chip in no-output mode
  digitalWrite(DIP_CE_N, LOW);

  delayMicroseconds(1); //A little delay to avoid contention

  //Set data pins as outputs
  setDataPinMode(OUTPUT);
  
  
  DIPPushData(0x5555,0xAA); //First magic number
  DIPPushData(0x2AAA,0x55); //Second magic number 
  DIPPushData(0x5555,0xA0); //Third magic number

  DIPPushData(address,data); //Actually write the data
  delayMicroseconds(20); //Wait for write cycle to finish
  
  
  //Set data pins back to input
  setDataPinMode(INPUT);


  byte readback = DIPReadSST(address);

  //make sure things are turned off
  digitalWrite(DIP_CE_N, HIGH);

  if (data == readback){
    return 0;
  }

  return 1;
  
}



bool DIPEraseSST(){

  //activate chip in no-output mode
  digitalWrite(DIP_CE_N, LOW);


  //Set data pins as outputs
  setDataPinMode(OUTPUT);

  
  DIPPushData(0x5555UL,0xAA);//First magic number
  DIPPushData(0x2AAAUL,0x55);//Second magic number
  DIPPushData(0x5555UL,0x80);//Third magic number
  DIPPushData(0x5555UL,0xAA);//Fourth magic number
  DIPPushData(0x2AAAUL,0x55);//Fifth magic number
  DIPPushData(0x5555UL,0x10);//Sixth magic number


  
  delay(1);

  //Set data pins back to input
  setDataPinMode(INPUT);

  delay(1000);

  //make sure things are turned off
  digitalWrite(DIP_CE_N, HIGH);

  return 0;
  
}
