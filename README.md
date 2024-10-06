# Project 5 Part 1: Link Lint List - Find Shortest Word Ladder
**Course**: CS 211, Spring 2024, UIC  
**System**: ZyLabs IDE / VSCode  
**Author**: Areesh Nadeem  

## Overview

This project implements a **Word Ladder Generator**. A word ladder is a sequence of words where each word differs from the previous one by exactly one letter. The program attempts to find the **shortest possible word ladder** between two words of the same length. 

The main algorithm works by:

1. **Reading the input file**: A dictionary file containing a list of words is loaded. The program filters words that are of a specific length (e.g., all 5-letter words).
2. **Searching for a word ladder**: The user provides two words, and the program finds the shortest sequence of transformations that changes the start word into the final word.
3. **Using Breadth-First Search (BFS)**: The algorithm explores possible words by changing one letter at a time and checks if the new word exists in the dictionary. If it does, it's added to the ladder.
4. **Displaying the result**: If a valid ladder is found, the program prints the ladder and its height (the number of words in the sequence). If no ladder exists, it prints a message saying so.

## Key Functions

- `countWordsOfLength`: Counts the number of words in a file that have a specific length.
- `buildWordArray`: Fills an array with words of the given length from the dictionary file.
- `findWord`: Performs a binary search to locate a word in a sorted array.
- `insertWordAtFront` and `insertWordAtBack`: Insert words at the front or back of a linked list (the word ladder).
- `findShortestWordLadder`: The main BFS-based algorithm that generates the shortest word ladder between two words.
- `setWord`: Ensures the word provided by the user is in the dictionary and meets the length requirement.
- `printLadder` and `printList`: Helper functions to print the current word ladder or a list of ladders.
- `freeLadder`, `freeLadderList`, `freeWords`: Free dynamically allocated memory to prevent memory leaks.

## Program Flow

1. The user selects a word size and inputs a dictionary file.
2. The program builds an array of words from the dictionary that match the selected length.
3. The user is asked to input a start and final word.
4. The program runs the BFS algorithm to find the shortest word ladder between the two words.
5. The result is printed, and the memory used by the program is freed.

## Important Notes
- The word array is dynamically allocated based on the number of words that match the specified length.
- The program ensures that the start and final words are valid and different.
- The dictionary must contain at least two words of the given length for the program to function.
- The algorithm will pick a random word if the user fails to input a valid word after five tries.
