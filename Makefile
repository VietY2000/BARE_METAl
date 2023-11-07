PRO_DIR := .
PATH_OUTPUT := bin
PROJ_NAME := bare_metal_stm32f4

SOURCE_DIR := ./src
INCLUDE_DIR := ./inc
SOURCE_FILE := $(foreach SOURCE_DIR, $(SOURCE_DIR), $(wildcard $(SOURCE_DIR)/*))
INCLUDE_FILE := $(foreach INCLUDE_DIR, $(INCLUDE_DIR), $(wildcard $(INCLUDE_DIR)/*))

COMPILER_DIR := C:/GNU_ARM/Tool/bin
FLASH_DIR := C:/STM32_Tool/bin
CC := $(COMPILER_DIR)/arm-none-eabi-gcc

LD := $(COMPILER_DIR)/arm-none-eabi-ld
OBJCOPY := $(COMPILER_DIR)/arm-none-eabi-objcopy
LINKER_FILE := $(PRO_DIR)/linker/bare_metal_stm32f4.ld
FL := $(FLASH_DIR)/STM32_Programmer_CLI.exe

INCLUDE_DIR_OPT := $(foreach INCLUDE_DIR, $(INCLUDE_DIR), -I$(INCLUDE_DIR))

CFLAG := -mcpu=cortex-m4 -c -O0 -g -mfloat-abi=soft -std=gnu11 -mthumb $(INCLUDE_DIR_OPT)
LDFLAG := -T $(LINKER_FILE) -Map $(PATH_OUTPUT)/$(PROJ_NAME).map

OBJ_FILE := $(notdir $(SOURCE_FILE)) 
OBJ_FILE := $(subst .c,.o,$(OBJ_FILE)) 
PATH_OBJ := $(foreach OBJ_FILE, $(OBJ_FILE), $(PATH_OUTPUT)/$(OBJ_FILE))

vpath %.c $(SOURCE_DIR)
vpath %.h $(INCLUDE_DIR)

build: $(OBJ_FILE) $(LINKER_FILE)
	$(LD) $(LDFLAG) $(PATH_OBJ) -o $(PATH_OUTPUT)/$(PROJ_NAME).elf
	$(OBJCOPY) -O ihex "$(PATH_OUTPUT)/$(PROJ_NAME).elf" "$(PATH_OUTPUT)/$(PROJ_NAME).hex"
	$(OBJCOPY) -O binary "$(PATH_OUTPUT)/$(PROJ_NAME).elf" "$(PATH_OUTPUT)/$(PROJ_NAME).bin"
	@echo -----------------------------build OK-----------------------------

%.o: %.c $(INCLUDE_FILE)
	mkdir -p $(PATH_OUTPUT)
	$(CC) $(CFLAG) $< -o $(PATH_OUTPUT)/$@

flash: 
	$(FL) -c port=SWD -w "$(PATH_OUTPUT)/$(PROJ_NAME).hex" 0x0800000
	@echo -----------------------------flash OK-----------------------------

clean:
	rm -rf $(PATH_OUTPUT)