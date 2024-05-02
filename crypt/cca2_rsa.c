#include <stdio.h> 
#include <math.h>
// Function to calculate GCD
int gcd(int a, int b)
{
if (b == 0) 
return a;
return gcd(b, a % b);
}
// Function to calculate modular inverse
int modInverse(int a, int m){ 
a = a % m;
for (int x = 1; x < m; x++){ 
if ((a * x) % m == 1){
return x;
}
}
return -1;
}
// Function to calculate modular exponentiation
int modExp(int a, int b, int n){ 
int r = 1;
while (b > 0)
{
if (b % 2 == 1)
r = (r * a) % n;
a = (a * a) % n;
b /= 2;
}
return r;
}
// Function to encrypt plaintext
int encrypt(int plaintext, int e, int n){ 
return modExp(plaintext, e, n);
}
// Function to decrypt ciphertext 
int decrypt(int ciphertext, int n){ 
int p = 7, q = 5, phi, e = 11, d;
// Calculate phi(n)
phi = (p - 1) * (q - 1);
// Calculate d as the modular inverse of e with respect to phi(n) 
d = modInverse(e, phi);
return modExp(ciphertext, d, n);
}

int CCA2_attack(int ciphertext, int e, int n){
int m_dash = 31;
int c_dash = (ciphertext * modExp(m_dash, e, n)) % n;
int decrypted_result = decrypt(c_dash, n); // decrypt(c_dash, n) should return (c_dash)^d mod n
int m = decrypted_result * modInverse(m_dash, n) % n; // Divide by m_dash to obtain m 
return m;
}
int main(){
int n, e, plaintext, ciphertext, cca2_text;
// Set public key components 
n = 35;
e = 11;
printf("Enter plaintext: "); 
scanf("%d", &plaintext);
// Encrypt plaintext
ciphertext = encrypt(plaintext, e, n); 
printf("Ciphertext: %d\n", ciphertext);
// CCA2 Text
cca2_text = CCA2_attack(ciphertext, e, n); 
printf("CCA2 Text: %d\n", cca2_text);
// Decrypt ciphertext
plaintext = decrypt(ciphertext, n); 
printf("Decrypted plaintext: %d\n", plaintext); 
if (cca2_text == plaintext){
printf("CCA2 attack is successful\n");
}
else{
printf("CCA2 attack is unsuccessful\n");
}
return 0;
}
