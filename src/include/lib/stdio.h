/**
 * SPDX-FileCopyrightText: 2020 Anuradha Weeraman <anuradha@weeraman.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef TERMIO_H
#define TERMIO_H

int   prints(char *str);
int   putchar(int c);
int   getchar(void);
char *getstr(char *buf, int size);
void  printf(const char *fmt, ...);

#endif