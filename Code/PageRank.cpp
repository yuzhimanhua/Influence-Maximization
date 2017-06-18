#include <cstdio>
#include <queue>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
//#include <windows.h>
using namespace std;

#define NODE 20000
#define EDGE 100000
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
    choose[NODE] = {0},
    seed[TOPK] = {0},
    nb[NODE] = {0};
bool visit[NODE] = {0};
int n, m, K;
float delta[NODE] = {0};

double pr[NODE] = {0},
       pr2[NODE] = {0},
       deltap = 1e-8,
       cc = 0.9; 

void GenerateThreshold()
{
    for (int i = 0; i < n; i++){
        delta[i] = (float)rand()/RAND_MAX;
        //delta[i] = delta[i]*delta[i];
    }
}

int Simulate(int topk)
{
    queue <int> Q;
	int x,y,i,
	    tot = 0;
	float thrs;
	
	memset(visit,0,sizeof(visit));
	memset(nb,0,sizeof(nb));
	for (i = 0;i < topk; i++){
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

void PageRank()
{
	int x,tf;
	while (1){
		for (int i = 0; i < n; i++){
		    pr2[i] = (1-cc)/n;
		}
		for (int i = 0; i < n; i++)
		    for (int j = firstedge[i]; j != 0; j = E[j].next){
			    x = E[j].v;
			    pr2[x] += cc*pr[i]/deg[i];
		    }
		tf = 0;
		for (int i = 0; i < n; i++)
		    if (abs(pr[i]-pr2[i]) > deltap){
		    	tf = 1;
		    	break;
		    }
		if (!tf) break;
		for (int i = 0; i < n; i++) pr[i] = pr2[i];
	}
}

int main()
{
	int x,y,maxj,
	    tot=0;
	double maxd = 0,
	       totnum = 0;

	fp = fopen("../Data/GrQc.txt","r");
	fout = fopen("GrQcout.txt","w");
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
	printf("%d %d\n",n,tot);
	fclose(fp);
	
	for (int i = 0; i < n; i++) pr[i] = (double)1/n;
	PageRank();
	
	for (int i = 1; i <= TOPK; i++){
		maxd = 0; 
		for (int j = 0; j < n; j++)
		    if (pr[j] > maxd){
		        maxd = pr[j];
		        maxj = j;
		    }
		pr[maxj] = 0;
		seed[i-1] = maxj;
		cout<<maxd<<' '<<maxj<<endl;
	}
	
	end = clock();
    fprintf(fout,"%lfs\n",double(end-start)/CLOCKS_PER_SEC); 
	
	for (K = 0; K <= TOPK; K++){
		totnum = 0;
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

