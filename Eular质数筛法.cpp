#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	vector<bool> nums(n+1, true);
	vector<int> primes;
	primes.reserve(1000);
	for(int i=2; i<=n; ++i){
		if(nums[i])
			primes.push_back(i);
		for(int j=0; j<(int)primes.size(); ++j){
			if((long long)i * primes[j] > n)
				break;
			nums[i*primes[j]] = false;
			if(i % primes[j] == 0)
				break;
		}
	}
	printf("%d\n", (int)primes.size());
	return 0;
}