// programa realizado em dupla por Gustavo Murai e Igor Murai

#include <iostream>
using namespace std;

struct Node {
    int valor;
    Node* prox;
};

struct Fila {
    Node* inicio;
    Node* fim;
};

void inicializarFila(Fila* f) {
    f->inicio = nullptr;
    f->fim = nullptr;
}

bool filaVazia(Fila* f) {
    return f->inicio == nullptr;
}

void enfileirar(Fila* f, int valor) {
    Node* novo = new Node();
    novo->valor = valor;
    novo->prox = nullptr;
    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

int desenfileirar(Fila* f) {
    if (filaVazia(f)) {
        return -1;
    }
    Node* temp = f->inicio;
    int valor = temp->valor;
    f->inicio = f->inicio->prox;
    delete temp;
    if (f->inicio == nullptr) {
        f->fim = nullptr;
    }
    return valor;
}

int contarElementos(Fila* f) {
    int count = 0;
    Node* atual = f->inicio;
    while (atual != nullptr) {
        count++;
        atual = atual->prox;
    }
    return count;
}

void listarFila(Fila* f) {
    Node* atual = f->inicio;
    while (atual != nullptr) {
        cout << atual->valor << " ";
        atual = atual->prox;
    }
    cout << endl;
}

struct Guiche {
    int id;
    Fila senhasAtendidas;
    Guiche* prox;
};

Guiche* listaGuiches = nullptr;

void adicionarGuiche(int id) {
    Guiche* novo = new Guiche();
    novo->id = id;
    inicializarFila(&novo->senhasAtendidas);
    novo->prox = listaGuiches;
    listaGuiches = novo;
}

Guiche* buscarGuiche(int id) {
    Guiche* atual = listaGuiches;
    while (atual != nullptr) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return nullptr;
}

int contarGuiches() {
    int count = 0;
    Guiche* atual = listaGuiches;
    while (atual != nullptr) {
        count++;
        atual = atual->prox;
    }
    return count;
}

int main() {
    Fila senhasGeradas;
    inicializarFila(&senhasGeradas);

    int senhaAtual = 0;
    int opcao;

    do {
        cout << "\n----------------------------\n";
        cout << "Senhas aguardando: " << contarElementos(&senhasGeradas) << "\n";
        cout << "Guiches abertos: " << contarGuiches() << "\n";
        cout << "----------------------------\n";
        cout << "0 - Sair\n";
        cout << "1 - Gerar senha\n";
        cout << "2 - Abrir guiche\n";
        cout << "3 - Realizar atendimento\n";
        cout << "4 - Listar senhas atendidas\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                senhaAtual++;
                enfileirar(&senhasGeradas, senhaAtual);
                cout << "Senha " << senhaAtual << " gerada.\n";
                break;

            case 2: {
                int id;
                cout << "Digite o ID do novo guiche: ";
                cin >> id;
                if (buscarGuiche(id)) {
                    cout << "Guiche ja existente.\n";
                } else {
                    adicionarGuiche(id);
                    cout << "Guiche " << id << " aberto.\n";
                }
                break;
            }

            case 3: {
                if (filaVazia(&senhasGeradas)) {
                    cout << "Nenhuma senha para atender.\n";
                    break;
                }
                int id;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                Guiche* g = buscarGuiche(id);
                if (!g) {
                    cout << "Guiche nao encontrado.\n";
                    break;
                }
                int senha = desenfileirar(&senhasGeradas);
                enfileirar(&g->senhasAtendidas, senha);
                cout << "Guiche " << id << " atendeu senha " << senha << ".\n";
                break;
            }

            case 4: {
                int id;
                cout << "Digite o ID do guiche: ";
                cin >> id;
                Guiche* g = buscarGuiche(id);
                if (!g) {
                    cout << "Guiche nao encontrado.\n";
                } else {
                    cout << "Senhas atendidas pelo guiche " << id << ": ";
                    listarFila(&g->senhasAtendidas);
                }
                break;
            }

            case 0:
                if (!filaVazia(&senhasGeradas)) {
                    cout << "Ainda ha senhas na fila. Atenda todas antes de sair.\n";
                    opcao = -1;
                } else {
                    // Somar todas as senhas atendidas
                    int totalAtendidas = 0;
                    Guiche* g = listaGuiches;
                    while (g != nullptr) {
                        totalAtendidas += contarElementos(&g->senhasAtendidas);
                        g = g->prox;
                    }
                    cout << "Encerrando programa...\n";
                    cout << "Total de senhas atendidas: " << totalAtendidas << "\n";
                }
                break;

            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    return 0;
}
