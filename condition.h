#ifndef CONDITION_H
#define CONDITION_H

#include <QObject>

enum class e_device{  // 设备类型
    LIGHT,
    SCREEN
};

class Condition : public QObject
{
    Q_OBJECT
public:
    explicit Condition(QObject *parent = nullptr);

signals:
};

#endif // CONDITION_H
