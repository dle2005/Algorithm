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
	printf("������ ���� �Է��Ͻÿ� : ");
	scanf("%d", &Vertex);
	printf("�������� ���� �Է��Ͻÿ� : ");
	scanf("%d", &Edge);
	 
	edge *E, *F;
	U = (universe*)malloc(sizeof(universe)*Edge); // �����Ҵ� 
	E = (edge*)malloc(sizeof(edge)*Edge);
	F = (edge*)malloc(sizeof(edge)*Edge);
	
	int i;
	for(i=0; i<Edge; i++)
	{
		printf("���۰� ���� ���� �Է��Ͻÿ� : ");
		scanf("%d %d", &E[i].start, &E[i].end);
		printf("������ ����ġ�� �Է��Ͻÿ� : ");
		scanf("%d", &E[i].distance);	
	}
	
	int n=1, m=0; // n�� ������ ���� m�� �������� ���� 
	bubblesort(E); 
	kruskal(n,m,E,F);
	
	int weight=0;
	printf("\n");
	printf("[��� ���]\n\n");
	printf("�ּҺ�� ������������ �������� ���� F\n");
	for(i=0; i<Vertex-1; i++)
	{
		printf("������ F[%d] (v%dv%d)�� ����ġ : %d\n", i, F[i].start, F[i].end, F[i].distance);
		weight += F[i].distance;
	}
	printf("\n");
	printf("�ּҺ�� ����Ʈ�� : %d", weight);
}

void makeset(int i)
{
	U[i].parent = i;
	U[i].depth = 0;
}

set_pointer find(int i) // p�� �ε��� i�� �����ϰ� �ִ� ������ ����Ű�� �Ѵ� 
{
	int j = i;
	if(U[j].parent == j)
		return j;
	return find(U[j].parent);
}

void merge(set_pointer p, set_pointer q) // p�� q�� ����Ű�� �ִ� �� ���� ������ �ϳ��� ��ģ�� 
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
 
bool equal(set_pointer p, set_pointer q) // p�� q�� ���� ������ ����Ű�� true�� �Ѱ��ش� 
{
	if(p == q)
		return true;
	else
		return false;
}

void initial() // n���� ���μ� �κ������� �ʱ�ȭ 
{				// (�ϳ��� �κ����տ� 1���� n������ �ε����� ��Ȯ�� �ϳ� ���Ե�) 
	int i;
	for(i=0; i<Vertex; i++)
		makeset(i);
}

void bubblesort(edge* E) // ������ ����ġ�� ������������ ���� 
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
	
	initial(); // �ҷμҺκ������� �ʱ�ȭ 
	
	while(n < Vertex) // F���� �������� ���� n-1���� �۴� 
	{
		e.distance = E[m].distance; // e=���� ������� ���� ������ �� ����ġ�� �ּ��� ������ 
		e.start = E[m].start;
		e.end = E[m].end;
		i = e.start; // e�� ����� ������ �ε��� 
		j = e.end;
		p = find(i);
		q = find(j);
		
		if(!equal(p,q))
		{
			merge(p,q);
			F[n-1].distance = e.distance; // e�� F�� �߰� 
			F[n-1].start = e.start;
			F[n-1].end = e.end;
			n++;
		}
		m++;
	}
}