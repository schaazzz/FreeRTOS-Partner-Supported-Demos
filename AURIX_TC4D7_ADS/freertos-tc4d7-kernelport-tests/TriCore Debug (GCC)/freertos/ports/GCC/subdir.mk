################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/ports/GCC/port.c 

C_DEPS += \
./freertos/ports/GCC/port.d 

OBJS += \
./freertos/ports/GCC/port.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/ports/GCC/%.o: ../freertos/ports/GCC/%.c freertos/ports/GCC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-ports-2f-GCC

clean-freertos-2f-ports-2f-GCC:
	-$(RM) ./freertos/ports/GCC/port.d ./freertos/ports/GCC/port.o

.PHONY: clean-freertos-2f-ports-2f-GCC

