#include "serpent_functions.h"

int main(int argc, const char *argv[])
{

    // HEX INPUT
    // (8 bits * 4) * 4 = 128 bits
    const char *test_string = "31321654654984984654331321554648";
    // key in this implementation must be 128bits
    const char *key_string = "000000000000000000000000000000000";
    /*                          ^ = msb                        ^ = lsb */
    unsigned char *encrypted_string = malloc(16 /*bytes*/);
    unsigned char *decrypted_string = malloc(16 /*bytes*/);

    unsigned char *test_string_hex = malloc(16);
    hexConvert(test_string, test_string_hex);
    unsigned char *key_string_hex = malloc(16);
    hexConvert(key_string, key_string_hex);

    serpent_encrypt_standard(test_string_hex, key_string_hex, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");
    serpent_decrypt_standard(encrypted_string, key_string_hex, decrypted_string, 16);
    printHex(decrypted_string, 16, "Decrypted Cipher:");

    return 0;
}
