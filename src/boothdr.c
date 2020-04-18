/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright 2020, Anuradha Weeraman
 */

#include "boothdr.h"
#include "memory.h"

/*
 * Extract multiboot provided information
 */
void init_mb(uint64_t magic, uint64_t addr) {
  struct multiboot_tag *tag;
  multiboot_memory_map_t *mmap;

  // Check if bootloader complies with multiboot2
  if (magic == MULTIBOOT2_BOOTLOADER_MAGIC) {
    printk("Multiboot2 header: 0x%u [valid]\n", magic);
  }

  for (tag = (struct multiboot_tag *) ((uint32_t) (addr + 8));
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag +
                                      ((tag->size + 7) & ~7))) {
    switch (tag->type) {
      case MULTIBOOT_TAG_TYPE_CMDLINE:
        printk("  CMDLINE, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
        printk("  BOOT_LOADER: %s\n",
            ((struct multiboot_tag_string *) tag)->string);
        break;

      case MULTIBOOT_TAG_TYPE_MODULE:
        printk("  MODULE, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
        printk("  BASIC_MEMINFO, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_BOOTDEV:
        printk("  BOOTDEV, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_MMAP:
        printk("  MMAP, size 0x%u\n", tag->size);
        int counter = 0;
        for (mmap = ((struct multiboot_tag_mmap *) tag)->entries;
            (multiboot_uint8_t *) mmap < (multiboot_uint8_t *) tag + tag->size;
            mmap = (multiboot_memory_map_t *)
                   ((unsigned long) mmap + ((struct multiboot_tag_mmap *) tag)->entry_size)) {
                add_mem_region(counter,
                               (uint64_t) mmap->addr,
                               (uint64_t) (mmap->addr + mmap->len),
                               (uint32_t) mmap->len,
                               (uint32_t) mmap->type);
                set_num_mem_regions(counter++);
        }
        break;

      case MULTIBOOT_TAG_TYPE_VBE:
        printk("  VBE, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
        printk("  FRAMEBUFFER, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
        printk("  ELF_SECTIONS, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_APM:
        printk("  APM, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI32:
        printk("  EFI32, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI64:
        printk("  EFI64, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_SMBIOS:
        printk("  SMBIOS, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_ACPI_OLD:
        printk("  ACPI_OLD, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_ACPI_NEW:
        printk("  ACPI_NEW, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_NETWORK:
        printk("  NETWORK, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI_MMAP:
        printk("  EFI_MMAP, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI_BS:
        printk("  EFI_BS, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI32_IH:
        printk("  EFI32_IH, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_EFI64_IH:
        printk("  EFI64_IH, size 0x%u\n", tag->size);
        break;

      case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:
        printk("  LOAD_BASE_ADDR, size 0x%u\n", tag->size);
        break;
    }
  }
}