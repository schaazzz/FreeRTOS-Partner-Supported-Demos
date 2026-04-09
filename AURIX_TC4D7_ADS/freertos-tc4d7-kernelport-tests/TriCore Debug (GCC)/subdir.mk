################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../Cpu3_Main.c \
../Cpu4_Main.c \
../Cpu5_Main.c \
../IntQueueTimer.c \
../RegTests.c \
../TestRunner.c 

LSL_SRCS += \
../Lcf_Gcc_Tricore_Tc.lsl \
../Lcf_Hightec_Tricore_Tc.lsl \
../Lcf_Tasking_Tricore_Tc.lsl 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./Cpu3_Main.d \
./Cpu4_Main.d \
./Cpu5_Main.d \
./IntQueueTimer.d \
./RegTests.d \
./TestRunner.d 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./Cpu3_Main.o \
./Cpu4_Main.o \
./Cpu5_Main.o \
./IntQueueTimer.o \
./RegTests.o \
./TestRunner.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Cpu0_Main.d ./Cpu0_Main.o ./Cpu1_Main.d ./Cpu1_Main.o ./Cpu2_Main.d ./Cpu2_Main.o ./Cpu3_Main.d ./Cpu3_Main.o ./Cpu4_Main.d ./Cpu4_Main.o ./Cpu5_Main.d ./Cpu5_Main.o ./IntQueueTimer.d ./IntQueueTimer.o ./RegTests.d ./RegTests.o ./TestRunner.d ./TestRunner.o

.PHONY: clean--2e-

