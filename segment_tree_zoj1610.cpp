//统计有多少染色线段
#include<cstdio>
#include<cstring>
#include<vector>
#include<utilty>
#include<algorithm>

using namespace std;

#define maxn 10240
#define unknow -1
#define mix -2

int cnt[maxn];

struct node{
	int left;
	int right;
	int color;
};

struct segment_tree{
	node ele[maxn*2];

	void create_tree(int pos, int l, int r, int c)
	{
		ele[pos].left = l;
		ele[pos].right = r;
		ele[pos].color = c;
		if(l+1 < r){
			int mid = (l+r)>>1;
			create_tree(pos<<1, l, mid, c);
			create_tree((pos<<1)+1, mid, r, c);
		}
	}

	void push_down(int pos)
	{
		if(ele[pos].color >= 0){
			ele[pos<<1].color = ele[pos].color;
			ele[(pos<<1)+1].color = ele[pos].color;
		}
	}

	void update(int pos, int l, int r, int c)
	{
		if(ele[pos].left>=l && ele[pos].right<=r)
			ele[pos].color = c;
		else{
			push_down(pos);
			ele[pos].color = mix;
			int mid = (ele[pos].left+ele[pos].right)>>1;
			if(l < mid)
				update(pos<<1, l, r, c);
			if(mid < r)
				update((pos<<1)+1, l, r, c);
		}
	}

	int count(int pos, int c)
	{
		int pre = unknow;
		if(ele[pos].color == unknow){
			if(c >= 0) ++cnt[c];
			return unknow;
		}
		if(ele[pos].color == mix){
			pre = count(pos<<1, c);
			return count((pos<<1)+1, pre);
		}
		if(ele[pos].color == c)
			return c;
		if(c >= 0);
			++cnt[c];
		return ele[pos].color;
	}
};

int main()
{
	int c, n;
	scanf("%d", &c);
	while(c--){
		scanf("%d", &n);
	}
	return 0;
}