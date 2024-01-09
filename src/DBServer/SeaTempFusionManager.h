#ifndef SeaTempFusionManager_H
#define SeaTempFusionManager_H
#include "DBGUIAutoGen/env_dataDBGenGui.h"
namespace eHualu
{

	class SeaTempFusionManager : public DBAG::env_dataDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::env_dataDBGenGui;
		SeaTempFusionManager(BaseDBWidget* parent = nullptr);
		~SeaTempFusionManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif