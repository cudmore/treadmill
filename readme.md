
### Web based experiment control


### Overview

This is a python server and web based javascript duo that allows an experiment to be run using an Arduino microcontroller.

It has been tested on both OS X and Debian Linux (Microsoft Windows is next).

### Interface

<IMG SRC="images/screenshot1.png" border="1">

The top section provides an interface to start/stop a trial and plots real-time feedback as the trial is running

The middle section provides an interface to set stimulus parameters for a trial and then upload these parameters to an Arduino. This section also provides a plot of what the trial will look like based on the set of parameters entered.


### Installation

This is a work in progress. The code here on Github is not up to date. When this is finished, an installation and use guide will be provided.

### Libraries Used

  Programming an Arduino
  
  - platformio

  Server
  
  - python
  - flask
  - socket io
  
  
  Web based client
  
  - jquery
  - plotly js
  - highcharts
  - bootstrap
  
### Hardware

  - Stepper Motor, [sparkfun][11], ROB-09238, $15

  - Stepper motor driver, EasyDriver, [sparkfun][12], ROB-12779, $15. Main website for [EasyDriver][13]
  
  - Rotary encoder, [Honeywell-600-128-CBL][14], [.pdf spec sheet][15], $37
  
  - IR LED, 840-850 nm, [sparkfun][16] $1 each (960 nm IR LEDs do not work well with Pi Noir camera)

  - Actobotics at [ServoCity][17] and [sparkfun][18]. Give [ServoCity][17] a shot, their visual guides and project ideas are really helpful in desining components. This can be your one stop shop for all structural components including frames, rods, bearings, clamps, and motor mounts.
  
### Arduino libraries

Key is to use libraries that do not block your main event loop. These are 'non-blocking' and usually written in C.

  - [AccelStepper][19] library to control stepper motor
  
  - Rotary encoder library from [PJRC][20]

### mkdocs

This documentation is written in markdown and a static site is generated with [mkDocs][21]. Previously I have used [Jekyll][22] which is amazing. Going with mkDocs to see if a simple site is acceptable.
 
When writing markdown, serve an mkDocs site locally with

  >> mkdocs serve --dev-addr=0.0.0.0:80

and build with

  >> mkdocs build
  
### Links

  - [flask-socketio][5]
  - [eventlet][6]
  - [platormio][1]
  - [simplehttpserver][2]
  - [pyserial][3]
  - [flask-misaka][4]
  - [flask-markdown][9] and [python markdown][10]
  - platform io [serial port monitor][7]
  - [AccelStepper][8] non blocking arduino library to control stepper motor
    
[1]: http://platformio.org/#!/
[2]: https://docs.python.org/2/library/simplehttpserver.html
[3]: https://pythonhosted.org/pyserial/shortintro.html
[4]: https://flask-misaka.readthedocs.org
[5]: https://flask-socketio.readthedocs.org/en/latest/
[6]: http://eventlet.net
[7]: http://docs.platformio.org/en/latest/userguide/cmd_serialports.html#platformio-serialports-monitor
[8]: http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
[9]: https://pythonhosted.org/Flask-Markdown/
[10]: http://pythonhosted.org/Markdown

[11]: https://www.sparkfun.com/products/9238
[12]: https://www.sparkfun.com/products/12779
[13]: http://www.schmalzhaus.com/EasyDriver/

[14]: http://www.digikey.com/product-detail/en/600128CBL/600CS-ND/53504
[15]: http://sensing.honeywell.com/600%20series_005940-2-en_final_12sep12.pdf

[16]: https://www.sparkfun.com/products/9469

[17]: https://www.servocity.com/html/actoboticstm.html
[18]: https://www.sparkfun.com/actobotics

[19]: http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html

[20]: https://www.pjrc.com/teensy/td_libs_Encoder.html

[21]: http://mkdocs.readthedocs.org/en/stable/
[22]: https://jekyllrb.com
