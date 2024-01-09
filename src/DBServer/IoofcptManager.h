#ifndef IoofcptManager_H
#define IoofcptManager_H

#include "DBGUIAutoGen/ioofcptDBGenGui.h"

namespace eHualu
{

	class IoofcptManager : public DBAG::ioofcptDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::ioofcptDBGenGui;
		IoofcptManager(BaseDBWidget* parent = nullptr);
		~IoofcptManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif