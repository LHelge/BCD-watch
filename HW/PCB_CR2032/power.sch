EESchema Schematic File Version 4
LIBS:PCB_CR2032-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 7
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
L Device:Battery_Cell BT?
U 1 1 5DC4CEDF
P 5200 3650
AR Path="/5DC4CEDF" Ref="BT?"  Part="1" 
AR Path="/5DC4948F/5DC4CEDF" Ref="BT1"  Part="1" 
F 0 "BT1" H 4900 3750 50  0000 L CNN
F 1 "CR2032" H 4850 3600 50  0000 L CNN
F 2 "BCD-watch:BAT-HLD-001-xx-OTL" V 5200 3710 50  0001 C CNN
F 3 "~" V 5200 3710 50  0001 C CNN
F 4 "Linx" H 5200 3650 50  0001 C CNN "Make"
F 5 "BAT-HLD-001" H 5200 3650 50  0001 C CNN "Part"
F 6 "712-BAT-HLD-001" H 5200 3650 50  0001 C CNN "Mouser"
	1    5200 3650
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5DC4CEE5
P 8700 1350
AR Path="/5DC4CEE5" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DC4CEE5" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 8700 1200 50  0001 C CNN
F 1 "VDD" H 8717 1523 50  0000 C CNN
F 2 "" H 8700 1350 50  0001 C CNN
F 3 "" H 8700 1350 50  0001 C CNN
	1    8700 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC4CEEB
P 5200 3950
AR Path="/5DC4CEEB" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DC4CEEB" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 5200 3700 50  0001 C CNN
F 1 "GND" H 5205 3777 50  0000 C CNN
F 2 "" H 5200 3950 50  0001 C CNN
F 3 "" H 5200 3950 50  0001 C CNN
	1    5200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5DC4CEFD
P 8700 1650
AR Path="/5DC4CEFD" Ref="#FLG?"  Part="1" 
AR Path="/5DC4948F/5DC4CEFD" Ref="#FLG02"  Part="1" 
F 0 "#FLG02" H 8700 1725 50  0001 C CNN
F 1 "PWR_FLAG" H 8700 1823 50  0000 C CNN
F 2 "" H 8700 1650 50  0001 C CNN
F 3 "~" H 8700 1650 50  0001 C CNN
	1    8700 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky_x2_KCom_AAK D1
U 1 1 5DC85BE1
P 6000 3350
F 0 "D1" H 6000 3566 50  0000 C CNN
F 1 "BAR43CFILM" H 6000 3475 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6000 3350 50  0001 C CNN
F 3 "~" H 6000 3350 50  0001 C CNN
F 4 "ST" H 6000 3350 50  0001 C CNN "Make"
F 5 "511-BAR43CFILM" H 6000 3350 50  0001 C CNN "Mouser"
F 6 "BAR43CFILM" H 6000 3350 50  0001 C CNN "Part"
	1    6000 3350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 5DC4CEF3
P 8300 1350
AR Path="/5DC4CEF3" Ref="#FLG?"  Part="1" 
AR Path="/5DC4948F/5DC4CEF3" Ref="#FLG01"  Part="1" 
F 0 "#FLG01" H 8300 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 8300 1523 50  0000 C CNN
F 2 "" H 8300 1350 50  0001 C CNN
F 3 "~" H 8300 1350 50  0001 C CNN
	1    8300 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3750 5200 3950
$Comp
L Device:R R27
U 1 1 5DC893D2
P 5450 3350
F 0 "R27" V 5350 3350 50  0000 C CNN
F 1 "10k" V 5450 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5380 3350 50  0001 C CNN
F 3 "~" H 5450 3350 50  0001 C CNN
F 4 "" H 5450 3350 50  0001 C CNN "Make"
F 5 "" H 5450 3350 50  0001 C CNN "Mouser"
F 6 "" H 5450 3350 50  0001 C CNN "Part"
F 7 "C25804" H 5450 3350 50  0001 C CNN "LCSC"
F 8 "0603WAF1002T5E" H 5450 3350 50  0001 C CNN "jlcpcb"
	1    5450 3350
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky_x2_KCom_AAK D2
U 1 1 5DC8B19F
P 6900 3250
F 0 "D2" H 6850 3500 50  0000 L CNN
F 1 "BAR43CFILM" H 6650 3400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6900 3250 50  0001 C CNN
F 3 "~" H 6900 3250 50  0001 C CNN
F 4 "ST" H 6900 3250 50  0001 C CNN "Make"
F 5 "511-BAR43CFILM" H 6900 3250 50  0001 C CNN "Mouser"
F 6 "BAR43CFILM" H 6900 3250 50  0001 C CNN "Part"
	1    6900 3250
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC8CE7C
P 6000 4150
AR Path="/5DC8CE7C" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DC8CE7C" Ref="#PWR024"  Part="1" 
F 0 "#PWR024" H 6000 3900 50  0001 C CNN
F 1 "GND" H 6005 3977 50  0000 C CNN
F 2 "" H 6000 4150 50  0001 C CNN
F 3 "" H 6000 4150 50  0001 C CNN
	1    6000 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DC8E511
