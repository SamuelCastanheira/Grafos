#include <iostream>
using namespace std;

#include <stdio.h>

class Grafo_MA 
{
    private:
        int n;
        int m;
        int  **M;

        void DFS_in (int *pre, int &cont, int pai, int v){
            cont=cont+1;
            pre[v]=cont;
            for (int w=0;w<n;w++){
                if (M[v][w]==1 && pre[w]==0){
                    DFS_in(pre,cont,v,w);
                }
            }
        }

        bool DFS_Ciclo (int *marcado, int pai, int v){
            marcado[v]=1;
            for (int w=0;w<n;w++){
                if (M[v][w]==1 && marcado[w]==0){
                    if (DFS_Ciclo(marcado,v,w)){
                        return true;
                    }
                }
                else if (M[v][w]==1 && w!= pai){
                    return true;
                    }
                }
            return false;
        }

        void DFS_Comp (int *compConexa, int &cont, int pai, int v){
            compConexa[v]=cont;
            for (int w=0;w<n;w++){
                if (M[v][w]==1 && compConexa[w]==0){
                    DFS_Comp(compConexa,cont,v,w);
                }
            }
        }

        void DFSII_in (int *pre, int *saida, int &contPre, int &contSaida, int pai, int v){
            contPre=contPre+1;
            pre[v]=contPre;
            for (int w=0;w<n;w++){
                if (M[v][w]==1 && pre[w]==0){
                    DFSII_in(pre,saida,contPre,contSaida,v,w);
                }
            }
            saida[v]=++contSaida;
        }
    
    public:
        void lerGrafo(){
            int u;
            int v;
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
                cout << "(u, v): ";
                cin >> u;
                cin >>v;
                M[u-1][v-1]=1;
                M[v-1][u-1]=1;
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

        int* DFS (){
            int cont = 0;
            int * pre;
            pre = (int*)(malloc(n*sizeof(int)));
            for (int i=0;i<n;i++){
                pre[i]=0;
            }
            
            for (int i=0;i<n;i++){
                if (pre[i]==0){
                    DFS_in(pre,cont,i,i);
                }
            }
            return pre;
            
        }

        void compConexas (){
            int *compConexa;
            int cont=0;
            
            compConexa = (int*)(malloc(n*sizeof(int)));
            for (int i=0;i<n;i++){
                compConexa[i]=0;
            }
            
            for (int i=0;i<n;i++){
                if (compConexa[i]==0){
                    cont+=1;
                    DFS_Comp(compConexa,cont,i,i);
                }
            }
            
            for (int i=1;i<cont+1;i++){
                cout << "Componente "  << i <<": ";
                for (int j=0;j<n;j++){
                    if (compConexa[j]==i){
                        cout<< (j +1)<< " ";
                    }
                }
                cout<<"\n";
            }
        }

        void EhConexo (){
            int cont = 0;
            int * pre;
            int componentes=0;
            
            pre = (int*)(malloc(n*sizeof(int)));
            for (int i=0;i<n;i++){
                pre[i]=0;
            }
            
            for (int i=0;i<n;i++){
                if (pre[i]==0){
                    componentes += 1;
                    DFS_in(pre,cont,i,i);
                }
            }
            
            if (componentes==1){
                cout<<"Conexo\n";
            }
            else {
                cout<<"Desconexo\n";
            }
            
        }

        void EhCiclico(){
            int * marcado;
            marcado = (int*)malloc(n*sizeof(int));
            bool temCiclo = false;
            for (int i=0;i<n;i++){
                marcado[i]=0;
            }

            for (int i=0;i<n;i++){
                if (marcado[i]==0){
                    temCiclo = temCiclo || DFS_Ciclo(marcado,i,i);
                }
            }

            if (temCiclo){
                cout <<"Ciclico\n";
            }
            else {
                cout <<"Aciclico\n";
            }

        }

        int* DFSII (){
            int contPre= 0;
            int contSaida=0;
            int * pre;
            int * saida;

            pre = (int*)(malloc(n*sizeof(int)));
            for (int i=0;i<n;i++){
                pre[i]=0;
            }
            
            saida = (int*)(malloc(n*sizeof(int)));
            for (int i=0;i<n;i++){
                saida[i]=0;
            }

            for (int i=0;i<n;i++){
                if (pre[i]==0){
                    DFSII_in(pre,saida,contPre,contSaida,i,i);
                }
            }

            for (int i=0;i<n;i++){
                cout << pre[i] <<" ";
            }
            cout <<"\n";

            for (int i=0;i<n;i++){
                cout << saida[i] <<" ";
            }
            cout <<"\n";
            return pre;
            
        }


        
};

int main (void){
    Grafo_MA G;
    G.lerGrafo();
    G.imprime();
    G.DFSII();


}