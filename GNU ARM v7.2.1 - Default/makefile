################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth/lib/EFR32MG21/GCC/subdir.mk
-include platform/service/sleeptimer/src/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/emdrv/nvm3/src/subdir.mk
-include platform/Device/SiliconLabs/MGM21/Source/GCC/subdir.mk
-include platform/Device/SiliconLabs/MGM21/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include app/bluetooth/common/util/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: soc-peripherals-on-MGM210P032.axf

# Tool invocations
soc-peripherals-on-MGM210P032.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\mgm210p032jia.ld" -Xlinker --gc-sections -Xlinker -Map="soc-peripherals-on-MGM210P032.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o soc-peripherals-on-MGM210P032.axf -Wl,--start-group "./app/bluetooth/common/util/infrastructure.o" "./app.o" "./application_properties.o" "./gatt_db.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./interrupt_usart_2.o" "./main.o" "./peripheral_utils.o" "./pti.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/i2cspm.o" "./hardware/kit/common/drivers/retargetio.o" "./hardware/kit/common/drivers/retargetserial.o" "./platform/Device/SiliconLabs/MGM21/Source/GCC/startup_mgm21.o" "./platform/Device/SiliconLabs/MGM21/Source/system_mgm21.o" "./platform/emdrv/nvm3/src/nvm3_default.o" "./platform/emdrv/nvm3/src/nvm3_hal_flash.o" "./platform/emdrv/nvm3/src/nvm3_lock.o" "./platform/emdrv/sleep/src/sleep.o" "./platform/emlib/src/em_assert.o" "./platform/emlib/src/em_burtc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_core.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_crypto.o" "./platform/emlib/src/em_emu.o" "./platform/emlib/src/em_eusart.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_iadc.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rmu.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_se.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "./platform/service/sleeptimer/src/sl_sleeptimer.o" "./platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o" "./platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\protocol\bluetooth\lib\EFR32MG21\GCC\binapploader.o" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\autogen\librail_release\librail_config_mgm210p032jia_gcc.a" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\protocol\bluetooth\lib\EFR32MG21\GCC\libmbedtls.a" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\radio\rail_lib\autogen\librail_release\librail_module_efr32xg21_gcc_release.a" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\platform\emdrv\nvm3\lib\libnvm3_CM33_gcc.a" "D:\Study Material\Proj-on-GitHub\soc-peripherals-on-MGM210P032\protocol\bluetooth\lib\EFR32MG21\GCC\libbluetooth.a" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: soc-peripherals-on-MGM210P032.hex'
	arm-none-eabi-objcopy -O ihex "soc-peripherals-on-MGM210P032.axf" "soc-peripherals-on-MGM210P032.hex"
	@echo ' '

	@echo 'Building bin file: soc-peripherals-on-MGM210P032.bin'
	arm-none-eabi-objcopy -O binary "soc-peripherals-on-MGM210P032.axf" "soc-peripherals-on-MGM210P032.bin"
	@echo ' '

	@echo 'Building s37 file: soc-peripherals-on-MGM210P032.s37'
	arm-none-eabi-objcopy -O srec "soc-peripherals-on-MGM210P032.axf" "soc-peripherals-on-MGM210P032.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "soc-peripherals-on-MGM210P032.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) soc-peripherals-on-MGM210P032.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
