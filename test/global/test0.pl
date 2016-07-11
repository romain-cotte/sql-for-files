#!/usr/bin/env perl
# TODO: Change this script for python

use strict;
use warnings;

system("../../build/sql-file query1.txt > temp1.txt");
system("../../build/sql-file query2.txt > temp2.txt");
system("../../build/sql-file query3.txt > temp3.txt");

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

# $diff = `diff temp3.txt expected3.in`;
# chomp($diff);
# if ($diff) {
#   print STDERR $diff;
#   exit(-1);
# }

print STDERR "***PASSED***\n";
# unlink("temp.txt");
exit(0);