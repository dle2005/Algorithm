#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//�Է� ���� �迭�� ũ�⸸ŭ �����Ҵ� ���ִ� �Լ�  
int** init(int size)
{
    int** matrix;
    int i;
    matrix = (int**)malloc(sizeof(int*)*size);
    for(i=0;i<size;i++)
    {
       matrix[i]=(int*)malloc(sizeof(int)*size);
       memset(matrix[i], 0, sizeof(int)*size);
    }
    
    return matrix;
}
//A�� B�迭 �Է¹޴� �� ��  
void AB(int **X,int n)
{
    int i, j;
    printf("�迭 �� �Է�: \n");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d", &X[i][j]);
}  
// 4���� �κ���ķ� ������ 
void dev(int **m, int** matrix11, int** matrix12, int** matrix21, int** matrix22, int n)
{
   for(int i = 0; i < n; i++)
   {
      for(int j = 0; j < n; j++)
      {
         matrix11[i][j] = m[i][j];                  // �»�� ���
         matrix12[i][j] = m[i][j + n];            // ���� ���
         matrix21[i][j] = m[i + n][j];            // ���ϴ� ���
         matrix22[i][j] = m[i + n][j + n];      // ���ϴ� ���
      }
   }
}
//�迭 �����ϴ� �� ��  
void m(int n, int **X, int **Y, int **Z)
{
    int i, j, k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
                Z[i][j]+=X[i][k]*Y[k][j];
        }
}
// ����� ��
void sum(int** a, int** b, int** c, int n)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j< n; j++)
      {
         c[i][j] = a[i][j] + b[i][j];
      }
   }
}
// ����� ���� 
void sub(int** a, int** b, int** c, int n)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j< n; j++)
      {
         c[i][j] = a[i][j] - b[i][j];
      }
   }
}
void merge(int **m, int** matrix11, int** matrix12, int** matrix21, int** matrix22, int n)
{
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         m[i][j] = matrix11[i][j];
         m[i][j + n] = matrix12[i][j];
         m[i + n][j] = matrix21[i][j];
         m[i + n][j + n] = matrix22[i][j];
      }
   }
}
void strassen(int **a, int **b, int**c, int n)
{
   // �Ӱ谪���� ���� ��� �Ϲ� ����� �� ����
   if(n <= 2)
   {
      m(n, a, b, c);
      return;
   }
   else // ��� 4��� 
   {
      //�Լ� ����
       int **a11, **a12, **a21, **a22;
       int **b11, **b12, **b21, **b22;
       int **c11, **c12, **c21, **c22;
       int **m1, **m2, **m3, **m4, **m5, **m6, **m7;
       int **tempA, **tempB;
    
       //�Ҵ����� ��  
       a11=init(n/2);   a12=init(n/2);  a21=init(n/2);  a22=init(n/2);
       b11=init(n/2);   b12=init(n/2);  b21=init(n/2);  b22=init(n/2);
       c11=init(n/2);   c12=init(n/2);  c21=init(n/2);  c22=init(n/2);
       m1=init(n/2);   m2=init(n/2);   m3=init(n/2);
       m4=init(n/2);   m5=init(n/2);   m6=init(n/2);   m7=init(n/2);
      tempA=init(n/2);            tempB=init(n/2);

         //�迭 �ɰ���  
       dev(a, a11, a12, a21, a22, n/2);
       dev(b, b11, b12, b21, b22, n/2);
       
       sum(a11, a22, tempA, n/2);
       sum(b11, b22, tempB, n/2);
       strassen(tempA, tempB, m1, n/2);    // m1 = (a11+a11)(b11+b22)
      
      sum(a21, a22, tempA, n/2);          // a21+a22
      strassen(tempA, b11, m2, n/2);      // m2 = (a21+a22)b11

      sub(b12, b22, tempB, n/2);          // b12-b22
      strassen(a11, tempB, m3, n/2);      // m3 = a11(b12-b22)

      sub(b21, b11, tempB, n/2);          // b21-b11
      strassen(a22, tempB, m4, n/2);      // m4 = a22(b21-11)

      sum(a11, a12, tempA, n/2);          // a11+a12
      strassen(tempA, b22, m5, n/2);          // m5 = (a11+a12)b22

      sub(a21, a11, tempA, n/2);          // a21-a11
      sum(b11, b12, tempB, n/2);          // b11+b12
      strassen(tempA, tempB, m6, n/2);    // m6 = (a21-a11)(b11+b12)

      sub(a12, a22, tempA, n/2);          // a12-a22
      sum(b21, b22, tempB, n/2);          // b21+b22
      strassen(tempA, tempB, m7, n/2);    // m7 = (a12 - a22)(a12 - a22)

      // ������ ���� m1~m7 �����  c11 ~ c22 �� �����.
      sum(m1, m4, tempA, n/2);    //m1 + m4
      sum(tempA, m7, tempB, n/2); //m1 + m4 + m7
      sub(tempB, m5, c11, n/2);    //c11 = m1 + m4 - m5 + m7

      sum(m3, m5, c12, n/2);       //c12 = m3 + m5

      sum(m2, m4, c21, n/2);       //c21 = m2 + m4

      sum(m1, m3, tempA, n/2);    //m1 + m3
      sum(tempA, m6, tempB, n/2); //m1 + m3 + m6
      sub(tempB, m2, c22, n/2);    //c22 = m1 + m3 - m2 + m6

      //�纴��
      merge(c, c11, c12, c21, c22, n/2);
   }
}
int main()
{
    int n, i, j, garo, sero, high, num=2;
    printf("���� �迭 �Է� : ");
    scanf("%d", &garo);
    printf("���� �迭 �Է� : ") ;
    scanf("%d", &sero);
    
    //�ִ밪�� ������ 2�� �ŵ�����  ã��  
   if(garo>sero)
       high=garo;
    else
       high=sero;
    while(1)
    {
       if(high>num)
          num=num*2;
       else
       {
          n=num;
          break;
      }
   }

      //�Լ� ����  
    int **A, **B, **C;
    
    //�Ҵ����� ��  
    A=init(n);  
   B=init(n);   
   C=init(n);

   //a�� b �迭�� nxn���� �Է¹ޱ�  
    AB(A, n);
    AB(B, n);
    
    strassen(A,B,C,n);
    
      //������ ����ϱ�
      printf("\n [��� ȭ��]\n");
    for (i = 0; i<n; i++)
    {
        for (j = 0; j<n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

   return 0; 
}