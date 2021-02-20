################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../host/port/beken_driver/Main.c \
../host/port/beken_driver/bk3266_calibration.c \
../host/port/beken_driver/bootloader.c \
../host/port/beken_driver/driver_IrDA.c \
../host/port/beken_driver/driver_audio.c \
../host/port/beken_driver/driver_bk1080.c \
../host/port/beken_driver/driver_codec.c \
../host/port/beken_driver/driver_dma_fft.c \
../host/port/beken_driver/driver_dtmf.c \
../host/port/beken_driver/driver_flash.c \
../host/port/beken_driver/driver_gpio.c \
../host/port/beken_driver/driver_i2c.c \
../host/port/beken_driver/driver_i2s.c \
../host/port/beken_driver/driver_icu.c \
../host/port/beken_driver/driver_pwm.c \
../host/port/beken_driver/driver_ringbuff.c \
../host/port/beken_driver/driver_saradc.c \
../host/port/beken_driver/driver_sdadc.c \
../host/port/beken_driver/driver_sdcard.c \
../host/port/beken_driver/driver_serio.c \
../host/port/beken_driver/driver_spi.c \
../host/port/beken_driver/driver_usb.c \
../host/port/beken_driver/driver_usb_device.c \
../host/port/beken_driver/driver_usb_interrupt.c \
../host/port/beken_driver/driver_usb_standard_requests.c \
../host/port/beken_driver/target.c 

S_UPPER_SRCS += \
../host/port/beken_driver/boot_handler.S \
../host/port/beken_driver/boot_vectors.S 

OBJS += \
./host/port/beken_driver/Main.o \
./host/port/beken_driver/bk3266_calibration.o \
./host/port/beken_driver/boot_handler.o \
./host/port/beken_driver/boot_vectors.o \
./host/port/beken_driver/bootloader.o \
./host/port/beken_driver/driver_IrDA.o \
./host/port/beken_driver/driver_audio.o \
./host/port/beken_driver/driver_bk1080.o \
./host/port/beken_driver/driver_codec.o \
./host/port/beken_driver/driver_dma_fft.o \
./host/port/beken_driver/driver_dtmf.o \
./host/port/beken_driver/driver_flash.o \
./host/port/beken_driver/driver_gpio.o \
./host/port/beken_driver/driver_i2c.o \
./host/port/beken_driver/driver_i2s.o \
./host/port/beken_driver/driver_icu.o \
./host/port/beken_driver/driver_pwm.o \
./host/port/beken_driver/driver_ringbuff.o \
./host/port/beken_driver/driver_saradc.o \
./host/port/beken_driver/driver_sdadc.o \
./host/port/beken_driver/driver_sdcard.o \
./host/port/beken_driver/driver_serio.o \
./host/port/beken_driver/driver_spi.o \
./host/port/beken_driver/driver_usb.o \
./host/port/beken_driver/driver_usb_device.o \
./host/port/beken_driver/driver_usb_interrupt.o \
./host/port/beken_driver/driver_usb_standard_requests.o \
./host/port/beken_driver/target.o 

C_DEPS += \
./host/port/beken_driver/Main.d \
./host/port/beken_driver/bk3266_calibration.d \
./host/port/beken_driver/bootloader.d \
./host/port/beken_driver/driver_IrDA.d \
./host/port/beken_driver/driver_audio.d \
./host/port/beken_driver/driver_bk1080.d \
./host/port/beken_driver/driver_codec.d \
./host/port/beken_driver/driver_dma_fft.d \
./host/port/beken_driver/driver_dtmf.d \
./host/port/beken_driver/driver_flash.d \
./host/port/beken_driver/driver_gpio.d \
./host/port/beken_driver/driver_i2c.d \
./host/port/beken_driver/driver_i2s.d \
./host/port/beken_driver/driver_icu.d \
./host/port/beken_driver/driver_pwm.d \
./host/port/beken_driver/driver_ringbuff.d \
./host/port/beken_driver/driver_saradc.d \
./host/port/beken_driver/driver_sdadc.d \
./host/port/beken_driver/driver_sdcard.d \
./host/port/beken_driver/driver_serio.d \
./host/port/beken_driver/driver_spi.d \
./host/port/beken_driver/driver_usb.d \
./host/port/beken_driver/driver_usb_device.d \
./host/port/beken_driver/driver_usb_interrupt.d \
./host/port/beken_driver/driver_usb_standard_requests.d \
./host/port/beken_driver/target.d 

S_UPPER_DEPS += \
./host/port/beken_driver/boot_handler.d \
./host/port/beken_driver/boot_vectors.d 


# Each subdirectory must supply rules for building sources it contributes
host/port/beken_driver/%.o: ../host/port/beken_driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: BA ELF GNU C compiler'
	ba-elf-gcc -DBA22_DEee -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avctp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\core" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avdtp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\le\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\FatLib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\Mp3Lib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\config" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\pkg\sbc" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_app" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_driver" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_no_os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\bt\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\dl\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\uslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\lslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lmp\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\tc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\transport\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\radio\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include\class" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none\afs" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\drivers\msd" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\AEC" -O1 -flto -G 100000 -g3 -Wall -c -fmessage-length=0  -mno-hard-float -ffast-math -march=ba2 -mle -mabi=3 -mtj-rodata -msingle-float -mdsp -mmac -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

host/port/beken_driver/%.o: ../host/port/beken_driver/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: BA ELF GNU C compiler'
	ba-elf-gcc -DBA22_DEee -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avctp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\core" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avdtp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\le\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\FatLib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\Mp3Lib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\config" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\pkg\sbc" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_app" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_driver" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_no_os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\bt\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\dl\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\uslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\lslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lmp\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\tc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\transport\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\radio\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include\class" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none\afs" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\drivers\msd" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\AEC" -O1 -flto -G 100000 -g3 -Wall -c -fmessage-length=0  -mno-hard-float -ffast-math -march=ba2 -mle -mabi=3 -mtj-rodata -msingle-float -mdsp -mmac -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


