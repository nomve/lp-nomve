PALS Location Service
=======

To use these files you'll need:
+ Nordic SDK 6.0.0 (6.1.0 or higher will probably work)
+ Softdevice S110 7.1.0 (older will not work, this is the latest as of this writing)

To compile use Keil, the project files are in arm/. It is also possible to compile with gcc, see [this post](https://devzone.nordicsemi.com/blogs/22/getting-started-with-nrf51-development-on-mac-os-x/), but there is no makefile for this one. You can maybe adapt a makefile from other example projects in the SDK. They are located in gcc/.

The directory should be placed in the SDK directory nrf51822/Board/pca10001/s110 or something comparable in depth. Otherwise, you can put it anywhere, but you'll need to adapt the include paths to header and additional .c files.

The project was adapted from the health thermometer example. Most of the code is as of this writing the same, but we are broadcasting different data. It was also modified to work with Softdevice 7.1.0.

Branches
=======
*master*: data is placed in the service data part of the advertisement packet
*ble/manufacturer*: data is placed in the manufacturer data part of the advertisement packet
*ble/custom-uuid*: broadcasting a custom UUID, data not transmitted atm. If we do it this way, we will need to use a scan response 
