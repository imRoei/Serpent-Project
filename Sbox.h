#ifndef SERPENT_SBOXES_H
#define SERPENT_SBOXES_H

// Serpent S-boxes definitions
uint32_t S[32][16] = {
    {3, 8, 15, 1, 10, 6, 5, 11, 14, 13, 4, 2, 7, 0, 9, 12}, /* S0: */
    {15, 12, 2, 7, 9, 0, 5, 10, 1, 11, 14, 8, 6, 13, 3, 4}, /* S1: */
    {8, 6, 7, 9, 3, 12, 10, 15, 13, 1, 14, 4, 0, 11, 5, 2}, /* S2: */
    {0, 15, 11, 8, 12, 9, 6, 3, 13, 1, 2, 4, 10, 7, 5, 14}, /* S3: */
    {1, 15, 8, 3, 12, 0, 11, 6, 2, 5, 4, 10, 9, 14, 7, 13}, /* S4: */
    {15, 5, 2, 11, 4, 10, 9, 12, 0, 3, 14, 8, 13, 6, 7, 1}, /* S5: */
    {7, 2, 12, 5, 8, 4, 6, 11, 14, 9, 1, 15, 13, 3, 10, 0}, /* S6: */
    {1, 13, 15, 0, 14, 8, 2, 11, 7, 4, 12, 10, 9, 3, 5, 6}, /* S7: */
};

// Function to apply S-box transformation
unsigned char applySbox(int boxNumber, unsigned char input)
{
    return S[boxNumber][input];
}

#endif // SERPENT_SBOXES_H
