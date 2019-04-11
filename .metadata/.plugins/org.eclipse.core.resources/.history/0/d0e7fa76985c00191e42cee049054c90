ifeq ($(OS),Windows_NT)
SHELL = cmd
RMDIR = rmdir /s /q
RM = del /q
mymkdir = if not exist "$1" mkdir "$1"
else
RMDIR = rm -fr
RM = rm -f
mymkdir = mkdir -p $1
endif

PROJECT_OBJS = \
	project/Funkcije.cpp.o \
	project/VarnostnaRazdalja.cpp.o \

PLATFORM_CORE_OBJS = \
	core/new.cpp.o \
	core/wiring_pulse.c.o \
	core/USBCore.cpp.o \
	core/HardwareSerial3.cpp.o \
	core/wiring_pulse.S.o \
	core/WString.cpp.o \
	core/wiring_analog.c.o \
	core/hooks.c.o \
	core/WInterrupts.c.o \
	core/wiring.c.o \
	core/IPAddress.cpp.o \
	core/main.cpp.o \
	core/HardwareSerial0.cpp.o \
	core/HardwareSerial2.cpp.o \
	core/HardwareSerial1.cpp.o \
	core/Tone.cpp.o \
	core/Print.cpp.o \
	core/abi.cpp.o \
	core/wiring_digital.c.o \
	core/HardwareSerial.cpp.o \
	core/PluggableUSB.cpp.o \
	core/WMath.cpp.o \
	core/CDC.cpp.o \
	core/wiring_shift.c.o \
	core/Stream.cpp.o \

PLATFORM_VARIANT_OBJS = \

LIBRARIES_OBJS = \
	libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp.o \
	libraries/Wire/src/Wire.cpp.o \
	libraries/Wire/src/utility/twi.c.o \
	libraries/Keypad/3.1.1/src/Key.cpp.o \
	libraries/Keypad/3.1.1/src/Keypad.cpp.o \

TARGETS = \
	VarnostnaRazdalja.hex \
	VarnostnaRazdalja.eep \

all: $(TARGETS)

VarnostnaRazdalja.hex: VarnostnaRazdalja.elf
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-objcopy" -O ihex -R .eeprom  "./VarnostnaRazdalja.elf" "./VarnostnaRazdalja.hex"

VarnostnaRazdalja.eep: VarnostnaRazdalja.elf
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "./VarnostnaRazdalja.elf" "./VarnostnaRazdalja.eep"

VarnostnaRazdalja.elf: $(PROJECT_OBJS) $(LIBRARIES_OBJS) core.a
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega2560  -o "./VarnostnaRazdalja.elf" $(PROJECT_OBJS) $(LIBRARIES_OBJS) "./core.a" "-L." -lm

core.a:	$(PLATFORM_CORE_OBJS) $(PLATFORM_VARIANT_OBJS)

clean:
	-$(RMDIR) project core variant libraries
	-$(RM) *.hex *.eep *.bin *.elf *.a *.ar *.d

size:
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-size" -A "./VarnostnaRazdalja.elf"

project/Funkcije.cpp.o: ../../Funkcije.cpp project/Funkcije.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

project/Funkcije.cpp.d: ;

-include project/Funkcije.cpp.d 

project/VarnostnaRazdalja.cpp.o: ../../VarnostnaRazdalja.cpp project/VarnostnaRazdalja.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

project/VarnostnaRazdalja.cpp.d: ;

-include project/VarnostnaRazdalja.cpp.d 


core/new.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/new.cpp core/new.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/new.cpp.d: ;

-include core/new.cpp.d

core/wiring_pulse.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_pulse.c core/wiring_pulse.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_pulse.c.d: ;

-include core/wiring_pulse.c.d

core/USBCore.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/USBCore.cpp core/USBCore.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/USBCore.cpp.d: ;

-include core/USBCore.cpp.d

core/HardwareSerial3.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial3.cpp core/HardwareSerial3.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial3.cpp.d: ;

-include core/HardwareSerial3.cpp.d

core/wiring_pulse.S.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_pulse.S
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -x assembler-with-cpp -flto -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WString.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WString.cpp core/WString.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WString.cpp.d: ;

-include core/WString.cpp.d

core/wiring_analog.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_analog.c core/wiring_analog.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_analog.c.d: ;

-include core/wiring_analog.c.d

core/hooks.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/hooks.c core/hooks.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/hooks.c.d: ;

-include core/hooks.c.d

