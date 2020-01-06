#!/usr/bin/perl
#!C:\Perl64\bin\perl.exe
# http://b-67.spdns.de/cgi/arduino.pl?clock=20:12:54&p=20&day=20.12.2013&Eday=4325&Etot=54356.324
# use dos2unix to convert to linux format. Otherwise it will not run on the web server

use strict;
use FileHandle;
use CGI;

my $fname="arduino.data";
my $fcodename="arduino_code.data";

# choose newline
my $nl="<br>"; # html version
# my $nl="\n"; # debug version

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
my $pwin=getcgi($cgi,"c");
my $pwref="";


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
print "Eday=$Eday$nl";
print "Etot=$Etot$nl";
# print "pw=$pwin$nl";

my $fc = new FileHandle("$fcodename");
if($fc){
  $pwref=<$fc>;
  $pwref=~s/^\s+//; # remove leading white spaces
  $pwref=~s/\s+.*//g; # remove anything after next white space (including new line)
  $fc->close;
}else{
  print "couldn't find pw file $fcodename. Not checking PW.$nl";
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
  print $fp "Eday=$Eday\n";
  print $fp "Etot=$Etot\n";

  $fp->close;

  print "done$nl";

}
print "</body>\n</html>\n";
