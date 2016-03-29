
#pragma once

#include "db.h"

/**
 * Open up one of the three databases for Project 2, First Part
 */
int proj2_open(DB **db, const char *filename, DBTYPE type);

/**
 * Close the database
 */
int proj2_close(DB *db);

/**
 * Insert a key-value pair
 */
int proj2_insert(DB *db, int key, const char *value);


/**
 * Get a single record by it's key
 * Value is returned in value
 */
int proj2_getbykey(DB *db, int key, DBT *value);

/**
 * Get a single record by it's value
 */
int proj2_getbyvalue(DB *db, const char *value, int *key);

/**
 * Get each record with min <= key <= max
 */
typedef void (*HandleRecordProc)(int key, const char *value);
int proj2_getinrange(DB *db, int low, int high, HandleRecordProc handler);