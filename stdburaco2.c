#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stdburaco2.h"

void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

Cards converte_carta(char *line){
    char  aux1[10];
    Cards carta;
    if(strstr(line,"♥")){
            carta.naipe= Copas;
        }else if(strstr(line,"♠")){
            carta.naipe= Espadas;
        }else if(strstr(line,"♣")){
            carta.naipe= Paus;
        }else if(strstr(line,"♦")){
            carta.naipe= Ouro;
        } 
        
        memset(aux1, '\0', sizeof(aux1));
        if(strlen(line) == 5){
            strncpy(aux1, line, 2);
        }else{
            strncpy(aux1, line, 1);
        }

        if(strstr(aux1,"A"))
            carta.numero = 14;
        else if(strstr(aux1,"K"))
            carta.numero = 13;
        else if(strstr(aux1,"Q"))
            carta.numero = 12;
        else if(strstr(aux1,"J"))
            carta.numero = 11;
        else
            carta.numero = atoi(aux1);
    return carta;
}

Hand converte_entrada(char *line){
    char *aux1;
    int indice =0, num_espacos =0,tamanho =0;
    Cards *cartas;
    Hand mao;
    
    for(int a=strlen(line)-1;a >= 0;a--){
        if(line[a] == ' ')
            num_espacos++;
    }
    tamanho = num_espacos -1;
    cartas = malloc(sizeof(Cards) * tamanho);
    aux1 = strtok(line,"[");
    aux1 = strtok(aux1," ");
    
    while(strstr(aux1, "]") == NULL){
        cartas[indice] = converte_carta(aux1);
        aux1= strtok(NULL," ");
        indice++;
    }
    mao.cartas = cartas;
    mao.tamanho = tamanho;
    return mao;
}

void ordernar(Hand *mao, int organiza_mele){
    int num_aux;
    Suit naip_aux;
    //Organização Simples
    for(int a=0; a<mao->tamanho; a++){
        for(int b=a; b<mao->tamanho; b++){
            if(mao->cartas[a].numero> mao->cartas[b].numero){
                naip_aux = mao->cartas[b].naipe;
                num_aux = mao->cartas[b].numero;
                mao->cartas[b].naipe= mao->cartas[a].naipe;
                mao->cartas[b].numero = mao->cartas[a].numero;
                mao->cartas[a].naipe= naip_aux;
                mao->cartas[a].numero = num_aux;
            }
            if(mao->cartas[a].naipe> mao->cartas[b].naipe){
                naip_aux = mao->cartas[b].naipe;
                num_aux = mao->cartas[b].numero;
                mao->cartas[b].naipe= mao->cartas[a].naipe;
                mao->cartas[b].numero = mao->cartas[a].numero;
                mao->cartas[a].naipe= naip_aux;
                mao->cartas[a].numero = num_aux;
            }
        }
    }
    num_aux =0;
    for(int a = mao->tamanho-1 ;mao->cartas[a].naipe ==Removido; a--)
        num_aux++;
    if(num_aux){
        mao->tamanho -= num_aux;
        mao->cartas = realloc(mao->cartas ,sizeof(Cards) * mao->tamanho);   
    } 
    //Organização se tiver melé
    int indice_mele;
    if(organiza_mele){
        for(int a=0;a<mao->tamanho-1; a++){
            if(mao->cartas[a].numero+ 2 == mao->cartas[a+1].numero && mao->cartas[a].numero != 2){
                for(int b=0;b<mao->tamanho; b++){
                    if(mao->cartas[b].numero == 2){
                        indice_mele = b;
                        if(mao->cartas[a].naipe == mao->cartas[b].naipe){
                            for(int c=0;c<mao->tamanho; c++){
                                if(mao->cartas[c].numero == 2 && c != b){
                                    indice_mele =c;
                                    break;
                                }
                            }
                        }
                        if(indice_mele < a){
                            for(int c = indice_mele; c <a;c++){
                                    naip_aux = mao->cartas[c+1].naipe;
                                    num_aux = mao->cartas[c+1].numero;
                                    mao->cartas[c].naipe= mao->cartas[c+1].naipe;
                                    mao->cartas[c].numero = mao->cartas[c+1].numero;
                                    mao->cartas[c+1].naipe= naip_aux;
                                    mao->cartas[c+1].numero = num_aux;
                                }
                        }else{
                            for(int c = indice_mele; c >a+1;c--){
                                    naip_aux = mao->cartas[c-1].naipe;
                                    num_aux = mao->cartas[c-1].numero;
                                    mao->cartas[c].naipe= mao->cartas[c-1].naipe;
                                    mao->cartas[c].numero = mao->cartas[c-1].numero;
                                    mao->cartas[c-1].naipe= naip_aux;
                                    mao->cartas[c-1].numero = num_aux;
                                }
                        }

                    }

                }
            }
        }
    }
    return;
}

