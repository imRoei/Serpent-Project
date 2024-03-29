
#ifndef __Serpent__s_boxes__
#define __Serpent__s_boxes__

typedef unsigned int uint;

uint SBox[32][16] = {
    {3, 8, 15, 1, 10, 6, 5, 11, 14, 13, 4, 2, 7, 0, 9, 12}, /* S0: */
    {15, 12, 2, 7, 9, 0, 5, 10, 1, 11, 14, 8, 6, 13, 3, 4}, /* S1: */
    {8, 6, 7, 9, 3, 12, 10, 15, 13, 1, 14, 4, 0, 11, 5, 2}, /* S2: */
    {0, 15, 11, 8, 12, 9, 6, 3, 13, 1, 2, 4, 10, 7, 5, 14}, /* S3: */
    {1, 15, 8, 3, 12, 0, 11, 6, 2, 5, 4, 10, 9, 14, 7, 13}, /* S4: */
    {15, 5, 2, 11, 4, 10, 9, 12, 0, 3, 14, 8, 13, 6, 7, 1}, /* S5: */
    {7, 2, 12, 5, 8, 4, 6, 11, 14, 9, 1, 15, 13, 3, 10, 0}, /* S6: */
    {1, 13, 15, 0, 14, 8, 2, 11, 7, 4, 12, 10, 9, 3, 5, 6}, /* S7: */
};

uint SBoxInverse[32][16] = {
    {13, 3, 11, 0, 10, 6, 5, 12, 1, 14, 4, 7, 15, 9, 8, 2}, /* InvS0: */
    {5, 8, 2, 14, 15, 6, 12, 3, 11, 4, 7, 9, 1, 13, 10, 0}, /* InvS1: */
    {12, 9, 15, 4, 11, 14, 1, 2, 0, 3, 6, 13, 5, 8, 10, 7}, /* InvS2: */
    {0, 9, 10, 7, 11, 14, 6, 13, 3, 5, 12, 2, 4, 8, 15, 1}, /* InvS3: */
    {5, 0, 8, 3, 10, 9, 7, 14, 2, 12, 11, 6, 4, 15, 13, 1}, /* InvS4: */
    {8, 15, 2, 9, 4, 1, 13, 14, 11, 6, 5, 3, 7, 12, 10, 0}, /* InvS5: */
    {15, 10, 1, 13, 5, 3, 6, 0, 4, 9, 14, 7, 2, 12, 8, 11}, /* InvS6: */
    {3, 0, 6, 13, 9, 14, 15, 8, 5, 12, 11, 7, 10, 1, 4, 2}, /* InvS7: */
};

