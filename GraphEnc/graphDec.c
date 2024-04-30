#include "../headers/graphs.h"



char *getEncryptedText(Graph **EncryptedBlocks, char firstSpecial, int textLength)
{
    // Set a fixed seed for any randomness used in the encryption process
    double diff;
    char *encryptedText = (char *)malloc(sizeof(char) * textLength + 1); // +1 for null terminator
    encryptedText[textLength] = '\0';                                    // Ensure null termination

    for (int i = 0; i < textLength / block_size; i++)
    {
        for (int j = 0; j < block_size; j++)
        {
            if (i == 0 && j == 0)
            {
                diff = firstSpecial + EncryptedBlocks[0]->adjacencyMatrix[0][1];
                encryptedText[0] = diff;
            }
            else
            {
                // Assuming you want to use the PREVIOUS character in the SAME block:
                diff = encryptedText[i * block_size + j - 1] + EncryptedBlocks[i]->adjacencyMatrix[j][j + 1];
                encryptedText[i * block_size + j] = diff;
            }
        }
    }
    return encryptedText; // Add return!
}


void Decreyption(double key[][keyMatSize], Graph **EncryptedBlocks, int blocknumber, int a, int b)
{
    double inverseKey[keyMatSize][keyMatSize];
    char special = calculateFirstSpecial(key);
    inverseMatrix(key, inverseKey, keyMatSize);
    printf("\nDecryption");
    for (int i = 0; i < blocknumber; i++)
    {
        multiplyMatrices(inverseKey, EncryptedBlocks[i]);
    }
    int textLength = blocknumber * block_size;
    char *Enctext = strdup(getEncryptedText(EncryptedBlocks, special, textLength));
    printf("Not determinent enc: %s\n", Enctext);
    for (int i = 0; i < textLength; i++)
    {
        Enctext[i] -= 'A';
        if (Enctext[i] >= 14)
        {
            Enctext[i] = Enctext[i] + 26;
        }
        else
        {

            Enctext[i] = (Enctext[i] + 26 * 2);
        }
        Enctext[i] += 25 - 'A';
        int inverse = modularInverse(a, 26);
        Enctext[i] = (inverse * (Enctext[i] - b)) % 26;
    }
    char *Decrypted = (char *)malloc((textLength + 1) * sizeof(char));
    for (int i = 0; i < textLength; i++)
    {
        Decrypted[i] = ((int)Enctext[i]) + 'A' + 26;
    }
    printf("Decrypted: %s", Decrypted);
}