core/WInterrupts.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WInterrupts.c core/WInterrupts.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/WInterrupts.c.d: ;

-include core/WInterrupts.c.d

core/wiring.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring.c core/wiring.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring.c.d: ;

-include core/wiring.c.d

core/IPAddress.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/IPAddress.cpp core/IPAddress.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/IPAddress.cpp.d: ;

-include core/IPAddress.cpp.d

core/main.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/main.cpp core/main.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/main.cpp.d: ;

-include core/main.cpp.d

core/HardwareSerial0.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial0.cpp core/HardwareSerial0.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial0.cpp.d: ;

-include core/HardwareSerial0.cpp.d

core/HardwareSerial2.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial2.cpp core/HardwareSerial2.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial2.cpp.d: ;

-include core/HardwareSerial2.cpp.d

core/HardwareSerial1.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial1.cpp core/HardwareSerial1.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial1.cpp.d: ;

-include core/HardwareSerial1.cpp.d

core/Tone.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Tone.cpp core/Tone.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Tone.cpp.d: ;

-include core/Tone.cpp.d

core/Print.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Print.cpp core/Print.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Print.cpp.d: ;

-include core/Print.cpp.d

core/abi.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/abi.cpp core/abi.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/abi.cpp.d: ;

-include core/abi.cpp.d

core/wiring_digital.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_digital.c core/wiring_digital.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_digital.c.d: ;

-include core/wiring_digital.c.d

core/HardwareSerial.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/HardwareSerial.cpp core/HardwareSerial.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/HardwareSerial.cpp.d: ;

-include core/HardwareSerial.cpp.d

core/PluggableUSB.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/PluggableUSB.cpp core/PluggableUSB.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/PluggableUSB.cpp.d: ;

-include core/PluggableUSB.cpp.d

core/WMath.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/WMath.cpp core/WMath.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/WMath.cpp.d: ;

-include core/WMath.cpp.d

core/CDC.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/CDC.cpp core/CDC.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/CDC.cpp.d: ;

-include core/CDC.cpp.d

core/wiring_shift.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/wiring_shift.c core/wiring_shift.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"
	
core/wiring_shift.c.d: ;

-include core/wiring_shift.c.d

core/Stream.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino/Stream.cpp core/Stream.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc-ar" rcs  "./core.a" "$@"

core/Stream.cpp.d: ;

-include core/Stream.cpp.d



libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp.o: /root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp.d: ;

-include libraries/LiquidCrystal_I2C/1.1.2/LiquidCrystal_I2C.cpp.d

libraries/Wire/src/Wire.cpp.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/Wire.cpp libraries/Wire/src/Wire.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

libraries/Wire/src/Wire.cpp.d: ;

-include libraries/Wire/src/Wire.cpp.d

libraries/Wire/src/utility/twi.c.o: /root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src/utility/twi.c libraries/Wire/src/utility/twi.c.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-gcc" -c -g -Os -w -std=gnu11 -ffunction-sections -fdata-sections -MMD -flto -fno-fat-lto-objects -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

libraries/Wire/src/utility/twi.c.d: ;

-include libraries/Wire/src/utility/twi.c.d

libraries/Keypad/3.1.1/src/Key.cpp.o: /root/.arduinocdt/libraries/Keypad/3.1.1/src/Key.cpp libraries/Keypad/3.1.1/src/Key.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

libraries/Keypad/3.1.1/src/Key.cpp.d: ;

-include libraries/Keypad/3.1.1/src/Key.cpp.d

libraries/Keypad/3.1.1/src/Keypad.cpp.o: /root/.arduinocdt/libraries/Keypad/3.1.1/src/Keypad.cpp libraries/Keypad/3.1.1/src/Keypad.cpp.d
	@$(call mymkdir,$(dir $@))
	"/root/.arduinocdt/packages/arduino/tools/avr-gcc/5.4.0-atmel3.6.1-arduino2/bin/avr-g++" -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10608 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR   -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/cores/arduino" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/variants/mega" -I"/root/.arduinocdt/libraries/LiquidCrystal_I2C/1.1.2" -I"/root/.arduinocdt/packages/arduino/hardware/avr/1.6.23/libraries/Wire/src" -I"/root/.arduinocdt/libraries/Keypad/3.1.1/src" "$<" -o "$@"

libraries/Keypad/3.1.1/src/Keypad.cpp.d: ;

-include libraries/Keypad/3.1.1/src/Keypad.cpp.d

