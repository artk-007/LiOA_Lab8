// Lab8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <iostream>
#include <locale.h>
#include <queue>
#include <malloc.h>
#include <windows.h>
using namespace std;
void rand_Zap_vz_nor(int* Matrix, int n) {
	srand(time(NULL));
	printf("Взвешаный неорентированный граф\n");
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Matrix[i * n + j] = 0;
			}
			if (i < j) {
				if (rand() % 100 > 50)
					Matrix[i * n + j] = rand() % 10;
				else
					Matrix[i * n + j] = 0;
				Matrix[j * n + i] = Matrix[i * n + j];
			}
		}
}
void dsit_0(int* Matrix, int n) {
	for (int i = 0; i < n; i++)
		Matrix[i] = 65536;
}
void BFSD_vz(int* Matrix, int* dist, int n, int v) {
	queue <int> Q;
	Q.push(v);
	dist[v] = 0;
	while (Q.empty() == false) {
		v = Q.front();
		Q.pop();
		printf("%d ", v + 1);
		for (int i = 0; i < n; i++) {
			if ((Matrix[v * n + i] != 0) && dist[i] > dist[v] + Matrix[v * n + i]) {
				Q.push(i);
				dist[i] = dist[v] + Matrix[v * n + i];
			}
		}
	}
	printf("\n");
}
void print_G(int* Matrix, int n) {
	printf("  ");
	for (int i = 0; i < n; i++)
		printf("%3d", i + 1);
	printf("\n\n");
	for (int i = 0; i < n; i++) {
		printf("%2d", i + 1);
		for (int j = 0; j < n; j++) {

			printf("%3d", Matrix[i * n + j]);
		}
		printf("\n");
	}
	printf("\n");

}
int main()
{
	setlocale(LC_ALL, "Rus");
	int* a, * DIST, size, *eks, max=0, min,*step;
	printf("введите кол-во вершин\n");
	scanf("%d", &size);
	a = (int*)malloc(size * size * sizeof(int));
	DIST = (int*)malloc(size * sizeof(int));
	eks = (int*)malloc(size * sizeof(int));
	step = (int*)malloc(size * sizeof(int));
	rand_Zap_vz_nor(a, size);
	print_G(a, size);
	dsit_0(DIST, size);
	for (int i = 0; i < size; i++) {
		max = 0;
		dsit_0(DIST, size);
		printf("от вершины %d\n", i + 1);
		BFSD_vz(a, DIST, size, i);
		for (int j = 0; j < size; j++)
		{
			if (DIST[j] != 65536) {
				printf("%d \t", DIST[j]);
				if (DIST[j] > max)
					max = DIST[j];
			}
			else
				printf("нет прохода \t");
			
			
		}
		eks[i] = max;

		printf("\n");
	}
	printf("\n");
	for (int j = 0; j < size; j++)
		printf("%d \t", eks[j]);
	min = eks[1];
	max = eks[1];
	for (int i=0; i < size; i++) {
		if (eks[i] > max)
			max = eks[i];
		if (eks[i] < min)
			min = eks[i];
	}
	printf("\n\nДиаметр графа=%d \t радиус графа=%d\n\n", max, min);
	printf("\n\nПериферийные вершины\n\n");
	for (int i = 0; i < size; i++) 
		if (eks[i] ==max)
			printf("%d \t", i+1);
	printf("\n\nЦентральные вершины\n\n");
	for (int i = 0; i < size; i++)
		if (eks[i] == min)
			printf("%d \t", i+1);
	printf("\n\n");
	for (int i = 0; i < size; i++)
	{
		step[i] = 0;
		for (int j = 0; j < size; j++) {
			if (a[i * size + j] != 0)
				step[i]++;
		}
		switch (step[i])
		{
		case 0: printf("\n\n%d вершина-изолированая\n\n",i+1);
			break;
		case 1:printf("\n\n%d вершина-концевая\n\n", i + 1);
			break;
		
		default:
			if(step[i]==size)
				printf("\n\n%d вершина-доминирующая\n\n", i + 1);
			
		}
	}

}



