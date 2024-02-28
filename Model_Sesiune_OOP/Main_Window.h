#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Main_Window.h"
#include "service.h"
#include <QtWidgets/QMainWindow>
#include "Main_Window.h"
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qmessagebox>
#include <QTextEdit>
#include <QtWidgets/QListWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QRandomGenerator>
#include <qlayout.h>
#include <sstream>
#include <qtableview.h>
#include <QAbstractItemModel>
#include <qabstractitemmodel.h>
#include <algorithm>

vector<string> splitString(const string& input, char delimiter);

class TableModel : public QAbstractTableModel {
    Q_OBJECT
private:
    vector<Task> tasks;
public:
    TableModel(QWidget* parent) : QAbstractTableModel(parent) {};
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    void setTasks(vector<Task> ts);
};
//////////////////////////////////////////////////


class StareWindow : public QWidget, public Observer
{
    Q_OBJECT
private:
    string stare;
    Service& service;
    QVBoxLayout* layout;
    QTableView* table;
    TableModel* model;
    QPushButton* openButton;
    QPushButton* inProgressButton;
    QPushButton* closedButton;


public:
    StareWindow(Service& _service, string stare);
    void update() override;
    ~StareWindow();
};




/////////////////////////////////////////////////

class Adaugare : public QWidget
{
    Q_OBJECT
public:
    Adaugare(Service& service);

private:
    Service& srv;
    QFormLayout* layout;
    QLabel* label_id;
    QLabel* label_desc;
    QLabel* label_prog;
    QLabel* label_stare;
    QLineEdit* text_id;
    QLineEdit* text_desc;
    QLineEdit* text_prog;
    QLineEdit* text_stare;
    QPushButton* submit_button;

signals:

private slots:
    void submit_button_clicked();
};

class Cautare : public QWidget
{
    Q_OBJECT
public:
    Cautare(Service& service);

private:
    Service& srv;
    QFormLayout* layout;
    QLabel* label_prog;
    QLineEdit* text_prog;
    QPushButton* submit_button;

    QTableView* table_c;
    TableModel* model_c;

signals:

private slots:
    void submit_button_clicked();
};




///////////////////////////////////////////////////////////////



class Main_Window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Main_Window(Service& srv);
    void update() override;

private:
    QVBoxLayout* layout;
    Service& service;
    QPushButton* add_button;
    QPushButton* cauta_button;

    Adaugare* adauga;
    Cautare* cauta;

    QTableView* table;
    TableModel* model;

    StareWindow* openWindow;
    StareWindow* inProgressWindow;
    StareWindow* closedWindow;

private slots:
    void reload();
};
