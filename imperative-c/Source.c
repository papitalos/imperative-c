// Cross-platform compatibility
#ifdef _WIN32
    #define _CRT_SECURE_NO_WARNINGS
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define PAUSE_COMMAND "pause > nul"
    #define SCANF_FUNC scanf_s
#else
    #include <unistd.h>
    #define CLEAR_SCREEN "clear"
    #define PAUSE_COMMAND "read -p 'Press Enter to continue...' dummy"
    #define SCANF_FUNC scanf
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Struct to store date information
typedef struct {
    int day;
    int month;
    int year;
} Date;

// Struct to store time information
typedef struct {
    int hour;
    int minute;
} Time;

// Struct to store customer information
typedef struct {
    int id;
    char name[100];
    char telephone[50];
    int age;
} Customer;

// Struct to store activity information
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




// Function to open and read the "customer.txt" file
int ReadCustomerFile(char* filename, Customer* customers, int max_customers) {
    // Open file
    FILE* customers_file = fopen(filename, "r");
    if (customers_file == NULL) {
        printf("Error opening customers file\n");
        return 0;
    }

    // Read customer information
    int num_customers = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), customers_file) != NULL && num_customers < max_customers) {
        // Parse the line
        sscanf(buffer, "%d;%[^;];%[^;];%d", &customers[num_customers].id,
            customers[num_customers].name, customers[num_customers].telephone,
            &customers[num_customers].age);
        num_customers++;
    }

    fclose(customers_file);
    return num_customers;
}

