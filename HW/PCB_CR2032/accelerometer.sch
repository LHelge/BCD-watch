EESchema Schematic File Version 4
LIBS:PCB_CR2032-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2400 3600 0    50   Input ~ 0
SCL
Text HLabel 2400 3500 0    50   BiDi ~ 0
SDA
Text HLabel 4800 3450 2    50   Output ~ 0
WAKE_UP
$Comp
L PCB_CR2032:LIS2DW12 U3
U 1 1 5DC90EA6
P 2900 3500
F 0 "U3" H 3200 4050 50  0000 C CNN
F 1 "LIS2DW12" H 3300 3950 50  0000 C CNN
F 2 "Package_LGA:LGA-12_2x2mm_P0.5mm" H 3050 4050 50  0001 L CNN
F 3 "www.st.com/resource/en/datasheet/lis2hh12.pdf" H 2550 3500 50  0001 C CNN
F 4 "ST" H 2900 3500 50  0001 C CNN "Make"
F 5 "511-LIS2DW12TR" H 2900 3500 50  0001 C CNN "Mouser"
F 6 "LIS2DW12TR" H 2900 3500 50  0001 C CNN "Part"
	1    2900 3500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky_x2_KCom_AAK D?
U 1 1 5DCAA080
P 4500 3450
AR Path="/5DC4948F/5DCAA080" Ref="D?"  Part="1" 
AR Path="/5DC486A4/5DCAA080" Ref="D3"  Part="1" 
F 0 "D3" V 4546 3529 50  0000 L CNN
F 1 "BAR43CFILM" V 4455 3529 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 4500 3450 50  0001 C CNN
F 3 "~" H 4500 3450 50  0001 C CNN
F 4 "ST" H 4500 3450 50  0001 C CNN "Make"
F 5 "511-BAR43CFILM" H 4500 3450 50  0001 C CNN "Mouser"
F 6 "BAR43CFILM" H 4500 3450 50  0001 C CNN "Part"
	1    4500 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 3450 4800 3450
$Comp
L power:VDD #PWR028
U 1 1 5DCAE2F8
P 2950 2800
F 0 "#PWR028" H 2950 2650 50  0001 C CNN
F 1 "VDD" H 2967 2973 50  0000 C CNN
F 2 "" H 2950 2800 50  0001 C CNN
F 3 "" H 2950 2800 50  0001 C CNN
	1    2950 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR027
U 1 1 5DCAEA47
P 2900 4200
F 0 "#PWR027" H 2900 3950 50  0001 C CNN
F 1 "GND" H 2905 4027 50  0000 C CNN
F 2 "" H 2900 4200 50  0001 C CNN
F 3 "" H 2900 4200 50  0001 C CNN
	1    2900 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4000 2800 4100
Wire Wire Line
	2800 4100 2900 4100
Wire Wire Line
	3000 4100 3000 4000
Wire Wire Line
	2900 4000 2900 4100
Connection ~ 2900 4100
Wire Wire Line
	2900 4100 3000 4100
Wire Wire Line
	2900 4100 2900 4200
Wire Wire Line
	2900 3000 2900 2900
Wire Wire Line
	2900 2900 2950 2900
Wire Wire Line
	3000 2900 3000 3000
Wire Wire Line
	2950 2900 2950 2800
Connection ~ 2950 2900
Wire Wire Line
	2950 2900 3000 2900
$Comp
L power:VDD #PWR026
U 1 1 5DCB1169
P 2400 3200
F 0 "#PWR026" H 2400 3050 50  0001 C CNN
F 1 "VDD" H 2417 3373 50  0000 C CNN
F 2 "" H 2400 3200 50  0001 C CNN
F 3 "" H 2400 3200 50  0001 C CNN
	1    2400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3300 2400 3300
Wire Wire Line
	2400 3300 2400 3200
Wire Wire Line
	2500 3400 2400 3400
Wire Wire Line
	2400 3400 2400 3300
Connection ~ 2400 3300
Wire Wire Line
	2500 3500 2400 3500
Wire Wire Line
	2500 3600 2400 3600
