#ifndef WORKERSTREAM_H
#define WORKERSTREAM_H

#include <QObject>

class WorkerStream : public QObject
{
    Q_OBJECT
public:
    explicit WorkerStream(QObject *parent = nullptr);

signals:

public slots:
    void stremAudio();
};

#endif // WORKERSTREAM_H
