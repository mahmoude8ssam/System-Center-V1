#include "DashboardWidget.h"

DashboardWidget::DashboardWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* wrapperLayout = new QVBoxLayout(this);

    QWidget* contentWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(contentWidget);

    // =============================
    // welcome txt
    // =============================
    QLabel* title = new QLabel("مرحبًا، " + User::instance().getName() + " 👋");
    QFont f; f.setPointSize(20); f.setBold(true);
    title->setFont(f);
    title->setStyleSheet("color: #2c3e50; margin-bottom: 20px;");
    mainLayout->addWidget(title);

    statsCardsWidget = createStatsCards();
    mainLayout->addWidget(statsCardsWidget);
    mainLayout->addWidget(createChart());
    mainLayout->addStretch();

    contentWidget->setLayout(mainLayout);

    // =============================
    // إضافة Scroll Area
    // =============================
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true); // مهم عشان المحتوى يتوسع
    scrollArea->setWidget(contentWidget);

    wrapperLayout->addWidget(scrollArea);
    setLayout(wrapperLayout);

    setStyleSheet(R"(
        QLabel {
            color: #34495e;
        }
        QFrame {
            background-color: #ecf0f1;
            border-radius: 12px;
            padding: 3px;
        }
    )");
}

QWidget* DashboardWidget::createStatsCards()
{
    QWidget* container = new QWidget(this);
    QGridLayout* grid = new QGridLayout(container);
    grid->setSpacing(15);

    // get fake data now
    int studentsCount = Student::getCountAll();
    int groupsCount = Group::getCountAll();
    int lessonsCount = 45;
    int teachersCount = Teacher::getCountAll();
    int gradesCount = Stage::getCountAll();


  // cards
 c1 = new CardWidget("👨‍🎓 عدد الطلبة", studentsCount, this);
 c2 = new CardWidget("👥 عدد المجموعات", groupsCount, this);
 c3 = new CardWidget("📘 عدد الحصص", lessonsCount, this);
 c4 = new CardWidget("👩‍🏫 عدد المدرسين", teachersCount, this);
 c5 = new CardWidget("🏫 عدد المراحل الدراسية", gradesCount, this);

    grid->addWidget(c1, 0, 0);
    grid->addWidget(c2, 0, 1);
    grid->addWidget(c3, 1, 0);
    grid->addWidget(c4, 1, 1);
    grid->addWidget(c5, 2, 1);

    return container;
}
void DashboardWidget::refreshData() {
    c1->updateValue(Student::getCountAll());
    c2->updateValue(Group::getCountAll());
    c3->updateValue(45);
    c4->updateValue(Teacher::getCountAll());
    c5->updateValue(Stage::getCountAll());
    }

QChartView* DashboardWidget::createChart()
{
    // =============================
    // graph QtCharts
    // =============================
    QBarSet *set0 = new QBarSet("عدد الطلبة");
    QBarSet *set1 = new QBarSet("عدد المجموعات");
    QBarSet *set2 = new QBarSet("عدد الحصص");
    QBarSet *set3 = new QBarSet("عدد المدرسين");

    *set0 << 120;
    *set1 << 8;
    *set2 << 45;
    *set3 << 5;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("📊 إحصائيات عامة");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "البيانات الحالية";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 150);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(300);

    return chartView;
}
