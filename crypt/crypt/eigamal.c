#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
// Function to compute modular exponentiation (a^b mod m)
int mod_exp(int a, int b, int m)
{
int result = 1; 
a = a % m; 
while (b > 0)
{
if (b % 2 == 1)
{
result = (result * a) % m;
}
a = (a * a) % m;
b /= 2;
}
return result;
}
// Function to compute the modular inverse using Extended Euclidean Algorithm
int mod_inverse(int a, int m)
{
a = a % m;
for (int x = 1; x < m; x++)
{
if ((a * x) % m == 1)
{
return x;
}
}
// Modular inverse doesn't exist 
return -1;
}
// Function to generate Bob's public key
int generate_public_key(int p, int g, int *x)
{
*x = 7; // Generate Bob's private key 
return mod_exp(g, *x, p);
}
// Function to perform encryption

void encrypt(int m, int p, int g, int y, int *c1, int *c2)
{
int r = 26; // Random ephemeral secret
*c1 = mod_exp(g, r, p);
*c2 = (m * mod_exp(y, r, p)) % p;
}
// Function to perform decryption
int decrypt(int c1, int c2, int p, int x)
{
int decrypted_message = (c2 * mod_inverse(mod_exp(c1, x, p), p)) % p; 
return decrypted_message;
}
int main()
{
// Bob's parameters
int p = 43; // Prime number
int g = 3; // Generator
int x; // Bob's private key
// Generate Bob's public key
int y = generate_public_key(p, g, &x);
printf("Bob's Public Key: (p: %d, g: %d, y: %d)\n", p, g, y);
// Alice's parameters
int m;
printf("Enter plaintext: "); 
scanf("%d", &m);
// Encryption
int c1, c2;
encrypt(m, p, g, y, &c1, &c2); 
printf("Ciphertext: (c1 :%d, c2: %d)\n", c1, c2);
// Decryption
int decrypted_message = decrypt(c1, c2, p, x); 
printf("Decrypted Message: %d\n", decrypted_message);
return 0;
}
