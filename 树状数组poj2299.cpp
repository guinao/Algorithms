//ͳ�������
#include<cstdio>
#include<cstring>
#include<utility>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

#define maxn 500010

/*��״���������޸ĵ��ѯ������޸������ѯ�㣬�����0��á�
  ����������������ⶼ���Կ����ܷ�����״���顣
  ������޸ĵ��ѯ����İ汾update()��getsum()����o(log N)���Ӷ�
  �޸�����ο�poj2155*/
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