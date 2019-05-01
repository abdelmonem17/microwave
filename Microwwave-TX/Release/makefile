################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include HAL/keypad/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Microwwave-TX.lss \

FLASH_IMAGE += \
Microwwave-TX.hex \

EEPROM_IMAGE += \
Microwwave-TX.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Microwwave-TX.elf secondary-outputs

# Tool invocations
Microwwave-TX.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Microwwave-TX.map -mmcu=atmega16 -o "Microwwave-TX.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Microwwave-TX.lss: Microwwave-TX.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Microwwave-TX.elf  >"Microwwave-TX.lss"
	@echo 'Finished building: $@'
	@echo ' '

Microwwave-TX.hex: Microwwave-TX.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Microwwave-TX.elf  "Microwwave-TX.hex"
	@echo 'Finished building: $@'
	@echo ' '

Microwwave-TX.eep: Microwwave-TX.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Microwwave-TX.elf  "Microwwave-TX.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Microwwave-TX.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Microwwave-TX.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Microwwave-TX.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
