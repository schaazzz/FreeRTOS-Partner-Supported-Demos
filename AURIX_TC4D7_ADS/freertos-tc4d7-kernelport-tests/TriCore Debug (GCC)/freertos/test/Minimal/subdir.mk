################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/test/Minimal/AbortDelay.c \
../freertos/test/Minimal/BlockQ.c \
../freertos/test/Minimal/EventGroupsDemo.c \
../freertos/test/Minimal/GenQTest.c \
../freertos/test/Minimal/IntQueue.c \
../freertos/test/Minimal/IntSemTest.c \
../freertos/test/Minimal/MessageBufferAMP.c \
../freertos/test/Minimal/MessageBufferDemo.c \
../freertos/test/Minimal/PollQ.c \
../freertos/test/Minimal/QPeek.c \
../freertos/test/Minimal/QueueOverwrite.c \
../freertos/test/Minimal/QueueSet.c \
../freertos/test/Minimal/QueueSetPolling.c \
../freertos/test/Minimal/StaticAllocation.c \
../freertos/test/Minimal/StreamBufferDemo.c \
../freertos/test/Minimal/StreamBufferInterrupt.c \
../freertos/test/Minimal/TaskNotify.c \
../freertos/test/Minimal/TaskNotifyArray.c \
../freertos/test/Minimal/TimerDemo.c \
../freertos/test/Minimal/blocktim.c \
../freertos/test/Minimal/countsem.c \
../freertos/test/Minimal/death.c \
../freertos/test/Minimal/dynamic.c \
../freertos/test/Minimal/flop.c \
../freertos/test/Minimal/integer.c \
../freertos/test/Minimal/recmutex.c \
../freertos/test/Minimal/semtest.c 

C_DEPS += \
./freertos/test/Minimal/AbortDelay.d \
./freertos/test/Minimal/BlockQ.d \
./freertos/test/Minimal/EventGroupsDemo.d \
./freertos/test/Minimal/GenQTest.d \
./freertos/test/Minimal/IntQueue.d \
./freertos/test/Minimal/IntSemTest.d \
./freertos/test/Minimal/MessageBufferAMP.d \
./freertos/test/Minimal/MessageBufferDemo.d \
./freertos/test/Minimal/PollQ.d \
./freertos/test/Minimal/QPeek.d \
./freertos/test/Minimal/QueueOverwrite.d \
./freertos/test/Minimal/QueueSet.d \
./freertos/test/Minimal/QueueSetPolling.d \
./freertos/test/Minimal/StaticAllocation.d \
./freertos/test/Minimal/StreamBufferDemo.d \
./freertos/test/Minimal/StreamBufferInterrupt.d \
./freertos/test/Minimal/TaskNotify.d \
./freertos/test/Minimal/TaskNotifyArray.d \
./freertos/test/Minimal/TimerDemo.d \
./freertos/test/Minimal/blocktim.d \
./freertos/test/Minimal/countsem.d \
./freertos/test/Minimal/death.d \
./freertos/test/Minimal/dynamic.d \
./freertos/test/Minimal/flop.d \
./freertos/test/Minimal/integer.d \
./freertos/test/Minimal/recmutex.d \
./freertos/test/Minimal/semtest.d 

OBJS += \
./freertos/test/Minimal/AbortDelay.o \
./freertos/test/Minimal/BlockQ.o \
./freertos/test/Minimal/EventGroupsDemo.o \
./freertos/test/Minimal/GenQTest.o \
./freertos/test/Minimal/IntQueue.o \
./freertos/test/Minimal/IntSemTest.o \
./freertos/test/Minimal/MessageBufferAMP.o \
./freertos/test/Minimal/MessageBufferDemo.o \
./freertos/test/Minimal/PollQ.o \
./freertos/test/Minimal/QPeek.o \
./freertos/test/Minimal/QueueOverwrite.o \
./freertos/test/Minimal/QueueSet.o \
./freertos/test/Minimal/QueueSetPolling.o \
./freertos/test/Minimal/StaticAllocation.o \
./freertos/test/Minimal/StreamBufferDemo.o \
./freertos/test/Minimal/StreamBufferInterrupt.o \
./freertos/test/Minimal/TaskNotify.o \
./freertos/test/Minimal/TaskNotifyArray.o \
./freertos/test/Minimal/TimerDemo.o \
./freertos/test/Minimal/blocktim.o \
./freertos/test/Minimal/countsem.o \
./freertos/test/Minimal/death.o \
./freertos/test/Minimal/dynamic.o \
./freertos/test/Minimal/flop.o \
./freertos/test/Minimal/integer.o \
./freertos/test/Minimal/recmutex.o \
./freertos/test/Minimal/semtest.o 


