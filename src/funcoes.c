#include <stdio.h>
#include <string.h>
#include "funcoes.h"
#include "modulo.h"

void limpaBuffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int imprimeMenu(){
	printf("===== Carteira de investimentos =====\n");
	printf("1. Cadastrar\n");
	printf("2. Listar\n");
	printf("3. Total\n");
	printf("4. Rentabilidade geral\n");
	printf("5. Ordenar por rentabilidade\n");
	printf("6. Simulador educativo\n");
	printf("7. Relatorio final\n");
	printf("0. Sair\n");
	
	//return capturaOpcao();
}

int capturaOpcao(){
	int opcao;
	scanf("%d", &opcao);
	while (opcao < 0 || opcao > 7){
		printf("Escolha uma opção entre 0 e 7: ");
		scanf("%d", &opcao);
	}
	limpaBuffer();
	return opcao;
}

void cadastrarAtivo(Ativo ativos[], int *total, int tamanho){
	int i = *total;
	if (i >= tamanho){
		printf("Numero maximo de ativos ja alcancado.\n");
		return;
	}
	
	printf("Digite o nome do ativo: ");
	fgets(ativos[i].nome, sizeof(ativos[i].nome), stdin);
	ativos[i].nome[strcspn(ativos[i].nome, "\n")] = '\0';
	printf("Digite a categoria do ativo: ");
	fgets(ativos[i].categoria, sizeof(ativos[i].categoria), stdin);
	ativos[i].categoria[strcspn(ativos[i].categoria, "\n")] = '\0';
	printf("Digite a quantidade compra: ");
	scanf("%d", &ativos[i].quantidade);
	printf("Digite o preco de compra: ");
	scanf("%lf", &ativos[i].precoCompra);
	printf("Digite o preco atual: ");
	scanf("%lf", &ativos[i].precoAtual);
	
	(*total)++;
	salvarCarteira(ativos, *total);
}

void listarAtivos(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	
	printf("\n=== Ativos cadastrados===\n");
	int i;
	for (i = 0; i < totalAtivos; i++){
		printf("%d. %s - %s :\n", i+1, ativos[i].nome, ativos[i].categoria);
		printf("Quantidade possuida: %d\n", ativos[i].quantidade);
		printf("Preco de compra: R$ %.2lf\n", ativos[i].precoCompra);
		printf("Preco atual: R$ %.2lf\n", ativos[i].precoAtual);
		//double total = totalIndividual(ativos, i);
		printf("Valor total atual: R$ %.2lf\n", totalIndividual(ativos, i));
		printf("Rentabilidade: %.2lf%%\n\n", rentabilidadeIndividual(ativos, i));
		
	} 
	
}

double totalIndividual(Ativo ativos[], int indice){
	int i = indice;
	double total = ativos[i].precoAtual * ativos[i].quantidade; 
	
	return total;
}

double rentabilidadeIndividual(Ativo ativos[], int indice){
	int i = indice;
	double rentabilidade = ((ativos[i].precoAtual - ativos[i].precoCompra) / ativos[i].precoCompra) * 100;
	
	return rentabilidade;
}

double total(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	double total = 0;
	int i;
	for(i = 0; i < totalAtivos; i++){
		total += ativos[i].precoAtual * ativos[i].quantidade;
	}
	
	
	return total;
}

void imprimeTotal(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	printf("=== Valor total da carteira ===\n\n");
	printf("A carteira possui um valor total de: R$ %.2lf\n\n", total(ativos, totalAtivos));
}

void rentabilidadeGeral(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	double rentabilidade = 0;
	double valorTotalCompra = 0;
	double valorTotalAtual = 0;
	int i;
	for(i = 0; i < totalAtivos; i++){
		valorTotalCompra += ativos[i].precoCompra * ativos[i].quantidade;
		valorTotalAtual += totalIndividual(ativos, i);
	}
	
	rentabilidade = ((valorTotalAtual - valorTotalCompra) / valorTotalCompra) * 100;
	printf("A rentabilidade geral da carteira e de: %.2lf%%\n", rentabilidade);
}

void imprimeRentabilidade(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	
	printf("=== Rentabilidade Geral ===\n\n");
	rentabilidadeGeral(ativos, totalAtivos);
	printf("\n");
}

void lucro(Ativo ativos[], int totalAtivos){
	double compraTotal = 0;
	double precoAtualTotal = 0;
	
	int i;
	for (i = 0; i < totalAtivos; i++){
		compraTotal += ativos[i].precoCompra * ativos[i].quantidade;
		precoAtualTotal += ativos[i].precoAtual * ativos[i].quantidade;
	}
	
	double balanco = precoAtualTotal - compraTotal;
	
	if (balanco > 0){
		printf("Lucro total: R$ %.2lf\n", balanco);
	} else if (balanco < 0){
		printf("Prejuizo total: R$ %.2lf\n", balanco);
	} else {
		printf("Nao ha lucro nem prejuizo na carteira.\n");
	}
}

