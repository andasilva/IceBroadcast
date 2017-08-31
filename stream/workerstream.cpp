#include "workerstream.h"

WorkerStream::WorkerStream(QObject *parent) : QObject(parent)
{

}

void WorkerStream::stremAudio()
{
    /*mp3File = new QFile(":/ressources/medias/sound.mp3");

    if(mp3File->open(QFile::ReadOnly)){
       qDebug() << "File opened";
    }else{
        qDebug() << "Error";
    }

    FILE * pFile;
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
    }*/
}
