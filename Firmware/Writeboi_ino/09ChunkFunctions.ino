//Reading
////////////////////////////////////////////////////////////////

bool MBCDumpHeader(){
  //Resets the cartridge, then dumps the first KB without changing memory banks
  resetCartridge();
  GLB_MBCROMBankValid = true;
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(MBC5Read(i));
  }
  return 0;  
}


bool MBC1ChunkRead(unsigned long startaddress){
  //Reads in 1KB chunks
  setMBC1BankRegister(3,1); //Go to memory mode 1
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(MBC1Read(startaddress+i));
  }
  setMBC1BankRegister(3,0); //Return to memory mode 0
  return 0;  
}


bool MBC5ChunkRead(unsigned long startaddress){
  //Reads in 1KB chunks
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(MBC5Read(startaddress+i));
  }
  return 0;  
}


bool DIPChunkReadSST(unsigned long startaddress){
  //Reads in 1KB chunks
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(DIPReadSST(startaddress+i));
  }
  return 0;  
}

bool MBC1ChunkReadRAM(unsigned long startaddress){
  //Reads in 1KB chunks
  setMBC1BankRegister(3,1); //Go to memory mode 1
  setMBC1BankRegister(0,0xA); //Enable RAM
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(MBC1ReadRAM(startaddress+i));
  }
  setMBC1BankRegister(0,0x0); //Disable RAM
  setMBC1BankRegister(3,0); //Return to memory mode 0
  return 0;  
}

bool MBC5ChunkReadRAM(unsigned long startaddress){
  //Reads in 1KB chunks
  setMBC5BankRegister(0,0xA); //Enable RAM
  for (unsigned long i = 0; i<1024;i++){
    Serial.write(MBC5ReadRAM(startaddress+i));
  }
  setMBC5BankRegister(0,0x0); //Disable RAM
  return 0;  
}
////////////////////////////////////////////////////////////////

//Writing
////////////////////////////////////////////////////////////////

unsigned int DIPChunkWriteSST(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (DIPWriteSST(address+i, GLB_bytearray[i])) {failed += 1;}
  }

  return failed;
}


unsigned int MBC1ChunkWriteSST(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  
  setMBC1BankRegister(3,1); //Go to memory mode 1
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (MBC1WriteSST(address+i, GLB_bytearray[i])) {failed += 1;}
  }
  setMBC1BankRegister(3,0); //Return to memory mode 0
  return failed;
}


unsigned int MBC1ChunkWriteM29(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  
  setMBC1BankRegister(3,1); //Go to memory mode 1
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (MBC1WriteM29(address+i, GLB_bytearray[i])) {failed += 1;}
  }
  setMBC1BankRegister(3,0); //Return to memory mode 0
  return failed;
}


unsigned int MBC1ChunkWriteRAM(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  setMBC1BankRegister(3,1); //Go to memory mode 1
  setMBC1BankRegister(0,0xA); //Enable RAM
  //Transfer them over to the RAM chip at our leisure (as long as we don't timeout)
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (MBC1WriteRAM(address+i, GLB_bytearray[i])) {failed += 1;}
  }
  setMBC1BankRegister(0,0x0); //Disable RAM
  setMBC1BankRegister(3,0); //Return to memory mode 0
  return failed;
}

unsigned int MBC5ChunkWriteSST(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (MBC5WriteSST(address+i, GLB_bytearray[i])) {failed += 1;}
  }

  return failed;
}

unsigned int MBC5ChunkWriteM29(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
 
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  if(address<2097152UL){ //If we're on the first chip of a 4MB board
    for (unsigned long i=0; i<ARRSIZE; i++){
      if (MBC5WriteM29(address+i, GLB_bytearray[i])) {failed += 1;}
    }
  }
  else{ //If we're on the second chip
  for (unsigned long i=0; i<ARRSIZE; i++){
      if (MBC5WriteM29Chip2(address+i, GLB_bytearray[i])) {failed += 1;}
    }
  }
  
  return failed;
}

unsigned int MBC5ChunkWriteRAM(unsigned long address){
  //Writes in 1024 byte chunks.
  //Will absolutely keep reading data until there's none left. If it breaks midway, you'll have to reset.
  unsigned int failed = 0; 
  
  //Store all incoming bytes in the array
  Serial.readBytes(GLB_bytearray,ARRSIZE);
  
  //Transfer them over to the flash chip at our leisure (as long as we don't timeout)
  setMBC5BankRegister(0,0xA); //Enable RAM
  for (unsigned long i=0; i<ARRSIZE; i++){
    if (MBC5WriteRAM(address+i, GLB_bytearray[i])) {failed += 1;}
  }
  setMBC5BankRegister(0,0x0); //Disable RAM

  return failed;
}

////////////////////////////////////////////////////////////////
