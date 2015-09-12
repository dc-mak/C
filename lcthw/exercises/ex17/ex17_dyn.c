#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

/* IMPORTANT: HAD I KNOW ABOUT C VLAs (VARIABLE SIZE ARRAYS) THEN THIS CODE
 * COULD HAVE LOOKED CONSIDERABLY DIFFERENT. ALTHOUGH ONE WOULD HAVE TO BE
 * CAREFUL ABOUT THE SCOPE OF SUCH DECLARATIONS. */
struct Address {
	int id;
	bool set;
	char *name;
	char *email;
};

struct Database {
	int MAX_STRLEN;
	int MAX_ADDR;
	// points to Address *ARRAY*
	struct Address *adds;
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Address_close(struct Database* db)
{
	int i = 0;
	for (i = 0; i < db->MAX_ADDR; i++) {
		free(db->adds[i].name);
		free(db->adds[i].email);
	}

	free(db->adds);
}

void Database_close(struct Connection *conn)
{
	if (conn) {
		if (conn->file)
			fclose(conn->file);

		if (conn->db) {
			Address_close(conn->db);
			free(conn->db);
		}
		free(conn);
	}
}

void die(struct Connection *conn, const char *message)
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
	printf("%d %s %s", addr->id, addr->name, addr->email);
}

void Address_load(struct Connection *conn)
{
	int i = 0;
	int MAX_STRLEN = conn->db->MAX_STRLEN;
	int MAX_ADDR = conn->db->MAX_ADDR;
	conn->db->adds = malloc(MAX_ADDR*sizeof(struct Address));

	struct Address *addr = conn->db->adds;
	for (i = 0; i < MAX_ADDR; i++) {
		int rc = fread(&addr[i].id, sizeof(int), 1, conn->file);
		if (rc != 1)
			die(conn, "Failed to load database.");

		rc = fread(&addr[i].set, sizeof(bool), 1, conn->file);
		if (rc != 1)
			die(conn, "Failed to load database.");

		addr[i].name = malloc(MAX_STRLEN*sizeof(char));
		rc = fread(addr[i].name, sizeof(char), MAX_STRLEN, conn->file);
		if (rc != MAX_STRLEN)
			die(conn, "Failed to load database.");

		addr[i].email = malloc(MAX_STRLEN*sizeof(char));
		rc = fread(addr[i].email, sizeof(char), MAX_STRLEN, conn->file);
		if (rc != MAX_STRLEN)
			die(conn, "Failed to load database.");
	}
}

