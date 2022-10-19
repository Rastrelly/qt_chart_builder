#include "stdafx.h"
#include "qt_chart_builder.h"

qt_chart_builder::qt_chart_builder(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	onRefresh = false;
	//connect button Add click to btnAddClick()
	connect(ui.btnAdd, &QPushButton::clicked, this, &qt_chart_builder::btnAddClick);
	connect(ui.btnRemove, &QPushButton::clicked, this, &qt_chart_builder::btnRemoveClick);
	connect(ui.btnUpdate, &QPushButton::clicked, this, &qt_chart_builder::btnUpdateClick);
	connect(ui.btnSort, &QPushButton::clicked, this, &qt_chart_builder::btnSortClick);
	connect(ui.btnMoveUp, &QPushButton::clicked, this, &qt_chart_builder::btnMoveUpClick);
	connect(ui.btnMoveDown, &QPushButton::clicked, this, &qt_chart_builder::btnMoveDownClick);
	connect(ui.tableData, &QTableWidget::cellClicked, this, &qt_chart_builder::tableDataClick);
	connect(ui.tableData, &QTableWidget::cellChanged, this, &qt_chart_builder::tableDataChange);
}

qt_chart_builder::~qt_chart_builder()
{}

void qt_chart_builder::btnAddClick()
{
	float px = 0, py = 0;
	px = ui.editX->text().toFloat();
	py = ui.editY->text().toFloat();
	cMgrPtr->addPoint({px,py});
	refreshTable();
}

void qt_chart_builder::btnRemoveClick()
{
	cMgrPtr->removePoint(cMgrPtr->getSelPoint());
	refreshTable();
}

void qt_chart_builder::btnUpdateClick()
{
	float px = 0, py = 0;
	px = ui.editX->text().toFloat();
	py = ui.editY->text().toFloat();
	cMgrPtr->setPoint(cMgrPtr->getSelPoint() , { px,py });
	refreshTable();
}

void qt_chart_builder::btnSortClick()
{
	cMgrPtr->sortByX();
	refreshTable();
}

void qt_chart_builder::btnMoveUpClick()
{
	cMgrPtr->move(-1);
	refreshTable();
}
void qt_chart_builder::btnMoveDownClick()
{
	cMgrPtr->move(1);
	refreshTable();
}

void qt_chart_builder::tableDataClick(int r, int c)
{
	QString dataBuf;
	
	cMgrPtr->SetSelPoint(r);

	dataBuf.setNum(cMgrPtr->getPointX(cMgrPtr->getSelPoint()));
	ui.editX->setText(dataBuf);
	dataBuf.setNum(cMgrPtr->getPointY(cMgrPtr->getSelPoint()));
	ui.editY->setText(dataBuf);
}

void qt_chart_builder::tableDataChange(int r, int c)
{
	if (!onRefresh)
	{
		ui.tableData->blockSignals(true);

		QString iTxtX = ui.tableData->item(r, 0)->text();
		QString iTxtY = ui.tableData->item(r, 1)->text();

		float px = iTxtX.toFloat();
		float py = iTxtY.toFloat();

		cMgrPtr->setPoint(r, { px,py });

		refreshTable();

		ui.tableData->blockSignals(false);
	}
}

void qt_chart_builder::refreshTable()
{
	cMgrPtr->setCallRefresh(true);
	onRefresh = true;
	int cc = 2;
	int rc = cMgrPtr->getChartSize();
	ui.tableData->setColumnCount(cc); //set number of columns
	ui.tableData->setRowCount(rc); //set number of rows

	if (rc <= 0)
	{
		onRefresh = false;
		return;
	}

	for (int i = 0; i < rc; i++)
	{
		tableItems.push_back(
			new QTableWidgetItem(
			  tr("%1").arg(cMgrPtr->getPointX(i))
			)
		);
		tableItems.push_back(
			new QTableWidgetItem(
				tr("%1").arg(cMgrPtr->getPointY(i))
			)
		);

		ui.tableData->setItem(i, 0, tableItems[tableItems.size() - 2]); //X
		ui.tableData->setItem(i, 1, tableItems[tableItems.size() - 1]); //Y
	}
	onRefresh = false;
}
