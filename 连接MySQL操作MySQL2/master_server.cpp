#pragma once

#include "master_server.hpp"
#include "connect_mysql.hpp"
#include <iostream>
using namespace std;

int main()
{
  //创建存储路径
  MasterServer server_object;
  //尝试连接MySQL
  ConnectMysql CMHandle;
  CMHandle.ConnectZhuCeTable();
  return 0;
}
