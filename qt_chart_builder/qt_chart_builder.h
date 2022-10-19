#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qt_chart_builder.h"
#include "chartManager.h"
#include <vector>


class qt_chart_builder : public QMainWindow
{
    Q_OBJECT

public:
    qt_chart_builder(QWidget *parent = nullptr);
    ~qt_chart_builder();
	chartManager * cMgrPtr;
	void refreshTable();

	std::vector<QTableWidgetItem*> tableItems;

	bool onRefresh;

public slots:
	void btnAddClick();
	void btnRemoveClick();
	void btnUpdateClick();
	void btnSortClick();
	void btnMoveUpClick();
	void btnMoveDownClick();
	void tableDataClick(int r, int c);
	void tableDataChange(int r, int c);

private:
    Ui::qt_chart_builderClass ui;
};
