#include <fstream>
//#include <filesystem> //zhd: warning：expected either a definition or a tag name
#include "BaseDBWidget.h"
#include "BaseQueryWidget.h"
#include "ui/ui_BaseDBWidget.h"
#include "glog/logging.h"
#include "json/json.h"
#include "rttr_serialization/from_json.h"
#include "rttr_serialization/to_json.h"

#include <QDate>
#include <QCheckBox>
#include <QDir>

#define CreatetringItem(obj,row,index,str)\
    item = new QTableWidgetItem(str);\
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);\
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);\
    obj->setItem(row, index, item);

using namespace DBAG;

#define Test

BaseDBWidget::BaseDBWidget(QWidget* parent)
	:QWidget(parent), ui(new Ui::BaseDBWidget)
{
	ui->setupUi(this);
	this->setWindowTitle("通用数据管理器");

	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setAlternatingRowColors(true);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	connect(ui->searchDataBtn, &QPushButton::clicked, this, &BaseDBWidget::onBaseSearchBtonClicked);

	connect(ui->delDataBtn, &QPushButton::clicked, this, &BaseDBWidget::onBaseDeleteBtonClicked);

	connect(ui->allSelectBtn, &QPushButton::clicked, [this] {
		if (!_add_checkbox) return;

		int rowCount = ui->tableWidget->rowCount();
		for (int i = 0; i < rowCount; i++) {
			auto widget = ui->tableWidget->cellWidget(i, 0);
			if (!widget)  continue;

			auto layout = qobject_cast<QHBoxLayout*>(widget->layout());
			auto checkBox = qobject_cast<QCheckBox*>(layout->itemAt(0)->widget());
			checkBox->setChecked(true);
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
			checkBox->setChecked(false);
		}
	});

	//TODO
	ui->nextPageBtn->hide();
	ui->prePageBtn->hide();
}

BaseDBWidget::~BaseDBWidget()
{
}

bool DBAG::BaseDBWidget::checkFieldSelectedInput()
{
	return true;
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
	if (!_header_en_name_map.empty()) {
		return;
	}

	do {
		if (filePath.empty()) {
			break;
		} 

		/*auto path = std::filesystem::path(filePath) / std::filesystem::path(_tableName + ".json");*/ //zhd 
		QDir dir(QString::fromStdString(filePath));
		auto path = dir.path() + "/" + QString::fromStdString(_tableName) + ".json";
		parseTableConfig(path);
	} while (false);

	
	if (_header.empty()) {
		LOG(WARNING) << "_header is empty(),use default header!!	";
		loadDefaultTableHeader();
	}
	QStringList headText;
	for (const auto& s : _header) {
		headText << QString::fromStdString(s);
	}
	setHeader(headText);
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
		DLOG(INFO) << "addRowTable: " << root[member].asString();
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
	return { ui->tableWidget->currentRow(), ui->tableWidget->currentColumn() };
}

void DBAG::BaseDBWidget::addRowEndCustom(QTableWidget* table, int row, int colume)
{
}

QTableWidget* DBAG::BaseDBWidget::getTableWidget()
{
	return ui->tableWidget;
}

void DBAG::BaseDBWidget::parseTableConfig(const QString& filePath)
{
	DLOG(INFO) << "table config path: " << filePath.toStdString();

	if(!QFile::exists(filePath)) { //if (!std::filesystem::exists(filePath)) {
		return;
	}

	std::string p = filePath.toStdString();
	std::ifstream file(p);
	if (!file.is_open()) {
		return;
	}

	_tableConfigFilePath = std::move(p);
	std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	_tableConfig = std::make_shared<TableConfig>();
	io::from_json(json, *(_tableConfig.get()));

	_header.emplace_back(std::string("选择"));
	for (const auto& field : _tableConfig->_fields) {
		_header_en_name_map.insert({ field._comment,field._field });
		_header.emplace_back(field._comment);
	}
	_header.emplace_back(std::string("操作"));
}

const TableKey& DBAG::BaseDBWidget::getTableKey()
{
	if (_tableConfig) {
		return _tableConfig->_key;
	}
	return TableKey();
}

void DBAG::BaseDBWidget::onBaseSearchBtonClicked()
{
	BaseQueryWidget baseQueryWidget;
	baseQueryWidget.setTableConfig(_tableConfig);
	int is_search_clicked = baseQueryWidget.exec();

	if (is_search_clicked) {
		_fieldSelectedInfo = std::move(baseQueryWidget.getSelectFieldInfo());
		DLOG(INFO) << "continu onSearchBtonClicked in derived class...";

		if (checkFieldSelectedInput()) {
			onSearchBtonClicked();

			//save select json
			std::string json = io::to_json(*(_tableConfig.get()));
			std::ofstream file(_tableConfigFilePath);
			if (!json.empty() && file.is_open()) {
				file << json;
				file.close();
				LOG(INFO) << "table config save to " << _tableConfigFilePath;
			}
		}
	}
}

void DBAG::BaseDBWidget::onBaseDeleteBtonClicked()
{
	onDeleteBtonClicked();
}

void BaseDBWidget::onSearchBtonClicked() {
	
}

void DBAG::BaseDBWidget::onDeleteBtonClicked()
{
}