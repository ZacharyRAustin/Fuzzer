#!/usr/bin/perl
# use strict;
use warnings;

print "Running test suite for Fuzzer\n";

print "Running Valgrind tests\n";

@valgrindArgs = ("valgrind", "-v", "-q", "--xml=yes", "--xml-file=valgrind_output.xml", "--leak-check=full", "--show-reachable=yes", "--error-exitcode=2", "./fuzzer", "0");
system(@valgrindArgs);

$valgrindArgs[9] = "1";
$valgrindArgs[4] = "--xml-file=valgrind_output1.xml";
system(@valgrindArgs);