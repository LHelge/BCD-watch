BCDW_C_SRC = BCDw/hacks.c

BCDW_CPP_SRC = BCDw/BCDw.cpp \
			   BCDw/Debug.cpp \
			   BCDw/HAL/gpio.cpp \
			   BCDw/HAL/i2c.cpp \
			   BCDw/HAL/rtc.cpp \
			   BCDw/HAL/timer.cpp \
			   BCDw/HAL/uart.cpp \
			   BCDw/Drivers/lis3dh.cpp \
			   BCDw/Drivers/display.cpp 

BCDW_INC = BCDw \
           BCDw/HAL \
           BCDw/Drivers
