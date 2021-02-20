################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../host/port/common/bluetooth/Bt_a2dp_src_backend.c \
../host/port/common/bluetooth/bt_a2dp_backend.c \
../host/port/common/bluetooth/bt_app.c \
../host/port/common/bluetooth/bt_avrcp_backend.c \
../host/port/common/bluetooth/bt_cli_frontend.c \
../host/port/common/bluetooth/bt_hf_backend.c \
../host/port/common/bluetooth/bt_hid_backend.c \
../host/port/common/bluetooth/bt_hs_backend.c \
../host/port/common/bluetooth/bt_sco_backend_utils.c \
../host/port/common/bluetooth/bt_spp_backend.c \
../host/port/common/bluetooth/bt_unit_backend.c 

OBJS += \
./host/port/common/bluetooth/Bt_a2dp_src_backend.o \
./host/port/common/bluetooth/bt_a2dp_backend.o \
./host/port/common/bluetooth/bt_app.o \
./host/port/common/bluetooth/bt_avrcp_backend.o \
./host/port/common/bluetooth/bt_cli_frontend.o \
./host/port/common/bluetooth/bt_hf_backend.o \
./host/port/common/bluetooth/bt_hid_backend.o \
./host/port/common/bluetooth/bt_hs_backend.o \
./host/port/common/bluetooth/bt_sco_backend_utils.o \
./host/port/common/bluetooth/bt_spp_backend.o \
./host/port/common/bluetooth/bt_unit_backend.o 

C_DEPS += \
./host/port/common/bluetooth/Bt_a2dp_src_backend.d \
./host/port/common/bluetooth/bt_a2dp_backend.d \
./host/port/common/bluetooth/bt_app.d \
./host/port/common/bluetooth/bt_avrcp_backend.d \
./host/port/common/bluetooth/bt_cli_frontend.d \
./host/port/common/bluetooth/bt_hf_backend.d \
./host/port/common/bluetooth/bt_hid_backend.d \
./host/port/common/bluetooth/bt_hs_backend.d \
./host/port/common/bluetooth/bt_sco_backend_utils.d \
./host/port/common/bluetooth/bt_spp_backend.d \
./host/port/common/bluetooth/bt_unit_backend.d 


# Each subdirectory must supply rules for building sources it contributes
host/port/common/bluetooth/%.o: ../host/port/common/bluetooth/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: BA ELF GNU C compiler'
	ba-elf-gcc -DBA22_DEee -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avctp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\core" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\protocol\avdtp" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\le\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\FatLib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\Mp3Lib" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\bluetooth\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\config" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\pkg\sbc" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\jos\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_app" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_driver" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\beken_no_os" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\common\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\include\bluetooth" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\bt\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\dl\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\uslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lc\lslc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\lmp\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\tc\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\transport\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\core\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\hw\radio\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\hw\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\controller\hal\beken\sys\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\include\class" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\systems\none\afs" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\port\usb\src\drivers\msd" -I"D:\tech_prj_2020\20_1119_3266_¼Ñç÷\BK3266_DM_OTA_Full_Func_designkit_2020112001\BK3266_DM_OTA_Full_Func_designkit\host\libs\AEC" -O1 -flto -G 100000 -g3 -Wall -c -fmessage-length=0  -mno-hard-float -ffast-math -march=ba2 -mle -mabi=3 -mtj-rodata -msingle-float -mdsp -mmac -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


