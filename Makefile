
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
SRC_DIR_MIDDLE										=	./0_Src/Middle
SRC_DIR_DRIVER										=	./0_Src/Driver
SRC_DIR_DRIVER_DRIVERSTM							=	./0_Src/Driver/DriverStm
SRC_DIR_DRIVER_DRIVERWATCHDOG						=	./0_Src/Driver/DriverWatchdog
SRC_DIR_DRIVER_DRIVERDIO							=	./0_Src/Driver/DriverDio
SRC_DIR_DRIVER_DRIVERADC							=	./0_Src/Driver/DriverAdc
SRC_DIR_DRIVER_DRIVERASC							=	./0_Src/Driver/DriverAsc
SRC_DIR_DRIVER_DRIVERGTM							=	./0_Src/Driver/DriverGtm
SRC_DIR_DRIVER_DRIVERTLF							= 	./0_Src/Driver/DriverTlf
SRC_DIR_DRIVER_DRIVERTLF_CFGILLD					=	./0_Src/Driver/DriverTlf/Cfg_Illd
SRC_DIR_DRIVER_DRIVERTLF_TFTAPP						= 	./0_Src/Driver/DriverTlf/TftApp
SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE_QSPI			= 	./0_Src/Driver/DriverTlf/CDrv/Tricore/Qspi
SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE_TFT			= 	./0_Src/Driver/DriverTlf/CDrv/Tricore/Tft
SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE				= 	./0_Src/Driver/DriverTlf/CDrv/Tricore

SRC_DIR_ADAPTION									= 	./0_Src/Adaption
SRC_DIR_ADAPTION_ADAPTIONDIO						= 	./0_Src/Adaption/AdaptionDio
SRC_DIR_SERVICE										=	./0_Src/Service
SRC_DIR_COMPONENT									=	./0_Src/Component
SRC_DIR_COMPONENT_DATAINTERFACE						=	./0_Src/Component/DataInterface

DEBUG_DIR			= ./Debug
EXE_DIR 			= $(DEBUG_DIR)/Exe
OBJ_DIR				= $(DEBUG_DIR)/Obj
#-----------------------------------------------------------------
#		Define include directorys to build
#-----------------------------------------------------------------    
INCLUDE 			+= $(SRC_DIR_APP)
INCLUDE 			+= $(SRC_DIR_APP_SCHEDULER)
INCLUDE 			+= $(SRC_DIR_MIDDLE)
INCLUDE 			+= $(SRC_DIR_DRIVER)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERSTM)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERWATCHDOG)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERDIO)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERADC)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERASC)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERGTM)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF_CFGILLD)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF_TFTAPP)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE_QSPI)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE_TFT)
INCLUDE 			+= $(SRC_DIR_DRIVER_DRIVERTLF_CDRV_TRICORE)
INCLUDE 			+= $(SRC_DIR_ADAPTION_ADAPTIONDIO)
INCLUDE 			+= $(SRC_DIR_COMPONENT_DATAINTERFACE)
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
APP_SOURCE				=	Ifx_InterfaceConst.c

APP_SOURCE				+= 	Main.c

# APP_SOURCE				+= 	Qspi0.c
# APP_SOURCE				+= 	conio_tft.c
# APP_SOURCE				+= 	fifo.c
# APP_SOURCE				+= 	font_8_12.c
# APP_SOURCE				+= 	libtft_ascii.c
# APP_SOURCE				+= 	libtft_graphics.c
# APP_SOURCE				+= 	tfthw.c
# APP_SOURCE				+= 	touch.c

# APP_SOURCE				+= 	background_light.c
# APP_SOURCE				+= 	basebar.c
# APP_SOURCE				+= 	display_io.c
# APP_SOURCE				+= 	DrawLogo.c
# APP_SOURCE				+= 	keyboard.c
# APP_SOURCE				+= 	menu.c
# APP_SOURCE				+= 	Perf_Meas.c
# APP_SOURCE				+= 	tft_app.c
APP_SOURCE				+= 	Scheduler.c

APP_SOURCE				+= 	Comp_ComplexInterface.c

APP_SOURCE				+= 	Adapt_Dio.c

APP_SOURCE				+= 	DrvSys.c
APP_SOURCE				+= 	DrvWatchdog.c
APP_SOURCE				+= 	DrvStm.c
APP_SOURCE				+= 	DrvDio.c
APP_SOURCE				+= 	DrvAdc.c
APP_SOURCE				+= 	DrvAsc.c
APP_SOURCE				+= 	DrvGtmTom.c
# APP_SOURCE				+= 	DrvTlf.c

APP_SOURCE				+= 	MidStm.c

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
.PHONY: dir all build clean 

all: dir build

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