sma_web
=======

Arduino SMA Monitor and Web Publisher with TLG10UA03 Wifi Module


This work is base on Dean Fogarty's dfinvrelay and indirectly to Stuart Pittaway's nanodesmapvmonitor. 

Link to these codes:
Dean Fogerty: https://github.com/angrytongan/dfinvrelay/
Dean's licence: not known
Stuart Pittaway: https://github.com/stuartpittaway/nanodesmapvmonitor
Stuart's licence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0) http://creativecommons.org/licenses/by-nc-sa/3.0/

Thanks to both for their work.


This is my very first commit and the documentation is not fully complete yet.
From Dean I am using:
- the SMA code: sma.* There are only little changes in this part
- the bluetooth code bt.*: I have adapted it to my bluetooth module
- util.*: I have added some functions
Regarding the SMA code, please consult Stuart's page. My code has the same limitations.


I am using an Arduino Mega, a SeeedStudio bluetooth shield and a TLG10UA03 Wifi module which I use in command mode as a client.

The code does the following:
- read out data from SMA inverter (current power, energy per day, total energy and the time)
- send data to a web server with a GET command
I am also providing code for the web server
- Perl script to receive data as command line options and write it in a file on the web server (cgi/arduino.pl)
- Master web page to display data in a browser: solar_plant.shtml
- CGI script to generate the dynamic web page: cgi/solar_plant.pl
- sample data files on the web server: arduino_init.data, code.data, arduino.data

I am still in the progress of uploading the code, adding the proper licences to the files and writing this documentation.
So please still wait a couple of days/weeks for me to complete the upload and improve this documentation






===========================================================================================================================
Stuart Pittaway's code and licence:

Latest version found at https://github.com/stuartpittaway/nanodesmapvmonitor
Licence
Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
http://creativecommons.org/licenses/by-nc-sa/3.0/

You are free:
    to Share — to copy, distribute and transmit the work
    to Remix — to adapt the work
Under the following conditions:
    Attribution — You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work).
    Noncommercial — You may not use this work for commercial purposes.
    Share Alike — If you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one.
