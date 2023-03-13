/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2022                           **/
/**   Turma 03 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Marcos Martins de Oliveira Pacheco>      <13672602>          **/
/**                                                                 **/
/*********************************************************************/

#include <stdlib.h>

#include <stdio.h>

#define false 0
#define true 1

typedef int bool;

typedef struct {
  int nusp;
  int nota;
  int freq;
}
ALUNO;

typedef struct aux {
  ALUNO * aluno;
  struct aux * prox;
}
ELEMENTO;

typedef ELEMENTO * PONT;

typedef struct {
  PONT listaNUSP;
  PONT listaNOTA;
}
TURMA;

/* ASSINATURAS DAS FUNCOES INICIAIS - NAO MODIFICAR */
int tamanho(TURMA * turma);
ALUNO * buscarAluno(TURMA * turma, int nusp);
bool inserirAluno(TURMA * turma, int nusp, int nota, int frequencia);
bool excluirAluno(TURMA * turma, int nusp);
void print123();
TURMA inicializaTurma();
void reinicializaTurma(TURMA * turma);
void exibirTurma(TURMA * turma);

/* Funcao usada em testes da correcao automatica - NAO APAGAR OU MODIFICAR */
void print123() {
  /* Funcao utilizada pelo sistema de correcao automatia
     Nao apague ou modifique esta funcao                 */
}

/* IMPLEMENTE FUNCOES EXTRAS/AUXILIARES SE JULGAR NECESSARIO */

/* Funcao que retorna o numero de alunos da turma cujo endereco foi passado
   como parametro de entrada. */
int tamanho(TURMA * turma) {
  int tam = 0;
  PONT end = turma -> listaNUSP -> prox;
  while (end != turma -> listaNUSP) {
    end = end -> prox;
    tam++;
  }

  return tam;
}

/* Funcao que recebe o endereco de uma turma e um numero USP e retorna 
   NULL caso nao exista um aluno com o respectivo numero USP na turma ou
   o endereco de memoria do registro do respectivo aluno, caso ele esteja
   presente na turma. */
ALUNO * buscarAluno(TURMA * turma, int nusp) {
  PONT pos = turma -> listaNUSP -> prox;
  turma -> listaNUSP -> aluno -> nusp = nusp;
  while (pos -> aluno -> nusp != nusp) {
    pos = pos -> prox;
  }
  if (pos != turma -> listaNUSP && pos -> aluno -> nusp == nusp) {
    return pos -> aluno;
  }
  return NULL;
}

/* Funcao que recebe o endereco de uma turma e o numero USP, nota e frequencia
   de um aluno e deve:
   Retornar false caso o numero USP seja menor do que zero, ou a nota seja
   menor do que zero ou maior do que cem ou a frequencia seja menor do que 
   zero ou maior do que cem;
   Deve, tambem, retornar false se a turma ja contiver um aluno com o mesmo
   numero USP.
   Caso contrario, esse novo aluno devera ser inserido na turma e a funcao
   devera retornar true. A insercao na turma contem as seguintes atividades:
     1a) alocacao dinamica de memoria para uma estrutura do tipo ALUNO e
         preenchimento de seus campos com os respectivos parametros recebidos
         pela funcao de insercao;
     2a) alocacao dinamica de memoria de duas estruturas do tipo ELEMENTO
         (ambas irao referenciar o novo aluno por meio de seu campo 'aluno'.
         Uma delas devera ser inserida na posicao correta da lista ordenada 
         por nusp e a outra na posicao correta da lista ordenada por nota.
     3a) por fim, a funcao devera retornar true.
*/
bool inserirAluno(TURMA * turma, int nusp, int nota, int frequencia) {
  if (nusp < 0 || nota < 0 || nota > 100 || frequencia < 0 || frequencia > 100) {
    return false;
  }

  ALUNO * j = (ALUNO * ) malloc(sizeof(ALUNO));
  j -> nusp = nusp;
  j -> nota = nota;
  j -> freq = frequencia;
  PONT i;
  PONT n;
  n = (PONT) malloc(sizeof(ELEMENTO));
  i = (PONT) malloc(sizeof(ELEMENTO));
  i -> aluno = buscarAluno(turma, nusp);
  if (i -> aluno != NULL) {
    return false;
  }
  
  PONT atual = turma -> listaNUSP -> prox;
  PONT ant = turma -> listaNUSP;
  turma -> listaNUSP->aluno->nusp=nusp+1;
  
  while (atual -> aluno -> nusp < nusp) {
    ant = atual;
    atual = atual -> prox;
  }
  i -> aluno = j;
  i -> prox = ant -> prox;
  ant -> prox = i;

  PONT atualn = turma -> listaNOTA -> prox;  
  PONT antn = turma -> listaNOTA;
  turma -> listaNOTA->aluno->nota=nota+1;
  while (atualn -> aluno -> nota < nota) {
    antn = atualn;
    atualn = atualn -> prox;
  }
  n -> aluno = j;
  n -> prox = antn -> prox;
  antn -> prox = n;
  
  return true;

}

