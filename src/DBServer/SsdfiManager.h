#ifndef SsdfiManager_H
#define SsdfiManager_H
#include "DBGUIAutoGen/ssdfiDBGenGui.h"
namespace eHualu
{

	class SsdfiManager : public DBAG::ssdfiDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::ssdfiDBGenGui;
		SsdfiManager(BaseDBWidget* parent = nullptr);
		~SsdfiManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif