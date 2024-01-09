#ifndef IomgffManager_H
#define IomgffManager_H

#include "DBGUIAutoGen/iomgffDBGenGui.h"

namespace eHualu
{
	class IomgffManager : public DBAG::iomgffDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::iomgffDBGenGui;

		IomgffManager(BaseDBWidget* parent = nullptr);
		~IomgffManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif // !IomgffManager_H
