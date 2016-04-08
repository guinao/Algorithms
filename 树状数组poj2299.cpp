//统计逆序对
#include<cstdio>
#include<cstring>
#include<utility>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

#define maxn 500010

/*树状数组用于修改点查询区间或修改区间查询点，数组第0项不用。
  满足区间减法的问题都可以考虑能否用树状数组。
  这个是修改点查询区间的版本update()和getsum()都是o(log N)复杂度
  修改区间参看poj2155*/
typedef long long elem_t;

struct sum{
	elem_t c[maxn];
	int n;

	void init(int a)
	{
		n = a;
		memset(c, 0, sizeof c);
	}

	int lowbit(int x)
	{
		return x&(-x);
	}

	void update(int x, elem_t v)
	{
		while(x <= n){
			c[x] += v;
			x += lowbit(x);
		}
	}

	elem_t getsum(int x)
	{
		elem_t sum = 0;
		while(x > 0){
			sum += c[x];
			x -= lowbit(x);
		}
		return sum;
	}
};

sum s;
int order[maxn];

bool cmp(const pair<int,int>& a, const pair<int,int>& b)
{
	return a.first < b.first;
}

int main()
{
	int n, x, m;
	elem_t ans;
	vector<pair<int,int> > v;
	while(EOF!=scanf("%d",&n) && n!=0){
		v.clear();
		for(int i=0; i<n; ++i){
			scanf("%d", &x);
			v.push_back(pair<int,int>(x, i));
		}
		sort(v.begin(), v.end(), cmp);
		for(int i=0; i<n; ++i)
			order[v[i].second] = i+1;
		ans = 0;
		s.init(n);
		for(int i=0; i<n; ++i){
			ans += s.getsum(order[i]);
			s.update(order[i], 1);
		}
		ans = (long long)n*(n-1)/2 - ans;
		printf("%lld\n", ans);
	}
	return 0;
}