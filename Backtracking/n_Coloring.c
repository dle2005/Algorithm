#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n=4, m=3, vcolor[4];
int W[4][4]=
{{0,1,1,1},
{1,0,1,0},
{1,1,0,1},
{1,0,1,0}};

void m_coloring(int i);
bool promising(int i);


void main()
{
	int i=-1; 
	printf("[결과출력]\n");
	printf("v1 v2 v3 v4\n");
	m_coloring(i);
}

void m_coloring(int i)
{
	int color, j;
	if(promising(i))
	{
		if(i == n)
		{
			for(j=0;j<n;j++)
				printf(" %d ", vcolor[j]+1);
			printf("\n");
		}
		else
		{
			for(color=0;color<m;color++)
			{
				vcolor[i+1]=color;
				m_coloring(i+1);
			}
		}
	}
}

bool promising(int i)
{
	int j=0;
	bool check = true;
	while(j<i&&check)
	{
		if(W[i][j]&&vcolor[i]==vcolor[j])
			check = false;
		j++;
	}
	return check;
}
