#ifndef MOVEWORK_H
#define MOVEWORK_H

#include <QObject>

class MoveWork : public QObject
{
    Q_OBJECT
public:
    explicit MoveWork(QObject *parent = nullptr);

signals:

public slots:
    void doWork(void);
};

#endif // MOVEWORK_H
