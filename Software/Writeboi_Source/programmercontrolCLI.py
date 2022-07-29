import serial
import binascii
import time
import timeit
import cProfile



class programmerException(Exception):
    pass;


carttypedict = {
    0x00:"ROM ONLY",
    0x01:"MBC1",
    0x02:"MBC1+RAM",
    0x03:"MBC1+RAM+BATTERY",
    0x05:"MBC2",
    0x06:"MBC2+BATTERY",
    0x08:"ROM+RAM",
    0x09:"ROM+RAM+BATTERY",
    0x0B:"MMM01",
    0x0C:"MMM01+RAM",
    0x0D:"MMM01+RAM+BATTERY",
    0x0F:"MBC3+TIMER+BATTERY",
    0x10:"MBC3+TIMER+RAM+BATTERY",
    0x11:"MBC3",
    0x12:"MBC3+RAM",
    0x13:"MBC3+RAM+BATTERY",
    0x19:"MBC5",
    0x1A:"MBC5+RAM",
    0x1B:"MBC5+RAM+BATTERY",
    0x1C:"MBC5+RUMBLE",
    0x1D:"MBC5+RUMBLE+RAM",
    0x1E:"MBC5+RUMBLE+RAM+BATTERY",
    0x20:"MBC6",
    0x22:"MBC7+SENSOR+RUMBLE+RAM+BATTERY",
    0xFC:"POCKET CAMERA",
    0xFD:"TAMA5",
    0xFE:"HuC3",
    0xFF:"HuC1+RAM+BATTERY",
    }


romsizedict = {
    0x00:"32 KByte",
    0x01:"64 KByte",
    0x02:"128 KByte",
    0x03:"256 KByte",
    0x04:"512 KByte",
    0x05:"1 MByte",
    0x06:"2 MByte",
    0x07:"4 MByte",
    0x08:"8 MByte",
    }


ramsizedict = {
    0x00:"No RAM (512 nybbles if MBC2)",
    0x02:"8 KByte",
    0x03:"32 KByte",
    0x04:"128 KByte",
    0x05:"64 KByte",
    }









def dumpHeader(targetdevice,interface):
    if interface == "MBC":
        commandID = "4,";
    elif interface == "DIP":
        commandID = "70,";
    else:
        print("Invalid interface selected: " + str(interface) );
        raise Exception("");
        
    command = commandID+"0,0\n";
    targetdevice.write(command.encode('utf-8'));
    response = targetdevice.read(1024);
    targetdevice.readline();
    return response[:];

def parseHeader(headerkb):
    print("Parsing cartridge header.");
    print("Title + Manufacturer code: ",end="");
    try:
        print(headerkb[0x134:0x143].decode("utf-8"));
    except UnicodeDecodeError:
        print("INVALID");

    carttype = int(headerkb[0x147]);
    print("Cartridge type: " + hex(carttype) +" - ",end="");
    if carttype in carttypedict:
        print(carttypedict[carttype]);
    else:
        print("INVALID");

    romsize = int(headerkb[0x148]);
    print("ROM size: " + hex(romsize) + " - ",end="");
    if romsize in romsizedict:
        print(romsizedict[romsize]);
    else:
        print("INVALID");
    
    ramsize = int(headerkb[0x149]);
    print("RAM size: " + hex(ramsize) + " - ",end="");
    if ramsize in ramsizedict:
        print(ramsizedict[ramsize]);
    else:
        print("INVALID");


    checksum = 0;
    i = 0x134;
    while i<=0x14C:
        checksum = (checksum - headerkb[i] - 1) & 0xFF;
        i += 1;
    print("Header checksum: " + hex(headerkb[0x14D]) + " - ", end="");
    if int(headerkb[0x14D]) == checksum:
        print("OK!");
    else:
        print("Error.");
        print("Correct checksum would be " + hex(checksum));



def printFileHeader(filename):
    with open(filename,'rb') as f:
        headerkb = f.read(1024);
        parseHeader(headerkb);

def printCartridgeHeader(targetdevice, interface):
    parseHeader(dumpheader(targetdevice, interface));


