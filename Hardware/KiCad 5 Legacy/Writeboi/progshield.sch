EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Writeboi Programmer"
Date "2022-09-15"
Rev ""
Comp "ALXCO-Hardware"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Memory_Flash:SST39SF040 U1
U 1 1 61E45A49
P 7200 2750
F 0 "U1" H 6800 4350 50  0000 C CNN
F 1 "SST39SF040" H 6800 4200 50  0000 C CNN
F 2 "Socket:DIP_Socket-32_W11.9_W12.7_W15.24_W17.78_W18.5_3M_232-1285-00-0602J" H 7200 3050 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/25022B.pdf" H 7200 3050 50  0001 C CNN
	1    7200 2750
	1    0    0    -1  
$EndComp
$Comp
L GBprogparts:GB-CART J1
U 1 1 61E49431
P 10300 2500
F 0 "J1" H 10122 2553 60  0000 R CNN
F 1 "GB-CART" H 10122 2447 60  0000 R CNN
F 2 "Gekkio_Connector_PCBEdge:GameBoy_Cartridge_DMG_1x32_P1.50mm_Socket_Horizontal" H 10300 2500 60  0001 C CNN
F 3 "" H 10300 2500 60  0000 C CNN
	1    10300 2500
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 61E4B8E6
P 4400 2000
F 0 "#PWR0101" H 4400 1850 50  0001 C CNN
F 1 "+5V" H 4415 2173 50  0000 C CNN
F 2 "" H 4400 2000 50  0001 C CNN
F 3 "" H 4400 2000 50  0001 C CNN
	1    4400 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2250 4250 2250
Wire Wire Line
	4250 2350 4200 2350
Wire Wire Line
	4250 2450 4200 2450
Connection ~ 4250 2350
Wire Wire Line
	4250 2250 4400 2250
Connection ~ 4250 2250
$Comp
L Switch:SW_Push SW1
U 1 1 61E4D002
P 4500 3350
F 0 "SW1" H 4800 3550 50  0000 R CNN
F 1 "SW_Push" H 4900 3450 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H5mm" H 4500 3550 50  0001 C CNN
F 3 "~" H 4500 3550 50  0001 C CNN
	1    4500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3350 4300 3350
Text Label 6400 1550 0    50   ~ 0
A0
Text Label 6400 1650 0    50   ~ 0
A1
Text Label 6400 1750 0    50   ~ 0
A2
Text Label 6400 1850 0    50   ~ 0
A3
Text Label 6400 1950 0    50   ~ 0
A4
Text Label 6400 2050 0    50   ~ 0
A5
Text Label 6400 2150 0    50   ~ 0
A6
Text Label 6400 2250 0    50   ~ 0
A7
Text Label 6400 2350 0    50   ~ 0
A8
Text Label 6400 2450 0    50   ~ 0
A9
Text Label 6400 2550 0    50   ~ 0
A10
Text Label 6400 2650 0    50   ~ 0
A11
Text Label 6400 2750 0    50   ~ 0
A12
Text Label 6400 2850 0    50   ~ 0
A13
Text Label 6400 2950 0    50   ~ 0
A14
Text Label 6400 3050 0    50   ~ 0
A15
Text Label 6400 3150 0    50   ~ 0
A16
Text Label 6400 3250 0    50   ~ 0
A17
Text Label 6400 3350 0    50   ~ 0
A18
Text Label 6150 3750 0    50   ~ 0
DIP_CE_N
Text Label 6150 3550 0    50   ~ 0
DIP_WE_N
Text Label 6150 3850 0    50   ~ 0
DIP_OE_N
Text Label 8000 1550 2    50   ~ 0
D0
Text Label 8000 1650 2    50   ~ 0
D1
Text Label 8000 1750 2    50   ~ 0
D2
Text Label 8000 1850 2    50   ~ 0
D3
Text Label 8000 1950 2    50   ~ 0
D4
Text Label 8000 2050 2    50   ~ 0
D5
Text Label 8000 2150 2    50   ~ 0
D6
Text Label 8000 2250 2    50   ~ 0
D7
Wire Wire Line
	8000 2250 7800 2250
Wire Wire Line
	8000 2150 7800 2150
Wire Wire Line
	8000 2050 7800 2050
Wire Wire Line
	7800 1950 8000 1950
Wire Wire Line
	8000 1850 7800 1850
Wire Wire Line
	7800 1750 8000 1750
Wire Wire Line
	8000 1650 7800 1650
Wire Wire Line
	7800 1550 8000 1550
