#!/usr/bin/env perl
# TODO: Change this script for python

use strict;
use warnings;

system("../sql-file query1.txt > temp1.txt");
system("../sql-file query2.txt > temp2.txt");

my $diff = `diff temp1.txt expected1.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}


$diff = `diff temp2.txt expected2.in`;
chomp($diff);
if ($diff) {
  print STDERR $diff;
  exit(-1);
}

print STDERR "***PASSED***\n";
# unlink("temp.txt");
exit(0);
