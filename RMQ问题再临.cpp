#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int inf = 99999999;

struct segment_tree{
	int n_;
	int data[1<<21];

	int init(int n)
	{
		n_ = 1;
		while(n_ < n)
			n_ <<= 1;
		fill(data, data+n_*2, inf);
		return n_;
	}

	void udpate(int n, int w)
	{
		n += n_ - 1;
		data[n] = w;
		while(n){
			n = (n-1) / 2;
			data[n] = min(data[2*n+1], data[2*n+2]);
		}
	}

	int query(int a, int b, int k, int l, int r)
	{
		if(r<=a || b<=l)
			return inf;
		else if(a<=l && r<=b)
			return data[k];
		int lv = query(a, b, k*2+1, l, (l+r)/2);
		int rv = query(a, b, k*2+2, (l+r)/2, r);
		return min(lv, rv);
	}
}st;

int main()
{
	int n;
	while(EOF != scanf("%d", &n)){
		int s = st.init(n);
		int c, x, y;
		for(int i=0; i<n; ++i){
			scanf("%d", &x);
			st.udpate(i, x);
		}
		scanf("%d", &n);
		for(int i=0; i<n; ++i){
			scanf("%d %d %d", &c, &x, &y);
			if(c == 0){
				printf("%d\n", st.query(x-1, y, 0, 0, s));
			}else{
				st.udpate(x-1, y);
			}
		}
	}
	return 0;
}