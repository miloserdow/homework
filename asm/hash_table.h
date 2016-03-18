// hash table implementation took from past homework ;)
#define MXL 64

typedef struct entry_t entry_t;
typedef struct hashtable_t hashtable_t;
typedef unsigned long long hash_t;

const int p = 31;

struct entry_t {
	char *key;
	int value;
    entry_t *next;
};

struct hashtable_t {
	int size;
	entry_t **table;
    hash_t *precalc;
};

// stupid check for NULL (after malloc and related calls)
void chkNull(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "ERROR: allocation failed\n");
        exit(1);
    }
}

hash_t get_hash(hashtable_t *hashtable, char *s) {
	hash_t hashval = 0;
	int i = 0;
    for (i = 0; i < strlen(s); i++)
        hashval += ((s[i] - 'a' + 1) * hashtable->precalc[i]);
	return hashval % hashtable->size;
}

hashtable_t* init_table(int size) {
	if (size < 1)
        return NULL;
	int i;
    
    // allocate table
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    chkNull(hashtable);
    hashtable->table = malloc(sizeof(entry_t*) * size);
    chkNull(hashtable->table);
    
    // allocate precalculated pows of p
    hashtable->precalc = (hash_t*) malloc(sizeof(hash_t) * MXL);
    chkNull(hashtable->precalc);
    
    // do precalculations
    hashtable->precalc[0] = p;
    for (i = 1; i < MXL; i++)
        hashtable->precalc[i] = hashtable->precalc[i - 1] * p;
	
    for (i = 0; i < size; i++)
		hashtable->table[i] = NULL;
	hashtable->size = size;
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

void delete_element(hashtable_t *hashtable, char *key) {
    hash_t bin = get_hash(hashtable, key);
	entry_t *pair = hashtable->table[bin], *prev = NULL;
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0) {
        prev = pair; 
        pair = pair->next;
    }

    if (pair != NULL && pair->key != NULL && strcmp(key, pair->key) == 0) {
        // middle case
        if (pair->next != NULL && prev != NULL)
            prev->next = pair->next;
        else if (prev == NULL) // first in the chain
            hashtable->table[bin] = pair->next;
        else // last in the chain
            prev->next = NULL;
        free(pair->key);
        free(pair);
    }
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

void set_value(hashtable_t *hashtable, char *key, int val) {
	entry_t *newpair = NULL, *next = NULL, *last = NULL;
	hash_t bin = get_hash(hashtable, key);
	next = hashtable->table[bin];

	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0) {
		last = next;
		next = next->next;
	}

	// already exists
	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
		next->value = val;
	// not found - creating new
	} else {
		newpair = create_pair(key, val);
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

int get_value(hashtable_t *hashtable, char *key) {
	hash_t bin = get_hash(hashtable, key);
	entry_t *pair = hashtable->table[bin];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
	     pair = pair->next;
    
    // not found
    if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
	     return -1;
	else // found
	     return pair->value;
}