/* Funcao que recebe o endereco de uma turma e um numero USP e deve:
   Retornar false se a turma nao possuir um aluno com esse numero USP.
   Caso contrario, esse aluno devera ser excluido da turma e a funcao
   devera retornar true. A exclusao na turma contem as seguintes atividades:
     1a) remocao dos elementos que apontam para o respectivo aluno das duas
         listas (ordenada por nusp e ordenada por nota).
     2a) liberacao da memoria do registro do aluno e dos elementos das listas
         que apontavam para o respectivo aluno.
     3a) por fim, a funcao devera retornar true.
*/
bool excluirAluno(TURMA * turma, int nusp) {

  if (buscarAluno(turma, nusp) == NULL) {
    return false;
  }
  PONT atual,ant,atualn,antn;
  atual = turma -> listaNUSP -> prox;
  ant = turma -> listaNUSP;
  while(atual->aluno->nusp!=nusp){
    ant=atual;
    atual=atual->prox;
  }
  ant->prox=atual->prox;
  
  atualn = turma -> listaNOTA -> prox;
  antn = turma -> listaNOTA;
  while(atualn->aluno->nusp!=nusp){
    antn=atualn;
    atualn=atualn->prox;
  }
  antn->prox=atualn->prox;
  free(atualn);  
  free(atual);
  
 
  return true;
}

/* Funcao que cria e retorna uma TURMA.
   Neste EP, uma turma contem duas listas ligadas de ELEMENTOS,
   estas listas sao circulares e possuem no-cabeca
*/
TURMA inicializaTurma() {
  TURMA t1;

  // criacao de um aluno ficticio que poder ser usado como sentinela
  ALUNO * ficticio = (ALUNO * ) malloc(sizeof(ALUNO));
  ficticio -> nusp = -1;
  ficticio -> nota = -1;
  ficticio -> freq = -1;

  // criacao do primeiro no-cabeca
  t1.listaNUSP = (PONT) malloc(sizeof(ELEMENTO));
  t1.listaNUSP -> aluno = ficticio;
  t1.listaNUSP -> prox = t1.listaNUSP;

  // criacao do segundo no-cabeca
  t1.listaNOTA = (PONT) malloc(sizeof(ELEMENTO));
  t1.listaNOTA -> aluno = ficticio;
  t1.listaNOTA -> prox = t1.listaNOTA;

  return t1;
}

/* Funcao que reinicia (ou limpa) a TURMA passada como parametro.
   Todos os elementos, exceto os nos-cabeca, sao apagamos e a TURMA fica
   da mesma forma como se ela tivesse sido recem criada.
*/
void reinicializaTurma(TURMA * turma) {
  PONT atual, apagar;

  // apagar todos os elementos, exceto o cabeca, da listaNUSP
  atual = turma -> listaNUSP -> prox;
  while (atual != turma -> listaNUSP) {
    apagar = atual;
    atual = apagar -> prox;
    free(apagar);
  }
  atual -> prox = atual;

  // apagar todos os elementos e os alunos, exceto o cabeca, da listaNOTA
  atual = turma -> listaNOTA -> prox;
  while (atual != turma -> listaNOTA) {
    apagar = atual;
    atual = apagar -> prox;
    free(apagar -> aluno);
    free(apagar);
  }
  atual -> prox = atual;
}

/* Funcao que exibe todos os alunos da turma referenciada como parametro.
   Alem de exibir os alunos nas duas ordens. */