#define MARKER 0xff
uint LTTable[128][8] = {
    {16, 52, 56, 70, 83, 94, 105, MARKER},
    {72, 114, 125, MARKER},
    {2, 9, 15, 30, 76, 84, 126, MARKER},
    {36, 90, 103, MARKER},
    {20, 56, 60, 74, 87, 98, 109, MARKER},
    {1, 76, 118, MARKER},
    {2, 6, 13, 19, 34, 80, 88, MARKER},
    {40, 94, 107, MARKER},
    {24, 60, 64, 78, 91, 102, 113, MARKER},
    {5, 80, 122, MARKER},
    {6, 10, 17, 23, 38, 84, 92, MARKER},
    {44, 98, 111, MARKER},
    {28, 64, 68, 82, 95, 106, 117, MARKER},
    {9, 84, 126, MARKER},
    {10, 14, 21, 27, 42, 88, 96, MARKER},
    {48, 102, 115, MARKER},
    {32, 68, 72, 86, 99, 110, 121, MARKER},
    {2, 13, 88, MARKER},
    {14, 18, 25, 31, 46, 92, 100, MARKER},
    {52, 106, 119, MARKER},
    {36, 72, 76, 90, 103, 114, 125, MARKER},
    {6, 17, 92, MARKER},
    {18, 22, 29, 35, 50, 96, 104, MARKER},
    {56, 110, 123, MARKER},
    {1, 40, 76, 80, 94, 107, 118, MARKER},
    {10, 21, 96, MARKER},
    {22, 26, 33, 39, 54, 100, 108, MARKER},
    {60, 114, 127, MARKER},
    {5, 44, 80, 84, 98, 111, 122, MARKER},
    {14, 25, 100, MARKER},
    {26, 30, 37, 43, 58, 104, 112, MARKER},
    {3, 118, MARKER},
    {9, 48, 84, 88, 102, 115, 126, MARKER},
    {18, 29, 104, MARKER},
    {30, 34, 41, 47, 62, 108, 116, MARKER},
    {7, 122, MARKER},
    {2, 13, 52, 88, 92, 106, 119, MARKER},
    {22, 33, 108, MARKER},
    {34, 38, 45, 51, 66, 112, 120, MARKER},
    {11, 126, MARKER},
    {6, 17, 56, 92, 96, 110, 123, MARKER},
    {26, 37, 112, MARKER},
    {38, 42, 49, 55, 70, 116, 124, MARKER},
    {2, 15, 76, MARKER},
    {10, 21, 60, 96, 100, 114, 127, MARKER},
    {30, 41, 116, MARKER},
    {0, 42, 46, 53, 59, 74, 120, MARKER},
    {6, 19, 80, MARKER},
    {3, 14, 25, 100, 104, 118, MARKER},
    {34, 45, 120, MARKER},
    {4, 46, 50, 57, 63, 78, 124, MARKER},
    {10, 23, 84, MARKER},
    {7, 18, 29, 104, 108, 122, MARKER},
    {38, 49, 124, MARKER},
    {0, 8, 50, 54, 61, 67, 82, MARKER},
    {14, 27, 88, MARKER},
    {11, 22, 33, 108, 112, 126, MARKER},
    {0, 42, 53, MARKER},
    {4, 12, 54, 58, 65, 71, 86, MARKER},
    {18, 31, 92, MARKER},
    {2, 15, 26, 37, 76, 112, 116, MARKER},
    {4, 46, 57, MARKER},
    {8, 16, 58, 62, 69, 75, 90, MARKER},
    {22, 35, 96, MARKER},
    {6, 19, 30, 41, 80, 116, 120, MARKER},
    {8, 50, 61, MARKER},
    {12, 20, 62, 66, 73, 79, 94, MARKER},
    {26, 39, 100, MARKER},
    {10, 23, 34, 45, 84, 120, 124, MARKER},
    {12, 54, 65, MARKER},
    {16, 24, 66, 70, 77, 83, 98, MARKER},
    {30, 43, 104, MARKER},
    {0, 14, 27, 38, 49, 88, 124, MARKER},
    {16, 58, 69, MARKER},
    {20, 28, 70, 74, 81, 87, 102, MARKER},
    {34, 47, 108, MARKER},
    {0, 4, 18, 31, 42, 53, 92, MARKER},
    {20, 62, 73, MARKER},
    {24, 32, 74, 78, 85, 91, 106, MARKER},
    {38, 51, 112, MARKER},
    {4, 8, 22, 35, 46, 57, 96, MARKER},
    {24, 66, 77, MARKER},
    {28, 36, 78, 82, 89, 95, 110, MARKER},
    {42, 55, 116, MARKER},
    {8, 12, 26, 39, 50, 61, 100, MARKER},
    {28, 70, 81, MARKER},
    {32, 40, 82, 86, 93, 99, 114, MARKER},
    {46, 59, 120, MARKER},
    {12, 16, 30, 43, 54, 65, 104, MARKER},
    {32, 74, 85, MARKER},
    {36, 90, 103, 118, MARKER},
    {50, 63, 124, MARKER},
    {16, 20, 34, 47, 58, 69, 108, MARKER},
    {36, 78, 89, MARKER},
    {40, 94, 107, 122, MARKER},
    {0, 54, 67, MARKER},
    {20, 24, 38, 51, 62, 73, 112, MARKER},
    {40, 82, 93, MARKER},
    {44, 98, 111, 126, MARKER},
    {4, 58, 71, MARKER},
    {24, 28, 42, 55, 66, 77, 116, MARKER},
    {44, 86, 97, MARKER},
    {2, 48, 102, 115, MARKER},
    {8, 62, 75, MARKER},
    {28, 32, 46, 59, 70, 81, 120, MARKER},
    {48, 90, 101, MARKER},
    {6, 52, 106, 119, MARKER},
    {12, 66, 79, MARKER},
    {32, 36, 50, 63, 74, 85, 124, MARKER},
    {52, 94, 105, MARKER},
    {10, 56, 110, 123, MARKER},
    {16, 70, 83, MARKER},
    {0, 36, 40, 54, 67, 78, 89, MARKER},
    {56, 98, 109, MARKER},
    {14, 60, 114, 127, MARKER},
    {20, 74, 87, MARKER},
    {4, 40, 44, 58, 71, 82, 93, MARKER},
    {60, 102, 113, MARKER},
    {3, 18, 72, 114, 118, 125, MARKER},
    {24, 78, 91, MARKER},
    {8, 44, 48, 62, 75, 86, 97, MARKER},
    {64, 106, 117, MARKER},
    {1, 7, 22, 76, 118, 122, MARKER},
    {28, 82, 95, MARKER},
    {12, 48, 52, 66, 79, 90, 101, MARKER},
    {68, 110, 121, MARKER},
    {5, 11, 26, 80, 122, 126, MARKER},
    {32, 86, 99, MARKER}};

