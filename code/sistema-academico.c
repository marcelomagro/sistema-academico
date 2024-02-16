#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//M�DIA = ((nota1*1)+(nota2*2)+(nota3*3))/6

//Definindo a estrutura para representar um aluno
struct Aluno{
    char nome[100];
    float notas[3];
};

//Definindo a estrutura para representar uma turma
struct Turma{
    int codigo_disciplina; //Utilizamos valores de inteiro para o c�digo de disciplina, afim de facilitar o processo de busca e armazenamento
    char nome_disciplina[100];
    char professor[100];
    int qtd_alunos;
    int capacidade_alunos;
    struct Aluno *alunos; //Ponteiro para armazenar os alunos da turma
    char horario_inicio[10];
    char horario_fim[10];
    int num_sala;
    int carga_horaria;
};

//Fun��o para definir as informa��es da turma
void info_turma(struct Turma turmas[], int *qtd_turmas){
    printf("\nDigite o codigo da disciplina (N�mero inteiro): ");
    scanf("%d", &turmas[*qtd_turmas].codigo_disciplina);
    
	getchar(); //Limpa o buffer do teclado

    printf("Digite o nome da disciplina: ");
	fgets(turmas[*qtd_turmas].nome_disciplina, 100, stdin);
	//turmas[*qtd_turmas].nome_disciplina[strcspn(turmas[*qtd_turmas].nome_disciplina, "\n")] = 0; //tentativa remo��o de linha adicional do fgets
	strtok(turmas[*qtd_turmas].nome_disciplina, "\n"); //essa funcionou melhor; remo��o de linha adicional do fgets

	printf("Digite o nome do professor: ");
	fgets(turmas[*qtd_turmas].professor, 100, stdin);
	strtok(turmas[*qtd_turmas].professor, "\n");
	
    printf("Digite a quantidade de alunos: ");
    scanf("%d", &turmas[*qtd_turmas].capacidade_alunos);

    turmas[*qtd_turmas].alunos = malloc(turmas[*qtd_turmas].capacidade_alunos * sizeof(struct Aluno)); //Aloca mem�ria para armazenar os alunos da turma
    if(turmas[*qtd_turmas].alunos == NULL){ //Verifica se a aloca��o de mem�ria deu certo
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    printf("Digite o hor�rio de in�cio da disciplina: ");
    scanf("%s", turmas[*qtd_turmas].horario_inicio);

    printf("Digite o hor�rio de fim da disciplina: ");
    scanf("%s", turmas[*qtd_turmas].horario_fim);

    printf("Digite o numero da sala: ");
    scanf("%d", &turmas[*qtd_turmas].num_sala);

    printf("Digite a carga hor�ria da disciplina: ");
    scanf("%d", &turmas[*qtd_turmas].carga_horaria);

    turmas[*qtd_turmas].qtd_alunos = 0; //Inicializa a quantidade de alunos em 0

    (*qtd_turmas)++; //Incrementa o contador de turmas
    printf("\nInforma��es da turma definidas com sucesso!\n");
}

//Fun��o para exibir todas as turmas cadastradas
void exibir_turmas(struct Turma turmas[], int qtd_turmas){
    if(qtd_turmas == 0){ //Verifica se h� alguma turma
        printf("\nNenhuma turma cadastrada no momento.\n");
        return;
    }

    printf("\nTurmas cadastradas:\n");
    
    int i;
    
    for(i = 0; i < qtd_turmas; i++){ //Itera todas as turmas cadastradas
        printf("\nTurma %d:\n", i + 1);
        printf("C�digo da disciplina: %d\n", turmas[i].codigo_disciplina);
        printf("Nome da disciplina: %s\n", turmas[i].nome_disciplina);
        printf("Professor: %s\n", turmas[i].professor);
        printf("Quantidade de alunos: %d\n", turmas[i].capacidade_alunos);
        printf("Hor�rio de in�cio: %s\n", turmas[i].horario_inicio);
        printf("Hor�rio de fim: %s\n", turmas[i].horario_fim);
        printf("N�mero da sala: %d\n", turmas[i].num_sala);
        printf("Carga hor�ria: %d\n", turmas[i].carga_horaria);
    }
}

//Fun��o para inserir aluno e notas
void alunos_notas(struct Turma turmas[], int qtd_turmas){
    int codigo_disciplina, i, j;
	char nome_aluno[100];
	
    printf("\nDigite o c�digo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for(i = 0; i < qtd_turmas; i++){ //Itera sobre as turmas cadastradas
        if(turmas[i].codigo_disciplina == codigo_disciplina){ //Verifica se a turma atual corresponde ao c�digo da disciplina
            if(turmas[i].qtd_alunos < turmas[i].capacidade_alunos){
                printf("Digite o nome do aluno: ");
				getchar(); //Limpa o buffer do teclado antes de ler a string
                fgets(nome_aluno, 100, stdin);
                strtok(nome_aluno, "\n"); //Remove a quebra de linha no final do nome por conta do fgets

                struct Aluno aluno; //Cria uma nova vari�vel do tipo struct Aluno para armazenar temporariamente as informa��es do novo aluno a ser cadastrado
                
                printf("Digite as notas do aluno(de 0 a 10):\n");
                for(j = 0; j < 3; j++){ //Loop para inserir as notas do aluno
                    while(1){ //Loop para verificar se a nota inserida est� dentro do intervalo v�lido
                        printf("Nota %d: ", j + 1);
                        scanf("%f", &aluno.notas[j]);
                        if(aluno.notas[j] < 0 || aluno.notas[j] > 10){
                            printf("Nota inv�lida. Digite uma nota entre 0 e 10.\n");
                        } else{
                            break;
                        }
                    }
                }
                strcpy(aluno.nome, nome_aluno); //Copia o nome do aluno para a struct de aluno
                turmas[i].alunos[turmas[i].qtd_alunos] = aluno; //Adiciona o aluno a lista de alunos da turma
                turmas[i].qtd_alunos++;
                
                printf("\nAluno cadastrado!\n");
            } else{
                printf("Limite de alunos atingido para essa disciplina.\n");
            }
            return;
        }
    }
    printf("\nC�digo de disciplina inv�lido.\n");
}

//Fun��o para exibir alunos e m�dias
void exibir_alunos(struct Turma turmas[], int qtd_turmas){
    int codigo_disciplina, i, j;

    printf("\nDigite o c�digo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for(i = 0; i < qtd_turmas; i++){
        if(turmas[i].codigo_disciplina == codigo_disciplina){
            printf("\nAlunos cadastrados na disciplina %s:\n", turmas[i].nome_disciplina);
            for(j = 0; j < turmas[i].qtd_alunos; j++){ //Itera sobre todos os alunos da turma atual
                printf("Aluno: %s\n", turmas[i].alunos[j].nome); //Exibe o nome
                printf("Notas: %.2f, %.2f, %.2f\n", turmas[i].alunos[j].notas[0], turmas[i].alunos[j].notas[1], turmas[i].alunos[j].notas[2]); //Exibe as notas
                float media =(turmas[i].alunos[j].notas[0] * 1 + turmas[i].alunos[j].notas[1] * 2 + turmas[i].alunos[j].notas[2] * 3) / 6.0; //C�lculo da m�dia do aluno
                printf("M�dia: %.2f\n\n", media);
            }
            return;
        }
    }
    printf("\nC�digo de disciplina inv�lido.\n");
}

//Fun��o para exibir alunos aprovados
void alunos_aprovados(struct Turma turmas[], int qtd_turmas){
    int codigo_disciplina, i, j;
    
    printf("\nDigite o c�digo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for(i = 0; i < qtd_turmas; i++){
        if(turmas[i].codigo_disciplina == codigo_disciplina){ //Verifica se a turma corresponde ao c�digo
            printf("\nAlunos aprovados na disciplina %s:\n", turmas[i].nome_disciplina); //Mostra o nome da disciplina de acordo com o c�digo fornecido
            for(j = 0; j < turmas[i].qtd_alunos; j++){ //Itera sobre todos os alunos da turma atual
                float media =(turmas[i].alunos[j].notas[0] * 1 + turmas[i].alunos[j].notas[1] * 2 + turmas[i].alunos[j].notas[2] * 3) / 6.0; //C�lculo da m�dia do aluno
                if(media >= 7.0){ //Notas maiores ou iguais a 7 s�o aprovativas
                    printf("Aluno: %s, M�dia: %.2f\n", turmas[i].alunos[j].nome, media); //Exibe o nome e a m�dia do aluno
                }
            }
            return;
        }
    }
    printf("\nC�digo de disciplina invalido.\n");
}

//Fun��o para exibir alunos reprovados
//Essa fun��o segue a mesma l�gica da anterior, apenas foi alterada a sa�da de acordo com o valor de m�dia
void alunos_reprovados(struct Turma turmas[], int qtd_turmas){
    int codigo_disciplina, i, j;
    
    printf("\nDigite o c�digo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for(i = 0; i < qtd_turmas; i++){
        if(turmas[i].codigo_disciplina == codigo_disciplina){
            printf("\nAlunos reprovados na disciplina %s:\n", turmas[i].nome_disciplina);
            for(j = 0; j < turmas[i].qtd_alunos; j++){
                float media =(turmas[i].alunos[j].notas[0] * 1 + turmas[i].alunos[j].notas[1] * 2 + turmas[i].alunos[j].notas[2] * 3) / 6.0; //C�lculo da m�dia
                if(media < 7.0){ //Notas menores que 7 s�o reprovativas
                    printf("Aluno: %s, M�dia: %.2f\n", turmas[i].alunos[j].nome, media);
                }
            }
            return;
        }
    }
    printf("\nCodigo de disciplina invalido.\n");
}

//Fun��o para alterar notas de aluno
void alterar_notas_aluno(struct Turma turmas[], int qtd_turmas){
    int codigo_disciplina, i, j, num_aluno, num_nota;
    
    printf("\nDigite o c�digo da disciplina: ");
    scanf("%d", &codigo_disciplina);

    for(i = 0; i < qtd_turmas; i++){
        if(turmas[i].codigo_disciplina == codigo_disciplina){ //Verifica se a turma corresponde ao c�digo
            printf("\nAlunos cadastrados na disciplina %s:\n", turmas[i].nome_disciplina);
            for(j = 0; j < turmas[i].qtd_alunos; j++){ //Itera sobre todos os alunos cadastrados na turma e exibe as informa��es dos mesmos
                printf("%d. Aluno: %s, Notas: %.2f, %.2f, %.2f\n", j + 1, turmas[i].alunos[j].nome, turmas[i].alunos[j].notas[0], turmas[i].alunos[j].notas[1], turmas[i].alunos[j].notas[2]);
            }

            printf("\nDigite o n�mero do aluno que deseja alterar as notas: "); //Solicita o n�mero do aluno que deseja alterar a nota
            scanf("%d", &num_aluno);
            if(num_aluno <= 0 || num_aluno > turmas[i].qtd_alunos){ //Verifica se o n�mero � v�lido
                printf("N�mero de aluno inv�lido.\n");
                return;
            }

            printf("Digite o n�mero da nota que deseja alterar(1, 2 ou 3): "); //Pergunta qual nota deve ser alterada
            scanf("%d", &num_nota);
            if(num_nota < 1 || num_nota > 3){ //Verifica se foi digitado um valor v�lido
                printf("N�mero de nota inv�lido.\n");
                return;
            }

            printf("Digite a nova nota: ");
            scanf("%f", &turmas[i].alunos[num_aluno - 1].notas[num_nota - 1]); //Pede que o usu�rio digite a nova nota e logo em seguida armazena ela no lugar correspondente
            if(turmas[i].alunos[num_aluno - 1].notas[num_nota - 1] < 0 || turmas[i].alunos[num_aluno - 1].notas[num_nota - 1] > 10){ //Verifica se a nota � v�lida (0-10)
                printf("Nota inv�lida. Insira uma nota entre 0 e 10.\n");
                return;
            }

            printf("\nNota alterada com sucesso!\n");
            return;
        }
    }
    printf("\nC�digo de disciplina inv�lido.\n");
}

//Fun��o para salvar os dados em formato de texto
void salvar_dados_texto(struct Turma turmas[], int qtd_turmas){
    FILE *arq; //Ponteiro para o arquivo
    
    arq = fopen("dados_academico.txt", "w"); //Abre o arquivo para escrever
    
    if(arq == NULL){ //Verifica se houve algum erro ao tentar abrir o arquivo
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arq, "Dados das disciplinas:\n"); //Um pequeno t�tulo na parte inicial do arquivo
    
    int i, j;
    
    for(i = 0; i < qtd_turmas; i++){ //Itera sobre as turmas
    	//Escreve informa��es sobre a disciplina no arquivo
        fprintf(arq, "\nDisciplina: %s\n", turmas[i].nome_disciplina);
        fprintf(arq, "Carga hor�ria: %d\n", turmas[i].carga_horaria);
        fprintf(arq,"Hor�rio de in�cio: %s\n", turmas[i].horario_inicio);
        fprintf(arq, "Hor�rio de fim: %s\n", turmas[i].horario_fim);
        fprintf(arq, "Professor: %s\n", turmas[i].professor);
        fprintf(arq, "Quantidade de alunos: %d\n", turmas[i].qtd_alunos);
        for(j = 0; j < turmas[i].qtd_alunos; j++){ //Itera sobre todos os alunos da turma atual
            float media =(turmas[i].alunos[j].notas[0] * 1 + turmas[i].alunos[j].notas[1] * 2 + turmas[i].alunos[j].notas[2] * 3) / 6.0; //Calcula a m�dia do aluno atual
            fprintf(arq, "Aluno: %s| Notas: %.2f - %.2f - %.2f| M�dia: %.2f\n", turmas[i].alunos[j].nome, turmas[i].alunos[j].notas[0], turmas[i].alunos[j].notas[1], turmas[i].alunos[j].notas[2], media); //Escreve as informa��es do aluno atual
        }
    }

    fclose(arq); //Fecha o arquivo ap�s a escrita dos dados
    printf("\nDados salvos em formato de texto com sucesso!\n");
}

//Fun��o para salvar os dados em formato bin�rio
void salvar_dados_binario(struct Turma turmas[], int qtd_turmas){
    FILE *arq; //Ponteiro para o arquivo
    
    arq = fopen("dados_academico.bin", "wb"); //Abre o arquivo para escrever em bin�rio
    
    if(arq == NULL){ //Verifica se houve erro
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

	int i;
	
    for(i = 0; i < qtd_turmas; i++){//Itera sobre as turmas
        fwrite(&turmas[i], sizeof(struct Turma), 1, arq); //Escreve no arquivo os dados da turma atual
        fwrite(turmas[i].alunos, sizeof(struct Aluno), turmas[i].qtd_alunos, arq); //Escreve no arquivo os dados dos alunos da turma atual
    }

    fclose(arq); //Fecha o arquivo
    printf("\nDados salvos em formato binario com sucesso!\n");
}

//Fun��o para exibir o menu
void menu(){
    printf("\n===============MENU=================\n");
    printf("| 1- Definir informa��es da turma  |\n");
    printf("| 2- Exibir turmas                 |\n");
    printf("| 3- Inserir aluno e notas         |\n");
    printf("| 4- Exibir alunos e m�dias        |\n");
    printf("| 5- Exibir alunos aprovados       |\n");
    printf("| 6- Exibir alunos reprovados      |\n");
    printf("| 7- Alterar notas de aluno        |\n");
    printf("| 8- Salvar dados em texto         |\n");
    printf("| 9- Salvar dados em bin�rio       |\n");
    printf("| 0- Encerrar o programa           |\n");
    printf("====================================\n");
}

int main(){
	setlocale(LC_ALL, "portuguese"); //Alterando o idioma do cmd
	
    int opcao, i;
    struct Turma turmas[10]; //Definindo o n�mero m�ximo de turmas
    int qtd_turmas = 0; //Contador de turmas adicionadas

    do{
        menu();
        printf("\nOp��o: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                info_turma(turmas, &qtd_turmas); //Chamada da fun��o(info_turma)
                break;
            case 2:
                exibir_turmas(turmas, qtd_turmas); //Chamada da fun��o(exibir_turmas)
                break;
            case 3:
                alunos_notas(turmas, qtd_turmas); //Chamada da fun��o(alunos_notas)
                break;
            case 4:
                exibir_alunos(turmas, qtd_turmas); //Chamada da fun��o(exibir_alunos)
                break;
            case 5:
                alunos_aprovados(turmas, qtd_turmas); //Chamada da fun��o(alunos_aprovados)
                break;
            case 6:
                alunos_reprovados(turmas, qtd_turmas); //Chamada da fun��o(alunos_reprovados)
                break;
            case 7:
                alterar_notas_aluno(turmas, qtd_turmas); //Chamada da fun��o(alterar_notas_aluno)
                break;
            case 8:
                salvar_dados_texto(turmas, qtd_turmas); //Chamada da fun��o(salvar_dados_texto)
                break;
            case 9:
                salvar_dados_binario(turmas, qtd_turmas); //Chamada da fun��o(salvar_dados_binario)
                break;
            case 0:
                printf("Saindo... At� mais!\n");
                break;
            default:
                printf("OP��O INV�LIDA!\n");
                break;
        }
    } while(opcao != 0); //Enquanto a op��o for diferente de zero, o do while ir� continuar rodando a fun��o menu()

    //Liberando mem�ria alocada
    for(i = 0; i < qtd_turmas; i++){
        free(turmas[i].alunos);
    }

    return 0;
}
