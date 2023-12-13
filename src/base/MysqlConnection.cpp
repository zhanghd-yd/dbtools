#include "MysqlConnection.h"

#include "CommonMacro.h"
#include "XStringA.h"
#include <QThread>
#include <QDateTime>
#include <list>

const int MaxTryCount = 5;

MysqlConnection MysqlConnection::s_DefautMysqlConnection;
MysqlConnection::MysqlConnection()
{
	m_port = 0;
	m_Connect = NULL;
}
MysqlConnection::~MysqlConnection()
{
	Uninitialize();
}
MysqlConnection& MysqlConnection::GetDefautMysqlConnection()
{
	return s_DefautMysqlConnection;
}
bool MysqlConnection::Initialize()
{
	if(mysql_library_init(0,NULL,NULL))
	{
		//Logger()->TryError("Init() --> mysql_library_init() Failed");
		return false;
	}

	m_Connect = mysql_init(NULL);
	if(m_Connect == NULL)
	{
		//Logger()->TryError("Init() --> mysql_init() Failed (probably out of memory)");
		return false;
	}

	return true;
}
void MysqlConnection::Uninitialize()
{
	if(m_Connect)
	{
		mysql_close(m_Connect);
		m_Connect = NULL;
		mysql_library_end();
	}
}
bool MysqlConnection::Connect(ConstStringARef ip,unsigned port,ConstStringARef user,ConstStringARef password,ConstStringARef database)
{
	m_ip = ip;
	m_user = user;
	m_password = password;
	m_database = database;
	m_port = port;

	return Connect();
}


bool MysqlConnection::Connect()
{
	if(m_Connect == NULL)
	{
		if(!Initialize())
		{
			return false;
		}
	}

	my_bool reconnect = 1; //0:disable 1:enable
	mysql_options(m_Connect, MYSQL_OPT_RECONNECT, &reconnect);

	my_bool is_truncation = 0;
	mysql_options(m_Connect, MYSQL_REPORT_DATA_TRUNCATION, &is_truncation);

	char charset_name[] = "utf8";
	mysql_options(m_Connect, MYSQL_SET_CHARSET_NAME, charset_name);


	//*mySQL = mysql_real_connect(*mySQL, IP_, User_, Password_, Database_, Port_, nullptr, 0);


	if(mysql_real_connect(m_Connect,m_ip,m_user,m_password,m_database,m_port,NULL,CLIENT_MULTI_STATEMENTS) == NULL)
	{
		//Logger()->TryError("Connect() --> mysql_real_connect() Failed");
		return false;
	}
/*
	if(mysql_query(m_Connect,"SET NAMES GBK")!=0)
	{
		Logger()->TryError("%s",mysql_error(m_Connect));
		return false;
	}

	m_Connect->reconnect = 1;*/

	return true;
}
bool MysqlConnection::IsConnected()
{
	if(m_Connect == NULL)
	{
		return false;
	}

	return mysql_ping(m_Connect) == 0;
}
bool MysqlConnection::StartTranSaction()
{
	if(m_Connect == NULL)
	{
		return false;
	}

	if(mysql_query(m_Connect,"Start Transaction")!=0)
	{
		//Logger()->TryError("%s",mysql_error(m_Connect));
		return false;
	}

	return true;
}

bool MysqlConnection::RollBackTranSaction()
{
	if(m_Connect == NULL)
	{
		return false;
	}

	if(mysql_query(m_Connect,"ROLLBACK")!=0)
	{
		//Logger()->TryError("%s",mysql_error(m_Connect));
		return false;
	}

	return true;
}

bool MysqlConnection::CommitTranSaction()
{
	if(m_Connect == NULL)
	{
		return false;
	}

	if(mysql_query(m_Connect,"Commit")!=0)
	{
		//Logger()->TryError("%s",mysql_error(m_Connect));
		return false;
	}

	return true;
}

