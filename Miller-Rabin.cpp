#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

typedef unsigned long long int64;

int64 mod_mul(int64 a, int64 b, int64 mod)
{
	int64 ret = 0;
	b %= mod;
	while(a){
		if(a & 1)
			ret = (ret+b) % mod;
		a >>= 1;
		b = (b+b) % mod;
	}
	return ret;
}

int64 mod_exp(int64 a, int64 p, int64 mod)
{
	int64 ret = 1;
	a %= mod;
	while(p){
		if(p & 1)
			ret = mod_mul(ret, a, mod);
		p >>= 1;
		a = mod_mul(a, a, mod);
	}
	return ret;
}

bool witness(int64 a, int64 n)
{
	int64 u = n-1;
	int t = 0;
	while(u % 2 == 0){
		++t;
		u >>= 1;
	}
	a = mod_exp(a, u, n);
	for(int i=1; i<=t; ++i){
		int64 pa = mod_mul(a, a, n);
		if(pa==1 && a!=1 && a!=n-1)
			return true;
		a = pa;
	}
	if(a == 1)
		return false;
	return true;
}

int64 a[] = {2,3,5,7,11,13,17,19,23,29,31,37};

bool miller_rabin(int64 n)
{
	if(n<=2 || n%2==0)
		return n==2;

	int64 u = n-1;
	int t = 0;
	while(u%2 == 0){
		u >>= 1;
		++t;
	}

	for(int i=0; i<12&&a[i]<n; ++i){
		int64 x = mod_exp(a[i], u, n);
		for(int j=0; j<t; ++j){
			int64 y = mod_mul(x, x, n);
			if(y==1 && x!=1 && x!=n-1)
				return false;
			x = y;
		}
		if(x != 1)
			return false;
	}
	return true;
}

int main()
{
	int t;
	int64 x;
	scanf("%d", &t);
	while(t--){
		scanf("%lld", &x);
		if(miller_rabin(x))
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}