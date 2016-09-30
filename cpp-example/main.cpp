#include<iostream>
#include<string>
#include<vector>
extern "C" {
  #include "sqlite3.h"
}
using namespace std;

int main() {
  sqlite3* db;
  sqlite3_open(":memory:", &db);

  const char * query = "create table if not exists user ("
            "   _id integer primary key autoincrement not null,"
            "   age int,"
            "   name text,"
            "   weight real"
            ");";
  sqlite3_exec(db, query , 0, 0, nullptr);

  sqlite3_stmt *stmt;
  sqlite3_prepare( db, "insert into user (age,name,weight) values (?,?,?);", -1, &stmt, 0);

  const char* names[] = {"joey", "chandler", "monica", "ross", "phoebe", "rachel"};
  int ages[] = {21, 22, 23, 24, 25, 26 };
  double weights[] = { 80.0, 65.0, 50.0, 75.0, 45.0, 50.0 };

  for(int inx = 0; inx < 6; ++inx) {
    if(sqlite3_bind_int(stmt, 1, ages[inx]) != SQLITE_OK)
      return 1;
    sqlite3_bind_text (stmt, 2, names[inx], -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 3, weights[inx]);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
  }
  sqlite3_finalize(stmt);

  sqlite3_prepare( db, "select * from user", -1, &stmt, 0);
  while(sqlite3_step(stmt) == SQLITE_ROW) {
    int age = sqlite3_column_int(stmt, 1);
    sqlite3_column_bytes(stmt, 2);
    string name = string(reinterpret_cast<char const *>(sqlite3_column_text(stmt, 2)));
    double weight = sqlite3_column_double(stmt, 3);
    cout << age << ", " << name << ", " << weight << endl;
  }
  sqlite3_finalize(stmt);

  sqlite3_close(db);
  cout << "\n-------------------------";
  return 0;
}
