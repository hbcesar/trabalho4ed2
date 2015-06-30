//Estrutura job que contém numero do jobs, o seu tempo de processamento, sua deadline a multa
struct job {
	int id;
	int tproc;
	int deadline;
	int multa;
};

typedef struct job Job;

//Estrutura permuta que contém vetores dos jobs posicionaos e nao posicionados, seu lowerbound e upperbound
//quantidade de tempo decorrido até o momento, quantidade de jobs ja posicionaod e nao posicionados e ponteiro para
//proxima estrutura
struct permuta {
	Job** a_pos;
	Job** posicionados;
	int lowerbound;
	int upperbound;
	int tempoDecorrido;
	int qtdePosicionados;
	int qtdeNaoPosicionados;
	struct permuta* proximo;
};

//Estrutura lista de permutas que contem o tamanho da lista, ponteiro para o primeiro e o ultimo elemento da lista.
typedef struct permuta Permuta;

struct lista{
	Permuta* primeiro;
	Permuta* ultimo;
	int tamanho;
};

typedef struct lista Lista;

// Funcao que inicializa um job
// Input: Numero do job, seu tempo de processamento a deadline a multa
// Output: Ponteiro para estrutura job
// Pré-condição: Entradas nao sao nulas
// Pós condição: Estrutra job é inicializada
Job* inicializarJob(int id, int tproc, int deadline, int multa);

// Funcao que inicializa uma permuta 
// Input: Número de jobs de entrada
// Output: Estrutura permuta
// Pré-condição: Numero de jobs é inteiro positivo
// Pós condição: Estrutura permuta é inicializada
Permuta* inicializaPermuta(int n);

// Funcao que aloca uma lista
// Input: Nenhum
// Output: Ponteiro para a lista
// Pré-condição: Nenhum
// Pós condição: Lista é alocada
Lista* alocaLista();

// Funcao que inicializa uma lista
// Input: Lista de jobs e número de jobs
// Output: Ponteiro para a lista de jobs
// Pré-condição: Lista está alocada
// Pós condição: Lista é inicializada
Lista* inicializaLista(Job** entrada, int n);
Permuta* gerarRaiz(Job** entrada, int n);

// Funcao que cria um filho de uma estrutura permuta
// Input: A permuta pai, o numero de jobs e índice do job que sairá do vetor de não posicionados e irá para o lindo vetor de posicionados
// Output: Estrutura permuta filho
// Pré-condição: Estrutura permuta pai já estpa alocada, numero de jobs é inteiro positivo
// Pós condição: Filho da permuta é criado e inicializado
Permuta* criarFilho(Permuta* p, int n, int k);

// Funcao que insere uma permuta na lista de permutas ordenada pelo upperbound
// Input: Lista de permutas e permuta a ser inserida
// Output: Ponteiro para o inicio da lista
// Pré-condição: Permuta e lista não são nulas e já estão alocadas
// Pós condição: Permuta é inserida na lista no lugar correto
Lista* inserir(Lista* lista, Permuta* p);

// Funcao que remove o ultimo elemento da lista de permutacoes
// Input: A lista de permutacoes
// Output: Nenhum
// Pré-condição: Lista não é nula
// Pós condição: Ultimo elemento da lista é removido corretamente
void removerUltimo(Lista* lista);

// Funcao que retorna inteiro se a permuta é uma folha ou não
// Input: Estrutura permuta
// Output: 1 para folha ser permuta 0 para caso ela não seja
// Pré-condição: Permuta não é nula
// Pós condição: Inteiro correspondente é retornado corretamente
int eFolha(Permuta* p);

// Funcao que imprime os jobs do arquivo de entrada
// Input: O arquivo de entrada e o número total de jobs
// Output: Nenhum
// Pré-condição: Entrada não é nula
// Pós condição: Jobs são impressos no terminal
void imprimirEntrada(Job** entrada, int n);

// Funcao que imprime a melhor resposta dos algortimos utilizados
// Input: Estrutura permuta e o númro de jobs
// Output: Nenhum
// Pré-condição: Permuta não é nula e numero de jobs é um inteiro positivo
// Pós condição: Melhor resposta é impressa na tela
void imprimirResposta(Permuta* p, int n);

// Funcao que imprime os dados de uma estrutura permuta
// Input: A estrutura permuta
// Output: Nenhum
// Pré-condição: Estrutura permuta não é nula
// Pós condição:Dados da estrutura são impressos em terminal
void imprimir(Permuta* p);

// Funcao que desaloca a memoria utilizada por uma estrutura permuta
// Input: Estrutura permuta
// Output: Nenhum
// Pré-condição: Estrutura permuta não é nula
// Pós condição: Mémória da estrutura é desalocada
void liberarPermuta(Permuta* p);

// Funcao que desaloca a memoria utilizada pela lista
// Input: Estrutura lista
// Output: Nenhum
// Pré-condição: Estrutura lista não é nula
// Pós condição: Mémória da estrutura é desalocada
void liberarLista(Lista* lista);