P 8300 1650
AR Path="/5DC8E511" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DC8E511" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 8300 1400 50  0001 C CNN
F 1 "GND" H 8305 1477 50  0000 C CNN
F 2 "" H 8300 1650 50  0001 C CNN
F 3 "" H 8300 1650 50  0001 C CNN
	1    8300 1650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C12
U 1 1 5DC8EB7D
P 6000 3900
F 0 "C12" H 6118 3946 50  0000 L CNN
F 1 "11mF" H 6118 3855 50  0000 L CNN
F 2 "BCD-watch:CPH3225A" H 6038 3750 50  0001 C CNN
F 3 "~" H 6000 3900 50  0001 C CNN
F 4 "CPH3225A" H 6000 3900 50  0001 C CNN "Part"
F 5 "SII" H 6000 3900 50  0001 C CNN "Make"
F 6 "628-CPH3225A-2K" H 6000 3900 50  0001 C CNN "Mouser"
	1    6000 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 3550 6000 3650
Wire Wire Line
	6000 3650 6900 3650
Wire Wire Line
	6900 3650 6900 3550
Connection ~ 6000 3650
Wire Wire Line
	6000 3650 6000 3750
Wire Wire Line
	6900 2950 6900 2850
Wire Wire Line
	6900 2850 5200 2850
Wire Wire Line
	5200 2850 5200 3350
Wire Wire Line
	5300 3350 5200 3350
Connection ~ 5200 3350
Wire Wire Line
	5200 3350 5200 3450
Wire Wire Line
	5600 3350 5700 3350
NoConn ~ 6300 3350
$Comp
L power:VDD #PWR?
U 1 1 5DCA04C7
P 7200 3150
AR Path="/5DCA04C7" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DCA04C7" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 7200 3000 50  0001 C CNN
F 1 "VDD" H 7217 3323 50  0000 C CNN
F 2 "" H 7200 3150 50  0001 C CNN
F 3 "" H 7200 3150 50  0001 C CNN
	1    7200 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3250 7200 3250
Wire Wire Line
	7200 3250 7200 3150
Wire Wire Line
	6000 4150 6000 4050
Wire Wire Line
	8700 1650 8700 1350
Wire Wire Line
	8300 1650 8300 1350
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5DCE1F2A
P 6000 1600
F 0 "J3" H 5918 1275 50  0000 C CNN
F 1 "PWR" H 5918 1366 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" H 6000 1600 50  0001 C CNN
F 3 "~" H 6000 1600 50  0001 C CNN
	1    6000 1600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DCE2A7F
P 6300 1700
AR Path="/5DCE2A7F" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DCE2A7F" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 6300 1450 50  0001 C CNN
F 1 "GND" H 6305 1527 50  0000 C CNN
F 2 "" H 6300 1700 50  0001 C CNN
F 3 "" H 6300 1700 50  0001 C CNN
	1    6300 1700
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5DCE3453
P 6300 1400
AR Path="/5DCE3453" Ref="#PWR?"  Part="1" 
AR Path="/5DC4948F/5DCE3453" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 6300 1250 50  0001 C CNN
F 1 "VDD" H 6317 1573 50  0000 C CNN
F 2 "" H 6300 1400 50  0001 C CNN
F 3 "" H 6300 1400 50  0001 C CNN
	1    6300 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 1500 6300 1500
Wire Wire Line
	6300 1500 6300 1400
Wire Wire Line
	6200 1600 6300 1600
Wire Wire Line
	6300 1600 6300 1700
$EndSCHEMATC
