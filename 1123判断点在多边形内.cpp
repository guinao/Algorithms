#include<cstdio>
#include<cstring>
#include<cmath>

#define eps 1e-9

struct vector{
	double x,y;
	vector(double a, double b):
	x(a), y(b){}

	//dot product
	double operator*(const vector v)
	{
		return x*v.x + y*v.y;
	}

	double abs()
	{
		return sqrt(x*x+y*y);
	}
};

int main()
{
//	freopen("out.txt", "w", stdout);
	bool points[32][32];
	int x[4], y[4], a, b;
	int offset;
	char blank[] = "         ";
	puts("Program 4 by team X");
	while(EOF!=scanf("%d %d %d %d %d %d",&x[0],&y[0],&x[1],&y[1],&x[2],&y[2])){
		x[3] = x[0];
		y[3] = y[0];
		memset(points, 0, sizeof points);
		for(int i=0; i<19; i++){
			for(int j=0; j<19; j++){
				a = i - 9;
				b = j - 9;
				//计算待定点和多边形全部顶点的夹角和判断点是否在多边形内
				//计算几何的内容可以看黑书中相应章节
				double sum = 0;
				for(int k=0; k<3; ++k){
					vector v1 = vector(x[k]-a, y[k]-b);
					vector v2 = vector(x[k+1]-a, y[k+1]-b);
					double angle = acos(v1*v2/v1.abs()/v2.abs());
					if(fabs(angle-acos(-1.)) > eps)//不在边上
						sum += angle;
				}
				if(fabs(sum - 2*acos(-1.)) < eps)
					points[i][j] = true;
			}
		}
		offset = -1;
		for(int i=0; i<19 && offset<0; i++)
			for(int j=0; j<19 && offset<0; j++)
				if(points[i][j])
					offset = i;
		for(int j=19; j>=0; j--){
			int flag = true;
			int flag2 = false;
			for(int i=0; i<19; i++){
				if(points[i][j]){
					flag2 = true;
					if(flag){
						for(int k=0; k+offset<i; ++k)
							printf("%s", blank);
						flag = false;
					}
					printf("(%2d,%3d)",i-9,j-9);
					if(points[i+1][j]) putchar(' ');
				}
			}
			if(flag2) puts("");
		}
		puts("");
	}
	puts("End of program 4 by team X");
	return 0;
}