#ifndef EnvData_MANAGER_H
#define EnvData_MANAGER_H

#include "DBGUIAutoGen/env_dataDBGenGui.h"

class EnvDataManager : public DBAG::env_dataDBGenGui {
	Q_OBJECT
public:

	EnvDataManager(BaseDBWidget* parent = nullptr);
	~EnvDataManager();

	void addRowEndCustom(QTableWidget* table, int row, int colume) override;

};

#endif // !env_data_MANAGER_H