void exibirTurma(TURMA * turma) {
  PONT atual = turma -> listaNUSP -> prox;
  ALUNO * aluno;
  printf("Exibindo lista [%i aluno(s)]\n", tamanho(turma));
  printf("   Ordenada por nusp:");
  while (atual != turma -> listaNUSP) {
    aluno = atual -> aluno;
    printf(" (%4i, %3i, %3i)", aluno -> nusp, aluno -> nota, aluno -> freq);
    atual = atual -> prox;
  }
  printf("\n   Ordenada por nota:");
  atual = turma -> listaNOTA -> prox;
  while (atual != turma -> listaNOTA) {
    aluno = atual -> aluno;
    printf(" (%4i, %3i, %3i)", aluno -> nusp, aluno -> nota, aluno -> freq);
    atual = atual -> prox;
  }
  printf("\n");
}

int main() {

  int nusp;
  ALUNO * res;
  bool ok;

  TURMA turma1 = inicializaTurma();

  exibirTurma( & turma1);

  nusp = 1234;
  ok = inserirAluno( & turma1, nusp, 100, 95);
  if (ok) printf("Inseracao do aluno %4i retornou true.\t(OK)\n", nusp);
  else printf("Inseracao do aluno %4i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 1234;
  ok = inserirAluno( & turma1, nusp, 100, 95);
  if (ok) printf("Inseracao do aluno %4i retornou true.\t(NOK)\n", nusp);
  else printf("Inseracao do aluno %4i retornou false.\t(OK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 1111;
  ok = inserirAluno( & turma1, nusp, 50, 75);
  if (ok) printf("Inseracao do aluno %4i retornou true.\t(OK)\n", nusp);
  else printf("Inseracao do aluno %4i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 2345;
  ok = inserirAluno( & turma1, nusp, 25, 100);
  if (ok) printf("Inseracao do aluno %4i retornou true.\t(OK)\n", nusp);
  else printf("Inseracao do aluno %4i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  ok = inserirAluno( & turma1, nusp, 25, 100);
  if (ok) printf("Inseracao do aluno %4i retornou true.\t(NOK)\n", nusp);
  else printf("Inseracao do aluno %4i retornou false.\t(OK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 9876;
  res = buscarAluno( & turma1, nusp);
  if (res) printf("Nota do aluno %i: %3i\n", nusp, res -> nota);
  else printf("Aluno nao encontrado: '%i'\n", nusp);

  nusp = 1234;
  res = buscarAluno( & turma1, nusp);
  if (res) printf("Nota do aluno %i: %3i\n", nusp, res -> nota);
  else printf("Aluno nao encontrado: '%i'\n", nusp);

  nusp = 1111;
  res = buscarAluno( & turma1, nusp);
  if (res) printf("Nota do aluno %i: %3i\n", nusp, res -> nota);
  else printf("Aluno nao encontrado: '%i'\n", nusp);

  nusp = 2345;
  res = buscarAluno( & turma1, nusp);
  if (res) printf("Nota do aluno %i: %3i\n", nusp, res -> nota);
  else printf("Aluno nao encontrado: '%i'\n", nusp);

  nusp = 2345;
  ok = excluirAluno( & turma1, nusp);
  if (ok) printf("A exclursao do aluno %i retornou true.\t(OK)\n", nusp);
  else printf("A exclursao do aluno %i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 2345;
  ok = excluirAluno( & turma1, nusp);
  if (ok) printf("A exclursao do aluno %i retornou true.\t(NOK)\n", nusp);
  else printf("A exclursao do aluno %i retornou false.\t(OK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 1234;
  ok = excluirAluno( & turma1, nusp);
  if (ok) printf("A exclursao do aluno %i retornou true.\t(OK)\n", nusp);
  else printf("A exclursao do aluno %i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  nusp = 1111;
  ok = excluirAluno( & turma1, nusp);
  if (ok) printf("A exclursao do aluno %i retornou true.\t(OK)\n", nusp);
  else printf("A exclursao do aluno %i retornou false.\t(NOK)\n", nusp);

  exibirTurma( & turma1);

  nusp = -1;
  ok = excluirAluno( & turma1, nusp);
  if (ok) printf("A exclursao do aluno %i retornou true.\t(NOK)\n", nusp);
  else printf("A exclursao do aluno %i retornou false.\t(OK)\n", nusp);

  exibirTurma( & turma1);

  inserirAluno( & turma1, 2000, 80, 90);
  inserirAluno( & turma1, 2001, 81, 91);
  inserirAluno( & turma1, 2002, 82, 92);
  inserirAluno( & turma1, 1999, 79, 89);
  inserirAluno( & turma1, 1998, 78, 88);
  inserirAluno( & turma1, 1997, 77, 87);

  exibirTurma( & turma1);

  return 0;
}