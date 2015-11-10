CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS  = -Wall
CFLAGS += -mcpu=cortex-m4
CFLAGS += -mlittle-endian
CFLAGS += -mthumb
CFLAGS += -DSTM32F407xx
CFLAGS += -Os
CFLAGS += -nostartfiles

LINKFLAGS  = -DSTM32F407xx
LINKFLAGS += -T./link/STM32F407VG_FLASH.ld
LINKFLAGS += -Wl,--gc-sections

INCLUDES  = -I./driver/cmsis/include
INCLUDES += -I./driver/hal/include
INCLUDES += -I./include

SRCS  = $(wildcard ./src/*.c)
CMSIS = $(wildcard ./driver/cmsis/src/*.c)
HAL   = $(wildcard ./driver/hal/src/*.c)
ASMS  = $(wildcard ./driver/cmsis/src/*.s)

OBJS = $(SRCS:.c=.o) $(CMSIS:.c=.o) $(HAL:.c=.o) $(ASMS:.s=.o)

NAME=image

.PHONY: depend clean

all: $(NAME).hex

$(NAME).hex: $(NAME).elf
	$(OBJCOPY) -Oihex $(NAME).elf $(NAME).hex

$(NAME).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LINKFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

.s.o:
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f $(OBJS)
	rm -f *.o
	rm -f *.elf
	rm -f *.hex
