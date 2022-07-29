EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Memory_Flash:SST39SF040 U1
U 1 1 6238D7F1
P 1900 2250
F 0 "U1" H 1900 3731 50  0000 C CNN
F 1 "SST39SF040" H 1900 3640 50  0000 C CNN
F 2 "Package_DIP:DIP-32_W15.24mm_Socket_LongPads" H 1900 2550 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/25022B.pdf" H 1900 2550 50  0001 C CNN
	1    1900 2250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J1
U 1 1 62390622
P 1800 5350
F 0 "J1" H 1880 5342 50  0000 L CNN
F 1 "Conn_01x16" H 1880 5251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 1800 5350 50  0001 C CNN
F 3 "~" H 1800 5350 50  0001 C CNN
	1    1800 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J2
U 1 1 6239216A
P 2700 5450
F 0 "J2" H 2618 4425 50  0000 C CNN
F 1 "Conn_01x16" H 2618 4516 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 2700 5450 50  0001 C CNN
F 3 "~" H 2700 5450 50  0001 C CNN
	1    2700 5450
	-1   0    0    1   
$EndComp
Text Label 1350 4650 0    50   ~ 0
A18
Wire Wire Line
	1350 4650 1600 4650
Text Label 1350 4750 0    50   ~ 0
A16
Text Label 1350 4850 0    50   ~ 0
A15
Text Label 1350 4950 0    50   ~ 0
A12
Text Label 1350 5050 0    50   ~ 0
A7
Text Label 1350 5150 0    50   ~ 0
A6
Text Label 1350 5250 0    50   ~ 0
A5
Text Label 1350 5350 0    50   ~ 0
A4
Text Label 1350 5450 0    50   ~ 0
A3
Text Label 1350 5550 0    50   ~ 0
A2
Text Label 1350 5650 0    50   ~ 0
A1
Text Label 1350 5750 0    50   ~ 0
A0
Wire Wire Line
	1350 4750 1600 4750
Wire Wire Line
	1350 4850 1600 4850
Wire Wire Line
	1350 4950 1600 4950
Wire Wire Line
	1350 5050 1600 5050
Wire Wire Line
	1350 5150 1600 5150
Wire Wire Line
	1350 5250 1600 5250
Wire Wire Line
	1350 5350 1600 5350
Wire Wire Line
	1350 5450 1600 5450
Wire Wire Line
	1350 5550 1600 5550
Wire Wire Line
	1350 5650 1600 5650
Wire Wire Line
	1350 5750 1600 5750
Text Label 1350 5850 0    50   ~ 0
D0
Text Label 1350 5950 0    50   ~ 0
D1
Text Label 1350 6050 0    50   ~ 0
D2
$Comp
L power:GND #PWR0101
U 1 1 6239A500
P 1350 6250
F 0 "#PWR0101" H 1350 6000 50  0001 C CNN
F 1 "GND" H 1355 6077 50  0000 C CNN
F 2 "" H 1350 6250 50  0001 C CNN
F 3 "" H 1350 6250 50  0001 C CNN
	1    1350 6250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 6239AC50
P 3150 4550
F 0 "#PWR0102" H 3150 4400 50  0001 C CNN
F 1 "+5V" H 3165 4723 50  0000 C CNN
F 2 "" H 3150 4550 50  0001 C CNN
F 3 "" H 3150 4550 50  0001 C CNN
	1    3150 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4650 3150 4650
Wire Wire Line
	3150 4650 3150 4550
Wire Wire Line
	1600 6150 1350 6150
Wire Wire Line
	1350 6150 1350 6250
Wire Wire Line
	1350 6050 1600 6050
Wire Wire Line
	1350 5950 1600 5950
Wire Wire Line
	1350 5850 1600 5850
Text Label 3200 6150 2    50   ~ 0
D3
Text Label 3200 6050 2    50   ~ 0
D4
Text Label 3200 5950 2    50   ~ 0
D5
Text Label 3200 5850 2    50   ~ 0
D6
Text Label 3200 5750 2    50   ~ 0
D7
Text Label 3350 5650 2    50   ~ 0
ROMCS_N
Text Label 3200 5550 2    50   ~ 0
A10
Text Label 3350 5450 2    50   ~ 0
RD_N
Text Label 3200 5350 2    50   ~ 0
A11
Text Label 3200 5250 2    50   ~ 0
A9
Text Label 3200 5150 2    50   ~ 0
A8
Text Label 3200 5050 2    50   ~ 0
A13
Text Label 3200 4950 2    50   ~ 0
A14
Text Label 3200 4850 2    50   ~ 0
A17
Text Label 3200 4750 2    50   ~ 0
WR_N
Wire Wire Line
	3200 4750 2900 4750
Wire Wire Line
	3200 4850 2900 4850
Wire Wire Line
	3200 4950 2900 4950
Wire Wire Line
	3200 5050 2900 5050
Wire Wire Line
	3200 5150 2900 5150
Wire Wire Line
	3200 5250 2900 5250
Wire Wire Line
	3200 5350 2900 5350
Wire Wire Line
	3350 5450 2900 5450
Wire Wire Line
	3200 5550 2900 5550
Wire Wire Line
	3350 5650 2900 5650
Wire Wire Line
	3200 5750 2900 5750
Wire Wire Line
	3200 5850 2900 5850
Wire Wire Line
	3200 5950 2900 5950
Wire Wire Line
	3200 6050 2900 6050
