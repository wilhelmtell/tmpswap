/******************************************************************************
 * Copyright 2010 Matan Nassau
 *
 * This file is part of tmpswap.
 *
 * tmpswap is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * tmpswap is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * tmpswap.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include <stdio.h>
#include "config.h"

int main(int argc, char* argv[])
{
    FILE* tmp = NULL;
    char tmpfilenamebuf[FILENAME_MAX] = {0};
    char* tmpfilename = 0;
    char ch = 0;

    if( argc != 2 ) {
        printf("Usage:  %s <filename>\n", BINNAME);
        return 1;
    }
    if( (tmpfilename = tmpnam(tmpfilenamebuf)) == NULL ) {
        perror(NULL);
        return 1;
    }
    if( (tmp = fopen(tmpfilename, "w")) == NULL ) {
        perror(NULL);
        return 1;
    }
    while( (ch = fgetc(stdin)) != EOF ) fputc(ch, tmp);
    fclose(tmp);
    if( (rename(tmpfilename, argv[1])) != 0 )
        perror(NULL);
    return 0;
}
