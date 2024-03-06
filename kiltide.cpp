#include "kiltide.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>

KiltIDE::KiltIDE(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Kilt IDE");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Welcome to Kilt IDE", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QPushButton *newProjectButton = new QPushButton("Create New Project", this);
    connect(newProjectButton, &QPushButton::clicked, this, &KiltIDE::createNewProject);
    layout->addWidget(newProjectButton);

    QPushButton *openProjectButton = new QPushButton("Open Project", this);
    connect(openProjectButton, &QPushButton::clicked, this, &KiltIDE::openProject);
    layout->addWidget(openProjectButton);
}

void KiltIDE::createNewProject() {
    // Code to create a new project
    qDebug("Creating a new project...");
}

void KiltIDE::openProject() {
    // Code to open an existing project
    qDebug("Opening an existing project...");
}
