#!/usr/bin/env perl
# TODO: Change this script for python

use strict;
use warnings;

system("../../build/sql-file select/query1.txt > select/temp1.txt");
system("../../build/sql-file select/query2.txt > select/temp2.txt");
system("../../build/sql-file select/query3.txt > select/temp3.txt");
system("../../build/sql-file select/query4.txt > select/temp4.txt");
system("../../build/sql-file select/query5.txt > select/temp5.txt");
system("../../build/sql-file select/query6.txt > select/temp6.txt");

my $diff = `diff select/temp1.txt select/expected1.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

$diff = `diff select/temp2.txt select/expected2.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

$diff = `diff select/temp3.txt select/expected3.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

$diff = `diff select/temp4.txt select/expected4.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

$diff = `diff select/temp5.txt select/expected5.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

print STDERR "***PASSED***\n";
# unlink("temp.txt");
exit(0);
