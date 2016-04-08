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

/*Kruskal�㷨��������һ��������ͨͼ����С��������
  ����ο����㷨����23.2�ڵ�α���롣
  ʱ�临�Ӷ�ΪO(ElgE)Ҳ�ɱ���ΪO(ElgV)��
  �㷨��˼�룬��ȷ��֤���͸��Ӷ��Ƶ����ɲμ��㷨����23.2�ڡ�
  ��������Ϊ�ڵ���Ŀ�����еıߵļ��ϣ��ڵ��0��ʼ��š�
  �������Ϊ����������С�������ıߵļ���*/
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
