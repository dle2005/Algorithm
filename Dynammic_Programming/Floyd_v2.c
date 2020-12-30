#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void floyd2(int n, int **W, int **D, int **P) {
	int i, j, k; //for문에서 사용할 변수 선언

	for(i = 0; i <= n; i++) // P배열을 0으로 초기화
		for(j = 0; j <= n; j++) // 배열 생성시 0으로 초기화 하지만 pesudo code에 충실하기 위해 설정
			P[i][j] = 0;

	for(i = 0; i <= n; i++) // W배열을 D배열로 복사
		for(j = 0; j <= n; j++) // W배열은 const(상수)이며
			D[i][j] = W[i][j]; // D배열만을 사용

	for(k = 1; k <= n; k++) // 최단경로 구하기
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				if(D[i][k] + D[k][j] < D[i][j]) { // 현재의 경로와 새로운 경로를 비교, 새로운 경로가 최단경로일경우 갱신
					P[i][j] = k; // Path를 저장하는 P배열에 어떠한 정점을 거쳐 최단경로를 구했는지 저장
					D[i][j] = D[i][k] + D[k][j]; // 최단경로로 갱신
				}
}

void path(int q, int r, int **P) {
	if(P[q][r] != 0) { // P의 경로가 0 이 아닌 경우는, 다른 정점을 거쳐 최단경로가 갱신된 경우
		path(q, P[q][r], P); // 재귀 호출을 사용하여 최단 경로상의 중간 마디들을 구합니다.
		printf("v%d -> ", P[q][r]);
		path(P[q][r], r, P);
	}
}

int** init_matrix(int size) { // 2차원 배열 동적할당 함수
	int **matrix = (int**)malloc(sizeof(int*) * size); 
	for(int i = 0; i < size; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * size);
		memset(matrix[i], 0, sizeof(int)*size); // 배열을 0으로 초기화
	}

	return matrix;
}

void main() {

	int n = 5; // 배열의 크기는 예제와 같이 5로 설정
	int **W = init_matrix(n + 1); // 0번째는 사용하지 않아
	int **D = init_matrix(n + 1); // +1을 하여 2차원 배열 생성
	int **P = init_matrix(n + 1);

	for(int i = 1; i <= n; i++) // 입력부분
		for(int j = 1; j <= n; j++)
			scanf("%d", &W[i][j]);

	floyd2(n, W, D, P); // floyd알고리즘 실행

	printf("\n");
	for(int i = 1; i <= n; i++) { // floyd 알고리즘을 통해 얻은 최단경로 출력
		for(int j = 1; j <= n; j++)
			printf("%d ", D[i][j]);
		printf("\n");
	}
		
	printf("\n");
	for(int i = 1; i <= n; i++) { // floyd 알고리즘을 적용하여 만든 P배열 출력
		for(int j = 1; j <= n; j++)
			printf("%d ", P[i][j]);
		printf("\n");
	}
	
	printf("\n");
	for(int i = 1; i <= n; i++) { // 최단경로가 갱신된 경로가 어떻게 갱신되었는지를 출력
		for(int j = 1; j <= n; j++) {
			if(P[i][j] != 0) {
				printf("Path v%d ~ v%d: v%d -> ", i, j, i); 
				path(i, j, P);
				printf("v%d\n", j);
			}
		}
	}
}
