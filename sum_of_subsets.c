#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *w, W, *include;

void sum_of_subsets (int i, int weight, int total);
bool promising (int i, int weight, int total);


void main()
{
	int n, i, total=0;
	
	printf("n개의 양의 정수를 입력하시오: ");
	scanf("%d", &n);
	
	//w와 include를 입력받는 n만크의 크기로 동적할당 
	w = (int*)malloc(sizeof(int)*n);
	include = (int*)malloc(sizeof(int)*n);
	
	printf("정렬된 양의 정수의 배열w를 입력하시오:\n") ;
	for(i=0;i<n;i++)
	{
		printf("w%d = ", i+1);
		scanf("%d", &w[i]);
		total+=w[i];
	}
	printf("총 무게 W를 입력하시오:= ");
	scanf("%d", &W);
	
	sum_of_subsets(0,0,total);
}

void sum_of_subsets (int i, int weight, int total)
{
	int j;
	
	if(promising(i, weight, total))
	{
		if(weight==W) //종료조건 
		{ 
			printf("[결과]\n");
			for(j=0;j<i;j++) //include[1]에서 include[n]까지 출력 
				printf("%s\n", include[j]);
			printf("\n");
		}
		else
		{
			include[i] = "yes"; //w[i+1]을 포함시킨다. 
			sum_of_subsets(i+1, weight+w[i], total-w[i]);
			include[i] = "no"; //w[i+1]을 포함시지 않는다.
			sum_of_subsets(i+1,weight, total-w[i]);
		}
	}
	
}

bool promising (int i, int weight, int total)
{ //유망한지 검사 
	return (weight+total >= W) 
		&& (weight == W || weight+w[i] <= W);
}
