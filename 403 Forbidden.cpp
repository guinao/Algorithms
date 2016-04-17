// Segment Tree, Query Single Point, Update A Range. Discretization.

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int maxn = 1 << 20;
const int mix = -1;
const int unknow = 0;
const int allow = 1;
const int deny = 2;
const int full = 3;

struct segment_tree
{
	int n_;
	int data[maxn];

	int init(int n)
	{
		n_ = 1;
		while(n_ < n)
			n_ <<= 1;
		fill(data, data+2*n_-1, unknow);

		return n_;
	}

	void update(int a, int b, int c, int k, int l, int r)
	{
		if(b<=l || r<=a || data[k]>0)
			return;
		if(a<=l && r<=b && data[k]==unknow)
		{
			data[k] = c;
			// printf("%d %d %d %d %d %d\n", a, b, c, k, l, r);
		}
		else
		{
			int mid = (l+r)/2;
			update(a,b,c,k*2+1, l,mid);
			update(a,b,c,k*2+2, mid, r);
			if(data[k*2+1]>0 && data[k*2+2]>0)
				data[k] = full;
		}
	}

	int query(int k)
	{
		k += n_-1;
		while(k>0 && data[k]<=0)
			k = (k-1) / 2;
		return data[k];
	}

}stree;

int main()
{
	int n, m;
	char comm[8], buf[32];
	ll mask[33];
	mask[0] = 0;
	for(int i=1; i<33; ++i){
		mask[i] = (mask[i-1]<<1) | 1;
	}
	while(EOF != scanf("%d %d", &n, &m)){
		vector<ll> left(n),right(n);
		vector<ll> v;
		vector<int> type(n);
		v.reserve(2*n);
		int a, b, c, d;
		for(int i=0; i<n; ++i){
			scanf("%s %s", comm, buf);
			if(comm[0] == 'a')
				type[i] = allow;
			else
				type[i] = deny;
			char *pch = strtok(buf, "/");
			sscanf(pch, "%d.%d.%d.%d", &a, &b, &c, &d);
			left[i] = ((ll)a<<24) | ((ll)b<<16) | ((ll)c<<8) | (ll)d;
			pch = strtok(NULL, "/");
			int offset = 32;
			if(NULL != pch){
				sscanf(pch, "%d", &offset);
			}
			offset = 32 - offset;
			left[i] &= ~mask[offset];
			right[i] = left[i] | mask[offset];
			// printf("%lld %lld\n", left[i], right[i]);
			v.push_back(left[i]*2);
			v.push_back(right[i]*2+1);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		int s = stree.init(v.size());
		for(int i=0; i<n; ++i){
			int a = lower_bound(v.begin(), v.end(), left[i]*2) - v.begin();
			int b = lower_bound(v.begin(), v.end(), right[i]*2+1) - v.begin();
			stree.update(a, b, type[i], 0, 0, s);
		}
		for(int i=0; i<m; ++i){
			scanf("%d.%d.%d.%d", &a, &b, &c, &d);
			ll addr = ((ll)a<<24) | ((ll)b<<16) | ((ll)c<<8) | (ll)d;
			int pos = upper_bound(v.begin(), v.end(), addr*2) - v.begin();
			if(stree.query(pos-1) != deny)
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}