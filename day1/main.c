#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 1. Get file inputs in 2 arrays A, B
 * 2. Sort the arrays
 * 3. Read the arrays index by index
 * 4. Add distances to another array C
 * 5. Calculate the sum of the array C
 */

FILE* read_input(){
    FILE *fptr;

    if ((fptr = fopen("./input.txt", "r")) == NULL){
        printf("Error!");
        exit(1);
    }
    
    return fptr;
}

int count_lines(FILE *fptr){
    int lines_count = 0;
    char ch;
    while((ch = fgetc(fptr)) != EOF){
        if (ch == '\n') lines_count++;
    }

    rewind(fptr);
    return lines_count;
}

int compare(const void*a, const void *b){
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );
     
     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int calc_difference(int a, int b){
    if (a < b) return b - a;
    if (b < a) return a - b;
    return 0;
}

int sum(int a[], size_t size){
    int s = 0;
    for (int i = 0; i < size; i++){
        s += a[i];
    }
    return s;
}

int puzzle_one(int A[], int B[], FILE * input_file, int file_lines){
    char ch;
    int on_line = 0;

    char * line = malloc(sizeof(char) * 16); // 5 + 3 + 5 + 1

    // Build the arrays A and B.
    while (on_line<file_lines)
    {
        int line_index = 0;
        while((ch=fgetc(input_file)) != '\n'){
            line[line_index++] = ch;
        }

        char *delim = "   \0";
        char* token = strtok(line, delim);
        A[on_line] = atoi(token);
        token = strtok(NULL, delim);
        B[on_line] = atoi(token);

        on_line++;
    }

    // Sort A
    qsort(A, file_lines, sizeof(int), compare);

    // Sort B
    qsort(B, file_lines, sizeof(int), compare);

    int C[file_lines] = {};

    // Calcuale differences between A and B values
    for (int i = 0; i < file_lines; i++){
        C[i] = calc_difference(A[i], B[i]);
    }

    int sum_value = sum(C, file_lines);

    free(line);
    return sum_value;
}

int puzzle_two(int A[], int B[], int file_lines){
    int similarity_score = 0; 
    
    for (int i = 0; i < file_lines; i++){
        int el = A[i];
        int occurrencies_in_B = 0;

        for (int j = 0; j < file_lines; j++){
            if (B[j] == el) occurrencies_in_B++;
        }

        similarity_score += el * occurrencies_in_B;
    }

    return similarity_score;
}



int main(){
    FILE * input_file = read_input();
    int file_lines = count_lines(input_file);

    int A[file_lines] = {};
    int B[file_lines] = {};

    int res1 = puzzle_one(A, B, input_file, file_lines);
    int res2 = puzzle_two(A, B, file_lines);

    return 0;
}
