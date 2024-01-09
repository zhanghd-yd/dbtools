#ifndef IoovcpssdaManager_H
#define IoovcpssdaManager_H

#include "DBGUIAutoGen/ioovcpssdaDBGenGui.h"

namespace eHualu
{

	class IoovcpssdaManager : public DBAG::ioovcpssdaDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::ioovcpssdaDBGenGui;
		IoovcpssdaManager(BaseDBWidget* parent = nullptr);
		~IoovcpssdaManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif