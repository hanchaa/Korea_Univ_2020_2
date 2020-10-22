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

    HOME=c:/users/juhan/desktop/Korea_Univ_2020_2/COSE222/riscv32i
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

    labcode: lab0.o compare.o
	$(LD) $(LDFLAGS)  lab0.o compare.o -o labcode
	$(OBJDUMP) -xS  labcode > labcode.dump
	$(OBJCOPY) -O  binary labcode labcode.bin
	./bin2hex.perl > labcode.hex
	./hex2mif.perl
#	./mipsel-readelf -a labcode > labcode.r
#	./mipsel-nm labcode > labcode.n
	 
    lab0.o: lab0.s
	$(AS) $(ASFLAGS) lab0.s -o lab0.o
	
    compare.o:	compare.c
	# $(CPP) compare.c > compare.i
	# $(CC) -Wall -S compare.i
	# $(AS) $(ASFLAGS) compare.s -o compare.o
	# $(OBJDUMP) -xS compare.o > compare.dump
	$(CC) $(CCFLAGS) compare.c
	
    clean:
	rm -rf *.o *.mif *.dump *.hex *.bin *.mif labcode
