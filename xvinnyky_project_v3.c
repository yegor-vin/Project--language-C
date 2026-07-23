#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkFiles(FILE **sudoku, FILE **solutions, FILE **players)
{

  if (*sudoku == NULL && *solutions == NULL && *players == NULL)
  {
    *sudoku = fopen("Sudoku.txt", "r");
    *solutions = fopen("SolutionsRegister.txt", "r");
    *players = fopen("PlayersRegister.txt", "r");
  }

  if (*sudoku == NULL || *solutions == NULL || *players == NULL)
  {
    printf("V1: unopened txt files\n");
    return;
  }

  char string[100];

  while ((fgets(string, sizeof(string), *players)) != NULL)
  {

    string[strcspn(string, "\n")] = 0;

    char *separator = strtok(string, "#");
    int dataType = 0;
    char Identificator[100];
    while (separator != NULL)
    {

      switch (dataType)
      {
      case 0:
        strcpy(Identificator, separator);
        printf("Identificator: %s\n", separator);
        break;
      case 1:
        printf("First and last name: %s\n", separator);
        break;

      case 2:
        printf("country: %s\n", separator);
        break;

      case 3:
        printf("Year: %s\n", separator);
        break;

      default:
        break;
      }

      dataType++;
      separator = strtok(NULL, "#");
    }

    rewind(*solutions);
    char playerSol[250];

    while (fgets(playerSol, sizeof(playerSol), *solutions) != NULL)
    {
      playerSol[strcspn(playerSol, "\n")] = 0;

      if (strstr(playerSol, Identificator) != NULL)
      {
        printf("Sample: %s\n", playerSol);

        break;
      }
    }

    printf("\n");
  }

  rewind(*solutions);
  rewind(*sudoku);
  rewind(*players);
}

int checkCorrectnessOfIdentificatorByNumbers(char *a)
{

  for (int i = 4; i < 8; i++)
  {
    if (!(a[i] >= '0' && a[i] <= '9'))
    {
      return 0;
    }
  }
  return 1;
}

void findGame(FILE *solutions)
{

  char *gameIdentificator = (char *)malloc(10 * sizeof(char));
  printf("enter identifier in format(SIDA0001)\n");
  scanf("%s", gameIdentificator);

  if (strlen(gameIdentificator) != 8)
  {
    printf("H: Incorrect identifier\n");
    return;
  }
  else if (strncmp(gameIdentificator, "SID", 3) != 0 || !(gameIdentificator[3] >= 'A' && gameIdentificator[3] <= 'Z') || checkCorrectnessOfIdentificatorByNumbers(gameIdentificator) == 0)
  {
    printf("H: Incorrect identifier\n");
    return;
  }
  else
  {
    FILE *output = fopen("Output_H.txt", "w");

    int stringsAdded = 0;
    char currentString[100];
    while (fgets(currentString, sizeof(currentString), solutions) != NULL)
    {
      currentString[strcspn(currentString, "\n")] = 0;

      if (strstr(currentString, gameIdentificator) != NULL)
      {
        fprintf(output, "%s\n", currentString);
        stringsAdded++;
      }
    }

    if (stringsAdded == 0)
    {

      printf("H: Unopened txt file.\n");
    }
    else
    {

      printf("H: Summary successfully created.\n");
    }

    fclose(output);
  }

  free(gameIdentificator);

  rewind(solutions);
}

