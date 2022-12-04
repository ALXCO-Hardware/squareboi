import serial
import binascii
import time
import timeit
import cProfile

class programmerException(Exception):
    pass;


def getBuildID(manager,targetdevice):
    try:     
        command = "0,0,0\n";
        targetdevice.write(command.encode('utf-8'));
        response = int((targetdevice.readline()).decode('utf-8').rstrip(),base=16);
        return response;
    except serial.SerialException:
        manager.logprint("Programmer access denied.", text_color = "red");
        raise programmerException("");

def dumpHeader(manager,targetdevice,interface):
    if interface == "MBC":
        commandID = "4,";
    elif interface == "DIP":
        commandID = "70,";
    else:
        manager.logprint("Invalid interface selected: " + str(interface), text_color = "red");
        raise programmerException("");
    try:     
        command = commandID+"0,0\n";
        targetdevice.write(command.encode('utf-8'));
        response = targetdevice.read(1024);
        targetdevice.readline();
        return response[:];
    except serial.SerialException:
        manager.logprint("Programmer access denied.", text_color = "red");
        raise programmerException("");



def chipErase(manager,targetdevice,interface,targetIC):
    address = "0";
    
    if interface == "MBC1":
        if targetIC == "SST":
            commandID = "39,";
        elif targetIC == "M29":
            commandID = "59,";
        else:
            manager.logprint("Invalid IC selected: " + str(targetIC), text_color = "red");
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
            manager.logprint("Invalid IC selected: " + str(targetIC), text_color = "red");
            raise programmerException("");
        
    elif interface == "DIP":
        if targetIC == "SST":
            commandID = "19,";
        else:
            manager.logprint("Invalid IC selected: " + str(targetIC), text_color = "red");
            raise programmerException("");         
        
    else:
        manager.logprint("Invalid IC selected: " + str(targetIC), text_color = "red");
        raise programmerException("");

    if targetIC == "M29Chip2":
        manager.logprint("Starting Erase: Chip 2");
    else:
        manager.logprint("Starting Erase.");
    command = commandID+address+",0\n";
    targetdevice.write(command.encode('utf-8'));

    
    try:
        while True:
            response = int((targetdevice.readline()).decode('utf-8').rstrip(),base=16);
            if response == 0:
                manager.logprint("Erase successful.");
                return 0;
            elif response == 2:
                manager.logprint(".",end="");
                manager.update(timeout=1);
                
            else:
                manager.logprint("Erase error.", text_color = "red");
                raise programmerException("");
    except serial.SerialException:
        manager.logprint("Programmer access denied.", text_color = "red");
        raise programmerException("");





def chunkRead(manager,targetdevice,numkb,interface,targetIC,startkb=0):

    if interface == "MBC1":
        if targetIC == "RAM": commandID = "81,";
        elif targetIC == "ROM": commandID = "80,";
        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
        
    elif interface == "MBC5":
        if targetIC == "RAM": commandID = "91,";
        elif targetIC == "ROM": commandID = "90,";
        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
        
    elif interface == "DIP": 
        if targetIC == "ROM": commandID = "70,";
        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
        
    else:
        manager.logprint("Invalid interface selected: " + str(interface), text_color = "red");
        raise programmerException("");
    
    manager.logprint("Starting Chunkread.")
    manager.progbar.update(current_count=0, max=numkb);
    t0 = time.time();
    curpos = startkb;
    chunklist = [];

    try:
        while curpos<startkb+numkb:
            if manager.stoprequested:
                manager.logprint("Read interrupted by user.");
                manager.stoprequested = False;
                raise programmerException("");
            command = commandID+str(curpos*1024)+",0\n";
            targetdevice.write(command.encode('utf-8'));
            response = targetdevice.read(1024);
            chunklist.append(response);
            manager.progbar.update(current_count=curpos);
            curpos += 1;
            manager.update(timeout=1);
            targetdevice.readline();
    except serial.SerialException:
        manager.logprint("Programmer access denied.", text_color = "red");
        raise programmerException("");
    
    t1 = time.time();
    manager.logprint(str(numkb) + " kilobytes in " + str((t1-t0)) + " seconds.");
    manager.logprint("Read cycle complete.");
    return b"".join(chunklist);

def chunkWrite(manager,targetdevice,filebytes,numkb,interface,targetIC,erase=True,startoffset=0):
    #file size in kilobytes

    if interface == "MBC1":
        if targetIC == "SST":
            if erase:
                try:
                    chipErase(manager,targetdevice,interface,targetIC);
                except programmerException:
                    manager.logprint("Erase Failure.", text_color = "red");
                    raise programmerException("");
            commandID = "82,";
        elif targetIC == "M29":
            if erase:
                try:
                    chipErase(manager,targetdevice,interface,targetIC);
                except programmerException:
                    manager.logprint("Erase Failure.", text_color = "red");
                    raise programmerException("");
            commandID = "83,";
        elif targetIC == "RAM":
            commandID = "84,";

        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
 
            
        
    elif interface == "MBC5":
        if targetIC == "SST":
            if erase:
                try:
                    chipErase(manager,targetdevice,interface,targetIC);
                except programmerException:
                    manager.logprint("Erase Failure.", text_color = "red");
                    raise programmerException("");
            commandID = "92,";
        elif targetIC == "M29":
            if erase:
                try:
                    chipErase(manager,targetdevice,interface,targetIC);
                except programmerException:
                    manager.logprint("Erase Failure.", text_color = "red");
                    raise programmerException("");
                if startoffset+numkb > 2048:
                    try:
                        chipErase(manager,targetdevice,interface,"M29Chip2");
                    except programmerException:
                        manager.logprint("Erase Failure on Chip 2.", text_color = "red");
                        raise programmerException("");
            commandID = "93,";
        elif targetIC == "RAM":
            commandID = "94,";

        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
    
    elif interface == "DIP":
        if targetIC == "SST":
            if erase:
                if chipErase(manager,targetdevice,interface,targetIC): return 1;
            commandID = "71,";
        else:
            manager.logprint("Invalid IC selected.", text_color = "red");
            raise programmerException("");
        
    else:
        manager.logprint("Invalid interface selected: " + str(interface), text_color = "red");

        
    manager.logprint("Starting Chunkwrite.")
    manager.progbar.update(current_count=0, max=numkb);

    t0 = time.time();

    chunksize = 1024;

    manager.logprint("Total chunks: " + str(numkb));
    curchunk = 0;
    curbyte = 0;

    try:
        while curchunk < numkb:
            if manager.stoprequested:
                manager.logprint("Write interrupted by user.");
                manager.stoprequested = False;
                raise programmerException("");
            command = commandID+str(curchunk*chunksize + startoffset*chunksize)+",0\n";
            targetdevice.write(command.encode('utf-8'));
            targetdevice.write(filebytes[curchunk*1024:(curchunk+1)*1024]);
            response = int((targetdevice.readline()).decode('utf-8').rstrip(),base=16);
            manager.progbar.update(current_count=curchunk);
            if response != 0:
                manager.logprint("Write error on chunk "+ str(curchunk+startoffset) + ": " + str(response), text_color = "red");
                raise programmerException("");
            curchunk +=1;
            manager.update(timeout=1);
    except serial.SerialException:
        manager.logprint("Programmer access denied.", text_color = "red");
        raise programmerException("");
        
    t1 = time.time();
    manager.logprint(str(numkb) + " kilobytes in " + str((t1-t0)) + " seconds.");
    manager.logprint("Write cycle complete.");
    return 0;