Wire Wire Line
	6150 3550 6600 3550
Wire Wire Line
	6150 3750 6600 3750
Wire Wire Line
	6150 3850 6600 3850
$Comp
L power:+5V #PWR0103
U 1 1 61E63E4B
P 9800 900
F 0 "#PWR0103" H 9800 750 50  0001 C CNN
F 1 "+5V" H 9815 1073 50  0000 C CNN
F 2 "" H 9800 900 50  0001 C CNN
F 3 "" H 9800 900 50  0001 C CNN
	1    9800 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 900  9800 950 
Wire Wire Line
	9800 950  10000 950 
$Comp
L power:+5V #PWR0104
U 1 1 61E65899
P 7200 900
F 0 "#PWR0104" H 7200 750 50  0001 C CNN
F 1 "+5V" H 7215 1073 50  0000 C CNN
F 2 "" H 7200 900 50  0001 C CNN
F 3 "" H 7200 900 50  0001 C CNN
	1    7200 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1450 7200 1050
$Comp
L Device:C C1
U 1 1 61E67995
P 7550 1050
F 0 "C1" V 7298 1050 50  0000 C CNN
F 1 "100n" V 7389 1050 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 7588 900 50  0001 C CNN
F 3 "~" H 7550 1050 50  0001 C CNN
	1    7550 1050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 61E687C0
P 7800 1150
F 0 "#PWR0105" H 7800 900 50  0001 C CNN
F 1 "GND" H 7805 977 50  0000 C CNN
F 2 "" H 7800 1150 50  0001 C CNN
F 3 "" H 7800 1150 50  0001 C CNN
	1    7800 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 1050 7800 1050
Wire Wire Line
	7800 1050 7800 1150
Wire Wire Line
	7400 1050 7200 1050
Connection ~ 7200 1050
Wire Wire Line
	7200 1050 7200 900 
$Comp
L power:GND #PWR0106
U 1 1 61E69BA4
P 7200 4050
F 0 "#PWR0106" H 7200 3800 50  0001 C CNN
F 1 "GND" H 7205 3877 50  0000 C CNN
F 2 "" H 7200 4050 50  0001 C CNN
F 3 "" H 7200 4050 50  0001 C CNN
	1    7200 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4050 7200 3950
Wire Wire Line
	6400 1550 6600 1550
Wire Wire Line
	6400 1650 6600 1650
Wire Wire Line
	6400 1750 6600 1750
Wire Wire Line
	6400 1850 6600 1850
Wire Wire Line
	6400 1950 6600 1950
Wire Wire Line
	6400 2050 6600 2050
Wire Wire Line
	6400 2150 6600 2150
Wire Wire Line
	6400 2250 6600 2250
Wire Wire Line
	6400 2350 6600 2350
Wire Wire Line
	6400 2450 6600 2450
Wire Wire Line
	6400 2550 6600 2550
Wire Wire Line
	6400 2650 6600 2650
Wire Wire Line
	6400 2750 6600 2750
Wire Wire Line
	6400 2850 6600 2850
Wire Wire Line
	6400 2950 6600 2950
Wire Wire Line
	6400 3050 6600 3050
Wire Wire Line
	6400 3150 6600 3150
Wire Wire Line
	6400 3250 6600 3250
Wire Wire Line
	6400 3350 6600 3350
Text Label 9800 1050 0    50   ~ 0
CLK
Text Label 9550 1150 0    50   ~ 0
CRT_WR_N
Text Label 9550 1250 0    50   ~ 0
CRT_RD_N
Text Label 9550 1350 0    50   ~ 0
CRT_CS_N
Text Label 9800 1450 0    50   ~ 0
A0
Text Label 9800 1550 0    50   ~ 0
A1
Text Label 9800 1650 0    50   ~ 0
A2
Text Label 9800 1750 0    50   ~ 0
A3
Text Label 9800 1850 0    50   ~ 0
A4
Text Label 9800 1950 0    50   ~ 0
A5
Text Label 9800 2050 0    50   ~ 0
A6
Text Label 9800 2150 0    50   ~ 0
A7
Text Label 9800 2250 0    50   ~ 0
A8
Text Label 9800 2350 0    50   ~ 0
A9
Text Label 9800 2450 0    50   ~ 0
A10
Text Label 9800 2550 0    50   ~ 0
A11
Text Label 9800 2650 0    50   ~ 0
A12
Text Label 9800 2750 0    50   ~ 0
A13
Text Label 9800 2850 0    50   ~ 0
A14
Text Label 9800 2950 0    50   ~ 0
A15
Text Label 9800 3050 0    50   ~ 0
D0
Text Label 9800 3150 0    50   ~ 0
D1
Text Label 9800 3250 0    50   ~ 0
D2
Text Label 9800 3350 0    50   ~ 0
D3
Text Label 9800 3450 0    50   ~ 0
D4
Text Label 9800 3550 0    50   ~ 0
D5
Text Label 9800 3650 0    50   ~ 0
D6
Text Label 9800 3750 0    50   ~ 0
D7
Text Label 9700 3850 0    50   ~ 0
RST_N
Text Label 9550 3950 0    50   ~ 0
CRT_PG_N
$Comp
L power:GND #PWR0107
U 1 1 61E7C167
P 9900 4100
F 0 "#PWR0107" H 9900 3850 50  0001 C CNN
F 1 "GND" H 9905 3927 50  0000 C CNN
F 2 "" H 9900 4100 50  0001 C CNN
F 3 "" H 9900 4100 50  0001 C CNN
	1    9900 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 4050 9900 4050
