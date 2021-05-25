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
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-D__StackLimit=0x20000000' '-D__HEAP_SIZE=0xD00' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__STACK_SIZE=0x800' '-DHAL_CONFIG=1' '-DMGM210P032JIA=1' -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\hardware\kit\common\bsp" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Source" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emlib\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emlib\src" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Include" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\CMSIS\Include" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\src" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\protocol\ble" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\hardware\kit\common\halconfig" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\hardware\kit\common\drivers" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\common" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\Device\SiliconLabs\MGM21\Source\GCC" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\nvm3\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\hardware\kit\MGM21_BRD4308A\config" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\chip\efr32\efr32xg2x" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\common\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\common\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\app\bluetooth\common\util" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\hardware\module\config" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\nvm3\src" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\bootloader\api" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\uartdrv\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\sleep\src" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\emdrv\sleep\inc" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\service\sleeptimer\config" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\halconfig\inc\hal-config" -I"C:\Users\madha\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032\platform\bootloader" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/emdrv/sleep/src/sleep.d" -MT"platform/emdrv/sleep/src/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