void createDynamicArraysWithIndividualInfo(char ***arrayOfSudoku, char ***arrayOfSolutions, char ***arrayOfPlayers, int *numberOfSudoku, int *numberOfSolutions, int *numberOfPlayers, FILE *sudoku, FILE *solutions, FILE *players)
{

  if (sudoku == NULL || solutions == NULL || players == NULL)
  {

    printf("N: File not open\n");
    return;
  }

  if (*(arrayOfSudoku) != NULL || *(arrayOfSolutions) != NULL || *(arrayOfPlayers) != NULL)
  {
    for (int i = 0; i < *numberOfSudoku; i++)
    {
      free(arrayOfSudoku[i]);
    }
    free(arrayOfSudoku);
    *arrayOfSudoku = NULL;

    for (int i = 0; i < *numberOfSolutions; i++)
    {
      free(arrayOfSolutions[i]);
    }
    free(arrayOfSolutions);
    *arrayOfSolutions = NULL;

    for (int i = 0; i < *numberOfPlayers; i++)
    {
      free(arrayOfPlayers[i]);
    }
    free(arrayOfPlayers);
    *arrayOfPlayers = NULL;
  }

  *numberOfSudoku = 0;
  *numberOfSolutions = 0;
  *numberOfPlayers = 0;

  char sudokuString[256];
  while (fgets(sudokuString, sizeof(sudokuString), sudoku) != NULL)
  {
    sudokuString[strcspn(sudokuString, "\n")] = '\0';
    if (strlen(sudokuString) > 0)
    {
      (*numberOfSudoku)++;
    }
  }

  char solutionString[256];

  while (fgets(solutionString, sizeof(solutionString), solutions) != NULL)
  {
    solutionString[strcspn(solutionString, "\n")] = '\0';
    if (strlen(solutionString) > 0)
    {
      (*numberOfSolutions)++;
    }
  }

  char playerString[256];

  while (fgets(playerString, sizeof(playerString), players) != NULL)
  {
    playerString[strcspn(playerString, "\n")] = '\0';
    if (strlen(playerString) > 0)
    {

      (*numberOfPlayers)++;
    }
  }

  rewind(sudoku);
  rewind(solutions);
  rewind(players);

  *arrayOfSudoku = (char **)malloc((*numberOfSudoku) * sizeof(char *));
  *arrayOfSolutions = (char **)malloc((*numberOfSolutions) * sizeof(char *));
  *arrayOfPlayers = (char **)malloc((*numberOfPlayers) * sizeof(char *));

  for (int i = 0; i < *numberOfSudoku; i++)
  {
    fgets(sudokuString, sizeof(sudokuString), sudoku);

    *((*arrayOfSudoku) + i) = (char *)malloc(strlen(sudokuString) + 1);
    strcpy(*((*arrayOfSudoku) + i), sudokuString);
  }

  for (int i = 0; i < *numberOfSolutions; i++)
  {
    fgets(solutionString, sizeof(solutionString), solutions);

    *((*arrayOfSolutions) + i) = (char *)malloc(strlen(solutionString) + 1);
    strcpy(*((*arrayOfSolutions) + i), solutionString);
  }

  for (int i = 0; i < *numberOfPlayers; i++)
  {
    fgets(playerString, sizeof(playerString), players);

    *((*arrayOfPlayers) + i) = (char *)malloc(strlen(playerString) + 1);
    strcpy(*((*arrayOfPlayers) + i), playerString);
  }

  rewind(sudoku);
  rewind(solutions);
  rewind(players);
}

void displayIndividualRecords(char **arrayOfSolutions, char **arrayOfPlayers, int numberOfSolutions, int numberOfPlayers)
{

  if (arrayOfSolutions == NULL || arrayOfPlayers == NULL)
  {
    printf("V2: unfilled arrays\n");
    return;
  }

  for (int i = 0; i < numberOfPlayers; i++)
  {
    char currentString[256];
    strcpy(currentString, *(arrayOfPlayers + i));
    currentString[strcspn(currentString, "\n")] = '\0';

    char *partOfStr = strtok(currentString, "#");
    int numberOfPart = 0;
    char PID[10] = "";
    char Identity[50] = "";
    int year = 0;
    char country[50] = "";
    while (partOfStr)
    {

      switch (numberOfPart)
      {

      case 0:
        strncpy(PID, partOfStr, sizeof(PID) - 1);
        PID[sizeof(PID) - 1] = '\0';
        break;
      case 1:
        strncpy(Identity, partOfStr, sizeof(Identity) - 1);
        Identity[sizeof(Identity) - 1] = '\0';
        break;
      case 2:
        strncpy(country, partOfStr, sizeof(country) - 1);
        country[sizeof(country) - 1] = '\0';
        break;
      case 3:
        year = (int)strtol(partOfStr, NULL, 10);
        break;

      default:
        break;
      }

      numberOfPart++;
      partOfStr = strtok(NULL, "#");
    }

    if (strlen(PID) == 0)
      continue;

    printf("PID: %s/%d/%s\nIdentity: %s\n", PID, year, country, Identity);

    for (int i = 0; i < numberOfSolutions; i++)
    {
      char currentStringSol[256];

      strcpy(currentStringSol, *(arrayOfSolutions + i));
      currentStringSol[strcspn(currentStringSol, "\n")] = '\0';

      if (strstr(currentStringSol, PID) != NULL)
      {

        char SID[9];
        char DifficultyOfGame;
        char GID[8];
        char DifficultyOfCompetition;
        char GameDate[9];
        int Duration;
        int numberOfSol = 0;
        char *partOfStrSol = strtok(currentStringSol, "#");

        while (partOfStrSol)
        {
          switch (numberOfSol)
          {

          case 0:
            strncpy(GID, partOfStrSol, sizeof(GID) - 1);
            GID[sizeof(GID) - 1] = '\0';
            DifficultyOfCompetition = GID[3];
            break;
          case 2:
            strncpy(SID, partOfStrSol, sizeof(SID) - 1);
            SID[sizeof(SID) - 1] = '\0';
            DifficultyOfGame = SID[3];
            break;
          case 3:
            strncpy(GameDate, partOfStrSol, sizeof(GameDate) - 1);
            GameDate[sizeof(GameDate) - 1] = '\0';
          case 4:
            Duration = ((int)(strtol(partOfStrSol, NULL, 10))) * 60;
            break;
          case 5:
            Duration += (int)(strtol(partOfStrSol, NULL, 10));
            break;

          default:
            break;
          }
          numberOfSol++;
          partOfStrSol = strtok(NULL, "#");
        }

        printf("Result: %s/%s/%s/%s/%c/%c/%d\n", GID, PID, SID, GameDate, DifficultyOfCompetition, DifficultyOfGame, Duration);
      }
    }
    printf("\n");
  }
}

