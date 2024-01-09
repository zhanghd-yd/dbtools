#include "SsdfiManager.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>

using namespace DBAG;
using namespace eHualu;
#define CURRENT_CLASS SsdfiManager

CURRENT_CLASS::CURRENT_CLASS(BaseDBWidget* parent)
	: inherited(parent)
{

}

CURRENT_CLASS::~CURRENT_CLASS()
{
}


void CURRENT_CLASS::addRowEndCustom(QTableWidget* table, int row, int colume) {
	auto widget = new QWidget();
	auto layout = new QHBoxLayout();
	layout->setMargin(0);
	widget->setLayout(layout);
	table->setCellWidget(row, colume, widget);
	//添加可视化按钮
	{
		auto pushButton = new QPushButton;
		pushButton->setText(QString::fromUtf8("可视化"));
		layout->addWidget(pushButton, 0);

		//在按钮中保存行和列
		pushButton->setProperty("row", row);
		pushButton->setProperty("col", colume);

		connect(pushButton, &QPushButton::clicked, [this, pushButton]() {
			//取出行列数据
			int row = pushButton->property("row").toInt();
			int col = pushButton->property("col").toInt();

			//根据行，获取结构体数据
			DLOG(INFO) << " row: " << row << " col: " << col;

			//打印结构体数据
			auto obj = this->getSelectRowObj(row);
			if (obj.has_value()) {
				auto& data = obj.value();
				DLOG(INFO) << "current Data : ";
				DLOG(INFO) << io::to_json(data);
			}
		});
	}

	//添加删除按钮
	{
		auto pushButton = new QPushButton;
		pushButton->setText(QString::fromUtf8("删除"));
		layout->addWidget(pushButton, 0);

		//在按钮中保存行和列
		pushButton->setProperty("row", row);
		pushButton->setProperty("col", colume);

		connect(pushButton, &QPushButton::clicked, [this, pushButton]() {
			//取出行列数据
			int row = pushButton->property("row").toInt();
			_helper.deleteRowData(row);
		});
	}
}