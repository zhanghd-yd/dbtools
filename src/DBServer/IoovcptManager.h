#ifndef IoovcptManager_H
#define IoovcptManager_H

#include "DBGUIAutoGen/ioovcptDBGenGui.h"

namespace eHualu
{

	class IoovcptManager : public DBAG::ioovcptDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::ioovcptDBGenGui;
		IoovcptManager(BaseDBWidget* parent = nullptr);
		~IoovcptManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif