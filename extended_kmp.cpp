#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 128;

void compute_prefix(char p[], int m, int pi[])
{
	pi[0] = m;
	int k=0;
	while(1+k<m && p[k]==p[1+k]) ++k;
	pi[1] = k;
	k = 1;
	for(int i=2; i<m; ++i){
		if(i-k+pi[i-k] < pi[k])
			pi[i] = pi[i-k];
		else{
			k = max(0, pi[k]-1-i+k);
			while(i+k<m && p[k]==p[i+k]) ++k;
			pi[i] = k;
			k = i;
		}
	}
}

void extended_kmp(char t[], int n, char p[], int m, int extend[])
{
	int *pi = new int[m];
	compute_prefix(p, m, pi);
	int k=0;
	while(k<n && t[k]!=p[0])
		extend[k++] = 0;
	int len=1;
	while(len<m && k<n && p[len]==t[k+len])
		++len;
	extend[k] = len;
	for(int i=k+1; i<n; ++i){
		if(i-k<extend[k] && i+pi[i-k]<k+extend[k])
			extend[i] = pi[i-k];
		else{
			len = max(0, extend[k]+k-i);
			while(len<m && len+i<n && p[len]==t[len+i])
				++len;
			extend[i] = len;
			k = i;
		}
	}
	delete pi;
}

int main()
{
	char s[maxn], p[maxn];
	int extend[maxn];
	while(gets(s)&&gets(p)){
		extended_kmp(s,strlen(s),p,strlen(p),extend);
	}
	return 0;
}