#include "../../includes/network/diffiehellman.h"

#include <iostream>
#include <time.h>

using namespace std;
CDiffieHellman::CDiffieHellman(void)
{
	 g = 0;
	 n = 0;
	 a = 0;
	 b = 0;
	 X = 0;
	 Y = 0;
	 K = 0;
}

CDiffieHellman::~CDiffieHellman(void)
{
	CleanMem();
}

// Checks if the public keys have been created
// (used before attempting to create the sender interim key)
bool CDiffieHellman::GetIsPublicKeyCreated(void)
{
	if ( n != 0 && g != 0 )
		return true;

	return false;
}


// Checks the integer n for primality
bool CDiffieHellman::IsItPrime (long long n, long long a)
{ 
    long long d = XpowYmodN(a, n-1, n);
	if (d==1) 
		return true; 
	else 
		return false; 
	 
} 

//Performs the miller-rabin primality test on a guessed prime n.
//trials is the number of attempts to verify this, because the function
//is not 100% accurate it may be a composite.  However setting the trial
//value to around 5 should guarantee success even with very large primes
bool CDiffieHellman::MillerRabin (long long n, long long trials)
{ 
    long long a = 0;

    for (long long i=0; i<trials; i++)
	{ 
		a = (rand() % (n-3))+2;// gets random value in [2..n-1] 
		
		if (IsItPrime (n,a)==false) 
		{ 
			return false; 
			//n composite, return false 
		} 
	} return true; // n probably prime 
} 


// Returns the Read Time Stamp Counter of the CPU
// The instruction returns in registers EDX:EAX the count of ticks from processor reset.
// Added in Pentium. Opcode: 0F 31.
long long CDiffieHellman::GetRTSC( void )
{
    time_t  time1;
    time(&time1);

    srand(time1);
    return rand();
}

// Generates a random number by first getting the RTSC of the CPU, then 
// thanks to Ilya O. Levin uses a Linear feedback shift register.
// The RTSC is then added to fill the 64-bits
unsigned long long CDiffieHellman::GenerateRandomNumber(void)
{
  static unsigned long rnd = 0x41594c49;
  static unsigned long x   = 0x94c49514;

  LFSR(x); 
  rnd^=GetRTSC()^x; 
  ROT(rnd,7);

  return (unsigned long long)GetRTSC() + rnd;
} 



//Generates a large prime number by
//choosing a randomly large integer, and ensuring the value is odd
//then uses the miller-rabin primality test on it to see if it is prime
//if not the value gets increased until it is prime
unsigned long long CDiffieHellman::GeneratePrime()
{
    unsigned long long tmp = 0;

	tmp	=  GenerateRandomNumber() % MAX_PRIME_NUMBER;

	//ensure it is an odd number
	if ((tmp & 1)==0)
		tmp += 1;

	if (MillerRabin(tmp,5)==true) return tmp;
	
	do
	{
		tmp+=2;	
	} while (MillerRabin(tmp,5)==false);
		
	return tmp;
}
 
//Raises X to the power Y in modulus N
//the values of X, Y, and N can be massive, and this can be 
//acheived by first calculating X to the power of 2 then 
//using power chaining over modulus N
long long CDiffieHellman::XpowYmodN(long long x, long long y, long long N)
{
    long long tmp = 0;
	if (y==1) return (x % N);

	if ((y&1)==0)
	{
		tmp = XpowYmodN(x,y/2,N);
		return ((tmp * tmp) % N);
	}
	else
	{
		tmp = XpowYmodN(x,(y-1)/2,N);
		tmp = ((tmp * tmp) % N);
		tmp = ((tmp * x) % N);
		return (tmp);
	}
}


int CDiffieHellman::CreateKeys(long long &Generator, long long &Modulus)
{
    long long swap = 0;

	//Check if keys have already been established
	if ((n!=0) && (g!=0))
	{
		Generator = g;
		Modulus   = n;
	}
	else
	{
		g = GeneratePrime();
		n = GeneratePrime();

		if (g>n)
		{
			swap = g;
			g    = n;
			n    = swap;
		}
		Generator = g;
		Modulus   = n;
	}

	return 0;

}

int CDiffieHellman::CreateSenderInterKey(long long &InterKey)
{
	if ( GetIsPublicKeyCreated() == false )
		return -1;

    a = (long long) (GenerateRandomNumber() % MAX_RANDOM_INTEGER);

	X = XpowYmodN(g,a,n);
	
	InterKey = X;

	return 0;
	
}

int CDiffieHellman::CreateRecipientInterKey(long long &InterKey, long long Generator, long long Modulus)
{

    b = (long long) (GenerateRandomNumber() % MAX_RANDOM_INTEGER);

	g = Generator;
	n = Modulus;

	Y = XpowYmodN(g,b,n);
	
	InterKey = Y;

	return 0;
}

int CDiffieHellman::CreateSenderEncryptionKey(long long &EncryptionKey, long long RecipientInterKey)
{
	Y = RecipientInterKey;
	K = XpowYmodN(Y,a,n);
	EncryptionKey = K;

	//CleanMem(CLEAN_ALL_MEMORY_EXCEPT_KEY);

	return 0;
}


int CDiffieHellman::CreateRecipientEncryptionKey(long long &EncryptionKey, long long SendersInterKey)
{
	X = SendersInterKey;
	K = XpowYmodN(X,b,n);
	EncryptionKey = K;

	//CleanMem(CLEAN_ALL_MEMORY_EXCEPT_KEY);

	return 0;
}


void CDiffieHellman::CleanMem(unsigned long dwFlags)
{
	g = 0;
	n = 0;
	a = 0;
	b = 0;
	X = 0;
	Y = 0;
	
	if (dwFlags!=CLEAN_ALL_MEMORY_EXCEPT_KEY)
	{
		K = 0;
	}
}

int CDiffieHellman::GetValue(long long &value, unsigned long dwFlags)
{
	switch (dwFlags)
	{
		case MODULUS:
		{
			value = n;
			break;
		}
		case GENERATOR:
		{
			value = g;
			break;
		}
		case PRIVATE_A:
		{
			value = a;
			break;
		}
		case PRIVATE_B:
		{
			value = b;
			break;
		}
		case INTERIM_A:
		{
			value = X;
			break;
		}
		case INTERIM_B:
		{
			value = Y;
			break;
		}
		case KEY:
		{
			value = K ;
			break;
		}
	}

	return 0;
						
}