// Function to open and read the "activity.txt" file
int ReadActivityFile(char* filename, Activity* activities, int max_activities) {
    // Open file
    FILE* activities_file = fopen(filename, "r");
    if (activities_file == NULL) {
        printf("Error opening activities file\n");
        return 0;
    }

    // Read activity information
    int num_activities = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), activities_file) != NULL && num_activities < max_activities) {
        // Parse the line
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

// Function to open and read the "plan.txt" file
int ReadPlanFile(char* filename, Plan* plans, int max_plans) {
    // Open file
    FILE* plans_file = fopen(filename, "r");
    if (plans_file == NULL) {
        printf("Error opening plans file\n");
        return 0;
    }

    // Read plan information
    int num_plans = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), plans_file) != NULL && num_plans < max_plans) {
        // Parse the line
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




// Helper functions

// Function that compares dates and times
int CompareDatesAndTimes(Date date1, Time time1, Date date2, Time time2) {
    if (date1.year < date2.year) return -1;  // date1 before date2 (earlier date)
    if (date1.year > date2.year) return 1;   // date1 after date2 (later date)

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

// Function that gets only the customer name by ID
char* GetCustomerName(int participant_id, Customer* customers, int num_customers) {
    
    for (int i = 0; i < num_customers; i++) {
        if (customers[i].id == participant_id) {
            return customers[i].name;
        }
    }
    return "";
}




// ex4 Function that counts how many participants performed X physical activity in the determined period
int CountParticipants(Activity* activities, int num_activities) {
    // Declare variables
    Date start_date;
    Time start_time;
    Date end_date;
    Time end_time;
    char activity_name[60];
    int count = 0;

    // Prompt for user to enter activity name
    printf("Enter activity name: ");
    scanf("%s", activity_name);

    // Prompt for user to enter dates and times
    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Enter start time (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);
    system(CLEAR_SCREEN);
    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Enter end time (hh:mm): ");
    scanf("%d:%d", &end_time.hour, &end_time.minute);


    // Check if activities are within the given dates and count them
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

// ex5 Function that lists participants who performed some physical activity in the determined period
void ListParticipants(Activity* activities, int num_activities, Customer* customers, int num_customers) {
    // Declare variables
    int start_day, start_month, start_year;
    int end_day, end_month, end_year;
    Date start_date, end_date;

    // Prompt for user to enter dates
    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_day, &start_month, &start_year);
    start_date = (Date){ start_day, start_month, start_year };

    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_day, &end_month, &end_year);
    end_date = (Date){ end_day, end_month, end_year };

    // Allocate space for activity_counts variable with num_customers value
    int* activity_counts = malloc(sizeof(int) * num_customers);

    // Create an array to store the activity counter for each customer
    for (int i = 0; i < num_customers; i++) {
        activity_counts[i] = 0;
    }

    // Count the number of activities each customer performed within the determined interval
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

    // Sort customers in descending order by activity count
    for (int i = 0; i < num_customers - 1; i++) {
        for (int j = i + 1; j < num_customers; j++) {
            if (activity_counts[i] < activity_counts[j]) {
                // Swap activity counts
                int temp = activity_counts[i];
                activity_counts[i] = activity_counts[j];
                activity_counts[j] = temp;

                // Swap customers
                Customer temp_customer = customers[i];
                customers[i] = customers[j];
                customers[j] = temp_customer;
            }
        }
    }


    // Print customer list
    for (int i = 0; i < num_customers; i++) {
        printf("%d - %s - %d - %s\n", customers[i].id, customers[i].name, customers[i].age, customers[i].telephone);
    }

    // Free allocated memory
    free(activity_counts);
}

// ex6 Function that shows plans for X physical activity of X person in X determined time interval
void PresentActivity(Activity* activities, int num_activities, Plan* plans, int num_plans, Customer* customers, int num_customers) {
    // Declare variables
    char name[60];
    Date start_date;
    Time start_time;
    Date end_date;
    Time end_time;
    char customer[100];


    // Prompt for user to enter information
    printf("Enter activity type: ");
    scanf("%s", name);

    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Enter start time (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);

    system(CLEAR_SCREEN);
    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Enter end time (hh:mm): ");
    scanf("%d:%d", &end_time.hour, &end_time.minute);

    system(CLEAR_SCREEN);
    printf("Enter participant name: ");
    scanf("%s", customer);

    system(CLEAR_SCREEN);

    // Initial print
    printf("Activity plan of type %s from %02d-%02d-%04d %02d:%02d to %02d-%02d-%04d %02d:%02d for participant %s:\n",
        name, start_date.day, start_date.month, start_date.year, start_time.hour, start_time.minute,
        end_date.day, end_date.month, end_date.year, end_time.hour, end_time.minute, customer);
    
    // Check according to the number of plans the client has
    for (int i = 0; i < num_plans; i++) {
        // Get customer name by ID using GetCustomerName function
        char* customer_name = GetCustomerName(plans[i].id, customers, num_customers);
        // Validate information
        if (strcmp(plans[i].activity_name, name) == 0 &&
            CompareDatesAndTimes(start_date, start_time, plans[i].start_date, plans[i].start_time) <= 0 &&
            CompareDatesAndTimes(plans[i].end_date, plans[i].end_time, end_date, end_time) <= 0 &&
            strcmp(customer_name, customer) == 0) {
            printf("%d. %02d-%02d-%04d %02d:%02d to %02d-%02d-%04d %02d:%02d, distance %d %s\n",
                plans[i].id, plans[i].start_date.day, plans[i].start_date.month, plans[i].start_date.year,
                plans[i].start_time.hour, plans[i].start_time.minute,
                plans[i].end_date.day, plans[i].end_date.month, plans[i].end_date.year,
                plans[i].end_time.hour, plans[i].end_time.minute,
                plans[i].distance, plans[i].units);
        }
        else{   
            printf("ERROR! Non-existent Client!");
        }
    }
}

// ex7 Function that calculates the time each activity takes in a determined period for a specific client
void CalcActivitysTime(Customer* customers, int num_customers, Activity* activities, int num_activities) {
    // Variable declaration
    int i, j;
    Date start_date, end_date;
    Time start_time, end_time;
    int customer_id, total_time, avg_time;
    char customer_name[100];

    // Ask user for client name
    printf("Enter client name: ");
    scanf("%s", customer_name);

    // Ask user for date and time information
    printf("Enter start date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &start_date.day, &start_date.month, &start_date.year);
    printf("Enter start time (hh:mm): ");
    scanf("%d:%d", &start_time.hour, &start_time.minute);
    system(CLEAR_SCREEN);
    printf("Enter end date (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &end_date.day, &end_date.month, &end_date.year);
    printf("Enter end time (hh:mm): ");
    scanf("%d:%d", &end_time.hour, &end_time.minute);

    // Go through the client list
    for (i = 0; i < num_customers; i++) {
        // Initialize total time variable
        total_time = 0;

        // Check if client name equals the one specified by user
        if (strcmp(customers[i].name, customer_name) == 0) {
            customer_id = customers[i].id;

            // Go through the activity list
            for (j = 0; j < num_activities; j++) {
                // Check if activity occurred during the period specified by user
                // and if the client participated in the activity
                if (customers[i].id == activities[j].id &&
                    CompareDatesAndTimes(activities[j].date, activities[j].start_time, start_date, start_time) >= 0 &&
                    CompareDatesAndTimes(activities[j].date, activities[j].start_time, end_date, end_time) <= 0) {
                    // Add activity time to total time
                    total_time += activities[j].duration;
                }
            }

            // Calculate average time
            avg_time = total_time / num_activities;
            // Print total time and average time for the client
            printf("Client %s: total time = %d minutes, average time = %d minutes\n",
                GetCustomerName(customer_id, customers, num_customers), total_time, avg_time);
        }
    }
}





int main(int argc, char** argv) {

    // setlocale to use accentation
    setlocale(LC_ALL, "");
    // choice variable starting with an impossible value
    int choice = -1;


    // Read the 3 information from the 3 files
    // Read information from "Customer.txt" file
    Customer customers[100];
    int num_customers = ReadCustomerFile("customer.txt", customers, 100);

    // Read information from "Activity.txt" file
    Activity activities[100];
    int num_activities = ReadActivityFile("activity.txt", activities, 100);

    // Read information from "Plan.txt" file
    Plan plans[100];
    int num_plans = ReadPlanFile("plan.txt", plans, 100);


    // Start apparent program
    do
    {

        // Show options
        system(CLEAR_SCREEN);
        printf( "\n -----------------------------------"
                "\n | 1 - Search activity             |"
                "\n | 2 - List participants           |"
                "\n | 3 - Show Activity Plan          |"
                "\n | 4 - Calculate Activity Time     |"
                "\n | 0 - Exit                        |"
                "\n -----------------------------------"
                "\n > Choose your option: ");

        SCANF_FUNC("%d", &choice);


        // Choose between options
        switch (choice)
        {
        case 1:
            system(CLEAR_SCREEN);
            printf("Number of clients found: %d", CountParticipants(activities, num_activities));
            system(PAUSE_COMMAND);
            break;
        case 2:
            system(CLEAR_SCREEN);
            ListParticipants(activities, num_activities, customers, num_customers);
            system(PAUSE_COMMAND);
            break;
        case 3:
            system(CLEAR_SCREEN);
            PresentActivity(activities, num_activities, plans, num_plans, customers, num_customers);
            system(PAUSE_COMMAND);
            break;
        case 4:
            system(CLEAR_SCREEN);
            CalcActivitysTime(customers, num_customers, activities, num_activities);
            system(PAUSE_COMMAND);
            break;
        case 0:
            exit(0);
            break;
        default:

            // If option doesn't exist
            system(CLEAR_SCREEN);
            printf("\n ------------------"
                   "\n | Invalid option |"
                   "\n ------------------");
            system(PAUSE_COMMAND);
            break;

        }
    } while (choice != 0);
    


    return 0;
}