int checkCompetitionIdentifier(char *identifierCompetition)
{
  if (strlen(identifierCompetition) != 7)
    return 0;

  if (strncmp(identifierCompetition, "GID", 3) != 0)
    return 0;

  if (!(*(identifierCompetition + 3) >= 'a' && *(identifierCompetition + 3) <= 'z'))
    return 0;

  for (int i = 4; i < 7; i++)
  {
    if (!(identifierCompetition[i] >= '0' && identifierCompetition[i] <= '9'))
      return 0;
  }

  return 1;
}

int checkPlayerIdentifier(char *identifierPlayer)
{
  if (strlen(identifierPlayer) != 9)
    return 0;

  if (strncmp(identifierPlayer, "PID", 3) != 0)
    return 0;

  if (!((identifierPlayer[3] >= 'a' && identifierPlayer[3] <= 'z') ||
        (identifierPlayer[3] >= 'A' && identifierPlayer[3] <= 'Z')))
    return 0;

  for (int i = 4; i < 9; i++)
  {
    if (!(identifierPlayer[i] >= '0' && identifierPlayer[i] <= '9'))
      return 0;
  }

  return 1;
}

int checkGameIdentifier(char *identifierGame)
{
  if (strlen(identifierGame) != 8)
    return 0;

  if (strncmp(identifierGame, "SID", 3) != 0)
    return 0;

  if (!(identifierGame[3] >= 'A' && identifierGame[3] <= 'Z'))
    return 0;

  for (int i = 4; i < 8; i++)
  {
    if (!(identifierGame[i] >= '0' && identifierGame[i] <= '9'))
      return 0;
  }

  return 1;
}

int checkDateAndTime(char *date, char *minutes, char *seconds)
{
  if (strlen(date) != 8 || strlen(minutes) != 2 || strlen(seconds) != 2)
    return 0;

  return 1;
}

void addNewRecords(char ***arrayOfSolutions, char *identifierCompetition, char *identifierPlayer, char *identifierGame, char *date, char *minutes, char *seconds, int position, int *numberOfSolutions)
{

  if (!(arrayOfSolutions))
  {

    printf("Q: Arrays are not created \n");
    return;
  }

  int len = strlen(identifierCompetition) + strlen(identifierPlayer) + strlen(identifierGame) + strlen(date) + strlen(minutes) + strlen(seconds) + 8;
  char *resStr = (char *)malloc(len);

  sprintf(resStr, "%s#%s#%s#%s#%s#%s\n", identifierCompetition, identifierPlayer, identifierGame, date, minutes, seconds);

  (*numberOfSolutions)++;

  *arrayOfSolutions = realloc(*arrayOfSolutions, *numberOfSolutions * sizeof(char *));

  if (position >= *numberOfSolutions)
  {
    (*arrayOfSolutions)[*numberOfSolutions - 1] = resStr;
  }
  else if (position < *numberOfSolutions)
  {
    for (int i = (*numberOfSolutions) - 1; i > position - 1; i--)
    {
      (*arrayOfSolutions)[i] = (*arrayOfSolutions)[i - 1];
    }
    (*arrayOfSolutions)[position - 1] = resStr;
  }

  printf("Q: record successfully added\n");
}

