#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define ROTATE_RIGHT(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))
// Constants for SHA-256
uint32_t CONSTANTS[] = {
 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};
// Function to perform SHA-256 transformation
void transform(uint32_t *state, const uint8_t data[]) {
 uint32_t a, b, c, d, e, f, g, h, i, j, t1, t2, m[64];
 for (i = 0, j = 0; i < 16; ++i, j += 4) {
 m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
 }
 for (; i < 64; ++i) {
 m[i] = (ROTATE_RIGHT(m[i - 2], 17) ^ ROTATE_RIGHT(m[i - 2], 19) ^ (m[i - 2] >> 10)) + m[i - 7] +
 (ROTATE_RIGHT(m[i - 15], 7) ^ ROTATE_RIGHT(m[i - 15], 18) ^ (m[i - 15] >> 3)) + m[i - 16];
 }
 a = state[0];
 b = state[1];
 c = state[2];
 d = state[3];
 e = state[4];
 f = state[5];

 g = state[6];
 h = state[7];
 for (i = 0; i < 64; ++i) {
 t1 = h + (ROTATE_RIGHT(e, 6) ^ ROTATE_RIGHT(e, 11) ^ ROTATE_RIGHT(e, 25)) 
+ ((e & f) ^ ((~e) & g)) + CONSTANTS[i] + m[i];
 t2 = (ROTATE_RIGHT(a, 2) ^ ROTATE_RIGHT(a, 13) ^ ROTATE_RIGHT(a, 22)) 
+ ((a & b) ^ (a & c) ^ (b & c));
 h = g;
 g = f;
 f = e;
 e = d + t1;
 d = c;
 c = b;
 b = a;
 a = t1 + t2;
 }
 state[0] += a;
 state[1] += b;
 state[2] += c;
 state[3] += d;
 state[4] += e;
 state[5] += f;
 state[6] += g;
 state[7] += h;
}
// Function to compute SHA-256 hash
void compute_hash(const uint8_t *message, size_t len, uint8_t hash[]) {
 uint32_t state[8];
 uint64_t bitlen = len * 8;
 uint32_t i, j;
 
 state[0] = 0x6a09e667;
 state[1] = 0xbb67ae85;
 state[2] = 0x3c6ef372;
 state[3] = 0xa54ff53a;
 state[4] = 0x510e527f;
 state[5] = 0x9b05688c;
 state[6] = 0x1f83d9ab;
 state[7] = 0x5be0cd19;
 size_t new_len = len + 1 + ((len + 8) % 64 > 56 ? 64 : 0);
 uint8_t *msg = malloc(new_len + 8);
 memcpy(msg, message, len);
 msg[len] = 0x80;
 for (i = len + 1; i < new_len; ++i) {
 msg[i] = 0;
 }
 for (i = 0; i < 8; ++i) {
 msg[new_len + i] = (bitlen >> ((7 - i) * 8)) & 0xFF;
 }
 for (i = 0; i < new_len; i += 64) {
 transform(state, &msg[i]);
 }
 for (i = 0, j = 0; j < 8; ++i, j += 4) {
 hash[j] = (state[i] >> 24) & 0xFF;
 hash[j + 1] = (state[i] >> 16) & 0xFF;
 hash[j + 2] = (state[i] >> 8) & 0xFF;
 hash[j + 3] = state[i] & 0xFF;
 }
 free(msg);
}
// Function to print the hash
void print_hash(uint8_t hash[]) {
 for (int i = 0; i < 32; ++i) {
 printf("%02x", hash[i]);
 }
 printf("\n");
}
int main() {
 const char *message = "Rashi Batra";
 uint8_t hash[32];
 compute_hash((uint8_t *)message, strlen(message), hash);
 printf("Hash of '%s': ", message);
 print_hash(hash);
 return 0;
}