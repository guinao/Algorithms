#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

void compute_prefix(const char p[], int pi[], int m)
{
	pi[0] = -1;
	int k = -1;
	for(int i=1; i<m; ++i){
		while(k>=0 && p[k+1]!=p[i])
			k = pi[k];
		if(p[k+1] == p[i])
			++k;
		pi[i] = k;
	}
}


int pit[100];
//正确性待考证
void extended_compute_prefix(const char p[], int pi[], int m)
{
	compute_prefix(p, pit, m);
	for(int i=0; i<m; ++i){
		if(pit[i] == -1)
			pi[i] = -1;
		else if(p[pit[i]+1] == p[i+1])
			pi[i] = pi[pit[i]];
		else pi[i] = pit[i];
	}
}

vector<int> kmp_matcher(const char t[], const char p[])
{
	vector<int> ret;
	int n = strlen(t);
	int m = strlen(p);
	int *pi = new int[m];
	compute_prefix(p, pi, m);
	int q = -1;
	for(int i=0; i<n; ++i){
		while(q>=0 && p[q+1]!=t[i])
			q = pi[q];
		if(p[q+1] == t[i])
			++q;
		if(q == m-1){
			ret.push_back(i);
			q = pi[q];
		}
	}
	delete pi;
	return ret;
}

int main()
{
	char s[100], text[100];
	int pi[100], extend[100];
	while(0){}
	return 0;
}