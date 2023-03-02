# Akai ECV6607 car DVD head unit on arduino /w TVout lib

* Reuse old hardware for a fun mod.
* PRO; Easy to use & free.
* CON; screen resolution & CCFL backlight (energy efficiency).

## The idea
Make a small low cost LCD/MCU(ATmega328P) solution that can display pc stats using USB serial. Reusing old e-waste parts.
Add this to a SFF/mATX system with open side panel with acrylic glass from old LCD monitor.

First we wire the unit and run the **stock demo**:

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/stock-demo.jpg?raw=true)

Now we look at the simplified block diagram how it works: 

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/block_diagram.png?raw=true)

Power supply default values IC902:

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/IC902.png?raw=true)

Example of IC902 (might slightly differ):

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/TL494.png?raw=true)

Wire up the TVout output from arduino to the unit:

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/pinout.jpg?raw=true)

Wire up the TVout output from arduino to the unit:

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/pinout.jpg?raw=true)

Some of the demos I ran on it:

![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/demo0.jpg?raw=true)
![screendump blockchart](https://github.com/StackerDEV/Akai_ECV6607_display/blob/master/imgs/demo1.jpg?raw=true)

**Notes:**
TODO

Issue                                | Solution                                   | 
-------------------------------------|--------------------------------------------| 
RM CCFL add LED BL                   | off the shelf parts from CN                | 
RM mainboard except display driver   | off the shelf parts from CN, more compact  | 

Figure out what input the display driver likes remove HV parts retrofit CN parts.
Make it Energy Star® compliance, get rid of obsolete fluorescent tube.

## License

> None
