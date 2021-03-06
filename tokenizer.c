/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

enum states {
    undetermined,			//The begining of a token
    isAlphaNumeric, //Once a letter is found, it will be a word no matter what.
    done,
} curr_State, temp_State;

char err;
char* pc;
int onlySpaces = 0;

struct TokenizerT_ {
    int i;   			//Index number used later for creating tokens
    int stringSize;		//String size for getnexttoken function
    char *myString;		//input string
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

    TokenizerT *ptr = (TokenizerT*) malloc (sizeof(struct TokenizerT_));   //Allocation of size for TokenizerT_
    ptr -> i = 0;
    ptr -> stringSize = strlen(ts);
    ptr -> myString = ts;
    pc = (ptr -> myString);

    return ptr;           /*returning the pointer*/
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk -> myString);
    tk -> myString = NULL;
    free(tk);
    tk = NULL;
}


/*beginning of all states and function calls for states. Each function checks for the
 * current state and current char and makes a decision based on that.
 * It may change states or figure out that the current token is in a finished
 * state. Each function is called upon based on the previous state the FSM
 * was in. */

/* this will check whether or not the first character of token is a valid char of
 * (1-9), (this will be int or float), '0' (which will be float, hex, oct or zero state) or a letter (word)
 * or one of the many C operators or a malformed character. */
int isZeroLetterOrNot(char x) {
    if ((x >= 'a' && x <= 'z')||(x >= 'A' && x <= 'Z')) {
        curr_State = isAlphaNumeric;
    }
    return 0;
}

/*This function will check if the next character after the
 * first character in a word token is valid, if it is not
 * state becomes undetermined again*/
int isAlphaNumericOrNot(char x) {
    if (isalnum(x)) {
    }
    else {
        temp_State = curr_State;
        curr_State = done;
    }
    return 0;
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    if (*pc == '\0') {
        return NULL;
    }

    char* token = (char*) malloc (((tk -> stringSize)+2)*sizeof(char));
    char* tempToken = token;

    while (*pc != '\0' && !isalpha(*pc)) {
        pc++;
    }

    if (*pc == '\0' && onlySpaces == 0) {
        free(token);
        token = NULL;
        return NULL;
    }
    else if (*pc == '\0') {
        free(token);
        token = NULL;
        return NULL;
    }

    onlySpaces++;			//only if a nonspace is found;

    curr_State = undetermined;

    while (*pc != '\0') {
        if ((curr_State != done)&&(curr_State != undetermined)) {
            *token = *pc;
            pc++;
            token++;
        }
        switch(curr_State) {
            case (undetermined): {
                isZeroLetterOrNot(*pc);
                break;
            }
            case (isAlphaNumeric): {
                isAlphaNumericOrNot(*pc);
                break;
            }
            case (done): {
                *token = ' ';
                token++;
                *token = '\0';
                return tempToken;
            }
            default:
                break;
        }
    }
    *token = '\0';
    return tempToken;
}

void lowerCase(char * s) {
    for (; *s != '\0'; s++) {
        *s = tolower(*s);
    }
}

/*
 * tokenize will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

char* tokenize(char * str) {

    FILE * file = fopen(str, "r");

    char *fileContents;
    char *finalString;
    long fileSize;

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);
    fileContents = (char *)malloc((fileSize+1)*sizeof(char));
    finalString = (char *)malloc((fileSize+1)*sizeof(char));
    finalString[0] = '\0';
    fread(fileContents, sizeof(char), fileSize, file);
    fileContents[fileSize] = '\0';
    fclose(file);
    TokenizerT *tokenizer = TKCreate (fileContents);        //creation of tokenizerT
    curr_State = undetermined;
    char* token;

    while (*pc != '\0') {
        token = TKGetNextToken(tokenizer);
        if (token == NULL) {
            break;
        }
        lowerCase(token);
        strcat(finalString,token);
        free(token);
        token = NULL;
    }
    TKDestroy(tokenizer);
    char * temp = finalString;

    while (*temp != '\0') {
        if (*(temp+1) == '\0')
            break;
        temp++;
    }

    *temp = '\0';

    if (finalString[0] == '\0') {
        free(finalString);
        return NULL;
    }

    return finalString;
}
