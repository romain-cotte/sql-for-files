#!/usr/bin/env perl
# TODO: Change this script for python

use strict;
use warnings;
my $diff = "";


for (my $i=1; $i <= 6; $i++) {
  print "select query $i\n";
  system("../../build/sql-file select/query$i.txt > select/temp$i.txt");
  $diff = `diff select/temp$i.txt select/expected$i.in`;
  chomp($diff);
  if ($diff) {
    print STDERR $diff;
    exit(-1);
  }
}

for (my $i=1; $i <= 1; $i++) {
  print "delimiter query $i\n";
  system("../../build/sql-file delimiter/query$i.txt > delimiter/temp$i.txt");
  $diff = `diff delimiter/temp$i.txt delimiter/expected$i.in`;
  chomp($diff);
  if ($diff) {
    print STDERR $diff;
    exit(-1);
  }
}

for (my $i=1; $i <= 1; $i++) {
  print "limit query $i\n";
  system("../../build/sql-file limit/query$i.txt > limit/temp$i.txt");
  $diff = `diff limit/temp$i.txt limit/expected$i.in`;
  chomp($diff);
  if ($diff) {
    print STDERR $diff;
    exit(-1);
  }
}

print STDERR "***PASSED***\n";
# unlink("temp.txt");
exit(0);
