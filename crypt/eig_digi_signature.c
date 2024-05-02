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
// Function to generate ElGamal signature
void elgamal_sign(int p, int g, int x, int m, int *s, int *t)
{
int r = 5; // Random value from Zp*
*s = mod_exp(g, r, p);
int r_inv = mod_inverse(r, p - 1);
*t = (r_inv * (m - x * (*s))) % (p - 1); 
if (*t < 0)
{
*t += p - 1; // Ensure t is positive
}
}
// Function to verify ElGamal signature
int elgamal_verify(int p, int g, int y, int m, int s, int t)
{
int gm = mod_exp(g, m, p); 
int ys = mod_exp(y, s, p); 
int st = mod_exp(s, t, p); 
return (st * ys) % p == gm;
}
int main()
{
// Bob's parameters
int p = 43; // Prime number
int g = 3; // Generator
int x = 8; // Bob's private key
// Generate Bob's public key
int y = mod_exp(g, x, p);
// Alice's parameters
int m; // Message to be signed 
printf("Enter Message: "); 
scanf("%d", &m);
// Signing
int s, t;
elgamal_sign(p, g, x, m, &s, &t); 
printf("Signature: (%d, %d)\n", s, t);
// Verification
int valid = elgamal_verify(p, g, y, m, s, t); 
if (valid)
{
printf("Signature is valid.\n");
}
else
{
printf("Signature is invalid.\n");
}
return 0;
}
