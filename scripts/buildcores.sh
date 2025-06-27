#!/bin/bash

#fully working
make CONSOLE=amstradb   CORE=cores/libretro-cap32 PLATFORM=$(PLATFORM) && 
make CONSOLE=m2k        CORE=cores/libretro-mame2000 PLATFORM=$(PLATFORM) && 
make CONSOLE=a26        CORE=cores/libretro-stella2014 PLATFORM=$(PLATFORM) && 
make CONSOLE=a5200      CORE=cores/a5200 PLATFORM=$(PLATFORM) && 
make CONSOLE=a78        CORE=cores/libretro-prosystem PLATFORM=$(PLATFORM) && 
make CONSOLE=a800       CORE=cores/libretro-atari800lib PLATFORM=$(PLATFORM) && 
make CONSOLE=lnx        CORE=cores/libretro-handy PLATFORM=$(PLATFORM) && 
make CONSOLE=wswan      CORE=cores/libretro-beetle-wswan PLATFORM=$(PLATFORM) && 
make CONSOLE=chip8      CORE=cores/jaxe MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=col        CORE=cores/Gearcoleco/platforms/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=fcf        CORE=cores/FreeChaF PLATFORM=$(PLATFORM) && 
make CONSOLE=retro8     CORE=cores/retro8 PLATFORM=$(PLATFORM) && 
make CONSOLE=vapor      CORE=cores/vaporspec/machine MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
#make CONSOLE=2048       CORE=cores/libretro-2048 MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=gong       CORE=cores/gong MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=outrun     CORE=cores/cannonball PLATFORM=$(PLATFORM) && 
make CONSOLE=wolf3d     CORE=cores/ecwolf/src/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=prboom     CORE=cores/libretro-prboom PLATFORM=$(PLATFORM) && 
make CONSOLE=flashback  CORE=cores/REminiscence PLATFORM=$(PLATFORM) && 
make CONSOLE=xrick      CORE=cores/libretro-xrick PLATFORM=$(PLATFORM) && 
make CONSOLE=gw         CORE=cores/libretro-gw PLATFORM=$(PLATFORM) && 
make CONSOLE=cdg        CORE=cores/libretro-pocketcdg PLATFORM=$(PLATFORM) && 
make CONSOLE=int        CORE=cores/FreeIntv PLATFORM=$(PLATFORM) && 
make CONSOLE=msx        CORE=cores/libretro-blueMSX PLATFORM=$(PLATFORM) && 
make CONSOLE=gme        CORE=cores/libretro-gme PLATFORM=$(PLATFORM) && 
make CONSOLE=pce        CORE=cores/libretro-beetle-pce-fast PLATFORM=$(PLATFORM) && 
make CONSOLE=ngpc       CORE=cores/RACE PLATFORM=$(PLATFORM) && 
make CONSOLE=gba        CORE=cores/gpsp PLATFORM=$(PLATFORM) && 
make CONSOLE=gbb        CORE=cores/libretro-gambatte PLATFORM=$(PLATFORM) && 
make CONSOLE=gbgb       CORE=cores/Gearboy/platforms/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=gb         CORE=cores/libretro-tgbdual PLATFORM=$(PLATFORM) && 
make CONSOLE=nes        CORE=cores/libretro-fceumm PLATFORM=$(PLATFORM) && 
make CONSOLE=nesq       CORE=cores/QuickNES_Core PLATFORM=$(PLATFORM) && 
make CONSOLE=pokem      CORE=cores/PokeMini PLATFORM=$(PLATFORM) && 
make CONSOLE=snes02     CORE=cores/snes9x2002 PLATFORM=$(PLATFORM) && 
make CONSOLE=snes       CORE=cores/snes9x2005 PLATFORM=$(PLATFORM) && 
make CONSOLE=sega       CORE=cores/picodrive MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=gg         CORE=cores/Gearsystem/platforms/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=zx81       CORE=cores/libretro-81 PLATFORM=$(PLATFORM) && 
make CONSOLE=spec       CORE=cores/libretro-fuse PLATFORM=$(PLATFORM) && 
make CONSOLE=thom       CORE=cores/theodore PLATFORM=$(PLATFORM) && 
make CONSOLE=vec        CORE=cores/libretro-vecx PLATFORM=$(PLATFORM) && 
make CONSOLE=wsv        CORE=cores/potator/platform/libretro PLATFORM=$(PLATFORM) && 

