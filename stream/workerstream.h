#ifndef WORKERSTREAM_H
#define WORKERSTREAM_H

#include <QObject>
#include <QtWidgets>
#include "shout/shout.h"

class WorkerStream : public QObject
{
    Q_OBJECT
public:
    explicit WorkerStream(QObject *parent = nullptr);
    void setAborted(bool value);

private:
    bool aborted;
    FILE* pFile;
    signals:

        public slots:
        void start();
    void playAnotherSong(QString music);
};

#endif // WORKERSTREAM_H