bool MysqlConnection::ClearTable(ConstStringARef table)
{
	String strSql;
	strSql.Format("delete from `%s`", table.data());

	return ExecuteSQL(strSql);
}
bool MysqlConnection::CreateTableBy(ConstStringARef dis_table, ConstStringARef src_table, bool bCopyData)
{
	String strSql;
	if (bCopyData)
	{
		strSql.Format("CREATE TABLE IF NOT EXISTS `%s`  AS SELECT * FROM `%s` ", dis_table.data(), src_table.data());
	}
	else
	{
		strSql.Format("CREATE TABLE IF NOT EXISTS `%s`  LIKE `%s`  ", dis_table.data(), src_table.data());

	}
	return ExecuteSQL(strSql);
}
void MysqlConnection::GetTables(std::vector<String>& names)
{
	QMutexLocker lock(&m_Lock);
	names.clear();
	if (m_Connect == NULL)
	{
		return;
	}
	MYSQL_RES *res_set = mysql_list_tables(m_Connect,NULL);
	if (res_set)
	{
		//String name;
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			//name = row[0];
			//names.push_back(name);
			names.push_back(row[0]);
		}
		ReleaseResultSet(res_set);
	}
	else
	{
		//Logger()->TryError("mysql_list_tables() Failed");

	}
}
void MysqlConnection::GetTables(std::set<String>& names)
{


	QMutexLocker lock(&m_Lock);
	names.clear();
	if (m_Connect == NULL)
	{
		return;
	}
	MYSQL_RES *res_set = mysql_list_tables(m_Connect,NULL);
	if (res_set)
	{
		//String name;
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(res_set)) != NULL)
		{
			//name = row[0];
			//names.push_back(name);
			names.insert(String((row[0])).MakeUpper());
		}
		ReleaseResultSet(res_set);
	}
	else
	{
		//Logger()->TryError("mysql_list_tables() Failed");

	}
}

bool MysqlConnection::ExecuteSQL(ConstStringARef strSQL)
{
	QMutexLocker lock(&m_Lock);
	if(m_Connect == NULL)
	{
		return false;
	}
	String sql = String::GBToUTF8(strSQL);
	int nTry(1);
	int nRet = mysql_query(m_Connect, sql);
	while(nRet != 0)
	{
		nTry++;
		if(nRet == 1)
		{
			QThread::msleep(500);
			nRet = mysql_query(m_Connect, sql);
		}

		if(nTry > MaxTryCount)
		{
			break;
		}
	}

	if(nRet != 0)
	{
		//Logger()->TryError("%s : %s",mysql_error(m_Connect),strSQL);
	}

	do 
	{ 
		MYSQL_RES* result = mysql_store_result(m_Connect); 
		mysql_free_result(result); 
	}
	while(!mysql_next_result(m_Connect));

	return nRet == 0;
}

bool MysqlConnection::ExecuteSQLd(ConstStringARef strSQL)
{
	QMutexLocker lock(&m_Lock);
	if (m_Connect == NULL)
	{
		return false;
	}

	int nTry(1);
	String sql = String::GBToUTF8(strSQL);
	int nRet = mysql_query(m_Connect, sql);
	while (nRet != 0)
	{
		nTry++;
		if (nRet == 1)
		{
			QThread::msleep(500);
			nRet = mysql_query(m_Connect, sql);
		}

		if (nTry > MaxTryCount)
		{
			break;
		}
	}

	if (nRet != 0)
	{
		//Logger()->TryError("%s : %s", mysql_error(m_Connect), strSQL);
	}

	do
	{
		MYSQL_RES* result = mysql_store_result(m_Connect);
		mysql_free_result(result);
	} while (!mysql_next_result(m_Connect));

	return nRet == 0;
}
MYSQL_RES* MysqlConnection::QuerySQL(ConstStringARef strSQL)
{
	QMutexLocker lock(&m_Lock);
	if(m_Connect == NULL)
	{
		return NULL;
	}

	String sql = String::GBToUTF8(strSQL);
	int nRet = mysql_query(m_Connect, sql);
	if(nRet!=0)
	{
		//Logger()->TryError("Error Code %d, %s : %s",nRet,mysql_error(m_Connect),strSQL.c_str());
		return NULL;
	}

	MYSQL_RES *res_set = mysql_store_result(m_Connect);
	if(res_set == NULL)
	{
		//Logger()->TryError("mysql_store_result(%s) Failed",strSQL);
	}

	return res_set;
}

