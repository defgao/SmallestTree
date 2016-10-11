//
//  main.cpp
//  ��С������
//
//  Created by ������ on 16/4/7.
//  Copyright ? 2016�� HIT. All rights reserved.
//

#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
#define MAX 10
#define INF 65535
using namespace std;
typedef char Elem;
typedef struct {
	int n, e;
	Elem vertex[MAX];
	int edge[MAX][MAX];
} MTGraph;
typedef struct{
	int begin, end, weight;
} Edge;
ifstream input("input.txt");
ofstream output("output.txt",ios::app);
int Locate(Elem vertex, MTGraph *G){
	for (int i = 0; i<G->n; i++){
		if (G->vertex[i] == vertex) return i;
	}
	return -1;
}
void CreateMTGraph(MTGraph *G) {
	input >> G->n >> G->e;
	output << "����ͼ�Ķ��㡢�߸�����" << setw(5) << G->n << setw(5) << G->e << endl;
	output << "������Ϣ��";
	for (int i = 0; i<G->n; i++) {
		input >> G->vertex[i];
		output << setw(5) << G->vertex[i];
	}
	output << endl;
	for (int i = 0; i<G->n; i++) {
		for (int j = 0; j<G->n; j++) {
			G->edge[i][j] = INF;
		}
	}
	Elem head, tail;
	int weight;
	for (int i = 0; i<G->e; i++) {
		input >> head >> tail >> weight;
		output << "��" << i + 1 << "���ߣ�" << setw(5) << head << "<-->" << tail << ":" << weight << endl;
		while (Locate(head, G) == -1 || Locate(tail, G) == -1) {
			output << "����Ϣ����"<<endl;
			input >> head >> tail >> weight;
			output << "��" << i + 1 << "���ߣ�" << setw(5) << head << "<-->" << tail << ":" << weight << endl;
		}
		int k = Locate(head, G), l = Locate(tail, G);
		G->edge[k][l] = G->edge[l][k] = weight;
	}
	output<< "*****����ͼ�ڽӾ����ѽ��ɣ�*****" << endl;
}
void CreateHMTGraph(MTGraph *G) {
	input >> G->n >> G->e;
	output << "����ͼ�Ķ��㡢�߸�����" << setw(5) << G->n << setw(5) << G->e << endl;
	output << "������Ϣ��";
	for (int i = 0; i<G->n; i++){
		input >> G->vertex[i];
		output << setw(5) << G->vertex[i];
	}
	output << endl;
	for (int i = 0; i<G->n; i++){
		for (int j = 0; j<G->n; j++){
			G->edge[i][j] = INF;
		}
	}
	Elem head, tail;
	int weight;
	for (int i = 0; i<G->e; i++) {
		input >> head >> tail >> weight;
		output << "��" << i + 1 << "���ߣ�" << setw(5) << head << "-->" << tail << ":" << weight << endl;
		while (Locate(head, G) == -1 || Locate(tail, G) == -1) {
			output << "�ߵ���Ϣ����"<<endl;
			input >> head >> tail >> weight;
			output << "��" << i + 1 << "���ߣ�" << setw(5) << head << "-->" << tail << ":" << weight << endl;
		}
		int k = Locate(head, G), l = Locate(tail, G);
		G->edge[k][l] = weight;
	}
	output<< "*****����ͼ�ڽӾ����ѽ��ɣ�*****" << endl;
}
void Prim(MTGraph &G,MTGraph &F){
	F = G;
	for (int i = 0; i < F.n; i++) {
		for (int j = 0; j < F.n; j++){
			F.edge[i][j] = -1;
		}
	}
	bool visited[MAX];
	for (int i = 0; i<G.n; i++){
		visited[i] = false;
	}
	queue<char> BT;
	int vex[MAX], lowcost[MAX];
	lowcost[0] = 0;
	vex[0] = 0;
	for (int i = 1; i<G.n; i++){
		lowcost[i] = G.edge[0][i];
		vex[i] = 0;
	}
	int num=0;
	output << "�ܹ�����С�������ߵ�Ȩֵ��";
	for (int i = 1; i<G.n; i++){
		int min = INF;
		int j = 1;
		int k = 0;
		while (j<G.n){
			if (lowcost[j] != 0 && lowcost[j]<min){
				min = lowcost[j];
				k = j;
			}
			j++;
		}
		output<< "(" << G.vertex[vex[k]] << "," << G.vertex[k] << ")-->" << G.edge[vex[k]][k] << "  ";
		F.edge[vex[k]][k] = vex[k];
		if (!visited[Locate(G.vertex[vex[k]], &G)]){
			BT.push(G.vertex[vex[k]]);
			visited[Locate(G.vertex[vex[k]], &G)] = true;
		}
		if (!visited[Locate(G.vertex[k], &G)]){
			visited[Locate(G.vertex[k], &G)] = true;
			BT.push(G.vertex[k]);
		}
		num += G.edge[vex[k]][k];
		lowcost[k] = 0;
		for (int j = 1; j<G.n; j++){
			if (lowcost[j] != 0 && G.edge[k][j] <lowcost[j]){
				lowcost[j] = G.edge[k][j];
				vex[j] = k;
			}
		}
	}
	output<<endl << "Ԥ����С��������Ȩֵ��" << num << endl;
	if (BT.size() == G.n){
		output << "��С�������������ʾ��" << endl << " ";
		for (int i = 0; i < G.n; i++) {
			output << setw(5) << G.vertex[i];
		}
		output << endl;
		for (int i = 0; i < F.n; i++){
			output << G.vertex[i];
			for (int j = 0; j < F.n; j++){
				output << setw(5) << F.edge[i][j];
			}
			output << endl;
		}
	}
	else{
		output<< "ͼ����ͨ���޷�������С��������"<<endl;
	}
}
int find(int parent[], int f){
	while (parent[f] > 0){
		f = parent[f];
	}
	return f;
}
int cmp(const void *a, const void *b){
	return (*(Edge *)a).weight > (*(Edge *)b).weight ? 1 : -1;
}
void Kruskal(MTGraph &G,MTGraph &F){
	F = G;
	for (int i = 0; i < F.n; i++){
		for (int j = 0; j < F.n; j++) {
			F.edge[i][j] = -1;
		}
	}
	bool visited[MAX];
	for (int i = 0; i < G.n; i++){
		visited[i] = false;
	}
	int parent[MAX];
	for (int i = 0; i<G.n; i++){
		parent[i] = 0;
	}
	queue<int> kk;
	Edge edges[MAX];
	int knum = 0;
	for (int i = 0; i<G.n-1; i++){
		for (int j = i+1; j<G.n; j++){
			if (G.edge[i][j] != INF){
				edges[knum].begin = i;
				edges[knum].end = j;
				edges[knum].weight = G.edge[i][j];
				knum++;
			}
		}
	}
	qsort(edges,MAX, sizeof(edges[0]), cmp);
	output<< "�ܹ�����С�������ı�ȨֵΪ��";
	int num = 0;
	for (int i = 0; i<G.e; i++){
		int n = find(parent, edges[i].begin);
		int m = find(parent, edges[i].end);
		if (n != m){
			parent[n] = m;
			output << "(" << G.vertex[edges[i].begin] << "," << G.vertex[edges[i].end] << ")-->" << edges[i].weight << "  ";
			F.edge[edges[i].begin][edges[i].end] = edges[i].begin;
			if (!visited[Locate(G.vertex[edges[i].begin], &G)]){
				kk.push(G.vertex[edges[i].begin]);
				visited[Locate(G.vertex[edges[i].begin], &G)] = true;
			}
			if (!visited[Locate(G.vertex[edges[i].end], &G)]){
				visited[Locate(G.vertex[edges[i].end], &G)] = true;
				kk.push(G.vertex[edges[i].end]);
			}
			num += edges[i].weight;
		}
	}
	output << endl << "Ԥ����С��������Ȩֵ��" << num << endl;
	if (kk.size() == G.n){
		output << "��С�������������ʾ��" << endl << " ";
		for (int i = 0; i < G.n; i++) {
			output << setw(5) << G.vertex[i];
		}
		output << endl;
		for (int i = 0; i < F.n; i++) {
			output << G.vertex[i];
			for (int j = 0; j < F.n; j++) {
				output << setw(5) << F.edge[i][j];
			}
			output << endl;
		}
	}
	else {
		output << "ͼ����ͨ���޷�������С��������" << endl;
	}
}
int main(int argc, const char * argv[]) {
	MTGraph *G = new MTGraph;
	MTGraph *F = new MTGraph;
	char choose;
	while (1) {
		cout << "�Ƿ�ʼ��";
		cin >> choose;
		if (choose != 'y' && choose != 'Y') break;
		int num;
		cout << "��ѡ��ͼ��ʽ��";
		cin >> num;
		output << "�û�ѡ��Ľ�ͼ��ʽ��" << setw(5) << num << endl;
		switch (num) {
		case 1:
			CreateHMTGraph(G);
			break;
		case 2:
			CreateMTGraph(G);
			break;
		default:
			break;
		}
		cout << "��ѡ��������С�������㷨��";
		cin >> num;
		output << "�û�ѡ���������С�������㷨��" << setw(5) << num << endl;
		switch (num){
		case 1:
			Prim(*G,*F);
			break;
		case 2:
			Kruskal(*G,*F);
			break;
		default:
			break;
		}
	}
	return 0;
}

