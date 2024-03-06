#ifndef KILTIDE_H
#define KILTIDE_H

#include <QMainWindow>

class KiltIDE : public QMainWindow {
    Q_OBJECT
public:
    KiltIDE(QWidget *parent = nullptr);
public slots:
    void createNewProject();
    void openProject();
};

#endif // KILTIDE_H
