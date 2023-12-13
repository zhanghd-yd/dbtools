#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include "mysql/mysql.h"
#include "XStringA.h"
#include <QMutex>

class MysqlConnection
{
	friend class MysqlConnectionPool;

public:
	static MysqlConnection& GetDefautMysqlConnection();
	MysqlConnection();
	~MysqlConnection();
	bool Initialize();
	void Uninitialize();

	//建立到MySql数据库的连接
	bool Connect(ConstStringARef ip, unsigned port, ConstStringARef user, ConstStringARef password, ConstStringARef database);
	bool Connect();
	//测试到MySql数据库的连接状态.
	bool IsConnected();
	bool StartTranSaction();
	bool RollBackTranSaction();
	bool CommitTranSaction();

	bool ExecuteSQL(ConstStringARef strSQL);
	bool ExecuteSQLd(ConstStringARef strSQL);
	MYSQL_RES* QuerySQL(ConstStringARef strSQL);
	void ReleaseResultSet(MYSQL_RES* res_set);
	void GetTables(std::vector<String>& names);
	void GetTables(std::set<String>& names);
	bool CreateTableBy(ConstStringARef dis_table,ConstStringARef src_table, bool bCopyData = false);

	bool ClearTable(ConstStringARef table);
	StringA GetDatabaseName()
	{
		return m_database;
	}

	MYSQL_STMT* InitSTMT();
	bool Prepare(MYSQL_STMT* stmt, ConstStringARef sql);
	bool CloseSTMT(MYSQL_STMT* stmt);
	bool ExecuteSTMT(MYSQL_STMT* stmt,std::vector<MYSQL_BIND>* params = nullptr, std::vector<MYSQL_BIND>* results=nullptr);
	long long  GetAffectedRows(MYSQL_STMT* stmt);
	bool FetchResult(MYSQL_STMT* stmt);
private:

protected:
	MYSQL* m_Connect;
private:
	StringA m_ip;
	StringA m_user;
	StringA m_password;
	StringA m_database;
	unsigned m_port;
	QMutex m_Lock;
	static MysqlConnection s_DefautMysqlConnection;
};


class MysqlConnectionPool
{
public:
	MysqlConnectionPool(int nMaxConnectionCount =10);
	~MysqlConnectionPool();
	MysqlConnection* GetMysqlConnection();
	void ReleaseMysqlConnection(MysqlConnection* pMysqlConnection);
	void Connect(ConstStringARef ip, unsigned port, ConstStringARef user, ConstStringARef password, ConstStringARef database);
	static MysqlConnectionPool& GetDefautMysqlConnectionPool();
	void Stop();
	String GetInfo();
protected:
	std::list<MysqlConnection*> m_IdleList;
	std::list<MysqlConnection*> m_BusyList;

	StringA m_ip;
	StringA m_user;
	StringA m_password;
	StringA m_database;
	unsigned m_port;
	QMutex m_Lock;
	int m_MaxConnectionCount;
	int m_MinConnectionCount;

};


#endif // !MYSQL_CONNECTION_H