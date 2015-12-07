#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#define MX 64

typedef struct entry_t entry_t;
typedef struct hashtable_t hashtable_t;
typedef unsigned long long hash_t;

const int p = 31;
FILE *in, *out;

struct entry_t {
	char *key;
	int value;
    entry_t *next;
};

struct hashtable_t {
	int size;
	entry_t **table;
    hash_t *precalc;
    hash_t (*hash_func)(hashtable_t*, char*);	
};

// stupid check for NULL (after malloc and related calls)
void chkNull(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: allocation failed\n");
        exit(1);
    }
}

hashtable_t* init_table(hash_t (*hash_func)(hashtable_t*, char*), int size) {
	if (size < 1)
        return NULL;
	int i;
    
    // allocate table
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    chkNull(hashtable);
    hashtable->table = malloc(sizeof(entry_t*) * size);
    chkNull(hashtable->table);
    
    // allocate precalculated pows of p
    hashtable->precalc = (hash_t*) malloc(sizeof(hash_t) * MX);
    chkNull(hashtable->precalc);
    
    // do precalculations
    hashtable->precalc[0] = p;
    for (i = 1; i < MX; i++)
        hashtable->precalc[i] = hashtable->precalc[i - 1] * p;
	
    for (i = 0; i < size; i++)
		hashtable->table[i] = NULL;
	hashtable->size = size;
    hashtable->hash_func = hash_func;
	return hashtable;	
}

void delete_table(hashtable_t *hashtable) {
    int i;
    for (i = 0; i < hashtable->size; i++) {
        entry_t *pair = hashtable->table[i], *tmp;
        while (pair != NULL) {
            free(pair->key);
            tmp = pair->next;
            free(pair);
            pair = tmp;
        }
    }
    free(hashtable->table);
    free(hashtable->precalc);
    free(hashtable);
}
        
hash_t get_hash(hashtable_t *hashtable, char *s) {
	hash_t hashval = 0;
	int i = 0;
    for (i = 0; i < strlen(s); i++)
        hashval += ((s[i] - 'a' + 1) * hashtable->precalc[i]);
	return hashval % hashtable->size;
}

hash_t hash2(hashtable_t *hashtable, char *s) {
    return 10000 % hashtable->size;
}

hash_t hash3(hashtable_t *hashtable, char *s) {
    hash_t h = 0;
    int i = 0;
    for (i = 0; i < strlen(s); i++)
        h += s[i];
    return h % hashtable->size;
}

entry_t *create_pair(char *key, int val) {
	entry_t *newpair;
    newpair = malloc(sizeof(entry_t));
	chkNull(newpair);
    newpair->key = strdup(key);
	chkNull(newpair->key);
    newpair->value = val;
	newpair->next = NULL;
	return newpair;
}

void inc_value(hashtable_t *hashtable, char *key) {
	entry_t *newpair = NULL, *next = NULL, *last = NULL;
	hash_t bin = hashtable->hash_func(hashtable, key);
	next = hashtable->table[bin];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
	}
    
	// already exists
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		next->value += 1;
	// not found - creating new
	} else {
		newpair = create_pair(key, 1);
		// start
		if (next == hashtable->table[bin]) {
			newpair->next = next;
			hashtable->table[bin] = newpair;
		// end
		} else if (next == NULL) {
			last->next = newpair;
		// mid
		} else  {
			newpair->next = next;
			last->next = newpair;
		}
	}
}

void print_stats(hashtable_t *hashtable) {
    int i, non_empty = 0, min_len = 1e9, max_len = -1, cnt = 0;
    float avg_len = 0;
    for (i = 0; i < hashtable->size; i++) {
        entry_t *pair = hashtable->table[i];
        if (pair == NULL)
            continue; // empty one
        non_empty++;
        int cur_len = 0;
        while (pair != NULL && pair->key != NULL) {
            cnt++;
            cur_len++;
            fprintf(out, "%s: %d\n", pair->key, pair->value);
            pair = pair->next;
        }
        if (cur_len < min_len)
            min_len = cur_len;
        if (cur_len > max_len)
            max_len = cur_len;
        avg_len += cur_len;
    }
    avg_len /= (float) non_empty;
    printf("Total:\n");
    printf("Elements number: %d\n", cnt);
    printf("Occupied cells: %d\n", non_empty);
    printf("Average chain len: %.1f\n", avg_len);
    printf("Min chain len: %d\n", min_len);
    printf("Max chain len: %d\n", max_len);
}

int get_value(hashtable_t *hashtable, char *key) {
	hash_t bin = hashtable->hash_func(hashtable, key);
	entry_t *pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
	     pair = pair->next;
    
    // not found
    if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
	     return 0;
	else // found
	     return pair->value;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    in  = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    char s[256];
    
    time_t start = clock();
    hashtable_t *hashtable = init_table(get_hash, 1024);
    while (fscanf(in, "%s ", s) == 1) {
        inc_value(hashtable, s);
    }
    print_stats(hashtable);
    delete_table(hashtable);
    printf("polyhash: %f sec.\n", (clock() - start)/(double)CLOCKS_PER_SEC);
    
    start = clock();
    hashtable = init_table(hash2, 1024);
    fseek(in, 0, SEEK_SET);
    while (fscanf(in, "%s ", s) == 1) {
        inc_value(hashtable, s);
    }
    print_stats(hashtable);
    delete_table(hashtable);
    printf("const. hash: %f sec.\n", (clock() - start)/(double)CLOCKS_PER_SEC);
    
    start = clock();
    hashtable = init_table(hash3, 1024);
    fseek(in, 0, SEEK_SET);
    while (fscanf(in, "%s ", s) == 1) {
        inc_value(hashtable, s);
    }
    print_stats(hashtable);
    delete_table(hashtable);
    printf("char. sum: %f sec.\n", (clock() - start)/(double)CLOCKS_PER_SEC);
    return 0;
}

