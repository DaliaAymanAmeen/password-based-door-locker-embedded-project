################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../eeprom.c \
../helper_functions.c \
../i2c.c \
../main.c \
../motor.c \
../timer.c \
../uart.c 

OBJS += \
./eeprom.o \
./helper_functions.o \
./i2c.o \
./main.o \
./motor.o \
./timer.o \
./uart.o 

C_DEPS += \
./eeprom.d \
./helper_functions.d \
./i2c.d \
./main.d \
./motor.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


