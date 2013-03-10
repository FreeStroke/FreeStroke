// Il s'agit du fichier DLL principal.

#include "stdafx.h"

#include "DiffieHellman.h"
#include "CDiffieHellman.h"

using namespace AESDH;

DiffieHellman::DiffieHellman()
{
	diffie = new CDiffieHellman();
}

__int64 DiffieHellman::createRecipientInterKey(__int64 g, __int64 m)
{
	__int64 B = 0;
	diffie->CreateRecipientInterKey(B, g, m);
	return B;
}

__int64 DiffieHellman::createRecipientEncryptionKey(__int64 sik)
{
	__int64 ek = 0;
	diffie->CreateRecipientEncryptionKey(ek, sik);
	return ek;
}
