#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define user 10


typedef struct{
     char rua[20];
    int num;
    char bairro[20];
    int cep;

}endereco;


typedef struct cadastrar //struct para info de cada usuário
{
    char nome[20];
    double cpf;
    endereco ender;
    float renda;
    int telefone;
    char email[40];
    char senha[20];
    int posicaofila;
}cadastro;

typedef struct alimentos//struct para cada alimento
{
  char nome[20];
  int quantidade;
}al;

typedef struct cesta
{
    int quantidade;
    float total_dinheiro;
}ces;

// Cadastro do usuário
cadastro usuario[10] = {"Heitor", 12345678901, "xv de novembro",1295, "centro", 86300000, 1600.835, 40028922, "email", "senha"};
cadastro ong[10] = { "ALIMENTA VIDAS", 24354657 , "Madereira" , 34, " torres" , 567000 , 2344 , 455678294, "ong" , "senha"};

void zeraCPF();
void mostrarMenu();
int cadastrar();
//int cadastra_ong();
int login();
int doar(al *alimento);
void mostrarDadosUsuario(int id);
int doar_dinheiro(ces *cesta);
void verificaAlimento(al alimento[]);
void cesta_pronta(al *alimento,ces *cesta  );
int entregar_cesta(ces *cesta);
void receber(int *final_fila,int id);
int fila=0;

int main()
{
  int finalF = 0;
  int *final_fila= &finalF;
  int op, log, oplog,c,opdoar,op_receber=1,opdados=1,opONG;
  al alimento[12] = {"Acucar",2,"Arroz",1,"Cafe",1,"Extrato de Tomate",2,"Farinha de Milho",1,"Farinha de Trigo",2,"Feijao",1,"Macarrao",1,"Oleo de soja",2,"Sal",1,"Biscoito Recheado",3};
    ces *cesta;
    cesta = malloc(sizeof(ces));
    cesta->quantidade = 0;
    cesta->total_dinheiro = 0.00;
    zeraCPF();
    do{
        printf("%d",*final_fila);
        mostrarMenu();
        scanf("%d", &op); //seleciona opção do usuário
      setbuf(stdin, NULL);
        system("cls");
        fflush(stdin);
        if(op==1)
        {
            cadastrar();
            printf("\nVoce esta cadastrado, logue para entrar!\n");
        }
        if(op==2){
            log = login();
            if(log>0) //log-1 = ID do usuário
            {
                do{
                    printf("\n--------------------");
                    printf("\nVoce esta logado!\n\n");
                    printf("O que deseja fazer\n");
                    printf("0-Voltar\n");
                    printf("1-Doar\n");
                    printf("2-Receber\n");
                    printf("3-Mostrar dados do usuario\n");
                    printf("--------------------\n");
                    scanf("%d", &oplog);
                    system("cls");
                    if(oplog==1)
                    {
                        do{
                            printf("DOACAO\n");
                            printf("0- Deseja Voltar\n");
                            printf("1-Doar alimento\n");
                            printf("2-Doar dinheiro\n");
                            printf("3-Buscar alimentos em falta \n");
                            scanf("%d", &opdoar);
                            system("cls");
                            if(opdoar==1)
                            {
                                verificaAlimento(alimento);
                                doar(&alimento);
                            }
                            if(opdoar==2)
                            {
                                doar_dinheiro(cesta);
                            }
                            if(opdoar==3){
                                verificaAlimento(alimento);
                            }
                            else break;
                        }while(opdoar!=0);

                      if(fila<=*final_fila){
                        cesta_pronta(&alimento,cesta);
                        if(cesta>0){
                          entregar_cesta(cesta);
                        }
                      }
                        
                    }
                    if(oplog==3)
                    {
                        do{
                        mostrarDadosUsuario(log-1);
                        printf("\n\n0 - Deseja voltar : ");
                        scanf("%d",&opdados);
                        system("cls");
                        }while(opdados!=0);
  
                    }
                    if (oplog==2){
                        do{
                            receber(final_fila,log-1);
                            printf("\nVocê é o %dº da fila.",(usuario[log-1].posicaofila)-fila);
                            printf("\n\n0 - Deseja voltar : ");
                            scanf("%d",&op_receber);
                            system("cls");
                        }while (op_receber!=0);
                    }
                }while(oplog!=0);
            }

        }
       // if(op==3){
         //   cadastra_ong();
        //}
    }while(op!=0);
    return 0;
}

