#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QObject>


class GraphicsScene;

class FileService : public QObject
{
    Q_OBJECT
public:
    static FileService *sharedFileService();
    bool vaildFile(QString filepath);
    int saveInfo(GraphicsScene *scene,QWidget *parent);
    void saveInfoWithoutQues(GraphicsScene *scene);
    void saveAsInfo(GraphicsScene *scene);

    QString getOpenedFile();
protected:
    FileService(QObject *parent = 0);

private:
    static FileService *s_SharedFileService;
};

#endif // FILESERVICE_H
