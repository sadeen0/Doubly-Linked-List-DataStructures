/* Sadeen
 * 1212164
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Doubly Linked List
typedef struct Node {
    char Word[30]; // String with 30 characters
    struct Node* prev;
    struct Node* next;
} Node;

typedef Node* List;
typedef Node* ptrToNode;

List MakeEmpty(List list);
void DeleteList(List list);
int size(List list);
List Find(char string[30], List list);
void PrintList(List list, int isSorted);
void Menu();
void SortStrings(List list);
List ReadFromFile(const char *filename);
List CopyList(List original);
void AddNewWord(List list, char newWord[30]);
void Insert(char newWord[30], List list);
void DeleteWord(List list, char word[30]);
void SaveToFile(List list);

int main() {
    int s;
    struct Node* FileList =  (struct Node *) malloc(sizeof(struct Node));
    struct Node* SortedList=(struct Node *) malloc(sizeof(struct Node));
    FileList->next=NULL;
    SortedList->next=NULL;
    FileList->prev=NULL;
    SortedList->prev=NULL;
    int sorted = 0; // Flag to track if the strings have been sorted

    do {
        Menu();
        scanf("%d", &s);

        switch (s) {

            case 1: {
                // Load strings from the input file to the original list
                FileList= ReadFromFile("WordsFile.txt");
                // Copy the original list to the sorted list
                SortedList = CopyList(FileList);
                sorted = 0; // Reset the sorted flag

                // printf("size = %d", size(FileList));
                break;
            }

            case 2: {
                // Print the original strings from the file
                if (FileList == NULL) {
                    printf("No strings loaded.\n");
                }
                else {
                    PrintList(FileList, 0); // 0 represents unsorted list
                }
                break;
            }

            case 3: {
                // Sort the strings in the sorted list
                if (SortedList== NULL) {
                    printf("No strings loaded.\n");
                }
                else {
                    SortStrings(SortedList);
                    printf("Strings sorted successfully!\n\n");
                    sorted = 1; // Update the sorted flag
                }
                break;
            }

            case 4: {
                // Print the sorted strings
                if (SortedList == NULL) {
                    printf("No strings loaded.\n");
                }
                else if (sorted == 0) {
                    printf("The strings have not been sorted yet.\n\n");
                }
                else {
                    PrintList(SortedList, 1); // 1 represents sorted list
                }
                break;
            }

            case 5: {
                // Add a New Word to the list of Sorted Strings (And Sort it)
                char newWord[30];
                if (SortedList == NULL) {
                    printf("No strings loaded.\n");
                }
                else {

                    printf("Enter a New Word to be added: ");
                    scanf("%s", newWord);
                    AddNewWord(SortedList,newWord);
                    SortStrings(SortedList);
                    sorted = 1; // Update the sorted flag
                    printf("New word added and strings sorted successfully!\n\n");
                }
                break;
            }

            case 6: {
                // Delete a Word From the Sorted Strings
                char deleteWord[30];
                if (SortedList == NULL) {
                    printf("No strings loaded.\n");
                }
                else {
                    printf("Enter the word to delete: ");
                    scanf("%s", deleteWord);
                    DeleteWord(SortedList,deleteWord);
                }
                break;
            }

            case 7: {
                // Save to Output File
                if (SortedList == NULL) {
                    printf("No strings loaded.\n");
                }
                else {
                    SaveToFile(SortedList);
                    printf("Sorted strings saved to the output file successfully!\n\n");
                }
                break;
            }

            case 8: {
                return 0;
            }

            default: {
                printf("Invalid Choice. Please try again.\n");
                break;
            }
        }
    } while (1);
}

void Menu() {
    printf("HELLO, Choose one :\n");
    printf("  1- Load the Strings\n");
    printf("  2- Print the Strings before Sorting\n");
    printf("  3- Sort the Strings\n");
    printf("  4- Print the Sorted Strings\n");
    printf("  5- Add a New Word to the list of Sorted Strings (And Sort it)\n");
    printf("  6- Delete a Word From the Sorted Strings\n");
    printf("  7- Save to Output File\n");
    printf("  8- Exit\n");
}

// Function to create an empty list
List MakeEmpty(List list) {
    if (list!= NULL)
        DeleteList(list);
    list = (struct Node *) malloc(sizeof(struct Node));

    if (list == NULL)
        printf("Out of memory!\n");

    list->next = NULL;
    return list;
}

void DeleteList(struct Node *L)
{
    struct Node *P = (struct Node *) malloc(sizeof(struct Node)),
            *temp = (struct Node *) malloc(sizeof(struct Node));
    P = L;
    L->next = NULL;

    while (P->next != NULL)
    {
        temp = P->next;
        free(P);
        P = temp;
    }

}
List Find(char string[30], List list) {
    ptrToNode testPtr = list->next;

    while (testPtr != NULL && testPtr->Word != string) {
        testPtr = testPtr->next;
    }
    return testPtr;
}

void PrintList(List list, int isSorted) {
    ptrToNode temp = list;

    if (temp == NULL) {
        printf("Empty List!\n");
        return;
    }

    if (isSorted) {
        printf("List of Strings after Sorting :\n");
    }
    else {
        printf("List of Strings before Sorting :\n");
    }

    while (temp->next != NULL) {
        printf("%s\n", temp->next->Word);
        temp = temp->next;
    }
    printf("\n");
}

void SortStrings(List list) {
    List array[63]; //struct Node* array[63];
    for (int i = 0; i < 63; ++i) {
        array[i] = (struct Node *) malloc(sizeof(Node));
        array[i]->next = NULL;
        array[i]->prev=NULL;
    }

    struct Node * ptr;

    for (int i = 30; i >= 0; i--) {
        ptr = list;
        list->next->prev = NULL; // head = NULL
        while (ptr->next != NULL) {
            //free(ptr->prev);
            char character = ptr->next->Word[i]; // current data
            int index = 0;
            if (character >= '0' && character <= '9')  // 1-9
                index = character - '0' + 1;
            else if (character >= 'A' && character <= 'Z') // A-Z
                index = character - 'A' + 11;
            else if (character >= 'a' && character <= 'z') // a-z
                index = character - 'a' + 37;
            else {
                index = 0;
            }
            Insert(ptr->next->Word, array[index]);
            ptr=ptr->next;
        }
        MakeEmpty(list);
        for (int i = 0; i < 63; i++) {
            ptr->next = array[i]->next;
            while (ptr->next != NULL) {
                Insert(ptr->next->Word, list);//here we insert the LL of the bucket pointed node
                ptr = ptr->next;
            }
        }
        MakeEmpty(ptr);
        for (int j = 0; j < 63; ++j) {
            MakeEmpty(array[j]);
            array[j]->next=NULL;
        }
    }
}

List ReadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    List list =(Node*)malloc(sizeof(Node));
    ptrToNode tail = NULL;

    if (file == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    char word[31];
    //read a words line by line, One word in each Line
    while (fscanf(file, "%s", word) != EOF) {
        ptrToNode newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Out of Memory!\n");
            return NULL;
        }
        strcpy(newNode->Word, word);
        newNode->next = NULL;
        newNode->prev = tail;

        if (tail != NULL) {
            tail->next = newNode;
        }
        else {
            list->next = newNode;
        }
        tail = newNode;
    }

    fclose(file);
    return list;
}

List CopyList(List original) {
    List newList = MakeEmpty(newList);
    ptrToNode temp = original;
    ptrToNode tail = NULL;

    while (temp != NULL) {
        ptrToNode newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            printf("Out of Memory!\n");
            return NULL;
        }
        strcpy(newNode->Word, temp->Word);
        newNode->next = NULL;
        newNode->prev = tail;

        if (tail != NULL) {
            tail->next = newNode;
        }
        else {
            newList = newNode;
        }
        tail = newNode;
        temp = temp->next;
    }

    return newList;
}


void AddNewWord(List list,char newWord[30]) {
    ptrToNode newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Out of Memory!\n");
        return;
    }

    strcpy(newNode->Word, newWord);
    newNode->next = NULL;

    ptrToNode temp = list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void Insert(char newWord[30], List list) {

    struct Node *temp, *P = list;

    temp = (struct Node *) malloc(sizeof(struct Node));

    strcpy(temp->Word,newWord);

    while (P->next != NULL)
        P = P->next;

    P->next = temp;

    temp->next = NULL;
    temp->prev = P;

}

void DeleteWord(List list, char word[30]) {
    ptrToNode temp = list;
    ptrToNode prev = NULL;

    // If the first node has the word to delete
    if (strcmp(temp->Word, word) == 0) {
        list = temp->next;
        if (list != NULL) {
            list->prev = NULL;
        }
        free(temp);
        return;
    }

    while (temp != NULL && strcmp(temp->Word, word) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Word not found.\n");
        return;
    }

    prev->next = temp->next;
    if (temp->next != NULL) {
        temp->next->prev = prev;
    }
    free(temp);

    printf("Word deleted successfully!\n\n");
}


void SaveToFile(List list) {
    FILE *file = fopen("OutputFile.txt", "w");

    if (file == NULL) {
        printf("Error creating the file.\n");
        return;
    }

    ptrToNode temp = list;

    while (temp->next != NULL) {
        fprintf(file, "%s\n", temp->next->Word);
        temp = temp->next;
    }

    fclose(file);
}