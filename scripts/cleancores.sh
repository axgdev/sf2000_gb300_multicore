#!/bin/bash

#fully working
make clean CONSOLE=amstradb   CORE=cores/libretro-cap32 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=m2k        CORE=cores/libretro-mame2000 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=a26        CORE=cores/libretro-stella2014 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=a5200      CORE=cores/a5200 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=a78        CORE=cores/libretro-prosystem PLATFORM=$(PLATFORM) && \
make clean CONSOLE=a800       CORE=cores/libretro-atari800lib PLATFORM=$(PLATFORM) && \
make clean CONSOLE=lnx        CORE=cores/libretro-handy PLATFORM=$(PLATFORM) && \
make clean CONSOLE=wswan      CORE=cores/libretro-beetle-wswan PLATFORM=$(PLATFORM) && \
make clean CONSOLE=chip8      CORE=cores/jaxe MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=col        CORE=cores/Gearcoleco/platforms/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=fcf        CORE=cores/FreeChaF PLATFORM=$(PLATFORM) && \
make clean CONSOLE=retro8     CORE=cores/retro8 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=vapor      CORE=cores/vaporspec/machine MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=2048       CORE=cores/libretro-2048 MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gong       CORE=cores/gong MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=outrun     CORE=cores/cannonball PLATFORM=$(PLATFORM) && \
make clean CONSOLE=wolf3d     CORE=cores/ecwolf/src/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=prboom     CORE=cores/libretro-prboom PLATFORM=$(PLATFORM) && \
make clean CONSOLE=flashback  CORE=cores/REminiscence PLATFORM=$(PLATFORM) && \
make clean CONSOLE=xrick      CORE=cores/libretro-xrick PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gw         CORE=cores/libretro-gw PLATFORM=$(PLATFORM) && \
make clean CONSOLE=cdg        CORE=cores/libretro-pocketcdg PLATFORM=$(PLATFORM) && \
make clean CONSOLE=int        CORE=cores/FreeIntv PLATFORM=$(PLATFORM) && \
make clean CONSOLE=msx        CORE=cores/libretro-blueMSX PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gme        CORE=cores/libretro-gme PLATFORM=$(PLATFORM) && \
make clean CONSOLE=pce        CORE=cores/libretro-beetle-pce-fast PLATFORM=$(PLATFORM) && \
make clean CONSOLE=ngpc       CORE=cores/RACE PLATFORM=$(PLATFORM) && \
make clean CONSOLE=dblcherrygb  CORE=cores/libretro-doublecherryGB PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gba        CORE=cores/gpsp PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gbb        CORE=cores/libretro-gambatte PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gbgb       CORE=cores/Gearboy/platforms/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gb         CORE=cores/libretro-tgbdual PLATFORM=$(PLATFORM) && \
make clean CONSOLE=nes        CORE=cores/libretro-fceumm PLATFORM=$(PLATFORM) && \
make clean CONSOLE=nesq       CORE=cores/QuickNES_Core PLATFORM=$(PLATFORM) && \
make clean CONSOLE=pokem      CORE=cores/PokeMini PLATFORM=$(PLATFORM) && \
make clean CONSOLE=snes02     CORE=cores/snes9x2002 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=snes       CORE=cores/snes9x2005 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=sega       CORE=cores/picodrive MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gg         CORE=cores/Gearsystem/platforms/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=zx81       CORE=cores/libretro-81 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=spec       CORE=cores/libretro-fuse PLATFORM=$(PLATFORM) && \
make clean CONSOLE=thom       CORE=cores/theodore PLATFORM=$(PLATFORM) && \
make clean CONSOLE=vec        CORE=cores/libretro-vecx PLATFORM=$(PLATFORM) && \
make clean CONSOLE=wsv        CORE=cores/potator/platform/libretro PLATFORM=$(PLATFORM) && \

#working but issues
make clean CONSOLE=amstrad    CORE=cores/libretro-crocods PLATFORM=$(PLATFORM) && \
make clean CONSOLE=arduboy    CORE=cores/arduous PLATFORM=$(PLATFORM) && \
make clean CONSOLE=lnxb       CORE=cores/libretro-beetle-lynx PLATFORM=$(PLATFORM) && \
make clean CONSOLE=bk         CORE=cores/bk-emulator MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=c64sc         CORE=cores/libretro-vice EMUTYPE=x64sc PLATFORM=$(PLATFORM) && \
make clean CONSOLE=c64           CORE=cores/libretro-vice EMUTYPE=x64 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=c64f        CORE=cores/libretro-frodo EMUTYPE=frodo PLATFORM=$(PLATFORM) && \
make clean CONSOLE=c64fc       CORE=cores/libretro-frodo EMUTYPE=frodosc PLATFORM=$(PLATFORM) && \
make clean CONSOLE=vic20         CORE=cores/libretro-vice EMUTYPE=xvic PLATFORM=$(PLATFORM) && \
make clean CONSOLE=fake08     CORE=cores/fake-08/platform/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=lowres-nx  CORE=cores/lowres-nx/platform/LibRetro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=mrboom     CORE=cores/libretro-mrboom PLATFORM=$(PLATFORM) && \
make clean CONSOLE=jnb        CORE=cores/libretro-jumpnbump PLATFORM=$(PLATFORM) && \
make clean CONSOLE=cavestory  CORE=cores/libretro-nxengine PLATFORM=$(PLATFORM) && \
make clean CONSOLE=x48        CORE=cores/libretro-x48 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=o2em       CORE=cores/libretro-o2em PLATFORM=$(PLATFORM) && \
make clean CONSOLE=pcesgx     CORE=cores/libretro-beetle-supergrafx PLATFORM=$(PLATFORM) && \
make clean CONSOLE=pc8800     CORE=cores/libretro-quasi88 PLATFORM=$(PLATFORM) && \
make clean CONSOLE=pcfx       CORE=cores/libretro-beetle-pcfx PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gbav       CORE=cores/vba-next PLATFORM=$(PLATFORM) && \
make clean CONSOLE=mgba       CORE=cores/mgba PLATFORM=$(PLATFORM) && \
make clean CONSOLE=nest       CORE=cores/nestopia/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=vb         CORE=cores/libretro-beetle-vb PLATFORM=$(PLATFORM) && \
make clean CONSOLE=gpgx       CORE=cores/Genesis-Plus-GX MAKEFILE=-fMakefile.libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=geolith    CORE=cores/libretro-geolith/libretro PLATFORM=$(PLATFORM) && \
make clean CONSOLE=xmil       CORE=cores/libretro-xmil/libretro PLATFORM=$(PLATFORM) && \

#test cores
make clean CONSOLE=testadv CORE=cores/libretro-samples/tests/test_advanced PLATFORM=$(PLATFORM) && \
make clean CONSOLE=testwav CORE=cores/libretro-samples/audio/audio_playback_wav PLATFORM=$(PLATFORM) && \

true
