



GCC_BIN = C:/HolisticSystems/Sourcery_CodeBench_Lite_for_ARM_EABI/bin/
PROJECT = prova
MBED_TOOLS = C:/HolisticSystems/mbedDevelopmentTools/build
VPATH = $(MBED_TOOLS)/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard ./*.cpp ./src/*.cpp)) 
SYS_OBJECTS = cmsis_nvic.o sys.o startup_LPC17xx.o system_LPC17xx.o
INCLUDE_PATHS = -I. -I$(MBED_TOOLS)/mbed -I$(MBED_TOOLS)/rtos -I$(MBED_TOOLS)/usb -I$(MBED_TOOLS)/mbed/TARGET_LPC1768
LIBRARY_PATHS = -L$(MBED_TOOLS)/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM -L$(MBED_TOOLS)/rtos/LPC1768/GCC_ARM -L$(MBED_TOOLS)/usb/LPC1768/GCC_ARM
LIBRARIES = -lmbed -lrtos -lrtx -lUSBDevice
LINKER_SCRIPT = $(MBED_TOOLS)/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/LPC1768.ld
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
CPU = -mcpu=cortex-m3 -mthumb
CC_FLAGS = $(CPU) -c -Os -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections 
CC_SYMBOLS = -DTARGET_LPC1768 -DTOOLCHAIN_GCC_ARM -DNDEBUG -D__CORTEX_M3
LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections -u _printf_float -u _scanf_float
LD_SYS_LIBS = -lmbed -lstdc++ -lsupc++ -lm -lc -lgcc

all: $(PROJECT).bin

./$(PROJECT).bin:	./$(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

./$(PROJECT).elf:	$(OBJECTS) $(SYS_OBJECTS) 
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^  $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)



clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS)

.s.o:
	$(AS) $(CPU) -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++11 $(INCLUDE_PATHS) -o $@ $<


	
	
	
