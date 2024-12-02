#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 1. Get reports
 * 2. For each report "decide" if it safe or not
 * 3. increment counter for safeness
 */

FILE *read_input()
{
    FILE *fptr;

    if ((fptr = fopen("./input.txt", "r")) == NULL)
    {
        printf("Error!");
        exit(1);
    }

    return fptr;
}

int count_lines(FILE *fptr)
{
    int lines_count = 0;
    char ch;
    while (!feof(fptr))
    {
        ch = fgetc(fptr);
        if (ch == '\n')
        {
            lines_count++;
        }
    }

    rewind(fptr);
    return lines_count;
}

char *get_line(FILE *file)
{
    char ch;
    char *line = NULL;
    int line_size = 0;
    while ((ch = fgetc(file)) != '\n')
    {
        line = realloc(line, sizeof(char) * (line_size + 1));
        line[line_size++] = ch;
    }
    line[line_size] = '\0';
    return line;
}

bool is_line_safe(char *line)
{
    // 1. split the string.
    // 2. convert each with atoi()
    // 3. if prev < current && current-prev <=3 continue
    // 4. if prev == current return 0
    // 5. if pattern changes return 0

    char *token = strtok(line, " ");

    int increasing = 0; // 0: undef, 1: true, 2:false

    int last = atoi(token);
    while ((token = strtok(NULL, " ")) != NULL)
    {
        int curr = atoi(token);

        // Check adjecency rule
        int diff = abs(curr - last);
        if (!(diff >= 1 && diff <= 3))
        {
            return false;
        }

        // Invalid order conditions start
        if (increasing == 0) // Increasing is undefined ?
        {
            if (curr > last)
                increasing = 1;
            else if (curr < last)
                increasing = 2;
        }
        else if (increasing == 2) // Serie is not increasing
        {
            if (curr > last) // Breaks the decreasing order
            {
                return false;
            }
        }
        else if (increasing == 1) // Serie is increasing
        {
            if (curr < last) // Breaks the increasing order
            {
                return false;
            }
        }
        // Invalid order conditions ends

        last = curr;
    }

    return true;
}

bool is_line_safe_with_problem_dampener(char *line)
{
    char *line_copy;
    strcpy(line_copy, line);
}

int puzzle_one(FILE *input)
{
    int input_lines = count_lines(input);
    int safe_count = 0;

    for (int i = 0; i < input_lines; i++)
    {
        char *line = get_line(input);

        bool is_safe = is_line_safe(line);

        if (is_safe)
            safe_count++;

        free(line);
    }

    return safe_count;
}

int puzzle_two(FILE *input)
{
    int input_lines = count_lines(input);
    int safe_count = 0;

    for (int i = 0; i < input_lines; i++)
    {
        char *line = get_line(input);
        bool is_safe = is_line_safe_with_problem_dampener();
        if (is_safe)
            safe_count++;
        free(line);
    }

    return safe_count;
}

int main()
{
    FILE *input_file = read_input();
    int r1 = puzzle_one(input_file);

    printf("Result 1: %d\n", r1);

    return 0;
}