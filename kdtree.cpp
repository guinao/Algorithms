#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

struct kdTreeNode {
	vector<int> domain;
	int split;
	kdTreeNode *left;
	kdTreeNode *right;
};

static int level;

class kdTree {
private:
	kdTreeNode *root;

	int dist(vector<int>& lhs, vector<int>& rhs) {
		int d = 0;
		for (int i = 0; i < lhs.size(); ++i) {
			d += (lhs[i] - rhs[i]) * (lhs[i] - rhs[i]);
		}
		return d;
	}

	void quick_sort(vector<vector<int>>& domains, vector<int> &index, int i, int j, int d) {
		if (i + 1 >= j)
			return;

		int pivot = domains[index[i]][d];
		int reserve = index[i];
		int s = i, e = j - 1;
		while (s < e) {
			while (s < e && domains[index[e]][d] > pivot)
				--e;
			index[s] = index[e];
			while (s < e && domains[index[s]][d] <= pivot)
				++s;
			index[e] = index[s];
		}
		index[s] = reserve;
		quick_sort(domains, index, i, s, d);
		quick_sort(domains, index, s+1, j, d);
	}

	/*compute the variance on every dimension. Set split as the dismension that have the biggest
	variance. Then choose the instance which is the median on this split dimension.*/
	/*compute variance on the x,y dimension. DX=EX^2-(EX)^2*/
	pair<int, int> choosePivot(vector<vector<int>>& domains, vector<int> &domain_index) {
		pair<int, int> ret;

		int d = domains[0].size();
		int n = domain_index.size();
		int split = -1;
		double max_var = 0.0;
		for (int i = 0; i < d; ++i) {
			double ave = 0, var = 0;
			for (int &p : domain_index) {
				ave += domains[p][i];
			}
			ave /= n;
			for (int &p : domain_index) {
				var += (domains[p][i] - ave) * (domains[p][i] - ave);
			}
			if (split == -1 || var > max_var){
				split = i;
				max_var = var;
			}
		}
		
		quick_sort(domains, domain_index, 0, domain_index.size(), split);
		ret.first = split;
		ret.second = domain_index[domain_index.size() / 2];
		return ret;
	}

	int nearestNeighborCore(vector<int> &query, kdTreeNode* cur, vector<int>& nearestPoint) {
		if (cur == nullptr)
			return INT_MAX;
		int dim = cur->split, nd = cur->domain.size();

		printf("visit (");
		for (int i = 0; i < nd; ++i) {
			printf("%d%c", cur->domain[i], i + 1 == nd ? ')' : ',');
		}
		puts("");
		int min_d = dist(cur->domain, query);
		nearestPoint = cur->domain;
		vector<int> tmp;
		if (query[dim] > cur->domain[dim]) {
			int d = nearestNeighborCore(query, cur->right, tmp);
			if (min_d > d) {
				min_d = d;
				nearestPoint = tmp;
			}
			int bound = cur->domain[dim] - query[dim];
			bound = bound * bound;
			if (bound < min_d) {
				d = nearestNeighborCore(query, cur->left, tmp);
				if (min_d > d) {
					min_d = d;
					nearestPoint = tmp;
				}
			}
		}
		else {
			int d = nearestNeighborCore(query, cur->left, tmp);
			if (min_d > d) {
				min_d = d;
				nearestPoint = tmp;
			}
			int bound = cur->domain[dim] - query[dim];
			bound = bound * bound;
			if (bound < min_d) {
				d = nearestNeighborCore(query, cur->right, tmp);
				if (min_d > d) {
					min_d = d;
					nearestPoint = tmp;
				}
			}
		}
		printf("%d\n", min_d);
		return min_d;
	}

public:
	kdTree(vector<vector<int>> &domains) {
		vector<int> index(domains.size());
		for (int i = 0; i < index.size(); ++i) {
			index[i] = i;
		}
		root = build(domains, index);
	}

	kdTreeNode* build(vector<vector<int>>& domains, vector<int> & domain_index) {
		if (domain_index.empty())
			return nullptr;

		kdTreeNode *cur = new kdTreeNode();
		pair<int, int> p = choosePivot(domains, domain_index);
		cur->split = p.first;
		int v = domains[p.second][p.first];
		cur->domain = domains[p.second];

		int mid = domain_index.size() / 2;

		printf("Split by dimension %d, Tree Node(", p.first);
		int nd = domains[0].size();
		for (int i = 0; i < nd; ++i) {
			printf("%d%c", cur->domain[i], i+1==nd ? ')' : ',');
		}
		puts("");
		
		vector<int> d_left = vector<int>(domain_index.begin(), domain_index.begin() + mid);
		vector<int> d_right = vector<int>(domain_index.begin() + mid + 1, domain_index.end());
		printf("left\n");
		for (int id : d_left) {
			putchar('(');
			for (int i = 0; i < nd; ++i) {
				printf("%d%c", domains[id][i], i + 1 == nd ? ')' : ',');
			}
		}
		puts("");
		printf("right\n");
		for (int id : d_right) {
			putchar('(');
			for (int i = 0; i < nd; ++i) {
				printf("%d%c", domains[id][i], i + 1 == nd ? ')' : ',');
			}
		}
		puts("");

		cur->left = build(domains, d_left);
		cur->right = build(domains, d_right);

		return cur;
	}

	double nearestNeighbor(vector<int> &query) {
		vector<int> p;
		int d2 = nearestNeighborCore(query, root, p);
		printf("Nearest Neighbor (");
		for (int i = 0; i < p.size(); ++i) {
			printf("%d%c", p[i], i + 1 == p.size() ? ')' : ',');
		}
		printf("\n");
		return sqrt(d2*1.);
	}
};

int main()
{
	int n, d;
	while (EOF != scanf("%d %d", &n, &d)) {
		vector<vector<int> > domain;
		vector<int> point(d);
		int x;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < d; ++j) {
				scanf("%d", &x);
				point[j] = x;
			}
			domain.push_back(point);
		}
		kdTree tree(domain);
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < d; ++j) {
				scanf("%d", &x);
				point[j] = x;
			}
			printf("Nearest Distance: %lf\n", tree.nearestNeighbor(point));
		}
	}

	return 0;
}