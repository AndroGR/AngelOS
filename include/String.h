/*
 *  String.h: Functions to manipulate and make use of strings in C.
 *  Copyright (C) 2022 Aggelos Tselios.
 *
 *  AngelOS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  AngelOS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AngelOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "Types.h"

/* Returns the length of a string given, invalid strings will cause undefined behavior. */
size_t strlen(const char* data);

/* Compares str1 with str2. Will return 0 if they are the same, or 1 otherwise. */
int strcmp(const char* str1, const char* str2);
/* 
 * Compares str1 with str2 as far as len says to do so. If len is larger than strlen(str1)
 * or strlen(str2), this function will return -1.
*/
int strncmp(const char* str1, const char* str2, size_t len);