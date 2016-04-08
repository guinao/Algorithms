#include<cstdio>
#include<cstring>
#include<utility>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

#define maxv 512
#define maxe (maxv*(maxv-1)/2)

struct Disjoint_Set{
	int p[maxe], rank[maxe];

	void Init(int n)
	{
		for(int i=0; i<n; ++i)
			Make_Set(i);
	}

	void Make_Set(int x)
	{
		p[x] = x;
		rank[x] = 0;
	}

	void Union(int x, int y)
	{
		Link(Find_Set(x), Find_Set(y));
	}

	void Link(int x, int y)
	{
		if(rank[x] > rank[y])
			p[y] = x;
		else{
			p[x] = y;
			if(rank[x] == rank[y])
				++rank[y];
		}
	}

	int Find_Set(int x)
	{
		if(x != p[x])
			p[x] = Find_Set(p[x]);
		return p[x];
	}
}dset;

struct edge{
	int from, to;
	int w;
	edge(int a, int b, int c)
		:from(a), to(b), w(c){}
};

bool edge_cmp(const edge& e1, const edge& e2)
{
	return e1.w < e2.w;
}

/*Kruskal算法用于生成一个无向联通图的最小生成树。
  程序参考自算法导论23.2节的伪代码。
  时间复杂度为O(ElgE)也可表述为O(ElgV)。
  算法的思想，正确性证明和复杂度推导均可参见算法导论23.2节。
  程序输入为节点数目和所有的边的集合，节点从0开始编号。
  程序输出为所有属于最小生成树的边的集合*/
vector<edge> MST_Kruskal(int n, vector<edge>& ve)
{
	vector<edge> ret;
	dset.Init(n);
	sort(ve.begin(), ve.end(), edge_cmp);
	for(int i=0; i<(int)ve.size(); ++i){
		if(dset.Find_Set(ve[i].from) != dset.Find_Set(ve[i].to)){
			ret.push_back(ve[i]);
			dset.Union(ve[i].from, ve[i].to);
		}
	}
	return ret;
}

int main()
{
	int t, n, e, a, b, w, ans;
	vector<edge> ve;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &e);
		ve.clear();
		for(int i=0; i<e; ++i){
			scanf("%d %d %d", &a, &b, &w);
			ve.push_back(edge(a,b,w));
		}
		vector<edge> mst = MST_Kruskal(n, ve);
		ans = 0;
		for(int i=0; i<(int)mst.size(); ++i)
			ans += mst[i].w;
		printf("%d\n", ans);
	}
	return 0;
}
