#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void title()
{
    // print the title of the game
    printf(" __    __       ___      .__   __.   _______ .___  ___.      ___      .__   __.\n");
    printf("|  |  |  |     /   \\     |  \\ |  |  /  _____||   \\/   |     /   \\     |  \\ |  |\n");
    printf("|  |__|  |    /  ^  \\    |   \\|  | |  |  __  |  \\  /  |    /  ^  \\    |   \\|  |\n");
    printf("|   __   |   /  /_\\  \\   |  . `  | |  | |_ | |  |\\/|  |   /  /_\\  \\   |  . `  |\n");
    printf("|  |  |  |  /  _____  \\  |  |\\   | |  |__| | |  |  |  |  /  _____  \\  |  |\\   |\n");
    printf("|__|  |__| /__/     \\__\\ |__| \\__|  \\______| |__|  |__| /__/     \\__\\ |__| \\__|\n");
}

int random_num(int max_words)
{
    // generate random number between 0 and maximum number of words
    srand((unsigned)time(NULL) - 654321);
    int random = rand() % max_words;
    return random;
}



char **create_words(char filename[], char **words,int *max_words)
{
    // create a word_array with the words from a file
    // word_array is a 2D array

    FILE *fPointer;
    fPointer = fopen(filename, "r");
    if (fPointer == NULL)
    {
        printf("The file doesn't exist ! Please check again .");
        return NULL;
    }
    char singleLine[50];
    int cnt = 0;
    fgets(singleLine, 50, fPointer);
    while (!feof(fPointer))
    {

        char **new_words = (char**) malloc(sizeof(char*)*(cnt+1));
        new_words[0] = (char *)malloc(sizeof(char)*20*(cnt+1));
        for (int i = 1; i <cnt+1; ++i)
        {
        new_words[i] = new_words[i - 1] + 20;
        }

        for(int i=0;i<cnt;i++)
        {
            strcpy(new_words[i],words[i]);
        }
        singleLine[strlen(singleLine) - 1] = '\0';
        strcpy(new_words[cnt], singleLine);
        free(words[0]);
        free(words);
        words = new_words;
        cnt++;
        fgets(singleLine, 50, fPointer);
    }
    fclose(fPointer);
    *max_words = cnt;
    return words;
}

void randomWord(int length, char **words, char *w,int max_words)
{
    // from the word_array return a random word

    int rand_num = random_num(max_words);
    int count = 0;
    int i = 0;
    // the loop will end if the program finds the required word
    while (1)
    {
        // if the word of index random number is equal to the required length
        if (strlen(words[rand_num]) == length)
        {
            // it will copy that word
            strcpy(w, strlwr(words[rand_num]));
            break;
        }
        else
        {
            // if not it will decrease the random number till it reach the required word's index
            rand_num = rand_num - 1;
            // if the random number reaches below 0
            if (rand_num < 0)
            {
                // it will be assign to a random number again
                rand_num = random_num(max_words);
            }
        }
    }
    // This method can give complete random word
}

void print_dash(int length)
{
    // Printing dashes according to the number of letters in the word
    for (int i = 0; i < length; ++i)
    {
        printf("_ ");
    }
}

void print_arr(char *guess)
{
    // print the elements of an array
    for (int i = 0; i < strlen(guess); ++i)
    {
        printf("%c ", guess[i]);
    }
}

int already_guess(char letter, char *guess)
{
    // To check whether a letter is already guessed
    // if the letter is correct and has been already guessed
    // the letter will be checked as guessed
    int guessed = 0;
    for (int i = 0; i < strlen(guess); ++i)
    {
        if (letter == guess[i])
        {
            printf("Already guessed! Try another letter.\n");
            guessed = 1;
            break;
        }
    }
    return guessed;
}

int not_in(char letter, char *word)
{
    // To check whether a letter is in the original word
    // if the letter is in the original word
    // the letter will be checked as in the original word
    int not_in = 1;
    for (int i = 0; i < strlen(word); ++i)
    {
        if (letter == word[i])
        {
            not_in = 0;
        }
    }
    if (not_in)
    {
        printf("The letter is not in the word!\n");
    }
    return not_in;
}

void Words_statistics(char letter, int *num_words)
{
    // This function will do the statiscs of the letters guessed by user
    // This will count the number of the letters user guessed
    // Add it to the previous data
    if (letter >= 'a' && letter <= 'z')
    {
        int index = letter - 'a';
        num_words[index] += 1;
    }
}

void get_statistics(char filename[], int *num_words)
{
    // get the word statistics data of the letter
    // from the file
    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("File can't be opened");
        return;
    }
    int i = 0;
    char letter;
    while (fscanf(f, "[%c]:%d\n", &letter, &num_words[i]) != EOF)
    {
        i++;
    }
    fclose(f);
}

void read_statistics(char filename[])
{
    // print out the data from the file
    // which stores the statistics of the letters
    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("File can't be opened");
        return;
    }
    int num;
    char letter;
    int cnt = 0;
    printf("Printing the number of letters guessed\n");
    while (fscanf(f, "[%c]:%d\n", &letter, &num) != EOF)
    {
        printf("[%c]:%3d  ", letter, num);
        cnt++;
        if (cnt == 13)
        {
            printf("\n");
        }
    }

    printf("\n\n");
    fclose(f);
}