void deleteRecords(char ***arrayOfSolutions, char *playerIdentifier, int *numberOfSolutions)
{
  if (!(arrayOfSolutions))
  {

    printf("W: Arrays are not created \n");
    return;
  }

  int counterOfDletedEl = 0;
  for (int i = 0; i < *numberOfSolutions; i++)
  {

    if (strstr((*arrayOfSolutions)[i], playerIdentifier) != NULL)
    {
      free((*arrayOfSolutions)[i]);
      for (int j = i; j < *numberOfSolutions - 1; j++)
      {
        (*arrayOfSolutions)[j] = (*arrayOfSolutions)[j + 1];
      }
      i--;
      counterOfDletedEl++;
      *numberOfSolutions -= 1;
    }
  }

  *arrayOfSolutions = realloc(*arrayOfSolutions, *numberOfSolutions * sizeof(char *));

  printf("W: Deleted %d records\n", counterOfDletedEl);
}

void displaySudoku(char *gameIdentifier, int X, char **arrayOfSudoku, int numberOfSudoku)
{

  if (arrayOfSudoku == NULL)
  {
    printf("E: arrays are not created\n");

    return;
  }

  FILE *output = fopen("Output_E.txt", "w");

  for (int i = 0; i < numberOfSudoku; i++)
  {
    char currentString[93] = "";
    strcpy(currentString, *(arrayOfSudoku + i));
    currentString[strcspn(currentString, "\n")] = 0;

    if (strstr(currentString, gameIdentifier) != NULL)
    {

      char stringWithNumbers[81];

      strtok(currentString, "#");
      char *token = strtok(NULL, "#");

      if (token != NULL)
      {
        strcpy(stringWithNumbers, token);
      }

      char **arrayOfSudokuNum = (char **)malloc(9 * sizeof(char *));
      for (int i = 0; i < 9; i++)
      {
        *(arrayOfSudokuNum + i) = (char *)malloc(10 * sizeof(char));
        strncpy(arrayOfSudokuNum[i], stringWithNumbers + i * 9, 9);
        arrayOfSudokuNum[i][9] = '\0';

        int arrayOfUsedNumbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int j = 1; j <= X; j++)
        {
          int randomElementOfString = 1 + rand() % (9 - 1 + 1);

          if (arrayOfUsedNumbers[randomElementOfString - 1] == 0)
          {
            do
            {
              randomElementOfString = 1 + rand() % (9 - 1 + 1);
            } while (arrayOfUsedNumbers[randomElementOfString - 1] == 0);
          }
          arrayOfUsedNumbers[randomElementOfString - 1] = arrayOfUsedNumbers[randomElementOfString - 1] - randomElementOfString;

          arrayOfSudokuNum[i][randomElementOfString - 1] = ' ';
        }

        for (int a = 0; a < 9; a++)
        {
          fprintf(output, "|%c|", arrayOfSudokuNum[i][a]);
        }
        fprintf(output, "\n");
      }
      fprintf(output, "\n");

      for (int j = 0; j < 9; j++)
      {
        free(*(arrayOfSudokuNum + j));
      }

      free(arrayOfSudokuNum);
    }
  }

  fclose(output);
}

struct Record
{
  char SID[9];
  char DifficultyOfGame;
  char GID[8];
  char DifficultyOfCompetition;
  char GameDate[9];
  int Duration;
  struct Record *nextRecord;
};

struct Player
{
  char PID[10];
  char identity[50];
  char country[50];
  int yearOfBirth;
  struct Record *record;

  struct Player *nextPlayer;
};

