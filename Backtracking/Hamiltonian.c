#include <stdio.h>
#include <stdbool.h>

#define N 4

typedef int index;

void hamiltonian(index i);
bool promising(index i);
void input(int n);
void f(int n);

int n=4, vindex[5]={1,0,0,0,1};
int W[N][N]=
{{0,1,0,1},
{1,0,1,0},
{0,1,0,1},
{1,0,1,0}};

void main()
{	
	printf("경로 출력\n");
	hamiltonian(0);
}

void hamiltonian(index i)
{
	index j;
	if(promising(i))
	{
		if(i==n-1)
		{
			for(j=0;j<=n;j++)
				printf("%d ", vindex[j]);
			printf("\n");
		}
		else
		{
			for(j=2;j<=n;j++)
			{
				vindex[i+1]=j;
				hamiltonian(i+1);
			}
		}
	}
}

bool promising(index i)
{
	index j;
	bool tnf;
	//시작점과 끝점간의 연결선이 없는 경우 
	if(i==n-1 && !W[vindex[n-1]-1][vindex[0]-1])
		tnf = false;
	//i>0시작점이 아닌
	//i번째 정점과 i-1번째 정점간의 연결선이 없는 경우 
	else if(i>0 && !W[vindex[i-1]-1][vindex[i]-1])
		tnf = false;
	else //이미 연결되었는지를 검사  
	{
		tnf = true;
		j=0;
		while(j<i && tnf)
		{
			if(vindex[i]==vindex[j])
				tnf = false;
			j++;
		}
	}
	return tnf;
}