#working but issues
make CONSOLE=amstrad    CORE=cores/libretro-crocods PLATFORM=$(PLATFORM) && 
make CONSOLE=arduboy    CORE=cores/arduous PLATFORM=$(PLATFORM) && 
make CONSOLE=lnxb       CORE=cores/libretro-beetle-lynx PLATFORM=$(PLATFORM) && 
#make CONSOLE=bk         CORE=cores/bk-emulator MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64sc   CORE=cores/libretro-vice EMUTYPE=x64sc PLATFORM=$(PLATFORM) && 
make CONSOLE=c64sc         CORE=cores/libretro-vice EMUTYPE=x64sc PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64sc   CORE=cores/libretro-vice EMUTYPE=x64sc PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64     CORE=cores/libretro-vice EMUTYPE=x64 PLATFORM=$(PLATFORM) && 
make CONSOLE=c64           CORE=cores/libretro-vice EMUTYPE=x64 PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64     CORE=cores/libretro-vice EMUTYPE=x64 PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64f  CORE=cores/libretro-frodo EMUTYPE=frodo PLATFORM=$(PLATFORM) && 
make CONSOLE=c64f        CORE=cores/libretro-frodo EMUTYPE=frodo PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64f  CORE=cores/libretro-frodo EMUTYPE=frodo PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64fc CORE=cores/libretro-frodo EMUTYPE=frodosc PLATFORM=$(PLATFORM) && 
make CONSOLE=c64fc       CORE=cores/libretro-frodo EMUTYPE=frodosc PLATFORM=$(PLATFORM) && 
make clean CONSOLE=c64fc CORE=cores/libretro-frodo EMUTYPE=frodosc PLATFORM=$(PLATFORM) && 
make clean CONSOLE=vic20   CORE=cores/libretro-vice EMUTYPE=xvic PLATFORM=$(PLATFORM) && 
make CONSOLE=vic20         CORE=cores/libretro-vice EMUTYPE=xvic PLATFORM=$(PLATFORM) && 
make clean CONSOLE=vic20   CORE=cores/libretro-vice EMUTYPE=xvic PLATFORM=$(PLATFORM) && 
make CONSOLE=fake08     CORE=cores/fake-08/platform/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=lowres-nx  CORE=cores/lowres-nx/platform/LibRetro PLATFORM=$(PLATFORM) && 
#make CONSOLE=mrboom     CORE=cores/libretro-mrboom PLATFORM=$(PLATFORM) && 
make CONSOLE=jnb        CORE=cores/libretro-jumpnbump PLATFORM=$(PLATFORM) && 
make CONSOLE=cavestory  CORE=cores/libretro-nxengine PLATFORM=$(PLATFORM) && 
#make CONSOLE=x48        CORE=cores/libretro-x48 PLATFORM=$(PLATFORM) && 
make CONSOLE=o2em       CORE=cores/libretro-o2em PLATFORM=$(PLATFORM) && 
make CONSOLE=pcesgx     CORE=cores/libretro-beetle-supergrafx PLATFORM=$(PLATFORM) && 
make CONSOLE=pc8800     CORE=cores/libretro-quasi88 PLATFORM=$(PLATFORM) && 
make CONSOLE=pcfx       CORE=cores/libretro-beetle-pcfx PLATFORM=$(PLATFORM) && 
make CONSOLE=gbav       CORE=cores/vba-next PLATFORM=$(PLATFORM) && 
make CONSOLE=mgba       CORE=cores/mgba PLATFORM=$(PLATFORM) && 
make CONSOLE=nest       CORE=cores/nestopia/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=vb         CORE=cores/libretro-beetle-vb PLATFORM=$(PLATFORM) && 
make CONSOLE=gpgx       CORE=cores/Genesis-Plus-GX MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=geolith    CORE=cores/libretro-geolith/libretro PLATFORM=$(PLATFORM) && 
make CONSOLE=xmil       CORE=cores/libretro-xmil/libretro PLATFORM=$(PLATFORM) && 

#test cores
make CONSOLE=testadv CORE=cores/libretro-samples/tests/test_advanced PLATFORM=$(PLATFORM) && 
make CONSOLE=testwav CORE=cores/libretro-samples/audio/audio_playback_wav PLATFORM=$(PLATFORM) && 

true