void zeraCPF()
{
    for(int x=1; x<user; x++)
    {
        usuario[x].cpf=0;
    }
}

void mostrarMenu()
{
    system("cls");
    printf("--------MENU---------");
    printf("\n0 - SAIR");
    printf("\n1 - REALIZAR CADASTRO ");
    printf("\n2 - REALIZAR LOGIN");
    printf("\n--------------------\n");

}

int cadastrar()
{
    int email, cpf, erro;
    for(int x=0; x <user ;x++)
    {
        if(usuario[x].cpf==0) //para achar qual o próximo id de usuario que ira ser adicionado
        {
            printf("Digite seu nome: ");
            fgets(usuario[x].nome,20,stdin);
            //scanf("%s", usuario[x].nome);
            fflush(stdin);
            do{
                printf("Digite seu cpf: ");
                scanf("%lf", &usuario[x].cpf);
                setbuf(stdin, NULL);
                for(int j=0; j<x; j++)
                {
                    if(usuario[x].cpf==usuario[j].cpf)
                    {
                        printf("\nCPF ja cadastrado\n");
                        printf("0-sair\n");
                        printf("1-Tentar novamente\n");
                        scanf("%d", &cpf);
                        if(cpf==0)
                          return 0;
                          break;
                    }
                    else cpf=0;
                } 
            }while(cpf==1);
            setbuf(stdin, NULL);
            printf("Digite sua rua: ");
            fgets(usuario[x].ender.rua,20,stdin);
            //scanf("%s", usuario[x].rua);
            setbuf(stdin, NULL);
            printf("Digite seu numero da casa: ");
            scanf("%d", &usuario[x].ender.num);
            setbuf(stdin, NULL);
            printf("Digite seu bairro: ");
            fgets(usuario[x].ender.bairro,20,stdin);
            //scanf("%s", usuario[x].bairro);
            setbuf(stdin, NULL);
            printf("Digite seu CEP: ");
            scanf("%d", &usuario[x].ender.cep);
            printf("Digite sua renda: ");
            scanf("%f", &usuario[x].renda);
            setbuf(stdin, NULL);
            do{
                printf("Digite seu email: ");
                scanf("%s", usuario[x].email);
                for(int i=0; i<x; i++)
                {
                    if(strcmp(usuario[x].email, usuario[i].email)==0)
                    {
                        printf("\nEmail ja cadastrado!!");
                        printf("\n0-Voltar para menu inicial");
                        printf("\n1-Tentar novamente\n");
                        scanf("%d", &email);
                        if(email==0) return 0;
                        break;
                    }
                    else email=0;
                }
            }while(email==1);
            printf("Digite sua senha: ");
            scanf("%s", usuario[x].senha);
            setbuf(stdin, NULL);
            printf("\nVoce esta cadastrado, logue para entrar!\n");
            return 0;
        }
    }
}

int login()
{
    int op;
    char verificaEmail[40], verificaSenha[10];
    do{
        
        printf("\nDigite seu email: ");
        scanf("%s", verificaEmail);
        printf("\nDigite sua senha: ");
        scanf("%s", verificaSenha);
        system("cls");

        for(int x=0;x<user; x++)
        {
            if(strcmp(verificaEmail, usuario[x].email)==0)
            {
                if(strcmp(verificaSenha, usuario[x].senha)==0) //se email e senha forem iguais a cadastrada, loga com sucesso
                {
                    return x+1; //retorna id do usuário +1
                }
            }
        }
        printf("\nEmail ou senha invalidos\n");
        printf("0-Voltar");
        printf("\n1-Tentar novamente\n");
        scanf("%d", &op);
        system("cls");
    }while(op!=0);
    return 0;
}

