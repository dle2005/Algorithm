#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** init_matrix(int size) //2���� �迭 ���� �Ҵ� 
{
   int i;
   int **matrix = (int**)malloc(sizeof(int *)*size);
   for(i = 0; i < size; i++)
      {
      matrix[i] = (int*)malloc(sizeof(int)*size);
      memset(matrix[i],0,sizeof(int)*size);
   }

   return matrix;
}

int* ini_matrix(int size) //1���� �迭 ���� �Ҵ�  
{
   int *matrix = (int*)malloc(sizeof(int *)*size);
   return matrix;
} 

void arrinput(int size, int **A) //�Է¹��� ����� ��� ���� �Է� 
{
   int i, j;
   for(i=0;i<size;i++)
   {
         printf("%d���� ����� ���� ���� �Է��Ͻÿ� : ",i);
         scanf("%d %d", &A[i][0], &A[i][1]);
   }
}

void d(int size, int **A, int *D) //������ �ʿ��� d�� ��ĵ�� ���� �ޱ�  
{
   int i;
   D[0]=A[0][0];
   for(i=0;i<size;i++)
      D[i+1]=A[i][1];
}

int minimult(int n, int *d, int **M, int **P) //���� ��İ���  
{
   int i, j, k, diagonal;
   for(i=0;i<n;i++)
      M[i][i]=0;
   for(diagonal=1;diagonal<=n-1;diagonal++)
      for(i=1;i<=(n-diagonal);i++)
      {
         j = i + diagonal;
         k=minimum(i,j,M,d);
         M[i][j]=M[i][k]+M[k+1][j]+(d[i-1]*d[k]*d[j]);
         P[i][j]=k;
      }   
      return M[1][n];
}

int minimum(int i, int j, int **M, int *d) //�ּҰ� ã��   
{
   int k, check=0;
   int min=0;
   for (k = i; k <= j - 1; k++) {
      if (min == 0) {
         min = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
         check = k;
      }
      else if (M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j] < min) {
         min = M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j];
         check = k;
      }
   }
   return check;
}

void f(int size, int **X) //�迭 ���  
{
   int i, j;
   for(i=1;i<=size;i++)
   {
      for(j=1;j<=size;j++)
         printf("%5d\t",X[i][j]);
      printf("\n");
   }
}

void order(int i, int j, int **P) //��� ���  
{
   if(i==j)
      printf("%c", 'A'+i-1);
   else
   {
      int k=P[i][j];
      printf("(");
      order(i,k,P);
      order(k+1,j,P);
      printf(")");
   }
}

int main()
{
   int numarr, **M, **A, *D, **P;
   int bestcase; 
   printf("���ϽǷ��� ����� ������ �Է����ּ��� : ");
   scanf("%d", &numarr);
   M = init_matrix(numarr+1);
   A = init_matrix(numarr+1);
   P = init_matrix(numarr+1);
   D = ini_matrix(numarr+1);
   arrinput(numarr, A);
   d(numarr, A, D);
   bestcase=minimult(numarr,D,M,P);
   printf("bestcase=%d\n", bestcase);
   printf("[�ּ� ���� ���ȭ��]\n");
   f(numarr, M);
   printf("[��� ���ȭ��]\n");
   f(numarr,P);
   printf("optimal order : ");
   order(1,numarr,P);
}