void imprimir(Cards carta){
    if(carta.numero <= 10){
        printf("%d", carta.numero);
    }else{
        switch (carta.numero){
            case 11:
                printf("J");
                break;
            case 12:
                printf("Q");
                break;
            case 13:
                printf("K");
                break;
            case 14:
                printf("A");
                break;
        }
    }
    switch (carta.naipe){
        case Copas:
            printf("♥");
            break;
        case Ouro:
            printf("♦");
            break;
        case Espadas:
            printf("♠");
            break;
        case Paus:
            printf("♣");
            break;
        case Removido:
            printf("ERRO :Carta removida tentou ser impressa");
            break;
    }
    return;
}

void imprimir_console(int num, int naipe){
    if(num <= 10){
        fprintf(stderr, "%d", num);
    }else{
        switch (num){
            case 11:
                fprintf(stderr, "J");
                break;
            case 12:
                fprintf(stderr, "Q");
                break;
            case 13:
                fprintf(stderr, "K");
                break;
            case 14:
                fprintf(stderr, "A");
                break;
        }
    }
    switch (naipe){
        case Copas:
            fprintf(stderr, "♥ ");
            break;
        case Ouro:
            fprintf(stderr, "♦ ");
            break;
        case Espadas:
            fprintf(stderr, "♠ ");
            break;
        case Paus:
            fprintf(stderr, "♣ ");
            break;
    }
    return;
}

void adicionar_carta(Hand *mao, Cards nova_carta){
    if(mao->tamanho == 0)
        mao->cartas = malloc(sizeof(Cards));
    else{
        //fprintf(stderr,"%d\n", (mao->tamanho+1));
         mao->cartas = realloc(mao->cartas, sizeof(Cards)  *(mao->tamanho+1));
        //mao->cartas = realloc(mao->cartas, sizeof(Cards)*(500));
        
        if(mao->cartas==NULL){
            exit(57);
            fprintf(stderr,"57\n");
        }
    }
    mao->cartas[mao->tamanho].numero = nova_carta.numero;
    mao->cartas[mao->tamanho].naipe = nova_carta.naipe;
    mao->tamanho++;
    return;
}

void baixar_jogos(Hand *mao, Sequence *jogos){
    int sequencia = 1;
    for(int a=0;a <mao->tamanho-1;a++){
        if(mao->cartas[a].naipe == mao->cartas[a+1].naipe && (mao->cartas[a].numero - mao->cartas[a+1].numero) == -1){
            sequencia++;
        }else{
            if(sequencia >= 3){
                printf("MELD_NEW [");
                for(int b= a-(sequencia-1); b<=a;b++){
                    printf(" ");
                    imprimir(mao->cartas[b]);
                }
                printf(" ]\n");
                jogos->linha++;
                if(jogos->linha != 1){
                    jogos->mao = realloc(jogos->mao, sizeof(Hand)  * jogos->linha);
                }     
                jogos->mao[jogos->linha-1].tamanho = 0; 
                for(int b= a-(sequencia-1); b<=a;b++){
                    adicionar_carta(&(jogos->mao[jogos->linha-1]), mao->cartas[b]);
                    mao->cartas[b].naipe = Removido;
                }
                ordernar(mao, 0);
                ordernar(&jogos->mao[jogos->linha-1], 1);
                a =0;
            }
            sequencia =1 ;
        }  
    }
    return;
}

