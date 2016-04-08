#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

#define maxn 512
#define inf 999999999
#define nil -1

int g[maxn][maxn];

struct _edge
{
	int from;
	int to;
	int w;
	_edge(const int a, const int b, const int c){
		from = a, to = b, w = c;
	}
};

/*Dijkstra算法结构参考自算法导论24.3节，有修改。
  图用邻接矩阵形式保存，时间和空间的复杂度均为O(n*n)。
  如果用邻接表保存应该可以减少时间和空间的花费。
  邻接矩阵g为全局变量，n为顶点个数，d[]保存所有点到源
  点的最短距离，源点在这里被写死为顶点0，可以根据书中进行
  修改。pi[]保存每个顶点的前驱顶点，在这题里没用到*/
void Dijkstra(int n, int d[], int pi[])
{
	bool mark[maxn];
//-----------function Initialize_Single_Source()--------------
	fill(d, d+n, inf);
	fill(pi, pi+n, nil);
	memset(mark, false, sizeof mark);
	d[0] = 0;
//------------------------------------------------------------
	for(int re=0; re<n; ++re){
		//--------function Extract_Min()------------
		int u = -1;
		for(int i=0; i<n; ++i){
			if(!mark[i] && (u==-1 || d[u]>d[i]))
				u = i;
		}
		mark[u] = true;
//		if(u==-1 || d[u]==inf) continue;
		//------------------------------------------
		for(int i=0; i<n; ++i){
			//--------function Relax---------------
			if(d[i]-d[u] > g[u][i]){
				d[i] = g[0][i] = g[i][0] = d[u]+g[u][i];
				pi[i] = u;
			}
			//-------------------------------------
		}
	}
}

int main()
{
	int n, m;
	int a, b, l;
	int sys = 0, maxi;
	int d[maxn], pi[maxn];
	double ans;
	vector<_edge> e;
	while(EOF!=scanf("%d %d",&n,&m)
		&& n!=0){
		e.clear();
		for(int i=0; i<n; ++i)
			fill(g[i], g[i]+n, inf);
		for(int i=0; i<m; ++i){
			scanf("%d %d %d", &a, &b, &l);
			g[a-1][b-1] = g[b-1][a-1] = l;
			g[i][i] = 0;
			e.push_back(_edge(a-1,b-1,l));
		}
		Dijkstra(n, d, pi);
//		puts("debug1");
//		for(int i=0; i<n; ++i) printf("%d %d\n", d[i], pi[i]);
//		puts("end debug1");
		maxi = 0;
		ans = 0;
		for(int i=0; i<e.size(); ++i){
			double time = fabs(double(d[e[i].from]-d[e[i].to]));
			time = double(e[i].w-time)/2 + max(d[e[i].from], d[e[i].to]);
			if(time > ans)
				ans = time, maxi = i;
		}
		printf("System #%d\n", ++sys);
		printf("The last domino falls after %.1f seconds, ", ans);
		if(m == 0)
			puts("at key domino 1.");
		else if(d[e[maxi].to]+e[maxi].w <= d[e[maxi].from])
			printf("at key domino %d.\n", e[maxi].from+1);
		else if(d[e[maxi].from]+e[maxi].w <= d[e[maxi].to])
			printf("at key domino %d.\n", e[maxi].to+1);
		else
			printf("between key dominoes %d and %d.\n", 
			min(e[maxi].from, e[maxi].to)+1,max(e[maxi].from, e[maxi].to)+1);
		puts("");
	}
	return 0;
}