void addRecordToPlayer(struct Player *player, char SID[9], char DifficultyOfGame, char GID[8], char DifficultyOfCompetition, char GameDate[9], int Duration)
{

  struct Record *newRecord = malloc(sizeof(struct Record));

  if (newRecord == NULL)
  {
    return;
  }

  sprintf(newRecord->SID, "%s", SID);
  newRecord->DifficultyOfGame = DifficultyOfGame;
  sprintf(newRecord->GID, "%s", GID);
  newRecord->DifficultyOfCompetition = DifficultyOfCompetition;
  sprintf(newRecord->GameDate, "%s", GameDate);
  newRecord->Duration = Duration;
  newRecord->nextRecord = player->record;
  player->record = newRecord;
}

struct Player *addPlayerStruct(char PID[10], char identity[50], char country[50], int yearOfBirth, struct Player *head)
{

  struct Player *newPlayer = malloc(sizeof(struct Player));

  if (newPlayer == NULL)
  {
    return NULL;
  }

  sprintf(newPlayer->PID, "%s", PID);
  sprintf(newPlayer->identity, "%s", identity);
  sprintf(newPlayer->country, "%s", country);
  newPlayer->yearOfBirth = yearOfBirth;
  newPlayer->record = NULL;
  newPlayer->nextPlayer = head;

  return newPlayer;
}

void readDataForLL(struct Player **head, FILE *players, FILE *solutions)
{
  if (players == NULL || solutions == NULL)
  {
    printf("M: Unopened file\n");
    return;
  }

  if (head != NULL)
  {
    struct Player *current = *head;
    struct Player *temp = NULL;
    while (current != NULL)
    {

      temp = current;
      current = current->nextPlayer;
      free(temp);
    }

    *head = NULL;
  }

  char currentString[256];
  int numberOfRecords = 0;

  while ((fgets(currentString, sizeof(currentString), players)) != NULL)
  {
    currentString[strcspn(currentString, "\n")] = '\0';

    char *part = strtok(currentString, "#");

    int partOfString = 0;
    char PID[10] = "";
    char identity[50] = "";
    char country[50] = "";
    int yearOfBirth = 0;

    while (part)
    {

      switch (partOfString)
      {
      case 0:
        strncpy(PID, part, sizeof(PID) - 1);
        PID[sizeof(PID) - 1] = '\0';
        break;
      case 1:
        strncpy(identity, part, sizeof(identity) - 1);
        identity[sizeof(identity) - 1] = '\0';
        break;
      case 2:
        strncpy(country, part, sizeof(country) - 1);
        country[sizeof(country) - 1] = '\0';
        break;
      case 3:
        yearOfBirth = (int)strtol(part, NULL, 10);
        break;

      default:
        break;
      }

      partOfString++;
      part = strtok(NULL, "#");
    }

    if (strlen(PID) == 0)
      continue;

    numberOfRecords++;

    *head = addPlayerStruct(PID, identity, country, yearOfBirth, *head);

    rewind(solutions);

    char currentStringSol[256];

    while ((fgets(currentStringSol, sizeof(currentStringSol), solutions)) != NULL)
    {
      currentStringSol[strcspn(currentStringSol, "\n")] = '\0';

      if (strstr(currentStringSol, PID) != NULL)
      {
        int numberOfCurrentSolutionData = 0;

        char SID[9];
        char DifficultyOfGame;
        char GID[8];
        char DifficultyOfCompetition;
        char GameDate[9];
        int Duration;

        char *solData = strtok(currentStringSol, "#");

        while (solData)
        {
          switch (numberOfCurrentSolutionData)
          {
          case 0:
            strncpy(GID, solData, sizeof(GID) - 1);
            GID[sizeof(GID) - 1] = '\0';
            DifficultyOfCompetition = GID[3];
            break;
          case 2:
            strncpy(SID, solData, sizeof(SID) - 1);
            SID[sizeof(SID) - 1] = '\0';
            DifficultyOfGame = SID[3];
            break;
          case 3:
            strncpy(GameDate, solData, sizeof(GameDate) - 1);
            GameDate[sizeof(GameDate) - 1] = '\0';
          case 4:
            Duration = ((int)(strtol(solData, NULL, 10))) * 60;
            break;
          case 5:
            Duration += (int)(strtol(solData, NULL, 10));
            break;

          default:
            break;
          }

          numberOfCurrentSolutionData++;
          solData = strtok(NULL, "#");
        }

        addRecordToPlayer(*head, SID, DifficultyOfGame, GID, DifficultyOfCompetition, GameDate, Duration);
      }
    }
  }

  printf("M: %d records read\n", numberOfRecords);

  rewind(solutions);
  rewind(players);
}

