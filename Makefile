
##################################################################
#											                     #
# 				  GCC MakeFile Version 1.0.0 			         #
#                                                                #
##################################################################
#-----------------------------------------------------------------
#		iLLD Sw Path 
#-----------------------------------------------------------------
include ./2_ILLD/Config/iLLD_Config.mk

#-----------------------------------------------------------------
#		Define Target 
#-----------------------------------------------------------------
TARGET	= TC237_SMARTCAR
TARGET_ELE_FILE	= ./Debug/Exe/$(TARGET).elf
TARGET_HEX_FILE = ./Debug/Exe/$(TARGET).hex
TARGET_BIN_FILE = ./Debug/Exe/$(TARGET).bin
TARGET_MAP_FILE = ./Debug/Exe/$(TARGET).map

#-----------------------------------------------------------------
#		Define core ofr the micro
#-----------------------------------------------------------------
MCPU = tc23xx

#-----------------------------------------------------------------
#		Use Gcc for arm compiler otherwise Gcc for c compiler
#-----------------------------------------------------------------
TCPREFIX 	= tricore
CC 			= $(TCPREFIX)-gcc
AS			= $(TCPREFIX)-gcc
LD 			= $(TCPREFIX)-gcc
OBJCOPY 	= $(TCPREFIX)-objcopy

#-----------------------------------------------------------------
#		Directorys of source to build
#-----------------------------------------------------------------
SRC_DIR_APP											=	./0_Src/App
SRC_DIR_APP_SCHEDULER								=	./0_Src/App/Scheduler
SRC_DIR_APP_EXEVERIFICATION							=	./0_Src/App/ExeVerification
SRC_DIR_MIDDLE										=	./0_Src/Middle
SRC_DIR_MIDDLE_TLF									= 	./0_Src/Middle/Tlf
SRC_DIR_MIDDLE_TLF_CFGILLD							=	./0_Src/Middle/Tlf/Cfg_Illd
SRC_DIR_MIDDLE_TLF_TFTAPP							= 	./0_Src/Middle/Tlf/TftApp
SRC_DIR_MIDDLE_TLF_CDRV_TRICORE_QSPI				= 	./0_Src/Middle/Tlf/CDrv/Tricore/Qspi
SRC_DIR_MIDDLE_TLF_CDRV_TRICORE_TFT					= 	./0_Src/Middle/Tlf/CDrv/Tricore/Tft
SRC_DIR_MIDDLE_TLF_CDRV_TRICORE						= 	./0_Src/Middle/Tlf/CDrv/Tricore
SRC_DIR_DRIVER										=	./0_Src/Driver

DEBUG_DIR			= ./Debug
EXE_DIR 			= $(DEBUG_DIR)/Exe
OBJ_DIR				= $(DEBUG_DIR)/Obj
#-----------------------------------------------------------------
#		Define include directorys to build
#-----------------------------------------------------------------    
INCLUDE 			+= $(SRC_DIR_APP)
INCLUDE 			+= $(SRC_DIR_APP_SCHEDULER)
INCLUDE 			+= $(SRC_DIR_APP_EXEVERIFICATION)
INCLUDE 			+= $(SRC_DIR_MIDDLE)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF_CFGILLD)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF_TFTAPP)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF_CDRV_TRICORE_QSPI)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF_CDRV_TRICORE_TFT)
INCLUDE 			+= $(SRC_DIR_MIDDLE_TLF_CDRV_TRICORE)
INCLUDE 			+= $(SRC_DIR_DRIVER)

#-----------------------------------------------------------------
#		Set search path
#-----------------------------------------------------------------
vpath % $(INCLUDE)

#-----------------------------------------------------------------
#		Gcc compiler option
#-----------------------------------------------------------------
CFLAGS 		= -mtc161
CFLAGS 		+= -g
CFLAGS 		+= -O1
CFLAGS 		+= -fno-common
CFLAGS 		+= -fstrict-volatile-bitfields
CFLAGS 		+= -ffunction-sections
CFLAGS 		+= -fdata-sections
CFLAGS 		+= -Wall
CFLAGS 		+= -std=c99
CFLAGS 		+= $(patsubst %,-I%,$(INCLUDE))
     
                          
#-----------------------------------------------------------------
#		Gcc assembler option
#-----------------------------------------------------------------
ASFLAGS		= $(CFLAGS);
      
