#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *w, W, *include;

void sum_of_subsets (int i, int weight, int total);
bool promising (int i, int weight, int total);


void main()
{
	int n, i, total=0;
	
	printf("n���� ���� ������ �Է��Ͻÿ�: ");
	scanf("%d", &n);
	
	//w�� include�� �Է¹޴� n��ũ�� ũ��� �����Ҵ� 
	w = (int*)malloc(sizeof(int)*n);
	include = (int*)malloc(sizeof(int)*n);
	
	printf("���ĵ� ���� ������ �迭w�� �Է��Ͻÿ�:\n") ;
	for(i=0;i<n;i++)
	{
		printf("w%d = ", i+1);
		scanf("%d", &w[i]);
		total+=w[i];
	}
	printf("�� ���� W�� �Է��Ͻÿ�:= ");
	scanf("%d", &W);
	
	sum_of_subsets(0,0,total);
}

void sum_of_subsets (int i, int weight, int total)
{
	int j;
	
	if(promising(i, weight, total))
	{
		if(weight==W) //�������� 
		{ 
			printf("[���]\n");
			for(j=0;j<i;j++) //include[1]���� include[n]���� ��� 
				printf("%s\n", include[j]);
			printf("\n");
		}
		else
		{
			include[i] = "yes"; //w[i+1]�� ���Խ�Ų��. 
			sum_of_subsets(i+1, weight+w[i], total-w[i]);
			include[i] = "no"; //w[i+1]�� ���Խ��� �ʴ´�.
			sum_of_subsets(i+1,weight, total-w[i]);
		}
	}
	
}

bool promising (int i, int weight, int total)
{ //�������� �˻� 
	return (weight+total >= W) 
		&& (weight == W || weight+w[i] <= W);
}
