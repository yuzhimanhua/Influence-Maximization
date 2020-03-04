#include <cstdio>
#include <queue>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
//#include <windows.h>
using namespace std;

#define NODE 100000
#define EDGE 1000000
#define MAXK 60
#define T    10000

FILE* fp;
FILE* fs;

struct edge
{
    int v, next;
};
edge E[EDGE];

int firstedge[NODE] = {0},
    deg[NODE] = {0},
    degin[NODE] = {0},
    seed[MAXK] = {0},
    nb[NODE] = {0};
bool visit[NODE] = {0};
int n, m, 
    TOPK = 20, 
    DIR = 0;
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
            thrs = (float)nb[y]/degin[y];
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
    int x, y,
        tot = 0;
    float z,
          totnum = 0;
    fp = fopen(argv[1], "r");
    fs = fopen(argv[2], "r");
    srand(time(NULL));
    
    if (argc >= 4){
        TOPK = atoi(argv[3]); 
    }

    if (argc >= 5 && argv[4][0] == 'D'){
        DIR = 1;
    }
    
    time_t start,end;
    start = clock();
    
    fscanf(fp, "%d %d", &n, &m);
    for (int i = 0; i < m; i++){
        fscanf(fp, "%d %d", &x, &y);
        tot++; 
        E[tot].v = y;
        E[tot].next = firstedge[x];
        firstedge[x] = tot;
        deg[x]++;
        degin[y]++;
        if (DIR == 0){
            tot++;
            E[tot].v = x;
            E[tot].next = firstedge[y];
            firstedge[y] = tot;
            deg[y]++;
            degin[x]++;
        }
    }
    fclose(fp);

    for (int i = 0; i < TOPK; i++){
        fscanf(fs, "%d %f", &x, &z);
        seed[i] = x;
    }
    fclose(fs);
    
    for (int i = 1; i <= T; i++){
        GenerateThreshold();
        totnum += Simulate(TOPK);
        //cout<<totnum<<endl;
    }
    printf("Expected Influence: %d\n", (int)totnum/T);

    end = clock();
    printf("%lfs\n", double(end-start)/CLOCKS_PER_SEC); 

    return 0;
}

