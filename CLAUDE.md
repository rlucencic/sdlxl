# rpi5xl: the Atari 800XL and 130XE on the Raspberry Pi 5

esp32xl's Atari (`../esp32xl/components/atari_xl`, platform independent)
on the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi,
the lessons), the 6502 esp32emu's. The machine's own behaviour, lessons and
tests are esp32xl's CLAUDE.md; this project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Atari as an `emu_machine_t`: esp32xl's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py` |
| `src/settings.c` | esp32xl's, over `emu/nvs.h` (section `xl`) |
| `src/rom_store.c` | `~/rpi5emu/xl/roms/` through `emu_rom_read()` (`port_rom_store.py`): atarixl.rom, ataribas.rom |

Keep `src/main.c` in step with esp32xl's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5xl build
../rpi5emu/tools/pi.sh rpi5xl headless     # or run: the window here
../rpi5emu/tools/console.sh i 'T PRINT FRE(0)\n'
../rpi5emu/tools/pi.sh rpi5xl shot out.png
```

Console: the runtime's (`h`) and esp32xl's: `k <hex>` tap a key, `K <hex>
0|1` (40 Shift, 41 Ctrl, 42 Break, 43 Start, 44 Select, 45 Option),
`T <text>`, `j <port> <bits>`, `W` the Reset key, `P <0|1>` fast disks,
`R <model> [tv]`.

Checked on the Pi (2026-11-15, headless): the 800XL (PAL, BASIC) at 100%,
BASIC typed into; a blank ATR made in D1:; the 130XE (FRE(0) 37902). A
blank disk in D1: at power-on keeps the OS trying to boot it (as a real
one): eject it first. Not yet: the window by hand, sound heard, DOS and
saving to disk, games, NTSC.
