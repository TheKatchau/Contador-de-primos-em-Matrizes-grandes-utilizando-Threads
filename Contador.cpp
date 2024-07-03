#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <locale.h>
//#include <thread>
//#include <mutex>
#include <process.h>
#include <windows.h>
#include <iomanip>


using namespace std;

// mutex para proteger a variável global de contagem

//mutex mtx;

//Sem utilização das biblios Thread e mutex
HANDLE hMutex_01;
HANDLE hMutex_02;

//percorre o vetor de submatriz
int aux;
// Função que gera uma matriz aleatória com as dimensões informadas
void gerarMatriz(int linhas, int colunas);

//matriz
int** matriz = (int**)malloc(sizeof(int**));
vector<HANDLE>hThread;

//vetor de submatrizes
vector<vector<int>> submatrizes;

// variável contador
int contador;
double tempo_total = 0;
// Função que armazena as submatrizes em um vetor
void listaSubmatrizes(int linhas, int colunas, int sublinhas, int subcolunas);

bool meuPrimo(int num);

void contarPrimos(int thread_id, int nThreads);

void contarPrimosThreads(int linhas, int colunas, int sublinhas, int subcolunas, int nThreads);

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    int opt = 0;
    int linhas = 0, colunas = 0, semente = NULL, sublinhas = 0, subcolunas = 0, nThreads = 0, matrizcriada = 0;
    time_t start, end;
    while (opt != 8)
    {
        cout << "* Bem vindo a selva! *\n\n Escolha uma das opções abaixo: \n\n 1 - Definir o tamanho da matriz. \n 2 - Definir semente para o gerador de números aleatórios \n 3 - Preencher a matriz com números aleatórios \n 4 - Definir o tamanho das submatrizes \n 5 - Definir o número de Threads \n 6 - Executar \n 7 - Visualizar o tempo de execução e quantidade de números primos \n 8 - Encerrar:\n-------------------------------------------------\n";
        cin >> opt;
        if (cin.fail())
        {
            cout << "\n\nERRO - Tu não entrou um inteiro meu bom!\n\n";
            cin.clear();
            cin.ignore(256, '\n');
        }
        switch (opt)
        {
        case 1:
            system("cls");
            linhas = colunas = 0;
            while (linhas <= 0)
            {
                cout << "Digite a quantidade de linhas da matriz (um número maior que 0):\n";
                cin >> linhas;
                cout << "\n\n\n";
                if (linhas <= 0)
                    cout << "* Valor inválido! ***\n\n\n";
            }
            while (colunas <= 0)
            {
                cout << "Digite a quantidade de colunas da matriz:\n";
                cin >> colunas;
                cout << "\n\n\n";
                if (colunas <= 0)
                    cout << "* Valor inválido! ***\n\n\n";
            }
            matrizcriada = 0;
            system("cls");
            break;

        case 2:
            system("cls");
            cout << "Entre com a semente a ser utilizada para gerar os números aleatórios: ";
            cin >> semente;
            matrizcriada = 0;
            system("cls");
            break;

        case 3:
            system("cls");
            if (linhas > 0 and colunas > 0)
            {
                if (semente != NULL)
                {
                    srand(semente); // Seed para números aleatórios
                    gerarMatriz(linhas, colunas);
                    matrizcriada = 1;
                    cout << "Matriz preenchida!!! \n\n";
                }
                else
                    cout << "Semente não definida, Realize o passo 2 e tente novamente!\n\n";
            }
            else
                cout << "Linhas e colunas não definidas, Realize o passo 1 e tente novamente!\n\n";

            system("pause");
            system("cls");
            break;

        case 4:
            system("cls");
            sublinhas = subcolunas = 0;
            while (sublinhas <= 0)
            {
                cout << "Digite a quantidade de linhas da matriz (um número maior que 0):\n";
                cin >> sublinhas;
                cout << "\n\n\n";
                if (sublinhas <= 0)
                    cout << "* Valor inválido! ***\n\n\n";
            }
            while (subcolunas <= 0)
            {
                cout << "Digite a quantidade de colunas da matriz:\n";
                cin >> subcolunas;
                cout << "\n\n\n";
                if (subcolunas <= 0)
                    cout << "* Valor inválido! ***\n\n\n";
            }
            system("cls");
            break;

        case 5:
            system("cls");
            cout << "Digite a quantidade de threads: ";
            cin >> nThreads;
            system("cls");
            break;

        case 6:
            system("cls");
            if (linhas > 0 and colunas > 0)
            {
                if (semente != NULL)
                {
                    if (matrizcriada == 1)
                    {
                        if (sublinhas > 0 and subcolunas > 0)
                        {
                            if (nThreads != 0)
                            {
                                /*/cout << "Matriz gerada: " << endl;
                                for (int i = 0; i < linhas; i++)
                                {
                                    for (int j = 0; j < colunas; j++)
                                    {
                                        cout << matriz[i][j] << " ";
                                    }
                                    cout << endl;
                                }*/
                                if (!submatrizes.empty())
                                    submatrizes.clear();
                                tempo_total = 0;
                                aux = 0;
                                contador = 0;
                                contarPrimosThreads(linhas, colunas, sublinhas, subcolunas, nThreads);
                            }
                            else
                                cout << "Quantidade de Threads não definido, Realize o passo 5 e tente novamente!\n\n";
                        }
                        else
                            cout << "Tamanho das submatrizes não definido, Realize o passo 4 e tente novamente!\n\n";
                    }
                    else
                        cout << "Matriz não iniciada, Realize o passo 3 e tente novamente!\n\n";

                }
                else
                    cout << "Semente não definida, Realize o passo 2 e tente novamente!\n\n";
            }
            else
                cout << "Tamanho da matriz não definido, Realize o passo 1 e tente novamente!\n\n";
            system("pause");
            system("cls");
            break;

        case 7:
            system("cls");
            if (contador != 0)
            {
                cout << "Tempo de execução: " << fixed << tempo_total << setprecision(5) << " segs";
                cout << "\n\nQuantidade de Números primos: " << contador << "\n\n";
            }
            else
                cout << "Algoritmo ainda não executado, tente novamente após executar essa merda! \n\n";
            system("pause");
            system("cls");

            break;

        case 8:
            EXIT_SUCCESS;
            break;

        default:
            system("cls");
            cout << "Opção inválida, tente de Novo!\n";
            system("pause");
            system("cls");
            break;
        }


    }


    // Liberando a memória alocada para a matriz
    if (matriz != nullptr)
    {
        for (int i = 0; i < linhas; i++)
        {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

    CloseHandle(hMutex_01);

    CloseHandle(hMutex_02);
}


void gerarMatriz(int linhas, int colunas) {
    matriz = new int* [linhas];
    for (int i = 0; i < linhas; i++) {
        matriz[i] = new int[colunas];
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % 100000000;
        }
    }
}

