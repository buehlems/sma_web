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


I am using 
- an Arduino Mega
- a SeeedStudio bluetooth shield. E.g http://www.seeedstudio.com/depot/Bluetooth-Shield-p-866.html
- a TLG10UA03 Wifi module which I use in command mode as a client. E.g. http://www.elechouse.com/elechouse/index.php?main_page=product_info&cPath=90_186&products_id=1007
- 1602 LCD Keypad Shield. E.g. http://www.sainsmart.com/sainsmart-1602-lcd-keypad-shield-for-arduino-duemilanove-uno-mega2560-mega1280.html

I am using all three HW serials:
Serial: communication with the PC (mainly printing debug code).
Serial2: connects the wifi
Serial3: conncts the bluetooth shield

The code does the following:
- read out data from SMA inverter (current power, energy per day, total energy and the time)
- send data to a web server as parameters to a GET command
- show most important data and status on LCD

I am also providing code for the web server (sub directory html)
- Perl script to receive data as command line options and write it in a file on the web server (cgi/arduino.pl)
- Master web page to display data in a browser: solar_plant.shtml
- CGI script to generate the dynamic web page: cgi/solar_plant.pl
- sample data files on the web server: arduino_init.data, code.data, arduino.data

Currently the code consumes 36kb including the debug code. If you remove the debug code it shrinks to 27kB. So it should fit on an smaller Arduino device.

For development I recommend to install a local web server. I am using Abyss Web Server. It is relatively simple to setup and support CGI scripts.
To test my TCP/IP Sockets I use TCP/IP builder: http://www.drk.com.ar/builder.php
Without this tool I would never have been able to debug my HTML client.
The final application I have installed at a public web hoster.

In the future I plan the following extensions to the program:
- power down Wifi, bluetooth and Arduino when not used.
- get sunrise and sunset data from a public web server to control shut down during the night.
- run from a solar panel + batterie
- more energy savings features
- an MQTT interface


===========================================================================================================================
Stuart Pittaway's and my licence:

Latest version found at https://github.com/stuartpittaway/nanodesmapvmonitor
Licence
Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
http://creativecommons.org/licenses/by-nc-sa/3.0/

You are free:
    to Share - to copy, distribute and transmit the work
    to Remix - adapt the work
Under the following conditions:
    Attribution - You must attribute the work in the manner specified by the author or licensor (but not in any way that suggests that they endorse you or your use of the work).
    Noncommercial - You may not use this work for commercial purposes.
    Share Alike - you alter, transform, or build upon this work, you may distribute the resulting work only under the same or similar license to this one.
