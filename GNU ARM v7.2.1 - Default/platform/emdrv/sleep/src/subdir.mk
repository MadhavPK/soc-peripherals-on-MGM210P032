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
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-D__StackLimit=0x20000000' '-D__HEAP_SIZE=0xD00' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__STACK_SIZE=0x800' '-DHAL_CONFIG=1' '-DMGM210P032JIA=1' -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\hardware\kit\common\bsp" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\Device\SiliconLabs\MGM21\Source" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emlib\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emlib\src" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\Device\SiliconLabs\MGM21\Include" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\CMSIS\Include" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\service\sleeptimer\src" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\radio\rail_lib\protocol\ble" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\hardware\kit\common\halconfig" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\protocol\bluetooth\ble_stack\inc\common" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\hardware\kit\common\drivers" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\radio\rail_lib\common" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\Device\SiliconLabs\MGM21\Source\GCC" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\nvm3\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\hardware\kit\MGM21_BRD4308A\config" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\radio\rail_lib\chip\efr32\efr32xg2x" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\common\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\common\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\app\bluetooth\common\util" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\protocol\bluetooth\ble_stack\inc\soc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\hardware\module\config" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\service\sleeptimer\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\nvm3\src" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\bootloader\api" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\uartdrv\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\sleep\src" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\emdrv\sleep\inc" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\service\sleeptimer\config" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\halconfig\inc\hal-config" -I"C:\Users\z004emnf\SimplicityStudio\v4_workspace\soc-peripherals-on-MGM210P032_git\platform\bootloader" -O3 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/emdrv/sleep/src/sleep.d" -MT"platform/emdrv/sleep/src/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


