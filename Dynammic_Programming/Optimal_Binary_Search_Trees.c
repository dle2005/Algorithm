#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct Node{
   char key[100];
   Node* left;
   Node* right;
};

float A[100][100];
int R[100][100];
char key[100][100] = { '\0' };
float prob[100];
Node* root;
int n, minavg;

void search(Node* tree, char *keyin)
{
   bool found = false;
   Node *p;

   p = tree;
   while (!found)
   {
      if (p->key == keyin)
         found = true;
      else if (keyin < p->key)
         p = p->left;
      else
         p = p->right;
   }
}

float minimum(int i, int j)
{
   int k, check = 0;
   float min = 0;

   for (k = i; k <= j; k++)
   {
      if (min == 0)
      {
         min = A[i][k - 1] + A[k + 1][j];
         check = k;
      }
      else if (A[i][k - 1] + A[k + 1][j] < min)
      {
         min = A[i][k - 1] + A[k + 1][j];
         check = k;
      }
   }
   R[i][j] = check;
   return min;
}

void optsearchtree()
{
   int i, j, k, diagonal;

   for (i = 1; i <= n; i++)
   {
      A[i][i - 1] = 0;
      A[i][i] = prob[i];
      R[i][i] = i;
      R[i][i - 1] = 0;
   }
   A[n + 1][n] = 0;
   R[n + 1][n] = 0;

   for (diagonal = 1; diagonal <= n - 1; diagonal++)
      for (i = 1; i <= n - diagonal; i++)
      {
         j = i + diagonal;
         A[i][j] = minimum(i, j);
         for (k = i; k <= j; k++)
            A[i][j] += prob[k];
      }
   minavg = A[1][n];
}

Node* tree(int i, int j)
{
   int k;
   Node *p;

   k = R[i][j];
   if (k == 0)
      return NULL;
   else
   {
      p = (Node *)malloc(sizeof(Node));
      memset(p->key, 0, sizeof(p->key));
      strncpy(p->key, key[k], strlen(key[k]));
      p->left = tree(i, k - 1);
      p->right = tree(k + 1, j);
      return p;
   }
}

void input()
{
   int i;
   printf("데이터 입력 개수 : ");
   scanf("%d", &n);
   for (i = 1; i <= n; i++)
   {
      printf("key%d의 데이터 입력 : ", i);
      scanf("%s", key[i]);
      printf("key%d의 확률 입력 : ", i);
      scanf("%f", &prob[i]);
   }
}

void printnode(Node *p)
{
   if (p != NULL) {
      printf("(");
      printnode(p->left);
      printf("%s", p->key);
      printnode(p->right);
      printf(")");
   }
}

int main()
{
   // root node
   root = (Node*)malloc(sizeof(Node));
   root->left = NULL;
   root->right = NULL;

   input();
   optsearchtree();
   root = tree(1, 1);
   printf("\nresult : %g\n\n", A[1][n]);

   printf("Matxrix A \n");
   for (int i = 1; i <= n + 1; i++)
   {
      for (int j = 0; j <= n; j++)
         printf("%g\t", A[i][j]);
      printf("\n");
   }
   printf("\n\n");

   printf("Matrix R \n");
   for (int i = 1; i <= n + 1; i++)
   {
      for (int j = 0; j <= n; j++)
         printf("%d\t", R[i][j]);
      printf("\n");
   }
   printf("\n\n");

   root = tree(1, n);
   printf("Tree\n");
   printnode(root);
   printf("\n");

   return 0;
}