# Each subdirectory must supply rules for building sources it contributes
freertos/test/Minimal/%.o: ../freertos/test/Minimal/%.c freertos/test/Minimal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AURIX GCC Compiler'
	tricore-elf-gcc -std=c99 "@C:/Users/jinf/AURIX-v1.10.26-L-workspace/freertos-tc4d7-kernelport-tests/TriCore Debug (GCC)/AURIX_GCC_Compiler-Include_paths__-I_.opt" -Og -g3 -gdwarf-3 -Wall -c -fmessage-length=0 -fno-common -fstrict-volatile-bitfields -fdata-sections -ffunction-sections -mcpu=tc4DAx -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-freertos-2f-test-2f-Minimal

clean-freertos-2f-test-2f-Minimal:
	-$(RM) ./freertos/test/Minimal/AbortDelay.d ./freertos/test/Minimal/AbortDelay.o ./freertos/test/Minimal/BlockQ.d ./freertos/test/Minimal/BlockQ.o ./freertos/test/Minimal/EventGroupsDemo.d ./freertos/test/Minimal/EventGroupsDemo.o ./freertos/test/Minimal/GenQTest.d ./freertos/test/Minimal/GenQTest.o ./freertos/test/Minimal/IntQueue.d ./freertos/test/Minimal/IntQueue.o ./freertos/test/Minimal/IntSemTest.d ./freertos/test/Minimal/IntSemTest.o ./freertos/test/Minimal/MessageBufferAMP.d ./freertos/test/Minimal/MessageBufferAMP.o ./freertos/test/Minimal/MessageBufferDemo.d ./freertos/test/Minimal/MessageBufferDemo.o ./freertos/test/Minimal/PollQ.d ./freertos/test/Minimal/PollQ.o ./freertos/test/Minimal/QPeek.d ./freertos/test/Minimal/QPeek.o ./freertos/test/Minimal/QueueOverwrite.d ./freertos/test/Minimal/QueueOverwrite.o ./freertos/test/Minimal/QueueSet.d ./freertos/test/Minimal/QueueSet.o ./freertos/test/Minimal/QueueSetPolling.d ./freertos/test/Minimal/QueueSetPolling.o ./freertos/test/Minimal/StaticAllocation.d ./freertos/test/Minimal/StaticAllocation.o ./freertos/test/Minimal/StreamBufferDemo.d ./freertos/test/Minimal/StreamBufferDemo.o ./freertos/test/Minimal/StreamBufferInterrupt.d ./freertos/test/Minimal/StreamBufferInterrupt.o ./freertos/test/Minimal/TaskNotify.d ./freertos/test/Minimal/TaskNotify.o ./freertos/test/Minimal/TaskNotifyArray.d ./freertos/test/Minimal/TaskNotifyArray.o ./freertos/test/Minimal/TimerDemo.d ./freertos/test/Minimal/TimerDemo.o ./freertos/test/Minimal/blocktim.d ./freertos/test/Minimal/blocktim.o ./freertos/test/Minimal/countsem.d ./freertos/test/Minimal/countsem.o ./freertos/test/Minimal/death.d ./freertos/test/Minimal/death.o ./freertos/test/Minimal/dynamic.d ./freertos/test/Minimal/dynamic.o ./freertos/test/Minimal/flop.d ./freertos/test/Minimal/flop.o ./freertos/test/Minimal/integer.d ./freertos/test/Minimal/integer.o ./freertos/test/Minimal/recmutex.d ./freertos/test/Minimal/recmutex.o ./freertos/test/Minimal/semtest.d ./freertos/test/Minimal/semtest.o

.PHONY: clean-freertos-2f-test-2f-Minimal

