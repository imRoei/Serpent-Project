#include <stdint.h> //
typedef unsigned int WORD;
typedef unsigned char BIT;
typedef unsigned char NIBBLE;
typedef WORD BLOCK[4];
typedef uint32_t _128[4];
#define BITS_PER_NIBBLE 4
#define BITS_PER_BLOCK 128
#define BITS_PER_WORD 32
#define WORDS_PER_BLOCK 4
#define NIBBLES_PER_WORD 8

// Updated Function Prototypes
int Key_Padding(const unsigned char *key, unsigned int keyLength, unsigned char *paddedKey);
void Get_Prekeys(const uint32_t *paddedKey, uint32_t *prekeys);
void Get_Subkeys(const uint32_t *prekeys, uint32_t subkeysHat[33][4]); // Corrected prototype
void InitialPermutation(const uint32_t *input, uint32_t *output);
void RoundFunction(uint32_t *block, const uint32_t *subkey);
void LinearTransformation(uint32_t *X);
void serpent_encrypt(const unsigned char *plaintext, const unsigned char *key, unsigned char *output, unsigned int kBytes);
void hexConvert(const char *s, unsigned char *b);
void printHex(const unsigned char *s, int bytelength, const char *message);
void InverseInitialPermutation(const uint32_t *input, uint32_t *result);
void setBit(uint32_t *x, int p, BIT v);