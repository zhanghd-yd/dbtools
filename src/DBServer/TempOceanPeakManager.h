#ifndef TempOceanPeakManager_H
#define TempOceanPeakManager_H
#include "DBGUIAutoGen/env_dataDBGenGui.h"
namespace eHualu
{

class TempOceanPeakManager : public DBAG::env_dataDBGenGui {
	Q_OBJECT
public:
	using inherited = DBAG::env_dataDBGenGui;
	TempOceanPeakManager(BaseDBWidget* parent = nullptr);
	~TempOceanPeakManager();

	void addRowEndCustom(QTableWidget* table, int row, int colume) override;

};
}
#endif