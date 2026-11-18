<h1 align="center">sdlxl</h1>

<p align="center">
  <b>An Atari 800XL or 130XE in an SDL 3 window on Linux or macOS.</b><br>
  6502C with ANTIC's DMA to the cycle, GTIA with all its modes, POKEY sound, disk drives D1: and D2: with ATR and XFD images.
</p>

<p align="center">
  <img alt="Raspberry Pi 5" src="https://img.shields.io/badge/Raspberry%20Pi-5-c51a4a">
  <img alt="Linux arm64 and amd64" src="https://img.shields.io/badge/Linux-arm64%20%7C%20amd64-333">
  <img alt="macOS arm64" src="https://img.shields.io/badge/macOS-arm64-333">
  <img alt="SDL 3" src="https://img.shields.io/badge/SDL-3-1d4ed8">
  <img alt="CPU" src="https://img.shields.io/badge/CPU-6502C-555">
  <img alt="MIT licence" src="https://img.shields.io/badge/licence-MIT-green">
</p>

<p align="center">
  <b>Work in progress:</b> not everything has been tested, and games and demos may or may not
  work satisfactorily.
</p>

<p align="center">
  <img alt="Atari BASIC on the 800XL: PRINT &quot;HELLO FROM THE PI 5&quot; run" src="docs/images/800xl-basic.png" width="49%">
  <img alt="Atari BASIC on the 130XE: PRINT FRE(0), 37902" src="docs/images/130xe-basic.png" width="49%">
  <br>
  <sub>Atari BASIC on the 800XL and on the 130XE, on the Pi.</sub>
</p>

sdlxl runs [esp32xl](https://github.com/rlucencic/esp32xl)'s Atari on 64-bit Linux (arm64 and amd64) and Apple Silicon macOS. SDL 3 provides the window, sound and input. The machine is the
same code as on the ESP32 boards: esp32xl's platform-independent core and
[esp32emu](https://github.com/rlucencic/esp32emu)'s CPU core, on
[sdlemu](https://github.com/rlucencic/sdlemu), the family's desktop runtime: a setup
screen in the window, sound, the host's keyboard and mouse, a web page on your network and a
console.

It belongs to the SDL desktop family of the ESP32 emulators:
[sdlzx](https://github.com/rlucencic/sdlzx) (ZX Spectrum),
[sdlcpc](https://github.com/rlucencic/sdlcpc) (Amstrad CPC),
[sdlcbm](https://github.com/rlucencic/sdlcbm) (Commodore 64 and 128),
[sdlcoco](https://github.com/rlucencic/sdlcoco) (Tandy Color Computer 2 and 3),
[sdlgs](https://github.com/rlucencic/sdlgs) (Apple IIGS),
[sdlmsx](https://github.com/rlucencic/sdlmsx) (MSX1 and MSX2),
[sdlste](https://github.com/rlucencic/sdlste) (Atari STE),
[sdlpc](https://github.com/rlucencic/sdlpc) (IBM PC/XT and PC/AT),
[sdlmac](https://github.com/rlucencic/sdlmac) (Macintosh Plus, SE, Classic),
[sdlmac2](https://github.com/rlucencic/sdlmac2) (Macintosh LC and II),
[sdlmac3](https://github.com/rlucencic/sdlmac3) (Macintosh LC II and LC III),
[sdlarc](https://github.com/rlucencic/sdlarc) (Acorn Archimedes),
[sdlami](https://github.com/rlucencic/sdlami) (Amiga 500, 2000, 600, 1200).

## Features

**The machines**
- **Atari 800XL** (64 KB) and **130XE** (128 KB: four more 16 KB banks at
  `$4000`, for the CPU and ANTIC separately), **PAL or NTSC**, **Atari
  BASIC** on or off, chosen on the setup screen
- **6502C**: every bus cycle as the real CPU does it, on the shared 6502 core
- **ANTIC**: its DMA takes the CPU's cycles where the real one does (display
  list, screen data, characters, players and missiles, memory refresh), and
  WSYNC holds the CPU to the cycle; all text and graphics modes (2 to F),
  horizontal and vertical fine scrolling, narrow, normal and wide
  playfields, display list and vertical blank interrupts
- **GTIA**: players and missiles in all sizes, priority as GTIA's own logic
  (the fifth player, multicolour players), collisions, the GTIA modes 9, 10
  and 11 (16 shades, 9 colours, 16 hues), colour changes in the middle of a
  line timed to the colour clock, PAL and NTSC palettes
- **POKEY**: four sound channels, 8 and 16-bit timers at 64 kHz, 15 kHz or
  1.79 MHz, the 4, 5, 9 and 17-bit noise generators, high-pass filters,
  volume-only mode for samples, timer interrupts, the keyboard, RANDOM, the
  console speaker
- **PIA**: the XL's memory control (OS ROM, BASIC, Self Test, the 130XE's
  banks) and the joystick ports

**Disk drives**
- **D1: and D2:** on the SIO bus, like a 1050 that also does double density:
  status, read, write, format (single and enhanced density) and the PERCOM
  block that DOSes ask for
- **`.ATR`** (128 and 256-byte sectors, whichever way the first three sectors
  are stored) and **`.XFD`** images; writes go back into the image file
- **Fast**: the OS's disk calls are served straight from its device control
  block. Programs that work POKEY's serial port themselves still find the
  whole bus, byte by byte at 19,200 baud
- **New blank disks**: 90 KB single, 130 KB enhanced (1050) or 180 KB double
  density, ready for DOS to format

**Around it**
- **A window** of its own on the Pi's desktop (X11 or Wayland), resizable, full screen
  with Ctrl+Alt+F; the picture in the machine's shape, sharp pixels
- **Setup screen** in the window, first thing at start and any time with Ctrl+Alt+M:
  model, TV, BASIC, the sound's volume, the drives and their images (insert, eject, new
  blank ones), Start / Back / Restart, Reset
- **The Pi's keyboard and mouse**: keys by position, as the boards' Bluetooth keyboards;
  a click in the window gives the mouse to the machine, Ctrl+Alt+G takes it back
- **Web page** at `http://<the Pi>:8080/`: drop images (or ZIP files) onto it, insert
  them, make blank ones, and watch the machine and its drives live
- **Sound** through SDL (PipeWire, PulseAudio or ALSA), the machine paced by the clock
- **Console** on the terminal and on `127.0.0.1:6400`: keys, typing, drives, screenshots

<p align="center">
  <img src="docs/images/setup.png" width="80%" alt="The setup screen in the window: the Atari's choices, the sound, Disks and Start">
  <br><sub>The setup screen in the window, before the Atari starts</sub>
</p>

## Getting started

### 1. What you need

- 64-bit Linux (including Raspberry Pi 5) or Apple Silicon macOS with SDL 3.2 or newer. See [desktop build dependencies](https://github.com/rlucencic/sdlemu#building).
- [esp32emu](https://github.com/rlucencic/esp32emu), [sdlemu](https://github.com/rlucencic/sdlemu)
  and [esp32xl](https://github.com/rlucencic/esp32xl), cloned next to this project
- The ROMs (below)

### 2. Build

```sh
git clone https://github.com/rlucencic/esp32emu.git
git clone https://github.com/rlucencic/sdlemu.git
git clone https://github.com/rlucencic/esp32xl.git
git clone https://github.com/rlucencic/sdlxl.git && cd sdlxl
cmake -S . -B build -G Ninja && cmake --build build
```

### 3. ROMs

In the data folder's `xl/roms/` (`~/sdlemu/xl/roms`), named as esp32xl's:
`atarixl.rom` (the XL/XE OS, 16 KB) and `ataribas.rom` (BASIC, 8 KB). Not
part of this repository.

### 4. First start

1. `build/sdlxl`: the setup screen opens in a window.
2. Choose the model and click **Start**.
3. Put images into `~/sdlemu/xl/`, drop them on the window or the web page, and
   insert them on the setup screen's **Disks** page.

## Using it

| To | Do |
|---|---|
| Get back to the setup screen | Ctrl+Alt+M (the machine waits meanwhile) |
| Full screen | Ctrl+Alt+F |
| Give the mouse to the machine, take it back | A click in the window; Ctrl+Alt+G |
| Run as fast as it goes (warp) | Ctrl+Alt+W, again for real speed |
| Take a screenshot | Ctrl+Alt+S (into `~/sdlemu/screenshots`), or the console's `s` |
| Insert an image | The setup screen's **Disks** page, drop it on the window or the web page, or name it on the command line: `build/sdlxl dos25.atr` |
| Start straight into the machine | `build/sdlxl -S`, with the setup screen's rows as `--choice`: `build/sdlxl -S --choice Model=130XE` |
| Show the window on another computer | Log in with `ssh -C -Y <the Pi>` and start it there: fine for still pictures; games want the Pi's own monitor |
| Use DOS 2.5 | Boot its disk; **A** and Return lists the directory, **L** loads a binary file, **B** goes to BASIC |
| Load a BASIC program | `RUN "D:NAME.BAS"` (or `LOAD`, `ENTER` for listings) |
| Self Test | `BYE` in BASIC, or start with BASIC off and no disk |

Images live in `~/sdlemu/xl/`, settings in `~/.config/sdlemu/settings.ini`; the
inserted images are remembered across starts. `build/sdlxl --help` lists the options.

**Keyboard**: letters by position; digits and symbols by the character they
give on a US keyboard, with SHIFT as the Atari needs it (Shift+' is ", which
is Shift+2 on the Atari). Return, Esc, Tab, Backspace (DELETE BACK S), Caps
Lock (CAPS) and Ctrl as themselves; Delete is Ctrl+DELETE, Insert
Ctrl+INSERT, Home CLEAR, `` ` `` and End the inverse (Atari) key; the cursor
keys are Ctrl with `-` `=` `+` `*`. F1 HELP, F2 START, F3 SELECT, F4 OPTION,
F5 RESET, F7 or Pause BREAK.

**Joystick**: the numeric keypad (8 4 6 2 and the diagonals, 0 or 5 fire) in
port 1; F11 switches it to port 2. F12 makes the cursor keys the joystick as
well, with Alt as fire.

## How it works

```mermaid
flowchart LR
  subgraph emu [Emulation thread]
    EMU["Emulation<br>6502C · ANTIC · GTIA<br>POKEY · PIA · SIO drives"]
  end
  subgraph main [Main thread]
    WIN["Window · setup screen<br>SDL 3"]
  end
  subgraph others [Other threads]
    WEB[Web page :8080]
    CON[Console :6400]
  end
  EMU -- picture --> WIN
  EMU -- sound --> SND[SDL audio]
  WIN -- keys · mouse --> EMU
  DATA[("~/sdlemu<br>xl · xl/roms")]
  EMU <--> DATA
  WEB <--> DATA
```

- **[esp32xl](https://github.com/rlucencic/esp32xl)'s `components/atari_xl`**: the Atari,
  platform independent: the same code runs on the ESP32 boards.
- **`src/`**: the glue, esp32xl's `main/main.c` ported: memory, ROMs, settings, keyboard map,
  drives and status.
- **[sdlemu](https://github.com/rlucencic/sdlemu)**: the window, the setup screen, sound,
  input, the web page, the console, the data folder and the settings.
- **[esp32emu](https://github.com/rlucencic/esp32emu)**: the CPU core (6502C).

## Development

```sh
../sdlemu/tools/pi.sh sdlxl build        # from another computer: sync to the Pi, build there
../sdlemu/tools/pi.sh sdlxl run          # its window on this computer (ssh -C -Y)
../sdlemu/tools/pi.sh sdlxl headless     # no window: drive it through the console
../sdlemu/tools/console.sh i 's /tmp/shot.png'
```

`CLAUDE.md` has the details: the layout, how it was ported, the checks; esp32xl's own
`CLAUDE.md` has the machine's.

## Limitations

- Checked on the Pi through its console and screenshots: the 800XL and 130XE at full speed, BASIC; a blank disk made. Not yet by hand
  in the window, with the sound heard, or with much software.
- Over X forwarding (`ssh -Y`) every changed picture crosses the network: 8 to 15 a second.
- Tested so far with BASIC, the Self Test, Atari DOS 2.5 (formatting and
  copying too), MyDOS 4.50 in double density, the 130XE's banks and a few
  graphics demos; **games haven't been tried yet**.
- No cartridges, `.XEX` or `.CAS` files, no copy-protected disk images
  (`.ATX`, `.PRO`); no cassette, printer or 850 interface.
- ANTIC reads its registers as a line begins: a change in the middle of a
  line (a new character set, scrolling) shows from the next line. NTSC
  colour artefacts in high resolution aren't shown.
- Disks are faster than a real 1050: the drive answers at once, with no
  waiting for the disk to turn.

## Credits

- Avery Lee's [Altirra Hardware Reference Manual](https://www.virtualdub.org/altirra.html):
  the reference for ANTIC's DMA timing, GTIA's priority logic, POKEY, the SIO
  protocol and the disk drives
- Klaus Dormann's 6502 functional tests
- [SDL](https://libsdl.org) 3 for the window, the sound and the input

## Licence

[MIT](LICENSE).

Atari, 800XL and 130XE are trademarks of their owners. The ROM images are not
part of this repository.
