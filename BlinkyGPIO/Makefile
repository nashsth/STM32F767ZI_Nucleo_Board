##########################################################################################################################
# Simplified Makefile for STM32F767ZI bare-metal programming using the GCC compiler
##########################################################################################################################

######################################
# target
######################################
TARGET = GPIO


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C source files
C_SOURCES =  \
Core/Src/main.c \
Core/Src/system_stm32f7xx.c \
Core/Src/syscalls.c \
Core/Src/sysmem.c \
Drivers/CustomHAL/Src/Custom_GPIO_HAL.c

# ASM source files
ASM_SOURCES =  \
startup_stm32f767xx.s

#######################################
# Toolchain and Compiler
#######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# CPU and architecture-specific settings
CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# C defines
C_DEFS =  \
-DSTM32F767xx

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/CMSIS/Device/ST/STM32F7xx/Include \
-IDrivers/CMSIS/Core/Include \
-IDrivers/CustomHAL/Include


# compile gcc flags
ASFLAGS = $(MCU) -Wall -fdata-sections -ffunction-sections $(OPT)
CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) -Wall -fdata-sections -ffunction-sections $(OPT)

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = stm32f767zitx_flash.ld

# libraries
LIBS = -lc -lm -lnosys -larm_cortexM7lfsp_math
LIBDIR = -LDrivers/CMSIS/Lib/GCC
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

#######################################
# build the application
#######################################

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(ASFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
