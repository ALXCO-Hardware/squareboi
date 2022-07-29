/* 
 *  SerialManager command cheatsheet

PROGRAMMER CONTROL
00- request info
01- reset
02- set MBC1 bank register
03- set MBC5 bank register
04- dump cartridge header

DIP 
11- DIPSSTRead
12- DIPSSTWrite
19- DIPSSTErase

GENERAL MBC
20- MBC1Read
21- MBC1ReadRAM
22- MBC1WriteRAM

25- MBC5Read
26- MBC5ReadRAM
27- MBC5WriteRAM

MBC1 SST 
30- MBC1SSTWrite
39- MBC1SSTErase

MBC5 SST
40- MBC5SSTWrite
49- MBC5SSTErase

MBC1 M29 
50- MBC1M29Write
59- MBC1M29Erase

MBC5 M29
60- MBC5M29Write
69- MBC5M29Erase

DIP CHUNK
70- DIPSSTChunkRead
71- DIPSSTChunkWrite

MBC1 CHUNK
80- MBC1ChunkRead
81- MBC1ChunkReadRAM
82- MBC1SSTChunkWrite
83- MBC1M29ChunkWrite
84- MBC1ChunkWriteRAM

MBC5 CHUNK
90- MBC5ChunkRead
91- MBC5ChunkReadRAM
92- MBC5SSTChunkWrite
93- MBC5M29ChunkWrite
94- MBC5ChunkWriteRAM


*/



void serialManager(){
  
  //Message syntax: [operation],[address],[data]
  //3 decimal values, final one limited to 255
  //(wanted to do hex, but parsing got complicated)
  //Will always respond with a single hex value


  //examples: 
  // 1,1543,122
  // 0,5522,255
  // 2,0,0

  while (Serial.available() > 0) {
    
    // look for the next valid integer in the incoming serial stream:
    unsigned int command = Serial.parseInt();
    // do it again:
    unsigned long address = Serial.parseInt();
    // do it again:
    byte data = Serial.parseInt();   

    if (Serial.read() == '\n') {
      setBusy(true);
      switch(command){
        
        //PROGRAMMER CONTROL
        ////////////////////////////////
        case 0:
          //Requesting version data
          Serial.println(GLB_buildID,HEX);
          break;
        case 1:
          //Reset Cartridge
          resetCartridge();
          Serial.println(0,HEX);
          break;
        case 2:
          //set MBC1 bank register
          setMBC1BankRegister(address, data);
          Serial.println(0,HEX);
          break;
        case 3:
          //set MBC5 bank register
          setMBC5BankRegister(address, data);
          Serial.println(0,HEX);
          break;
        case 4:
          //Dump Cartridge Header
          Serial.println(MBCDumpHeader(),HEX);
          break;
        ////////////////////////////////
        
        //DIP  
        ////////////////////////////////
        case 11:
          //DIP SST Read
          Serial.println(DIPReadSST(address),HEX);
          break;
        case 12:
          //DIP SST Write
          Serial.println(DIPWriteSST(address,data),HEX);
          break;
        case 19:
          //DIP SST Erase
          Serial.println(DIPEraseSST(),HEX);
          break;
        ////////////////////////////////
          
        //COMMON MBC
        ////////////////////////////////
        case 20:
          //MBC1 Read
          Serial.println(MBC1Read(address),HEX);
          break;
        case 21:
          //MBC1 Read RAM
          Serial.println(MBC1ReadRAM(address),HEX);
          break;
        case 22:
          //MBC1 Write RAM
          Serial.println(MBC1WriteRAM(address,data),HEX);
        case 25:
          //MBC5 Read
          Serial.println(MBC5Read(address),HEX);
          break;
        case 26:
          //MBC5 Read RAM
          Serial.println(MBC5ReadRAM(address),HEX);
          break;
        case 27:
          //MBC5 Write RAM
          Serial.println(MBC5WriteRAM(address,data),HEX);
          break;
        ////////////////////////////////
        
        //MBC1 SST
        ////////////////////////////////
        case 30:
          //MBC1 SST Write
          Serial.println(MBC1WriteSST(address,data),HEX);
          break;
        case 39:
          //MBC1 SST Erase
          Serial.println(MBC1EraseSST(),HEX);
          break;
        ////////////////////////////////

        //MBC5 SST
        ////////////////////////////////
        case 40:
          //MBC5 SST Write
          Serial.println(MBC5WriteSST(address,data),HEX);
          break;
        case 49:
          //MBC5 SST Erase
          Serial.println(MBC5EraseSST(),HEX);
          break;
        ////////////////////////////////

        //MBC1 M29
        ////////////////////////////////
        case 50:
          //MBC1 M29 Write
          Serial.println(MBC1WriteM29(address,data),HEX);
          break;
        case 59:
          //MBC1 M29 Erase
          Serial.println(MBC1EraseM29(),HEX);
          break;
        ////////////////////////////////

        //MBC5 M29
        ////////////////////////////////
        case 60:
          //MBC5 M29 Write
          if(address<2097152UL){ 
            Serial.println(MBC5WriteM29(address,data),HEX);
          }
          else{
            Serial.println(MBC5WriteM29Chip2(address,data),HEX);
          }
          break;
        case 69:
          //MBC5 M29 Erase
          if(address<2097152UL){ 
            Serial.println(MBC5EraseM29(),HEX);
          }
          else{
            Serial.println(MBC5EraseM29Chip2(),HEX);
          }
          
          break;
        ////////////////////////////////


        //DIP CHUNK
        ////////////////////////////////
        case 70:
          //DIP SST ChunkRead
          Serial.println(DIPChunkReadSST(address),HEX);
          break;
        case 71:
          //DIP SST ChunkWrite
          Serial.println(DIPChunkWriteSST(address),HEX);
          break;
        ////////////////////////////////
        
        //MBC1 CHUNK
        ////////////////////////////////
        case 80:
          //MBC1 ChunkRead
          Serial.println(MBC1ChunkRead(address),HEX);
          break;
        case 81:
          //MBC1 ChunkRead RAM
          Serial.println(MBC1ChunkReadRAM(address),HEX);
          break;
        case 82:
          //MBC1 SST ChunkWrite
          Serial.println(MBC1ChunkWriteSST(address),HEX);
          break;
        case 83:
          //MBC1 M29 ChunkWrite
          Serial.println(MBC1ChunkWriteM29(address),HEX);
          break;
        case 84:
          //MBC1 ChunkWrite RAM
          Serial.println(MBC1ChunkWriteRAM(address),HEX);
          break;
        ////////////////////////////////
        
        //MBC5 CHUNK
        ////////////////////////////////
        case 90:
          //MBC5 ChunkRead
          Serial.println(MBC5ChunkRead(address),HEX);
          break;
        case 91:
          //MBC5 ChunkRead RAM
          Serial.println(MBC5ChunkReadRAM(address),HEX);
          break;
        case 92:
          //MBC5 SST ChunkWrite
          Serial.println(MBC5ChunkWriteSST(address),HEX);
          break;
        case 93:
          //MBC5 M29 ChunkWrite
          Serial.println(MBC5ChunkWriteM29(address),HEX);
          break;
        case 94:
          //MBC5 ChunkWrite RAM
          Serial.println(MBC5ChunkWriteRAM(address),HEX);
          break;
        ////////////////////////////////

        
        } //End of Switch statement
    setBusy(false);
    } //End of newline received
  } // End of Serial.available
   
} // End of Serialmanager
