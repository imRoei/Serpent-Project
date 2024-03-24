uint32_t testBlock[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    uint32_t tempBlock[4];
    uint32_t resultBlock[4];
    // Apply Initial Permutation and its Inverse
    InitialPermutation(testBlock, tempBlock);
    InverseInitialPermutation(tempBlock, resultBlock);
    // Check if resultBlock matches testBlock for Initial Permutation and its Inverse
    printf("Testing Initial Permutation and its Inverse...\n");
    int testPassed = 1; // Assume test passed, and try to disprove it
    for (int i = 0; i < 4; i++)
    {
        if (testBlock[i] != resultBlock[i])
        {
            testPassed = 0; // Test failed if any pair of elements doesn't match
            break;          // No need to check further if any mismatch is found
        }
    }

    if (testPassed)
    {
        printf("Test PASSED: Initial Permutation and its Inverse correctly reverses the block.\n");
    }
    else
    {
        printf("Test FAILED: Initial Permutation and its Inverse did not correctly reverse the block.\n");
        // Optionally print the blocks for debugging
        for (int i = 0; i < 4; i++)
        {
            printf("Original: %08x, Result: %08x\n", testBlock[i], resultBlock[i]);
        }
    }
 