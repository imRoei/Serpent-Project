#ifndef SERPENT_FUNCTIONS_H
#define SERPENT_FUNCTIONS_H

#include "serpent_defs.h"

// all the functions prototypes in order to split all the functions into
// different functions

void InitialPermutation(const uint *input, uint *result);

void InverseInitialPermutation(const uint *input, uint *result);

void FinalPermutation(const uint *input, uint *result);

void InverseFinalPermutation(const uint *input, uint *result);

BIT getBit(WORD x[], int p);

void setBit(uint *x, int p, BIT v);

void LinearTransformation(uint *X, uint *result, uint subkeysHat[33][4]);

void InverseLinearTransformation(uint *X, uint *result, uint subkeysHat[33][4]);

void KeyExpention(const uchar *key, uint *keysplit, uint kBytes);

void KeySchedule(uint subkeysHat[33][4], const uchar *key, uchar *output, uint kBytes);

void serpent_encrypt_standard(const unsigned char *plaintext, const unsigned char *key, unsigned char *output, unsigned int kBytes);

void serpent_decrypt_standard(const unsigned char *plaintext, const unsigned char *key, unsigned char *output, unsigned int kBytes);

void printHex(const unsigned char *s, int bytelength, const char *message);

void hexConvert(const char *s, unsigned char *b);

char *hex_to_string(const char *hex_string);

#endif