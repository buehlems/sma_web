#!/usr/bin/perl
#!C:\Perl64\bin\perl.exe

use strict;
use FileHandle;
use Time::Piece;

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
$solar{"pmodel"}=initvar();
$solar{"t0model"}=initvar();
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

# save the base value
$solar{"Edaybase"}=$solar{"Eday"};
$solar{"Etotbase"}=$solar{"Etot"};

# update with model values
my $dE=0;
my $dt=0;
my $currdate = localtime->strftime('%d.%m.%Y');

if($solar{"t0model"} ne "undefined" && $solar{"pmodel"} ne "undefined" && $currdate eq $solar{"day"}){
  $dt=midnight_seconds()-$solar{"t0model"};
  $dE=$dt*$solar{"pmodel"};
}

$solar{"Etot"}+=($dE/(1000*3600));
$solar{"Eday"}+=$dE/(1000.0*3600.0);

# round the values
$solar{"Etot"}=int($solar{"Etot"}+0.5);
$solar{"Eday"}=sprintf("%.3f", $solar{"Eday"});

$solar{"Emonth"}=$solar{"Etot"}-$solar{"Emonth_start"} unless($solar{"Emonth_start"} eq "undefined");
$solar{"Eyear"}=$solar{"Etot"}-$solar{"Eyear_start"} unless($solar{"year_start"} eq "undefined");

# save values for debug output
$solar{"dt"}=$dt;

# load data from arduino file

my $finname="arduino.html";

print $fplog "open $finname\n";
my $fpin = new FileHandle("$finname");
print $fplog  "couldn't open html file\n" unless($fpin);

print "couldn't open html file <br>" unless($fpin);

while($line = <$fpin>){
  # search lines with values to replace
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

sub midnight_seconds {
   my @time = localtime();
   my $secs = ($time[2] * 3600) + ($time[1] * 60) + $time[0];

   return $secs;
}
