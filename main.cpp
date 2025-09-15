#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

const int N = 10;
const int M = 10;

int compterVoisins(bool Mat[N][M], int x, int y) {
    int total = 0;
    for (int i=-1;i<=1;i++)
        for (int j=-1;j<=1;j++)
            if (!(i==0 && j==0)) {
                int nx = x+i, ny = y+j;
                if(nx>=0 && nx<N && ny>=0 && ny<M)
                    total += Mat[nx][ny];
            }
    return total;
}

void afficher(bool Mat[N][M]) {
    cout << endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++)
            cout << (Mat[i][j] ? "O" : ".") << " ";
            cout << endl;
    }
}

int main() {
    bool Mat[N][M] = {};


    cout << "Entrez la matrice initiale (" << N << " x " << M << ")\n";
    cout << "(1 = vivant, 0 = mort)\n\n";

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            int val;
            cout << "Cellule (" << i << "," << j << ") : ";
            cin >> val;
            Mat[i][j] = (val == 1);
            system("cls");
            cout << "Matrice actuelle :" << endl;
            afficher(Mat);
        }
    }

    cout << "\nMatrice initiale terminee. Appuyez sur une touche pour lancer la simulation...";
    _getch();

    bool pause = false;


    while(true){
        system("cls");
        cout << "Touches: P=Pause/Resume, S=Stop, E=Effacer\n";
        afficher(Mat);


        if(_kbhit()){
            char c = _getch();
            if(c=='P' || c=='p') pause = !pause;
            if(c=='S' || c=='s') break;
            if(c=='E' || c=='e'){
                for(int i=0;i<N;i++)
                    for(int j=0;j<M;j++)
                        Mat[i][j]=false;
            }
        }

        if(!pause){
            bool nouvelle[N][M] = {};
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    int v = compterVoisins(Mat,i,j);
                    if(v==3) nouvelle[i][j]=true;
                    else if(v==2) nouvelle[i][j]=Mat[i][j];
                    else nouvelle[i][j]=false;
                }
            }


            for(int i=0;i<N;i++)
                for(int j=0;j<M;j++)
                    Mat[i][j]=nouvelle[i][j];
        }

        Sleep(500);
    }

    cout << "Simulation arretee." << endl;
}
