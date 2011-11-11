# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./src/smartcopy.c \

OBJS += \
./src/smartcopy.o \

CPP_DEPS += \
./src/smartcopy.d \


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ./src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	gcc -I"/ffp/dev/projects" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
