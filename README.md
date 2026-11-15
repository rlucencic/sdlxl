# rpi5xl

An Atari 800XL or 130XE for the Raspberry Pi 5, in a window of its own:
[esp32xl](https://github.com/rlucencic/esp32xl)'s Atari on the
[rpi5emu](https://github.com/rlucencic/rpi5emu) runtime.

- The 6502C with ANTIC's DMA to the cycle, GTIA with all its modes, POKEY
  sound, disk drives D1: and D2: with ATR and XFD images, PAL or NTSC.
- The setup screen (model, TV, BASIC, sound, the drives), the web page for
  the disk images, the console, as the rest of the family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32xl and rpi5xl cloned side by side, then

```sh
cd rpi5xl && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

In the data folder's `roms/` (`~/rpi5emu/roms`), named as esp32xl's:
`atarixl.rom` (the XL/XE OS, 16 KB) and `ataribas.rom` (BASIC, 8 KB). Not
part of this repository.

## Running

```sh
build/rpi5xl                           # the setup screen first
build/rpi5xl -S --choice Model=130XE   # straight into a 130XE
build/rpi5xl dos25.atr                 # with a disk in D1:
```

Disks live in `~/rpi5emu/atari/`. Letters by position, digits and symbols
by the character a US keyboard gives; F1 HELP, F2 START, F3 SELECT, F4
OPTION, F5 RESET, F7 or Pause BREAK; the cursor keys are Ctrl with - = + *.
The numeric keypad is the joystick in port 1 (F11 switches to 2), F12 makes
the cursor keys the joystick too (Alt fire).

## Licence

MIT.