void listaSubmatrizes(int linhas, int colunas, int sublinhas, int subcolunas)
{
    // dividir a matriz em submatrizes de tamanho divisível
    for (int i = 0; i <= linhas - sublinhas; i += sublinhas)
    {
        for (int j = 0; j <= colunas - subcolunas; j += subcolunas)
        {
            vector<int> submatriz;
            submatriz.push_back(i);
            submatriz.push_back(j);
            submatriz.push_back(i + sublinhas - 1);
            submatriz.push_back(j + subcolunas - 1);
            submatrizes.push_back(submatriz);
        }
    }

    // verificar se há linhas restantes e criar uma submatriz extra para elas
    if (linhas % sublinhas != 0)
    {
        int i = linhas - (linhas % sublinhas);
        vector<int> submatriz;
        submatriz.push_back(i);
        submatriz.push_back(0);
        submatriz.push_back(linhas - 1);
        submatriz.push_back(colunas - 1);
        submatrizes.push_back(submatriz);
    }

    // verificar se há colunas restantes e criar uma submatriz extra para elas
    if (colunas % subcolunas != 0)
    {
        int j = colunas - (colunas % subcolunas);

        vector<int> submatriz;
        submatriz.push_back(0);
        submatriz.push_back(j);
        submatriz.push_back(linhas - (linhas % sublinhas) - 1);
        submatriz.push_back(colunas - 1);
        submatrizes.push_back(submatriz);
    }
    /*cout << "\n\n\nSubmatrizes geradas: " << endl;
    for (int i = 0; i < submatrizes.size(); i++)
    {
        cout << "[" << submatrizes[i][0] << ", " << submatrizes[i][1] << "] - [" << submatrizes[i][2] << ", " << submatrizes[i][3] << "]" << endl;
    }*/
}

bool meuPrimo(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i <= num / 2; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

void contarPrimos(int thread_id, int nThreads)
{
    int local_count = 0;
    hMutex_01 = CreateMutex(NULL, FALSE, NULL);
    hMutex_02 = CreateMutex(NULL, FALSE, NULL);
    while (true)
    {
        // Proteger acesso ao índice do vetor de submatrizes
        //mtx.lock();
        WaitForSingleObject(hMutex_01, INFINITE);
        if (aux >= submatrizes.size())
        {
            //mtx.unlock();
            ReleaseMutex(hMutex_01);
            break;
        }
        int i_inicio = submatrizes[aux][0];
        int j_inicio = submatrizes[aux][1];
        int i_fim = submatrizes[aux][2];
        int j_fim = submatrizes[aux][3];
        ++aux;
        //mtx.unlock();
        ReleaseMutex(hMutex_01);

        for (int x = i_inicio; x <= i_fim; ++x)
        {
            for (int y = j_inicio; y <= j_fim; ++y)
            {
                int num = matriz[x][y];
                if (meuPrimo(num))
                {
                    ++local_count;
                }
            }
        }
    }
    // Proteger acesso ao contador global
    //mtx.lock();
    WaitForSingleObject(hMutex_02, INFINITE);
    contador += local_count;
    //mtx.unlock();
    ReleaseMutex(hMutex_02);
}

void contarPrimosThreads(int linhas, int colunas, int sublinhas, int subcolunas, int nThreads)
{
    int i;
    // criar lista de submatrizes
    listaSubmatrizes(linhas, colunas, sublinhas, subcolunas);
    // inicializar contador
    int contador = 0;

    // CRIAR VETOR DE THREAD
    // 
    // 
    //vector<thread> threads;


    // criar threads e executar contarPrimos em cada submatriz

    for (i = 0; i < nThreads ; ++i)
    {
        //threads.emplace_back(contarPrimos, i, nThreads);
        DWORD threadID; // variável para armazenar o identificador da thread
        HANDLE Thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&contarPrimos, &i, CREATE_SUSPENDED, &threadID);
        hThread.push_back(Thread);
    }

    clock_t begin = clock();
    for (i = 0; i < nThreads && i < submatrizes.size(); i++)
    {
        ResumeThread(hThread[i]);
    }


    // aguardar todas as threads terminarem

    WaitForMultipleObjects(hThread.size(), &hThread[0], TRUE, INFINITE);

    clock_t end = clock();
    tempo_total += (double)(end - begin) / CLOCKS_PER_SEC;
    hThread.clear();
}
