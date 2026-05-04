################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include middleware/retarget_io/subdir.mk
-include freertos/test/Minimal/subdir.mk
-include freertos/ports/GCC/subdir.mk
-include freertos/freertoskernel/portable/MemMang/subdir.mk
-include freertos/freertoskernel/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/_PinMap/TC4Dx/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/_Impl/TC4Dx/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/_Impl/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Wtu/Std/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Vmt/Std/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Stm/Std/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Smu/Std/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Cpu/Trap/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Cpu/Std/subdir.mk
-include Libraries/iLLD/TC4xx/Tricore/Cpu/Irq/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/_PinMap/TC4Dx/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/_PinMap/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/_Lib/DataHandling/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/_Impl/TC4Dx/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/_Impl/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Src/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Port/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Geth/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Egtm/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Clock/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Asclin/Std/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Asclin/Asc/subdir.mk
-include Libraries/iLLD/TC4xx/CpuGeneric/Ap/Std/subdir.mk
-include Libraries/Service/CpuGeneric/SysSe/Time/subdir.mk
-include Libraries/Service/CpuGeneric/SysSe/Math/subdir.mk
-include Libraries/Service/CpuGeneric/SysSe/General/subdir.mk
-include Libraries/Service/CpuGeneric/SysSe/Comm/subdir.mk
-include Libraries/Service/CpuGeneric/SysSe/Bsp/subdir.mk
-include Libraries/Service/CpuGeneric/StdIf/subdir.mk
-include Libraries/Service/CpuGeneric/If/subdir.mk
-include Libraries/Infra/Ssw/TC4xx/Tricore/subdir.mk
-include Libraries/Infra/Platform/Compilers/subdir.mk
-include Libraries/Infra/Ipc/Tricore/ipc/src/subdir.mk
-include Configurations/subdir.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := freertos-tc4d7-kernelport-tests
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
freertos-tc4d7-kernelport-tests.hex \

SECONDARY_LIST += \
freertos-tc4d7-kernelport-tests.lst \

SECONDARY_SIZE += \
freertos-tc4d7-kernelport-tests.siz \


# All Target
all: main-build

# Main-build Target
main-build: freertos-tc4d7-kernelport-tests.elf secondary-outputs

# Tool invocations
freertos-tc4d7-kernelport-tests.elf: $(OBJS) ../Lcf_Gcc_Tricore_Tc.lsl makefile $(OPTIONAL_TOOL_DEPS) .freertos-tc4d7-kernelport-tests.elf.opt
	@echo 'Building target: $@'
	@echo 'Invoking: AURIX GCC Linker'
	tricore-elf-gcc @.freertos-tc4d7-kernelport-tests.elf.opt
	@echo 'Finished building target: $@'
	@echo ' '

.freertos-tc4d7-kernelport-tests.elf.opt:
	$(file >$@, -T"../Lcf_Gcc_Tricore_Tc.lsl" -nocrt0 -Wl,--gc-sections -mcpu=tc4DAx -o "freertos-tc4d7-kernelport-tests.elf" $(OBJS))

.PHONY: .freertos-tc4d7-kernelport-tests.elf.opt

freertos-tc4d7-kernelport-tests.hex: freertos-tc4d7-kernelport-tests.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Object Copy'
	tricore-elf-objcopy -O ihex "freertos-tc4d7-kernelport-tests.elf" "freertos-tc4d7-kernelport-tests.hex"
	@echo 'Finished building: $@'
	@echo ' '

freertos-tc4d7-kernelport-tests.lst: freertos-tc4d7-kernelport-tests.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Create Listing'
	tricore-elf-objdump -h -S "freertos-tc4d7-kernelport-tests.elf" > "freertos-tc4d7-kernelport-tests.lst"
	@echo 'Finished building: $@'
	@echo ' '

freertos-tc4d7-kernelport-tests.siz: freertos-tc4d7-kernelport-tests.elf makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: AURIX Print Size'
	tricore-elf-size  --format=berkeley "freertos-tc4d7-kernelport-tests.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) freertos-tc4d7-kernelport-tests.elf freertos-tc4d7-kernelport-tests.hex freertos-tc4d7-kernelport-tests.lst freertos-tc4d7-kernelport-tests.siz
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