Wire Wire Line
	9550 3950 10000 3950
Wire Wire Line
	10000 3850 9700 3850
Wire Wire Line
	9800 3750 10000 3750
Wire Wire Line
	9800 3650 10000 3650
Wire Wire Line
	9800 3550 10000 3550
Wire Wire Line
	9800 3450 10000 3450
Wire Wire Line
	9800 3350 10000 3350
Wire Wire Line
	9800 3250 10000 3250
Wire Wire Line
	10000 3150 9800 3150
Wire Wire Line
	9800 3050 10000 3050
Wire Wire Line
	10000 2950 9800 2950
Wire Wire Line
	9800 2850 10000 2850
Wire Wire Line
	10000 2750 9800 2750
Wire Wire Line
	9800 2650 10000 2650
Wire Wire Line
	10000 2550 9800 2550
Wire Wire Line
	9800 2450 10000 2450
Wire Wire Line
	10000 2350 9800 2350
Wire Wire Line
	9800 2250 10000 2250
Wire Wire Line
	10000 2150 9800 2150
Wire Wire Line
	9800 2050 10000 2050
Wire Wire Line
	10000 1950 9800 1950
Wire Wire Line
	10000 1850 9800 1850
Wire Wire Line
	9800 1750 10000 1750
Wire Wire Line
	10000 1650 9800 1650
Wire Wire Line
	9800 1550 10000 1550
Wire Wire Line
	10000 1450 9800 1450
Wire Wire Line
	10000 1350 9550 1350
Wire Wire Line
	9550 1250 10000 1250
Wire Wire Line
	10000 1150 9550 1150
Wire Wire Line
	9800 1050 10000 1050
Wire Wire Line
	4400 2250 4400 2000
Text Label 4400 3750 2    50   ~ 0
CLK
Text Label 4650 3650 2    50   ~ 0
CRT_WR_N
Text Label 1150 2250 0    50   ~ 0
CRT_RD_N
Text Label 1150 2150 0    50   ~ 0
CRT_CS_N
Text Label 1400 5250 0    50   ~ 0
A0
Text Label 1400 5150 0    50   ~ 0
A1
Text Label 1400 5050 0    50   ~ 0
A2
Text Label 1400 4950 0    50   ~ 0
A3
Text Label 1400 4850 0    50   ~ 0
A4
Text Label 1400 4750 0    50   ~ 0
A5
Text Label 1400 4650 0    50   ~ 0
A6
Text Label 1400 4550 0    50   ~ 0
A7
Text Label 1400 4450 0    50   ~ 0
A8
Text Label 1400 4350 0    50   ~ 0
A9
Text Label 1400 4250 0    50   ~ 0
A10
Text Label 1400 4150 0    50   ~ 0
A11
Text Label 1400 4050 0    50   ~ 0
A12
Text Label 1400 3950 0    50   ~ 0
A13
Text Label 1400 3850 0    50   ~ 0
A14
Text Label 1400 3750 0    50   ~ 0
A15
Wire Wire Line
	1600 3750 1400 3750
Wire Wire Line
	1400 3850 1600 3850
Wire Wire Line
	1600 3950 1400 3950
Wire Wire Line
	1400 4050 1600 4050
Wire Wire Line
	1600 4150 1400 4150
Wire Wire Line
	1400 4250 1600 4250
Wire Wire Line
	1600 4350 1400 4350
Wire Wire Line
	1400 4450 1600 4450
