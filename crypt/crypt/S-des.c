#include <stdio.h>

int temp[10];

void p10(int key[10])
{
    int p[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

    for (int i = 0; i < 10; i++)
    {
        temp[i] = key[p[i] - 1];
    }
}

void leftshift()
{
    int t = temp[0];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = temp[i + 1];
    }
    temp[4] = t;

    t = temp[5];
    for (int i = 5; i < 9; i++)
    {
        temp[i] = temp[i + 1];
    }
    temp[9] = t;
}

void p8(int p8_arr[8])
{
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
    int temp1[8];

    for (int i = 0; i < 8; i++)
    {
        temp1[i] = temp[p8[i] - 1];
    }

    for (int i = 0; i < 8; i++)
    {
        p8_arr[i] = temp1[i];
    }
}

void expandPermute(int input[4], int output[8])
{
    int expansionMatrix[8] = {4, 1, 2, 3, 2, 3, 4, 1};

    for (int i = 0; i < 8; i++)
    {
        output[i] = input[expansionMatrix[i] - 1];
    }
}

void binaryXOR(int input1[8], int input2[8], int output[8])
{
    for (int i = 0; i < 8; i++)
    {
        output[i] = input1[i] ^ input2[i];
    }
}

void calculateRowColumn(int xorResult[8], int *row1, int *column1, int *row2, int *column2)
{
    *row1 = xorResult[0] * 2 + xorResult[3];
    *column1 = xorResult[1] * 2 + xorResult[2];

    *row2 = xorResult[4] * 2 + xorResult[7];
    *column2 = xorResult[5] * 2 + xorResult[6];
}

void applySBox(int row, int column, int *output)
{
    int sBoxS0[4][4] = {{1, 0, 3, 2},
                        {3, 2, 1, 0},
                        {0, 2, 1, 3},
                        {3, 1, 3, 2}};

    int sBoxS1[4][4] = {{0, 1, 2, 3},
                        {2, 0, 1, 3},
                        {3, 0, 1, 0},
                        {2, 1, 0, 3}};

    int bitsS0 = sBoxS0[row][column];
    int bitsS1 = sBoxS1[row][column];

    output[0] = bitsS0 / 2;
    output[1] = bitsS0 % 2;
    output[2] = bitsS1 / 2;
    output[3] = bitsS1 % 2;
}

void p4(int input[4], int output[4])
{
    int p4Matrix[4] = {2, 4, 3, 1};

    for (int i = 0; i < 4; i++)
    {
        output[i] = input[p4Matrix[i] - 1];
    }
}

void initialPermutation(int input[8], int output[8])
{
    int ipMatrix[8] = {2, 6, 3, 1, 4, 8, 5, 7};

    for (int i = 0; i < 8; i++)
    {
        output[i] = input[ipMatrix[i] - 1];
    }
}

void reverseInitialPermutation(int input[8], int output[8])
{
    int ipInverseMatrix[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    for (int i = 0; i < 8; i++)
    {
        output[i] = input[ipInverseMatrix[i] - 1];
    }
}

void swapHalves(int input[8], int output[8])
{
    for (int i = 0; i < 4; i++)
    {
        output[i] = input[i + 4];
        output[i + 4] = input[i];
    }
}

void encrypt(int plaintext[8], int key[10])
{
    int subkey_K1[8], subkey_K2[8];
    int xorResult[8], ePResult[8], sBoxResult[8], p4Result[4], swappedResult[8], replacedResult[8], finalResult[8];
    int row1, column1, row2, column2;

    printf("Plaintext: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", plaintext[i]);
    }
    printf("\n");

    printf("Initial key: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", key[i]);
    }
    printf("\n");

    printf("Key Generation:\n");

    p10(key);
    leftshift();
    p8(subkey_K1);

    printf("Subkey K1: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", subkey_K1[i]);
    }
    printf("\n");

    leftshift();
    leftshift();
    p8(subkey_K2);

    printf("Subkey K2: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", subkey_K2[i]);
    }
    printf("\n");

    printf("Encryption Process:\n");

    // Initial Permutation
    int initialPermResult[8];
    initialPermutation(plaintext, initialPermResult);

    // Round 1
    printf("Round 1:\n");
    binaryXOR(initialPermResult, subkey_K1, xorResult);

    // S-Box and P4
    calculateRowColumn(xorResult, &row1, &column1, &row2, &column2);
    applySBox(row1, column1, sBoxResult);
    applySBox(row2, column2, sBoxResult + 4);
    p4(sBoxResult, p4Result);

    // Swapping halves and XOR
    swapHalves(initialPermResult, swappedResult);
    binaryXOR(p4Result, swappedResult, replacedResult);

    // Final Result
    for (int i = 0; i < 4; i++)
    {
        xorResult[i] = replacedResult[i];
        xorResult[i + 4] = initialPermResult[i + 4];
    }

    reverseInitialPermutation(xorResult, finalResult);

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", finalResult[i]);
    }
    printf("\n");
}

int main()
{
    int plaintext[8] = {1, 0, 1, 0, 0, 1, 0, 1};
    int key[10] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};

    encrypt(plaintext, key);

    return 0;
}