#ifndef __MEMTRACK__H
#define __MEMTRACK__H

#define MAX_STRUCT_NAME_SIZE 128
#define MAX_MEMBER_NAME_SIZE 128

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/*Enumeration of data type*/
typedef enum data_type_ {
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
}data_type_t;

char *DATA_TYPE[] = {"UINT8", "UINT32", "INT32",
                     "CHAR", "OBJ_PTR", "FLOAT",
                     "DOUBLE", "OBJ_STRUCT"};

#define OFFSETOF(struct_name, fld_name) \
        (long int)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name) \
        sizeof(((struct_name *)0)->fld_name)

/*Data structure to hold the information about one structure member*/
typedef struct struct_member_info_{
    char member_name[MAX_MEMBER_NAME_SIZE];
    data_type_t type;
    unsigned int size;
    unsigned int offset;
    char nested_str_name[MAX_STRUCT_NAME_SIZE];
}struct_member_info_t;
/*Data structure to hold the information about one structure in data base*/
typedef struct struct_db_rec_{
    struct struct_db_rec_ *next;  /*Pointer to the next structure in the linked list*/
    char struct_name[MAX_STRUCT_NAME_SIZE];  // key
    unsigned int size;   /*Size of the structure*/
    unsigned int num_member;  /*No of fields in the structure*/
    struct_member_info_t *members;   /*pointer to the array of fields*/
}struct_db_rec_t;
/*Data structure to hold the information about complete data base*/
typedef struct struct_db_{
    struct_db_rec_t *head;
    unsigned int count;
}struct_db_t;
/*Print a structure record in the db*/
void
print_struct_db_rec(struct_db_rec_t*);
/*Print a complete db*/
void
print_struct_db(struct_db_t*);
/*Add a struct to struct db*/
int
add_struct_to_struct_db(struct_db_t*, struct_db_rec_t*);
/*Helper MACROs*/
#define POPULATE_STRUCT_MEMBER_INFO(struct_name, member_name, data_type, nested_struct_name) \
    {#member_name, data_type, FIELD_SIZE(struct_name, member_name), \
    OFFSETOF(struct_name, member_name), #nested_struct_name} \

#define REGISTER_STRUCT_TO_DB(struct_db, struct_name, member_arr) \
    do{                                                                     \
        struct_db_rec_t* rec = calloc(1, sizeof(struct_db_rec_t));          \
        strncpy(rec->struct_name, #struct_name, MAX_STRUCT_NAME_SIZE);      \
        rec->size = sizeof(struct_name);                                    \
        rec->num_member = sizeof(member_arr)/sizeof(struct_member_info_t);  \
        rec->members = member_arr;                                           \
        if (add_struct_to_struct_db(struct_db, rec)) {                      \
            assert(0);                                                       \
        }                                                                     \
    }while(0);                                                                  \

#endif