#include <stdio.h>
// Custom PRNG parameters
#define PRIME_MODULUS 10000019 // A large prime number for modular operation
// Function to compute the factorial of a number
unsigned long long factorial(int n){ 
if (n <= 1){
return 1;
}
return n * factorial(n - 1);
}
// Function to generate a pseudo-random number using factorial function
unsigned long long custom_prng(unsigned long long prev1, unsigned long long prev2)
{
unsigned long long result = factorial(prev1) * factorial(prev2);
result = (prev1 + prev2); // XOR with sum of previous numbers 
result = (result << 1) | (result >> (30 - 1)); // Bit rotation
result += (result << 1) - (result >> 1); // Shift and add
return result % PRIME_MODULUS; // Apply modular operation for security
}
int main(){
unsigned long long prev1, prev2; // Initial seed values
// Input initial seed values from the user
printf("Enter the initial seed values (two integers): "); 
scanf("%llu %llu", &prev1, &prev2);
// Generate and print pseudo-random numbers 
printf("Pseudo-random numbers:\n");
for (int i = 0; i < 3; ++i){
unsigned long long next_number = custom_prng(prev1, prev2); 
printf("%llu\n", next_number);
prev1 = prev2;
prev2 = next_number;
}
return 0;
}