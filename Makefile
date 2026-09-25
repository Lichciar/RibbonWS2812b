# Чётные версии MINOR для коррекции орфографии и структуры кода.
# Нечётные версии MINOR для добавления кода и функционала.
# Версии PATCH ни на что не влияет.
MAJOR = 0
MINOR = 0
PATCH = 3

TARGET_MCU	:= atmega8
TARGET_FCPU := 8000000

OUTPUT_NAME	:= AVR_makefile
HEX_NAME	:= firmware_
VERSION		:= $(MAJOR).$(MINOR).$(PATCH)
ELF			:= $(OUTPUT_NAME).elf
HEX			:= $(HEX_NAME)$(VERSION).hex
ASM			:= firmware.asm

GXX_TARGET	:= -mmcu=$(TARGET_MCU) -DF_CPU=$(TARGET_FCPU)UL
GXX_FLAGS	:= -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -c

all: $(HEX)
	avr-size --format=berkeley $(ELF)
	rm ./Build/main.o ./Build/ws2812b.o $(ELF) $(LSS) $(MAP)
	@echo Finish: $@

./Build/main.o: ./Source/main.c Makefile
	avr-gcc $(GXX_FLAGS) $(GXX_TARGET) -o ./Build/main.o ./Source/main.c
	@echo Building: $@

./Build/ws2812b.o: ./Source/ws2812b.c Makefile
	avr-gcc $(GXX_FLAGS) $(GXX_TARGET) -o ./Build/ws2812b.o ./Source/ws2812b.c
	@echo Building: $@

$(ELF): ./Build/main.o ./Build/ws2812b.o
	avr-gcc -mmcu=$(TARGET_MCU) -o $(ELF) ./Build/main.o ./Build/ws2812b.o
	@echo Linking: $@

$(HEX): $(ELF)
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $(ELF) $(HEX)
	@echo Create: $@

upload: $(HEX)
	@echo Upload $(TARGET_MCU)
	avrdude -v -p $(TARGET_MCU) -c usbasp -B 10 -U flash:w:$(HEX):a

clean:
	rm ./Build/*.o
	rm *.hex
	rm *.elf

asm:
	avr-objdump -m avr -D $(HEX) > $(ASM)
