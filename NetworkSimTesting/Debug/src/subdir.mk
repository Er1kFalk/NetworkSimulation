################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EthernetHeaderTest.cpp \
../src/MainTester.cpp 

OBJS += \
./src/EthernetHeaderTest.o \
./src/MainTester.o 

CPP_DEPS += \
./src/EthernetHeaderTest.d \
./src/MainTester.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/erik/Documents/NetworkSimulation/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


