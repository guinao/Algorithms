#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define maxn 32
#define ele_t double

struct Matrix{
	ele_t ele[maxn][maxn];
	int nc, nr;
	Matrix(int a, int b)
		:nc(a), nr(b)
	{
		nc = a;
		nr = b;
		for(int i=0; i<nc; ++i)
			fill(ele[i], ele[i]+nr, 0.);
	}
};

Matrix mat_mul(const Matrix& a, const Matrix& b)
{
	Matrix c = Matrix(a.nc, b.nr);
	for(int i=0; i<c.nc; ++i)
		for(int j=0; j<c.nr; ++j)
			for(int k=0; k<a.nr; ++k)
				c.ele[i][j] += a.ele[i][k] * b.ele[k][j];
	return c;
}

Matrix mat_pow(const Matrix& a, int n)
{
	if(n == 1)
		return a;
	Matrix aa = mat_pow(a, n/2);
	Matrix b = mat_mul(aa, aa);
	if(n%2 == 1)
		return mat_mul(a, b);
	else
		return b;
}

int main()
{
	int t,n,k,c,m;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		Matrix b(1, n);
		for(int i=0; i<n; ++i){
			scanf("%lf", &b.ele[0][i]);
		}
		Matrix a(n, n);
		for(int i=0; i<n; ++i){
			scanf("%d", &k);
			if(k == 0) a.ele[i][i] = 1;
			for(int j=0; j<k; ++j){
				scanf("%d", &c);
				a.ele[i][c-1] = 1./k;
			}
		}
		scanf("%d", &m);
		a = mat_pow(a, m);
		b = mat_mul(b, a);
		for(int i=0; i<n-1; ++i)
			printf("%.2f ", b.ele[0][i]);
		printf("%.2f\n", b.ele[0][n-1]);
	}
	return 0;
}