#!/usr/bin/perl

#
# Author: Taeweon Suh
# It generates mif files for Altera FPGA Memory initialization
# Programmed assuming only for 4KB Instruction and Data Memories
#

open (FH, "<labcode.hex") or die "oooops: $!";
$lcount = 0;
while (<FH>)
{
	 $lcount++;
}
print $lcount;
close(FH);

open (FH, "<labcode.hex") or die "oooops: $!";

#
# Instruction & Data Memory Initialization
#

$file = 'insts_data.mif';
open(MEM, ">$file");

print MEM "WIDTH=32;\n";
print MEM "DEPTH=$lcount;\n\n";

print MEM "ADDRESS_RADIX=HEX;\n";
print MEM "DATA_RADIX=HEX;\n\n";

print MEM "CONTENT BEGIN\n\n";

$count = 0;
while (<FH>)
{
	 chomp;
    printf MEM "	%03X : ", $count;
    print MEM " $_ ;\n";
	 $count++;
}
print MEM "END;\n";
close(MEM);

close(FH);
