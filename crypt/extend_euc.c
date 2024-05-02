#include <stdio.h>
int customExtendedGCD(int a, int b, int *resultX, int *resultY)
{
if (a == 0)
{
*resultX = 0;
*resultY = 1; 
return b;
}
int x1, y1;
int gcd = customExtendedGCD(b % a, a, &x1, &y1);
*resultX = y1 - (b / a) * x1;
*resultY = x1; 
return gcd;
}
int customModInverse(int a, int m)
{
int x, y;
int gcd = customExtendedGCD(a, m, &x, &y); 
if (gcd != 1)
{
// Modular inverse does not exist 
return -1;
}
else
{
while (x < 0)
{
x = x + m;
}
return x;
}
}
int main()
{
int num1, num2;
printf("Enter the first number: "); 
scanf("%d", &num1); 
printf("Enter the modulo: "); 
scanf("%d", &num2);
int inverse = customModInverse(num1, num2); 

if (inverse == -1)
{
printf("The modular inverse does not exist for %d modulo %d.\n", num1, num2);
}
else
{
printf("Modular Inverse of %d modulo %d is: %d\n", num1, num2, inverse); 
printf("Explanation: %d * %d mod %d is 1.\n", inverse, num1, num2);
}
return 0;
}
