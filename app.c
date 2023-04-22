#include <stdio.h>
#include <stdlib.h>
#include "memtrack.h"

/*App data structures*/

typedef struct emp_ {

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
} emp_t;

typedef struct student_{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_college;
} student_t;

int 
main() {
    /*1. Allocate a DB*/
    struct_db_t* db = (struct_db_t*)calloc(1, sizeof(struct_db_t));
    if (!db) {
        printf("Failed to calloc()\n");
        return 0;
    }    
    /*2. Add emp_t struct to DB*/
    static struct_member_info_t struct_emp_members[] = {
        POPULATE_STRUCT_MEMBER_INFO(emp_t, emp_name, CHAR, 0),
        POPULATE_STRUCT_MEMBER_INFO(emp_t, emp_id, UINT32, 0),
        POPULATE_STRUCT_MEMBER_INFO(emp_t, age, UINT32, 0),
        POPULATE_STRUCT_MEMBER_INFO(emp_t, mgr, OBJ_PTR, emp_t),
        POPULATE_STRUCT_MEMBER_INFO(emp_t, salary, FLOAT, 0),
    };
    REGISTER_STRUCT_TO_DB(db, emp_t, struct_emp_members);    
    /*3. Add student_t struct to DB*/    
    static struct_member_info_t struct_student_members[] = {
        POPULATE_STRUCT_MEMBER_INFO(student_t, stud_name, CHAR, 0),
        POPULATE_STRUCT_MEMBER_INFO(student_t, rollno, UINT32, 0),
        POPULATE_STRUCT_MEMBER_INFO(student_t, age, UINT32, 0),
        POPULATE_STRUCT_MEMBER_INFO(student_t, aggregate, FLOAT, emp_t),
        POPULATE_STRUCT_MEMBER_INFO(student_t, best_college, OBJ_PTR, student_t),
    };
    REGISTER_STRUCT_TO_DB(db, student_t, struct_student_members);    
    /*Print full DB*/
    print_struct_db(db);
    return 0;
}