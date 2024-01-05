################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lcd_driver.c \
../gpio.c \
../keypad.c \
../main.c \
../timer1.c \
../uartf.c 

OBJS += \
./Lcd_driver.o \
./gpio.o \
./keypad.o \
./main.o \
./timer1.o \
./uartf.o 

C_DEPS += \
./Lcd_driver.d \
./gpio.d \
./keypad.d \
./main.d \
./timer1.d \
./uartf.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


