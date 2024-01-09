#ifndef SstfManager_H
#define SstfManager_H
#include "DBGUIAutoGen/sstfDBGenGui.h"
namespace eHualu
{

	class SstfManager : public DBAG::sstfDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::sstfDBGenGui;
		SstfManager(BaseDBWidget* parent = nullptr);
		~SstfManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif