#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define infinite 9999

typedef struct edge{
	int start;
	int end;
	int touch;
	int distance;
}edge;

void dijkstra(int n, int **W, edge *F);

void main()
{
	int i, j, n;
	printf("정점의 개수를 입력해주세요: ");
	scanf("%d", &n);
	edge *F = (edge*)malloc(sizeof(edge)*n);
	int **W = (int**)malloc(sizeof(int*)*n);
	for(i = 0; i < n; i++)
	{
		W[i] = (int*)malloc(sizeof(int)*n);
		memset(W[i],0,sizeof(int)*n);
	}
	
	printf("가중치 그래프를 입력해주세요:\n"); 
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &W[i][j]);
			
	dijkstra(n,W,F);
	for(i = 1; i < n; i++)
		printf("%d에서 %d까지의 최단 거리는 %d touch: %d\n",F[i].start, F[i].end+1, F[i].distance, F[i].touch);
}

void dijkstra(int n, int **W, edge *F)
{
	int i, j, vnear, min;
	edge e;
	int *touch, *length;
	touch = (int*)malloc(sizeof(int)*n);
	length = (int*)malloc(sizeof(int)*n);
	
	for(i = 1; i < n; i++)
	{
		touch[i] = 1;
		length[i] = W[0][i];
	}
	
	for(j = 1; j < n; j++)
	{
		min = infinite;
		for(i = 1; i < n; i++)
		{
			if(0<=length[i] && length[i] <= min)
			{
				min = length[i];
				vnear = i;
			}
		}
		
		e.start = 1;
		e.end = vnear;
		e.touch = touch[vnear];
		e.distance = length[vnear];
	
		F[vnear].start = e.start;
		F[vnear].end = e.end;
		F[vnear].touch = touch[vnear];
		F[vnear].distance = e.distance;
		
		for(i = 1; i < n; i++)
			if(length[vnear] + W[vnear][i] < length[i])
			{
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear+1;
			}
		length[vnear] = -1;			
	}
}

