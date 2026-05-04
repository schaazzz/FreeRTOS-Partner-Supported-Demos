################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../middleware/retarget_io/retarget_io_uart.c 

C_DEPS += \
./middleware/retarget_io/retarget_io_uart.d 

OBJS += \
./middleware/retarget_io/retarget_io_uart.o 


# Each subdirectory must supply rules for building sources it contributes
middleware/retarget_io/%.o: ../middleware/retarget_io/%.c middleware/retarget_io/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-middleware-2f-retarget_io

clean-middleware-2f-retarget_io:
	-$(RM) ./middleware/retarget_io/retarget_io_uart.d ./middleware/retarget_io/retarget_io_uart.o

.PHONY: clean-middleware-2f-retarget_io

