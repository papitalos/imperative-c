#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Struct para guardar as informações da data
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Struct para guardar as informações do tempo
typedef struct {
    int hour;
    int minute;
} Time;

// Struct para guardar as informações de customers
typedef struct {
    int id;
    char name[100];
    char telephone[50];
    int age;
} Customer;

// Struct para guardar as informações de atividades
typedef struct {
    int id;
    Date date;
    Time start_time;
    char activity_name[60];
    int duration;
    int distance;
    char units[10];
} Activity;

// Struct to store plan information
typedef struct {
    int id;
    Date start_date;
    Time start_time;
    Date end_date;
    Time end_time;
    char activity_name[60];
    int distance;
    char units[10];
} Plan;




// Function para abrir e ler o "customer.txt" file
int ReadCustomerFile(char* filename, Customer* customers, int max_customers) {
    // Abrir arquivo
    FILE* customers_file = fopen(filename, "r");
    if (customers_file == NULL) {
        printf("Error opening customers file\n");
        return 0;
    }

    // Ler as informações do customer
    int num_customers = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), customers_file) != NULL && num_customers < max_customers) {
        // Analisar a linha
        sscanf(buffer, "%d;%[^;];%[^;];%d", &customers[num_customers].id,
            customers[num_customers].name, customers[num_customers].telephone,
            &customers[num_customers].age);
        num_customers++;
    }

    fclose(customers_file);
    return num_customers;
}

// Function para abrir e ler o "activity.txt" file
int ReadActivityFile(char* filename, Activity* activities, int max_activities) {
    // Abrir arquivo
    FILE* activities_file = fopen(filename, "r");
    if (activities_file == NULL) {
        printf("Error opening activities file\n");
        return 0;
    }

    // Ler as informações da activity
    int num_activities = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), activities_file) != NULL && num_activities < max_activities) {
        // Analisar a linha
        sscanf(buffer, "%d;%d-%d-%d;%d:%d;%[^;];%d;%d;%[^;]", &activities[num_activities].id,
            &activities[num_activities].date.day, &activities[num_activities].date.month,
            &activities[num_activities].date.year, &activities[num_activities].start_time.hour,
            &activities[num_activities].start_time.minute, activities[num_activities].activity_name,
            &activities[num_activities].duration, &activities[num_activities].distance, activities[num_activities].units);
        num_activities++;
    }

    fclose(activities_file);
    return num_activities;
}

// Function para abrir e ler o "plan.txt" file
int ReadPlanFile(char* filename, Plan* plans, int max_plans) {
    // Abrir arquivo
    FILE* plans_file = fopen(filename, "r");
    if (plans_file == NULL) {
        printf("Error opening plans file\n");
        return 0;
    }

    // Ler as informações do plan
    int num_plans = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), plans_file) != NULL && num_plans < max_plans) {
        // Analisar a linha
        sscanf(buffer, "%d;%d-%d-%d;%d:%d;%d-%d-%d;%d:%d;%[^;];%d;%[^;]", &plans[num_plans].id,
            &plans[num_plans].start_date.day, &plans[num_plans].start_date.month, &plans[num_plans].start_date.year,
            &plans[num_plans].start_time.hour, &plans[num_plans].start_time.minute, &plans[num_plans].end_date.day,
            &plans[num_plans].end_date.month, &plans[num_plans].end_date.year, &plans[num_plans].end_time.hour,
            &plans[num_plans].end_time.minute, plans[num_plans].activity_name, &plans[num_plans].distance, plans[num_plans].units);
        num_plans++;
    }

    fclose(plans_file);
    return num_plans;
}




//Funções helpers

//Function que compara as datas e os tempos
int CompareDatesAndTimes(Date date1, Time time1, Date date2, Time time2) {
    if (date1.year < date2.year) return -1;//date1 antes date2 (data anterior)
    if (date1.year > date2.year) return 1;//date1 depois date2 (data posterior)

    if (date1.month < date2.month) return -1;
    if (date1.year == date2.year && date1.month > date2.month) return 1;

    if (date1.day < date2.day) return -1;
    if (date1.day > date2.day) return 1;

    if (time1.hour < time2.hour) return -1;
    if (time1.hour > time2.hour) return 1;

    if (time1.minute < time2.minute) return -1;
    if (time1.minute > time2.minute) return 1;

    return 0;
}
// Function que pega SÓ o nome do costumer pelo ID
char* GetCustomerName(int participant_id, Customer* customers, int num_customers) {
    
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].id == participant_id) {
            return customers[i].name;
        }
    }
    return "";
}




