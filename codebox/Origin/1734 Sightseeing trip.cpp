//floyd与Dijkstra区别，Dijkstra是从一点出发，到各点的最短距离;floyd是求出点到点之间最短距离，
//对已存在的路径通过添加一个点去松弛，看是否能得到更短的路径
//最小环问题 floyd变种
#include<iostream>
using namespace std;
const int N = 101;
const int INF = 0x7ffffff;
int mat[N][N],dist[N][N],pre[N][N],path[N],n;
int main(){
#ifdef _DEBUG
	freopen("data","r",stdin);
#endif
	int i,j,k,m,a,b,c;
	int num;
	while(~scanf("%d%d",&n,&m)){
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++){
				mat[i][j]=dist[i][j]=INF;
				pre[i][j]=i;
			}
		}
		while(m--){
			scanf("%d%d%d",&a,&b,&c);
			mat[a][b]=mat[b][a]=dist[a][b]=dist[b][a]=min(mat[a][b],c);
		}
		int min=INF;
		for(k=1;k<=n;k++){//最短路径外一点将最短路首尾链接,那么就得到一个最小环
			for(i=1;i<k;i++){//不能松弛成(1,n),(i,k)之间的最短路,(k,j)之间的最短路可能有重合的部分
				for(j=i+1;j<k;j++){
					//求最小环不能用两点间最短路松弛,因为(i,k)之间的最短路,(k,j)之间的最短路可能有重合的部分
					//所以mat[][]其实是不更新的,这里和单纯的floyd最短路不一样
					//dist[i][j]保存的是 i 到 j 的最短路权值和
					int tmp=dist[i][j]+mat[i][k]+mat[k][j];//这里 k 分别和 i 还有 j 在mat中直接相连
					if(tmp<min){
						min=tmp;
						num=0;
						int p=j;
						while(p!=i){//回溯，寻找父节点法
							path[num++]=p;
							p=pre[i][p];//pre[i][j]表示 i 到 j 最短路径上 j 前面的一个点
						}
						path[num++]=i;
						path[num++]=k;
					}
				}
			}
			//更新距离和传统floyd一样
			for(i=1;i<=n;i++){
				for(j=1;j<=n;j++){
					if(dist[i][j]>dist[i][k]+dist[k][j]){
						dist[i][j]=dist[i][k]+dist[k][j];//dist[][]保存两点间最短距离
						pre[i][j]=pre[k][j];//则j的前一个点是K，寻找父节点法
					}
				}
			}
		}
		if(min==INF)puts("No solution.");
		else{
			printf("%d",path[0]);
			for(i=1;i<num;i++)
				printf(" %d",path[i]);
			printf("\n");
		}
	}
#ifdef _DEBUG
	freopen("CON","r",stdin);
	system("pause");
#endif
	return 0;
}
