#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
void allocate_array(int **array, int *rows, int *col)
{
  int number;
  for (int i = 0; i < *rows; i++)
  {
    array[i] = (int *)malloc(*col * sizeof(int));

    for (int j = 0; j < *col; j++)
    {

      scanf("%d", &number);
      array[i][j] = number;
    }
  }


}

void print_arr(int **array, int *rows, int *col)
{
  for (int i = 0; i < *rows; i++)
  {

    for (int j = 0; j < *col; j++)
    {

      printf("%d", array[i][j]);
    }

    printf("\n");
  }
}

void main()
{
  int n, m;

  scanf("%d %d", &n, &m);

  int **array = (int **)malloc(n * sizeof(int *));

  allocate_array(array, &n, &m);

  print_arr(array, &n, &m);
}
 */

/* int SaveToFile(const int *arr, int count, const char *fileName)
{

  FILE *file = fopen(fileName, "w");
  if (file == NULL)
  {
    printf("cant open file");
    return 0;
  }

  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%d\n", *(arr + i));
  }

  return 1;
}

int GenerateNumbers(int *N, int *M, int *arr)
{
  int numberOfItems = 0;
  for (int i = *N; i <= *M; i++)
  {
    if (i % 3 == 0)
    {
      *(arr + numberOfItems) = i;

      numberOfItems++;
    }
  }

  if (numberOfItems)
  {
    return numberOfItems;
  }

  else
  {
    return 0;
  }
}

int main()
{

  int N, M;

  scanf("%d %d", &N, &M);

  if (N > M || N == 0 || M == 0)
  {
    return 0;
  }

  int *array = (int *)malloc((M - N) * sizeof(int));

  int numberOfItems = GenerateNumbers(&N, &M, array);

  if (numberOfItems == 0)
  {
    printf("no valid numbers found");
  }
  else
  {
    printf("Generated %d numbers divisible by 3\n ", numberOfItems);
  }

  (SaveToFile(array, numberOfItems, "!!!output.txt")) == 1 ? printf("Numbers saved successfully") : printf("File saving failed");
} */

struct PersonDetails
{
  char name[100];
  char street[100];
  int postalCode;
  int phoneNumber;
};

void main()
{

  struct PersonDetails persons[10] = {
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
      {"John", "Stare Grunty", 04201, 12345678},
  };

  for (int i = 0; i < 10; i++)
  {
    printf("Name: %s, street %s, postal code %d, phoneNumber %d\n", persons[i].name, persons[i].street, persons[i].postalCode, persons[i].phoneNumber);
  }
}