void printfListOfStructures(struct Player *head)
{
  struct Player *currentPlayer = head;

  if (head == NULL)
  {
    printf("V3: Merge list not filled\n");
    return;
  }

  while (currentPlayer != NULL)
  {
    printf("PID: %s\n Identity: %s\n Country: %s\n Year of Birth: %d\n", currentPlayer->PID, currentPlayer->identity, currentPlayer->country, currentPlayer->yearOfBirth);
    struct Record *temp = currentPlayer->record;

    while (temp != NULL)
    {
      printf("Result: %s/ %c/ %s/ %c/ %s/ %d\n", temp->SID, temp->DifficultyOfGame, temp->GID, temp->DifficultyOfCompetition, temp->GameDate, temp->Duration);
      temp = temp->nextRecord;
    }

    currentPlayer = currentPlayer->nextPlayer;
    printf("\n");
  }
}

void addNewPlayerToLinkedList(struct Player **head, char name[50], char country[50], int yearOfBirth, int position)
{
  struct Player *newPlayer = malloc(sizeof(struct Player));
  if (newPlayer == NULL)
    return;

  memset(newPlayer, 0, sizeof(struct Player));
  sprintf(newPlayer->identity, "%s", name);
  sprintf(newPlayer->country, "%s", country);
  newPlayer->yearOfBirth = yearOfBirth;

  if (*head == NULL)
  {
    sprintf(newPlayer->PID, "PIDa00001");
    newPlayer->nextPlayer = *head;
    *head = newPlayer;
    printf("A: Record successfully added to position 1\n");
    return;
  }

  int numberOfPlayers = 0;
  int playerExists = 0;
  struct Player *current = *head;

  while (current != NULL)
  {
    if (strcmp(current->identity, name) == 0 && current->yearOfBirth == yearOfBirth)
      playerExists++;
    numberOfPlayers++;
    current = current->nextPlayer;
  }

  if (playerExists != 0)
  {
    printf("A: Duplicate record\n");
    free(newPlayer);
    return;
  }

  int *pidNumbers = malloc(sizeof(int) * numberOfPlayers);
  if (pidNumbers == NULL)
  {
    free(newPlayer);
    return;
  }

  int countUsedPIDs = 0;
  current = *head;

  while (current != NULL)
  {
    if (strncmp(current->PID, "PIDa", 4) == 0)
    {
      sscanf(current->PID + 4, "%05d", &pidNumbers[countUsedPIDs]);
      countUsedPIDs++;
    }
    current = current->nextPlayer;
  }

  int pidNumber = 1;
  while (1)
  {
    int foundFree = 0;

    for (int i = 0; i < countUsedPIDs; i++)
    {
      if (pidNumber == *(pidNumbers + i))
      {
        foundFree = 1;
        break;
      }
    }

    if (!foundFree)
    {
      break;
    }

    pidNumber++;
  }

  sprintf(newPlayer->PID, "PIDa%05d", pidNumber);
  free(pidNumbers);

  if (position == 1)
  {
    newPlayer->nextPlayer = *head;
    *head = newPlayer;
  }
  else if (position > numberOfPlayers)
  {

    current = *head;
    while (current->nextPlayer != NULL)
      current = current->nextPlayer;
    current->nextPlayer = newPlayer;
    newPlayer->nextPlayer = NULL;
    numberOfPlayers += 1;
    printf("A: Record successfully added to position %d\n", numberOfPlayers);
    return;
  }
  else
  {

    current = *head;
    struct Player *prev = NULL;
    int playerPosition = 1;

    while (playerPosition < position && current != NULL)
    {
      prev = current;
      current = current->nextPlayer;
      playerPosition++;
    }

    newPlayer->nextPlayer = current;
    if (prev != NULL)
      prev->nextPlayer = newPlayer;
  }

  printf("A: Record successfully added to position %d\n", position);
}

