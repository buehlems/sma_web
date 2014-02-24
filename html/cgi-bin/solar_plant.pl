#!/usr/bin/perl
#!C:\Perl64\bin\perl.exe
# http://b-67.spdns.de/cgi/arduino.pl?clock=20:12:54&p=20&day=20.12.2013&Eday=4325&Etot=54356.324

use strict;
use FileHandle;

my $line;

# log file
my $logname=">arduino.log";
my $fplog = new FileHandle("$logname");

# load data from arduino file

my %solar=();

$solar{"year"}=initvar();
$solar{"clock"}=initvar();
$solar{"day"}=initvar();
$solar{"p"}=initvar();
$solar{"Eday"}=initvar();
$solar{"Etot"}=initvar();
$solar{"Emonth"}=initvar();
$solar{"Eyear"}=initvar();

# start values
$solar{"Eyear_start"}=initvar();
$solar{"Emonth_start"}=initvar();

loadSolar("arduino_init.data");
loadSolar("arduino.data");

# Calculated values
# get year
if($solar{"day"} ne "undefined"){
  $solar{"day"} =~ m/(\d+)/;
  $solar{"year"} = $1;
}

$solar{"Emonth"}=$solar{"Etot"}-$solar{"Emonth_start"} unless($solar{"Emonth_start"} eq "undefined");
$solar{"Eyear"}=$solar{"Etot"}-$solar{"Eyear_start"} unless($solar{"year_start"} eq "undefined");


# load data from arduino file

my $finname="arduino.html";

print $fplog "open $finname\n";
my $fpin = new FileHandle("$finname");
print $fplog  "couldn't open html file\n" unless($fpin);

print "couldn't open html file <br>" unless($fpin);

while($line = <$fpin>){
  if($line =~ /\[(\w+)\]/) {
    my $name=$1;
    my $val=$solar{$name};
    # print "found $name=$val\n";
    if($val ne "undefined"){
      $line =~ s/\[(\w+)\]/$val/;
    }
  }
  print $line;
}


$fpin->close;
$fplog->close;

exit;


sub initvar {
  return "undefined";
}

sub loadSolar {
  my($finname) = @_;

  print $fplog "open $finname\n";
  my $fpin = new FileHandle("$finname");
  print $fplog  "couldn't open data file\n" unless($fpin);
  # print "couldn't open data file <br>" unless($fpin);
  while (my $line = <$fpin>) {
    chomp($line);
    (my $name,my $val) = split /=/,$line;
    $solar{$name} = $val;
    # print "name=$name val=$val\n";
  }

  $fpin->close;
}
