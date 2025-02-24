# CoreCtl

A simple application to disable half of the CPU cores, possibly improving battery life on laptops. Linux does not do core parking like Windows, instead it tries to not move a process outside of the core it currently is on. This is still good for battery saving, but I wanted to test having only half of my cores active to possibly improve battery-life.

> [!WARNING]
> This program is only a proof of concept and not a finalised tool. If something happens, you are on your own!
------

## Usage

When parking/disabling, corectl automatically puts half of the cpu cores offline. When unparking/enabling, it sets all of the cpu cores online, even if they already where.

### Parking

    $ corectl park
    Parking 6 cores...

### Unparking

    $ corectl unpark
    Unparking 12 cores...

### List

    $ corectl list
    Total cores: 12
    Active cores: 6
    Parked cores: 6


## Installation

To build and install this software you should only need a C compiler available. (Yes, C. No, not Rust.)

> [!WARNING]
> `make install` enables SETUID for the executable, allowing it to be ran as root by every user in the `wheel` group. Use with caution!

    $ git clone https://github.com/RuiFPB/corectl.git
    $ make
    $ sudo make install


## Uninstall

    $ sudo make uninstall

## Testing

To be done...
