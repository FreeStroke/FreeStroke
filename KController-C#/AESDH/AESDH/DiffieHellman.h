// DiffieHellman.h

#pragma once

using namespace System;

#include "CDiffieHellman.h"

namespace AESDH {

	public ref class DiffieHellman
	{
	public:
		DiffieHellman();
		__int64 createRecipientInterKey(__int64 g, __int64 m);
		__int64 createRecipientEncryptionKey(__int64 sik);
	private:
		CDiffieHellman *diffie;
	};
}