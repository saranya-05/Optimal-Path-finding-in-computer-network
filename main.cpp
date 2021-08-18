#include<iostream>
#include<time.h>
#include<iomanip>
#include<string.h>
#define INF 9999
using namespace std;
int min(int a, int b);
int cost[10][10], adj[10][10];
inline int min(int a, int b){
   return (a<b)?a:b;
}
void johnson(int adj[10][10],int vert)
{
    for (int i = 1; i <= vert; i++)
      for (int j = 1; j <= vert; j++) {
         if (adj[i][j] == 0 && i != j)
            adj[i][j] = INF;
      }
    for (int k = 1; k <= vert; k++)
      for (int i = 1; i <= vert; i++)
         for (int j = 1; j <= vert; j++)
            adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
}
void floydWarshall(int adj[10][10],int vert) {
  int i, j, k;
  for (k = 0; k < vert; k++)
    {
        for (i = 0; i < vert; i++)
        {
            for (j = 0; j < vert; j++)
            {
                if ((adj[i][k] * adj[k][j] != 0) && (i != j))
                {
                    if ((adj[i][k] + adj[k][j] < adj[i][j]) || (adj[i][j] == 0))
                    {
                        adj[i][j] = adj[i][k] + adj[k][j];
                    }
                }
            }
        }
    }
}
void BellmanFord(int adj[][10], int V, int E,int src)
{
    int dis[V];
    for (int i = 0; i < V; i++)
    dis[i] = INT_MAX;
    dis[src] = 0;
    for (int i = 0; i < V - 1; i++) {
  
        for (int j = 0; j < E; j++) {
            if (dis[adj[j][0]] + adj[j][2] < dis[adj[j][1]])
                dis[adj[j][1]] =
                  dis[adj[j][0]] + adj[j][2];
        }
    }
    for (int i = 0; i < E; i++) {
        int x = adj[i][0];
        int y = adj[i][1];
        int weight = adj[i][2];
        if (dis[x] != INT_MAX &&
                   dis[x] + weight < dis[y])
            cout << "Graph contains negative"
                    " weight cycle"
                 << endl;
    }
}
int main() {
   int vert, edge, i, j, k, c,ch;
    double time_taken;
    clock_t start, end;
   cout << "Enter no of vertices: ";
   cin >> vert;
   cout << "Enter no of edges: ";
   cin >> edge;
   cout << "Enter the source,destination and edge Costs:\n";
   for (k = 1; k <= edge; k++) {
      cin >> i >> j >> c;
      adj[i][j] = cost[i][j] = c;
   }
   cout<<"enter 1.johnson\n 2.floyd warshall\n 3.Bellmanford: ";
   cin>>ch;
   switch(ch)
   {
       case 1:
           start=clock();
       johnson(adj,vert);
           end=clock();
           time_taken = double(end - start)/double(CLOCKS_PER_SEC);
           cout<<"time taken by johnson algorithm is: "<<time_taken<<setprecision(4)<<" sec"<<endl;
       break;
       case 2:
           start=clock();
       floydWarshall(adj,vert);
           end=clock();
           time_taken = double(end - start)/double(CLOCKS_PER_SEC);
           cout<<"time taken by floydwarshall algorithm is: "<<time_taken<<setprecision(4)<<" sec"<<endl;
       break;
       case 3:
           start=clock();
           BellmanFord(adj,vert, edge, 0);
           end=clock();
           time_taken = double(end - start)/double(CLOCKS_PER_SEC);
           cout<<"time taken by bellmanford algorithm is: "<<time_taken<<setprecision(4)<<" sec"<<endl;
           break;
   }
   cout << "Resultant adj matrix\n";
   for (i = 1; i <= vert; i++) {
      for (j = 1; j <= vert; j++) {
            if (adj[i][j] != INF)
               cout << adj[i][j] << " ";
      }
      cout << "\n";
   }
    return 0;
}
