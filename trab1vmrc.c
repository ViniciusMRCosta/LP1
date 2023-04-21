//VINICIUS MOURA RODRIGUES DA COSTA
//MATRICULA: 201920441911

#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
struct atracao{
	char nome[30];
	char local[30];
	char tipo[30];
	char qualidade[15];
	char resumo[200];
};

void cabecalho();
int criaarquivo();
int addevento(int *regiao);
int lerevento(int *regiao);
int menu();
int escolherR();
char agenda(char *op, int *regiao);
int excluievento();
int alteraevento();
int consultaR();

int main() {
	setlocale(LC_ALL, "Portuguese"); //acentuaçao de acordo com o portugues
	
	if (access("eventos.bin", F_OK) == -1)
	{
		if (criaarquivo()) {
		exit(1);
		}
	}

	if (menu()) {
		exit(1);
	}

	return 0;
}

int criaarquivo() {
	FILE *arquivo;
	arquivo = fopen("eventos.bin", "wb");
	if (arquivo == NULL)
	{
		printf("ERRO AO CRIAR ARQUIVO!");
		return 1;
	}
	fclose(arquivo);
	return 0;
}

int addevento(int *regiao) {
	system("cls");
	FILE *arquivo;
	arquivo = fopen("eventos.bin", "ab");
	if (arquivo == NULL)
	{
		printf("ERRO AO ABRIR ARQUIVO!");
		return 1;
	}
	
	struct atracao evento;
	int operacao;
	switch (*regiao)
	{
		case 1:
			strcpy(evento.local, "Norte");
			break;
	
		case 2:
			strcpy(evento.local, "Nordeste");
			break;

		case 3:
			strcpy(evento.local, "Centro");
			break;

		case 4:
			strcpy(evento.local, "Sudeste");
			break;

		case 5:
			strcpy(evento.local, "Sul");
			break;

		default:
			break;
	}
	do {
		printf("1 - restaurante\n");
		printf("2 - praia\n");
		printf("3 - show\n");
		printf("4 - teatro\n");
		printf("5 - parque\n");
		printf("6 - museu\n");
		printf("Escolha o numero referente ao tipo: ");
		scanf("%d", &operacao);
		switch (operacao)
		{
			case 1:
				strcpy(evento.tipo, "restaurante");
				break;

			case 2:
				strcpy(evento.tipo, "praia");
				break;

			case 3:
				strcpy(evento.tipo, "show");
				break;

			case 4:
				strcpy(evento.tipo, "teatro");
				break;

			case 5:
				strcpy(evento.tipo, "parque");
				break;

			case 6:
				strcpy(evento.tipo, "museu");
				break;

			default:
				printf("ERRO!");
				operacao = 0;
				break;
		}
	} while (operacao == 0);
	do {
		printf("\n");
		printf("1 - otimo\n");
		printf("2 - bom\n");
		printf("3 - regular\n");
		printf("4 - ruim\n");
		printf("5 - pessimo\n");
		printf("6 - caro\n");
		printf("7 - barato\n");
		printf("8 - gratis\n");
		printf("Escolha o numero referente a qualidade: ");
		fflush(stdin);
		scanf("%d", &operacao);
		switch (operacao)
		{
			case 1:
				strcpy(evento.qualidade, "otimo");
				break;

			case 2:
				strcpy(evento.qualidade, "bom");
				break;

			case 3:
				strcpy(evento.qualidade, "regular");
				break;

			case 4:
				strcpy(evento.qualidade, "ruim");
				break;

			case 5:
				strcpy(evento.qualidade, "pessimo");
				break;

			case 6:
				strcpy(evento.qualidade, "caro");
				break;

			case 7:
				strcpy(evento.qualidade, "barato");
				break;

			case 8:
				strcpy(evento.qualidade, "gratis");
				break;

			default:
				printf("ERRO!");
				operacao = 0;
				break;
		}
		printf("\n");
	} while (operacao == 0);
	printf("Insira um resumo: ");
	fflush(stdin);
	fgets(evento.resumo, 200, stdin);

	fwrite(&evento, sizeof(struct atracao), 1, arquivo);

	fclose(arquivo);
	return 0;
}

int lerevento(int *regiao) {
	system("cls");
	FILE *arquivo;
	arquivo = fopen("eventos.bin", "rb");

	struct atracao evento;
	if (arquivo == NULL)
	{
		printf("ERRO AO ABRIR ARQUIVO!");
		return 1;
	}
	
	int index, i;
	printf("Insira o numero referente a posicao do evento desejado: ");
	scanf("%d", &index);
	for ( i = 0; i <= index; i++)
	{
		fread(&evento, sizeof(struct atracao), 1, arquivo);
	}
	printf("regiao: %s\n",evento.local);
	printf("tipo: %s\n", evento.tipo);
	printf("qualidade: %s\n", evento.qualidade);
	printf("resumo: %s\n", evento.resumo);
	printf("pressione enter para voltar ao menu inicial\n");
	getch();
	fclose(arquivo);
	return 0;
}

