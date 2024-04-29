#include "serpent_functions.h"

int main(int argc, const char *argv[])
{
    // Regular text input
    const char *test_string = "Hello World!";
    const char *key_string = "MySecretKey12345"; // Key must still be 128 bits

    unsigned char *encrypted_string = malloc(16 /*bytes*/);
    unsigned char *decrypted_string = malloc(16 /*bytes*/);

    // Assuming serpent_encrypt_standard and serpent_decrypt_standard now handle text
    serpent_encrypt_standard(test_string, key_string, encrypted_string, 16);
    printHex(encrypted_string, 16, "Encrypted Cipher:");
    printf("\n");

    serpent_decrypt_standard(encrypted_string, key_string, decrypted_string, 16);
    printf("Decrypted Text: %s\n", decrypted_string);

    free(encrypted_string);
    free(decrypted_string);

    return 0;
}
