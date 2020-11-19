#
#  Makefile to generate RISC-V binary for Computer Architecture class
#
#  Author: Prof. Taeweon Suh
#          Computer Science & Engineering
#	   College of Informatics
#          Korea University
#
#  Date:   2020-06-11
#

    HOME=../../riscv32i
    MIPSBIN=$(HOME)/bin
    AS=$(MIPSBIN)/riscv32-unknown-elf-as
    LD=$(MIPSBIN)/riscv32-unknown-elf-ld
	CC=$(MIPSBIN)/riscv32-unknown-elf-gcc
	CPP=$(MIPSBIN)/riscv32-unknown-elf-cpp        
    OBJDUMP=$(MIPSBIN)/riscv32-unknown-elf-objdump
    OBJCOPY=$(MIPSBIN)/riscv32-unknown-elf-objcopy
#   ASFLAGS= -Wall -O2 -g
#    ASFLAGS= -g -mips32
    ASFLAGS= -g -march=rv32i
    LDFLAGS= -N -X -Tlabcode.lds
    CCFLAGS= -c -g -march=rv32i
    
    all: labcode 

    labcode: m5.o SevenSeg.o
	$(LD) $(LDFLAGS)  m5.o SevenSeg.o -o labcode
	$(OBJDUMP) -xS  labcode > labcode.dump
	$(OBJCOPY) -O  binary labcode labcode.bin
	./bin2hex.perl > labcode.hex
	./hex2mif.perl
#	./mipsel-readelf -a labcode > labcode.r
#	./mipsel-nm labcode > labcode.n
	 
    m5.o: m5.s
	$(AS) $(ASFLAGS) m5.s -o m5.o
	
    SevenSeg.o:	SevenSeg.c
#	$(CPP) add.c > add.i
#	$(CC) -Wall -S add.i
#	$(AS) $(ASFLAGS) add.s -o add.o
	$(CC) $(CCFLAGS) SevenSeg.c
	
    clean:
	rm -rf *.o *.mif *.dump *.hex *.bin *.mif labcode