int menu(){
	cabecalho();
	int op;
	int regiao; // talvez nao seja neccessario
	regiao = escolherR();
	do {
		printf("\n");
		printf("0-Sair  do programa\n");
		printf("1-Mudar Regiao\n");
		printf("2-Consultar Regiao\n"); // ler todos os eventos?
		printf("3-Incluir evento\n");
		printf("4-Alterar evento\n");
		printf("5-Excluir evento\n");
		printf("6-Mostrar um evento\n");
		printf("Escolha o numero referente a operacao desejada: ");
		fflush(stdin);
		scanf("%d", &op);
		switch (op){
			case 0:
				return 0;
				break;

			case 1:
				regiao = escolherR();
				break;
				
			case 2:
				consultaR();
				break;
			case 3:
				if (addevento(&regiao)) {
					return 1;
				}
				break;
				
			case 4:
				alteraevento();
				break;	
				
			case 5:
				excluievento();
				break;
			
			case 6:
				if (lerevento(&regiao)) {
					return 1;
				}
				break;

			default:
				printf("Opção Inválida!\n");
				break;
		}
	}while(op!=0);
	return 0;
}

int escolherR() {
	int operacao;
	do{
		cabecalho();
		printf("1-Região Norte\n");
		printf("2-Região Nordeste\n");
		printf("3-Região Centro-oeste\n");
		printf("4-Região Sudeste\n");
		printf("5-Região Sul\n");
		printf("Escolha o numero referente a regiao desejada: ");
		scanf("%d", &operacao);
		switch (operacao)
		{
		case 1:
			return 1;
			break;
		
		case 2:
			return 2;
			break;
		
		case 3:
			return 3;
			break;
		
		case 4:
			return 4;
			break;
		
		case 5:
			return 5;
			break;

		default:
			operacao = 0;
			break;
		}
	} while (operacao == 0);
	return 0;
}

int excluievento(){
	struct atracao evento;
	int index, i;
	i=0;
	printf("Insira o numero referente a posicao do evento que deseja excluir: ");
	fflush(stdin);
	scanf("%d", &index);
	
	FILE *arquivo;
	FILE *arquivoaux;
	arquivo = fopen("eventos.bin", "rb");
	if (arquivo == NULL)
	{
		printf("ERRO AO CRIAR ARQUIVO 1!");
		return 1;
	}
	
	arquivoaux = fopen("auxiliar.bin","wb");
	if (arquivoaux == NULL)
	{
		printf("ERRO AO CRIAR ARQUIVO 2!\n");
		return 1;
	}
	
	while(fread(&evento,sizeof(struct atracao),1,arquivo) !=NULL){
		if(i==index)
		{
			printf("DESCRICAO DELETADA\n\n");
		}
		else{
			fwrite(&evento,sizeof(struct atracao),1,arquivoaux);
		}
		i++;
	}
	
	fclose(arquivo);
	fclose(arquivoaux);
	
	remove("eventos.bin");
	rename("auxiliar.bin","eventos.bin");

	return 0;
}