Wire Wire Line
	3400 3400 3900 3400
Wire Wire Line
	3900 3400 3900 3050
Wire Wire Line
	3900 3050 4500 3050
Wire Wire Line
	4500 3050 4500 3150
Wire Wire Line
	3400 3500 3900 3500
Wire Wire Line
	3900 3500 3900 3850
Wire Wire Line
	3900 3850 4500 3850
Wire Wire Line
	4500 3850 4500 3750
$Comp
L Device:C C?
U 1 1 5DCB76AC
P 7950 2050
AR Path="/5DC1DE5A/5DCB76AC" Ref="C?"  Part="1" 
AR Path="/5DC486A4/5DCB76AC" Ref="C14"  Part="1" 
F 0 "C14" H 8065 2096 50  0000 L CNN
F 1 "100nF" H 8065 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7988 1900 50  0001 C CNN
F 3 "~" H 7950 2050 50  0001 C CNN
F 4 "Yageo" H 7950 2050 50  0001 C CNN "Make"
F 5 "603-CC805KRX7R9BB104" H 7950 2050 50  0001 C CNN "Mouser"
F 6 "CC0805KRX7R9BB104" H 7950 2050 50  0001 C CNN "Part"
	1    7950 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DCB76B5
P 7250 2050
AR Path="/5DC1DE5A/5DCB76B5" Ref="C?"  Part="1" 
AR Path="/5DC486A4/5DCB76B5" Ref="C13"  Part="1" 
F 0 "C13" H 7365 2096 50  0000 L CNN
F 1 "10uF 10V" H 7365 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7288 1900 50  0001 C CNN
F 3 "~" H 7250 2050 50  0001 C CNN
F 4 "Yageo" H 7250 2050 50  0001 C CNN "Make"
F 5 "CC0805KKX7R6BB106" H 7250 2050 50  0001 C CNN "Part"
F 6 "603-CC805KKX7R6BB106" H 7250 2050 50  0001 C CNN "Mouser"
	1    7250 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DCB76BB
P 7950 2300
AR Path="/5DC1DE5A/5DCB76BB" Ref="#PWR?"  Part="1" 
AR Path="/5DC486A4/5DCB76BB" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 7950 2050 50  0001 C CNN
F 1 "GND" H 7955 2127 50  0000 C CNN
F 2 "" H 7950 2300 50  0001 C CNN
F 3 "" H 7950 2300 50  0001 C CNN
	1    7950 2300
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5DCB76C1
P 7950 1800
AR Path="/5DC1DE5A/5DCB76C1" Ref="#PWR?"  Part="1" 
AR Path="/5DC486A4/5DCB76C1" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 7950 1650 50  0001 C CNN
F 1 "VDD" H 7967 1973 50  0000 C CNN
F 2 "" H 7950 1800 50  0001 C CNN
F 3 "" H 7950 1800 50  0001 C CNN
	1    7950 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DCB76C7
P 7250 2300
AR Path="/5DC1DE5A/5DCB76C7" Ref="#PWR?"  Part="1" 
AR Path="/5DC486A4/5DCB76C7" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 7250 2050 50  0001 C CNN
F 1 "GND" H 7255 2127 50  0000 C CNN
F 2 "" H 7250 2300 50  0001 C CNN
F 3 "" H 7250 2300 50  0001 C CNN
	1    7250 2300
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR?
U 1 1 5DCB76CD
P 7250 1800
AR Path="/5DC1DE5A/5DCB76CD" Ref="#PWR?"  Part="1" 
AR Path="/5DC486A4/5DCB76CD" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 7250 1650 50  0001 C CNN
F 1 "VDD" H 7267 1973 50  0000 C CNN
F 2 "" H 7250 1800 50  0001 C CNN
F 3 "" H 7250 1800 50  0001 C CNN
	1    7250 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1800 7250 1900
Wire Wire Line
	7250 2200 7250 2300
Wire Wire Line
	7950 2300 7950 2200
Wire Wire Line
	7950 1900 7950 1800
$EndSCHEMATC