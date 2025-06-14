NPROC=$(shell nproc)
SHELL:=/bin/bash

# clear the log file every boot
CLEAR_LOG_ON_BOOT = 0
# debug logging with xlog
DEBUG_XLOG = 1
# tweaks for the release build
#ALPHARELEASE = 0.10

LCDFONT_OFFSET=0x2260
LOADER_OFFSET=0x1500
LOADER_ADDR=0x80001500
LOADER_ADDR_MAX=0x80002180

MIPS=/opt/mips32-mti-elf/2019.09-03-2/bin/mips-mti-elf-

CC = $(MIPS)gcc
CXX = $(MIPS)g++
LD = $(MIPS)ld
OBJCOPY = $(MIPS)objcopy

CFLAGS := -EL -march=mips32 -mtune=mips32 -msoft-float
CFLAGS += -Os -G0 -mno-abicalls -fno-pic
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -I libs/libretro-common/include
# CFLAGS += -Wall
ifeq ($(CLEAR_LOG_ON_BOOT), 1)
CFLAGS += -DCLEAR_LOG_ON_BOOT=1
endif
ifeq ($(DEBUG_XLOG), 1)
CFLAGS += -DDEBUG_XLOG=1
endif

LDFLAGS := -EL -nostdlib -z max-page-size=32
LDFLAGS += --gc-sections
# needed for .text LMA = VMA
LDFLAGS += --build-id

CXX_LDFLAGS := -EL -march=mips32 -mtune=mips32 -msoft-float
CXX_LDFLAGS += -Wl,--gc-sections --static
CXX_LDFLAGS += -z max-page-size=32

# Set build directory
BUILD_DIR := build

# Source and object file locations
SRC_DIR := src
LD_DIR := linker_scripts
SCRIPTS_DIR := scripts

# Update object and output file locations
CORE_OBJS := $(addprefix $(BUILD_DIR)/,core_api.o lib.o debug.o video_sf2000.o)
LOADER_OBJS := $(addprefix $(BUILD_DIR)/,init.o main.o debug.o)

# Default target
ifneq ($(CORE),)
all: $(BUILD_DIR)/core_87000000 $(BUILD_DIR)/bisrv.asd install
else
all: $(BUILD_DIR)/bisrv.asd install
endif

# Ensure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile C source files from src/ to build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$*.o -c $(SRC_DIR)/$*.c

# Assemble .s source files from src/ to build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$*.o -c $(SRC_DIR)/$*.s

libretro_core:
	@$(call echo_i,"compiling $(CORE)")
	$(MAKE) -j$(NPROC) -C $(CORE) $(MAKEFILE) platform=sf2000