Wire Wire Line
	3200 6150 2900 6150
$Comp
L power:GND #PWR0103
U 1 1 623A3083
P 1900 3550
F 0 "#PWR0103" H 1900 3300 50  0001 C CNN
F 1 "GND" H 1905 3377 50  0000 C CNN
F 2 "" H 1900 3550 50  0001 C CNN
F 3 "" H 1900 3550 50  0001 C CNN
	1    1900 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 623A38E5
P 2200 750
F 0 "#PWR0104" H 2200 600 50  0001 C CNN
F 1 "+5V" H 2215 923 50  0000 C CNN
F 2 "" H 2200 750 50  0001 C CNN
F 3 "" H 2200 750 50  0001 C CNN
	1    2200 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 950  2200 950 
Wire Wire Line
	2200 950  2200 750 
Wire Wire Line
	1900 3550 1900 3450
$Comp
L power:+5V #PWR0105
U 1 1 623A616F
P 3150 850
F 0 "#PWR0105" H 3150 700 50  0001 C CNN
F 1 "+5V" H 3165 1023 50  0000 C CNN
F 2 "" H 3150 850 50  0001 C CNN
F 3 "" H 3150 850 50  0001 C CNN
	1    3150 850 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 623A6571
P 3150 1300
F 0 "#PWR0106" H 3150 1050 50  0001 C CNN
F 1 "GND" H 3155 1127 50  0000 C CNN
F 2 "" H 3150 1300 50  0001 C CNN
F 3 "" H 3150 1300 50  0001 C CNN
	1    3150 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 623A7221
P 3150 1050
F 0 "C1" H 3265 1096 50  0000 L CNN
F 1 "C" H 3265 1005 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 3188 900 50  0001 C CNN
F 3 "~" H 3150 1050 50  0001 C CNN
	1    3150 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 850  3150 900 
Wire Wire Line
	3150 1200 3150 1300
Text Label 1100 1050 0    50   ~ 0
A0
Text Label 1100 1150 0    50   ~ 0
A1
Text Label 1100 1250 0    50   ~ 0
A2
Text Label 1100 1350 0    50   ~ 0
A3
Text Label 1100 1450 0    50   ~ 0
A4
Text Label 1100 1550 0    50   ~ 0
A5
Text Label 1100 1650 0    50   ~ 0
A6
Text Label 1100 1750 0    50   ~ 0
A7
Text Label 1100 1850 0    50   ~ 0
A8
Text Label 1100 1950 0    50   ~ 0
A9
Text Label 1100 2050 0    50   ~ 0
A10
Text Label 1100 2150 0    50   ~ 0
A11
Text Label 1100 2250 0    50   ~ 0
A12
Text Label 1100 2350 0    50   ~ 0
A13
Text Label 1100 2450 0    50   ~ 0
A14
Text Label 1100 2550 0    50   ~ 0
A15
Text Label 1100 2650 0    50   ~ 0
A16
Text Label 1100 2750 0    50   ~ 0
A17
Text Label 1100 2850 0    50   ~ 0
A18
Text Label 1100 3050 0    50   ~ 0
WR_N
Text Label 950  3250 0    50   ~ 0
ROMCS_N
Text Label 950  3350 0    50   ~ 0
RD_N
Text Label 2700 1050 2    50   ~ 0
D0
Text Label 2700 1150 2    50   ~ 0
D1
Text Label 2700 1250 2    50   ~ 0
D2
Text Label 2700 1350 2    50   ~ 0
D3
Text Label 2700 1450 2    50   ~ 0
D4
Text Label 2700 1550 2    50   ~ 0
D5
Text Label 2700 1650 2    50   ~ 0
D6
Text Label 2700 1750 2    50   ~ 0
D7
Wire Wire Line
	2700 1750 2500 1750
Wire Wire Line
	2700 1650 2500 1650
Wire Wire Line
	2700 1550 2500 1550
Wire Wire Line
	2500 1450 2700 1450
Wire Wire Line
	2700 1350 2500 1350
Wire Wire Line
	2700 1250 2500 1250
Wire Wire Line
	2500 1150 2700 1150
Wire Wire Line
	2700 1050 2500 1050
Wire Wire Line
	1300 3050 1100 3050
Wire Wire Line
	1100 2850 1300 2850
Wire Wire Line
	1300 2750 1100 2750
Wire Wire Line
	1100 2650 1300 2650
Wire Wire Line
	1300 2550 1100 2550
Wire Wire Line
	1100 2450 1300 2450
Wire Wire Line
	1300 2350 1100 2350
Wire Wire Line
	1100 2250 1300 2250
Wire Wire Line
	1300 2150 1100 2150
Wire Wire Line
	1100 2050 1300 2050
Wire Wire Line
	1300 1950 1100 1950
Wire Wire Line
	1100 1850 1300 1850
Wire Wire Line
	1300 1750 1100 1750
Wire Wire Line
	1100 1650 1300 1650
Wire Wire Line
	1300 1550 1100 1550
Wire Wire Line
	1100 1450 1300 1450
Wire Wire Line
	1300 1350 1100 1350
Wire Wire Line
	1100 1250 1300 1250
Wire Wire Line
	1300 1150 1100 1150
Wire Wire Line
	1100 1050 1300 1050
Wire Wire Line
	950  3250 1300 3250
Wire Wire Line
	950  3350 1300 3350
$EndSCHEMATC