int doar(al *alimento) // Struct como parametro
{
    int op, qt;
    do
    {
        
        printf("\n0 - Sair do menu de doação: ");
        printf("\nGuia de doação de alimentos: \n");
        printf("1 - Açucar,\n2 - Arroz,\n3 - Cafe,\n4 - Extrato de tomate,\n5 - Farinha de Milho,\n6 - Farinha de trigo ");
        printf("\n7 - Feijao,\n8 - Macarrao,\n9 - Oleo de Soja,\n10 - Sal,\n11 - Biscoito Recheado ");
        scanf("%d", &op);
        switch(op-1)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            {
                printf("\nDigite o numero a ser doado: ");
                scanf("%d", &qt);
                alimento[op].quantidade += qt;
                break;
            }
            case -1:
            {
                return 0;
            }
            default:
            {
                printf("Valor invalido, tente novamente");
                break;
            }
        }
    }
    while(op != -1);

}

int doar_dinheiro(ces *cesta) // função de doação especifica para dinheiro
{
    int op;
    float qt;
    do
    {
        printf("\nDigite 1 para doar um valor em dinheiro: ");
        printf("\nDigite 0 para sair do menu: \n");
        scanf("%d", &op);
        system("cls");
        if(op==1)
        {
            printf("\nDigite o valor a ser doado: ");
            scanf("%f", &qt);
            cesta->total_dinheiro += qt;
        }
        else if(op==0)
        {
            return 0;
        }
        else
        {
            printf("\nValor invalido");
        }

    }while(op != 0);
}

void verificaAlimento(al alimento[])
{
    
    printf("\n\n----Alimentos em falta----\n\n");
    for(int i = 0;i<11;i++)
    {
        if(alimento[i].quantidade==0) printf("%s\n",alimento[i].nome);
    }
    
}


void quantidadeAlimento(al *alimento){

    printf("Quantidade de alimentos!\n");
    for(int i = 0 ; i < 11;i++){
        printf("%s =  %d",alimento[i].nome, alimento[i].quantidade);
    }
}


void mostrarDadosUsuario(int id) //mostra todos dados do usuário
{
    printf("---------Dados cadastrais-------\n");
    printf("\nNome : %s", usuario[id].nome);
    printf("CPF : %.lf", usuario[id].cpf);
    printf("\nRua : %s", usuario[id].ender.rua);
    printf("Bairro: %s", usuario[id].ender.bairro);
    printf("Numero da casa: %d", usuario[id].ender.num);
    printf("\nCEP: %d", usuario[id].ender.cep);
    printf("\nRenda: %.2f", usuario[id].renda);
    printf("\nTelefone: %d", usuario[id].telefone);
    printf("\nEmail: %s", usuario[id].email);
    printf("\nSenha: %s", usuario[id].senha);

   
}

void cesta_pronta(al *alimento, ces *cesta ){

    int cont=0,cestas=cesta->quantidade;
    int i;
    
    do{
        for(i = 0; i < 11 ;i++){
            if(alimento[i].quantidade > 0){
               cont++; 
            }
        } 

        if(cont == 11){
            cestas++;
            for(i=0;i<11;i++){ 
                alimento[i].quantidade--; 
            }
            cont = 0;
        }

    }while(cont == 0 );

    while(cesta->total_dinheiro > 200.00){
       cesta->total_dinheiro -= 200.00;
       cestas++;
    }
    cesta->quantidade = cestas;
  }

void receber(int *final_fila,int id){
  if(usuario[id].posicaofila>0){
    printf("voce ja esta na fila");
  }
  else{
    usuario[id].posicaofila = (*final_fila)+1;
    *final_fila = (usuario[id].posicaofila);
    //printf("\n Final fila %d",*final_fila);
    //printf("\n fila %d",fila);
  }
}

int entregar_cesta(ces *cesta){
  fila++;
  cesta->quantidade--;
 //return cesta->quantidade;
}

