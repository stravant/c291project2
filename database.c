
#include "database.h"

#include "string.h"


int int_comparison(DB *db, const DBT *a, const DBT *b) {
	int ia = *((int*)(a->data));
	int ib = *((int*)(b->data));
	if (ia < ib) {
		return -1;
	} else if (ia == ib) {
		return 0;
	} else {
		return 1;
	}
}


int proj2_open(DB **db, const char *filename, DBTYPE type) {
	// Variables needed
	int err;
	DB *store;

	// Create struct 
	if ((err = db_create(&store, NULL, 0)) != 0)
		return err;

	// Comparison function
	

	// Open
	if ((err = store->open(store, NULL, filename, NULL, type, DB_CREATE, 0)) != 0)
		return err;

	struct foo {
		int a, b;
	};

	// Return
	*db = store;
	return 0;
}

int proj2_use_bt_compare(DB *db) {
	db->set_bt_compare(db, int_comparison);
}


int proj2_use_h_compare(DB *db) {
	db->set_h_compare(db, int_comparison);
}


int proj2_close(DB *db) {
	// Close
	int err;
	if ((err = db->close(db, 0)) != 0)
		return err;

	return 0;
}


int proj2_insert(DB *db, int key, const char *value) {
	// Key and value storage
	DBT tkey = {0};
	DBT tvalue = {0};

	// Key
	tkey.size = sizeof(int);
	tkey.data = &key;

	// Value
	tvalue.size = strlen(value);
	tvalue.data = (char*)value;

	// Insert
	int err;
	if ((err = db->put(db, NULL, &tkey, &tvalue, 0)) != 0)
		return err;

	return 0;
}


int proj2_getbykey(DB *db, int key, DBT *value) {
	// Key
	DBT tkey = {0};
	tkey.data = &key;
	tkey.size = sizeof(int);

	// Get
	int err;
	if ((err = db->get(db, NULL, &tkey, value, 0)) != 0)
		return err;

	return 0;
}


int proj2_getbyvalue(DB *db, const char *value, int *key) {
	// Get a cursor
	DBC *cursor;
	int err;
	if ((err = db->cursor(db, NULL, &cursor, 0)) != 0)
		return err;

	// Iterate each value
	int tmpkey;
	char tmpvalue[32];
	DBT tkey = {0};
	DBT tvalue = {0};
	tkey.ulen = sizeof(int);
	tkey.data = &tmpkey;
	tkey.flags = DB_DBT_USERMEM;
	tvalue.ulen = 32;
	tvalue.data = tmpvalue;
	tvalue.flags = DB_DBT_USERMEM;
	while ((err = cursor->get(cursor, &tkey, &tvalue, DB_NEXT)) == 0) {
		if (strncmp(value, tvalue.data, tvalue.size) == 0) {
			// Found
			*key = *((int*)tkey.data);
			cursor->close(cursor);
			return 0;
		}
	}
	cursor->close(cursor);
	return err;
}


int proj2_getinrange(DB *db, int low, int high, HandleRecordProc handler) {
	// Get a cursor
	DBC *cursora, cursorb;
	int err;
	if ((err = db->cursor(db, NULL, &cursor, 0)) != 0)
		return err;
	if ((err = db->cursor(db, NULL, &cursor, 0)) != 0)
		return err;

	// First in range
	err = cursor->get(cursor, &tkey, &tvalue, DB_SET_RANGE);
	while (err == 0) {
		// Handle record
		handler(*((int*)tkey.data), tvalue.data);

		// Next record
		err = cursor->get(cursor, &tkey, &tvalue, DB_NEXT);
	}

	// TODO:
	return -1;
}