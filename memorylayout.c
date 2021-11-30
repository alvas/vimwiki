/*
 * memorylayout.c
 * Copyright (C) 2021 qingyun <qingyun.oracle@gmail.com>
 *
 * Distributed under terms of the MIT license.
 *
 * $ulimit -s unlimited; ./memorylayout
 * 
 * $ulimit -s 100; ./memorylayout
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char cmd[32];
    brk((void*)0x80510000);
    sprintf(cmd, "cat /proc/self/maps");
    system(cmd);
    return 0;
}