void write_file(int *num_words)
{

    // write the number of letters counted during the game to a file
    FILE *f;
    f = fopen("words_statistic.txt", "w");
    if (f == NULL)
    {
        printf("File can't be opened");
        return;
    }
    for (int i = 0; i < 26; ++i)
    {

        fprintf(f, "[%c]:%d\n", 'a' + i, num_words[i]);
    }
    fclose(f);
}

void hangman()
{
    // display hangman game over picture
    printf(" +---+\n");
    printf(" |   |\n");
    printf(" O   |\n");
    printf("/|\\  |\n");
    printf("/ \\  |\n");
    printf("     |\n");
    printf("=========\n");
}

int reduce_chance(int miss, char *guess, int chance)
{
    // print guessed words
    // increase miss count
    // print chance
    print_arr(guess);
    miss += 1;
    printf("       <Chances: %d>\n", chance - miss);
    return miss;
}

void guess_word(char *word, int chance, char filename[])
{
    // This is the source of the game
    // This function will receive a word and processes it
    // according to the rule of the Hangman game
    // This will check whether a word is guessed or in the correct word
    // Decide whether the user wins or lose the game
    int *num_words = (int *)calloc(26, sizeof(int));
    get_statistics(filename, num_words);
    char letter;
    char *guess = (char *)malloc((strlen(word) + 1) * sizeof(char));
    for (int i = 0; i < strlen(word); ++i)
    {
        guess[i] = '_';
    }
    guess[strlen(word)] = '\0';
    int miss = 0;
    printf("Guess a letter\n");
    while (miss <= chance)
    {
        if (miss == chance)
        {
            printf("No Chances left!!!\n");
            hangman();
            printf("You couldn't guess all the letters! You lose!");
            printf("The word is [ %s ]\n", word);
            write_file(num_words);
            break;
        }

        char str[20];
        scanf(" %s", &str);
        if (str[1] != '\0')
        {
            printf("Type only one letter at each time\n");
            miss = reduce_chance(miss, guess, chance);
            continue;
        }
        letter = str[0];

        if (!(letter >= 'a' && letter <= 'z'))
        {
            printf("Please type letter only\n");
            miss = reduce_chance(miss, guess, chance);
            continue;
        }
        Words_statistics(letter, num_words);

        if (already_guess(letter, guess) || not_in(letter, word))
        {
            miss = reduce_chance(miss, guess, chance);
            continue;
        }

        for (int i = 0; i < strlen(word); i++)
        {
            if (letter == word[i])
            {
                guess[i] = word[i];
            }
        }
        print_arr(guess);
        printf("       <Chances: %d>\n", chance - miss);
        int same = strcmp(word, guess);
        if (same == 0)
        {
            printf("You win!\nYou have guessed all the letter\n");
            write_file(num_words);
            break;
        }
    }
    free(guess);
    free(num_words);
}

void play_game()
{
    // This is Hangman_game.exe function

    char letter;
    int length;
    printf("Type the length for a random word (min-3,max-16)\n");

    scanf("%d", &length);
    if (length > 16)
    {
        printf("The maximum length can only be 16. Therefore it is set to 16\n");
        length = 16;
    }
    else if (length < 3)
    {
        printf("The minimum length can only be 3. Therefore it is set to 3\n");
        length = 3;
    }

    int chance;
    // The user will be able to choose the difficulty level
    // For 1, the user cannot miss even a single time
    // For 8, the user can miss 8 times
    printf("Choose the number of chances(Difficulty : 1 = The Hardest , 10 = the easiest)\n");
    scanf("%d", &chance);

    if (chance < 1)
    {
        printf("The minimum number of chance can only be 1. Therefore it is set to 1\n");
        chance = 1;
    }
    else if (chance > 10)
    {
        printf("The maximum number of chance can only be 10. Therefore it is set to 10\n");
        chance = 10;
    }

    // create a dynamic array for the word to store random word
    char *word = (char *)malloc((length + 1) * sizeof(char));
    if (word == NULL)
    {
        printf("Not enough Memory");
        return;
    }



    // create a 2D dynamic array for storing the words from a file
    char **word_arr = (char**) malloc(sizeof(char*)*1);
    word_arr[0] = (char *)malloc(sizeof(char)*20*1);

    if (word_arr == NULL)
    {
        printf("Not enough Memory");
        return;
    }
    int max_words;
    word_arr = create_words("words.txt", word_arr,&max_words);

    randomWord(length, word_arr, word,max_words);

    print_dash(strlen(word));
    printf("       <Chances: %d>\n", chance);

    guess_word(word, chance, "words_statistic.txt");

    free(word);
    free(word_arr[0]);
    free(word_arr);
    printf("\n");
}

void print_menu()
{
    char option[5];
    printf("To play game press 1\n");
    printf("To see the statistics of letters press 2\n");
    printf("To exit press 3\n");
    scanf("%s", &option);

    char opt = option[0];

    if (opt == '1')
    {
        play_game();
        print_menu();
    }
    else if (opt == '2')
    {
        read_statistics("words_statistic.txt");
        print_menu();
    }
    else if (opt == '3')
    {
        return;
    }
    else
    {
        printf("Please choose only from the given options\n");
        print_menu();
    }

}

int main()
{
    // This is the main function
    title();
    print_menu();
    return 0;
}
