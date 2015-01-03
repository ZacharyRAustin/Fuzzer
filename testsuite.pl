#!/usr/bin/perl
# use strict;
use warnings;

my $template = "template.txt";
my $output = "output.txt";
my @valgrindInputs = ("0", "1", "10000");

print "\nRunning test suite for Fuzzer\n";

print "\nRunning Valgrind tests\n";
checkValgrind();
print "\nRunning Word Count Check\n";
checkCharacterCount();

sub checkCharacterCount{
	my $outputCount = `wc -m $output`;
	my $templateCount = `wc -m $template`;

	my @out = split(" ", $outputCount);
	my @temp = split(" ", $templateCount);

	if($out[0] == $temp[0])
	{
		print "Character counts are equal\n";
	}
	else
	{
		print "Character counts are not equal: \n"; 
		print "$output: $out[0] words\n";
		print "$template: $temp[0] words\n";
	}
}

sub checkValgrind{
	my @valgrindArgs = ("valgrind", "./fuzzer", "0");

	foreach(@valgrindInputs){
		$valgrindArgs[2] = $_;
		@valgrindOutput = `@valgrindArgs 2>&1`;
		$check = 0;

		foreach(@valgrindOutput){
			if(index($_, "no leaks are possible") != -1)
			{
				$check = 1;
			}
		}

		if($check == 0)
		{
			print "valgrind ./fuzzer $valgrindArgs[2]: FAILED\n";
		}
		else
		{
			printf "valgrind ./fuzzer $valgrindArgs[2]: PASSED\n";
		}
	}
}
