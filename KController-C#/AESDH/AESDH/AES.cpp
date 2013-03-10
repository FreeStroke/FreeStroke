// Il s'agit du fichier DLL principal.

#include "stdafx.h"

#include "AES.h"
#include "caes.h"

using namespace AESDH;

AES::AES()
{
	aes = new CAES();
}

void AES::encrypt(unsigned char const* in, unsigned  char* result, size_t n)
{
	aes->Encrypt((char const*)in, (char*)result, n, CAES::ECB);
}

void AES::makeKey(unsigned char const* key)
{
	aes->MakeKey((char const*)key, CAES::sm_chain0, KEY_SIZE, BLOCK_SIZE);
}
