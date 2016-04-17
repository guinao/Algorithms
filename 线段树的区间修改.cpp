#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct segment_tree{
	int price[1<<18];
	int data[1<<18];
	int n_;

	int init(int n){
		n_ = 1;
		while(n_ < n)
			n_ <<= 1;
		fill(price, price+2*n_-1, -1);
		fill(data, data+2*n_-1, false);
		return n_;
	}
	
	void update(int x, int y, int p, int k, int l, int r)
	{
//		printf("%d %d %d %d %d %d\n", x, y, p, k, l, r);
		if(y<=l || r<=x)
			return;
		if(x<=l && r<=y){
			price[k] = p;
			data[k] = p * (r-l);
		}else{
			int mid = (l+r) / 2;
			if(price[k] != -1){
				price[k*2+1] = price[k*2+2] = price[k];
				data[k*2+1] = price[k] * (mid-l);
				data[k*2+2] = price[k] * (r-mid);
				price[k] = -1;
			}
			update(x, y, p, k*2+1, l, mid);
			update(x, y, p, k*2+2, mid, r);
			data[k] = data[k*2+1] + data[k*2+2];
		}
	}

	int query(int x, int y, int k, int l, int r)
	{
//		printf("%d %d %d %d %d\n", x, y, k, l, r);
		if(y<=l || r<=x)
			return 0;
		if(x<=l && r<=y)
			return data[k];
		int mid = (l+r) / 2;
		if(price[k] != -1){
			price[k*2+1] = price[k*2+2] = price[k];
			data[k*2+1] = price[k] * (mid-l);
			data[k*2+2] = price[k] * (r-mid);
			price[k] = -1;
		}
		int lv = query(x, y, k*2+1, l, mid);
		int rv = query(x, y, k*2+2, mid, r);
		return lv + rv;
	}
}st;

int main()
{
	int n;
	while(EOF != scanf("%d", &n)){
		int c, x, y;
		int s = st.init(n);
		for(int i=0; i<n; ++i){
			scanf("%d", &c);
			st.update(i,i+1, c, 0, 0, s);
		}
		scanf("%d\n", &n);
		for(int i=0; i<n; ++i){
			scanf("%d", &c);
			if(c == 0){
				scanf("%d %d", &x, &y);
				printf("%d\n", st.query(x-1, y, 0, 0, s));
			}else{
				scanf("%d %d %d", &x, &y, &c);
				st.update(x-1, y, c, 0, 0, s);
			}
		}
	}
	return 0;
}