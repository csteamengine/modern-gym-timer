#include <stdint.h>

static const uint8_t numbertable[] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x77, /* a */
    0x7C, /* b */
    0x39, /* C */
    0x5E, /* d */
    0x79, /* E */
    0x71, /* F */
};

static const uint8_t ascii_lookup[] = {
    0b00000000, /* (space) */
    0b10000110, /* ! */
    0b00100010, /* " */
    0b01111110, /* # */
    0b01101101, /* $ */
    0b11010010, /* % */
    0b01000110, /* & */
    0b00100000, /* ' */
    0b00101001, /* ( */
    0b00001011, /* ) */
    0b00100001, /* * */
    0b01110000, /* + */
    0b00010000, /* , */
    0b01000000, /* - */
    0b10000000, /* . */
    0b01010010, /* / */
    0b00111111, /* 0 */
    0b00000110, /* 1 */
    0b01011011, /* 2 */
    0b01001111, /* 3 */
    0b01100110, /* 4 */
    0b01101101, /* 5 */
    0b01111101, /* 6 */
    0b00000111, /* 7 */
    0b01111111, /* 8 */
    0b01101111, /* 9 */
    0b00001001, /* : */
    0b00001101, /* ; */
    0b01100001, /* < */
    0b01001000, /* = */
    0b01000011, /* > */
    0b11010011, /* ? */
    0b01011111, /* @ */
    0b01110111, /* A */
    0b01111100, /* B */
    0b00111001, /* C */
    0b01011110, /* D */
    0b01111001, /* E */
    0b01110001, /* F */
    0b00111101, /* G */
    0b01110110, /* H */
    0b00110000, /* I */
    0b00011110, /* J */
    0b01110101, /* K */
    0b00111000, /* L */
    0b00010101, /* M */
    0b00110111, /* N */
    0b00111111, /* O */
    0b01110011, /* P */
    0b01101011, /* Q */
    0b00110011, /* R */
    0b01101101, /* S */
    0b01111000, /* T */
    0b00111110, /* U */
    0b00111110, /* V */
    0b00101010, /* W */
    0b01110110, /* X */
    0b01101110, /* Y */
    0b01011011, /* Z */
    0b00111001, /* [ */
    0b01100100, /* \ */
    0b00001111, /* ] */
    0b00100011, /* ^ */
    0b00001000, /* _ */
    0b00000010, /* ` */
    0b01011111, /* a */
    0b01111100, /* b */
    0b01011000, /* c */
    0b01011110, /* d */
    0b01111011, /* e */
    0b01110001, /* f */
    0b01101111, /* g */
    0b01110100, /* h */
    0b00010000, /* i */
    0b00001100, /* j */
    0b01110101, /* k */
    0b00110000, /* l */
    0b00010100, /* m */
    0b01010100, /* n */
    0b01011100, /* o */
    0b01110011, /* p */
    0b01100111, /* q */
    0b01010000, /* r */
    0b01101101, /* s */
    0b01111000, /* t */
    0b00011100, /* u */
    0b00011100, /* v */
    0b00010100, /* w */
    0b01110110, /* x */
    0b01101110, /* y */
    0b01011011, /* z */
    0b01000110, /* { */
    0b00110000, /* | */
    0b01110000, /* } */
    0b00000001, /* ~ */
    0b00000000, /* (del) */
};

#define ASCII_CAPITAL_A ascii_lookup[33]
#define ASCII_CAPITAL_B ascii_lookup[34]
#define ASCII_CAPITAL_C ascii_lookup[35]
#define ASCII_CAPITAL_D ascii_lookup[36]
#define ASCII_CAPITAL_E ascii_lookup[37]
#define ASCII_CAPITAL_F ascii_lookup[38]
#define ASCII_CAPITAL_G ascii_lookup[39]
#define ASCII_CAPITAL_H ascii_lookup[40]
#define ASCII_CAPITAL_I ascii_lookup[41]
#define ASCII_CAPITAL_J ascii_lookup[42]
#define ASCII_CAPITAL_K ascii_lookup[43]
#define ASCII_CAPITAL_L ascii_lookup[44]
#define ASCII_CAPITAL_M ascii_lookup[45]
#define ASCII_CAPITAL_N ascii_lookup[46]
#define ASCII_CAPITAL_O ascii_lookup[47]
#define ASCII_CAPITAL_P ascii_lookup[48]
#define ASCII_CAPITAL_Q ascii_lookup[49]
#define ASCII_CAPITAL_R ascii_lookup[50]
#define ASCII_CAPITAL_S ascii_lookup[51]
#define ASCII_CAPITAL_T ascii_lookup[52]
#define ASCII_CAPITAL_U ascii_lookup[53]
#define ASCII_CAPITAL_V ascii_lookup[54]
#define ASCII_CAPITAL_W ascii_lookup[55]
#define ASCII_CAPITAL_X ascii_lookup[56]
#define ASCII_CAPITAL_Y ascii_lookup[57]
#define ASCII_CAPITAL_Z ascii_lookup[58]
#define ASCII_LOWER_A ascii_lookup[65]
#define ASCII_LOWER_B ascii_lookup[66]
#define ASCII_LOWER_C ascii_lookup[67]
#define ASCII_LOWER_D ascii_lookup[68]
#define ASCII_LOWER_E ascii_lookup[69]
#define ASCII_LOWER_F ascii_lookup[70]
#define ASCII_LOWER_G ascii_lookup[71]
#define ASCII_LOWER_H ascii_lookup[72]
#define ASCII_LOWER_I ascii_lookup[73]
#define ASCII_LOWER_J ascii_lookup[74]
#define ASCII_LOWER_K ascii_lookup[75]
#define ASCII_LOWER_L ascii_lookup[76]
#define ASCII_LOWER_M ascii_lookup[77]
#define ASCII_LOWER_N ascii_lookup[78]
#define ASCII_LOWER_O ascii_lookup[79]
#define ASCII_LOWER_P ascii_lookup[80]
#define ASCII_LOWER_Q ascii_lookup[81]
#define ASCII_LOWER_R ascii_lookup[82]
#define ASCII_LOWER_S ascii_lookup[83]
#define ASCII_LOWER_T ascii_lookup[84]
#define ASCII_LOWER_U ascii_lookup[85]
#define ASCII_LOWER_V ascii_lookup[86]
#define ASCII_LOWER_W ascii_lookup[87]
#define ASCII_LOWER_X ascii_lookup[88]
#define ASCII_LOWER_Y ascii_lookup[89]
#define ASCII_LOWER_Z ascii_lookup[90]


uint8_t get_ascii(int input);
