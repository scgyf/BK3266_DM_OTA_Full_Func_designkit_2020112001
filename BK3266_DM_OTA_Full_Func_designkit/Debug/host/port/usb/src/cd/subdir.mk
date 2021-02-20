################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../host/port/usb/src/cd/mu_cntlr.c \
../host/port/usb/src/cd/mu_descs.c \
../host/port/usb/src/cd/mu_drc.c \
../host/port/usb/src/cd/mu_fadma.c \
../host/port/usb/src/cd/mu_fc.c \
../host/port/usb/src/cd/mu_fdr.c \
../host/port/usb/src/cd/mu_fun.c \
../host/port/usb/src/cd/mu_funex.c \
../host/port/usb/src/cd/mu_hc.c \
../host/port/usb/src/cd/mu_hdr.c \
../host/port/usb/src/cd/mu_hst.c \
../host/port/usb/src/cd/mu_list.c \
../host/port/usb/src/cd/mu_pip.c 

OBJS += \
./host/port/usb/src/cd/mu_cntlr.o \
./host/port/usb/src/cd/mu_descs.o \
./host/port/usb/src/cd/mu_drc.o \
./host/port/usb/src/cd/mu_fadma.o \
./host/port/usb/src/cd/mu_fc.o \
./host/port/usb/src/cd/mu_fdr.o \
./host/port/usb/src/cd/mu_fun.o \
./host/port/usb/src/cd/mu_funex.o \
./host/port/usb/src/cd/mu_hc.o \
./host/port/usb/src/cd/mu_hdr.o \
./host/port/usb/src/cd/mu_hst.o \
./host/port/usb/src/cd/mu_list.o \
./host/port/usb/src/cd/mu_pip.o 

C_DEPS += \
./host/port/usb/src/cd/mu_cntlr.d \
./host/port/usb/src/cd/mu_descs.d \
./host/port/usb/src/cd/mu_drc.d \
./host/port/usb/src/cd/mu_fadma.d \
./host/port/usb/src/cd/mu_fc.d \
./host/port/usb/src/cd/mu_fdr.d \
./host/port/usb/src/cd/mu_fun.d \
./host/port/usb/src/cd/mu_funex.d \
./host/port/usb/src/cd/mu_hc.d \
./host/port/usb/src/cd/mu_hdr.d \
./host/port/usb/src/cd/mu_hst.d \
./host/port/usb/src/cd/mu_list.d \
./host/port/usb/src/cd/mu_pip.d 


# Each subdirectory must supply rules for building sources it contributes
host/port/usb/src/cd/%.o: ../host/port/usb/src/cd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: BA ELF GNU C compiler'
	ba-elf-gcc -DBA22_DEee -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avctp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\core" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avdtp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\le\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\FatLib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\Mp3Lib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\config" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\pkg\sbc" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_app" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_driver" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_no_os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\bt\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\dl\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\uslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\lslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lmp\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\tc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\transport\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\radio\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include\class" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none\afs" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\drivers\msd" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\AEC" -O1 -flto -G 100000 -g3 -Wall -c -fmessage-length=0  -mno-hard-float -ffast-math -march=ba2 -mle -mabi=3 -mtj-rodata -msingle-float -mdsp -mmac -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