$(BUILD_DIR)/libretro_core.a: libretro_core | $(BUILD_DIR)
	cp $(CORE)/*.a $(BUILD_DIR)/libretro_core.a

libretro-common:
	@$(call echo_i,"compiling $@")
	$(MAKE) -j$(NPROC) -C libs/libretro-common

$(BUILD_DIR)/libretro-common.a: libretro-common | $(BUILD_DIR)
	cp -u libs/libretro-common/libretro-common.a $(BUILD_DIR)/libretro-common.a

$(BUILD_DIR)/core.elf: $(BUILD_DIR)/libretro_core.a $(BUILD_DIR)/libretro-common.a $(CORE_OBJS)
	@$(call echo_i,"compiling $@")
	$(CXX) -Wl,-Map=$@.map $(CXX_LDFLAGS) -e __core_entry__ -T$(LD_DIR)/core.ld $(LD_DIR)/bisrv_08_03-core.ld -o $@ \
		-Wl,--start-group $(CORE_OBJS) $(BUILD_DIR)/libretro_core.a $(BUILD_DIR)/libretro-common.a -lc -Wl,--end-group

$(BUILD_DIR)/core_87000000: $(BUILD_DIR)/core.elf
	$(OBJCOPY) -O binary -R .MIPS.abiflags -R .note.gnu.build-id -R ".rel*" $(BUILD_DIR)/core.elf $(BUILD_DIR)/core_87000000

$(BUILD_DIR)/loader.elf: $(LOADER_OBJS)
	@$(call echo_i,"compiling $(BUILD_DIR)/loader.elf")
	$(LD) -Map $(BUILD_DIR)/loader.elf.map $(LDFLAGS) -e __start -Ttext=$(LOADER_ADDR) $(LD_DIR)/bisrv_08_03.ld $(LOADER_OBJS) -o $(BUILD_DIR)/loader.elf

$(BUILD_DIR)/loader.bin: $(BUILD_DIR)/loader.elf
	$(Q)$(OBJCOPY) -O binary -j .text -j .rodata -j .data $(BUILD_DIR)/loader.elf $(BUILD_DIR)/loader.bin

$(BUILD_DIR)/bisrv.asd: $(BUILD_DIR)/loader.bin $(BUILD_DIR)/lcd_font.bin $(BUILD_DIR)/crc
	@$(call echo_i,"patching $(BUILD_DIR)/bisrv.asd")

# check that loader's .bss does not exceeds LOADER_ADDR_MAX
	@BSSEND=$(shell grep -w "_end =" $(BUILD_DIR)/loader.elf.map | awk '{print $$1}'); \
	if [ $$(($${BSSEND})) -gt $$(($(LOADER_ADDR_MAX))) ]; then \
		$(call echo_e,"error: loader is too big. \\n		bss ending $${BSSEND} exceeds $(LOADER_ADDR_MAX) by \\n		$$(( $${BSSEND} - $(LOADER_ADDR_MAX) )) bytes") ; \
		exit 1; \
	else \
		echo "bss ending $${BSSEND}. still $$(( $(LOADER_ADDR_MAX) - $${BSSEND} )) bytes left" ; \
	fi

# check that lcd_font.bin has the anticipated size
	@LCDFONT_SIZE=$(shell stat -c %s $(BUILD_DIR)/lcd_font.bin) ; \
	if [ $${LCDFONT_SIZE} -ne 672 ]; then \
		$(call echo_e,"error: lcd_font.bin size $${LCDFONT_SIZE}. should be 672") ; \
		exit 1; \
	fi

	$(Q)cp bisrv_08_03.asd $(BUILD_DIR)/bisrv.asd

	$(Q)dd if=$(BUILD_DIR)/loader.bin of=$(BUILD_DIR)/bisrv.asd bs=$$(($(LOADER_OFFSET))) seek=1 conv=notrunc 2>/dev/null

	dd if=$(BUILD_DIR)/lcd_font.bin of=$(BUILD_DIR)/bisrv.asd bs=$$(($(LCDFONT_OFFSET))) seek=1 conv=notrunc

	# note: this patch must match $(LOADER_ADDR)
	# jal run_gba -> jal 0x80001500
	printf "\x40\x05\x00\x0C" | dd of=$(BUILD_DIR)/bisrv.asd bs=1 seek=$$((0x35a900)) conv=notrunc

	# endless loop in sys_watchdog_reboot -> j 0x80001508
	printf "\x42\x05\x00\x08" | dd of=$(BUILD_DIR)/bisrv.asd bs=1 seek=$$((0x30d4)) conv=notrunc
	# endless loop in INT_General_Exception_Hdlr -> j 0x80001510
	printf "\x44\x05\x00\x08" | dd of=$(BUILD_DIR)/bisrv.asd bs=1 seek=$$((0x495a0)) conv=notrunc

	# patch the buffer size for handling the save state snapshot image
	# \x0c (768k) would be enough up to cores displaying at 640x480x2
	printf "\x0c" | dd of=$(BUILD_DIR)/bisrv.asd bs=1 seek=$$((0x34f8b8)) conv=notrunc

	$(Q)$(BUILD_DIR)/crc $(BUILD_DIR)/bisrv.asd

$(BUILD_DIR)/lcd_font.bin: $(BUILD_DIR)/lcd_font.o
	$(OBJCOPY) -O binary -j ".rodata.lcd_font" $(BUILD_DIR)/lcd_font.o $(BUILD_DIR)/lcd_font.bin

$(BUILD_DIR)/crc: $(SRC_DIR)/crc.c | $(BUILD_DIR)
	gcc -o $(BUILD_DIR)/crc $(SRC_DIR)/crc.c

install:
	@$(call echo_i,"install to sdcard")
	-$(call copy_if_updated,$(BUILD_DIR)/bisrv.asd,sdcard/bios/bisrv.asd)
	-$(call copy_if_updated,$(BUILD_DIR)/core_87000000,sdcard/cores/$(CONSOLE)/core_87000000)
	# -rm -f sdcard/log.txt
	@$(call echo_d,"bisrv.asd")
	@$(call echo_d,"$(CORE)")

ifneq ($(ALPHARELEASE),)
updatelogo:
	@$(call echo_i,"update boot logo")
	-$(call update_bisrv_logo,sdcard/bios/bisrv.asd)
	@$(call echo_d,"$(1) logo updated")
else
updatelogo:
	@$(call echo_e,"ALPHARELEASE not defined!")
endif

# Clean intermediate files and the final executable
clean:
	-rm -rf $(BUILD_DIR)
ifneq ($(CORE),)
	$(MAKE) -j$(NPROC) -C $(CORE) $(MAKEFILE) clean platform=sf2000
endif

.PHONY: all clean

define echo_i
	echo -e "\033[1;33m$(1)\033[0m"
endef

define echo_e
	echo -e "\033[1;31m$(1)\033[0m"
endef

define echo_d
	echo -e "\033[1;37m$(1)\033[0m"
endef

define copy_if_updated
	diff -q $(1) $(2) || (rm -rf $$(dirname $(2)) && mkdir -p $$(dirname $(2)) && cp $(1) $(2) && echo "$(1) updated")
endef

define update_bisrv_logo
	printf "\xB8\x0B" | dd of=$(1) bs=1 seek=$$((0x3463d0)) conv=notrunc && \
	convert /home/adcockm/downloads/multicore_alpha_release/Multicore_Boot_Logo_-_Xmasprint_-_RGB565.png -gravity North -font helvetica -fill white -pointsize 14 -annotate +0+36 'version $(ALPHARELEASE)' /home/adcockm/downloads/multicore_alpha_release/versionlogo.png && \
	python3 /home/adcockm/downloads/multicore_alpha_release/bootlogo.py
endef
