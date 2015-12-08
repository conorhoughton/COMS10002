//hash example from Ian Hoyer

/* Count the occurrences of words in a file, store them in a linked list and a
hash table, and measure the time taken to perform list/table operations.  Note:
on both Windows and Linux computers used for testing, times are only accurate
to 1/100 second.  The list time is usually 0.29s, but the hash table time is
sometimes 0.01s and sometimes 0.00s, so probably about 0.005s. */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// ----- Words -----

// The size of an array to store a word of up to 19 characters, and the
// format string for reading one in.
enum { W = 20 };
const char word_format[] = "%19s";

// Remove punctuation from a word (possibly leaving it empty).  Note: this is
// not ideal (e.g. don't -> dont) but there is no perfect algorithm, and it
// doesn't seem right to customise it based on just one actual file.
void clean(char word[W]) {
    char *punctuation = ".,;:*!?'-";
    int p=0;
    for (int i=0; i<strlen(word); i++) {
        char ch = word[i];
        if (strchr(punctuation, ch) == NULL) {
            word[p] = word[i];
            p++;
        }
    }
    word[p] = '\0';
}

// Read a word from a file into a char array.  Return false at the end of the
// file.  Remove all punctuation, and skip any 'words' which end up empty.
// Note: fscanf deals with line endings, but not punctuation.
bool read(char word[W], FILE *file) {
    bool done = false;
    fscanf(file, word_format, word);
    while (! feof(file) && ! done) {
        clean(word);
        done = strlen(word) != 0;
        if (! done) fscanf(file, word_format, word);
    }
    return done;
}

// ----- Lists -----

// A structure for storing a word and its count as a list node.
struct node {
    struct node *next;
    char word[W];
    int count;
};
typedef struct node node;

// A structure for storing a list, and its total count, and measurements.
// Note: the extra complication of a wrapping structure is more than paid back
// because (a) you don't have to return an updated structure from any of the
// functions (b) this leaves you free to return other things and (c) the
// wrapping structure is a convenient place to put measurements.
struct list {
    node *first;
    int total;
    int comparisons;
};
typedef struct list list;

// Create a new word-list.
list *new_list() {
    list *wl = malloc(sizeof(list));
    wl->first = NULL;
    wl->total = 0;
    return wl;
}

// Add a node to the start of a word-list. Takes O(1) time.
// Note: this is more efficient than adding the node at the end, but might
// cause the words to end up in a worse order.
void add_node(list *wl, node *n) {
    n->next = wl->first;
    wl->first = n;
}

// In a list, find the node containing a given word, or NULL. Takes O(n) time.
node *find_node(list *wl, char word[W]) {
    bool found = false;
    node *p = wl->first;
    while (p != NULL && ! found) {
        found = strcmp(p->word, word) == 0;
        if (! found) p = p->next;
    }
    return p;
}

// In a list, find a word, and count it or add it. Takes O(n) time.
void add_to_list(list *wl, char word[W]) {
    node *n = find_node(wl, word);
    if (n != NULL) {
        n->count++;
    }
    else {
        n = malloc(sizeof(node));
        strcpy(n->word, word);
        n->count = 1;
        add_node(wl, n);
    }
    wl->total++;
}

// Lookup a word in a list and return its count.  Put the number of
// comparisons into the list structure.
int lookup_in_list(list *ws, char word[W]) {
    bool found = false;
    ws->comparisons = 0;
    node *p = ws->first;
    while (p != NULL && ! found) {
        ws->comparisons++;
        if (strcmp(p->word, word) == 0) found = true;
        if (! found) p = p->next;
    }
    int count = 0;
    if (p != NULL) count = p->count;
    return count;
}

// Read an array of words into a list
list *read_list(int n, char words[n][W]) {
    list *wl = new_list();
    for (int i=0; i<n; i++) add_to_list(wl, words[i]);
    return wl;
}

// Free up all the space for a list.  Take care over the order of operations.
void free_list(list *words) {
    node *nodes = words->first;
    while (nodes != NULL) {
        node *p = nodes;
        nodes = nodes->next;
        free(p);
    }
    free(words);
}

// Measure the time it takes to build a list.  The words are passed in as a
// list, not read from a file, to avoid measuring disk time.  Note: if
// file or terminal I/O happens between start and stop, the I/O time
// would dominate the measurements and make them nearly useless.
double time_list(list *words) {
    double start = (double) clock();
    list *wl = new_list();
    node *p = words->first;
    while (p != NULL) {
        for (int i=0; i<p->count; i++) {
            add_to_list(wl, p->word);
        }
        p = p->next;
    }
    double end = (double) clock();
    free_list(wl);
    return (end - start) / CLOCKS_PER_SEC;
}