void Database_load(struct Connection *conn)
{
	// assert(!conn->db);
	int rc = fread(&conn->db->MAX_STRLEN, sizeof(int), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to load database.");

	rc = fread(&conn->db->MAX_ADDR, sizeof(int), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to load database.");

	Address_load(conn);
}

void Database_create(struct Connection *conn,
		int MAX_STRLEN, int MAX_ADDR) 
{
	conn->db->MAX_STRLEN = MAX_STRLEN;
	conn->db->MAX_ADDR = MAX_ADDR;

	conn->db->adds = malloc(MAX_ADDR * sizeof(struct Address));
	if (!conn->db->adds)
		die(conn, "Failed to open file.");

	int i = 0;
	for (i = 0; i < MAX_ADDR; i++) {
		// make a prototype to initialise it
		struct Address addr = {.id = i, .set = false, .name = NULL, .email = NULL};
		// then just assign it
		conn->db->adds[i] = addr;
	}
}

struct Connection *Connection_open(const char *filename)
{
	struct Connection conn;
	if (!conn)
		die(&conn, "Memory error");

	struct Database db;
	conn.db = &db;
	if (!conn.db)
		die(&conn, "Memory error");

	return &conn;
}

void Address_write(struct Connection *conn)
{
	int i = 0;
	int MAX_STRLEN = conn->db->MAX_STRLEN;
	int MAX_ADDR = conn->db->MAX_ADDR;
	char *blank = malloc(2*MAX_STRLEN*sizeof(char));
	for (i = 0; i < 2*MAX_STRLEN; i++) {
		blank[i] = '\0';
	}

	struct Address *addr = conn->db->adds;
	for (i = 0; i < MAX_ADDR; i++) {
		int rc = fwrite(&addr[i].id, sizeof(int), 1, conn->file);
		if (rc != 1) {
			die(conn, "Failed to write database.");
			free(blank);
		}

		rc = fwrite(&addr[i].set, sizeof(bool), 1, conn->file);
		if (rc != 1) {
			die(conn, "Failed to write database.");
			free(blank);
		}

		if (addr[i].set) {
			rc = fwrite(addr[i].name, sizeof(char), MAX_STRLEN, conn->file);
			if (rc != MAX_STRLEN) {
				die(conn, "Failed to write database.");
				free(blank);
			}

			rc = fwrite(addr[i].email, sizeof(char), MAX_STRLEN, conn->file);
			if (rc != MAX_STRLEN) {
				die(conn, "Failed to write database.");
				free(blank);
			}
		} else {
			rc = fwrite(&blank, sizeof(char), 2*MAX_STRLEN, conn->file);
			if (rc != 2*MAX_STRLEN) {
				die(conn, "Failed to write database.");
				free(blank);
			}
		}
	}

	free(blank);
}


void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fwrite(&conn->db->MAX_STRLEN, sizeof(int), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to write database.");

	rc = fwrite(&conn->db->MAX_ADDR, sizeof(int), 1, conn->file);
	if (rc != 1)
		die(conn, "Failed to write database.");

	Address_write(conn);

	rc = fflush(conn->file);
	if (rc == -1)
		die(conn, "Cannot flush database.");
}

void Database_set(struct Connection *conn,
		int id, const char *name, const char *email)
{
	int MAX_STRLEN = conn->db->MAX_STRLEN;
	struct Address *addr = &conn->db->adds[id];

	if (addr->set)
		die(conn, "Already set, delete it first");
	
	addr->set = true;
	addr->name = malloc(MAX_STRLEN * sizeof(char));
	char *res = strncpy(addr->name, name, MAX_STRLEN-1);
	addr->name[MAX_STRLEN-1] = '\0';
	if (!res)
		die(conn, "Name copy failed.");

	addr->email = malloc(MAX_STRLEN * sizeof(char));
	res = strncpy(addr->email, email, MAX_STRLEN-1);
	addr->email[MAX_STRLEN-1] = '\0';
	if (!res)
		die(conn, "Email copy failed.");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->adds[id];
	
	if (addr->set) {
		Address_print(addr);
	} else {
		die(conn, "ID is not set.");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = false, .name = NULL, .email = NULL};
	conn->db->adds[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;
	
	for (i = 0; i < db->MAX_ADDR; i++) {
		struct Address *cur = &db->adds[i];

		if (cur->set) {
			Address_print(cur);
			printf("\n");
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		die(NULL, "Usage: ex17 <dbfile> <action> [action params]");

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Connection_open(filename);

	if (action == 'c') {

		conn->file = fopen(filename, "w");
		if (!conn->file)
			die(conn, "Failed to open the file");

	} else {

		conn->file = fopen(filename, "r+");
		if (!conn->file)
			die(conn, "Failed to open the file");
		else
			Database_load(conn);

	}

	switch(action) {
		case 'c':
			if (argc != 5)
				die(conn, "Need maximum string length and maxium number of records.");

			Database_create(conn, atoi(argv[3]), atoi(argv[4]));
			Database_write(conn);
			break;

		case 'g':
			if (argc != 4)
				die(conn, "Need an id for get.");

			Database_get(conn, atoi(argv[3]));
			break;

		case 's':
			if (argc != 6)
				die(conn, "Need id, name and email to set.");
			
			Database_set(conn, atoi(argv[3]), argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if (argc != 4)
				die(conn, "Need id to delete");
			
			Database_delete(conn, atoi(argv[3]));
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;

		default:
			die(conn, "Invalid action: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);

	return 0;
}