int alteraevento(){
	struct atracao eventonovo;
	struct atracao evento;
	int index, i, regiao, operacao;
	i=regiao=0;
	
	printf("Insira o numero referente a posicao do evento que deseja alterar: ");
	fflush(stdin);
	scanf("%d", &index);
	
	FILE *arquivo;
	FILE *arquivoaux;
	arquivo = fopen("eventos.bin", "rb");
	if (arquivo == NULL)
	{
		printf("ERRO AO CRIAR ARQUIVO 1!");
		return 1;
	}
	
	arquivoaux = fopen("auxiliar.bin","wb");
	if (arquivoaux == NULL)
	{
		printf("ERRO AO CRIAR ARQUIVO 2!\n");
		return 1;
	}
	
	while(fread(&evento,sizeof(struct atracao),1,arquivo) !=NULL){
		if(i==index){
			printf("\nlocal da descricao: %s", evento.local);
	
			printf("\n\n1-Região Norte\n");
			printf("2-Região Nordeste\n");
			printf("3-Região Centro-oeste\n");
			printf("4-Região Sudeste\n");
			printf("5-Região Sul\n");
			printf("\npara manter essa informação digite o numero que corresponde a mesma informacao nas opcoes.\n");
			printf("para altera-la digite outro numero.\n");
			printf("Escolha o numero referente a regiao desejada: ");
			scanf("%d", &regiao);
			
			switch (regiao)
			{
				case 1:
					strcpy(eventonovo.local, "Norte");
					break;
			
				case 2:
					strcpy(eventonovo.local, "Nordeste");
					break;
		
				case 3:
					strcpy(eventonovo.local, "Centro");
					break;
		
				case 4:
					strcpy(eventonovo.local, "Sudeste");
					break;
		
				case 5:
					strcpy(eventonovo.local, "Sul");
					break;
		
				default:
					break;
			}
		}
		if(i==index){
			printf("\n");
			printf("\ntipo da descricao: %s", evento.tipo);
			do {
				printf("1 - restaurante\n");
				printf("2 - praia\n");
				printf("3 - show\n");
				printf("4 - teatro\n");
				printf("5 - parque\n");
				printf("6 - museu\n");
				printf("\npara manter essa informação digite o numero que corresponde a mesma informacao nas opcoes.\n");
				printf("para altera-la digite outro numero.\n");
				printf("Escolha o numero referente ao tipo: ");
				fflush(stdin);
				scanf("%d", &operacao);
				switch (operacao)
				{
					case 1:
						strcpy(eventonovo.tipo, "restaurante");
						break;
		
					case 2:
						strcpy(eventonovo.tipo, "praia");
						break;
		
					case 3:
						strcpy(eventonovo.tipo, "show");
						break;
		
					case 4:
						strcpy(eventonovo.tipo, "teatro");
						break;
		
					case 5:
						strcpy(eventonovo.tipo, "parque");
						break;
		
					case 6:
						strcpy(eventonovo.tipo, "museu");
						break;
		
					default:
						printf("ERRO!");
						operacao = 0;
						break;
				}
			} while (operacao == 0);	
		}
		if(i==index){
			printf("\n\ntipo da descricao: %s", evento.qualidade);
			do {
				printf("1 - otimo\n");
				printf("2 - bom\n");
				printf("3 - regular\n");
				printf("4 - ruim\n");
				printf("5 - pessimo\n");
				printf("6 - caro\n");
				printf("7 - barato\n");
				printf("8 - gratis\n");
				printf("\npara manter essa informação digite o numero que corresponde a mesma informacao nas opcoes.\n");
				printf("para altera-la digite outro numero.\n");
				printf("Escolha o numero referente a qualidade: ");
				fflush(stdin);
				scanf("%d", &operacao);
				switch (operacao)
				{
					case 1:
						strcpy(eventonovo.qualidade, "otimo");
						break;
		
					case 2:
						strcpy(eventonovo.qualidade, "bom");
						break;
		
					case 3:
						strcpy(eventonovo.qualidade, "regular");
						break;
		
					case 4:
						strcpy(eventonovo.qualidade, "ruim");
						break;
		
					case 5:
						strcpy(eventonovo.qualidade, "pessimo");
						break;
		
					case 6:
						strcpy(eventonovo.qualidade, "caro");
						break;
		
					case 7:
						strcpy(eventonovo.qualidade, "barato");
						break;
		
					case 8:
						strcpy(eventonovo.qualidade, "gratis");
						break;
		
					default:
						printf("ERRO!");
						operacao = 0;
						break;
				}
			} while (operacao == 0);
		}
			
		if(i==index){
			printf("descricao: %s", evento.resumo);
			printf("\n\n1-SIM\n2-NAO");
			printf("\ndeseja altera-lo?\n");
			fflush(stdin);
			scanf("%d",&operacao);
			if(operacao==1){
				printf("\nInsira um resumo: ");
				fflush(stdin);
				fgets(eventonovo.resumo, 200, stdin);
			}
			else{
				strcpy(eventonovo.resumo,evento.resumo);
			}	
		}
		if(i==index){
			printf("\nDESCRICAO ALTERADA\n\n");
			fwrite(&eventonovo,sizeof(struct atracao),1,arquivoaux);
		}
		else{
			fwrite(&evento,sizeof(struct atracao),1,arquivoaux);
		}
		i++;
	}
	getchar();
	
	fclose(arquivo);
	fclose(arquivoaux);
	
	remove("eventos.bin");
	rename("auxiliar.bin","eventos.bin");
	return 0;
}

int consultaR(){
	int op;
	printf("\n");
	printf("1-Região Norte\n");
	printf("2-Região Nordeste\n");
	printf("3-Região Centro-oeste\n");
	printf("4-Região Sudeste\n");
	printf("5-Região Sul\n");
	printf("Informe o numero referente a região desejada: ");
	scanf("%d", &op);
	switch (op){
		case 1:
			printf("RESUMO SOBRE A REGIAO NORTE\n\n");
			printf("pressione enter para voltar");
			getch();
			escolherR();
			break;
			
		case 2:
			printf("RESUMO SOBRE A REGIAO NORDESTE\n\n");
			printf("pressione enter para voltar");
			getch();
			escolherR();
			break;
			
		case 3:
			printf("RESUMO SOBRE A REGIAO CENTRO-OESTE\n");
			printf("pressione enter para voltar");
			getch();
			escolherR();
			break;
			
		case 4:
			printf("RESUMO SOBRE A REGIAO SUDESTE\n");
			printf("pressione enter para voltar");
			getch();
			escolherR();
			break;
			
		case 5:
			printf("RESUMO SOBRE A REGIAO SUL\n");
			printf("pressione enter para voltar");
			getch();
			escolherR();
			break;
	}
	
	return 0;	
}

void cabecalho(){
	system("cls");
	printf("------------------------------\n");
	printf(" MENU DE ATRAÇÕES TURÍSTICAS\n");
	printf("------------------------------\n\n");
}

