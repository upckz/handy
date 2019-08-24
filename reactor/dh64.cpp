#include <cstdlib>
#include <ctime>
#include <random>
#include <string.h>
#include "dh64.h"
using namespace std;

namespace reactor {
const uint64_t p = 0xffffffffffffffc5;
const uint64_t g = 5;
    
uint64_t mul_mod_p(uint64_t a, uint64_t b) {
    uint64_t m = 0;
    while (b > 0) {
        if (b&1 > 0) {
            uint64_t t = p-a;
            if (m >= t) {
                 m-=t;
            }else {
                m += a;
            }
        }
        if (a >= p-a) {
            a = a*2 -p;
        } else {
            a = a*2;
        }
        b >>= 1;

    }
    return m;
}
uint64_t pow_mod_p(uint64_t a, uint64_t b) {
    if (b == 1) {
        return a;
    }
    uint64_t t = pow_mod_p(a, b>>1);
    t = mul_mod_p(t, t);
    if (b%2 > 0) {
        t = mul_mod_p(t, a);
    }
    return t;

}

uint64_t powmodp(uint64_t a, uint64_t b) {
    if (a > p) {
        a %= p; 
    }
    return pow_mod_p(a, b);
}

uint64_t PublicKey(uint64_t privateKey) {
    return powmodp(g, privateKey);
}


void KeyPair(uint64_t &privateKey, uint64_t& publicKey) {

    independent_bits_engine<default_random_engine,64,unsigned long long int> engine;

    uint64_t a = engine();
    uint64_t b  = engine() + 1;
    privateKey = (a << 32) | b;
    publicKey = PublicKey(privateKey);
}


void Secret(char* secertStr, uint64_t privateKey, uint64_t anotherPublicKey) {
    int n = strlen(secertStr);
    if (n < 32) {
        //return ;
    }
    uint64_t secert = powmodp(anotherPublicKey, privateKey);
    sprintf(secertStr, "%lu", secert);
    n = strlen(secertStr);
    int j = 0;
    for (int i = n; i<32; i++) {
        secertStr[n++] = secertStr[j++];
    }
    secertStr[n]='\0';
}
}
