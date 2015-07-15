CROSS_TARGET=arm-none-eabi

# toolchain
CC=$(CROSS_TARGET)-gcc
CPP=$(CROSS_TARGET)-g++
LD=$(CROSS_TARGET)-ld
AS=$(CROSS_TARGET)-as
AR=$(CROSS_TARGET)-ar
OBJCOPY=$(CROSS_TARGET)-objcopy
OBJDUMP=$(CROSS_TARGET)-objdump
SIZE=$(CROSS_TARGET)-size
READELF=$(CROSS_TARGET)-readelf

PREFIX = $(shell which $(CC) | xargs dirname | sed "s/bin//")

CFLAGS  = -mfloat-abi=soft -mlittle-endian
CFLAGS += -nostartfiles -ffreestanding
CFLAGS += -O0 -mcpu=cortex-a7
CFLAGS += -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fno-rtti

LDFLAGS = $(shell $(CC) -print-search-dirs | grep libraries | sed -e "s/libraries\:\ =/-L/" | sed -e "s/\:/\ -L/g")
LDFLAGS += -lstdc++ -lsupc++ -lm -lc -lgcc

