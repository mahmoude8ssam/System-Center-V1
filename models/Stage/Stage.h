#pragma once
#include <QString>
#include <QList>

struct StageData {
    int id;
    QString name;
};

class Stage {
public:
    static QList<StageData> getAllStages();
    static int getCountAll();
    static StageData getStageById(int id);
    static bool addStage(const StageData& g);
    static bool updateStage(const StageData& g);
    static bool deleteStage(int id);
};
