################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include host/port/usb/src/test/msd/subdir.mk
-include host/port/usb/src/systems/none/afs/subdir.mk
-include host/port/usb/src/systems/none/subdir.mk
-include host/port/usb/src/lib/subdir.mk
-include host/port/usb/src/functions/trans_fn/subdir.mk
-include host/port/usb/src/examples/msd/subdir.mk
-include host/port/usb/src/drivers/msd/subdir.mk
-include host/port/usb/src/cd/subdir.mk
-include host/port/common/bluetooth/subdir.mk
-include host/port/common/audio_out_interface/subdir.mk
-include host/port/common/subdir.mk
-include host/port/beken_no_os/pts/subdir.mk
-include host/port/beken_no_os/subdir.mk
-include host/port/beken_driver/subdir.mk
-include host/port/beken_app/subdir.mk
-include host/pkg/sbc/subdir.mk
-include host/libs/Mp3Lib/subdir.mk
-include host/libs/FatLib/subdir.mk
-include host/bluetooth/profile/spp/subdir.mk
-include controller/hal/beken/sys/subdir.mk
-include controller/hal/beken/hw/subdir.mk
-include controller/core/le/include/subdir.mk
-include controller/core/le/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
BA_SIZE_DISPLAY += \
ba-size-display \

BA_OBJCOPY_OUTPUT += \
BK3266_DM_Full_Func_designkit.bin \


# All Target
all: pre-build main-build

# Main-build Target
main-build: BK3266_DM_Full_Func_designkit.elf secondary-outputs

# Tool invocations
BK3266_DM_Full_Func_designkit.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: BA ELF GNU C linker'
	ba-elf-gcc -nostartfiles -L"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs" -L"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\AEC" -T ../ram.ld -flto -Os -G 100000 -march=ba2 -mle -o "BK3266_DM_Full_Func_designkit.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

ba-size-display: BK3266_DM_Full_Func_designkit.elf
	@echo 'Showing the size of executable'
	ba-elf-size -B BK3266_DM_Full_Func_designkit.elf
	@echo 'Finished building: $@'
	@echo ' '

BK3266_DM_Full_Func_designkit.bin: BK3266_DM_Full_Func_designkit.elf
	@echo 'Invoking: BA ELF GNU objcopy'
	ba-elf-objcopy -O binary BK3266_DM_Full_Func_designkit.elf  "BK3266_DM_Full_Func_designkit.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BA_SIZE_DISPLAY)$(OBJS)$(C_DEPS)$(SX_DEPS)$(S_DEPS)$(EXECUTABLES)$(BA_OBJCOPY_OUTPUT)$(S_UPPER_DEPS) BK3266_DM_Full_Func_designkit.elf
	-@echo ' '

pre-build:
	-rm -rf *.dmp *.map *.bin *.out *.elf *.txt *.IMG
	-@echo ' '

post-build:
	-./encrypt.bat
	-@echo ' '

secondary-outputs: $(BA_SIZE_DISPLAY) $(BA_OBJCOPY_OUTPUT)

.PHONY: all clean dependents
.SECONDARY: main-build pre-build post-build

-include ../makefile.targets