void MysqlConnection::ReleaseResultSet(MYSQL_RES* res_set)
{
	if(m_Connect == NULL)
	{
		return;
	}

	if(mysql_errno(m_Connect) != NULL)
	{
		//Logger()->TryError("mysql_fetch_row() Failed");
	}

	mysql_free_result(res_set);
}



MYSQL_STMT* MysqlConnection::InitSTMT()
{
	MYSQL_STMT* stmt = mysql_stmt_init(m_Connect);
	return stmt;
}

bool MysqlConnection::Prepare(MYSQL_STMT* stmt, ConstStringARef sql)
{
	return mysql_stmt_prepare(stmt, sql.c_str(), sql.size()) == 0;
}
bool MysqlConnection::CloseSTMT(MYSQL_STMT* stmt)
{
	if (mysql_stmt_free_result(stmt))
	{
		return mysql_stmt_close(stmt);
	}
	return false;
}

bool MysqlConnection::ExecuteSTMT(MYSQL_STMT* stmt, std::vector<MYSQL_BIND>* params, std::vector<MYSQL_BIND>* results)
{
	int flag = 0;
	std::vector<MYSQL_BIND>& inParams = *params;
	if (params && inParams.size() > 0)
	{
	//绑定输入数据
		flag = mysql_stmt_bind_param(stmt, &inParams[0]);
	}
	if (flag)
	{
		return false;
	}
	std::vector<MYSQL_BIND>& outParams = *results;
	if (results && outParams.size() > 0)
	{
		//绑定输出数据
		flag = mysql_stmt_bind_result(stmt, &outParams[0]);
	}
	if (flag)
	{
		return false;
	}
	//执行sql
	flag = mysql_stmt_execute(stmt);
	if (flag)
	{
		return false;
	}
	//保存临时数据
	flag = mysql_stmt_store_result(stmt);
	if (flag)
	{
		return false;
	}

	return true;

}

long long  MysqlConnection::GetAffectedRows(MYSQL_STMT* stmt)
{
	return mysql_stmt_affected_rows(stmt);
}
bool MysqlConnection::FetchResult(MYSQL_STMT* stmt)
{
	return mysql_stmt_fetch(stmt) == 0;
}
/// //////////////////////MysqlConnectionPool////////////////////////////////////////////////////////////////////////////////
void MysqlConnectionPool::Connect(ConstStringARef ip, unsigned port, ConstStringARef user, ConstStringARef password, ConstStringARef database)
{
	Stop();//关闭原来的库，连接新库时，需要清理以前的东西
	m_ip = ip;
	m_user = user;
	m_password = password;
	m_database = database;
	m_port = port;
}

MysqlConnectionPool::MysqlConnectionPool(int nMaxConnectionCount)
{
	m_MaxConnectionCount = nMaxConnectionCount;
	if (m_MaxConnectionCount < 1)
	{
		m_MaxConnectionCount = 1;
	}
	m_MinConnectionCount = 1;
	For(i, m_MinConnectionCount)
	{
		m_IdleList.push_back(new MysqlConnection());
	}
}
MysqlConnectionPool::~MysqlConnectionPool()
{	
	qint64 nTick = QDateTime::currentMSecsSinceEpoch();

	while (QDateTime::currentMSecsSinceEpoch() - nTick > 200)
	{
		{
			QMutexLocker Lock(&m_Lock);
			m_MaxConnectionCount = 0;
			std::list<MysqlConnection*>::iterator it;
			For_Each(it, m_IdleList)
			{

				delete *it;
			}
			m_IdleList.clear();
			if (m_BusyList.size() == 0)
			{
				break;
			}
		}
		QThread::msleep(1);
	}

	if (m_BusyList.size() > 0)
	{
		//Logger()->TryError("退出时有%d个没有释放的数据连接", m_BusyList.size());
	}
}

