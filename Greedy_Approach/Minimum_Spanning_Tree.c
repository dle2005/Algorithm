#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int set_pointer;

typedef struct universe{
	int parent;
	int depth;
}universe;

typedef struct edge {
	int start;
	int end;
	int distance;
}edge;

universe *U;
int Vertex, Edge;

void makeset(int i);
set_pointer find(int i);
void merge(set_pointer p, set_pointer q);
bool equal(set_pointer p, set_pointer q);
void initial();
void bubblesort(edge* E);
void kruskal(int n, int m, edge *E, edge *F);

void main()
{
	printf("마디의 수를 입력하시오 : ");
	scanf("%d", &Vertex);
	printf("이음선의 수를 입력하시오 : ");
	scanf("%d", &Edge);
	 
	edge *E, *F;
	U = (universe*)malloc(sizeof(universe)*Edge); // 동적할당 
	E = (edge*)malloc(sizeof(edge)*Edge);
	F = (edge*)malloc(sizeof(edge)*Edge);
	
	int i;
	for(i=0; i<Edge; i++)
	{
		printf("시작과 종료 마디를 입력하시오 : ");
		scanf("%d %d", &E[i].start, &E[i].end);
		printf("이음선 가중치를 입력하시오 : ");
		scanf("%d", &E[i].distance);	
	}
	
	int n=1, m=0; // n은 마디의 개수 m은 이음선의 개수 
	bubblesort(E); 
	kruskal(n,m,E,F);
	
	int weight=0;
	printf("\n");
	printf("[출력 결과]\n\n");
	printf("최소비용 신장츠리에서 이음선의 집합 F\n");
	for(i=0; i<Vertex-1; i++)
	{
		printf("이음선 F[%d] (v%dv%d)의 가중치 : %d\n", i, F[i].start, F[i].end, F[i].distance);
		weight += F[i].distance;
	}
	printf("\n");
	printf("최소비용 신장트리 : %d", weight);
}

void makeset(int i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

set_pointer find(int i) // p가 인덱스 i를 포함하고 있는 집합을 가르키게 한다 
{
	int j = i;
	if(U[j].parent == j)
		return j;
	return find(U[j].parent);
}

void merge(set_pointer p, set_pointer q) // p와 q가 가르키고 있는 두 개의 집합을 하나로 합친다 
{
	if(U[p].depth == U[q].depth)
	{
		U[p].depth += 1;
		U[q].parent = p;
	} 
	else if (U[p].depth < U[q].depth)
      U[p].parent = q;
	else
      U[q].parent = p;
}
 
bool equal(set_pointer p, set_pointer q) // p와 q가 같은 집합을 가리키면 true를 넘겨준다 
{
	if(p == q)
		return true;
	else
		return false;
}

void initial() // n개의 서로소 부분집합을 초기화 
{				// (하나의 부분집합에 1에서 n사이의 인덱스가 정확히 하나 포함됨) 
	int i;
	for(i=0; i<Vertex; i++)
		makeset(i);
}

void bubblesort(edge* E) // 이음선 가중치를 오름차순으로 정렬 
{  
	int i, j, temp;
	for(i=0; i<Edge-1; i++)
	{
		for(j=0; j<Edge-(i+1); j++)
		{
			if(E[j].distance > E[j+1].distance)
			{
				temp = E[j].distance;
				E[j].distance = E[j+1].distance;
				E[j+1].distance = temp;
				
				temp = E[j].start;
				E[j].start = E[j+1].start;
				E[j+1].start = temp;
				
				temp = E[j].end;
				E[j].end = E[j+1].end;
				E[j+1].end = temp;
			}
		}
	}
}

void kruskal(int n, int m, edge *E, edge *F)
{
	int i, j;
	set_pointer p, q;
	edge e;
	
	initial(); // 소로소부분집합을 초기화 
	
	while(n < Vertex) // F에서 이음선의 수는 n-1보다 작다 
	{
		e.distance = E[m].distance; // e=아직 고려하지 않은 이음선 중 가중치가 최소인 이음선 
		e.start = E[m].start;
		e.end = E[m].end;
		i = e.start; // e로 연결된 마디의 인데스 
		j = e.end;
		p = find(i);
		q = find(j);
		
		if(!equal(p,q))
		{
			merge(p,q);
			F[n-1].distance = e.distance; // e를 F에 추가 
			F[n-1].start = e.start;
			F[n-1].end = e.end;
			n++;
		}
		m++;
	}
}