Wire Wire Line
	1600 4550 1400 4550
Wire Wire Line
	1400 4650 1600 4650
Wire Wire Line
	1600 4750 1400 4750
Wire Wire Line
	1600 4850 1400 4850
Wire Wire Line
	1400 4950 1600 4950
Wire Wire Line
	1600 5050 1400 5050
Wire Wire Line
	1400 5150 1600 5150
Wire Wire Line
	1600 5250 1400 5250
Wire Wire Line
	1600 2150 1150 2150
Wire Wire Line
	1150 2250 1600 2250
Wire Wire Line
	4650 3650 4200 3650
Wire Wire Line
	4200 3750 4400 3750
$Comp
L Device:R R3
U 1 1 61FF7DA8
P 7400 5700
F 0 "R3" H 7470 5746 50  0000 L CNN
F 1 "20K" H 7470 5655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7330 5700 50  0001 C CNN
F 3 "~" H 7400 5700 50  0001 C CNN
	1    7400 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 61FF8C6E
P 7750 5700
F 0 "R4" H 7820 5746 50  0000 L CNN
F 1 "20K" H 7820 5655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7680 5700 50  0001 C CNN
F 3 "~" H 7750 5700 50  0001 C CNN
	1    7750 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 61FF9584
P 8050 5700
F 0 "R5" H 8120 5746 50  0000 L CNN
F 1 "20K" H 8120 5655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 7980 5700 50  0001 C CNN
F 3 "~" H 8050 5700 50  0001 C CNN
	1    8050 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 61FF9CD0
P 8350 5700
F 0 "R6" H 8420 5746 50  0000 L CNN
F 1 "100K" H 8420 5655 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8280 5700 50  0001 C CNN
F 3 "~" H 8350 5700 50  0001 C CNN
	1    8350 5700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 61FFA46B
P 7900 5450
F 0 "#PWR0108" H 7900 5300 50  0001 C CNN
F 1 "+5V" H 7915 5623 50  0000 C CNN
F 2 "" H 7900 5450 50  0001 C CNN
F 3 "" H 7900 5450 50  0001 C CNN
	1    7900 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 5550 7400 5500
Wire Wire Line
	7400 5500 7750 5500
Wire Wire Line
	7900 5500 7900 5450
Wire Wire Line
	7750 5550 7750 5500
Connection ~ 7750 5500
Wire Wire Line
	7750 5500 7900 5500
Wire Wire Line
	8050 5550 8050 5500
Wire Wire Line
	8050 5500 7900 5500
Connection ~ 7900 5500
Wire Wire Line
	8350 5550 8350 5500
Wire Wire Line
	8350 5500 8050 5500
Connection ~ 8050 5500
Text Label 8800 6000 2    50   ~ 0
RST_N
Wire Wire Line
	8350 5850 8350 6000
Text Label 8800 6100 2    50   ~ 0
DIP_WE_N
Text Label 8800 6200 2    50   ~ 0
DIP_CE_N
Text Label 8800 6300 2    50   ~ 0
DIP_OE_N
Wire Wire Line
	8050 5850 8050 6100
Wire Wire Line
	7750 5850 7750 6200
Wire Wire Line
	7400 5850 7400 6300
$Comp
L Device:LED D2
U 1 1 6203C4BA
P 6850 5400
F 0 "D2" V 6889 5282 50  0000 R CNN
F 1 "LED" V 6798 5282 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 6850 5400 50  0001 C CNN
F 3 "~" H 6850 5400 50  0001 C CNN
	1    6850 5400
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D1
U 1 1 6203D315
P 6450 5400
F 0 "D1" V 6489 5282 50  0000 R CNN
F 1 "LED" V 6398 5282 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 6450 5400 50  0001 C CNN
F 3 "~" H 6450 5400 50  0001 C CNN
	1    6450 5400
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 6203D678
P 6450 5800
F 0 "R1" H 6520 5846 50  0000 L CNN
F 1 "10K" H 6520 5755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6380 5800 50  0001 C CNN
F 3 "~" H 6450 5800 50  0001 C CNN
	1    6450 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6203DCD2
P 6850 5800
F 0 "R2" H 6920 5846 50  0000 L CNN
F 1 "10K" H 6920 5755 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6780 5800 50  0001 C CNN
F 3 "~" H 6850 5800 50  0001 C CNN
	1    6850 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5650 6450 5550
Wire Wire Line
	6850 5650 6850 5550
