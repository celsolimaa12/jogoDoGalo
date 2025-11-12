#include <iostream>  
#include <cstdlib>    
#include <ctime>      
using namespace std;

// Códigos de cor ANSI para mostrar cores no terminal
const string VERMELHO = "\033[31m";  
const string VERDE = "\033[32m";     
const string AZUL = "\033[34m";      
const string RESET = "\033[0m";      


int rolarDados() {
    return rand() % 6 + 1; 
}


void mostrarTabuleiro(int pos[], int numJogadores) {
    cout << "Tabuleiro atual: " << endl;

    
    for (int i = 1; i <= 30; i++) {
        bool casaEspecial = false; // Marca se a casa é especial

        
        if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25) {
            casaEspecial = true;
            cout << "[" << i << "(" << VERMELHO << "E" << RESET << ")] "; 
        } else {
            bool jogadorNaCasa = false; 

        
            for (int j = 0; j < numJogadores; j++) {
                if (pos[j] == i) {
                    jogadorNaCasa = true;
                  
                    if (j == 0)
                        cout << "[" << VERDE << "P" << j + 1 << RESET << "] ";
                
                    else
                        cout << "[" << AZUL << "P" << j + 1 << RESET << "] ";
                    break;
                }
            }

            if (!jogadorNaCasa)
                cout << "[" << i << "] ";
        }

       
        if (i % 10 == 0)
            cout << endl;
    }
    cout << endl;
}


void aplicarCasaEspecial(int &pos, int &perdeVez, int &jogaNovamente, bool &espera) {
    if (pos == 5) { 
        cout << "Perde a vez! Próxima jogada será pulada." << endl;
        perdeVez = 1;
    } else if (pos == 10) { 
        cout << "Avança 3 casas!" << endl;
        pos += 3;
    } else if (pos == 15) { 
        cout << "Retorna 3 casas!" << endl;
        pos -= 3;
    } else if (pos == 20) { 
        cout << "Joga novamente!" << endl;
        jogaNovamente = 1;
    } else if (pos == 25) { 
        cout << "Esperar pela passagem dos outros jogadores!" << endl;
        espera = true;
    }
}

int main() {
    system("clear");  

    srand(time(0));    

    const int numJogadores = 2;      
    int pos[numJogadores] = {1, 1};    // Ambos começam na casa 1
    int perdeuVez[numJogadores] = {0, 0};   
    int jogaNovamente[numJogadores] = {0, 0}; 
    bool espera[numJogadores] = {false, false}; 

    int vez = 0;  
    
  
    while (true) {
     
        mostrarTabuleiro(pos, numJogadores);

      
        if (espera[vez]) {
            cout << "Jogador " << vez + 1 << " está esperando pela passagem dos outros jogadores..." << endl;
            espera[vez] = false;
        }

        if (perdeuVez[vez]) {
            cout << "Jogador " << vez + 1 << " perdeu a vez." << endl;
            perdeuVez[vez] = 0;
            vez = (vez + 1) % numJogadores; 
            continue; 
        }

       
        cout << "Jogador " << vez + 1 << ", pressione Enter para rolar o dado...";
        cin.ignore();  
        cin.get();     
        int dado = rolarDados();
        cout << "Jogador " << vez + 1 << " rolou o dado e tirou: " << dado << endl;

       
        pos[vez] += dado;

        
        if (pos[vez] > 30)
            pos[vez] = 30;

       
        aplicarCasaEspecial(pos[vez], perdeuVez[vez], jogaNovamente[vez], espera[vez]);

        
        if (jogaNovamente[vez]) {
            cout << "Jogador " << vez + 1 << " joga novamente!" << endl;
            jogaNovamente[vez] = 0;
        } 
        
        else {
            vez = (vez + 1) % numJogadores;
        }

       
        for (int i = 0; i < numJogadores; i++) {
            if (pos[i] == 30) {
                cout << "Jogador " << i + 1 << " venceu o jogo!" << endl;
                return 0; 
            }
        }
    }

    return 0;
}