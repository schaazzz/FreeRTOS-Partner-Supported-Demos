################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/freertoskernel/croutine.c \
../freertos/freertoskernel/event_groups.c \
../freertos/freertoskernel/list.c \
../freertos/freertoskernel/queue.c \
../freertos/freertoskernel/stream_buffer.c \
../freertos/freertoskernel/tasks.c \
../freertos/freertoskernel/timers.c 

C_DEPS += \
./freertos/freertoskernel/croutine.d \
./freertos/freertoskernel/event_groups.d \
./freertos/freertoskernel/list.d \
./freertos/freertoskernel/queue.d \
./freertos/freertoskernel/stream_buffer.d \
./freertos/freertoskernel/tasks.d \
./freertos/freertoskernel/timers.d 

OBJS += \
./freertos/freertoskernel/croutine.o \
./freertos/freertoskernel/event_groups.o \
./freertos/freertoskernel/list.o \
./freertos/freertoskernel/queue.o \
./freertos/freertoskernel/stream_buffer.o \
./freertos/freertoskernel/tasks.o \
./freertos/freertoskernel/timers.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/freertoskernel/%.o: ../freertos/freertoskernel/%.c freertos/freertoskernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-freertoskernel

clean-freertos-2f-freertoskernel:
	-$(RM) ./freertos/freertoskernel/croutine.d ./freertos/freertoskernel/croutine.o ./freertos/freertoskernel/event_groups.d ./freertos/freertoskernel/event_groups.o ./freertos/freertoskernel/list.d ./freertos/freertoskernel/list.o ./freertos/freertoskernel/queue.d ./freertos/freertoskernel/queue.o ./freertos/freertoskernel/stream_buffer.d ./freertos/freertoskernel/stream_buffer.o ./freertos/freertoskernel/tasks.d ./freertos/freertoskernel/tasks.o ./freertos/freertoskernel/timers.d ./freertos/freertoskernel/timers.o

.PHONY: clean-freertos-2f-freertoskernel

