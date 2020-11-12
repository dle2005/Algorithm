
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void floyd(int n,int **w,int **d,int **p)
{
   int i,j,k;
   for(i=0;i<n;i++)
    for(j=0;j<n;j++)
       {
      p[i][j] = 0;
      d[i][j] = w[i][j];
   }

 
 
 for(k=0;k<n;k++)
  {
  
  for(i=0;i<n;i++)
   {
   for(j=0;j<n;j++)
   {
      if(d[i][k] + d[k][j] < d[i][j])
      {
         p[i][j] = k+1;
         d[i][j] = d[i][k] + d[k][j];
    	 }
    	 printf("%d", d[i][j]);
    }
   printf("\n");  
}
   printf("\n");  
}
}

int** init_matrix(int size)
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

void in(int n, int **w)
{
   int a,b;
   for(a=0;a<n;a++)
     for(b=0;b<n;b++)
       scanf("%d", &w[a][b]);
       
}

void out(int n,int **d)
{
   int c,q;
   for(c=0;c<n;c++)
     {
    for(q=0;q<n;q++)
      printf(" %3d", d[c][q]);
      printf("\n");
  }
}

void main()
{
   int **w, **d, **p;
   int n; 
   printf("배열크기를 입력하시오 : ");
   scanf("%d",&n);
   w = init_matrix(n);
    d = init_matrix(n);
    p = init_matrix(n);
   printf("배열을 입력하시오 : ");
   printf("\n");
   in(n,w);
   floyd(n,w,d,p);
   printf("결과 값 출력 : ");
   printf("\n"); 
   out(n,d);
}
