################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/emdrv/sleep/src/sleep.c 

OBJS += \
./platform/emdrv/sleep/src/sleep.o 

C_DEPS += \
./platform/emdrv/sleep/src/sleep.d 


# Each subdirectory must supply rules for building sources it contributes
platform/emdrv/sleep/src/sleep.o: ../platform/emdrv/sleep/src/sleep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-D__StackLimit=0x20000000' '-D__HEAP_SIZE=0xD00' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__STACK_SIZE=0x800' '-DHAL_CONFIG=1' '-DMGM210P032JIA=1' -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\hardware\kit\common\bsp" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Source" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emlib\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emlib\src" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Include" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\CMSIS\Include" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\src" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\protocol\ble" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\hardware\kit\common\halconfig" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\protocol\bluetooth\ble_stack\inc\common" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\hardware\kit\common\drivers" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\common" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Source\GCC" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\nvm3\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\hardware\kit\MGM21_BRD4308A\config" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\chip\efr32\efr32xg2x" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\common\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\common\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\app\bluetooth\common\util" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\protocol\bluetooth\ble_stack\inc\soc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\hardware\module\config" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\nvm3\src" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\bootloader\api" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\uartdrv\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\gpiointerrupt\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\protocol\ieee802154" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\sleep\src" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\sleep\inc" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\config" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\halconfig\inc\hal-config" -I"D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\bootloader" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/emdrv/sleep/src/sleep.d" -MT"platform/emdrv/sleep/src/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


