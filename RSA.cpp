/*欧几里得算法求a和b的最大公约数
  算法原型和证明参见算法导论32.2节*/
long long gcd(long long a, long long b)
{
	if(b==0)
		return a;
	else
		return gcd(b, a%b);
}


/*扩展欧几里得算法，计算满足以下条件的整系数x和y：
        d = gcd(a,b) = ax + by
  算法原理，原型和证明参见算法导论32.2节及32.4节推论31.26*/
void Extend_Euclid(long long a,long long b,
	long long *d, long long *x, long long *y)
{
	if(b==0){
		*d = a;
		*x = 1;
		*y = 0;
		return;
	}
	else{
		Extend_Euclid(b, a%b, d, x, y);
		long long temp = *y;
		*y = *x - a / b * *y;
		*x = temp;
		return;
	}
}


/*输入两个素数p和q，且p!=q，p和q应都为32位以内整数
  结果放在e,d,n中，其中(e,n)为公钥，(d,n)为私钥；
  算法的描述和证明参见算法导论31.7节*/
void RSA_Generator(long long p, long long q, 
	long long *e, long long *d, long long *n)
{
	*n = p * q;//这里有溢出的风险
	long long fi = (p-1)*(q-1);//同样可能溢出
	for(long long i=1; i<*n; ++i){
		if(gcd(fi, i*2+1) == 1){
			*e = i*2 + 1;
			break;//循环应该总是在这里跳出，而且正因为如此只产生一组密钥
		}
	}
	long long temp1=0, temp2=0;
	Extend_Euclid(*e, fi, &temp1, d, &temp2);
	while(*d < 0) *d += fi/temp1;
}

/*输出(a^b)mod n 的结果，
  算法原型和思想参看算法导论31.6节*/
//long long Modular_Exponentiation(long long a, int b, long long n)
//{
//	if(b==0)
//		return 1;
//	long long c = 0;
//	long long d = 1;
//	long long test = 0x4000000000000000;
//	while(test&b == 0) test = test>>1;
//	do{
//		c = c << 1;
//		d = d * d % n;
//		if(test&b){
//			++c;
//			d = d * a %n;
//		}
//		test = test>>1;
//	}while(test);
//	return d;
//}
//
//long long RSA_Encryption_And_Decryption(long long text, long long key1, long long key2)
//{
//	return Modular_Exponentiation(text, (int)key1, key2);
//}

/********************Sample 1**************************
#incldue<cstdio>
int main()
{
	long long p, q;
	long long e=0, d=0, n=0;
	while(2==scanf("%lld %lld", &p, &q)){
		RSA_Generator(p,q,&e,&d,&n);
		printf("Public Key is (%lld,%lld)\n",e,n);
		printf("Private Key is (%lld,%lld)\n",d,n);
	}
	return 0;
}
********************************************************/
