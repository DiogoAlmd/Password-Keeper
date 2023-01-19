#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//structs
typedef struct dados{
	char lugar[80];
	char senha[30];
}dados;


//protótipos
void alocaSenha(dados **p, int tam);
int verificaEspacoSenha();
void menu();
void recebeSenhas(dados *p);
void grava(dados *p, char *str, int pos);
void mostrarSenhas(dados *p, int qtde);

//main
int main()
{
	setlocale(LC_ALL, "portuguese");

	menu();	
	return 0;
}

//funções
void alocaSenha(dados **p, int tam)
{
        if((*p=(dados*)realloc(*p,tam*sizeof(dados)))==NULL)
	        exit(1);
}

int verificaEspacoSenha()
{
	FILE *fptr=NULL;
	long int cont=0;

	if((fptr=fopen("senhas.bin","rb"))==NULL)
		return cont;

	else{
		fseek(fptr,0,2);   
		cont=ftell(fptr)/sizeof(dados);

		fclose(fptr);     
		return cont;
	  }//else
}

void menu()
{
	dados *pd=NULL;
	//dados *p;
	int qtde=0;
	int qtde2 = verificaEspacoSenha();
	
	alocaSenha(&pd, qtde+1);
	
	int op;

	printf("\n1.Mostrar senhas");
	printf("\n2.Criar senhas");
	printf("\n3.Sair\n");
	scanf("%i", &op);
	fflush(stdin);

	switch(op){
		case 1: mostrarSenhas(pd, qtde2+1);
			break;

		case 2: recebeSenhas(pd);
			break;

		case 3: exit(1);
			break;

		default: printf("\nOpção Inválida");
			 break;
	}
}

void recebeSenhas(dados *p)
{
	system("cls");
	printf("\nDigite de onde a sua senha é: ");
	gets(p->lugar);
	fflush(stdin);

	printf("\nDigite a sua senha: ");
	gets(p->senha);
	fflush(stdin);

	grava(p,"ab",1);
}

void grava(dados *p, char *str, int pos)
{
	FILE *fptr=NULL;
	
	if((fptr=fopen("senha.bin",str))==NULL)
		printf("\nErro ao abrir o arquivo");
	
	else{
	   if(strcmp(str,"rb+")==0)
	   	fseek(fptr,pos*sizeof(dados),0);
	   
	   fwrite(p,sizeof(dados), 1, fptr);
	  }//else
	fclose(fptr);   //fora do else - por conta do ab ou rb+
}

void mostrarSenhas(dados *p, int qtde)
{
	int i;
	FILE *fptr = NULL;
	system("cls");
	
	if((fptr = fopen("senha.bin","rb"))==NULL)
	  printf("\nErro ao abrir o arquivo");
	
	else{
	  	for(i=0;i<qtde;i++)
	  	  {
		  	fseek(fptr,i*sizeof(dados),0);
		  	fread(p,sizeof(dados),1,fptr);
		  	
		  	printf("Senha do(a): %s\n"
			  	   "Senha: %s\n", p->lugar, p->senha);
		  	
	      }
	      
	    fclose(fptr);
	  }
	  
	printf("\n\n");
	system("pause");
}
