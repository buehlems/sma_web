#!/usr/bin/perl
#!C:\Perl64\bin\perl.exe
# http://b-67.spdns.de/cgi/arduino.pl?clock=20:12:54&p=20&day=20.12.2013&Eday=4325&Etot=54356.324
# use dos2unix to convert to linux format. Otherwise it will not run on the web server

use strict;
use FileHandle;
use CGI;

my $fname="arduino.data";
my $fcodename="sma_pw.h";

# choose newline
# my $nl="<br>"; # html version
my $nl="\n"; # debug version

sub getcgi {
  my ( $cgi, $name) = @_;
  my $val =  $cgi->param($name);
  # $val = "undefined" unless $val;
  return $val;
}

sub midnight_seconds {
   my @time = localtime();
   my $secs = ($time[2] * 3600) + ($time[1] * 60) + $time[0];

   return $secs;
}

my $cgi = new CGI;

my $clock=getcgi($cgi,"clock"); # time given by the inverter
my $day=getcgi($cgi,"day"); # date
my $p=getcgi($cgi,"p"); # current power given by the inverter
my $pmodel=getcgi($cgi,"pmodel"); # model power
my $Eday=getcgi($cgi,"Eday"); # energy day
my $Etot=getcgi($cgi,"Etot"); # total energy
my $pwin=getcgi($cgi,"c"); # password
my $pwref=""; # the password as stored
my $t0model=midnight_seconds(); # start time for the model


print <<"EOF";
Content-Type:text/html


<html>
<head><title>Hello World</title></head>
<body>
<center>Hello Perl-World!</center>
EOF


print "clock=$clock$nl";
print "day=$day$nl";
print "p=$p$nl";
print "pmodel=$pmodel$nl";
print "Eday=$Eday$nl";
print "Etot=$Etot$nl";
print "t0model=$t0model$nl";

my $fc = new FileHandle("$fcodename");
if($fc){
  $pwref=<$fc>;
  $pwref=~/#define SMA_PW "(\S+)"/;
  if($1){
    $pwref=$1;
  }else{
    print("PW file found but invalid$nl");
    $pwref="invalid:2"; # such a PW will always fail
  }
  $fc->close;
}else{
  print "couldn't find pw file $fcodename. Not checking PW.$nl";
}

# print only if in debug mode
if($nl eq "\n"){
  print "pwin=$pwin$nl";
  print "pwref=$pwref$nl";
}

if($pwref ne "" && $pwref ne $pwin){
  print "PW error $nl";
}else{
  # print "PW ok $nl";
  my $fp = new FileHandle(">$fname");
  print "couldn't open output file $nl" unless($fp);

  print $fp "clock=$clock\n";
  print $fp "day=$day\n";
  print $fp "p=$p\n";
  print $fp "pmodel=$pmodel\n";
  print $fp "t0model=$t0model\n";
  print $fp "Eday=$Eday\n";
  print $fp "Etot=$Etot\n";

  $fp->close;

  print "done$nl";

}
print "</body>\n</html>\n";
