#ifndef SsdaiManager_H
#define SsdaiManager_H
#include "DBGUIAutoGen/ssdaiDBGenGui.h"
namespace eHualu
{

class SsdaiManager : public DBAG::ssdaiDBGenGui {
	Q_OBJECT
public:
	using inherited = DBAG::ssdaiDBGenGui;
	SsdaiManager(BaseDBWidget* parent = nullptr);
	~SsdaiManager();

	void addRowEndCustom(QTableWidget* table, int row, int colume) override;

};
}
#endif