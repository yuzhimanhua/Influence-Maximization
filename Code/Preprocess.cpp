#include <fstream>
using namespace std;
#define MAXN 5300

FILE* fp;
FILE* fout;

int k = 0,
    f[MAXN][MAXN]={0},
    n,m,x,y;

int main()
{
	fp = fopen("GrQc.txt","r");
	fout = fopen("Preprocess.txt","w");
	
	fscanf(fp,"%d %d",&n,&m);
	//fprintf(fout,"%d %d\n",n,2*m);

	for (int i = 0; i < m; i++){
	    fscanf(fp,"%d %d",&x,&y);
	    if (f[x][y] == 0 && f[y][x] == 0){
	    	fprintf(fout,"%d %d\n",x,y);
	    	//fprintf(fout,"%d %d\n",y,x);
	    	f[x][y] = 1;
	    	f[y][x] = 1;
	    } 
	}
	return 0;
}
