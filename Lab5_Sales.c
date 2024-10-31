#include <stdio.h>
#include <stdlib.h>

#define NUM_MONTHS 12

// Function to read monthly sales from the input file
void read_sales(double sales[]) {
    FILE *file = fopen("monthly_sales.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int read_count = 0;
    for (int i = 0; i < NUM_MONTHS; i++) {
        if (fscanf(file, "%lf", &sales[i]) == 1) {
            read_count++;
        }
    }
    if (read_count != NUM_MONTHS) {
        printf("Error reading sales data from file.\n");
        fclose(file);
        exit(1);
    }

    fclose(file);
}

// Function to generate the sales report
void generate_sales_report(double sales[]) {
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};
    printf("Monthly Sales Report for 2024\n");  // Updated year to 2024
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%-10s $%.2f\n", months[i], sales[i]);  // Adjusted spacing for output
    }
}

// Function to calculate sales summary
void calculate_sales_summary(double sales[], double *min_sale, double *max_sale, double *avg_sale, int *min_month_index, int *max_month_index) {
    *min_sale = sales[0];
    *max_sale = sales[0];
    *avg_sale = 0;
    *min_month_index = 0;
    *max_month_index = 0;

    for (int i = 0; i < NUM_MONTHS; i++) {
        *avg_sale += sales[i];
        if (sales[i] < *min_sale) {
            *min_sale = sales[i];
            *min_month_index = i; // Store index of the month
        }
        if (sales[i] > *max_sale) {
            *max_sale = sales[i];
            *max_month_index = i; // Store index of the month
        }
    }

    *avg_sale /= NUM_MONTHS;
}

// Function to calculate six-month moving averages
void calculate_moving_averages(double sales[], double moving_averages[]) {
    for (int i = 0; i <= NUM_MONTHS - 6; i++) {
        double sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        moving_averages[i] = sum / 6;
    }
}

// Function to generate the sorted sales report
void generate_sorted_sales_report(double sales[]) {
    char *months[] = {"January", "February", "March", "April", "May", "June",
                      "July", "August", "September", "October", "November", "December"};

    // Sort sales and months in descending order
    for (int i = 0; i < NUM_MONTHS - 1; i++) {
        for (int j = i + 1; j < NUM_MONTHS; j++) {
            if (sales[j] > sales[i]) {
                // Swap sales
                double temp = sales[j];
                sales[j] = sales[i];
                sales[i] = temp;
                // Swap months
                char *temp_month = months[j];
                months[j] = months[i];
                months[i] = temp_month;
            }
        }
    }

    printf("Sales Report (Highest to Lowest):\n");
    printf("Month\t\tSales\n");
    for (int i = 0; i < NUM_MONTHS; i++) {
        printf("%-10s $%.2f\n", months[i], sales[i]);  // Adjusted spacing for output
    }
}

int main() {
    double sales[NUM_MONTHS];
    double min_sale, max_sale, avg_sale;
    double moving_averages[NUM_MONTHS - 5];
    int min_month_index, max_month_index;

    read_sales(sales);
    generate_sales_report(sales);
    calculate_sales_summary(sales, &min_sale, &max_sale, &avg_sale, &min_month_index, &max_month_index);
    
    printf("\nSales Summary Report:\n");  // Updated to match your format
    printf("Minimum sales: $%.2f (%s)\n", min_sale, (char *[]){"January", "February", "March", "April", "May", "June",
                                                                 "July", "August", "September", "October", "November", "December"}[min_month_index]);
    printf("Maximum sales: $%.2f (%s)\n", max_sale, (char *[]){"January", "February", "March", "April", "May", "June",
                                                                 "July", "August", "September", "October", "November", "December"}[max_month_index]);
    printf("Average sales: $%.2f\n", avg_sale);

    printf("\nSix-Month Moving Average Report:\n");  // Updated to match your format
    calculate_moving_averages(sales, moving_averages);
    for (int i = 0; i <= NUM_MONTHS - 6; i++) {
        printf("%-10s-%-10s $%.2f\n", (char *[]){"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}[i],
                                              (char *[]){"June", "July", "August", "September", "October", "November", "December"}[i], moving_averages[i]);  // Adjusted to display range
    }
    
    generate_sorted_sales_report(sales);

    return 0;
}
