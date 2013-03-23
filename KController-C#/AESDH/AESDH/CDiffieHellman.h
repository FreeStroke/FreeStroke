/*
* Projet de fin d'études LastProject de
* Adrien Broussolle
* Camille Darcy
* Guillaume Demurger
* Sylvain Fay-Chatelard
* Anthony Fourneau
* Aurèle Lenfant
* Adrien Madouasse
*
* Copyright (C) 2013 Université Paris-Est Marne-la-Vallée
*
* FreeStroke is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
*/
#pragma once

#include <stdlib.h>


// CRYPTO LIBRARY FOR EXCHANGING KEYS
// USING THE DIFFIE-HELLMAN KEY EXCHANGE PROTOCOL

// The diffie-hellman can be used to securely exchange keys
// between parties, where a third party eavesdropper given
// the values being transmitted cannot determine the key.

// Implemented by Lee Griffiths, Jan 2004.
// This software is freeware, you may use it to your discretion,
// however by doing so you take full responsibility for any damage
// it may cause.

// Hope you find it useful, even if you just use some of the functions
// out of it like the prime number generator and the XtoYmodN function.

// It would be great if you could send me emails to: griffter@hotmail.co.uk
// with any suggestions, comments, or questions!

// Enjoy.

// Updated 12 Novemeber 2008 - class appropriately renamed

// Updated 06 July 2006 - no longer requires Windows API's
//                        random number generation replaced.
//                        Thanks to Ilya O. Levin on help with q-rng

#define MAX_RANDOM_INTEGER 2147483648 //Should make these numbers massive to be more secure
#define MAX_PRIME_NUMBER   2147483648 //Bigger the number the slower the algorithm

// Thanks to Ilya O. Levin (whoever you are, thanks!)
//Linear Feedback Shift Registers
#define LFSR(n)    {if (n&1) n=((n^0x80000055)>>1)|0x80000000; else n>>=1;}

//Rotate32
#define ROT(x, y)  (x=(x<<y)|(x>>(32-y)))


#define CLEAN_ALL_MEMORY				1
#define CLEAN_ALL_MEMORY_EXCEPT_KEY		2


#define MODULUS							1
#define GENERATOR						2
#define PRIVATE_A						3
#define PRIVATE_B						4
#define INTERIM_A						5
#define INTERIM_B						6
#define KEY								7

class CDiffieHellman
{
public:
	CDiffieHellman(void);
	~CDiffieHellman(void);

    int CreateKeys(long long &Generator, long long &Modulus);
    int CreateSenderInterKey(long long &InterKey);
    int CreateRecipientInterKey(long long &InterKey, long long Generator, long long Modulus);
    int CreateSenderEncryptionKey(long long &EncryptionKey, long long RecipientInterKey);
    int CreateRecipientEncryptionKey(long long &EncryptionKey, long long SendersInterKey);
	
    int GetValue(long long &value, unsigned long dwFlags = KEY);

	bool GetIsPublicKeyCreated(void);

private:
    long long XpowYmodN(long long x, long long y, long long N);
    unsigned long long GenerateRandomNumber( void );
    unsigned long long GeneratePrime();
    long long GetRTSC( void );
    bool MillerRabin (long long n, long long trials);
    bool IsItPrime (long long n, long long a);

    long long g;
    long long n;
    long long a;
    long long b;
    long long X;
    long long Y;
    long long K;

	void CleanMem(unsigned long dwFlags=CLEAN_ALL_MEMORY);

};
