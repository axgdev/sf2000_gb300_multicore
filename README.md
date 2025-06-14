# Frog Multicore

## About the platform
More information about the SF2000 handheld gaming system can be found [here](https://vonmillhausen.github.io/sf2000/). Information about the GB300 can be found here: https://github.com/nummacway/gb300

## About this repository

This repository intends to be a clean slate for the SF2000 and GB300 multicore repositories. We currently have the original repository: https://gitlab.com/kobily/sf2000_multicore, which was then forked by: https://github.com/madcock/sf2000_multicore and then multiple other forks exist for sf2000: https://github.com/leonardothehuman/sf2000_multicore which contains nightly saves 1, 2 and 3 and https://github.com/Trademarked69/sf2000_multicore which contains nightly save 4, which contain improvements over the github repository. Then another fork was created: https://github.com/tzubertowski/gb300_multicore, which contains the specific modifications needed for the GB300.

The proliferation of forks is a bit of a problem for a new developer trying to understand multicore. Also... git submodules. I'm not sure how I feel about those, they might be better for some devs, but I have decided to use git patches/diffs instead.

## Status
Some cores build and work well, others build and have issues (no sound, slowness, etc.), some build but do not currently work, and others do not build at all. For current information on the state of each core, please see the [spreadsheet](https://docs.google.com/spreadsheets/d/1BDPqLwRcY2cN7tObuyW7RzLw8oGyY9XGLS1D4jLgz2Q/edit?usp=sharing).

## Releases
TBD

## Setup (before building)
- from the top level of this repo, install the compiler tools
    - `./install-toolchain.sh`
- copy the 08/03/2023 (official release 1.6) file
    - `cp <YOUR_1.6_BISRV.ASD> bisrv_08_03.asd`
- clone the libretro-common repository to lib/
- checkout the commit in the filename of the patch in patches/
- patch libretro-common
- clone a core you would like to use and checkout the commit in the name in patches
- patch each core
 
## Building
If setup properly, there are a few ways to build.

Use the scripts to clean and build all the buildable cores:
- `./cleancores.sh` to clean all cores
- `./buildcores.sh` to build all cores

All of the cores are independent.

## Discussion
All the latest information can be found in the [dev channel on Discord](https://discord.com/channels/741895796315914271/1099465777825972347) which is part of [Retro Handhelds](https://discord.gg/retrohandhelds).

## Multicore brief history
- SF2000 was released. Cheap but not a famiclone, it can actually run consoles like GBA and SNES, although limited.
- The hardware and the software was studied by developers, mainly osaka/bnister.
- A toolchain/compiler was found that could compile binaries for the SF2000.
- osaka/bnister reverse engineered most of the important functions used in the stock firmware.
- osaka/bnister reverse engineered the crc algorithm used to prevent tinkering with the original firmware.
- osaka/bnister created a proof of concept: a binary loader and libretro core to load a .bmp file. The binary loader was patched into the stock firmware in the function that loads a GD3 game (.GD3 extension). The firmware will call the loader instead of the GD3 libretro core and then the loader would clal the .bmp viewer. Mind blown.
- work was continued between osaka/bnister and kobil to expand the functionality of the binary loader and patch libretro cores (emulators) to work on the SF2000. That's how the first repo was born: https://gitlab.com/kobily/sf2000_multicore.
- I must make emphasis that all of this wouldn't have been possible without all of the hard work of osaka/bnister but also open sourcing his contributions.
- From this point onwards kobil expanded on the multicore funtionality. One of the main objectives was to make the gpSP (GBA) emulator to work with Dynarec for performance improvements. More information about Dynarec here: https://en.wikipedia.org/wiki/Dynamic_recompilation
- madcock creates https://github.com/madcock/sf2000_multicore as a fork of kobil's repository using git submodules and trying to compile as many libretro-cores as possible.
- GB300 was released, cheap as SF2000 but almost the same firmware.
- kobil managed to get dynarec working. In kobil's own words: `the dynamically generated code modifies the $gp register for the duration of its execution, but it conflicts with what stock irq/interrupt handlers expect $gp to be.`
- osaka/bnister reverse engineered the GB300 firmware identifying the main functions.
- prosty creates GB300 multicore repo with guidance from osaka/bnister: https://github.com/leonardothehuman/sf2000_multicore
- dynarec patches plus some other enhancements such as built-in SRAM save were built into nightly save 1, 2 and 3: https://github.com/leonardothehuman/sf2000_multicore
- further enhancements to folder structure were built into nightly save 4: https://github.com/Trademarked69/sf2000_multicore
- andymcca999 creates an optimized partial flush (p-flush) version of gpSP which was compiled by prosty.
- prosty adds his own optimizations to libretro-cores for SF2000 and GB300. In prosty's own words: `eliminated most of floating points math that was killing SF2000/GB300 FPU-less CPU`
- this repository is born!