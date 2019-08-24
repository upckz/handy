

#ifndef _DH64_LIB_H_
#define _DH64_LIB_H_

#include <cstdlib>
#include <ctime>
#include <random>
#include <string.h>
using namespace std;

namespace reactor {

uint64_t mul_mod_p(uint64_t a, uint64_t b) ;
  
uint64_t pow_mod_p(uint64_t a, uint64_t b) ;
  

uint64_t powmodp(uint64_t a, uint64_t b) ;

uint64_t PublicKey(uint64_t privateKey) ;

void KeyPair(uint64_t &privateKey, uint64_t& publicKey) ;

void Secret(char* secertStr, uint64_t privateKey, uint64_t anotherPublicKey) ;


}
#endif