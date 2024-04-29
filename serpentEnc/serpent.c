#include "../headers/serpent_functions.h"
#include "../headers/Sbox.h"

// main function of encryption
void serpent_encrypt_standard(const unsigned char *plaintext, const unsigned char *key, unsigned char *output, unsigned int kBytes)
{

    // 33 subkeys * 32bits * 4 blocks
    uint subkeysHat[33][4] = {0};
    KeySchedule(subkeysHat, key, output, kBytes);

    /* INITIAL PERMUTATION */

    // ignore bit[0] and bit[127]
    // replace bit[1..126] with bit[(i*32)%127]
    const uint *charpToInt = (const uint *)plaintext;
    uint result[4] = {0};
    InitialPermutation(charpToInt, result);

    /* LINEAR TRANSFORMATION */
    uint X[4] = {0};
    LinearTransformation(X, result, subkeysHat);

    /* FINAL PERMUTATION */

    uint finalResult[4] = {0};
    FinalPermutation(result, finalResult);

    // copy 128 bits to output string
    memcpy(output, finalResult, 16);
}

// main function of decryption
void serpent_decrypt_standard(const unsigned char *plaintext, const unsigned char *key, unsigned char *output, unsigned int kBytes)
{

    uint subkeysHat[33][4] = {0};

    KeySchedule(subkeysHat, key, output, kBytes);

    /*  Start plaintext processing  */

    /* REVERSE FINAL PERMUTATION */

    // ignore bit[0] and bit[127]
    // replace bit[1..126] with bit[(i*32)%127]
    const uint *charpToInt = (const uint *)plaintext;
    uint result[4] = {0};
    InverseFinalPermutation(charpToInt, result);

    // result == Bi

    /* REVERSE LINEAR TRANSFORMATION */

    // 32 rounds
    uint X[4] = {0};
    InverseLinearTransformation(X, result, subkeysHat);

    /* REVERSE INITIAL PERMUTATION */

    uint finalResult[4] = {0};
    InverseInitialPermutation(result, finalResult);

    // copy 128 bits to output string
    memcpy(output, finalResult, 16);
}
