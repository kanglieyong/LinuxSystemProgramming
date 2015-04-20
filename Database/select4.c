#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

MYSQL my_connection;
MYSQL_RES* res_ptr;
MYSQL_ROW sqlrow;

void display_header();
void display_row();

int main(int argc, char* argv[])
{
  int res;
  int first_row = 1;

  mysql_init(&my_connection);
  if (mysql_real_connect(&my_connection, "localhost", "qinguan", "shaoyou", "foo", 0, NULL, 0)) {
    printf("Conection success!\n");

    res = mysql_query(&my_connection, "SELECT childno, fname, age FROM children WHERE age > 5");
    if (res) {
      fprintf(stderr, "SELECT error: %s\n", mysql_error(&my_connection));
    } else {
      res_ptr = mysql_use_result(&my_connection);
      if (res_ptr) {
	//
      }
      mysql_free_result(res_ptr);
    }

    mysql_close(&my_connection);
  } else {
    fprintf(stderr, "Connection failed\n");
    if (mysql_errno(&my_connection)) fprintf(stderr, "Connection error %d: %s\n", mysql_errno(&my_connection), mysql_error(&my_connection));
  }
  
  return EXIT_SUCCESS;
}
