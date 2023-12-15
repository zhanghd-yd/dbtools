#include "BaseDBWidget.h"
#include "ui_BaseDBWidget.h"
#include "glog/logging.h"
#include "json/json.h"

#include <QDate>
#include <QCheckBox>

#define CreatetringItem(obj,row,index,str)\
    item = new QTableWidgetItem(str);\
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);\
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);\
    obj->setItem(row, index, item);

using namespace DBAG;

#define Test

BaseDBWidget::BaseDBWidget(QWidget* parent)
	:QWidget(parent), ui(new Ui::Form)
{
	ui->setupUi(this);

	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	connect(ui->searchDataBtn, &QPushButton::clicked, this, &BaseDBWidget::onSearchBtonClicked);

	connect(ui->delDataBtn, &QPushButton::clicked, this, &BaseDBWidget::onDeleteBtonClicked);

	connect(ui->allSelectBtn, &QPushButton::clicked, [this] {
		if (!_add_checkbox) return;
		
		int rowCount = ui->tableWidget->rowCount();
		for (int i = 0; i < rowCount; i++) {
			auto widget = ui->tableWidget->cellWidget(i, 0);
			if (!widget)  continue;

			auto layout = qobject_cast<QHBoxLayout*>(widget->layout());
			auto checkBox = qobject_cast<QCheckBox*>(layout->itemAt(0)->widget());
			checkBox->setChecked(Qt::Checked);
		}
	});

	connect(ui->notAllSelectBtn, &QPushButton::clicked, [this] {
		if (!_add_checkbox) return;

		int rowCount = ui->tableWidget->rowCount();
		for (int i = 0; i < rowCount; i++) {
			auto widget = ui->tableWidget->cellWidget(i, 0);
			if (!widget)  continue;

			auto layout = qobject_cast<QHBoxLayout*>(widget->layout());
			auto checkBox = qobject_cast<QCheckBox*>(layout->itemAt(0)->widget());
			checkBox->setChecked(Qt::Unchecked);
		}
	});
}

BaseDBWidget::~BaseDBWidget()
{
}

std::vector<FieldInfo> BaseDBWidget::getSelectFieldInfo()
{
#ifdef Test
	std::vector<FieldInfo> infos;
	{
		FieldInfo info;
		info._name = "NcFileDataName";
		info._type = FieldType::STRING;
		info._cond = WhereCond::LIKE;
		info._value = std::make_any<std::string>(u8"NcFileDataName");
		infos.emplace_back(info);
	}
	return std::move(infos);
#endif // Test

}

std::vector<int> DBAG::BaseDBWidget::getCheckBoxRowList()
{
	std::vector<int> rowList;
	do {
		if (!_add_checkbox) {
			break;
		}

		int rowCount = ui->tableWidget->rowCount();
		for (int i = 0; i < rowCount; i++) {
			auto widget = ui->tableWidget->cellWidget(i, 0);
			if (!widget)  continue;
			
			auto layout = qobject_cast<QHBoxLayout*>(widget->layout());
			auto checkBox = qobject_cast<QCheckBox*>(layout->itemAt(0)->widget());
			if (checkBox->checkState() == Qt::Checked) {
				rowList.emplace_back(i);
				DLOG(INFO) << "Select Box Row: " << i;
			}
		}
	} while (false);	
	
	return std::move(rowList);
}

void DBAG::BaseDBWidget::loadTableHeader(const std::string& filePath)
{
	do {
		if (!_header_en_name_map.empty()) {
			break;
		}

		if (filePath.empty()) {
			loadDefaultTableHeader();
		} else {
			// read file TODO
		}

		QStringList headText;
		for (const auto& s : _header) {
			headText << QString::fromStdString(s);
		}

		setHeader(headText);

	} while (false);
}

void BaseDBWidget::setHeader(const QStringList& header)
{
	ui->tableWidget->setColumnCount(header.size());
	ui->tableWidget->verticalHeader()->setDefaultSectionSize(30);//表头设置行高
	ui->tableWidget->setHorizontalHeaderLabels(header);
}

void BaseDBWidget::clearTable()
{
	ui->tableWidget->setRowCount(0);
}

void BaseDBWidget::addRowTable(const std::string& json)
{
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(json, root)) {
		LOG(WARNING) << "parse failed: " << json;
		return;
	}

	int currentRow = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(currentRow);
	std::vector<std::string> members = root.getMemberNames();
	int index = 0;

	if (_add_checkbox) {
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();
		auto checkBox = new QCheckBox;

		checkBox->setCheckState(Qt::Unchecked);
		layout->addWidget(checkBox, 0, Qt::AlignCenter);
		layout->setMargin(0);
		widget->setLayout(layout);
		ui->tableWidget->setCellWidget(currentRow, index, widget);

		index += 1;
	}

	QTableWidgetItem* item{ nullptr };
	for (const auto& member : members) {
		DLOG(INFO) << "addRowTable: "  << root[member].asString();
		QString value = QString::fromStdString(root[member].asString());
		CreatetringItem(ui->tableWidget, currentRow, index++, value);
	}

	addRowEndCustom(ui->tableWidget, currentRow, index);
}

void BaseDBWidget::addRowTable(std::vector<std::string>& vec)
{
	if (vec.empty()) return;

	int currentRow = ui->tableWidget->rowCount();
	ui->tableWidget->insertRow(currentRow);
	int index = 0;

	if (_add_checkbox) {
		auto widget = new QWidget();
		auto layout = new QHBoxLayout();
		auto checkBox = new QCheckBox;

		checkBox->setCheckState(Qt::Unchecked);
		layout->addWidget(checkBox, 0, Qt::AlignCenter);
		layout->setMargin(0);
		widget->setLayout(layout);
		ui->tableWidget->setCellWidget(currentRow, index, widget);

		index += 1;
	}

	QTableWidgetItem* item{ nullptr };
	for (const auto& member : vec) {
		DLOG(INFO) << "addRowTable: " << member;
		QString value = QString::fromStdString(member);
		CreatetringItem(ui->tableWidget, currentRow, index++, value);
	}

	addRowEndCustom(ui->tableWidget, currentRow, index);
}

std::pair<int, int> DBAG::BaseDBWidget::getCurrentSelectRowAndColmun()
{
	return { ui->tableWidget->currentRow(), ui->tableWidget->currentColumn()};
}

void DBAG::BaseDBWidget::addRowEndCustom(QTableWidget* table, int row, int colume)
{
}

QTableWidget* DBAG::BaseDBWidget::getTableWidget()
{
	return ui->tableWidget;
}

void DBAG::BaseDBWidget::onDeleteBtonClicked()
{
}

void BaseDBWidget::onSearchBtonClicked() {

}