// ----- Hash tables -----

// Hash table size and type (array of lists)
enum { SIZE = 1000 };
struct table {
    list *slots[SIZE];
    int total;
    int comparisons;
};
typedef struct table table;

// Form a hash number from a word, given a hash table size (djb2 algorithm).
// Note: reduction modulo table size is only done at the end.
int hash(char word[W]) {
    unsigned long int hash = 5381;
    for (int i=0; i<strlen(word); i++) {
        char c = word[i];
        hash = ((hash << 5) + hash) + c;
    }
    return hash % SIZE;
}

// Create a new word-table.
table *new_table() {
    table *wt = malloc(sizeof(table));
    for (int i=0; i<SIZE; i++) wt->slots[i] = new_list();
    wt->total = 0;
    return wt;
}

// In a table, find a word, and count it or add it.  Can take O(1) time on
// average if the table is big enough.
void add_to_table(table *wt, char word[W]) {
    int h = hash(word);
    add_to_list(wt->slots[h], word);
    wt->total++;
}

// Lookup a word in a table and return the count.  Put the number of
// comparisons into the table structure.  Can take O(1) time.
int lookup_in_table(table *wt, char word[W]) {
    int h = hash(word);
    int count = lookup_in_list(wt->slots[h], word);
    wt->comparisons = wt->slots[h]->comparisons;
    return count;
}

// Read an array of words into a table
table *read_table(int n, char words[n][W]) {
    table *wt = new_table();
    for (int i=0; i<n; i++) add_to_table(wt, words[i]);
    return wt;
}

// Free up all the space for a table.
void free_table(table *wt) {
    for (int i=0; i<SIZE; i++) {
        if (wt->slots[i] != NULL) free_list(wt->slots[i]);
    }
    free(wt);
}

// Measure the time taken to build a table.  The words are passed in as a list,
// not read from a file, to avoid measuring disk time.  Note: time calculations
// are done using doubles, to avoid getting a whole number of seconds.
double time_table(list *words) {
    double start = (double) clock();
    table *wt = new_table();
    node *p = words->first;
    while (p != NULL) {
        for (int i=0; i<p->count; i++) {
            add_to_table(wt, p->word);
        }
        p = p->next;
    }
    double end = (double) clock();
    free_table(wt);
    return (end - start) / CLOCKS_PER_SEC;
}

// ----- Main program -----

// Read all the words from a file into a given array, so that timings don't
// include I/O.  If the array is NULL, just count the words.  That allows the
// function to be called twice, once to find out how big the array should be,
// and once to fill the array in.
int readFile(char *filename, char words[][W]) {
    FILE *file = fopen(filename, "r");
    char word[W];
    int count = 0;
    bool ok = read(word, file);
    while (ok) {
        if (words != NULL) strcpy(words[count], word);
        count++;
        ok = read(word, file);
    }
    fclose(file);
    return count;
}

// Process a series of queries from the user.
// Note: use fflush(stdout) before fgets(...,stdin) for safety.
void queries(list *lw, table *tw) {
    bool more = true;
    while (more) {
        char line[100];
        printf("Enter word for retrieval: ");
        fflush(stdout);
        fgets(line, 100, stdin);
        char word[W];
        sscanf(line, word_format, word);
        int n = lookup_in_list(lw, word);
        int c = lw->comparisons;
        printf("\n'%s' occurs %d times.\n", word, n);
        printf("Retrieval from list took %d comparisons.\n", c);
        n = lookup_in_table(tw, word);
        c = tw->comparisons;
        printf("Retrieval from table took %d comparisons.\n\n", c);
        printf("Another query? [y/n] ");
        fflush(stdout);
        fgets(line, 100, stdin);
        more = line[0] == 'y';
    }
}

// Read and process a file given on the command line.
int main(int n, char *args[n]) {
    if (n != 2) {
        fprintf(stderr, "Use: list filename\n");
        exit(1);
    }
    char *filename = args[1];
    int count = readFile(filename, NULL);
    char all_words[count][W];
    readFile(filename, all_words);

    list *wl = read_list(count, all_words);
    int total = wl->total;
    double time = time_list(wl);
    printf("\nReading into a list took %fs for %d words.\n", time, total);

    table *wt = read_table(count, all_words);
    total = wt->total;
    time = time_table(wl);
    printf("Reading into a table took %fs for %d words.\n\n", time, total);

    queries(wl, wt);
}
