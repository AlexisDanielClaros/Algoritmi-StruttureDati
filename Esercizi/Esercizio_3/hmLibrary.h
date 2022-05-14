
typedef struct hashNode hashNode;
typedef struct hashMap hashMap;
typedef int (*Type)(void*, int);
typedef int (*Compare)(hashNode*, hashNode*);

// Create a new hashmap and set all Nodes to null
hashMap* new_hm();

//Resize the capacity of an existing hashmap
void resize_hm(hashMap* table);

// Create the hash
int numericHash(int key,int capacity);
int stringHash(char* key,int capacity);

// Destroy an hashmap
void destroy_hm(hashMap* table);

// Check if the hashmap is empty
int is_empty(hashMap* table);

hashNode* set(hashMap* table, void* key, void* value);

// Return the numbers of Nodes in an hashmap
int number_of_nodes(hashMap* table);

// Insert a Node in an hashmap
void insert_Node(hashMap* table, void* key, void* value);

// Return the value of a key in an hashmap
void* get_value(hashMap* table, void* key);

// Cancel a node in an hashmap
void delete_element(hashMap* table, void* key);

// Return all keys of an hashmap
void* get_all_keys(hashMap* table);

// Check if there is a certain key in an hashmap
int is_inside(hashMap* table, void* key);