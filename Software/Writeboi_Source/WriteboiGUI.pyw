import serial
import binascii
import time
import timeit
import cProfile
import ntpath
import PySimpleGUI as sg

import programmercontrol as pgc
from programmercontrol import programmerException

##About this program!
about_layout = [
    [sg.Text("Writeboi GUI")],
    [sg.Text("Version 1.00")],
    [sg.Text("For use with Squareboi V2.01")],
    [sg.Text("And Writeboi V2.01")],
    [sg.Text("ALXCO 2022")],
    [sg.Button("Close")],

];
##



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

usableMBCdict = {
    "ROM ONLY":"MBC1",
    "MBC1":"MBC1",
    "MBC1+RAM":"MBC1",
    "MBC1+RAM+BATTERY":"MBC1",
    "MBC2":"MBC1",
    "MBC2+BATTERY":"MBC1",
    "ROM+RAM":"MBC1",
    "ROM+RAM+BATTERY":"MBC1",
    "MMM01":"Unsupported",
    "MMM01+RAM":"Unsupported",
    "MMM01+RAM+BATTERY":"Unsupported",
    "MBC3+TIMER+BATTERY":"MBC5",
    "MBC3+TIMER+RAM+BATTERY":"MBC5",
    "MBC3":"MBC5",
    "MBC3+RAM":"MBC5",
    "MBC3+RAM+BATTERY":"MBC5",
    "MBC5":"MBC5",
    "MBC5+RAM":"MBC5",
    "MBC5+RAM+BATTERY":"MBC5",
    "MBC5+RUMBLE":"MBC5",
    "MBC5+RUMBLE+RAM":"MBC5",
    "MBC5+RUMBLE+RAM+BATTERY":"MBC5",
    "MBC6":"Unsupported",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY":"Unsupported",
    "POCKET CAMERA":"MBC5",
    "TAMA5":"Unsupported",
    "HuC3":"Unsupported",
    "HuC1+RAM+BATTERY":"MBC1",
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

romsizeconverterdict = {
    "32 KByte":"32KB",
    "64 KByte":"64KB",
    "128 KByte":"128KB",
    "256 KByte":"256KB",
    "512 KByte":"512KB",
    "1 MByte":"1MB",
    "2 MByte":"2MB",
    "4 MByte":"4MB",
    "8 MByte":"8MB",
    }

romvaluesdict = {
    "32KB":32,
    "64KB":64,
    "128KB":128,
    "256KB":256,
    "512KB":512,
    "1MB":1024,
    "2MB":2048,
    "4MB":4096,
    "8MB":8192,
    }

ramsizedict = {
    0x00:"No RAM (512 nybbles if MBC2)",
    0x02:"8 KByte",
    0x03:"32 KByte",
    0x04:"128 KByte",
    0x05:"64 KByte",
    }



ramsizeconverterdict = {
    "No RAM (512 nybbles if MBC2)":"No RAM/512",
    "8 KByte":"8KB",
    "32 KByte":"32KB",
    "128 KByte":"64KB",
    "64 KByte":"128KB",
    }

ramvaluesdict = {
    "No RAM/512":1,
    "8KB":8,
    "32KB":32,
    "64KB":64,
    "128KB":128,
    }



def inttosquares(n): #takes a nibble from the logo, returns as an ASCII bitmap representation
    return "".join(["█" if digit=='1' else " " for digit in bin(int(n,16))[2:6].zfill(4)]);


def parselogo(logobytes):

    logolisthex = list(logobytes.hex());
    logolist = [inttosquares(i) for i in logolisthex];
    linelist = ['']*8

    #Upper half:
    for i in range(4):
        linelist[i] = "".join([logolist[j] for j in range(i,48,4)])+"\n";
    #Lower half:
    for i in range(4):
        linelist[i+4] = "".join([logolist[j] for j in range(i+48,96,4)])+"\n";


    return "".join([i for i in linelist]);




class progmanager(object):
    def __init__(self):

        ##Variables:

        self.workingfile = bytearray();
        self.busy = False;
        self.serialconnected = False;
        self.stoprequested = False;
        self.serialtarget = None;
        
     

        ##Menu elements:

        self.menu_layout = [
            ["File",["Open","Save","---","Exit"]],
            ["Tools",["Correct Checksum"]],
            ["Help",["About..."]],
        ];

        #File elements:

        self.workingfilesource = sg.Input(readonly=True,size=40);

        self.sizebar = sg.ProgressBar(8192, orientation="horizontal", size=(35,40));
        self.workingfilesizetext = sg.Text("0/8192KB",size=55,justification="right");

        self.RAtitletext = sg.Input(readonly=True,size=27)
        self.RAlogobox = sg.Multiline(default_text=" ",size=(48,8),no_scrollbar = True,disabled=True)
        self.RAchecksumtext = sg.Input(readonly=True,size=4);
        self.RAmbctext = sg.Input(readonly=True)
        
        
        self.analyzerlayout = [
            [sg.Text("Title/Manufacturer:"),self.RAtitletext],
            [sg.Text("Logo Bitmap:")],
            [self.RAlogobox],
            [sg.Text("Header Checksum:"),self.RAchecksumtext],
            [sg.Text("MBC:"),self.RAmbctext],
        ];

        self.analyzertab = sg.Frame("ROM Analyzer",self.analyzerlayout);
        
        self.file_layout = [
            [sg.Text("Source:"),self.workingfilesource],
            [self.analyzertab],
            [self.sizebar],
            [self.workingfilesizetext],

        ];
        
        self.fileframe = sg.Frame("Working File",self.file_layout,size=(416,386), element_justification="center");
        
        #Programmer elements:
        
        self.serialport = sg.Input("COM3",size=8);
        self.connectbutton = sg.Button("Connect",key="-CONNECT-");
        self.connectstatustext = sg.Input("Disconnected",text_color="red",readonly=True,size=12);
        
        self.carttypecombo = sg.Combo(key="-CARTTYPE-", values=["Squareboi","DIP32 Socket","Original Cartridge"], default_value="Select...",readonly=True, enable_events=True);
        self.interfacecombo = sg.Combo(key="-INTERFACE-", values=["Select..."], default_value="Select...",readonly=True, disabled=True, size=9, enable_events=True);
        self.targetICcombo = sg.Combo(key="-TARGETIC-", values=["Select..."], default_value="Select...",readonly=True, disabled=True, size=9);
        self.romsizecombo = sg.Combo(key="-ROMSIZE-", values=["32KB","64KB","128KB","256KB","512KB","1MB","2MB","4MB","8MB"], default_value="Select...", readonly=True, size=9);
        self.ramsizecombo = sg.Combo(key="-RAMSIZE-", values=["No RAM/512","8KB","32KB","64KB","128KB"], default_value="Select...", readonly=True, size=9);

        #Programmer: ReadWrite Tabgroup

        self.detectbutton = sg.Button("Autodetect", key="-AUTODETECT-", disabled=True);

        self.readlayout = [
            [self.detectbutton],
            [sg.Text("ROM Size:"),sg.Text("RAM Size:")],
            [self.romsizecombo,self.ramsizecombo],
            [sg.Button("Read From Cartridge", key="-CARTREAD-")],
        ];

        self.readtab = sg.Tab("Read",self.readlayout);

        self.erasecheckbox = sg.Checkbox("Erase Before Writing",default=True);
        self.verifycheckbox = sg.Checkbox("Verify Data");
        
        self.writelayout = [
            [self.erasecheckbox],
            [self.verifycheckbox],
            [sg.Button("Write To Cartridge", key="-CARTWRITE-")],
        ];
        
        self.writetab = sg.Tab("Write",self.writelayout);
        
        self.readwritelayout= [
        [self.readtab,self.writetab]
        ];
    
        self.readwritetabs = sg.TabGroup(self.readwritelayout)

        self.forcestopbutton = sg.Button("Force Stop", key="-FORCESTOP-", disabled=True)

        self.programmer_layout = [
            [sg.Text("Serial Port:"),self.serialport],
            [self.connectbutton,self.connectstatustext],
            [sg.Text("Cartridge Type:")],
            [self.carttypecombo],
            [sg.Text("Interface:"),sg.Text("Target IC:")],
            [self.interfacecombo, self.targetICcombo],
            [self.readwritetabs],
            [self.forcestopbutton],
            
        ];

        self.programmerframe = sg.Frame("Programmer",self.programmer_layout,size=(216,386), element_justification="left");
      
        #General elements:
        
        self.progbar = sg.ProgressBar(8192, orientation="horizontal", size=(58,40));

        self.outputbox = sg.MLine(key='-OUTPUT-'+sg.WRITE_ONLY_KEY, size=(77,6));



        self.layout = [
            [sg.Menu(self.menu_layout)],
            [self.fileframe,self.programmerframe],
            [self.outputbox],
            [self.progbar],
            ];


        self.window = sg.Window("Writeboi V2.01",self.layout,font="courier 10",enable_close_attempted_event=True);






        
    def calculatechecksum(self,data):
        checksum = 0;
        i = 0x134;
        while i<=0x14C:
            checksum = (checksum - data[i] - 1) & 0xFF;
            i += 1;
        return checksum;

        


    def analyzeROM(self,source):
        self.sizebar.update(len(self.workingfile)/1024);
        self.workingfilesizetext.update(str(len(self.workingfile)//1024)+"/8192KB");
        self.workingfilesource.update(value = source);
        if len(self.workingfile)>=1024 and source != "Cartridge RAM" and source[-4:]!=".sav":
            try:
                self.RAtitletext.update(value= self.workingfile[0x134:0x143].decode("utf-8"));
            except UnicodeDecodeError:
                pass;
            self.RAlogobox.update(value= parselogo(self.workingfile[0x104:0x134]));
            checksum = self.calculatechecksum(self.workingfile);
            color = "red";
            if int(self.workingfile[0x14D]) == checksum:
                color = "green";
            self.RAchecksumtext.update(value="0x"+hex(self.workingfile[0x14D])[2:].upper(),text_color = color);
            if int(self.workingfile[0x147]) in carttypedict.keys():
                self.RAmbctext.update(value = carttypedict[self.workingfile[0x147]]);
            else:
                self.RAmbctext.update(value = "INVALID");
                
        else:
            self.RAlogobox.update(value="");
            self.RAchecksumtext.update(value="");
            self.RAmbctext.update(value = "Not a ROM file.");

    def correctchecksum(self):

        if self.workingfile and len(self.workingfile)>=512:
            actualchecksum = self.workingfile[0x14D];
            correctchecksum = self.calculatechecksum(self.workingfile);
            if actualchecksum != correctchecksum:
                self.workingfile[0x14D] = correctchecksum;
                self.RAchecksumtext.update(value="0x"+hex(self.workingfile[0x14D])[2:].upper(),text_color = "green");
                self.logprint("Corrected header checksum.");
            else:
                self.logprint("Header hecksum is already correct!");
        else:
            self.logprint("Working file is not long enough to contain a header checksum!");

    def logprint(self,text,end="\n"):
        self.outputbox.print(text,end=end);


    def busyOn(self):
        self.busy = True;
        self.forcestopbutton.update(disabled = False);

    def busyOff(self):
        self.busy = False;
        self.stoprequested = False;
        self.forcestopbutton.update(disabled = True);


    def serialconnect(self):
        if self.serialconnected:
            self.serialtarget.close();
            self.serialconnected = False;
            self.connectstatustext.update(value="Disconnected", text_color="red");
            self.connectbutton.update(text="Connect");
            self.logprint("Disconnecting.");
        else:
            self.busyOn();
            self.logprint("Establishing connection...");
            self.window.read(1);
            try:
                self.serialtarget = serial.Serial(port=self.serialport.get(), baudrate=115200,timeout=3);
            except serial.SerialException as err:
                self.logprint(err);
            else:
                self.serialconnected = True;
                self.connectstatustext.update(value="Connected", text_color="green");
                self.connectbutton.update(text="Disconnect");
                time.sleep(2);
                self.logprint("Programmer connected.");
            self.busyOff();

    def cartread(self,values):
        if "Select..." not in [values["-CARTTYPE-"], values["-INTERFACE-"], values["-TARGETIC-"],self.ramsizecombo.get(),self.romsizecombo.get(), ]:
            if self.serialconnected:
                self.busyOn();
                if values["-TARGETIC-"] == "RAM":
                    temp_targic = "RAM";
                    temp_readsize = ramvaluesdict[self.ramsizecombo.get()];
                else:
                    temp_targic = "ROM";
                    temp_readsize = romvaluesdict[self.romsizecombo.get()];

                try:
                    tempfile = pgc.chunkRead(self, self.serialtarget, numkb=temp_readsize, interface=values["-INTERFACE-"] ,targetIC=temp_targic);
                except programmerException:
                    self.logprint("Operation aborted. Working file has not been changed.");
                else:
                    self.workingfile = tempfile;
                    self.analyzeROM("Cartridge " + temp_targic);
                self.busyOff();
            else:
                self.logprint("Programmer is not connected!");
        else:
            self.logprint("Please fill in all programmer fields first!");

    def cartwrite(self,values):
        if "Select..." not in [values["-CARTTYPE-"], values["-INTERFACE-"], values["-TARGETIC-"], ]:
            if self.serialconnected:
                self.busyOn();

                if len(self.workingfile)>(2048*1024) and values["-INTERFACE-"] != "MBC5":
                    self.logprint("ROMs larger than 2MB are only supported on MBC5!");
                elif len(self.workingfile)>(512*1024) and values["-TARGETIC-"] == "SST":
                    self.logprint("ROMs larger than 512KB are not supported on SST39 memory!");
                else:
                    try:
                        pgc.chunkWrite(self,self.serialtarget, self.workingfile, numkb=len(self.workingfile)/1024 ,interface=values["-INTERFACE-"],targetIC=values["-TARGETIC-"],erase=self.erasecheckbox.get() );
                    except programmerException:
                        self.logprint("Write cycle failure. Data may be corrupt.");
                    else:
                        if self.verifycheckbox.get():
                            self.logprint("Verifying written data.");
                            try:
                                if values["-TARGETIC-"] == "RAM":
                                    temp_targic = "RAM";
                                else:
                                    temp_targic = "ROM";
                                tempfile = pgc.chunkRead(self, self.serialtarget, numkb=len(self.workingfile)/1024, interface=values["-INTERFACE-"] ,targetIC=temp_targic);
                                if bytearray(tempfile) == self.workingfile:
                                    self.logprint("Verification complete. Data written successfully.");
                                else:
                                    self.logprint("Verification failure. Data does not match.");
                            except programmerException:
                                self.logprint("Verification failure. Could not confirm integrity of written data.");
                                
                self.busyOff();
            else:
                self.logprint("Programmer is not connected!");
        else:
            self.logprint("Please fill in all programmer fields first!");


    def autodetect(self,carttype):
        try:
            if carttype == "DIP32 Socket":
                targinterface = "DIP";
            else:
                targinterface = "MBC";
            try:
                headerfile = pgc.dumpHeader(self, self.serialtarget, targinterface);
            except programmerException:
                self.logprint("Could not retrieve cartridge header!");
                raise programmerException("");
            
            
            try:
                titletext = headerfile[0x134:0x143].decode("utf-8");
            except UnicodeDecodeError:
                titletext = "";

            if headerfile[0x147] in carttypedict.keys():
                actualmbc = carttypedict[headerfile[0x147]];
                if targinterface == "DIP":
                    mbctouse = "DIP";
                else:
                    mbctouse = usableMBCdict[actualmbc];
            else:
                actualmbc = "Unknown";
                mbctouse = "Unsupported";
                
            if headerfile[0x148] in romsizedict.keys():
                romsize =  romsizedict[headerfile[0x148]];
                actualromsize = romsizeconverterdict[romsize];
            else: romsize = "Unsupported";
            
            if headerfile[0x148] in romsizedict.keys():
                ramsize = ramsizedict[headerfile[0x149]];
                actualramsize = ramsizeconverterdict[ramsize];
            else: ramsize = "Unsupported";

            okdisabled = False;
            if "Unsupported" in (mbctouse,romsize,ramsize):
                okdisabled = True;

            
            checksum = self.calculatechecksum(headerfile);
            if headerfile[0x14D] == checksum:
                checkcolor = "green";
                warningvisible = False;
            else:
                checkcolor = "red";
                warningvisible = True;               
                      
            autodetectlayout = [
                [sg.Text("The following parameters were detected:") ],
                [sg.Text("Title/Manufacturer: "),sg.Input(titletext, readonly=True) ],
                [sg.Text("Cartridge MBC: "),sg.Input(actualmbc, readonly=True) ],
                [sg.Text("Interface to use: "),sg.Input(mbctouse, readonly=True) ],
                [sg.Text("ROM size: "), sg.Input(romsize, readonly=True)],
                [sg.Text("RAM size:"), sg.Input(ramsize,readonly=True)],
                [sg.Text("Header Checksum:"), sg.Input(checksum,readonly=True, text_color=checkcolor)],
                [sg.Push(),sg.Text("WARNING: Header Checksum failed", visible= warningvisible),sg.Push()],
                [sg.Push(),sg.Text("Data may be innacurate", visible= warningvisible),sg.Push()],
                [sg.VPush()],
                [sg.Push(),sg.Text("Use these parameters?"),sg.Push()],
                [sg.Button("OK",key="-AUTOOK-",disabled=okdisabled),sg.Push(),sg.Button("Cancel")],
                
            ];
            autodetectwindow = sg.Window("Autodetect",size=(380,350), layout=autodetectlayout, font="courier 10", modal=True);

            autoevent, autovalues = autodetectwindow.read();

            if autoevent == "-AUTOOK-":
                self.interfacecombo.update(value=mbctouse);
                self.romsizecombo.update(value=romsizeconverterdict[romsize]);
                self.ramsizecombo.update(value=ramsizeconverterdict[ramsize]);
                if self.carttypecombo.get() == "Squareboi":
                    self.targetICcombo.update(value="Select...", values=["SST","M29","RAM"], disabled=False);
                elif self.carttypecombo.get() == "DIP32 Socket":
                    self.targetICcombo.update(value="SST", values=["SST"], disabled=True);
                elif self.carttypecombo.get() == "Original Cartridge":
                    self.targetICcombo.update(value="Select...", values=["ROM","RAM"], disabled=False);
                

                
                self.window.refresh();
                

            autodetectwindow.close();
            
        except programmerException:
            self.logprint("Autodetect failure.");

            


    def update(self,timeout=None):
        event, values = self.window.read(timeout);

        ###If we're performing an operation:
        if self.busy:
            
            if event == "-FORCESTOP-":
                print("stop requested");
                self.logprint("Stop requested.");
                self.stoprequested = True;


        else:
            if event == sg.WINDOW_CLOSE_ATTEMPTED_EVENT:
                return 1;

            if event == "Open":
                filepath = sg.popup_get_file("Open",no_window = True);
                if filepath:
                    with open(filepath,'rb') as f:
                        self.workingfile = bytearray(f.read(8388608)); #Max of 8MB
                        self.analyzeROM(ntpath.basename(filepath));

            if event == "-CONNECT-":
                self.serialconnect();

            if event == "-AUTODETECT-":
                if self.serialconnected:
                    self.busyOn();
                    self.autodetect(values["-CARTTYPE-"]);
                    self.busyOff();
                else:
                    self.logprint("Programmer is not connected!");

            if event == "-CARTREAD-":
                self.cartread(values);


            if event == "-CARTWRITE-":
                self.cartwrite(values);        


            if event == "-CARTTYPE-":
                
                if values["-CARTTYPE-"] != "Select...":
                    self.detectbutton.update(disabled=False);

                if values["-CARTTYPE-"] == "Squareboi":
                    self.interfacecombo.update(value="Select...",values=["MBC1","MBC5"], disabled=False);
                    self.targetICcombo.update(value="Select...", disabled=True);
                elif values["-CARTTYPE-"] == "DIP32 Socket":
                    self.interfacecombo.update(value="DIP",values=["DIP"], disabled=True);
                    self.targetICcombo.update(value="SST",values=["SST"], disabled=True);
                elif values["-CARTTYPE-"] == "Original Cartridge":
                    self.interfacecombo.update(value="Select...",values=["MBC1","MBC5"], disabled=False);
                    self.targetICcombo.update(value="Select...", values=["ROM","RAM"], disabled=False);


            if event == "-INTERFACE-":
                if values["-CARTTYPE-"] == "Squareboi":
                    if values["-INTERFACE-"] == "MBC1":
                        self.targetICcombo.update(value="Select...", values=["SST","M29","RAM"], disabled=False);
                    elif values["-INTERFACE-"] == "MBC5":
                        self.targetICcombo.update(value="Select...", values=["SST","M29","RAM"], disabled=False);

            if event == "About...":
                aboutwindow = sg.Window("About...", layout=about_layout, font="courier 10", modal=True, element_justification="center");
                aboutwindow.read();
                aboutwindow.close();

            if event == "Correct Checksum":
                self.correctchecksum();
                    

                          
                    

        if event == "Save":
            if self.workingfile:
                filepath = sg.popup_get_file("Save as",no_window = True, save_as = True);
                if filepath:
                    with open(filepath,'wb') as f:
                        f.write(self.workingfile);
            else:
                self.logprint("No file loaded!");

        return 0;

    def terminate(self):
        self.window.close();


def main():

    pgm = progmanager();

    while True:
        if pgm.update():
            pgm.terminate();
            break;



if __name__ == "__main__":
    main();