#-----------------------------------------------------------------
#		Gcc Linker option
#-----------------------------------------------------------------
LDFLAGS		= -mtc161
LDFLAGS		+= -Wl,-Map,$(TARGET_MAP_FILE)
LDFLAGS		+= -Wl,--gc-sections
LDFLAGS		+= -Wl,-n
LDFLAGS		+= -T./1_ToolEnv/0_Build/1_Config/Config_Tricore_Gnuc/Lcf_Gnuc_Tricore_Tc.lsl

#-----------------------------------------------------------------
#		App Source files to build
#-----------------------------------------------------------------
APP_SOURCE				+= 	Main.c
APP_SOURCE				+= 	Scheduler.c
APP_SOURCE				+= 	ExeVerification.c

APP_SOURCE				+= 	MidStm.c

APP_SOURCE				+= 	DrvSys.c
APP_SOURCE				+= 	DrvWatchdog.c
APP_SOURCE				+= 	DrvStm.c
APP_SOURCE				+= 	DrvDio.c
APP_SOURCE				+= 	DrvAdc.c
APP_SOURCE				+= 	DrvAsc.c
APP_SOURCE				+= 	DrvGtmTom.c

APP_SOURCE				+= 	DrvTlf.c
APP_SOURCE				+= 	Qspi0.c
APP_SOURCE				+= 	conio_tft.c
APP_SOURCE				+= 	fifo.c
APP_SOURCE				+= 	font_8_12.c
APP_SOURCE				+= 	libtft_ascii.c
APP_SOURCE				+= 	libtft_graphics.c
APP_SOURCE				+= 	tfthw.c
APP_SOURCE				+= 	touch.c

APP_SOURCE				+= 	background_light.c
APP_SOURCE				+= 	basebar.c
APP_SOURCE				+= 	display_io.c
APP_SOURCE				+= 	DrawLogo.c
APP_SOURCE				+= 	keyboard.c
APP_SOURCE				+= 	menu.c
APP_SOURCE				+= 	Perf_Meas.c
APP_SOURCE				+= 	tft_app.c

APP_SOURCE_NAMES = $(notdir $(APP_SOURCE))
APP_BASE_NAMES	 = $(basename $(APP_SOURCE_NAMES))
APP_OBJECTS_NAMES = $(addsuffix .o, $(APP_BASE_NAMES))
APP_OBJECTS = $(addprefix $(OBJ_DIR)/, $(APP_OBJECTS_NAMES))
#-----------------------------------------------------------------
#		Define Rules (make objects)
#-----------------------------------------------------------------

$(OBJ_DIR)/%.o: %.s
	@$(CC) -mcpu=$(MCPU) -c -o $@ $(ASFLAGS) $<
	@echo $(notdir $@)
	
$(OBJ_DIR)/%.o: %.c
	@$(CC) -mcpu=$(MCPU) -c -o $@ $(CFLAGS) $<
	@echo $(notdir $@)	
#-----------------------------------------------------------------
#		Build targets
#-----------------------------------------------------------------
.PHONY: dir all build clean total

all: dir build

total: clean illd dir build

illd : 
	$(MAKE) -C 2_ILLD

dir: 
	@echo make dir...
	@if test ! -d $(DEBUG_DIR); then mkdir -p $(DEBUG_DIR);fi
	@if test ! -d $(EXE_DIR); then mkdir -p $(EXE_DIR);fi
	@if test ! -d $(OBJ_DIR); then mkdir -p $(OBJ_DIR);fi
		
build : $(APP_OBJECTS)
	@echo /****Linking Start****/
	@$(LD) -mcpu=$(MCPU) -o $(TARGET_ELE_FILE) $^ $(ILLD_OBJECTS) $(LDFLAGS) $(LIBS) 
	@$(OBJCOPY) -O binary $(TARGET_ELE_FILE) $(TARGET_BIN_FILE)
	@$(OBJCOPY) -O ihex $(TARGET_ELE_FILE) $(TARGET_HEX_FILE)
	@echo /****Linking Success****/

clean:
	@rm	-rf	$(OBJ_DIR)/*.o $(TARGET_ELE_FILE) $(TARGET_BIN_FILE) $(TARGET_MAP_FILE)
	@if test -d $(EXE_DIR); then rm -r $(EXE_DIR);fi
	@if test -d $(OBJ_DIR); then rm -r $(OBJ_DIR);fi
	@if test -d $(DEBUG_DIR); then rm -r $(DEBUG_DIR);fi