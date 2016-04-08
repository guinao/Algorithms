/*ŷ������㷨��a��b�����Լ��
  �㷨ԭ�ͺ�֤���μ��㷨����32.2��*/
long long gcd(long long a, long long b)
{
	if(b==0)
		return a;
	else
		return gcd(b, a%b);
}


/*��չŷ������㷨����������������������ϵ��x��y��
        d = gcd(a,b) = ax + by
  �㷨ԭ��ԭ�ͺ�֤���μ��㷨����32.2�ڼ�32.4������31.26*/
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


/*������������p��q����p!=q��p��qӦ��Ϊ32λ��������
  �������e,d,n�У�����(e,n)Ϊ��Կ��(d,n)Ϊ˽Կ��
  �㷨��������֤���μ��㷨����31.7��*/
void RSA_Generator(long long p, long long q, 
	long long *e, long long *d, long long *n)
{
	*n = p * q;//����������ķ���
	long long fi = (p-1)*(q-1);//ͬ���������
	for(long long i=1; i<*n; ++i){
		if(gcd(fi, i*2+1) == 1){
			*e = i*2 + 1;
			break;//ѭ��Ӧ��������������������������Ϊ���ֻ����һ����Կ
		}
	}
	long long temp1=0, temp2=0;
	Extend_Euclid(*e, fi, &temp1, d, &temp2);
	while(*d < 0) *d += fi/temp1;
}

/*���(a^b)mod n �Ľ����
  �㷨ԭ�ͺ�˼��ο��㷨����31.6��*/
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