void MysqlConnectionPool::Stop()
{
	QMutexLocker Lock(&m_Lock);

	std::list<MysqlConnection*>::iterator it;
	For_Each(it, m_IdleList)
	{
		(*it)->Uninitialize();
		delete *it;
	}
	if (m_BusyList.size() > 0)
	{
		//Logger()->TryError("数据库连接池退出时有%d个没有释放的数据连接", m_BusyList.size());
		
	}
	For_Each(it, m_BusyList)
	{
		(*it)->Uninitialize();
		delete *it;
	}
	m_IdleList.clear();
	m_BusyList.clear();
}

MysqlConnection* MysqlConnectionPool::GetMysqlConnection()
{
	MysqlConnection* pMysqlConnection = NULL;
	if (m_MaxConnectionCount == 0)
	{
		return NULL;
	}
	{//Lock作用域
		QMutexLocker Lock(&m_Lock);
		if (m_IdleList.size() > 0)
		{
			pMysqlConnection = m_IdleList.front();
			m_IdleList.pop_front();
			m_BusyList.push_back(pMysqlConnection);
		}
		else
		{
			if (m_BusyList.size() < m_MaxConnectionCount)
			{
				pMysqlConnection = new MysqlConnection();
				m_BusyList.push_back(pMysqlConnection);
			}
			else
			{//已经达到最大值,等待其他资源释放
				//CSpinInverseLock InverseLock(m_Lock);
				m_Lock.unlock();
				for (int i = 0; i < 1; i++)
				{
					QThread::msleep(10);
					QMutexLocker Lock(&m_Lock);
					if (m_IdleList.size() + m_BusyList.size() == 0)
					{//这里说明程序退出了
						//break;
						return NULL;
					}
					if (m_IdleList.size() > 0)
					{
						pMysqlConnection = m_IdleList.front();
						m_IdleList.pop_front();
						m_BusyList.push_back(pMysqlConnection);
						break;
					}
				}

				m_Lock.lock();
			}
		}

		//Lock作用域
	}
	if (pMysqlConnection)
	{
		if (!pMysqlConnection->IsConnected())
		{
			bool flag = pMysqlConnection->Connect(m_ip, m_port, m_user, m_password, m_database);
			if (!flag)
			{
				ReleaseMysqlConnection(pMysqlConnection);

				//Logger()->Info("连接数据库[%s:%d,%s]失败,失败原因:%s", m_ip.data(), m_port, m_database.data(), mysql_error(pMysqlConnection->m_Connect));
				pMysqlConnection = NULL;
				return NULL;
			}
		}
	}
	if (!pMysqlConnection)
	{
		//Logger()->Info("没有获取到有效的数据连接,当前数据库最大连接数[%d]", m_MaxConnectionCount);
		m_MaxConnectionCount++;

		//Logger()->TryError("增加数据库最大连接数[%d]", m_MaxConnectionCount);
		return GetMysqlConnection();
		ASSERT(false);
	}
	return pMysqlConnection;
}
void MysqlConnectionPool::ReleaseMysqlConnection(MysqlConnection* pMysqlConnection)
{
	QMutexLocker Lock(&m_Lock);

	//m_BusyList.remove(pMysqlConnection);
	std::list<MysqlConnection*>::iterator it;
	For_Each(it, m_BusyList)
	{
		if (*it == pMysqlConnection)
		{
			m_BusyList.erase(it);
			m_IdleList.push_back(pMysqlConnection);
			return;
		}
	}

	//Logger()->TryError("错误:没有找到要释放的数据连接!!!!!!!!!!!!!!!");
}

MysqlConnectionPool& MysqlConnectionPool::GetDefautMysqlConnectionPool()
{
	static MysqlConnectionPool s_DefautMysqlConnection(6);
	return s_DefautMysqlConnection;
}



String MysqlConnectionPool::GetInfo()
{
	QMutexLocker Lock(&m_Lock);
	String str;
	str.Format("数据库连接池信息,Max=%d,IdleSize=%d,BusySize=%d", m_MaxConnectionCount,m_IdleList.size(), m_BusyList.size());
	return str;
}



