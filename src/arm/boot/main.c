/**
 * SPDX-FileCopyrightText: 2020 Anuradha Weeraman <anuradha@weeraman.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <sys/serial.h>

#define UART0_BASE 0x1c090000
 
void kernel_main() {
        write_serial('O');
}
