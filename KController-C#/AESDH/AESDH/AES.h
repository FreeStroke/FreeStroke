// AES.h

#pragma once

using namespace System;

#include "caes.h"

namespace AESDH {
	#define KEY_SIZE 32
	#define BLOCK_SIZE 16
	
	public ref class AES
	{
	public:
		AES();
		void encrypt(unsigned char const* in, unsigned  char* result, size_t n);
		void makeKey(unsigned char const* key);
	private:
		CAES *aes;
	};
}