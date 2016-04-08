#include<cstdio>
#include<cstring>

#define maxn 1024

int max(int a, int b)
{
	return a>b? a : b;
}

int abs(int a)
{
	return a>0? a : -a;
}

struct _node{
	int p;   //正数代表和根相同，负数表示不同
	int bnum;//相同的数量
	int gnum;//不同的数量
}nodes[maxn];

void Make_Set(int x)
{
	nodes[x].p = x;
	nodes[x].bnum = 1;
	nodes[x].gnum = 0;
}

int Find_Set(int x)
{
	if(nodes[x].p == x)
		return x;
	else if(nodes[x].p > 0)
		nodes[x].p = Find_Set(nodes[x].p);
	else
		nodes[x].p = -Find_Set(-nodes[x].p);
	return nodes[x].p;
}

bool Link(int x, int y, bool same)
{
	int xp = Find_Set(x);
	int yp = Find_Set(y);
	if(same){
		if(xp == yp) return true;
		if(xp == -yp) return false;
		if(xp*yp > 0){
			xp = abs(xp), yp = abs(yp);
			nodes[xp].p = yp;
			nodes[yp].bnum += nodes[xp].bnum;
			nodes[yp].gnum += nodes[xp].gnum;
		}
		else{
			xp = abs(xp), yp = abs(yp);
			nodes[xp].p = -yp;
			nodes[yp].bnum += nodes[xp].gnum;
			nodes[yp].gnum += nodes[xp].bnum;
		}
	}
	else{//not same
		if(xp == yp) return false;
		if(xp == -yp) return true;
		if(xp*yp > 0){
			xp = abs(xp), yp = abs(yp);
			nodes[xp].p = -yp;
			nodes[yp].bnum += nodes[xp].gnum;
			nodes[yp].gnum += nodes[xp].bnum;
		}
		else{
			xp = abs(xp), yp = abs(yp);
			nodes[xp].p = yp;
			nodes[yp].bnum += nodes[xp].bnum;
			nodes[yp].gnum += nodes[xp].gnum;
		}
	}
	return true;
}

int main()
{
	int n, x, ans;
	bool consistent;
	char id[10];
	while(EOF!=scanf("%d",&n) && n!=0){
		getchar();
		consistent = true;
		for(int i=0; i<=n; ++i) Make_Set(i);
		for(int i=1; i<=n; ++i){
			scanf("Sentence %d is %s", &x, id);
			getchar();
			if(consistent){
				if(id[0] == 'f')
					consistent = Link(i, x, false);
				else
					consistent = Link(i, x, true);
			}
		}
		if(consistent){
			ans = 0;
			for(int i=1; i<=n; ++i)
				if(i == Find_Set(i))
					ans += max(nodes[i].bnum, nodes[i].gnum);
			printf("%d\n", ans);
		}
		else puts("Inconsistent");
	}
	return 0;
}