#include <cstdio>
#include <queue>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <iostream>
//#include <windows.h>
#include <math.h>
using namespace std;

#define NODE 40000
#define EDGE 500000
#define TOPK 20
#define T    10000

FILE* fp;
FILE* fout;

struct edge
{
	int v, next;
};
edge E[EDGE];

int firstedge[NODE] = {0},
    deg[NODE] = {0},
    deg1[NODE] = {0},
    seed[TOPK] = {0},
    nb[NODE] = {0};
bool visit[NODE] = {0};
int n, m, K;
float delta[NODE] = {0};

void GenerateThreshold()
{
    for (int i = 0; i < n; i++){
        delta[i] = (float)rand()/RAND_MAX;  //Linear Threshold
    }
}

int Simulate()
{
    queue <int> Q;
	int x,y,i,
	    tot = 0;
	float thrs;
	
	memset(visit,0,sizeof(visit));
	memset(nb,0,sizeof(nb));
	for (i = 0; i < K; i++){
	    Q.push(seed[i]);
	    visit[seed[i]] = 1;
	    tot++;
	}
	while (!Q.empty()){
		x = Q.front();
		Q.pop();
		for (i = firstedge[x]; i != 0; i = E[i].next){
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
	fout = fopen("PhyoutDG.txt","w");
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
		tot++;
		E[tot].v = x;
		E[tot].next = firstedge[y];
		firstedge[y] = tot;
		deg[y]++;
	}
	fclose(fp);
	
	for (int i = 0; i < n; i++) deg1[i] = deg[i];
	for (int i = 1; i <= TOPK; i++){
		maxd = 0; 
		for (int j = 0; j < n; j++)
		    if (deg1[j] >= maxd){
		    	maxd = deg1[j];
		    	maxj = j;
		    }
		deg1[maxj] = 0;
		seed[i-1] = maxj;
		//printf("%d %d\n",maxj,maxd);
	}
	
	end = clock();
    fprintf(fout,"%lfs\n",double(end-start)/CLOCKS_PER_SEC);   
	
	for (K = 0; K <= TOPK; K++){
		totnum = 0;
		for (int i = 1; i <= T; i++){
			GenerateThreshold();
			totnum += Simulate();
			//cout<<totnum<<endl;
		}	
		fprintf(fout,"%d %d %d\n",K,seed[K-1],totnum/T);
	}
    
    fclose(fout);
	return 0;
}