int jogo_lixo(Hand *mao, Cards lixo, Sequence *jogos){
    for(int a=0;a <mao->tamanho-1; a++){
        if(lixo.naipe == mao->cartas[a].naipe && mao->cartas[a].naipe == mao->cartas[a+1].naipe){                   //Topo do lixo e carta mesmo naipe
            if((lixo.numero + 1 == mao->cartas[a].numero && mao->cartas[a].numero +1 == mao->cartas[a+1].numero) || //Estão na forma [lixo, carta[a], carta[a+1]]
            (mao->cartas[a].numero +1 ==lixo.numero  && lixo.numero +1 ==  mao->cartas[a+1].numero) ||              //ou estão na forma [carta[a], lixo, carta[a+1]]
            (mao->cartas[a].numero +1 ==mao->cartas[a+1].numero  &&  mao->cartas[a+1].numero +1 == lixo.numero)){   //ou estão na forma [carta[a], carta[a+1], lixo]
                printf("GET_DISCARD [ ");
                imprimir(mao->cartas[a]);
                printf(" ");
                imprimir(mao->cartas[a+1]);
                printf(" ]\n");  
                jogos->linha++;
                if(jogos->linha != 1){
                    jogos->mao = realloc(jogos->mao, sizeof(Hand) * jogos->linha);
                }
                jogos->mao[jogos->linha-1].tamanho = 0; 
                adicionar_carta(&jogos->mao[jogos->linha-1], mao->cartas[a]);
                adicionar_carta(&jogos->mao[jogos->linha-1], mao->cartas[a+1]);
                adicionar_carta(&jogos->mao[jogos->linha-1], lixo);

                ordernar(&jogos->mao[jogos->linha-1],1);
                mao->cartas[a].naipe = Removido;
                mao->cartas[a+1].naipe = Removido;
                return 1;
            }
        }
    }
    fprintf(stderr,"Primeira parte ok\n");
    for(int a=0;a <mao->tamanho-1; a++){  
        fprintf(stderr,"1");       
        if(lixo.naipe == mao->cartas[a].naipe    &&
        (lixo.numero == mao->cartas[a].numero +1 ||
        lixo.numero == mao->cartas[a].numero -1  ||
        lixo.numero == mao->cartas[a].numero +2  ||
        lixo.numero == mao->cartas[a].numero -2)){                       
            for(int b=0;b <mao->tamanho; b++){
                fprintf(stderr,"2");
                if(mao->cartas[b].numero == 2 && a != b){
                    jogos->linha++;
                    if(jogos->linha != 1){
                        jogos->mao = realloc(jogos->mao, sizeof(Hand) * jogos->linha);
                    }
                    jogos->mao[jogos->linha-1].tamanho = 0; 
                    adicionar_carta(&jogos->mao[jogos->linha-1], mao->cartas[a]);
                    adicionar_carta(&jogos->mao[jogos->linha-1], lixo);
                    printf("GET_DISCARD [ ");
                    imprimir(mao->cartas[a]);
                    printf(" ");
                    for(int c=b;c <mao->tamanho; c++){
                        fprintf(stderr,"3");
                        if(mao->cartas[c].numero == 2 &&mao->cartas[c].naipe == mao->cartas[a].naipe){
                            fprintf(stderr,"4");
                            adicionar_carta(&jogos->mao[jogos->linha-1], mao->cartas[c]);
                           fprintf(stderr,"(4.1)"); 
                            imprimir(mao->cartas[c]);
                            fprintf(stderr,"(4.2)");
                            ordernar(&jogos->mao[jogos->linha-1],1);
                            fprintf(stderr,"(4.3)");
                            printf(" ]\n");
                            mao->cartas[c].naipe = Removido;
                            mao->cartas[a].naipe = Removido;
                            return 1;
                        }
                    }
                    fprintf(stderr,"5");
                    imprimir(mao->cartas[b]);
                    adicionar_carta(&jogos->mao[jogos->linha-1], mao->cartas[b]);
                    ordernar(&jogos->mao[jogos->linha-1],1);
                    printf(" ]\n");
                    mao->cartas[b].naipe = Removido;
                    mao->cartas[a].naipe = Removido;
                    return 1;
                }
            }
        }
    }
    return 0;
}

