#include "EnvDataManager.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "DBDataAutoGen/env_dataStruct.h"

using namespace DBAG;

EnvDataManager::EnvDataManager(BaseDBWidget* parent)
	: DBAG::env_dataDBGenGui(parent)
{
	connect(getTableWidget(), &QTableWidget::itemClicked, [](QTableWidgetItem* item) {
		DLOG(INFO) << "itemClicked: " << item->text().toStdString();
	});
}

EnvDataManager::~EnvDataManager()
{
}


void EnvDataManager::addRowEndCustom(QTableWidget* table, int row, int colume) {
	auto widget = new QWidget();
	auto layout = new QHBoxLayout();

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

	//添加测试按钮
	{
		auto pushButton = new QPushButton;
		pushButton->setText(QString::fromUtf8("输出测试按钮"));
		layout->addWidget(pushButton, 0);

		//在按钮中保存行和列
		pushButton->setProperty("row", row);
		pushButton->setProperty("col", colume);

		connect(pushButton, &QPushButton::clicked, [this, pushButton]() {
			//取出行列数据
			int row = pushButton->property("row").toInt();
			int col = pushButton->property("col").toInt();

			//获取指定行列的文本 1
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 0);
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 1);
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 2);
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 3);
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 4);
			DLOG(INFO) << " ......... getSelectRowColumeText............" << this->getSelectRowColumeText(0, 5);

			//获取指定行列的文本 2
			//DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 0)->text().toStdString();//checkbox error !!
			DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 1)->text().toStdString();
			DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 2)->text().toStdString();
			DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 3)->text().toStdString();
			DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 4)->text().toStdString();
			DLOG(INFO) << " ......... item text............" << getTableWidget()->item(0, 5)->text().toStdString();
		});
	}

	layout->setMargin(0);
	widget->setLayout(layout);
	table->setCellWidget(row, colume, widget);
}