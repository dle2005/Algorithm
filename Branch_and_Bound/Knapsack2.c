#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

int n, *p, *w, W, maxprofit;

typedef struct node {
    int level;
    int profit;
    int weight;
} node;

int front = -1;
int rear = -1;
node queue[MAX];

bool empty() {
    if(front == rear) return true;
    else return false;
}

void enqueue(node v) {
    rear = rear+1;
//    printf("enquee %d %d %d\n", v.level, v.profit, v.weight);
    queue[rear].level = v.level;
    queue[rear].profit = v.profit;
    queue[rear].weight = v.weight;
}

void dequeue(node *v) {
    front = front+1;
    v->level = queue[front].level;
    v->profit = queue[front].profit;
    v->weight = queue[front].weight;
//    printf("dequee %d %d %d\n", v->level, v->profit, v->weight);
}

float bound(node u) {
    int j, k, totweight;
    float result;

    if(u.weight >= W) return 0;
    else {
        result = u.profit; j = u.level + 1; totweight = u.weight;
        while((j <= n) && (totweight + w[j] <= W)) {
            totweight = totweight + w[j];
            result = result + p[j];
            j++;
        }
        k = j;
        if(k <= n) result = result + (W - totweight) * p[k] / w[k];
        return result;
    }
}
    
void knapsack2() {
    node u, v;
    v.level = 0; v.profit = 0; v.weight = 0; maxprofit = 0;
    enqueue(v);

    while(!empty()) {
        dequeue(&v);

        printf("%d profit: %3d weight: %3d bound: %3d maxprofit: %3d\n",
                v.level, v.profit, v.weight, (int)bound(v), maxprofit);

        u.level = v.level+1;
        u.profit = v.profit + p[u.level];
        u.weight = v.weight + w[u.level];
        
        if((u.weight <= W) && (u.profit > maxprofit))
            maxprofit = u.profit;
        if(bound(u) > (float)maxprofit) enqueue(u);

        u.weight = v.weight;
        u.profit = v.profit;

        if(bound(u) > (float)maxprofit) enqueue(u);
    }
}

void main() {
    printf("n = ");
    scanf("%d", &n);
    printf("W = ");
    scanf("%d", &W);

    w = (int *)malloc(sizeof(int) * n + 1);
    p = (int *)malloc(sizeof(int) * n + 1);
    
    printf("w[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    printf("p[1...n] = ");
    for(int i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    printf("\n");

    knapsack2();

    printf("maxprofit = %d\n", maxprofit);
}