def chipErase(targetdevice,interface,targetIC):
    address = "0";
    
    if interface == "MBC1":
        if targetIC == "SST":
            commandID = "39,";
        elif targetIC == "M29":
            commandID = "59,";
        else:
            print("Invalid IC selected: " + str(targetIC));
            raise programmerException("");
        
    elif interface == "MBC5":
        if targetIC == "SST":
            commandID = "49,";
        elif targetIC == "M29":
            commandID = "69,";
        elif targetIC == "M29Chip2":
            commandID = "69,";
            address = "2097152";
        else:
            print("Invalid IC selected: " + str(targetIC));
            raise programmerException("");
        
    elif interface == "DIP":
        if targetIC == "SST":
            commandID = "19,";
        else:
            print("Invalid IC selected: " + str(targetIC));
            raise programmerException("");       
        
    else:
        print("Invalid interface selected: " + str(interface));
        raise programmerException("");
    
    print("Starting Erase.")
    command = commandID+address+",0\n";
    targetdevice.write(command.encode('utf-8'));
    
    while True:
        response = int((targetdevice.readline()).decode('utf-8').rstrip(),base=16);
        if response == 0:
            print("Erase successful.");
            return 0;
        elif response == 2:
            print(".",end="");
        else:
            print("Erase error.");
            raise programmerException("");
        





def chunkRead(targetdevice,filename,numkb,interface,targetIC="ROM",startkb=0):

    if interface == "MBC1":
        if targetIC == "RAM": commandID = "81,";
        elif targetIC == "ROM": commandID = "80,";
        else:
            print("Invalid IC selected.");
            raise programmerException("");
        
    elif interface == "MBC5":
        if targetIC == "RAM": commandID = "91,";
        elif targetIC == "ROM": commandID = "90,";
        else:
            print("Invalid IC selected.");
            raise programmerException("");
        
    elif interface == "DIP": 
        if targetIC == "ROM": commandID = "70,";
        else:
            print("Invalid IC selected.");
            raise programmerException("");
        
    else:
        print("Invalid interface selected: " + str(interface));
        raise programmerException("");
    
    print("Starting Fastread.")
    t0 = time.time();
    curpos = startkb;
    with open(filename,'wb') as f:
        while curpos<startkb+numkb:
            command = commandID+str(curpos*1024)+",0\n";
            targetdevice.write(command.encode('utf-8'));
            response = targetdevice.read(1024);
            f.write(response);
            print(curpos);
            curpos += 1;
            targetdevice.readline();
    t1 = time.time();
    print(str(numkb) + " kilobytes in " + str((t1-t0)) + " seconds.");
    return 0;

def chunkWrite(targetdevice,filename,numkb,interface,targetIC,erase=True,startoffset=0):
    #file size in kilobytes

    if interface == "MBC1":
        if targetIC == "SST":
            if erase:
                chipErase(targetdevice,interface,targetIC);
            commandID = "82,";
        elif targetIC == "M29":
            if erase:
                chipErase(targetdevice,interface,targetIC);
            commandID = "83,";
        elif targetIC == "RAM":
            commandID = "84,";

        else:
            print("Invalid IC selected.");
            raise programmerException("");
 
            
        
    elif interface == "MBC5":
        if targetIC == "SST":
            if erase:
                chipErase(targetdevice,interface,targetIC);
            commandID = "92,";
        elif targetIC == "M29":
            if erase:
                chipErase(targetdevice,interface,targetIC);
                if startoffset+numkb > 2048:
                    chipErase(targetdevice,interface,"M29Chip2");
            commandID = "93,";
        elif targetIC == "RAM":
            commandID = "94,";

        else:
            print("Invalid IC selected.");
            raise programmerException("");
    
    elif interface == "DIP":
        if targetIC == "SST":
            if erase:
                chipErase(targetdevice,interface,targetIC);
            commandID = "71,";
        else:
            print("Invalid IC selected.");
            raise programmerException("");
        
    else:
        print("Invalid interface selected: " + str(interface));
        raise programmerException("");

        
    print("Starting Fastwrite.")


    t0 = time.time();

    chunksize = 1024;
    with open(filename,'rb') as f:
        chunks = (numkb*(1024/chunksize));
        print("Total chunks: " + str(chunks));
        curchunk = 0;
        curbyte = 0;

        while curchunk < chunks:
            command = commandID+str(curchunk*chunksize + startoffset*chunksize)+",0\n";
            targetdevice.write(command.encode('utf-8'));
            targetdevice.write(f.read(chunksize));
            response = int((targetdevice.readline()).decode('utf-8').rstrip(),base=16);
            print("Chunk "+ str(curchunk+startoffset) + ": " + str(response) );
            if response != 0:
                print("Write error at chunk " + str(curchunk));
                raise programmerException("");


            curchunk +=1;
    t1 = time.time();
    print(str(numkb) + " kilobytes in " + str((t1-t0)) + " seconds.");
    print("Done.");
    return 0;











