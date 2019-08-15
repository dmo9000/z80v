#!/usr/bin/perl

print ("#include \"z80.h\"\n");
print ("opcode z80opmap[0xFF] = {\n");

my %opcodes;

for ($i = 0; $i < 254; $i++) {
	$opcode{$i}{'data'} = "";
	$opcode{$i}{'description'} = "NULL";
	$opcode{$i}{'opcode'} = "OPCODE_NONE";
	$opcode{$i}{'length'} = 0;
	$opcode{$i}{'cycles'} = 0;
	$opcode{$i}{'register1'} = "REG_NONE";
	$opcode{$i}{'register2'} = "REG_NONE";
}

while (<STDIN>)
{
	$data = $_;
	chop $data;
	($insn,$description,$opcode,$length,$cycles,$register1,$register2) = split(',', $data);
	$insn = hex("0x$insn");
	print("// $insn, $register\n");
	$opcode{$insn}{'data'} = $data;
	$opcode{$insn}{'description'} = $description;
	$opcode{$insn}{'opcode'} = $opcode;
	$opcode{$insn}{'length'} = $length;
	$opcode{$insn}{'cycles'} = $cycles;
	$opcode{$insn}{'register1'} = $register1;
	$opcode{$insn}{'register2'} = $register2;
}

for ($i = 0; $i < 254; $i++) {
		$opdata = $opcode{$i}{'opcode'};
		$description = $opcode{$i}{'description'};
		$length = $opcode{$i}{'length'};
		$register1 = $opcode{$i}{'register1'};
		$register2 = $opcode{$i}{'register2'};
		$cycles = $opcode{$i}{'cycles'};
		print ("\t{ \"$description\", FLAGS_NONE, $opdata, $length, $cycles, ( $register1 ), ( $register2 ) },\n");
		}

# $opdata = $opcode{$i}{'opcode'};
# $description = $opcode{$i}{'description'};
# print ("\t{ \"$description\", FLAGS_NONE, $opdata },\n");

print ("};\n");

exit 0;
