#include <stdio.h>
#include <iostream>
#include <climits>
using namespace std;

void imprimeM(int ** M, int n) {
   for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << M[i][j] <<" ";
        }
        cout << "\n";
    }
    cout <<"\n";
}

void imprimeV(int * M, int n) {
   for (int i = 0; i < n; i++) {
        cout << M[i]<<" ";
    }
    cout <<"\n";
}

class Grafo_MA 
{
    private:
        
        int n;
        int m;
        int  **M;

    public:
        
        void lerGrafo(){
            int u;
            int v;
            int peso;
            bool digrafo = false;

            cout << "Digrafo (1/0): ";
            cin >> digrafo; 
            cout << "Numero de Vertices: ";
            cin >> n;
            cout << "Numero de Arestas: ";
            cin >> m;

            M = (int**) malloc(n*sizeof(int*));

            for (int i=0;i<n;i++){
                M[i] = (int*) malloc (n*sizeof(int));
            }
            
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    M[i][j]=0;
                }
            }

            for (int i=0;i<m;i++){
                cout << "(u, v) (p): ";
                cin >> u;
                cin >>v;
                cin >> peso;
                M[u-1][v-1]=peso;
                if (!digrafo){
                M[v-1][u-1]=peso;
                }
            }
        }

        int getn() {
            return n;
        }

        int getm(){
            return m;
        }

        void imprime() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", M[i][j]);
                }
                printf("\n");
            }
        }

        int* Dijkstra(int v){
            v=v-1;
            int * distancia = (int*)malloc((n+1)*sizeof(int));
            bool * marcado = (bool*)malloc((n+1)*sizeof(bool));
            int w;
            for (int i=0;i<n+1;i++){
                distancia[i] = INT_MAX;
                marcado[i] = false;
                
            }
            distancia[v]=0;
            for (int i=0;i<n;i++){
                w = n;
                for (int j=0;j<n+1;j++){
                    if (!marcado[j] && (distancia[j] <= distancia[w])){
                        w=j;
                    }
                }
                marcado[w]=true;
            
                for (int z=0;z<n;z++){
                    if (M[w][z] > 0 && !marcado[z]){
                        distancia[z]=min(distancia[z],distancia[w]+M[w][z]);
                    }
                }
            }
            return distancia;
        }

        int* Dijkstra(int v, int * vcm){
            v=v-1;
            int * distancia = (int*)malloc((n+1)*sizeof(int));
            bool * marcado = (bool*)malloc((n+1)*sizeof(bool));
            int w;
            for (int i=0;i<n+1;i++){
                distancia[i] = INT_MAX;
                marcado[i] = false;
                vcm[i]=0;
            }
            distancia[v]=0;
            for (int i=0;i<n;i++){
                w = n;
                for (int j=0;j<n+1;j++){
                    if (!marcado[j] && (distancia[j] <= distancia[w])){
                        w=j;
                    }
                }
                marcado[w]=true;
            
                for (int z=0;z<n;z++){
                    if (M[w][z] > 0 && !marcado[z]){
                        distancia[z]=min(distancia[z],distancia[w]+M[w][z]);
                        vcm[z] = w;
                    }
                }
            }
            return distancia;
        }

        void caminhoMinimo(int v, int t){
            int * vcm = (int*)malloc(n*sizeof(int));
            int * distancia = Dijkstra(v,vcm);
            int * caminho = (int*)malloc(n*sizeof(int));
            for (int i=0;i<n+1;i++){
                caminho[i] = 0;
                
            }
            int i=0;
            int vertice = t-1;
            v=v-1;
            caminho[i++]=vertice +1;
            while (vertice!=v){
                caminho[i++]=vcm[vertice]+1;
                vertice = vcm[vertice];
            }
            cout << "Caminho minimo: " ;
            for (int i=0;i<n;i++){
                if (caminho[i]!=0){
                cout << caminho[i] << " ";
                }
            }
            cout << "\n";
        }
        
        int ** floyd(){
            int ** distancia;
            distancia = (int**)malloc(n*sizeof(int*));
            for (int i=0;i<n;i++){
                distancia[i]= (int*)malloc(n*sizeof(int));
            }

            for(int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if (M[i][j]==0 && i!=j){
                    distancia[i][j]=300000;
                    }
                   else {
                    distancia[i][j]=M[i][j];
                   }
                }
            }

            for (int k=0;k<n;k++){
                for (int i=0;i<n;i++){
                    if (distancia[i][k] != 300000){
                        for (int j=0;j<n;j++){
                            distancia[i][j]= min(distancia[i][j],distancia[i][k] + distancia[k][j]);
                        }
                    }
                }
                cout << "k: "<<k <<"\n";
                //imprimeM(distancia,n);
            }

            return distancia;
        }

        int ** floyd(int ** vcm){
            int ** distancia;
            
            distancia = (int**)malloc(n*sizeof(int*));
            
            for (int i=0;i<n;i++){
                distancia[i]= (int*)malloc(n*sizeof(int));
            }

            for(int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if (M[i][j]==0 && i!=j){
                    distancia[i][j]=300000;
                    }
                   else {
                    distancia[i][j]=M[i][j];
                   }
                   vcm[i][j]=i;
                }
            }

            for (int k=0;k<n;k++){
                for (int i=0;i<n;i++){
                    if (distancia[i][k] != 300000){
                        for (int j=0;j<n;j++){
                            distancia[i][j]= min(distancia[i][j],distancia[i][k] + distancia[k][j]);
                            vcm[i][j]=vcm[k][j];
                        }
                    }
                }
                cout << "k: "<<k <<"\n";
                //imprimeM(distancia,n);
            }

            return distancia;
        }

/*     int * caminhoMinimoFloyd(int u, int v){
            int ** vcm;
            int * caminho = (int*)malloc(n*sizeof(int)); 
            vcm = (int**)malloc(n*sizeof(int*));          
            for (int i=0;i<n;i++){
                vcm[i]= (int*)malloc(n*sizeof(int));
            }
            int ** distancia = floyd(vcm);

            if (M[u][v]==0 || M[u][v] > distancia[u][v]){
                int k = vcm[u][v];
                cmf(u,k);

            }
        }*/

        int * bellmanFord(int v){
            int * distancia = (int*)malloc(n*sizeof(int));
            v=v-1;
            for (int i=0;i<n;i++){
                distancia[i]= 300000;
            }
            distancia[v]=0;
            for (int k=0;k<n-1;k++){
                for (int i=0;i<n;i++){
                    for (int j=0;j<n;j++){
                        if (M[i][j]!=0 && (distancia[j] > (distancia[i]+M[i][j]))){
                            distancia[j] = distancia[i] + M[i][j];
                        }
                    }
                }    
            }
            return distancia;
        }

        int * bellmanFord(int v, int * vcm){
            int * distancia = (int*)malloc(n*sizeof(int));
            for (int i=0;i<n;i++){
                distancia[i]= 300000;
            }
            distancia[v]=0;
            for (int k=0;k<n-1;k++){
                for (int i=0;i<n;i++){
                    for (int j=0;j<n;j++){
                        if (M[i][j]!=0 && (distancia[j] > (distancia[i]+M[i][j]))){
                            distancia[j] = distancia[i] + M[i][j];
                            vcm[j]=i;
                        }
                    }
                }    
            }
            return distancia;
        }

        bool negCiclo(int v){
            int * distancia = (int*)malloc(n*sizeof(int));
            v=v-1;
            for (int i=0;i<n;i++){
                distancia[i]= 300000;
            }
            distancia[v]=0;
            for (int k=0;k<n-1;k++){
                for (int i=0;i<n;i++){
                    for (int j=0;j<n;j++){
                        if (M[i][j]!=0 && (distancia[j] > (distancia[i]+M[i][j]))){
                            distancia[j] = distancia[i] + M[i][j];
                        }
                    }
                }    
            }
            for (int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if (M[i][j]!=0 && (distancia[j] > (distancia[i]+M[i][j]))){
                        return true;
                    }
                }
            }
            return false;    
        }
};

int main(void){
    Grafo_MA G;
    G.lerGrafo();
    imprimeV(G.bellmanFord(1),G.getn());
    if (G.negCiclo(1)){
        cout << "Tem ciclo neg\n";
    } else {
        cout << "Nao tem ciclo neg\n";
    }
    
}