#pragma once

#include "httplib.h"
#include "boost/filesystem.hpp"
#include "boost/algorithm/string.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

//总文件存储路径
#define SERVER_MAIN_FILE_PASS "../distributed_file_storage/MainStorageFile"
//总用户文件存储路径
#define SERVER_MAIN_CLIENT_FILE_PASS SERVER_MAIN_FILE_PASS"/ClientsStorageFile"
//用户正常文件存储路径
#define CLIENT_NORMALFILE_PATH SERVER_MAIN_CLIENT_FILE_PASS"/NormalFile"
//用户压缩文件存储路径
#define CLIENT_COMPRESSFILE_PATH SERVER_MAIN_CLIENT_FILE_PASS"/CompressFile"

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

    //创建总用户文件句柄
    BF::path main_client_file_path(SERVER_MAIN_CLIENT_FILE_PASS);
    //如果总用户文件句柄不存在则创建
    if(!BF::exists(main_client_file_path))
    {
      if(BF::create_directory(main_client_file_path))
      {
        cout << "总用户文件存储路径创建成功！45" << endl;
      }
    }

    //创建用户正常文件备份目录句柄
    BF::path client_normal_file_path(CLIENT_NORMALFILE_PATH);
    //如果用户正常文件备份目录不存在则创建
    if(!BF::exists(client_normal_file_path))
    {
      if(BF::create_directory(client_normal_file_path))
      {
        cout << "服务端正常备份文件目录创建成功" << endl;
      }
    }

    //创建服务端压缩文件目录句柄
    BF::path client_compress_file_path(CLIENT_COMPRESSFILE_PATH);
    //如果用户压缩文件目录不存在则创建
    if(!BF::exists(client_compress_file_path))
    {
      if(BF::create_directory(client_compress_file_path))
      {
        cout << "服务端压缩备份文件目录创建成功" << endl;
      }
    }
  }

  //获取文件路径
  //获取正常文件备份路径
  static string GetNormalFileNamePath()
  {
    string NormalFilePath;
    //创建正常文件路径句柄
    BF::directory_iterator normal_file_path(CLIENT_NORMALFILE_PATH);
    NormalFilePath = normal_file_path->path().string();
    return NormalFilePath;
  }
  //获取压缩文件备份路径
  static string GetCompressFileNamePath()
  {
    string CompressFilePath;
    //创建压缩文件路径句柄
    BF::directory_iterator compress_file_path(CLIENT_COMPRESSFILE_PATH);
    CompressFilePath = compress_file_path->path().string();
    return CompressFilePath;
  }
private:
};