$Comp
L power:GND #PWR0109
U 1 1 6204BDF3
P 6650 6100
F 0 "#PWR0109" H 6650 5850 50  0001 C CNN
F 1 "GND" H 6655 5927 50  0000 C CNN
F 2 "" H 6650 6100 50  0001 C CNN
F 3 "" H 6650 6100 50  0001 C CNN
	1    6650 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5950 6450 6050
Wire Wire Line
	6450 6050 6650 6050
Wire Wire Line
	6650 6050 6650 6100
Wire Wire Line
	6850 5950 6850 6050
Wire Wire Line
	6850 6050 6650 6050
Connection ~ 6650 6050
Text Label 6150 5200 0    50   ~ 0
LED_RY
Text Label 6150 5000 0    50   ~ 0
LED_BY
Wire Wire Line
	6450 5200 6450 5250
Wire Wire Line
	6850 5000 6850 5250
Wire Wire Line
	6150 5200 6450 5200
Wire Wire Line
	6150 5000 6850 5000
Wire Wire Line
	8350 6000 8800 6000
Text Label 1400 5950 0    50   ~ 0
A18
Wire Wire Line
	1400 5950 1600 5950
Text Label 1400 5850 0    50   ~ 0
A16
Text Label 1400 5750 0    50   ~ 0
A17
Wire Wire Line
	1400 5850 1600 5850
Wire Wire Line
	1400 5750 1600 5750
Text Label 4700 6150 2    50   ~ 0
LED_RY
NoConn ~ 4200 6450
NoConn ~ 4200 6350
NoConn ~ 4200 5850
NoConn ~ 4200 5750
NoConn ~ 4200 6050
NoConn ~ 4200 5950
NoConn ~ 4200 5650
NoConn ~ 4200 5550
NoConn ~ 4200 5450
NoConn ~ 4200 5350
NoConn ~ 4200 5150
NoConn ~ 4200 5050
NoConn ~ 4200 4950
NoConn ~ 4200 4850
NoConn ~ 4200 4750
NoConn ~ 4200 4650
NoConn ~ 4200 4550
NoConn ~ 4200 4450
NoConn ~ 4200 4350
NoConn ~ 4200 4250
NoConn ~ 4200 4150
NoConn ~ 4200 4050
NoConn ~ 4200 3950
NoConn ~ 4200 3550
NoConn ~ 4200 3250
NoConn ~ 4200 2550
NoConn ~ 4200 2150
NoConn ~ 1600 6350
NoConn ~ 1600 6450
$Comp
L power:GND #PWR0110
U 1 1 620A54DA
P 5150 3150
F 0 "#PWR0110" H 5150 2900 50  0001 C CNN
F 1 "GND" H 5155 2977 50  0000 C CNN
F 2 "" H 5150 3150 50  0001 C CNN
F 3 "" H 5150 3150 50  0001 C CNN
	1    5150 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3050 4300 3050
Wire Wire Line
	5150 3050 5150 3150
Wire Wire Line
	4200 2950 4300 2950
Wire Wire Line
	4300 2950 4300 3050
Connection ~ 4300 3050
Wire Wire Line
	4300 3050 5050 3050
Wire Wire Line
	4200 2850 4300 2850
Wire Wire Line
	4300 2850 4300 2950
Connection ~ 4300 2950
Wire Wire Line
	4200 2750 4300 2750
Wire Wire Line
	4300 2750 4300 2850
Connection ~ 4300 2850
Wire Wire Line
	4200 2650 4300 2650
Wire Wire Line
	4300 2650 4300 2750
Connection ~ 4300 2750
Text Label 4700 6250 2    50   ~ 0
LED_BY
Wire Wire Line
	4200 6150 4700 6150
Wire Wire Line
	4200 6250 4700 6250
Wire Wire Line
	4250 2250 4250 2350
Wire Wire Line
	4250 2350 4250 2450
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 61EBFEAC
P 9800 5750
F 0 "J2" H 9880 5792 50  0000 L CNN
F 1 "AUX_POW" H 9880 5701 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-03A_1x03_P2.54mm_Vertical" H 9800 5750 50  0001 C CNN
F 3 "~" H 9800 5750 50  0001 C CNN
	1    9800 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0111
U 1 1 61EC0932
P 9400 5600
F 0 "#PWR0111" H 9400 5450 50  0001 C CNN
F 1 "+5V" H 9415 5773 50  0000 C CNN
F 2 "" H 9400 5600 50  0001 C CNN
F 3 "" H 9400 5600 50  0001 C CNN
	1    9400 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 61EC125B