// ex4 Function que conta quantos participantes fizeram X atividade fisica no periodo determinado
int CountParticipants(Activity* activities, int num_activities) {
    // Declara variaveis
    Date start_date;
    Time start_time;
    Date end_date;
    Time end_time;
    char activity_name[60];
    int count = 0;

    // Prompt para o usuarios inserir nome da atividade
    printf("Digite o nome da atividade: ");
    scanf("%s", activity_name);

    // Prompt para o usuarios inserir datas e horas
    printf("Insira a data de início (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Insira o horário de início (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);
    system("cls");
    printf("Insira a data de término (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Insira o horário de término (hh:mm):");
    scanf("%d:%d", &end_time.hour, &end_time.minute);


    // Verifica se as atividades estao dentro das datas dadas e conta 
    for (int i = 0; i < num_activities; i++) {
        Activity activity = activities[i];
        if (strcmp(activity.activity_name, activity_name) == 0 &&
            CompareDatesAndTimes(activity.date, activity.start_time, start_date, start_time) >= 0 &&
            CompareDatesAndTimes(activity.date, activity.start_time, end_date, end_time) <= 0) {
            count++;
        }
    }

    return count;
}

// ex5 Function que lista os participantes que fizeram alguma atividade fisica no periodo determinado
void ListParticipants(Activity* activities, int num_activities, Customer* customers, int num_customers) {
    // Declara variaveis
    int start_day, start_month, start_year;
    int end_day, end_month, end_year;
    Date start_date, end_date;

    // Prompt pro usuario introduzir as datas
    printf("Insira a data de início (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_day, &start_month, &start_year);
    start_date = (Date){ start_day, start_month, start_year };

    printf("Insira a data de término (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_day, &end_month, &end_year);
    end_date = (Date){ end_day, end_month, end_year };

    // Aloca espaço para activity_counts variable dando o vallor de num_costumers
    int* activity_counts = malloc(sizeof(int) * num_customers);

    // Cria uma array pra armazenar o contador de activity para cada customer
    for (int i = 0; i < num_customers; i++) {
        activity_counts[i] = 0;
    }

    // Conta o número de atividades que cada customer executou dentro do intervalo determinado
    for (int i = 0; i < num_activities; i++) {
        if (activities[i].date.year > start_date.year && activities[i].date.year < end_date.year) {
            activity_counts[activities[i].id]++;
        }
        else if (activities[i].date.year == start_date.year && activities[i].date.month >= start_date.month) {
            activity_counts[activities[i].id]++;
        }
        else if (activities[i].date.year == end_date.year && activities[i].date.month <= end_date.month) {
            activity_counts[activities[i].id]++;
        }
    }

    // Classifique os customers em ordem decrescente por contagem de atividades
    for (int i = 0; i < num_customers - 1; i++) {
        for (int j = i + 1; j < num_customers; j++) {
            if (activity_counts[i] < activity_counts[j]) {
                //  Troca das contagens das activity
                int temp = activity_counts[i];
                activity_counts[i] = activity_counts[j];
                activity_counts[j] = temp;

                // Troca dos customers
                Customer temp_customer = customers[i];
                customers[i] = customers[j];
                customers[j] = temp_customer;
            }
        }
    }


    // Print da lista de customers
    for (int i = 0; i < num_customers; i++) {
        printf("%d - %s - %d - %s\n", customers[i].id, customers[i].name, customers[i].age, customers[i].telephone);
    }
}

// ex6 Function que mostra os planos de X atividade fisica de X pessoa em X determinado intervalo de tempo
void PresentActivity(Activity* activities, int num_activities, Plan* plans, int num_plans, Customer* customers, int num_customers) {
    // Declara variaveis
    char name[60];
    Date start_date;
    Time start_time;
    Date end_date;
    Time end_time;
    char costumer[100];


    // Prompt pro usuario introduzir as informações
    printf("Insira o tipo de atividade: ");
    scanf("%s", name);

    printf("Insira a data de início (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Insira o horário de início (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);

    system("cls");
    printf("Insira a data de término (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Insira o horário de término (hh:mm): ");
    scanf("%d:%d", &end_time.hour, &end_time.minute);

    system("cls");
    printf("Insira o nome do praticante: ");
    scanf("%s", costumer);

    system("cls");

    //print inicial
    printf("Plano de atividade do tipo %s de %02d-%02d-%04d %02d:%02d até %02d-%02d-%04d %02d:%02d para o praticante %s:\n",
        name, start_date.day, start_date.month, start_date.year, start_time.hour, start_time.minute,
        end_date.day, end_date.month, end_date.year, end_time.hour, end_time.minute, costumer);
    //Verifica de acordo com a quantidade de planos que o cliente tem
    for (int i = 0; i < num_plans; i++) {
        //pega o nome do customer pelo ID usando a funçao GetCustomerName
        char* costumer_name = GetCustomerName(plans[i].id, customers, num_customers);
        //valida as informações
        if (strcmp(plans[i].activity_name, name) == 0 &&
            CompareDatesAndTimes(start_date, start_time, plans[i].start_date, plans[i].start_time) <= 0 &&
            CompareDatesAndTimes(plans[i].end_date, plans[i].end_time, end_date, end_time) <= 0 &&
            strcmp(costumer_name, costumer) == 0) {
            printf("%d. %02d-%02d-%04d %02d:%02d até %02d-%02d-%04d %02d:%02d, distância %d %s\n",
                plans[i].id, plans[i].start_date.day, plans[i].start_date.month, plans[i].start_date.year,
                plans[i].start_time.hour, plans[i].start_time.minute,
                plans[i].end_date.day, plans[i].end_date.month, plans[i].end_date.year,
                plans[i].end_time.hour, plans[i].end_time.minute,
                plans[i].distance, plans[i].units);
        }
        else{   
            printf("ERROR! Cliente Inexistente!");
        }
    }
}

// ex7 Function que calcula o tempo que demora cada atividade num determinadoperiodo de tempo pra um X cliente
void CalcActivitysTime(Customer* customers, int num_customers, Activity* activities, int num_activities) {
    // Declaração de variáveis
    int i, j;
    Date start_date, end_date;
    Time start_time, end_time;
    int customer_id, total_time, avg_time;
    char customer_name[100];

    // Perguntar ao usuário pelo nome do cliente
    printf("Insira o nome do cliente: ");
    scanf("%s", customer_name);

    // Perguntar ao usuário pelas informações de data e hora
    printf("Insira a data de início (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Insira o horário inicio (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);
    system("cls");
    printf("Insira a data de término (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Insira o horário de término (hh:mm): ");
    scanf("%d:%d", &end_time.hour, &end_time.minute);

    // Percorrer a lista de clientes
    for (i = 0; i < num_customers; i++) {
        // Inicializar a variável de tempo total
        total_time = 0;

        // Verificar se o nome do cliente é ígual ao especificado pelo usuário
        if (strcmp(customers[i].name, customer_name) == 0) {
            customer_id = customers[i].id;

            // Percorrer a lista de atividades
            for (j = 0; j < num_activities; j++) {
                // Verificar se a atividade ocorreu durante o período especificado pelo usuário
                // e se o cliente participou da atividade
                if (customers[i].id == activities[j].id &&
                    CompareDatesAndTimes(start_date, start_time, end_date, end_time,
                        activities[j].date, activities[j].start_time) == 0) {
                    // Adicionar o tempo da atividade ao tempo total
                    total_time += activities[j].duration;
                }
            }

            // Calcular o tempo médio
            avg_time = total_time / num_activities;
            // Imprimir o tempo total e o tempo médio para o cliente
            printf("Cliente %s: tempo total = %d minutos, tempo médio = %d minutos\n",
                GetCustomerName(customers, num_customers, customer_id), total_time, avg_time);
        }
    }
}





int main(int argc, char** argv) {

    //setlocale para usar acentuação
    setlocale(LC_ALL, "");
    //variavel de escolha começando em uma impossivel
    int choice = -1;


    //Lê as 3 informações dos 3 files
    // Ler as informações da "Customer.txt" file
    Customer customers[100];
    int num_customers = ReadCustomerFile("customer.txt", customers, 100);

    // Ler as informações da "Activity.txt" file
    Activity activities[100];
    int num_activities = ReadActivityFile("activity.txt", activities, 100);

    // Ler as informações da "Plan.txt" file
    Plan plans[100];
    int num_plans = ReadPlanFile("plan.txt", plans, 100);


    //iniciar programa aparente
    do
    {

        //mostrar opções
        system("cls");
        printf( "\n -----------------------------------"
                "\n | 1 - Procurar atividade          |"
                "\n | 2 - Listar participantes        |"
                "\n | 3 - Mostrar Plano de Atividade  |"
                "\n | 4 - Calcular Tempo de Atividade |"
                "\n | 0 - Sair                        |"
                "\n -----------------------------------"
                "\n > Escolha a sua opcao: ");

        scanf_s("%d", &choice);


        //escolher entre as opções
        switch (choice)
        {
        case 1:
            system("cls");
            printf("Número de clientes encontrados: %d", CountParticipants(activities, num_activities));
            system("pause > nul");
            break;
        case 2:
            system("cls");
            ListParticipants(activities, num_activities, customers, num_customers);
            system("pause > nul");
            break;
        case 3:
            system("cls");
            PresentActivity(activities, num_activities, plans, num_plans, customers, num_customers);
            system("pause > nul");
            break;
        case 4:
            system("cls");
            CalcActivitysTime(customers, num_customers, activities, num_activities);
            system("pause > nul");
            break;
        case 0:
            exit(0);
            break;
        default:

            //caso opção não exista
            system("cls");
            printf("\n ------------------"
                   "\n | Opcao invalida |"
                   "\n ------------------");
            system("pause > nul");
            break;

        }
    } while (choice != 0);
    


    return 0;
}