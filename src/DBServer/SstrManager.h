#ifndef SstrManager_H
#define SstrManager_H
#include "DBGUIAutoGen/sstrDBGenGui.h"
namespace eHualu
{

	class SstrManager : public DBAG::sstrDBGenGui {
		Q_OBJECT
	public:
		using inherited = DBAG::sstrDBGenGui;
		SstrManager(BaseDBWidget* parent = nullptr);
		~SstrManager();

		void addRowEndCustom(QTableWidget* table, int row, int colume) override;

	};
}
#endif