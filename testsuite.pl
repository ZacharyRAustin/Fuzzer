#!/usr/bin/perl
# use strict;
use warnings;

my $template = "template.txt";
my $output = "output.txt";

print "Running test suite for Fuzzer\n";

print "Running Valgrind tests\n";

my @valgrindArgs = ("valgrind", "-v", "-q", "--xml=yes", "--xml-file=valgrind_output.xml", "--leak-check=full", "--show-reachable=yes", "--error-exitcode=2", "./fuzzer", "0");
system(@valgrindArgs);

$valgrindArgs[9] = "1";
$valgrindArgs[4] = "--xml-file=valgrind_output1.xml";
system(@valgrindArgs);

print "Running Word Count Check\n";
checkWordCount();

sub checkWordCount{
	my $outputCount = `wc -m $output`;
	my $templateCount = `wc -m $template`;

	my @out = split(" ", $outputCount);
	my @temp = split(" ", $templateCount);

	if($out[0] == $temp[0])
	{
		print "Word Counts are Equal\n";
	}
	else
	{
		print "Word Counts are not equal: \n"; 
		print "$output: $out[0] words\n";
		print "$template: $temp[0] words\n";
	}
}

sub checkValgrind{

}
