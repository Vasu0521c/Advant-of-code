#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

typedef uint64_t byte64;
typedef uint32_t byte32;
typedef uint8_t  byte;

byte32  left_rotate(byte32 value, byte32 rotate_times);
;

byte32* words_block(byte *block);
byte*   padder(char *input);

byte32  MD5(byte32 *M);

byte32  F(byte32 B, byte32 C, byte32 D);
byte32  G(byte32 B, byte32 C, byte32 D);
byte32  H(byte32 B, byte32 C, byte32 D);
byte32  I(byte32 B, byte32 C, byte32 D);

byte32* words_block(byte *block) {

    byte32 *word = calloc(16, (sizeof(byte32)));

    byte i = 0;

    while (i < 16) {

      for (byte j = 0; j < 4; j++) {
          word[i] |= (byte32) block[i * 4 + j] << (j * 8);
      }

      i++;
    }

    free(block);

    return word;
}

byte* padder(char *input) {

    byte *block    = calloc(64, sizeof(byte));

    int length = 0;

    while (*input != '\0' && *input != EOF) {
        block[length] = (byte) *input;
        length++;
        input++;
    }

    block[length] = 0x80;
    byte64 len  = (byte64) length * 8;

    for (int i = 0; i < 8; i++) {
        block[56 + i] = (byte) (len >> (i * 8));
    }
    return block;
}

byte32 left_rotate(byte32 value, byte32 rotate_times) {

    return (value << rotate_times) | (value >> (32-rotate_times));
}

byte32 endian_conversion(byte32 value) {
  return ((value & 0x000000ff) << 24 |
          (value & 0x0000ff00) << 8  |
          (value & 0x00ff0000) >> 8  |
          (value & 0xff000000) >> 24);
}

byte32 F(byte32 B, byte32 C, byte32 D) {

    return (B & C) | ((~B) & D);
}

byte32 G(byte32 B, byte32 C, byte32 D) {

    return (B & D) | (C & (~D));
}

byte32 H(byte32 B, byte32 C, byte32 D) {
    
    return (B ^ C ^ D);
}
byte32 I(byte32 B, byte32 C, byte32 D) {
    
    return C ^ (B | (~D));
}

byte32 MD5(byte32 *M) {

    byte32 A = 0x67452301;
    byte32 B = 0xefcdab89;
    byte32 C = 0x98badcfe;
    byte32 D = 0x10325476;

    byte32 a = A;
    byte32 b = B;
    byte32 c = C;
    byte32 d = D;

    byte32 T[64] = {0};

    for (int i = 0; i < 64; i++) {
        T[i] = (byte32) (fabs(sin(i + 1)) * pow(2, 32));
    }

    static const byte32 S[64] = {

        7,  12,  17,  22,
        7,  12,  17,  22,
        7,  12, 17, 22,
       7,  12,17, 22,

        5, 9, 14, 20,
        5, 9, 14, 20,
        5, 9, 14, 20,
        5, 9, 14, 20,

        4, 11, 16, 23,
        4, 11, 16, 23,
        4, 11, 16, 23,
        4, 11, 16, 23,

        6, 10, 15, 21,
        6, 10, 15, 21,
        6, 10, 15, 21,
        6, 10, 15, 21
    };

    for (int i = 0; i < 64; i++) {

        byte32 f;
        int k;

        if (i < 16) {
            f = F(B, C, D);
            k = i;
        } else if (i < 32) {
            f = G(B, C, D);
            k = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(B, C, D);
            k = (3 * i + 5) % 16;
        } else {
            f = I(B, C, D);
            k = (7 * i) % 16;
        }
        byte32 temp = B + left_rotate(
            A + f + M[k] + T[i],
            S[i]);

        A = D;
        D = C;
        C = B;
        B = temp;
    }
    a += A;
    b += B;
    c += C;
    d += D;

    return endian_conversion(a);
}

void zero_MD5(char *input, int size) {

    int i = 0;
    char temp1[size + 2];

    while(*input != '\0') {
        temp1[i] = *input;
        input++;
        i++;
    }
    temp1[i] = '\0';

    int k = 0;
    for (i = 0; ; i++) {

        char temp[1024];
        char temp2[1024];
        memset(temp, '\0', 1023);
        memset(temp2, '\0', 1023);

        memcpy(temp, temp1, size * (sizeof(char)));

        snprintf(temp2, 1023, "%s%d",temp, i);
        byte32 *m = words_block(padder(temp2));
        byte32 val = MD5(m);
        free(m);

        if (val <= 4095 && k == 0) {
            printf("value for hex with five zeroes : %d\n", i);
            k++;
        }
        if(val <= 255) {
            printf("value for hex with six zeroes : %d\n", i);
            return;

        }
    }
    return;
}

int main() {

    int size      = 0;
    FILE *fileptr = fopen("../inputs/2015day4.txt", "r");

    fseek(fileptr, 0L, SEEK_END);
    size = ftell(fileptr);

    char *input = malloc(size + 1);
    fseek(fileptr, 0L, SEEK_SET);

    fread(input, 1, size, fileptr);
    input[size - 1] = '\0';

    zero_MD5(input, size);
    return 0;
}
