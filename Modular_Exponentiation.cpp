/*输出(a^b)mod n 的结果，
  算法原型和思想参看算法导论31.6节*/
long long Modular_Exponentiation(long long a, int b, long long n)
{
	if(b==0)
		return 1;
	long long c = 0;
	long long d = 1;
	long long test = 0x4000000000000000;
	while(test&b == 0) test = test>>1;
	do{
		c = c << 1;
		d = d * d % n;
		if(test&b){
			++c;
			d = d * a %n;
		}
		test = test>>1;
	}while(test);
	return d;
}

/*
#include<cstdio>

int main()
{
	int a;
	printf("%lld\n", Modular_Exponentiation(7, 560, 561));
	scanf("%d", &a);
	return 0;
}
*/