#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emu/emu.h"
#include "rom_store.h"

static const struct {
    const char *name;
    uint8_t slot;
    uint32_t size;
} roms[ROM_COUNT] = {
    { "atarixl.rom", 0, 16384 }, { "ataribas.rom", 1, 8192 },
};

const char *rom_store_name(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].name : "";
}

uint32_t rom_store_size(rom_id_t id)
{
    return id < ROM_COUNT ? roms[id].size : 0;
}

/* Not erased flash, not zeros: something at the start of most 4 KB blocks
 * (a ROM may have one that starts with $FF bytes)
 */
static bool plausible(const uint8_t *p, uint32_t size)
{
    int blank = 0, blocks = 0;
    for (uint32_t off = 0; off < size; off += 4096, blocks++) {
        bool ff = true, zero = true;
        for (int i = 0; i < 64; i++) {
            ff &= p[off + i] == 0xFF;
            zero &= p[off + i] == 0x00;
        }
        blank += ff || zero;
    }
    return blank * 4 <= blocks;
}

bool rom_store_load(rom_id_t id, uint8_t *buf)
{
    if (id >= ROM_COUNT) {
        return false;
    }
    uint32_t size = rom_store_size(id);
    return emu_rom_read(roms[id].name, buf, size) == (long)size && plausible(buf, size);
}
