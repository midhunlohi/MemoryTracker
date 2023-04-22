#include "memtrack.h"
#include <stdio.h>
#include <stdlib.h>

/*Print a structure record in the db*/
void
print_struct_db_rec(struct_db_rec_t* rec) {
    if(!rec) return;
    int j = 0;
    struct_member_info_t *field = NULL;
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "| %-20s | size = %-8d | #flds = %-3d |\n" ANSI_COLOR_RESET, rec->struct_name, rec->size, rec->num_member);
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    for(j = 0; j < rec->num_member; j++){
        field = &rec->members[j];
        printf("  %-20s |", "");
        printf("%-3d %-20s | dtype = %-15s | size = %-5d | offset = %-6d|  nstructname = %-20s  |\n",
                j, field->member_name, DATA_TYPE[field->type], field->size, field->offset, field->nested_str_name);
        printf("  %-20s |", "");
        printf(ANSI_COLOR_CYAN "--------------------------------------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    }
}
/*Print a complete db*/
void
print_struct_db(struct_db_t* db) {
    if (!db) {
        return;        
    }
    unsigned int count = 0;
    printf("Printing the DB ( Registered structs : %d)\n", db->count);
    struct_db_rec_t* rec = db->head;
    while(rec) {
        printf("structure number = %d\n", count);
        print_struct_db_rec(rec);
        rec = rec->next;
        count++;
    }
    return;
}
/*Add a struct to struct db*/
int
add_struct_to_struct_db(struct_db_t* db, struct_db_rec_t* rec) {
    struct_db_rec_t* head = db->head;
    if (!head) {
        db->head = rec;
        rec->next = NULL;
        db->count++;
        return 0;
    }
    rec->next = head;
    db->head = rec;
    db->count++;
    return 0;
}