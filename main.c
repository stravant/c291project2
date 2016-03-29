
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "db.h"

#include "database.h"

int main(int argc, char *argv[]) {
// 	printf("Test\n");

// 	int err;
// 	DB *store;
// 	if ((err = db_create(&store, NULL, 0)) != 0) {
// 		printf("error: %d\n", err);
// 		return -1;
// 	} else {
// 		printf("created\n");
// 	}

// 	if ((err = store->open(store, NULL, "test.db", NULL, DB_BTREE, DB_CREATE, 0)) != 0) {
// 		printf("error opening\n");
// 		return -1;
// 	} else{
// 		printf("opened\n");
// 	}

// 	char *sname = "blah";
// 	char *svalue = "test";
// 	DBT key, value;
// 	memset(&key, 0, sizeof(key));
// 	memset(&value, 0, sizeof(value));
// 	key.data = sname;
// 	key.size = strlen(sname);
// 	value.data = svalue;
// 	value.size = strlen(svalue);

// 	if ((err = store->put(store, NULL, &key, &value, 0)) != 0) {
// 		printf("error putting\n");
// 		goto cleanup;
// 	} else {
// 		printf("Put data\n");
// 	}

// 	DBT rvalue;
// 	memset(&rvalue, 0, sizeof(rvalue));
// 	char valuebuffer[20];
// 	rvalue.data = valuebuffer;
// 	rvalue.ulen = 20;
// 	rvalue.flags = DB_DBT_USERMEM;

// 	if ((err = store->get(store, NULL, &key, &rvalue, 0)) != 0) {
// 		printf("error getting\n");
// 		goto cleanup;
// 	} else {
// 		printf("Got: '%.*s'\n", rvalue.size, (char*)rvalue.data);
// 	}

// cleanup:
// 	if ((err = store->close(store, 0)) != 0) {
// 		printf("Error closing\n");
// 		return -1;
// 	} else {
// 		printf("Done\n");
// 	}

	DB *store;
	proj2_open(&store, "tree.db", DB_BTREE);

	proj2_insert(store, 10, "ten");
	proj2_insert(store, 5, "five");

	int res;
	proj2_getbyvalue(store, "five", &res);
	printf("Result: 'five' -> %d\n", res);

	char buffer[32];
	DBT key = {0};
	key.ulen = 32;
	key.data = buffer;
	key.flags = DB_DBT_USERMEM;
	proj2_getbykey(store, 5, &key);
	printf("Result: 5 -> '%.*s'\n", key.size, (char*)key.data);

	return 0;
}