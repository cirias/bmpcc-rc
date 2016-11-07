ARDUINO_VERSION = 1.6.10
ARDUINO_DIR = /usr/share/arduino
ARDMK_DIR = /usr/share/arduino
# AVR_TOOLS_DIR = /usr
ARDUINO_CORE_PATH = /usr/share/arduino/hardware/arduino/avr/cores/arduino
BOARDS_TXT = /usr/share/arduino/hardware/arduino/avr/boards.txt
ARDUINO_VAR_PATH = /usr/share/arduino/hardware/arduino/avr/variants
BOOTLOADER_PARENT = /usr/share/arduino/hardware/arduino/avr/bootloaders

ARDUINO_LIBS = PinChangeInterrupt

BOARD_TAG    = nano
BOARD_SUB = atmega328

CXXFLAGS_STD = -std=gnu++11

MONITOR_BAUDRATE = 115200

include ${ARDMK_DIR}/Arduino.mk
