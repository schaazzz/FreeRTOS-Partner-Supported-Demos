################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertoskernel/portable/MemMang/heap_4.c 

C_DEPS += \
./freertos/freertoskernel/portable/MemMang/heap_4.d 

OBJS += \
./freertos/freertoskernel/portable/MemMang/heap_4.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertoskernel/portable/MemMang/%.o: ../freertos/freertoskernel/portable/MemMang/%.c freertos/freertoskernel/portable/MemMang/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertoskernel-2f-portable-2f-MemMang

clean-freertos-2f-freertoskernel-2f-portable-2f-MemMang:
	-$(RM) ./freertos/freertoskernel/portable/MemMang/heap_4.d ./freertos/freertoskernel/portable/MemMang/heap_4.o

.PHONY: clean-freertos-2f-freertoskernel-2f-portable-2f-MemMang