P 9400 5950
F 0 "#PWR0112" H 9400 5700 50  0001 C CNN
F 1 "GND" H 9405 5777 50  0000 C CNN
F 2 "" H 9400 5950 50  0001 C CNN
F 3 "" H 9400 5950 50  0001 C CNN
	1    9400 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 5950 9400 5850
Wire Wire Line
	9400 5850 9600 5850
Wire Wire Line
	9400 5600 9400 5650
Wire Wire Line
	9400 5650 9600 5650
NoConn ~ 9600 5750
Text Label 1200 5650 0    50   ~ 0
DIP_WE_N
Text Label 1200 5550 0    50   ~ 0
DIP_OE_N
Text Label 1200 5450 0    50   ~ 0
DIP_CE_N
Wire Wire Line
	1200 5450 1600 5450
Wire Wire Line
	1200 5550 1600 5550
Wire Wire Line
	1600 5650 1200 5650
$Comp
L arduino:Arduino_Mega2560_ShieldNOSPI XA1
U 1 1 61E39D1E
P 2900 4300
F 0 "XA1" H 3000 1900 60  0000 R CNN
F 1 "Arduino_Mega2560_Shield" H 3500 1750 60  0000 R CNN
F 2 "Arduino:Arduino_Mega2560_Shield" H 3600 7050 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 3600 7050 60  0001 C CNN
	1    2900 4300
	-1   0    0    1   
$EndComp
Text Label 1400 3250 0    50   ~ 0
D0
Text Label 1400 3150 0    50   ~ 0
D1
Text Label 1400 3050 0    50   ~ 0
D2
Text Label 1400 2950 0    50   ~ 0
D3
Text Label 1400 2850 0    50   ~ 0
D4
Text Label 1400 2750 0    50   ~ 0
D5
Text Label 1400 2650 0    50   ~ 0
D6
Text Label 1400 2550 0    50   ~ 0
D7
Wire Wire Line
	1400 2550 1600 2550
Wire Wire Line
	1400 2650 1600 2650
Wire Wire Line
	1400 2750 1600 2750
Wire Wire Line
	1400 2850 1600 2850
Wire Wire Line
	1400 2950 1600 2950
Wire Wire Line
	1400 3050 1600 3050
Wire Wire Line
	1600 3150 1400 3150
Wire Wire Line
	1400 3250 1600 3250
Wire Wire Line
	1600 2450 1300 2450
Text Label 1300 2450 0    50   ~ 0
RST_N
Wire Wire Line
	4200 3850 4650 3850
Text Label 4650 3850 2    50   ~ 0
CRT_PG_N
Wire Wire Line
	4700 3350 5050 3350
Wire Wire Line
	5050 3350 5050 3050
Connection ~ 5050 3050
Wire Wire Line
	5050 3050 5150 3050
NoConn ~ 1600 3350
NoConn ~ 1600 3450
NoConn ~ 1600 3550
NoConn ~ 1600 3650
NoConn ~ 1600 6250
NoConn ~ 1600 6150
NoConn ~ 1600 6050
NoConn ~ 1600 5350
NoConn ~ 1600 2350
Wire Wire Line
	8050 6100 8800 6100
Wire Wire Line
	7750 6200 8800 6200
Wire Wire Line
	7400 6300 8800 6300
Text Notes 7200 4900 0    100  ~ 0
LEDs, Pullups Etc
Wire Notes Line
	5950 4550 10450 4550
Wire Notes Line
	10450 4550 10450 6400
Wire Notes Line
	10450 6400 5950 6400
Wire Notes Line
	5950 6400 5950 4550
Text Notes 8600 1000 0    100  ~ 0
Cartridge Slot
Text Notes 5850 1050 0    100  ~ 0
DIP Socket
Wire Notes Line
	5800 550  8200 550 
Wire Notes Line
	8200 550  8200 4350
Wire Notes Line
	8200 4350 5800 4350
Wire Notes Line
	5800 4350 5800 550 
Wire Notes Line
	8500 550  8500 4350
Wire Notes Line
	8500 4350 11000 4350
Wire Notes Line
	11000 4350 11000 550 
Wire Notes Line
	11000 550  8500 550 
Wire Wire Line
	9900 4050 9900 4100
Text Notes 1500 1650 0    100  ~ 0
Arduino
Wire Notes Line
	1000 1450 5400 1450
Wire Notes Line
	5400 1450 5400 7000
Wire Notes Line
	5400 7000 1000 7000
Wire Notes Line
	1000 7000 1000 1450
$EndSCHEMATC