uint LTTableInverse[128][8] = {
    {53, 55, 72, MARKER},
    {1, 5, 20, 90, MARKER},
    {15, 102, MARKER},
    {3, 31, 90, MARKER},
    {57, 59, 76, MARKER},
    {5, 9, 24, 94, MARKER},
    {19, 106, MARKER},
    {7, 35, 94, MARKER},
    {61, 63, 80, MARKER},
    {9, 13, 28, 98, MARKER},
    {23, 110, MARKER},
    {11, 39, 98, MARKER},
    {65, 67, 84, MARKER},
    {13, 17, 32, 102, MARKER},
    {27, 114, MARKER},
    {1, 3, 15, 20, 43, 102, MARKER},
    {69, 71, 88, MARKER},
    {17, 21, 36, 106, MARKER},
    {1, 31, 118, MARKER},
    {5, 7, 19, 24, 47, 106, MARKER},
    {73, 75, 92, MARKER},
    {21, 25, 40, 110, MARKER},
    {5, 35, 122, MARKER},
    {9, 11, 23, 28, 51, 110, MARKER},
    {77, 79, 96, MARKER},
    {25, 29, 44, 114, MARKER},
    {9, 39, 126, MARKER},
    {13, 15, 27, 32, 55, 114, MARKER},
    {81, 83, 100, MARKER},
    {1, 29, 33, 48, 118, MARKER},
    {2, 13, 43, MARKER},
    {1, 17, 19, 31, 36, 59, 118, MARKER},
    {85, 87, 104, MARKER},
    {5, 33, 37, 52, 122, MARKER},
    {6, 17, 47, MARKER},
    {5, 21, 23, 35, 40, 63, 122, MARKER},
    {89, 91, 108, MARKER},
    {9, 37, 41, 56, 126, MARKER},
    {10, 21, 51, MARKER},
    {9, 25, 27, 39, 44, 67, 126, MARKER},
    {93, 95, 112, MARKER},
    {2, 13, 41, 45, 60, MARKER},
    {14, 25, 55, MARKER},
    {2, 13, 29, 31, 43, 48, 71, MARKER},
    {97, 99, 116, MARKER},
    {6, 17, 45, 49, 64, MARKER},
    {18, 29, 59, MARKER},
    {6, 17, 33, 35, 47, 52, 75, MARKER},
    {101, 103, 120, MARKER},
    {10, 21, 49, 53, 68, MARKER},
    {22, 33, 63, MARKER},
    {10, 21, 37, 39, 51, 56, 79, MARKER},
    {105, 107, 124, MARKER},
    {14, 25, 53, 57, 72, MARKER},
    {26, 37, 67, MARKER},
    {14, 25, 41, 43, 55, 60, 83, MARKER},
    {0, 109, 111, MARKER},
    {18, 29, 57, 61, 76, MARKER},
    {30, 41, 71, MARKER},
    {18, 29, 45, 47, 59, 64, 87, MARKER},
    {4, 113, 115, MARKER},
    {22, 33, 61, 65, 80, MARKER},
    {34, 45, 75, MARKER},
    {22, 33, 49, 51, 63, 68, 91, MARKER},
    {8, 117, 119, MARKER},
    {26, 37, 65, 69, 84, MARKER},
    {38, 49, 79, MARKER},
    {26, 37, 53, 55, 67, 72, 95, MARKER},
    {12, 121, 123, MARKER},
    {30, 41, 69, 73, 88, MARKER},
    {42, 53, 83, MARKER},
    {30, 41, 57, 59, 71, 76, 99, MARKER},
    {16, 125, 127, MARKER},
    {34, 45, 73, 77, 92, MARKER},
    {46, 57, 87, MARKER},
    {34, 45, 61, 63, 75, 80, 103, MARKER},
    {1, 3, 20, MARKER},
    {38, 49, 77, 81, 96, MARKER},
    {50, 61, 91, MARKER},
    {38, 49, 65, 67, 79, 84, 107, MARKER},
    {5, 7, 24, MARKER},
    {42, 53, 81, 85, 100, MARKER},
    {54, 65, 95, MARKER},
    {42, 53, 69, 71, 83, 88, 111, MARKER},
    {9, 11, 28, MARKER},
    {46, 57, 85, 89, 104, MARKER},
    {58, 69, 99, MARKER},
    {46, 57, 73, 75, 87, 92, 115, MARKER},
    {13, 15, 32, MARKER},
    {50, 61, 89, 93, 108, MARKER},
    {62, 73, 103, MARKER},
    {50, 61, 77, 79, 91, 96, 119, MARKER},
    {17, 19, 36, MARKER},
    {54, 65, 93, 97, 112, MARKER},
    {66, 77, 107, MARKER},
    {54, 65, 81, 83, 95, 100, 123, MARKER},
    {21, 23, 40, MARKER},
    {58, 69, 97, 101, 116, MARKER},
    {70, 81, 111, MARKER},
    {58, 69, 85, 87, 99, 104, 127, MARKER},
    {25, 27, 44, MARKER},
    {62, 73, 101, 105, 120, MARKER},
    {74, 85, 115, MARKER},
    {3, 62, 73, 89, 91, 103, 108, MARKER},
    {29, 31, 48, MARKER},
    {66, 77, 105, 109, 124, MARKER},
    {78, 89, 119, MARKER},
    {7, 66, 77, 93, 95, 107, 112, MARKER},
    {33, 35, 52, MARKER},
    {0, 70, 81, 109, 113, MARKER},
    {82, 93, 123, MARKER},
    {11, 70, 81, 97, 99, 111, 116, MARKER},
    {37, 39, 56, MARKER},
    {4, 74, 85, 113, 117, MARKER},
    {86, 97, 127, MARKER},
    {15, 74, 85, 101, 103, 115, 120, MARKER},
    {41, 43, 60, MARKER},
    {8, 78, 89, 117, 121, MARKER},
    {3, 90, MARKER},
    {19, 78, 89, 105, 107, 119, 124, MARKER},
    {45, 47, 64, MARKER},
    {12, 82, 93, 121, 125, MARKER},
    {7, 94, MARKER},
    {0, 23, 82, 93, 109, 111, 123, MARKER},
    {49, 51, 68, MARKER},
    {1, 16, 86, 97, 125, MARKER},
    {11, 98, MARKER},
    {4, 27, 86, 97, 113, 115, 127, MARKER}};

#endif /* defined(__Serpent__s_boxes__) */