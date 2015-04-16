#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main()
{
  MYSQL* conn_ptr;
  int res;
  const char* info = NULL;

  conn_ptr = mysql_init(NULL);
  if (!conn_ptr) {
    fprintf(stderr, "mysql_init failed\n");
    return EXIT_FAILURE;
  }

  conn_ptr = mysql_real_connect(conn_ptr, "localhost", "qinguan", "shaoyou", "foo", 0, NULL, 0);
  if (conn_ptr) printf("Connection success\n");
  else printf("Connection failed\n");

  info = mysql_get_client_info();
  printf("mysql client info: %s\n", info);

  info = mysql_get_host_info(conn_ptr);
  printf("mysql host info: %s\n", info);

  info = mysql_get_server_info(conn_ptr);
  printf("mysql server info: %s\n", info);

  info = mysql_info(conn_ptr);
  printf("mysql info: %s\n", info);

  mysql_close(conn_ptr);

  return EXIT_SUCCESS;
}
