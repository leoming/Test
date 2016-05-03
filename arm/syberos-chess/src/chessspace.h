#ifndef SPACE_H
#define SPACE_H
#include <cworkspace.h>
#include <QQuickView>

class Space : public SYBEROS::CWorkspace
{
    Q_OBJECT
public:
    Space(QObject *parent = NULL);
    ~Space();

    virtual void onLaunchComplete(Option option, const QStringList& params);
};

#endif // SPACE_H