void anexar_cartas(Hand *mao, Sequence *jogos){
    Suit linha_naipe;
    int indice_mele = -1, valor;
    for(int a=0;a <mao->tamanho;a++){                       //Passa pelas cartas da mao
        for(int b=0; b<jogos->linha; b++){                  //Passa pelos jogos feitos
            for(int c=0; c <jogos->mao[b].tamanho; c++){
                if(jogos->mao[b].cartas[c].numero != 2)
                    linha_naipe = jogos->mao[b].cartas[c].naipe;
                else
                    indice_mele = c;
            }
            if(mao->cartas[a].naipe == linha_naipe && mao->cartas[a].numero != 2){ //Se tem o mesmo naipe...
                if(jogos->mao[b].cartas[0].numero == 2){
                    valor = jogos->mao[b].cartas[1].numero -1;
                    linha_naipe  = jogos->mao[b].cartas[1].naipe;
                }else{
                    valor = jogos->mao[b].cartas[0].numero;
                    linha_naipe  = jogos->mao[b].cartas[0].naipe;
                } 
                if(valor == mao->cartas[a].numero + 1 && mao->cartas[a].naipe == linha_naipe){
                    printf("MELD_JOIN %d [ ", b);
                    do{ 
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a--;
                    } while(a >= 0 && mao->cartas[a].naipe ==  mao->cartas[a+1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1);
                    printf("]\n");
                    if(a < 0)
                        a =0;
                    ordernar(mao,0);
                    ordernar(&jogos->mao[b],1);
                }else if(jogos->mao[b].cartas[jogos->mao[b].tamanho - 1].numero == mao->cartas[a].numero - 1  
                && indice_mele != jogos->mao[b].tamanho - 1 && mao->cartas[a].naipe == linha_naipe){
                    printf("MELD_JOIN %d [ ", b);
                    do{
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a++;
                    } while (a < mao->tamanho && mao->cartas[a].naipe ==  mao->cartas[a-1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1 && a != indice_mele);
                    printf("]\n");
                    a =0;
                    ordernar(mao,0);
                    ordernar(&jogos->mao[b],1);         
                }
                
            }
        }
    }
    return;
}

int pior_carta(Hand mao){
    return 0;
    /*
    int indice = 0, maior_diferenca=0;
    for(int a=0; a< mao.tamanho; a++){
        if((a > 0 && a < mao.tamanho -1 && mao.cartas[a].naipe != mao.cartas[a-1].naipe && mao.cartas[a+1].naipe != mao.cartas[a].naipe) ||
        (a == 0 && mao.cartas[a+1].naipe != mao.cartas[a].naipe) || (a ==mao.tamanho -1 && mao.cartas[a-1].naipe != mao.cartas[a].naipe)){
            return a;
        }else if(a ==0  && mao.cartas[a].naipe == mao.cartas[a+1].naipe && mao.cartas[a+1].numero -mao.cartas[a].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao.cartas[a+1].numero -mao.cartas[a].numero;
        }else if(a ==mao.tamanho-1 && mao.cartas[a].naipe == mao.cartas[a-1].naipe  && mao.cartas[a].numero -mao.cartas[a-1].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao.cartas[a].numero -mao.cartas[a-1].numero;
        }else if(mao.cartas[a].naipe == mao.cartas[a+1].naipe  && mao.cartas[a].naipe != mao.cartas[a-1].naipe && mao.cartas[a+1].numero -mao.cartas[a].numero > maior_diferenca){
            indice = a;
            maior_diferenca =  mao.cartas[a+1].numero -mao.cartas[a].numero ;
        }else if(mao.cartas[a].naipe == mao.cartas[a-1].naipe  && mao.cartas[a].naipe != mao.cartas[a+1].naipe && mao.cartas[a].numero -mao.cartas[a-1].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao.cartas[a].numero -mao.cartas[a-1].numero;
        }else if(mao.cartas[a].naipe == mao.cartas[a+1].naipe  && mao.cartas[a+1].numero -mao.cartas[a].numero > maior_diferenca){
            indice = a;
            maior_diferenca = mao.cartas[a+1].numero -mao.cartas[a].numero;
        }else if(mao.cartas[a].naipe == mao.cartas[a-1].naipe  && mao.cartas[a].numero -mao.cartas[a-1].numero > maior_diferenca){
            indice = a;
            maior_diferenca =  mao.cartas[a].numero -mao.cartas[a-1].numero;
        }
    }
    return indice;
    */
}

/*

void anexar_cartas(Hand *mao, Sequence *jogos){
    Suit linha_naipe;
    int indice_mele = -1, valor;
    fprintf(stderr, "\nYAMETE KUDASSAI: %d\n", mao->tamanho);
    for(int a=0;a <mao->tamanho;a++){  
        fprintf(stderr, "\nYAMETE KUDASSAI: %d\n", mao->tamanho);                     //Passa pelas cartas da mao
        for(int b=0; b<jogos->linha; b++){                  //Passa pelos jogos feitos
            for(int c=0; c <jogos->mao[b].tamanho; c++){
                if(jogos->mao[b].cartas[c].numero != 2)
                    linha_naipe = jogos->mao[b].cartas[c].naipe;
                else
                    indice_mele = c;
            }
            if(mao->cartas[a].naipe == linha_naipe && mao->cartas[a].numero != 2){ //Se tem o mesmo naipe...
                if(jogos->mao[b].cartas[0].numero == 2){
                    valor = jogos->mao[b].cartas[1].numero -1;
                    linha_naipe  = jogos->mao[b].cartas[1].naipe;
                }else{
                    valor = jogos->mao[b].cartas[0].numero;
                    linha_naipe  = jogos->mao[b].cartas[0].naipe;
                } 
                if(valor == mao->cartas[a].numero + 1 && mao->cartas[a].naipe == linha_naipe){
                    printf("MELD_JOIN %d [ ", b);
                    do{ 
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a--;
                    } while(a >= 0 && mao->cartas[a].naipe ==  mao->cartas[a+1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1);
                    printf("]\n");
                    if(a < 0)
                        a =0;
                    ordernar(mao,0);
                    ordernar(&jogos->mao[b],1);
                }else if(jogos->mao[b].cartas[jogos->mao[b].tamanho - 1].numero == mao->cartas[a].numero - 1  
                && indice_mele != jogos->mao[b].tamanho - 1 && mao->cartas[a].naipe == linha_naipe){
                    printf("MELD_JOIN %d [ ", b);
                    do{
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a++;
                    } while (a < mao->tamanho && mao->cartas[a].naipe ==  mao->cartas[a-1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1 && a != indice_mele);
                    printf("]\n");
                    ordernar(mao,0);
                    ordernar(&jogos->mao[b],1);         
                }
                
            }
        }
    }
    return;
}
void anexar_cartas(Hand *mao, Sequence *jogos){
    Suit linha_naipe;
    int indice_mele = -1;
    for(int a=0;a <mao->tamanho;a++){ //Passa pelas cartas da mao
        for(int b=0; b<jogos->linha; b++){ //Passa pelos jogos feitos
            for(int c=0; c <jogos->mao[b].tamanho; c++){
                if(jogos->mao[b].cartas[c].numero != 2)
                    linha_naipe = jogos->mao[b].cartas[c].naipe;
                else
                    indice_mele = c;
            }
            if(mao->cartas[a].naipe == linha_naipe && mao->cartas[a].numero != 2){ //Se tem o mesmo naipe...
                if(jogos->mao[b].cartas[0].numero == mao->cartas[a].numero + 1 && indice_mele != 0){
                    printf("MELD_JOIN %d [ ", b);
                    do{ 
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a--;
                    } while(a >= 0 && mao->cartas[a].naipe ==  mao->cartas[a+1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1 && a != indice_mele &&
                             mao->cartas[a].numero != 2);
                    printf("]\n");
                    
                    ordernar(mao);
                    ordernar(&jogos->mao[b]);
                }else if(jogos->mao[b].cartas[jogos->mao[b].tamanho - 1].numero == mao->cartas[a].numero - 1  && indice_mele != jogos->mao[b].tamanho - 1){
                    printf("MELD_JOIN %d [ ", b);
                    do{
                        adicionar_carta(&jogos->mao[b], mao->cartas[a]);
                        imprimir(mao->cartas[a]);
                        printf(" ");
                        mao->cartas[a].naipe = Removido;
                        a++;
                    } while (a < mao->tamanho && mao->cartas[a].naipe ==  mao->cartas[a-1].naipe &&
                            mao->cartas[a].numero==  mao->cartas[a+1].numero -1 && a != indice_mele);
                    printf("]\n");
                    ordernar(mao);
                    ordernar(&jogos->mao[b]);         
                }

            }
        }
    }
    return;
}
*/