#include <cstdio>

int Josephus(int n, int k)
{
	int ret = 0;
	if(n == 1)
		return ret;
	if(n < k){
		for(int i=2; i<=n; ++i)
			ret = (ret+k) % i;
	}else{
		ret = Josephus(n-n/k, k);
		if(ret < n%k)
			ret = ret - n%k + n;
		else
			ret = ret - n%k + (ret-n%k)/(k-1);
	}
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--){
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%d\n", Josephus(x, y));
	}
	return 0;
}