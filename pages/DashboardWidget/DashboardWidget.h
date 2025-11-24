//DashboardWidget
#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGridLayout>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "../../components/CardWidget/CardWidget.h"
#include "../../models/User/User.h"
#include "../../models/Student/Student.h"
#include "../../models/Group/Group.h"
#include "../../models/Teacher/Teacher.h"
#include "../../models/Stage/Stage.h"



class DashboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit DashboardWidget(QWidget *parent = nullptr);
    void refreshData();

private:
    QVBoxLayout* mainLayout;
    QWidget* createStatsCards();  // crt cards
    QChartView* createChart();    // crt graph
    QWidget* statsCardsWidget;  // store card


    
    CardWidget* c1;
    CardWidget* c2;
    CardWidget* c3;
    CardWidget* c4;
    CardWidget* c5;
};