void deleteResultsFromLinkedList(struct Player *head, char *competitionIdentifier)
{

  if (head == NULL)
  {
    printf("S: Linked list has not been created\n");
    return;
  }

  int numberOfDeletedResults = 0;

  struct Player *current = head;

  while (current != NULL)
  {
    struct Record *currentRec = current->record;
    struct Record *prevRec = NULL;

    while (currentRec != NULL)
    {
      if (strcmp(currentRec->GID, competitionIdentifier) == 0)
      {

        struct Record *recordToDel = currentRec;
        if (prevRec == NULL)
        {

          current->record = currentRec->nextRecord;
        }
        else
        {

          prevRec->nextRecord = currentRec->nextRecord;
        }
        currentRec = currentRec->nextRecord;
        free(recordToDel);
        numberOfDeletedResults++;
      }
      else
      {

        prevRec = currentRec;
        currentRec = currentRec->nextRecord;
      }
    }
    current = current->nextPlayer;
  }

  printf("S: Deleted %d records!\n", numberOfDeletedResults);
}

void sortLL(struct Player *head)
{
  if (head == NULL)
  {
    printf("Linked list is not created\n");
    return;
  }

  struct Player *current = head;

  while (current != NULL)
  {
    struct Record *prevRec = NULL;
    struct Record *currentRec = current->record;

    if (current->record == NULL)
    {
      current = current->nextPlayer;
      continue;
    }

    while (1)
    {
      int swapped = 0;
      currentRec = current->record;
      prevRec = NULL;

      while (currentRec->nextRecord != NULL)
      {
        struct Record *nextRec = currentRec->nextRecord;

        if ((currentRec->Duration) > (nextRec->Duration))
        {
          if (prevRec == NULL)
          {

            current->record = nextRec;
            currentRec->nextRecord = nextRec->nextRecord;
            nextRec->nextRecord = currentRec;
          }

          else
          {
            currentRec->nextRecord = nextRec->nextRecord;
            nextRec->nextRecord = currentRec;
            prevRec->nextRecord = nextRec;
          }

          prevRec = currentRec;
          currentRec = nextRec;
          swapped = 1;
        }
        else
        {
          prevRec = currentRec;
          currentRec = nextRec;
        }
      }

      if (swapped == 0)
        break;
    }

    current = current->nextPlayer;
  }

  printf("Sorted\n");
}

