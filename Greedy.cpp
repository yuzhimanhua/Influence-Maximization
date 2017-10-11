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
#define MAXK 200
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
    seed[MAXK] = {0},
    nb[NODE] = {0};
bool visit[NODE] = {0};
int n, m, K,
    TOPK = 20, 
    DIR = 0;
float delta[NODE] = {0};

float marg[NODE] = {0};
struct myless
{
    bool operator()(int x,int y){
	    return marg[x] < marg[y];
    }
};
bool cur[NODE];
priority_queue <int, vector<int>, myless> PQ;

void GenerateThreshold()
{
    for (int i = 0; i < n; i++){
        delta[i] = (float)rand()/RAND_MAX;
          delta[i] = sqrt(delta[i]);
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
	for (i = 0; i < topk; i++){
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

int main(int argc, char* argv[])
{
	int x,y,maxj,
	    tot = 0;
	float maxd,
	      totnum = 0;
	fp = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
    srand(time(NULL));
	
	if (argc >= 4){
        TOPK = atoi(argv[3]); 
    }

    if (argc >= 5 && argv[4] == "Directed"){
    	DIR = 1;
    }
    
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
		if (DIR == 0){
			tot++;
			E[tot].v = x;
			E[tot].next = firstedge[y];
			firstedge[y] = tot;
			deg[y]++;
		}
	}
	fclose(fp);
	
	memset(choose,0,sizeof(choose));
	
	for (int i = 0; i < n; i++){
	    marg[i] = NODE+1;
	    PQ.push(i);
	}
		
	for (int i = 1; i <= TOPK; i++){
	    memset(cur,0,sizeof(cur));
	    while (1){
	    	maxj = PQ.top();
	    	PQ.pop();
	    	maxd = marg[maxj];
	    	if (cur[maxj]){
	    		seed[i-1] = maxj;
		        fprintf(fout,"%d %f\n",maxj,maxd);
		        break;
	    	}
	    	else {
	    		seed[i-1] = maxj;
		        totnum = 0;
		        for (int u = 1; u <= T; u++){
		            GenerateThreshold();
		            totnum += Simulate(i)-Simulate(i-1);
	            }
	            marg[maxj] = totnum/T;
	            cur[maxj] = 1;
	            PQ.push(maxj);
	    	}
	    }
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

