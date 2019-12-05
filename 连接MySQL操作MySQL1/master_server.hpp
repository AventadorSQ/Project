#pragma once

#include "httplib.h"
#include "boost/filesystem.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

//总文件存储路径
#define SERVER_MAIN_FILE_PASS "../distributed_file_storage/MainStorageFile"
//总用户文件存储路径
#define SERVER_MAIN_CLIENT_FILE_PASS SERVER_MAIN_FILE_PASS"/ClientsStorageFile"

//服务器所监听的IP地址（监听所有IP）
#define SERVER_LISTEN_IP "0.0.0.0"
//服务器所监听的主机端口号
#define SERVER_LISTEN_PORT "51666"

namespace BF = boost::filesystem;
class MasterServer
{
public:
  MasterServer()
  {
    //创建总文件路径句柄
    BF::path main_file_path(SERVER_MAIN_FILE_PASS);

    //如果总文件句柄不存在，则创建
    if(!BF::exists(main_file_path))
    {
      if(BF::create_directory(main_file_path))
      {
        cout << "总文件存储路径创建成功！33" << endl;
      }
    }

    //如果总用户文件句柄不存在则创建
    BF::path main_client_file_path(SERVER_MAIN_CLIENT_FILE_PASS);

    //如果总用户文件句柄不存在则创建
    if(!BF::exists(main_client_file_path))
    {
      if(BF::create_directory(main_client_file_path))
      {
        cout << "总用户文件存储路径创建成功！45" << endl;
      }
    }
  }


private:
};
