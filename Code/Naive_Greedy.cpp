#include <cstdio>
#include <queue>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <iostream>
//#include <windows.h>
using namespace std;

#define NODE 50000
#define EDGE 1000000
#define TOPK 20
#define T    10000

FILE* fp;
FILE* fout;

struct edge
{
	int v,next;
};
edge E[EDGE];

int firstedge[NODE] = {0},
    deg[NODE] = {0},
    choose[NODE] = {0},
    seed[TOPK] = {0},
    nb[NODE]={0};
bool visit[NODE] = {0};
int n,m,K;
float delta[NODE] = {0};

void GenerateThreshold()
{
    for (int i = 0; i < n; i++){
        delta[i] = (float)rand()/RAND_MAX;
    }
}

int Simulate(int topk)
{
    queue <int> Q;
	int x,y,i,
	    tot=0;
	float thrs;
	
	memset(visit,0,sizeof(visit));
	memset(nb,0,sizeof(nb));
	for (i = 0; i < topk; i++){
	    Q.push(seed[i]);
	    visit[seed[i]] = 1;
	    tot++;
	}
	while (!Q.empty()){
		x = Q.front();
		Q.pop();
		for (i = firstedge[x];i != 0; i = E[i].next){
			y = E[i].v;
			nb[y]++;
			thrs = (float)nb[y]/deg[y];
			if (thrs >= delta[y] && !visit[y]){
				Q.push(y);
				visit[y] = 1;
				tot++;
			}
		}
	}
	return tot;
}

int main()
{
	int x,y,
	    tot = 0,
	    maxd,maxj,totnum;

	fp = fopen("NetPhy.txt","r");
	fout = fopen("PhyoutGR.txt","w");
    srand(time(NULL));
    
    time_t start,end;
	start = clock();
    //Sleep(30);
	
	fscanf(fp,"%d %d",&n,&m);
	for (int i = 0; i < m; i++){
	    fscanf(fp,"%d %d",&x,&y);
	    tot++; 
		E[tot].v = y;
		E[tot].next = firstedge[x];
		firstedge[x] = tot;
		deg[x]++;
		//tot++;
		//E[tot].v = x;
		//E[tot].next = firstedge[y];
		//firstedge[y] = tot;
		//deg[y]++;
	}
	fclose(fp);
	
	memset(choose,0,sizeof(choose));
	for (int i = 1; i <= TOPK; i++){
		maxd = 0; 
		for (int j = 0; j<n; j++)
		    if (!choose[j]){
		        seed[i-1] = j;
		        totnum = 0;
		        for (int u = 1; u <= T; u++){
		            GenerateThreshold();
		            totnum += Simulate(i);
	            }
	            if (totnum >= maxd){
	            	maxd = totnum;
	            	maxj = j;
	            }
		    }
		choose[maxj] = 1;
		seed[i-1] = maxj;
		printf("%d %d\n",maxj,maxd/T);
	}
	
	end = clock();
    fprintf(fout,"%lfs\n",double(end-start)/CLOCKS_PER_SEC); 
	
	for (K = 0; K <= TOPK; K++){
		totnum=0;
		for (int i = 1; i <= T; i++){
			GenerateThreshold();
			totnum += Simulate(K);
			//cout<<totnum<<endl;
		}
		fprintf(fout,"%d %d %d\n",K,seed[K-1],(int)totnum/T);
	}  
    
    fclose(fout);
	return 0;
}


