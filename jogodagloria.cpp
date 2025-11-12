#include <iostream>   // Entrada e saída (cout, cin)
#include <cstdlib>    // Funções rand(), srand(), system()
#include <ctime>      // Função time() para gerar números aleatórios diferentes
using namespace std;

// Códigos de cor ANSI para mostrar cores no terminal
const string VERMELHO = "\033[31m";  // Cor vermelha (usada para casas especiais)
const string VERDE = "\033[32m";     // Cor verde (para o jogador 1)
const string AZUL = "\033[34m";      // Cor azul (para o jogador 2)
const string RESET = "\033[0m";      // Reset das cores (volta ao normal)

// Função que gera um número aleatório de 1 a 6 (simula um dado)
int rolarDados() {
    return rand() % 6 + 1; 
}

// Função que desenha o tabuleiro na tela
void mostrarTabuleiro(int pos[], int numJogadores) {
    cout << "Tabuleiro atual: " << endl;

    // O tabuleiro tem 30 casas (de 1 a 30)
    for (int i = 1; i <= 30; i++) {
        bool casaEspecial = false; // Marca se a casa é especial

        // Casas especiais: 5, 10, 15, 20 e 25
        if (i == 5 || i == 10 || i == 15 || i == 20 || i == 25) {
            casaEspecial = true;
            cout << "[" << i << "(" << VERMELHO << "E" << RESET << ")] "; // Mostra o número e um "E" vermelho
        } else {
            bool jogadorNaCasa = false; // Marca se há um jogador nesta casa

            // Verifica se algum jogador está nessa casa
            for (int j = 0; j < numJogadores; j++) {
                if (pos[j] == i) {
                    jogadorNaCasa = true;
                    // Se for o jogador 1, mostra em verde
                    if (j == 0)
                        cout << "[" << VERDE << "P" << j + 1 << RESET << "] ";
                    // Se for o jogador 2, mostra em azul
                    else
                        cout << "[" << AZUL << "P" << j + 1 << RESET << "] ";
                    break;
                }
            }

            // Se não houver jogador, mostra só o número da casa
            if (!jogadorNaCasa)
                cout << "[" << i << "] ";
        }

        // Quebra a linha a cada 10 casas (para o tabuleiro ficar organizado)
        if (i % 10 == 0)
            cout << endl;
    }
    cout << endl;
}

// Função que aplica os efeitos das casas especiais
void aplicarCasaEspecial(int &pos, int &perdeVez, int &jogaNovamente, bool &espera) {
    if (pos == 5) { // Casa 5 → perde a próxima vez
        cout << "Perde a vez! Próxima jogada será pulada." << endl;
        perdeVez = 1;
    } else if (pos == 10) { // Casa 10 → avança 3 casas
        cout << "Avança 3 casas!" << endl;
        pos += 3;
    } else if (pos == 15) { // Casa 15 → volta 3 casas
        cout << "Retorna 3 casas!" << endl;
        pos -= 3;
    } else if (pos == 20) { // Casa 20 → joga novamente
        cout << "Joga novamente!" << endl;
        jogaNovamente = 1;
    } else if (pos == 25) { // Casa 25 → deve esperar uma rodada
        cout << "Esperar pela passagem dos outros jogadores!" << endl;
        espera = true;
    }
}

int main() {
    system("clear");   // Limpa o terminal (no Linux ou Mac)

    srand(time(0));    // Garante que os números aleatórios mudem a cada execução

    const int numJogadores = 2;        // Jogo com 2 jogadores
    int pos[numJogadores] = {1, 1};    // Ambos começam na casa 1
    int perdeuVez[numJogadores] = {0, 0};   // Controla se o jogador perdeu a vez
    int jogaNovamente[numJogadores] = {0, 0}; // Controla se o jogador vai jogar de novo
    bool espera[numJogadores] = {false, false}; // Controla se o jogador deve esperar

    int vez = 0;  // Começa com o jogador 1 (índice 0)
    
    // Loop principal do jogo (só termina quando alguém ganha)
    while (true) {
        // Mostra o tabuleiro
        mostrarTabuleiro(pos, numJogadores);

        // Se o jogador estiver esperando, mostra mensagem e limpa o estado de espera
        if (espera[vez]) {
            cout << "Jogador " << vez + 1 << " está esperando pela passagem dos outros jogadores..." << endl;
            espera[vez] = false;
        }

        // Se o jogador perdeu a vez, pula sua rodada
        if (perdeuVez[vez]) {
            cout << "Jogador " << vez + 1 << " perdeu a vez." << endl;
            perdeuVez[vez] = 0;
            vez = (vez + 1) % numJogadores; // Passa a vez ao próximo jogador
            continue; // Volta ao início do loop
        }

        // Espera o jogador pressionar Enter para rolar o dado
        cout << "Jogador " << vez + 1 << ", pressione Enter para rolar o dado...";
        cin.ignore();  // Ignora entrada anterior
        cin.get();     // Espera Enter

        // Rola o dado
        int dado = rolarDados();
        cout << "Jogador " << vez + 1 << " rolou o dado e tirou: " << dado << endl;

        // Move o jogador conforme o resultado do dado
        pos[vez] += dado;

        // Se passar da casa 30, para na casa 30
        if (pos[vez] > 30)
            pos[vez] = 30;

        // Aplica o efeito da casa onde caiu
        aplicarCasaEspecial(pos[vez], perdeuVez[vez], jogaNovamente[vez], espera[vez]);

        // Se o jogador ganhou o direito de jogar novamente
        if (jogaNovamente[vez]) {
            cout << "Jogador " << vez + 1 << " joga novamente!" << endl;
            jogaNovamente[vez] = 0;
        } 
        // Caso contrário, passa a vez para o outro jogador
        else {
            vez = (vez + 1) % numJogadores;
        }

        // Verifica se algum jogador chegou à casa 30
        for (int i = 0; i < numJogadores; i++) {
            if (pos[i] == 30) {
                cout << "Jogador " << i + 1 << " venceu o jogo!" << endl;
                return 0; // Encerra o jogo
            }
        }
    }

    return 0;
}