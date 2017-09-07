#include "workerstream.h"
#include "streamengine.h"

WorkerStream::WorkerStream(QObject *parent) : QObject(parent)
{
    aborted = false;
}

void WorkerStream::setAborted(bool value)
{
    aborted = value;
}

void WorkerStream::start()
{
    qDebug() << "Stream started";
    StreamEngine &streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();

    shout_t* connexion = streamEngine.getConnexion();


    unsigned char buff[4096];

    pFile = fopen (streamEngine.getCurrentlyPlaying()->toStdString().c_str() , "r");
    if (pFile == NULL) perror ("Error opening file");

    long read, ret;

    while (!aborted) {
        read = fread(buff, 1, sizeof(buff), pFile);
        qDebug() << read;
        if (read > 0) {
            ret = shout_send(connexion, buff, read);
            if (ret != SHOUTERR_SUCCESS) {
                printf("DEBUG: Send error: %s\n", shout_get_error(connexion));
                break;
            }
        }
        shout_sync(connexion);
    }
    qDebug() << "End of the song...";
    streamEngine.setIsRunning(false);
    streamEngine.getThread()->exit();
    shout_close(connexion);
}

void WorkerStream::playAnotherSong(QString music)
{
    pFile = fopen (music.toStdString().c_str() , "r");
}
