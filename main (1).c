/*-------------------------------------------
Project 5 Part 1: Link Lint List - Find Shortest Word Ladder
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE / VSCode
Author: Areesh Nadeem
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;



// Opens a file with name <filename> and count the 
// number of words in the file that are exactly 
// <wordSize> letters long 
//     return the count, if filename is valid
//     return -1 if the file cannot be opened
int countWordsOfLength(char* filename, int wordSize) { 

    FILE* inFS = NULL;
    inFS = fopen(filename, "r");
    if (inFS == NULL) { return -1; } // unable to open file

    int count = 0;
    char word[81]; // word to scan from file

    while (!feof(inFS)) {
        fscanf(inFS, "%80s", word);
        if (strlen(word) == wordSize) { count++; }
    }
    fclose(inFS);

    return count;
}


// opens a file with name <filename> and fill the 
// pre-allocated word array <words> with only words
// that are exactly <wordSize> letters long;
// return true if successfully built, else returns false
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
   
    FILE* inFS = NULL;
    inFS = fopen(filename, "r");
    if (inFS == NULL) { return false; } // unable to open file

    int count = 0;
    char word[81];

    while (!feof(inFS)) {
        fscanf(inFS, "%80s", word);
        if (strlen(word) == wordSize) { 
            strcpy(words[count], word);
            count++; 
        }
    }
    fclose(inFS);

    if (numWords == count) { return true; } // if correct number of words in array
    else return false;
}



// Binary search for string <aWord> in an 
// alphabetically sorted array of strings <words>, 
// only between <loInd> & <hiInd>
//      return index of <aWord> if found
//      return -1 if not found b/w loInd & hiInd
int findWord(char** words, char* aWord, int loInd, int hiInd) { 

    while (hiInd >= loInd) {
        int mid = (hiInd + loInd) / 2;
        
        if (strcmp(words[mid], aWord) == 0) { return mid; } // found word
        else if (strcmp(words[mid], aWord) < 0) { loInd = mid + 1; } // search upper half
        else hiInd = mid - 1; // search lower half
    }

    return -1; // not found
}



// free up all heap-allocated space for <words>,
// which is an array of <numWords> C-strings
void freeWords(char** words, int numWords) {

    for (int i = 0; i < numWords; i++) {
        free(words[i]);
    }
    free(words);
}


// Inserts a newly allocated WordNode to the front of the ladder
// updates head node pointer as well 
void insertWordAtFront(WordNode** ladder, char* newWord) {

    // allocate space for newNode and assign data members
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    newNode->myWord = newWord;
    newNode->next = *ladder;
    *ladder = newNode; // reassign head node
}


// Finds & returns number of words in <ladder> list
int getLadderHeight(WordNode* ladder) {

    int height = 0;

    // iterate through ladder and iterate count
    while (ladder != NULL) {
        height++;
        ladder = ladder->next;
    }
    return height;
}


// Allocates space for a new [WordNode], set its 
// [myWord] subitem using <newWord> and insert
// it to the BACK/TAIL of <ladder>
void insertWordAtBack(WordNode** ladder, char* newWord) {

    // allocate space for newNode and assign data members
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    newNode->myWord = newWord;
    newNode->next = NULL;
    
    if (*ladder == NULL) { *ladder = newNode; } // edge case if list empty
    else {

        // go to tail node and then add the new node to the end
        WordNode* curr = *ladder;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}


// Makes a complete copy of <ladder> and return it;
WordNode* copyLadder(WordNode* ladder) {

    WordNode* ladderCopy = NULL;

    // append ladder->myWord to the ladderCopy for each node
    while (ladder != NULL) {
        insertWordAtBack(&ladderCopy, ladder->myWord);
        ladder = ladder->next;
    }
    return ladderCopy; 
}



// Free up all heap-allocated space for <ladder>;
// this does NOT include the actual words, 
void freeLadder(WordNode* ladder) {

    while (ladder != NULL) {
        WordNode* tempNode = ladder; // store ladder to be deleted 
        ladder = ladder->next;
        free(tempNode); // delete stored ladder
    }
}


// Allocate space for a new [LadderNode], set its 
// [topWord] subitem using <newLadder>; then, find
// the back of <list> and append the newly created
// [LadderNode] to the back.
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {

    // allocate space for newNode and assign data members
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    newNode->next = NULL;

    if (*list == NULL) { *list = newNode; }

    else {
        LadderNode* curr = *list;

        // find tail node then add to end
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}


// Pop the first ladder from the front of the list
// by returning the pointer to the head node of 
// the ladder that is the subitem of the head node
// of <list> AND updating the head node of <list>
// to the next [LadderNode]
WordNode* popLadderFromFront(LadderNode** list) {

    // edge case if empty
    if (*list == NULL) { return NULL; }

    // store value to remove 
    WordNode* poppedLadder = (*list)->topWord;

    // iterate the head pointer, store the original head
    LadderNode* temp = *list;
    *list = (*list)->next;

    free(temp);
    return poppedLadder;
}


// Frees up all heap-allocated space for <myList>
void freeLadderList(LadderNode* myList) {

    while (myList != NULL) {

        // next ladder to be freed
        LadderNode* next = myList->next;

        freeLadder(myList->topWord); // free word nodes in ladder
        free(myList); // free ladder

        myList = next; // go to next ladder
    }
}


// Algorithm to find the shortest word ladder
// from <startWord> to <finalWord> in the <words>
// word array, where each word is <wordSize> long 
// and there are <numWords> total words;
//     returns a pointer to the shortest ladder;
//     return NULL if no ladder is possible;
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {

    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;

    insertWordAtFront(&myLadder, startWord);
    insertLadderAtBack(&myList, myLadder);

    while (myList != NULL) {
        WordNode* myLadder = popLadderFromFront(&myList);
        char* word = myLadder->myWord;

        // iterate through each letter in the word
        for (int i = 0; i < wordSize; i++) {

            // store word in a temp var so it doesn't alter words[]
            char tempWord[wordSize+1];
            strcpy(tempWord, word);

            // iterate through all possible chars
            for (char j = 'a'; j <= 'z'; j++) {
                tempWord[i] = j;

                // index where word can be found in words[] (1:1 with usedWord[])
                int index = findWord(words, tempWord, 0, numWords-1);

                // if neighbor is equal to finalWord
                if (strcmp(tempWord, finalWord) == 0) {
                    insertWordAtFront(&myLadder, finalWord);
                    freeLadderList(myList);
                    return myLadder;
                }

                // otherwise if word has not been used
                // copy the ladder and add the word, then add the ladder to list
                if (index != -1 && usedWord[index] == false) {
                    usedWord[index] = true;
                    WordNode* anotherLadder = copyLadder(myLadder);
                    insertWordAtFront(&anotherLadder, words[index]);
                    insertLadderAtBack(&myList, anotherLadder);
                }
                
            }
        }
        freeLadder(myLadder);
    }

    // no ladder found
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
