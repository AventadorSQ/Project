#pragma once

#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

class ConnectMysql
{
  public:
    ConnectMysql()
    {
      //初始化句柄
      mysql_init(&MysqlHandle);
    }

    //连接数据库中注册表
    bool ConnectZhuCeTable(std::string EmailName = "EmailName", std::string Passwd = "Passwd", std::string BackFileName = "BackFileName", std::string BackFileSize = "BackFileSize",
        std::string CompressFileName = "CompressFileName", std::string CompressFileSize = "CompressFileSize")
    {
      if(mysql_real_connect(&MysqlHandle, "localhost", "root", "5210", "struct_data_storage_system", 0, NULL, 0))
      {
        JinDuTiao();
        std::cout << "连接数据库<<struct_data_storage_system>>成功!!!" << std::endl;

        //需要查看请求连接哪个表》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》
        //此处需处理请求哪个表操作
        string RequestTable;
        RequestTable = "RegisteredTable";
        vetor<string> vTableName("RegisteredTable", "ClientFileTable", "NormalFileTable", "CompressFileTable");
        int TableNameNum = 0;
        for (int i = 0; i < 4; i++)
        {
          if(RequestTable == vTableName[i])
          {
            TableNameNum = i + 1;
            break;
          }
        }
        //选择指定表指定数据操作
        SelectTableCaoZuo(TableNameNum, EmailName, Passwd, BackFileName, BackFileSize, CompressFileName, CompressFileSize);
        return true;
      }
      std::cout << "连接数据库中注册表失败!!!" << std::endl;
      return false;
    }

  private:
    //*******************************选择操作表**************************//
    void SelectTableCaoZuo(int TableNameNum, std::string EmailName = "EmailName", std::string Passwd = "Passwd", std::string BackFileName = "BackFileName",
        std::string BackFileSize = "BackFileSize", std::string CompressFileName = "CompressFileName", std::string CompressFileSize = "CompressFileSize")
    {
      if(TableNameNum == 1)
      {
        //注册表操作
        break;
      }
      else if(i == 2)
      {
        //用户正常备份表操作
        break;
      }
      else if(i == 3)
      {
        //服务器备份正常文件表操作
        break;
      }
      else
      {
        //服务器备份压缩文件表操作
        break;
      }
    }
    //********************每个表操作************************************//
    //用户正常备份表操作
    bool SelectClientTableDataCaoZuo(std::string& EmailName,std:: string& Passwd, std::string& BackFileName, std::string& BackFileSize, std::string& CompressFileName, std::string& CompressFileSize)
    {
      int ClientRegisteredId = 0;
      //通过查找注册表中的用户名来找到用户注册号
      while(!IsSuccessFindIdRegisteredTable(EmailName, ClientRegisteredId))
      {
        //如果在已注册用户中查找注册ID不成功将1s后再次查找
        usleep(1000000000);
      }

      //需要看请求时进行什么操作》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》
      //这里只是测试
      
      int select = 0;
      std::cout << "输入[1],选择插入数据;输入[2],选择删除数据;" << std::endl;
      std::cout << "输入[3],选择查找数据;输入[4],选择修改数据;" << std::endl;
      std::cout << "请选择的数据操作:";
      cin >> select;
      if(select == 1)
      {
        while(!IsSuccessInsertClientFileInfoTable(ClientRegisteredId, BackFileName, BackFileSize))
        {
          //如果插入不成功将1s后再次插入
          usleep(1000000000);
        }
        mysql_close(&MysqlHandle);
      }
      else if(select == 2)
      {
        //删除数据
      }
    }

    //*********************增删查改子操作*********************************//
    //向注册表中插入注册用户信息
    bool IsSuccessInsertRegisteredTable(const std::string& EmailName, const std::string& Passwd)
    {
      state = mysql_query(&MysqlHandle, "insert into RegisteredTable(email_name, passwd) value(EmailName, Passwd)");
      if(state)
      {
        std::cout << "向注册表插入元素失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "向注册表插入元素成功" << std::endl;
        return true;
      }
    }

    //从用户表中查找已注册用户对应的注册序号
    bool IsSuccessFindIdRegisteredTable(const std::string& EmailName, int& RegisteredId)
    {
      state  = mysql_query(&MysqlHandle, "select register_id from RegisteredTable where email_name = EmailName");
      if(state)
      {
        std::cout << "从注册表中查询该用户注册序号失败" << std::endl;
        return false;
      }
      else
      {
        RegisteredId = state;
        std::cout << "从注册表中查询该用户注册序号成功" << std::endl;
        return true;
      }
    }

    //向用户正常备份表插入备份文件信息
    bool IsSuccessInsertClientFileInfoTable(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
    {
      state = mysql_query(&MysqlHandle, "insert into ClientFileTable(Clientregister_id, backfile_name, backfile_size) value(ClientRegisterId, BackupFileName,BackupFileSize)");
      if(state)
      {
        std::cout << "向用户备份表插入用户备份文件信息失败<P84>" << std::endl;
        return false;
      }
      else
      {
        std::cout << "向用户备份表插入用户备份文件信息成功<P89>" << std::endl;
        return true;
      }
    }

    //从用户正常备份表中删除用户要求删除的备份文件信息（用户删备份文件）
    bool IsSuccessDeleteClientFileInfoTable(const int ClientRegisterId, const std::string& BackupFileName)
    {
      state = mysql_query(&MysqlHandle, "delete from ClientFileTable where Clientregister_id = ClientRegisterId and backfile_name = BackupFileName");
      if(state)
      {
        std::cout << "从用户备份表删除用户指定备份文件信息失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从用户备份表删除用户指定备份文件信息成功" << std::endl;
        return true;
      }
    }

    //从用户正常备份表查找指定用户的所有备份文件信息
    bool IsSuccessFindAllClientFileInfoTable(const int ClientRegisterId)
    {
      state = mysql_query(&MysqlHandle, "select * from ClientFileTable where Clientregister_id = ClientRegisterId");
      if(state)
      {
        std::cout << "从用户备份表查找用户所有备份文件失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从用户备份表查找用户所有备份文件成功" << std::endl;
        return true;
      }
    }

    //从用户正常备份表中查找用户指定文件信息（用户查找文件）
    bool IsSuccessFindClientFileInfoTable(const int ClientRegisterId, const std::string& BackupFileName)
    {
      state = mysql_query(&MysqlHandle, "select * from ClientFileTable  where Clientregister_id = ClientRegisterId and backfile_name = BackupFileName");
      if(state)
      {
        std::cout << "从用户备份表没有找到用户指定文件" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从用户备份表找到了用户指定文件" << std::endl;
        return true;
      }
    }

    //从用户正常备份表中修改用户指定备份文件大小（用户上传修改后备份文件大小）
    bool IsSuccessUpdadeFileSizeTable(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
    {
      state = mysql_query(&MysqlHandle, "update ClientFileTable set backfile_size = BackupFileSize where Clientregister_id = ClientRegisterId and backfile_name = BackupFileName");
      if(state)
      {
        std::cout << "从用户备份表中更新备份文件大小失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从用户备份表中更新备份文件大小成功" << std::endl;
        return true;
      }
    }

    //
    //进度条程序
    void JinDuTiao()
    {
      int i = 0;
      char buff[102];
      memset(buff, 0, sizeof(buff));
      const char* ptr = "|/-\\";
      while(i <= 100)
      {
        printf("[%-100s][%d%%][%c]\r", buff, i, ptr[i%4]);
        fflush(stdout);
        buff[i++] = '#';
        usleep(50000);
      }
      std::cout << std::endl;
    }
  private:
    MYSQL MysqlHandle;
    int state;
};
