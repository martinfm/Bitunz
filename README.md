# Bitunz

Bitunz is a VST/AU plug-in 8-bit crusher where you can mute or invert each bit with a separate control. 
It also sports separate controls for dry and wet mix and downsampling, which downgrades the resolution up to 64 samples 


## Installation

##### Binaries

Grab one of the binaries (both Windows 32/64 and Mac available) from the [relases section](https://github.com/martinfm/Bitunz/releases). 
On Windows drop the .dll file where your DAW will look for it; on a Mac launch the dmg and copy Bitunz in the plug-ins folder.

##### From source code

 * Download or clone the [WDL-OL framework](https://github.com/olilarkin/wdl-ol);
 * use the duplicate.py script to create your own project: for example
   `duplicate IPlugText Bitunz yourname`;
 * replace Bitunz.h, Bitunz.cpp, resource.h and Bitunz.rc with the files in this repository;
 * compile.

## License 


Bitunz shares the same license as WDL / IPlug - Oli Larkin Edition.
It has been started from the IPlugText example. All the new code is Copyright (C) 2015  Fiore Martin.


-------------------------------------------
WDL / IPlug - Oli Larkin Edition

IPlug is a simple-to-use C++ framework for developing cross platform audio plugins and targeting multiple plugin APIs with the same code. Originally developed by Schwa/Cockos, IPlug has been enhanced by various contributors. IPlug depends on WDL, and that is why this project is called WDL-OL,  although most of the differences from Cockos' WDL are to do with IPlug.
This version of IPlug targets VST2, VST3, AudioUnit RTAS and AAX (Native) APIs. It can also produce standalone Windows/OSX audio/midi apps and apps for Apple's IOS devices. 

This version of WDL/IPlug shares the same license as the Cockos edition. Several of the added features are based on the work of other people. See individual source code files for any extra license information.

Cockos WDL Page: http://www.cockos.com/wdl

Discuss WDL on the WDL forum http://forum.cockos.com/forumdisplay.php?f=32

--------------------------------------------

Cockos WDL License

Copyright (C) 2005 and later Cockos Incorporated

Portions copyright other contributors, see each source file for more information

This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

WDL includes the following 3rd party libraries (which are all similarly licensed):

* JNetLib http://www.nullsoft.com/free/jnetlib
* LibPNG http://www.libpng.org/pub/png
* GifLib http://sourceforge.net/projects/libungif
* JPEGLib http://www.ijg.org
* zlib http://www.zlib.net

