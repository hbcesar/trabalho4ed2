// Funcao que calcula a melhor permuta utilizando a heuristica beam serach
// Input: Os jobs de entrada, numero de jobs e tamanho do beam width
// Output: Estrutura permuta com melhor solucao encontrada pelo beam serach
// Pré-condição: Jobs não são nulos, width é inteiro positivo
// Pós condição: Melhor permuta pelo beam search eh encontrada
Permuta* beamSearch(Job** entrada, int n, int w);
