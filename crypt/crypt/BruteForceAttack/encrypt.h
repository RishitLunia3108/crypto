#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void charToBinary(char input, char *binaryOutput)
{
    int i;
    if (input == 0)
    {
        for (i = 0; i < 8; i++)
        {
            binaryOutput[i] = '0';
        }
    }
    else
    {
        for (i = 8; i > 0; i--)
        {
            if (input % 2 == 0)
            {
                binaryOutput[i - 1] = '0';
            }
            else
            {
                binaryOutput[i - 1] = '1';
            }
            input = input / 2;
        }
    }
    binaryOutput[8] = '\0';
}

void binaryToChar(char *binaryInput, char *output)
{
    int i;
    *output = 0;
    for (i = 0; i < 8; i++)
    {
        *output = *output + (binaryInput[i] - '0') * pow(2, 7 - i);
    }
}

void ip8(char *input, char *output)
{
    int i;
    int ip[] = {2, 6, 3, 1, 4, 8, 5, 7};
    for (i = 0; i < 8; i++)
    {
        output[i] = input[ip[i] - 1];
    }

    output[8] = '\0';
}

void devide4n4(char *input, char *left, char *right)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        left[i] = input[i];
        right[i] = input[i + 4];
    }

    left[4] = '\0';
    right[4] = '\0';
}

void ep(char *input, char *output)
{
    int i;
    int ep[] = {4, 1, 2, 3, 2, 3, 4, 1};
    for (i = 0; i < 8; i++)
    {
        output[i] = input[ep[i] - 1];
    }

    output[8] = '\0';
}

void xor8bit(char *input1, char *input2, char *output)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        output[i] = (input1[i] - '0') ^ (input2[i] - '0') + '0';
    }

    output[8] = '\0';
}

void sBox(char *input1, char *input2, char *output)
{
    int s0[4][4] = {{1, 0, 3, 2},
                    {3, 2, 1, 0},
                    {0, 2, 1, 3},
                    {3, 1, 3, 2}};
    int s1[4][4] = {{0, 1, 2, 3},
                    {2, 0, 1, 3},
                    {3, 0, 1, 0},
                    {2, 1, 0, 3}};
    int i = (input1[0] - '0') * 2 + (input1[3] - '0');
    int j = (input1[1] - '0') * 2 + (input1[2] - '0');
    int k = (input2[0] - '0') * 2 + (input2[3] - '0');
    int l = (input2[1] - '0') * 2 + (input2[2] - '0');

    output[0] = s0[i][j] / 2 + '0';
    output[1] = s0[i][j] % 2 + '0';
    output[2] = s1[k][l] / 2 + '0';
    output[3] = s1[k][l] % 2 + '0';

    output[4] = '\0';
}

void p4(char *input, char *output)
{
    int i;
    int p[] = {2, 4, 3, 1};
    for (i = 0; i < 4; i++)
    {
        output[i] = input[p[i] - 1];
    }

    output[4] = '\0';
}

void xor4bit(char *input1, char *input2, char *output)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        output[i] = (input1[i] - '0') ^ (input2[i] - '0') + '0';
    }

    output[4] = '\0';
}

void combineS3S9(char *input1, char *input2, char *output)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        output[i] = input1[i];
        output[i + 4] = input2[i];
    }

    output[8] = '\0';
}

void swap(char *input, char *output)
{
    int i;
    char temp;
    for (i = 0; i < 4; i++)
    {
        temp = input[i];
        input[i] = output[i];
        output[i] = temp;
    }

    output[4] = '\0';
}

void ip8Inverse(char *input, char *output)
{
    int i;
    int ip[] = {4, 1, 3, 5, 7, 2, 8, 6};
    for (i = 0; i < 8; i++)
    {
        output[i] = input[ip[i] - 1];
    }

    output[8] = '\0';
}

void encryptForK(char *bin, char *key, char *output)
{
    
    char ip8Output[9];
    ip8(bin, ip8Output);

    
    char ip8Left[5], ip8Right[5];
    devide4n4(ip8Output, ip8Left, ip8Right);

    
    char epOutput[9];
    ep(ip8Right, epOutput);

    char xorOutput[9];
    xor8bit(epOutput, key, xorOutput);

    char sBoxOutput[5];
    sBox(xorOutput, ip8Left, sBoxOutput);

    char p4Output[5];
    p4(sBoxOutput, p4Output);

    char xorOutput2[5];
    xor4bit(p4Output, ip8Right, xorOutput2);

    char combineOutput[9];
    combineS3S9(ip8Left, xorOutput2, combineOutput);

    char combineLeft[5], combineRight[5];
    devide4n4(combineOutput, combineLeft, combineRight);

    swap(combineLeft, combineRight);

    char combineOutput2[9];
    combineS3S9(combineLeft, combineRight, combineOutput2);

    strcpy(output, combineOutput2);
}

void encrypt(char c, char *k1, char *k2, char *output)
{
    char bin[9];
    charToBinary(c, bin);
    char output1[9], output2[9], output3[9];

    encryptForK(bin, k1, output1);
    encryptForK(output1, k2, output2);

    ip8Inverse(output2, output3);

    output3[8] = '\0';

    strcpy(output, output3);
}
