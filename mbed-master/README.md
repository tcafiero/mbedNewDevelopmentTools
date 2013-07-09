mbed SDK
========

The mbed Software Development Kit (SDK) is a C/C++ microcontroller software platform relied upon by tens of thousands of
developers to build projects fast.

The SDK is licensed under the permissive Apache 2.0 licence, so you can use it in both commercial and personal projects
with confidence.

The mbed SDK has been designed to provide enough hardware abstraction to be intuitive and concise, yet powerful enough
to build complex projects. It is built on the low-level ARM CMSIS APIs, allowing you to code down to the metal if needed.
In addition to RTOS, USB and Networking libraries, a cookbook of hundreds of reusable peripheral and module libraries
have been built on top of the SDK by the mbed Developer Community.

Documentation
-------------
* [Tools](http://mbed.org/handbook/mbed-tools): how to setup and use the build system.
* [mbed library internals](http://mbed.org/handbook/mbed-library-internals)
* [Adding a new target microcontroller](http://mbed.org/handbook/mbed-SDK-porting)

Supported Microcontrollers
--------------------------
NXP:
* [LPC1768](http://mbed.org/handbook/mbed-NXP-LPC1768) (Cortex-M3)
* [LPC11U24](http://mbed.org/handbook/mbed-NXP-LPC11U24) (Cortex-M0)
* LPC2368 (ARM7TDMI-S)
* LPC812 (Cortex-M0+)
* LPC4088 (Cortex-M4)
* LPC4330 (Cortex-M4 + Cortex-M0)

Freescale:
* [KL25Z](http://mbed.org/handbook/mbed-FRDM-KL25Z) (Cortex-M0+)
* KL05Z (Cortex-M0+)

STMicroelectronics:
* STM32F407 (Cortex-M4)

Supported Toolchains and IDEs
-----------------------------
* GCC ARM: [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded/4.7/4.7-2012-q4-major)
* ARMCC (standard library and MicroLib): [uVision](http://www.keil.com/uvision/)
* IAR: [IAR Embedded Workbench](http://www.iar.com/en/Products/IAR-Embedded-Workbench/ARM/)
* GCC code_red: [Red Suite](http://www.code-red-tech.com/)
* GCC CodeSourcery: [Sourcery CodeBench](http://www.mentor.com/embedded-software/codesourcery)

API Documentation
-----------------
* [RTOS API](http://mbed.org/handbook/RTOS)
* [TCP/IP Socket API](http://mbed.org/handbook/Socket) (Transports: Ethernet, WiFi, 3G)
* [USB Device API](http://mbed.org/handbook/USBDevice)
* [USB Host API](http://mbed.org/handbook/USBHost)
* [DSP API](http://mbed.org/users/mbed_official/code/mbed-dsp/docs/tip/)
* Flash File Systems: [SD](http://mbed.org/handbook/SDFileSystem), [USB MSD](http://mbed.org/handbook/USBHostMSD), [semihosted](http://mbed.org/handbook/LocalFileSystem)
* [Peripheral Drivers API](http://mbed.org/handbook/Homepage)

Community
---------
For discussing the development of the mbed SDK itself (Addition/support of microcontrollers/toolchains, build and test system, Hardware Abstraction Layer API, etc) please join our [mbed-devel mailing list](https://groups.google.com/forum/?fromgroups#!forum/mbed-devel).

For every topic regarding the use of the mbed SDK, rather than its development, please post on the [mbed.org forum](http://mbed.org/forum/), or the [mbed.org Q&A](http://mbed.org/questions/).

For reporting issues in the mbed libraries please open a ticket on the issue tracker of the relevant [mbed official library](http://mbed.org/users/mbed_official/code/).
