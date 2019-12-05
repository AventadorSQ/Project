#pragma once

#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include "master_server.hpp"

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
        //这里只是测试
        std::string RequestTable;
        RequestTable = "RegisteredTable";
        std::vector<std::string> vTableName;
        //("RegisteredTable", "ClientFileTable", "NormalFileTable", "CompressFileTable");
        vTableName.push_back("RegisteredTable");
        vTableName.push_back("ClientFileTable");
        vTableName.push_back("NormalFileTable");
        vTableName.push_back("CompressFileTable");
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
      std::cout << "连接数据库<<struct_data_storage_system>>失败!!!" << std::endl;
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
        SelectRegisterTableDataCaoZuo(EmailName, Passwd);
      }
      else if(TableNameNum == 2)
      {
        //用户正常备份表操作
        SelectClientTableDataCaoZuo(EmailName, BackFileName, BackFileSize);
      }
      else if(TableNameNum == 3)
      {
        //服务器备份正常文件表操作
      }
      else
      {
        //服务器备份压缩文件表操作
      }
    }
    //********************************************************每个表操作***********************************************************//
    //1.0注册表操作
    bool SelectRegisterTableDataCaoZuo(std::string& EmailName, std::string& Passwd)
    {
      //这里只是测试
      int select = 0;
      std::cout << "输入[1],选择查看该用户是否注册;输入[2],选择验证用户密码是否正确;" << std::endl;
      std::cout << "输入[3],选择插入用户注册信息;  输入[4],选择修改用户密码;" << std::endl;
      std::cout << "请输入你的选择:";
      cin >> select;
      if(select == 1)
      {
        //查看用户是否注册
        RegisterFindClientInfoTable1(EmailName);
      }
      else if(select == 2)
      {
        //验证用户登录信息
        RegisterYanZhengClientNamePasswdTable1(EmailName, Passwd);
      }
      else if(select == 3)
      {
        //向注册表中插入注册信息
        RegisterInsertRegisterClientInfoTable1(EmailName, Passwd);
      }
      else
      {
        //修改用户密码
        RegisterUpdateClientPasswdTable1(EmailName, Passwd);
      }
    }
    //2.0用户正常备份表操作
    bool SelectClientTableDataCaoZuo(std::string& EmailName, std::string& BackFileName, std::string& BackFileSize)
    {
      int ClientRegisteredId = 0;
      //通过查找注册表中的用户名来找到用户注册号
      while(!RegisterFindRegisterIdTable1(EmailName, ClientRegisteredId))
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
        //用户备份表中插入备份文件信息
        ClientInsertBackupFileInfoTable2(ClientRegisteredId, BackFileName, BackFileSize);

        //此处不能关闭数据库，关闭数据库应该在程序末尾
        //mysql_close(&MysqlHandle);
      }
      else if(select == 2)
      {
        //用户备份表删除备份信息
        ClientDeleteBackupFileInfoTable2(ClientRegisteredId, BackFileName);
      }
      else if(select == 3)
      {
        //查该文件是否备份
        ClientFindClientFileInfoTable2(ClientRegisteredId, BackFileName);
      }
      else
      {
        //用户对该文件进行修改
        ClientUpdadeFileSizeTable2(ClientRegisteredId, BackFileName, BackFileSize);
      }
    }

    //3.0server正常表操作
    bool SelectSNormalTableDataCaoZuo(const std::string& EmailName, const std::string& BackFileName, const std::string& BackFileSize)
    {
      //获取用户注册序号
      int ZhuCeId = 0;
      RegisterFindRegisterIdTable1(EmailName,ZhuCeId);

      //需要看请求时进行什么操作》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》
      //这里只是测试
      int select = 0;
      std::cout << "输入[1],选择插入数据;输入[2],选择删除数据;" << std::endl;
      std::cout << "输入[3],选择修改数据;" << std::endl;
      std::cout << "请选择的数据操作:";
      cin >> select;
      if(select == 1)
      {
        //向server正常表中添加数据
        SNormalInsertBackupFileInfoTable3(ZhuCeId, BackFileName, BackFileSize);
      }
      else if(select == 2)
      {
        //删除server正常表中的指定数据
        SNormalDeleteBackupFileInfoTable3(ZhuCeId, BackFileName);
        //删除备份的文件
        std::string NormalFile;
        NormalFile = MasterServer::GetNormalFileNamePath();
        NormalFile += BackFileName;
        unlink(NormalFile.c_str());
      }
      else
      {
        //更新用户上传的正常文件大小
        SNormalUpdateBackupFileSizeTable3(ZhuCeId, BackFileName, BackFileSize);
      }
    }

    //4.0server压缩表操作
    bool SelectSCompressTableDataCaoZuo(const std::string& EmailName, const std::string& BackFileName, const std::string& CompressFileName, const std::string& CompressFileSize)
    {
      //获取用户注册序号
      int ZhuCeId = 0;
      RegisterFindRegisterIdTable1(EmailName,ZhuCeId);

      //需要看请求时进行什么操作》》》》》》》》》》》》》》》》》》》》》》》》》》》》》》
      //这里只是测试
      int select = 0;
      std::cout << "输入[1],选择插入数据;输入[2],选择删除数据;" << std::endl;
      std::cout << "输入[3],查找源文件名;输入[4],选择修改数据;" << std::endl;
      std::cout << "请选择的数据操作:";
      cin >> select;
      if(select == 1)
      {
        //向server压缩表插入数据
        ServerCompressInsertFileInfoTable4(ZhuCeId, BackFileName,  CompressFileName, CompressFileSize);
      }
      else if(select == 2)
      {
        //从server压缩表中删除压缩文件信息
        ServerCompressDeleteFileInfoTable4(ZhuCeId, BackFileName);
        //此处删除压缩备份文件
        std::string CompressFile;
        CompressFile = MasterServer::GetCompressFileNamePath();
        CompressFile += BackFileName;
        CompressFile += ".gz";
        unlink(CompressFile.c_str());
      }
      else if(select == 3)
      {
        //从server压缩表查找源文件名
        ServerCompressFindNormalFileNameTable4(ZhuCeId, CompressFileName, BackFileName);
      }
      else
      {
        //更新压缩文件大小
        ServerCompressUpdateFileSizeTable4(ZhuCeId, BackFileName, CompressFileSize);
      }

    }

    //***************************************************************增删查改子操作*********************************************************************************//
    //1.1向注册表中插入注册用户信息
    bool RegisterInsertRegisterClientInfoTable1(const std::string& EmailName, const std::string& Passwd)
    {
      state = mysql_query(&MysqlHandle, "insert into RegisteredTable(email_name, passwd) values(EmailName, Passwd)");
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

    //1.2从注册表中查找该用户是否已经注册
    bool RegisterFindClientInfoTable1(const std::string& EmailName)
    {
      state = mysql_query(&MysqlHandle, "select register_id from RegisteredTable where email_name = EmailName");
      if(state)
      {
        std::cout << "所查用户邮箱没有注册" << std::endl;
        return false;
      }
      else
      {
        std::cout << "所查用户邮箱已经注册" << std::endl;
        return true;
      }
    }

    //1.3从注册表中验证注册用户是否用户名与密码都无误
    bool RegisterYanZhengClientNamePasswdTable1(const std::string& EmailName, const std::string& Passwd)
    {
      state = mysql_query(&MysqlHandle, "select register_id from RegisteredTable where email_name = EmailName and passwd = Passwd");
      if(state)
      {
        std::cout << "用户名或者密码错误" << std::endl;
        return false;
      }
      else
      {
        std::cout << "用户名和密码正确" << std::endl;
        return true;
      }
    }

    //1.4从注册表中修改注册用户密码
    bool RegisterUpdateClientPasswdTable1(const std::string& EmailName, const std::string& Passwd)
    {
      state = mysql_query(&MysqlHandle, "update RegisteredTable set passwd = Passwd where email_name = EmailName");
      if(state)
      {
        std::cout << "更改用户密码失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "更改用户密码成功" << std::endl;
        return true;
      }
    }

    //1.5从注册表中查找已注册用户对应的注册序号
    bool RegisterFindRegisterIdTable1(const std::string& EmailName, int& RegisteredId)
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

    //2.1向用户正常备份表插入备份文件信息
    bool ClientInsertBackupFileInfoTable2(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
    {
      state = mysql_query(&MysqlHandle, "insert into ClientFileTable(Clientregister_id, backfile_name, backfile_size) values(ClientRegisterId, BackupFileName,BackupFileSize)");
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

    //2.2从用户正常备份表中删除用户要求删除的备份文件信息（用户删备份文件）
    bool ClientDeleteBackupFileInfoTable2(const int ClientRegisterId, const std::string& BackupFileName)
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

    //2.3从用户正常备份表查找指定用户的所有备份文件信息
    bool ClientFindAllBackupFileInfoTable2(const int ClientRegisterId)
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

    //2.4从用户正常备份表中查找用户指定文件信息（用户查找文件）
    bool ClientFindClientFileInfoTable2(const int ClientRegisterId, const std::string& BackupFileName)
    {
      state = mysql_query(&MysqlHandle, "select normal_id from ClientFileTable  where Clientregister_id = ClientRegisterId and backfile_name = BackupFileName");
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

    //2.5从用户正常备份表中修改用户指定备份文件大小（用户上传修改后备份文件大小）
    bool ClientUpdadeFileSizeTable2(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
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

    //3.1向服务器正常备份表中插入用户备份文件信息
    bool SNormalInsertBackupFileInfoTable3(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
    {
      state = mysql_query(&MysqlHandle, "insert into NormalFileTable(serverregister_id, backfile_name, backfile_size) values(ClientRegisterId, BackupFileName, BackupFileSize)");
      if(state)
      {
        std::cout << "向server正常表中插入数据失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "向server正常表中插入数据成功" << std::endl;
        return true;
      }
    }

    //3.2从服务器正常备份表中删除用户指定备份文件
    bool SNormalDeleteBackupFileInfoTable3(const int ClientRegisterId, const std::string& BackupFileName)
    {
      state = mysql_query(&MysqlHandle, "delete from NormalFileTable where serverregister_id = ClientRegisterId and backfile_name = BackupFileName");
      if(state)
      {
        std::cout << "从server正常表中删除指定文件数据失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从server正常表中删除指定文件数据成功" << std::endl;
        return true;
      }
    }

    //3.3向服务器正常备份表中修改备份文件大小（用户上传修改后备份文件大小）
    bool SNormalUpdateBackupFileSizeTable3(const int ClientRegisterId, const std::string& BackupFileName, const std::string& BackupFileSize)
    {
      state = mysql_query(&MysqlHandle, "update NormalFileTable set backfile_size = BackupFileSize where serverregister_id = ClientRegisterId and backfile_name = BackFileName");
      if(state)
      {
        std::cout << "从server正常表中修改指定文件大小失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从server正常表中修改指定文件大小成功" << std::endl;
        return true;
      }
    }

    //4.1向服务器压缩表中插入用户压缩文件信息
    bool ServerCompressInsertFileInfoTable4(const int ClientRegisterId, const std::string& BackupFileName, const std::string& CompressFileName, const std::string& CompressFileSize)
    {
      state = mysql_query(&MysqlHandle, "insert into CompressFileTable(compressregister_id, backfile_name, compfile_name, compfile_size) values(ClientRegisterId, BackupFileName, CompressFileName, CompressFileSize)");
      if(state)
      {
        std::cout << "向server压缩文件表中插入压缩文件信息失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "向server压缩文件表中插入压缩文件信息成功" << std::endl;
        return true;
      }
    }

    //4.2从服务器压缩表中删除压缩文件信息(用户下载时可能删除，用户删除文件时可能删除)
    bool ServerCompressDeleteFileInfoTable4(const int ClientRegisterId, const std::string& BackFileName)
    {
      state = mysql_query(&MysqlHandle, "delete from CompressFileTable where compressregister_id = ClientRegisterId and backfile_name = BackFileName");
      if(state)
      {
        std::cout << "从server压缩文件表中删除压缩文件信息失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从server压缩文件表中删除压缩文件信息成功" << std::endl;
        return true;
      }
    }

    //4.3从服务器压缩表中通过用户压缩文件名称找到源文件名***********************************************
    void ServerCompressFindNormalFileNameTable4(const int ClientRegisterId, const std::string& CompressFileName, const std::string& NormalFileName)
    {
      state = mysql_query(&MysqlHandle, "select backfile_name from CompressFileTable where compressregister_id = ClientRegisterId and compfile_name = CompressFileName");
    }

    //4.4从服务器压缩表中修改压缩文件大小
    bool ServerCompressUpdateFileSizeTable4(const int ClientRegisterId, const std::string& BackFileName, const std::string& CompressFileSize)
    {
      state = mysql_query(&MysqlHandle, "update CompressFileTable set compfile_size = CompressFileSize where compressregister_id = ClientRegisterId and backfile_name = BackFileName");
      if(state)
      {
        std::cout << "从server压缩表中修改压缩文件大小失败" << std::endl;
        return false;
      }
      else
      {
        std::cout << "从server压缩表中修改压缩文件大小成功" << std::endl;
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
