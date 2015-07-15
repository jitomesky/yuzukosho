include ./config.make

TARGET=mykernel

# linker script
LD_SCR  = library/linker.ld

# startup
#STARTUP= startup.o
# systemcall
#SYSCALL= syscalls.o
# mmu
#MMU = mmu.o

# library
LIB=libbmrpi.a

# source
OBJS  = main.o

CFLAGS+= -DBUILDING_RPIBOOT

INCLUDE = -Ilibrary/ -Ilibrary/cmsis/

all:	$(TARGET).bin

#$(TARGET).elf: $(STARTUP) $(OBJS) $(SYSCALL) $(LIB)
$(TARGET).elf: $(OBJS) $(LIB)
	$(LD) -static -nostartfiles -T $(LD_SCR) $^ -o $@ $(LDFLAGS)
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).disas
	$(SIZE) $(TARGET).elf > $(TARGET).size
	$(READELF) -a $(TARGET).elf > $(TARGET).readelf

.SUFFIXES: .elf .bin

libbmrpi.a: FORCE
	cd library; $(MAKE) libbmrpi.a; cd ..
	- cp library/libbmrpi.a libbmrpi.a

FORCE:

.elf.bin:
	$(OBJCOPY) -O binary $< $@
.c.o:
	$(CC) $(CFLAGS) -std=c99 $(INCLUDE) -c $< -o $@
.cpp.o:
	$(CC) $(CFLAGS) -std=c++98 $(INCLUDE) -c $< -o $@
.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean::
	$(RM) -f *.o *.bin *.elf */*.o */*/*.o 
	$(RM) -f tags *~ *.disas *.readelf *.size
	$(RM) -f libbcm2836.a
	cd library; make clean

tags::
	ctags *.[chS]


