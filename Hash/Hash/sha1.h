#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string.h>

typedef unsigned int uint;

#define one_block_size_bytes 64 // êîëè÷åñòâî áàéá â áëîêå
#define one_block_size_uints 16 // êîëè÷åñòâî 4áàéòîâûõ  â áëîêå
#define block_expend_size_uints 80 // êîëè÷åñòâî 4áàéòîâûõ â äîïîëíåííîì áëîêå

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5


typedef uint* Block;
typedef uint ExpendBlock[block_expend_size_uints];

const uint H[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
}; // êîíñòàíòû, ñîãëàñíî ñòàíäàðòó

uint cycle_shift_left(uint val, int bit_count);
uint bring_to_human_view(uint val);

uint* sha1(char* message, uint msize_bytes); // îòäàííûé ìàññèâ íóæíî óäàëèòü âðó÷íóþ