# Чётные версии MINOR для коррекции орфографии и структуры кода.
# Нечётные версии MINOR для добавления кода и функционала.
# Версии PATCH ни на что не влияет.
MAJOR = 0
MINOR = 0
PATCH = 1

TARGET_MCU	:= attiny13a
TARGET_FCPU := 9600000

OUTPUT_NAME	:= AVR_makefile
HEX_NAME	:= firmware_
VERSION		:= $(MAJOR).$(MINOR).$(PATCH)
ELF			:= $(OUTPUT_NAME).elf
HEX			:= $(HEX_NAME)$(VERSION).hex

GXX_TARGET	:= -mmcu=$(TARGET_MCU) -DF_CPU=$(TARGET_FCPU)UL
GXX_FLAGS	:= -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -c

all: $(HEX)
	avr-size --format=berkeley $(ELF)
	rm ./Build/main.o $(ELF) $(LSS) $(MAP)
	@echo Finish: $@

./Build/main.o: ./Source/main.c Makefile
	avr-gcc $(GXX_FLAGS) $(GXX_TARGET) -o ./Build/main.o ./Source/main.c
	@echo Building: $@

$(ELF): ./Build/main.o
	avr-gcc -mmcu=$(TARGET_MCU) -o $(ELF) ./Build/main.o
	@echo Linking: $@

$(HEX): $(ELF)
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex $(ELF) $(HEX)
	@echo Create: $@

upload: $(HEX)
	@echo Upload $(TARGET_MCU)
	avrdude -v -p $(TARGET_MCU) -c usbasp -B 10 -u -U flash:w:$(HEX):a

clean:
	rm ./Build/*.o
	rm *.hex
	rm *.elf
