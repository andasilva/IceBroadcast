#include "workerstream.h"
#include "streamengine.h"

WorkerStream::WorkerStream(QObject *parent) : QObject(parent)
{

}

void WorkerStream::start()
{
    StreamEngine &streamEngine = StreamEngine::getInstance();
    streamEngine.connexionToServer();

    shout_t* connexion = streamEngine.getConnexion();

    FILE* pFile;
    unsigned char buff[4096];

    pFile = fopen ("/home/angelkiro/Documents/Dev/Qt/IceBroadcast/medias/sound.mp3" , "r");
    if (pFile == NULL) perror ("Error opening file");

    long read, ret;

    while (true) {
        read = fread(buff, 1, sizeof(buff), pFile);
        qDebug() << read;
        if (read > 0) {
            ret = shout_send(connexion, buff, read);
            if (ret != SHOUTERR_SUCCESS) {
                printf("DEBUG: Send error: %s\n", shout_get_error(connexion));
                break;
            }
        } else {
            break;
        }
        shout_sync(connexion);
    }
}
