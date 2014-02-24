#!/usr/bin/perl
#!C:\Perl64\bin\perl.exe
# http://b-67.spdns.de/cgi/arduino.pl?clock=20:12:54&p=20&day=20.12.2013&Eday=4325&Etot=54356.324

use strict;
use FileHandle;
use CGI;

my $fname="arduino.data";

sub getcgi {
  my ( $cgi, $name) = @_;
  my $val =  $cgi->param($name);
  # $val = "undefined" unless $val;
  return $val;
}

my $cgi = new CGI;

my $clock=getcgi($cgi,"clock");
my $day=getcgi($cgi,"day");
my $p=getcgi($cgi,"p");
my $Eday=getcgi($cgi,"Eday");
my $Etot=getcgi($cgi,"Etot");


print <<"EOF";
Content-Type:text/html


<html>
<head><title>Hello World</title></head>
<body>
<center>Hello Perl-World!</center>
EOF


print "clock=$clock<br>";
print "day=$day<br>";
print "p=$p<br>";
print "Eday=$Eday<br>";
print "Etot=$Etot<br>";

my $fp = new FileHandle(">$fname");
print "couldn't open output file <br>" unless($fp);

print $fp "clock=$clock\n";
print $fp "day=$day\n";
print $fp "p=$p\n";
print $fp "Eday=$Eday\n";
print $fp "Etot=$Etot\n";

$fp->close;

print "</body>\n</html>\n";
