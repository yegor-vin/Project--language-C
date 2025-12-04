#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void checkFiles()
{
  FILE *sudoku = fopen("Sudoku.txt", "r");
  FILE *solutions = fopen("SolutionsRegister.txt", "r");
  FILE *players = fopen("PlayersRegister.txt", "r");

  if (sudoku == NULL || solutions == NULL || players == NULL)
  {
    FILE *sudoku = fopen("Sudoku.txt", "r");
    FILE *solutions = fopen("SolutionsRegister.txt", "r");
    FILE *players = fopen("PlayersRegister.txt", "r");

    if (sudoku == NULL || solutions == NULL || players == NULL)
    {
      printf("V1: unopened txt files\n");
    }
  }

  char string[100];

  while ((fgets(string, sizeof(string), players)) != NULL)
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

    rewind(solutions);
    char playerSol[250];

    while (fgets(playerSol, sizeof(playerSol), solutions) != NULL)
    {
      playerSol[strcspn(playerSol, "\n")] = 0;

      if (strstr(playerSol, Identificator) != NULL)
      {
        printf("Sample: %s\n\n", playerSol);

        break;
      }
    }

    printf("\n");
  }

  fclose(solutions);
  fclose(players);
  fclose(sudoku);
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

void findGame()
{
  FILE *solutions = fopen("SolutionsRegister.txt", "r");

  char *gameIdentificator = (char *)malloc(10 * sizeof(char));
  printf("enter identifier in format(SIDA0001)\n");
  scanf("%s", gameIdentificator);

  if (strlen(gameIdentificator) != 8)
  {
    printf("H: Incorrect identifier\n");
  }
  else

      if (strncmp(gameIdentificator, "SID", 3) != 0 || !(gameIdentificator[3] >= 'A' && gameIdentificator[3] <= 'Z') || checkCorrectnessOfIdentificatorByNumbers(gameIdentificator) == 0)
  {
    printf("H: Incorrect identifier\n");
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

  fclose(solutions);
}

void createDynamicArraysWithIndividualInfo(char *nameOfFile, char ***individualArr, int *numberOfStringsArr, int index)
{
  FILE *file = fopen(nameOfFile, "r");
  if (file == NULL)
  {
    printf("File not open: %s\n", nameOfFile);
    return;
  }

  numberOfStringsArr[index] = 0;
  char currentString[1000];
  while (fgets(currentString, sizeof(currentString), file))
  {
    numberOfStringsArr[index]++;
  }

  rewind(file);

  *individualArr = malloc(sizeof(char *) * numberOfStringsArr[index]);

  for (int i = 0; i < numberOfStringsArr[index]; i++)
  {
    fgets(currentString, sizeof(currentString), file);
    (*individualArr)[i] = malloc(strlen(currentString) + 1);
    strcpy((*individualArr)[i], currentString);
  }

  fclose(file);
}

void displayIndividualRecords(char ***individualArrays, int *arrLength, int *numberOfStrings)
{
  if (individualArrays == NULL)
  {
    printf("V2: unfilled arrays\n");
    return;
  }
  else
  {

    for (int i = 0; i < *arrLength; i++)
    {
      for (int j = 0; j < numberOfStrings[i]; j++)
      {

        char *value = individualArrays[i][j];

        if (strncmp(value, "GID", 3) == 0)
        {
          printf("Result: %s", value);
        }
        else if (strncmp(value, "PID", 3) == 0)
        {
          printf("PID: %s", value);
        }
        else
        {
          printf("Identity: %s", value);
        }
      }
      printf("\n");
    }
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

void addNewRecords(char ***arrayOfIndividualArr, char *identifierCompetition, char *identifierPlayer, char *identifierGame, char *date, char *minutes, char *seconds, int arrLength, int *numberOfStringsArr, int position)
{

  if (!(arrayOfIndividualArr))
  {

    printf("Q: Arrays are not created \n");
    return;
  }

  int len = strlen(identifierCompetition) + strlen(identifierPlayer) + strlen(identifierGame) + strlen(date) + strlen(minutes) + strlen(seconds) + 8;
  char *resStr = (char *)malloc(len);

  sprintf(resStr, "%s#%s#%s#%s#%s#%s#\n", identifierCompetition, identifierPlayer, identifierGame, date, minutes, seconds);

  int playerIndex = -1;
  for (int i = 0; i < arrLength; i++)
  {
    for (int j = 0; j < *(numberOfStringsArr + i); j++)
    {

      if (strstr(*(*(arrayOfIndividualArr + i) + j), identifierPlayer) != NULL)
      {
        playerIndex = i;
        *(numberOfStringsArr + playerIndex) += 1;
        break;
      }
    }
    if (playerIndex != -1)
    {
      break;
    }
  }

  if (playerIndex == -1)
  {
    return;
  }

  arrayOfIndividualArr[playerIndex] = realloc(arrayOfIndividualArr[playerIndex], numberOfStringsArr[playerIndex] * sizeof(char *));

  if (position >= numberOfStringsArr[playerIndex])
  {
    arrayOfIndividualArr[playerIndex][numberOfStringsArr[playerIndex] - 1] = resStr;
    return;
  }
  else if (position < numberOfStringsArr[playerIndex])
  {
    for (int i = numberOfStringsArr[playerIndex] - 1; i > position - 1; i--)
    {
      arrayOfIndividualArr[playerIndex][i] = arrayOfIndividualArr[playerIndex][i - 1];
    }
    arrayOfIndividualArr[playerIndex][position - 1] = resStr;
  }

  printf("Q: record successfully added\n");
}

void deleteRecords(char ***arrayOfIndividualArr, char *playerIdentifier, int arrLength, int *numberOfStringsArr)
{
  if (!(arrayOfIndividualArr))
  {

    printf("W: Arrays are not created \n");
    return;
  }

  int playerIndex = -1;
  for (int i = 0; i < arrLength; i++)
  {
    for (int j = 0; j < *(numberOfStringsArr + i); j++)
    {

      if (strstr(*(*(arrayOfIndividualArr + i) + j), playerIdentifier) != NULL)
      {
        playerIndex = i;
        break;
      }
    }
    if (playerIndex != -1)
    {
      break;
    }
  }

  if (playerIndex == -1)
  {
    return;
  }

  int counterOfDletedEl = 0;
  for (int i = 0; i < *(numberOfStringsArr + playerIndex); i++)
  {

    if (strncmp(arrayOfIndividualArr[playerIndex][i], "GID", 3) == 0)
    {
      free(arrayOfIndividualArr[playerIndex][i]);
      for (int j = i; j < *(numberOfStringsArr + playerIndex) - 1; j++)
      {
        arrayOfIndividualArr[playerIndex][j] = arrayOfIndividualArr[playerIndex][j + 1];
      }
      i--;
      counterOfDletedEl++;
      numberOfStringsArr[playerIndex] -= 1;
    }
  }

  arrayOfIndividualArr[playerIndex] = realloc(arrayOfIndividualArr[playerIndex], numberOfStringsArr[playerIndex] * sizeof(char *));

  printf("W: Deleted %d records\n", counterOfDletedEl);
}

void displaySudoku(char *gameIdentifier, int X)
{

  FILE *sudoku = fopen("Sudoku.txt", "r");
  FILE *output = fopen("Output_E.txt", "w");

  char currentString[93];

  int foundGame = 0;
  while (fgets(currentString, sizeof(currentString), sudoku))
  {
    currentString[strcspn(currentString, "\n")] = 0;

    if (strstr(currentString, gameIdentifier) != NULL)
    {
      foundGame++;
      break;
    }
  }

  if (foundGame == 0)
  {
    printf("E: arrays are not created");
    fclose(sudoku);
    fclose(output);
    return;
  }

  char stringWithNumbers[81];

  strtok(currentString, "#");
  char *token = strtok(NULL, "#");

  if (token != NULL)
  {
    strcpy(stringWithNumbers, token);
  }

  char **arrayOfSudoku = (char **)malloc(9 * sizeof(char *));
  for (int i = 0; i < 9; i++)
  {
    *(arrayOfSudoku + i) = (char *)malloc(10 * sizeof(char));
    strncpy(arrayOfSudoku[i], stringWithNumbers + i * 9, 9);
    arrayOfSudoku[i][9] = '\0';

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

      arrayOfSudoku[i][randomElementOfString - 1] = ' ';
    }

    for (int a = 0; a < 9; a++)
    {
      fprintf(output, "|%c|", arrayOfSudoku[i][a]);
    }
    fprintf(output, "\n");
  }

  fclose(sudoku);
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

  sprintf(newRecord->SID, SID);
  newRecord->DifficultyOfGame = DifficultyOfGame;
  sprintf(newRecord->GID, GID);
  newRecord->DifficultyOfCompetition = DifficultyOfCompetition;
  sprintf(newRecord->GameDate, GameDate);
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

  sprintf(newPlayer->PID, PID);
  sprintf(newPlayer->identity, identity);
  sprintf(newPlayer->country, country);
  newPlayer->yearOfBirth = yearOfBirth;
  newPlayer->record = NULL;
  newPlayer->nextPlayer = head;

  return newPlayer;
}

void printfListOfStructures(struct Player *head)
{
  struct Player *currentPlayer = head;

  while (currentPlayer != NULL)
  {
    printf("Player ID: %s\n Name: %s\n Country: %s\n Year of Birth: %d\n", currentPlayer->PID, currentPlayer->identity, currentPlayer->country, currentPlayer->yearOfBirth);
    struct Record *temp = currentPlayer->record;

    while (temp != NULL)
    {
      printf("Record: %s/ %c/ %s/ %c/ %s/ %d\n", temp->SID, temp->DifficultyOfGame, temp->GID, temp->DifficultyOfCompetition, temp->GameDate, temp->Duration);
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

int main()
{

  char command[3];

  char ***arrayOfIndividualArr = NULL;
  int numberOfFiles = 5;
  int *numberOfStringsArr = (int *)malloc(sizeof(int) * numberOfFiles);
  struct Player *head = NULL;

  while (1)
  {

    scanf("%s", command);

    command[strcspn(command, "\n")] = 0;

    if (strcmp(command, "v1") == 0)
    {
      checkFiles();
    }

    else if (strcmp(command, "h") == 0)
    {
      findGame();
    }

    else if (strcmp(command, "n") == 0)
    {

      char *arrayOfFiles[5] = {
          "Novak_Peter.txt",
          "Hruba_Jana.txt",
          "Kovacs_Aron.txt",
          "Johana_Van_Den_Dong.txt",
          "user.txt",
      };

      if (arrayOfIndividualArr != NULL)
      {
        for (int i = 0; i < numberOfFiles; i++)
        {

          if (arrayOfIndividualArr[i] != NULL)
          {

            for (int j = 0; j < *(numberOfStringsArr + i); j++)
            {
              free(arrayOfIndividualArr[i][j]);
            }
            free(arrayOfIndividualArr[i]);
          }
        }
        free(arrayOfIndividualArr);
        arrayOfIndividualArr = NULL;
      }

      arrayOfIndividualArr = (char ***)malloc(sizeof(char **) * numberOfFiles);

      for (int i = 0; i < numberOfFiles; i++)
      {

        createDynamicArraysWithIndividualInfo(arrayOfFiles[i], &arrayOfIndividualArr[i], numberOfStringsArr, i);
      }
    }

    else if (strcmp(command, "v2") == 0)
    {

      displayIndividualRecords(arrayOfIndividualArr, &numberOfFiles, numberOfStringsArr);
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

      addNewRecords(arrayOfIndividualArr, identifierCompetition, identifierPlayer, identifierGame, date, minutes, seconds, numberOfFiles, numberOfStringsArr, Y);
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

      deleteRecords(arrayOfIndividualArr, playerIdentifier, numberOfFiles, numberOfStringsArr);
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

      displaySudoku(gameIdentifier, X);
    }

    else if (strcmp(command, "m") == 0)
    {

      FILE *players = fopen("PlayersRegister.txt", "r");
      FILE *solutions = fopen("SolutionsRegister.txt", "r");

      if (players == NULL || solutions == NULL)
      {
        printf("M: Unopened file\n");
        return 0;
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

        head = addPlayerStruct(PID, identity, country, yearOfBirth, head);

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

            addRecordToPlayer(head, SID, DifficultyOfGame, GID, DifficultyOfCompetition, GameDate, Duration);
          }
        }
      }

      printf("M: %d records read\n", numberOfRecords);

      fclose(players);
      fclose(solutions);
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
    else
    {
      printf("V:Incorrect listing selection\n");
    }
  }

  return 0;
}