int main()
{

  FILE *sudoku = NULL;
  FILE *solutions = NULL;
  FILE *players = NULL;

  char **arrayOfSudoku = NULL;
  char **arrayOfSolutions = NULL;
  char **arrayOfPlayers = NULL;

  int numberOfSudoku;
  int numberOfSolutions;
  int numberOfPlayers;

  char command[3];

  struct Player *head = NULL;

  while (1)
  {

    scanf("%s", command);

    command[strcspn(command, "\n")] = 0;

    if (strcmp(command, "v1") == 0)
    {
      checkFiles(&sudoku, &solutions, &players);
    }

    else if (strcmp(command, "h") == 0)
    {
      findGame(solutions);
    }

    else if (strcmp(command, "n") == 0)
    {

      createDynamicArraysWithIndividualInfo(&arrayOfSudoku, &arrayOfSolutions, &arrayOfPlayers, &numberOfSudoku, &numberOfSolutions, &numberOfPlayers, sudoku, solutions, players);
    }

    else if (strcmp(command, "v2") == 0)
    {

      displayIndividualRecords(arrayOfSolutions, arrayOfPlayers, numberOfSolutions, numberOfPlayers);
    }

    else if (strcmp(command, "q") == 0)
    {

      int Y;
      char date[9], minutes[3], seconds[3];
      char identifierCompetition[8];
      char identifierPlayer[10];
      char identifierGame[9];

      scanf("%d", &Y);
      scanf("%s", identifierCompetition);

      if (!checkCompetitionIdentifier(identifierCompetition))
        do
        {
          printf("Q: incorrect input format, enter again: ");
          scanf("%s", identifierCompetition);
        } while (!checkCompetitionIdentifier(identifierCompetition));

      scanf("%s", identifierPlayer);

      if (!checkPlayerIdentifier(identifierPlayer))
        do
        {
          printf("Q: incorrect input format, enter again: ");
          scanf("%s", identifierPlayer);
        } while (!checkPlayerIdentifier(identifierPlayer));

      scanf("%s", identifierGame);
      if (!checkGameIdentifier(identifierGame))
        do
        {
          printf("Q: incorrect input format, enter again: ");
          scanf("%s", identifierGame);
        } while (!checkGameIdentifier(identifierGame));

      scanf("%s %s %s", date, minutes, seconds);

      if (!checkDateAndTime(date, minutes, seconds))
        do
        {
          printf("Q: incorrect input format, enter again: ");
          scanf("%s %s %s", date, minutes, seconds);

        } while (!checkDateAndTime(date, minutes, seconds));

      addNewRecords(&arrayOfSolutions, identifierCompetition, identifierPlayer, identifierGame, date, minutes, seconds, Y, &numberOfSolutions);
    }

    else if (strcmp(command, "w") == 0)
    {
      char playerIdentifier[10];

      scanf("%s", playerIdentifier);

      if (!checkPlayerIdentifier(playerIdentifier))
        do
        {
          printf("W: incorrect input format, enter again: ");
          scanf("%s", playerIdentifier);
        } while (!checkPlayerIdentifier(playerIdentifier));

      deleteRecords(&arrayOfSolutions, playerIdentifier, &numberOfSolutions);
    }

    else if (strcmp(command, "e") == 0)
    {
      char gameIdentifier[9];
      int X;

      scanf("%s", gameIdentifier);

      if (!checkGameIdentifier(gameIdentifier))
        do
        {
          printf("E: incorrect input: ");
          scanf("%s", gameIdentifier);
        } while (!checkGameIdentifier(gameIdentifier));

      scanf("%d", &X);
      if (!(X >= 1 && X <= 5))
      {
        do
        {
          printf("E: incorrect input: ");
          scanf("%d", &X);
        } while (!(X >= 1 && X <= 5));
      }

      displaySudoku(gameIdentifier, X, arrayOfSudoku, numberOfSudoku);
    }

    else if (strcmp(command, "m") == 0)
    {

      readDataForLL(&head, players, solutions);
    }
    else if (strcmp(command, "v3") == 0)
    {
      printfListOfStructures(head);
    }

    else if (strcmp(command, "a") == 0)
    {
      int Y;
      char name[50];
      char country[50];
      int yearOfBirth;

      scanf("%d", &Y);
      scanf(" %49[^\n]", name);
      scanf(" %49[^\n]", country);
      scanf("%d", &yearOfBirth);
      addNewPlayerToLinkedList(&head, name, country, yearOfBirth, Y);
    }

    else if (strcmp(command, "s") == 0)
    {

      char competitionIdentifier[8];

      scanf("%s", competitionIdentifier);

      if (!checkCompetitionIdentifier(competitionIdentifier))
        do
        {
          printf("S: incorrect input format, enter again: ");
          scanf("%s", competitionIdentifier);
        } while (!checkCompetitionIdentifier(competitionIdentifier));

      deleteResultsFromLinkedList(head, competitionIdentifier);
    }

    else if (strcmp(command, "d") == 0)
    {
      sortLL(head);
    }

    else if (strcmp(command, "k") == 0)
    {
      if (arrayOfSudoku != NULL || arrayOfSolutions != NULL || arrayOfPlayers != NULL)
      {
        for (int i = 0; i < numberOfSudoku; i++)
        {
          free(*(arrayOfSudoku + i));
        }

        free(arrayOfSudoku);
        arrayOfSudoku = NULL;

        for (int i = 0; i < numberOfSolutions; i++)
        {
          free(*(arrayOfSolutions + i));
        }

        free(arrayOfSolutions);
        arrayOfSolutions = NULL;

        for (int i = 0; i < numberOfPlayers; i++)
        {
          free(*(arrayOfPlayers + i));
        }

        free(arrayOfPlayers);
        arrayOfPlayers = NULL;
      }

      if (solutions && sudoku && players)
      {
        fclose(sudoku);
        fclose(solutions);
        fclose(players);
        solutions = NULL;
        players = NULL;
        sudoku = NULL;
      }

      if (head != NULL)
      {
        struct Player *current = head;
        struct Player *temp = NULL;
        while (current != NULL)
        {

          temp = current;
          current = current->nextPlayer;
          free(temp);
        }

        head = NULL;
      }

      printf("\n");
    }

    else
    {
      printf("V:Incorrect listing selection\n");
    }
  }

  return 0;
}
