#include <stdio.h>
#include <stdlib.h>

int main() {
    int students;
    
    printf("Enter the number of students: ");
    if (scanf("%d", &students) != 1 || students <= 0) return 1;
    
    int *grades = (int *)malloc(students * sizeof(int));
    if (grades == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter the grades: ");
    for (int i = 0; i < students; i++) {
        scanf("%d", &grades[i]);
    }
    
    int max = grades[0];
    int min = grades[0];
    
    for (int i = 1; i < students; i++) {
        if (grades[i] > max) max = grades[i];
        if (grades[i] < min) min = grades[i];
    }
    
    printf("Highest grade: %d\n", max);
    printf("Lowest grade: %d\n", min);
    
    free(grades);
    return 0;
}