void ordenarRentabilidade(Ativo ativos[], int totalAtivos){
	int i, j;
	for (i = 0; i < totalAtivos; i++){
		for (j = 0; j < totalAtivos - 1; j++){
			if (rentabilidadeIndividual(ativos, j) < rentabilidadeIndividual(ativos, j+1)){
				Ativo temp = ativos[j];
				ativos[j] = ativos[j+1];
				ativos[j+1] = temp;
			}
		}
	}
	
	salvarCarteira(ativos, totalAtivos);
}

void imprimeOrdenado(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	
	ordenarRentabilidade(ativos, totalAtivos);
	
	printf("=== Ativos ordenados ===\n\n");
	int i;
	for (i = 0; i < totalAtivos; i++){
		printf("%d. %s - %s - rentabilidade: %.2lf%%\n", i+1, ativos[i].nome, ativos[i].categoria, rentabilidadeIndividual(ativos, i));
	}
	
	printf("\nA carteira possui um valor total de: R$ %.2lf\n", total(ativos, totalAtivos));
	//total(ativos, totalAtivos);
	rentabilidadeGeral(ativos, totalAtivos);
	lucro(ativos, totalAtivos);
}

void simulador(Ativo ativos[], int totalAtivos, double poupanca, double tesouro, double cdb){
	int meses;
	
	printf("=== Simulador educativo ===\n");
	printf("Digite por quantos meses gostaria de aplicar seu dinheiro: ");
	scanf("%d", &meses);
	while (meses < 1){
		printf("Opcao invalida, digite um valor acima de 0: ");
		scanf("%d", &meses);
	}
	
	double valorTotal = total(ativos, totalAtivos);
	double poupancaAplicada = valorTotal, tesouroAplicado = valorTotal, cdbAplicado = valorTotal;
	
	int i;
	for (i = 0; i < meses; i++){
		poupancaAplicada *= (1.0 + poupanca);
		tesouroAplicado *= (1.0 + tesouro);
		cdbAplicado *= (1.0 + cdb);
	}
	
	
	printf("\nSe os seus R$ %.2lf ficassem aplicados por %d mes(es), estes seriam os rendimentos:\n", valorTotal, meses);
	printf("Poupanca       (%.2lf%%/mes): R$ %.2lf (+R$ %.2lf)\n", poupanca * 100, poupancaAplicada, poupancaAplicada - valorTotal);
	printf("Tesouro Selic  (%.2lf%%/mes): R$ %.2lf (+R$ %.2lf)\n", tesouro * 100, tesouroAplicado, tesouroAplicado - valorTotal);
	printf("CDB 100%% CDI   (%.2lf%%/mes): R$ %.2lf (+R$ %.2lf)\n", cdb * 100, cdbAplicado, cdbAplicado - valorTotal);
	
	printf("\n- Poupanca: e a que menos rende, porem e a mais conhecida e muitos aplicam nela por desconhecer\n"); 
	printf("outras opcoes melhores. O rendimento e a cada 30 dias, nao havendo rendimento algum se retirado antes.\n");
	printf("- Tesouro Selic: e um titulo de renda fixa pos-fixado emitiddo pelo governo federal, seu rendimento\n"); 
	printf("acompanha a taxa de jerus Selic, sempre rende mais que a poupanca.\n");
	printf("- CDB 100%% CDI: e um investimento de renda fixa onde quem investe estah emprestando dinheiro ao banco,\n"); 
	printf("o rendimento e diario, muitos CDBs permitem saque a qualquer momento, uma vantagem em relacaoo a poupanca.\n"); 
	printf("Ha um baixissimo risco, mas que e coberto pelo FGC ate R$ 250 mil por CPF.\n\n");
}

void relatorioFinal(Ativo ativos[], int totalAtivos){
	if (totalAtivos < 1){
		printf("Nao ha ativos registrados.\n");
		return;
	}
	
	printf("====== Relatorio final =====\n\n");
	printf("Ativos ordenados:\n");
	ordenarRentabilidade(ativos, totalAtivos);
	int i;
	for (i = 0; i < totalAtivos; i++){
		printf("%d. %s - %s - quantidade: %d - preco de compra: R$ %.2lf - preco atual: R$ %.2lf - rentabilidade: %.2lf%%\n", i+1, ativos[i].nome, ativos[i].categoria, ativos[i].quantidade, ativos[i].precoCompra, ativos[i].precoAtual, rentabilidadeIndividual(ativos, i));
	}
	printf("Valor total: R$ %.2lf\n", total(ativos, totalAtivos));
	rentabilidadeGeral(ativos, totalAtivos);
	lucro(ativos, totalAtivos);
	printf("\n");
}
	printf("===== Impacto Social ====\n\n");
	prinf("Nosso simulador se conecta com o ODS 8, meta 8.10, que fala sobre ampliar o acesso das pessoas a serviços financeiros. Muita gente fica longe do mercado de investimentos por falta de informação ou medo de perder dinheiro, e o programa oferece um lugar seguro pra treinar. A pessoa cadastra os ativos e vê no relatório final a rentabilidade de cada um, o valor total e o lucro, entendendo na prática como a carteira funciona, sem arriscar dinheiro real. Como é simples e não exige conta em corretora, também pode ser usado em escolas e projetos de educação financeira\n")
