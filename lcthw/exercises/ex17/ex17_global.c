#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DATA 512
#define MAX_ROWS 100
#define PHONE 12 // UK numbers, 11 digits

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
	char phone[PHONE];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	FILE *file;
	struct Database *db;
};

struct Connection *conn;

void Database_close()
{
	if (conn) {
		if (conn->file)
			fclose(conn->file);
		if (conn->db)
			free(conn->db);
		free(conn);
	}
}

void die(const char *message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Database_close(conn);
	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s %s", addr->id, addr->name, addr->email, addr->phone);
}

void Database_load()
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to load database.");
}

void Database_open(const char *filename, char mode)
{
	conn = malloc(sizeof(struct Connection));
	if (!conn)
		die("Memory error");

	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die("Memory error");

	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");

		if (conn->file)
			Database_load(conn);
	}

	if (!conn->file)
		die("Failed to open the file");

}

void Database_write()
{
	rewind(conn->file);

	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to write database.");

	rc = fflush(conn->file);
	if (rc == -1)
		die("Cannot flush database.");
}

void Database_create()
{
	int i = 0;

	for (i = 0; i < MAX_ROWS; i++) {
		// make a prototype to initialise it
		struct Address addr = {.id = i, .set = 0};
		// then just assign it
		conn->db->rows[i] = addr;
	}
}

void Database_set(int id, const char *name,
		const char *email, const char *phone)
{
	struct Address *addr = &conn->db->rows[id];
	if (addr->set)
		die("Already set, delete it first");
	
	addr->set = 1;
	char *res = strncpy(addr->name, name, MAX_DATA-1);
	addr->name[MAX_DATA-1] = '\0';
	if (!res)
		die("Name copy failed.");

	res = strncpy(addr->email, email, MAX_DATA-1);
	addr->email[MAX_DATA-1] = '\0';
	if (!res)
		die("Email copy failed.");

	res = strncpy(addr->phone, phone, PHONE-1);
	addr->phone[PHONE-1] = '\0';
	if (!res)
		die("Phone copy failed");
}

void Database_get(int id)
{
	struct Address *addr = &conn->db->rows[id];
	
	if (addr->set) {
		Address_print(addr);
		printf("\n");
	} else {
		die("ID is not set.");
	}
}

void Database_find(const char *find)
{
	struct Address *addr = conn->db->rows;
	int i = 0;
	bool found = false;
	for (i = 0; i < MAX_ROWS; i++) {
		if (addr->set &&
				(!strncmp(addr[i].name, find, MAX_DATA-1)
				 || !strncmp(addr[i].email, find, MAX_DATA-1)
				 || !strncmp(addr[i].phone, find, PHONE-1))) {
			found = true;
			break;
		}
	}

	if (found) {
		Address_print(&addr[i]);
		printf("\n");
	} else {
		printf("No match in database.");
	}
}
		

void Database_delete(int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list()
{
	int i = 0;
	struct Database *db = conn->db;
	
	for (i = 0; i < MAX_ROWS; i++) {
		struct Address *cur = &db->rows[i];

		if (cur->set) {
			Address_print(cur);
			printf("\n");
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		die("Usage: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	Database_open(filename, action);
	int id = 0;

	if (argc > 3) id = atoi(argv[3]); // strtol ideally
	if (id >= MAX_ROWS) die("Incorrect record number.");

	switch(action) {
		case 'c':
			Database_create();
			Database_write();
			break;

		case 'g':
			if (argc != 4)
				die("Need an id for get.");

			Database_get(id);
			break;

		case 's':
			if (argc != 7)
				die("Need id, name and email to set.");
			
			Database_set(id, argv[4], argv[5], argv[6]);
			Database_write();
			break;

		case 'd':
			if (argc != 4)
				die("Need id to delete");
			
			Database_delete(id);
			Database_write();
			break;

		case 'f':
			if (argc != 4)
				die("Need either name, email or phone");

			Database_find(argv[3]);
			break;

		case 'l':
			Database_list();
			break;

		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close();

	return 0;
}
