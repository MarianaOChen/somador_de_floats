/*Lab 1 - Somador de Floats*/
/*Autora: Mariana Onofre Chen RA: 156628*/
/*Neste exercício, construiremos um pequeno somador de números.
Ele recebe como entrada uma string e identifica nela todos os números
em formato float ou ponto flutuante, e então retorna a soma desses números.
O sistema não precisa operar com números negativos, mas deve rejeitar números
que estão "grudados" em strings (veja os exemplos). A resposta deve ser dada em
tão poucas casas decimais quanto possível. Os números podem ter zeros à esquerda
 (003 é igual a 3), mas a notação .3 para representar 0.3 é inválida. Caso não
 haja números na entrada, o programa deve retornar zero.*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int identify(char c){ /*função para identificar caracter recebido da strings
  se for numero retorna 1 / se for ponto retorna 2 / se for espaço retorna 3  /
  se for outro retorna 0 */
  //1o caso: é numero 0-9
  if((c>='0') && (c<='9')){
    return 1;
  }
  //2o caso: é ponto
  else if(c == '.'){
    return 2;
  }
  //3o caso: é espaço
  else if(c == ' '){
    return 3;
  }
  //4o caso: é outro
  else
  return 0;
} // fim função identify

/*Maquina de estado*/
typedef struct {
  int estado_atual;
} fsm, *Fsm; /* fsm = finite state machine */

/*Operar maquina de Estados */
int opera_fsm(void *this_fsm, char entrada) {
  Fsm maquina = (Fsm) this_fsm;
  int a = identify(entrada);

  switch (maquina->estado_atual) {
    case 0:
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
      if (a == 1) { //é um numero
        maquina->estado_atual = 1;
      } else {
        maquina->estado_atual = 2;
      }
      break;

    case 1:
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
      if (a == 1) { //Pode ser um numero valido
        maquina->estado_atual = 1;
      } else if(a == 2) {//é um ponto
        maquina->estado_atual = 3;
      } else if(a == 3){//é um espaço
        maquina->estado_atual = 5;
      } else{ // não é valido
        maquina->estado_atual = 2;
      }
      break;

    case 2: //não é numero
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
      if (a == 3) { // é espaço, pode voltar para IDLE
        maquina->estado_atual = 0;
      } else {
        maquina->estado_atual = 2;
      }
      break;

    case 3:
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
      if (a == 1) {
        maquina->estado_atual = 4; // é numero depois do ponto
      } else {
        maquina->estado_atual = 2; // não é numero dps do ponto
      }
      break;

    case 4:
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
      if (a == 1) {
        maquina->estado_atual = 4;
      } else if (a == 3) { // float valido
        maquina->estado_atual = 5;
      } else {
        maquina->estado_atual = 2;
      }
      break;

    case 5: // é um numero valido, deve ser somado
      printf("ESTADO: %d\n",maquina->estado_atual);  ///TESTE
        maquina->estado_atual = 0;

      break;
  }
  return (maquina->estado_atual);
}

/*Main*/
int main(){

/* Receber a String*/
  char string[500];
//Limpar string
  for(int i=0;i<500;i++){
    string[i] = '\0';
  }

  int a,c;
  c=0;
  a = 0; //Auxiliar
  while(c != '\n'){ // pegar os caracteres e salvar no vetor 'string'
    c = getchar();
    string[a++] = c;
  }
/*Maquina de estados*/
  fsm maquina;//Pegar nova string
  maquina.estado_atual = 0; //Começa em IDLE

//Tratar a string
  float soma; // variavel Soma final
  float sI; //auxiliar soma inteiros
  float sF; //auxiliar soma floats
  float aux;
  char auxc;
  int b;
  int aI; //auxiliar de inteiro
  int aF; // auxiliar de float

  soma = 0;
  aux = 0;
  a = 0;
  aI = 0;
  aF = 0;
  sI = 0;
  sF = 0;
  while(string[a] != '\0'){
    //chama maquina de estados
      opera_fsm((void*) (&maquina), string[a]);
      if(maquina.estado_atual == 0){
        aI = 0;
        aF = 0;
        sI = 0;
        sF = 0;
        a++;
      }
      else if(maquina.estado_atual == 1){ // é numero
       // aux = atof(string[a]);
        auxc = string[a];
          printf("Auxc: %c\n",auxc);
        aux = auxc -'0';
        printf("aux: %f\n",aux);  ///TESTE
        printf("aI: %d\n",aI);  ///TESTE

        if(aI ==0){// 1o numero
          b=1;
        }
        else{//b = pow(10,aI);
          b = 10;
        }
        printf("b:%d\n",b);
        sI = sI*b+aux;
        printf("sI:%f\n",sI);
        aI++;
        a++;

      }
      else if(maquina.estado_atual == 4){ //é numero com .
     //   aux = atof(string[a]);
     auxc = string[a];
       printf("Auxc: %c\n",auxc);
     aux = auxc -'0';
          printf("aux: %f\n",aux);  ///TESTE

        //b = pow(10,aF);
        if(aF ==1){// 1o numero
          b=1;
        }
        else{//b = pow(10,aI);
          b = 10;
        }
        sF =+ aux/b; // errado
        aF++;
        a++;

      }
      else if(maquina.estado_atual == 5){ // é numero valido
        soma = soma + sI +sF;
        a++;
      }
      else{
        a++;
      }

  }
  soma = soma + sI +sF;
//print soma de floats

  printf("Soma: %f\n",soma);


  return 0;
}
