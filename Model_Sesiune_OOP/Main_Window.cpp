#include "Main_Window.h"

Main_Window::Main_Window(Service& srv) : service{srv}
{
    this->resize(550, 400);
    QFont font("Courier");
    font.setStyleHint(QFont::Monospace);
    Main_Window::setFont(font);

    layout = new QVBoxLayout(this);
    service.add_observer(this);
    add_button = new QPushButton("Adauga Task");
    cauta_button = new QPushButton("Cauta Programator");

    adauga = new Adaugare(service);
    cauta = new Cautare(service);

    adauga->setWindowTitle("Adaugare");
    cauta->setWindowTitle("Cautare");

    layout->addWidget(add_button);
    layout->addWidget(cauta_button);
    
    this->connect(add_button, SIGNAL(clicked()), adauga, SLOT(show()));
    this->connect(cauta_button, SIGNAL(clicked()), cauta, SLOT(show()));

    table = new QTableView;
    model = new TableModel(table);
    model->setTasks(service.get_all());
    table->setModel(model);

    layout->addWidget(table);

    openWindow = new StareWindow(service, "open");
    inProgressWindow = new StareWindow(service, "inprogress");
    closedWindow = new StareWindow(service, "closed");
    openWindow->show();
    inProgressWindow->show();
    closedWindow->show();



}


void Main_Window::update()
{
    reload();
}
void Main_Window::reload() {

    model->setTasks(service.get_all());
    table->setModel(model);

}


/////////////////////////////////////////////////////////////

Adaugare::Adaugare(Service& service) : srv{ service }
{

    layout = new QFormLayout(this);

    label_id = new QLabel("ID");
    label_desc = new QLabel("Desc");
    label_prog = new QLabel("Programatori");
    label_stare = new QLabel("Stare");

    text_id = new QLineEdit;
    text_desc = new QLineEdit;
    text_prog = new QLineEdit;
    text_stare = new QLineEdit;
    submit_button = new QPushButton("Adauga task");

    layout->addRow(label_id, text_id);
    layout->addRow(label_desc, text_desc);
    layout->addRow(label_prog, text_prog);
    layout->addRow(label_stare, text_stare);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));
}

void Adaugare::submit_button_clicked()
{

    bool convert = true;
    int id = text_id->text().toInt(&convert);
    if (convert == false)
    {
        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Id nu este numar");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
        return;
    }
    
    string desc = text_desc->text().toStdString();
    string prog = text_prog->text().toStdString();
    string stare = text_stare->text().toStdString();

    vector<string> l_prog= splitString(prog, ';');

    try
    {
        srv.addTask(id, desc, l_prog, stare);
        this->close();
    }
    catch (...) {

        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Task-ul exista deja sau datele sunt invalide");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
    }


}

///////////////////////////////////////////////////////////////


Cautare::Cautare(Service& service) : srv{ service }
{
    layout = new QFormLayout(this);
    this->resize(600, 400);
    label_prog = new QLabel("Programator");

    text_prog = new QLineEdit;
    submit_button = new QPushButton("Cauta");


    layout->addRow(label_prog, text_prog);
    layout->addRow(submit_button);

    this->connect(submit_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));

    table_c = new QTableView;
    model_c = new TableModel(table_c);
    table_c->setModel(model_c);
    layout->addWidget(table_c);

    
}

void Cautare::submit_button_clicked()
{
    string prog = text_prog->text().toStdString();
    model_c->setTasks(srv.cauta_prog(prog));
    table_c->setModel(model_c);

    /*
    string prog = text_prog->text().toStdString();
    //vector<Task> tasks = srv.cauta_prog(prog);
    model_c->setTasks(srv.cauta_prog(prog));
    table_c->setModel(model_c);
    table_c->resize(400, 400);
    layout->addWidget(table_c);*/
    /*
    if(tasks.size()==0){

        QMessageBox* mesaj = new QMessageBox;
        mesaj->setText("Nu exista task");
        mesaj->setWindowTitle("Eroare");
        mesaj->show();
    }
    else {

        QMessageBox* mesaj = new QMessageBox;
        mesaj->setWindowTitle("Task-uri");
        
        QString message = QString("%1  %2 %3 %4").arg("Id", -7).arg("Desc", -7).arg("Programatori", -5).arg("Stare", -7);

        for (const auto& task : tasks) {
            QString id_str = QString::number(task.get_id());
            QString desc_str = QString::fromStdString(task.get_desc());
            QString prog_str = "";
            for (auto p : task.get_prog()) {
                prog_str.append(QString::fromStdString(p));
                prog_str.append(" ");
            }
            QString stare_str = QString::fromStdString(task.get_stare());
            QString tasks_string = QString("%1  %2 %3 %4").arg(id_str, -7).arg(desc_str, -7).arg(prog_str, -5).arg(stare_str, -7);
            message.append("\n");
            message.append(tasks_string);

        }
        mesaj->setText(message);
        mesaj->show();
    }*/

}


//////////////////////////////////////////////////////////////////////

vector<string> splitString(const string& input, char delimiter) {
    vector<std::string> result;
    stringstream ss(input);
    string item;

    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

////////////////////////////////////////////////////////

int TableModel::rowCount(const QModelIndex& parent) const {
    return tasks.size();
}

int TableModel::columnCount(const QModelIndex& parent) const {
    return 4;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    Task t = tasks.at(row);
    if (role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case 0:
            return QString::number(t.get_id());
            break;
        case 1:
            return QString::fromStdString(t.get_desc());
            break;
        case 2: {
            QString rez = "";
            for (auto p : t.get_prog())
            {
                rez.append(QString::fromStdString(p));
                rez.append(",");
            }
            return rez;
            break;
        }
        case 3:
            return QString::fromStdString(t.get_stare());
            break;
        }
    }
    return QVariant();
}

void TableModel::setTasks(vector<Task> ts)
{
    tasks = ts;
    std::sort(tasks.begin(), tasks.end(), [](Task& a, Task& b) {
        return a.get_stare() < b.get_stare();
        });
    emit layoutChanged();
}


///////////////////////////////////////////////////////////////////////

StareWindow::StareWindow(Service& _service, string stare) : service(_service), stare(stare)
{
    setWindowTitle(QString::fromStdString(stare));
    service.add_observer(this);
    layout = new QVBoxLayout(this);
    table = new QTableView();
    model = new TableModel(table);
    model->setTasks(service.filterByState(stare));
    table->setModel(model);
    layout->addWidget(table);
    openButton = new QPushButton("open");
    inProgressButton = new QPushButton("inprogress");
    closedButton = new QPushButton("closed");
    layout->addWidget(openButton);
    layout->addWidget(inProgressButton);
    layout->addWidget(closedButton);
    this->connect(openButton, &QPushButton::clicked, [this]() {
        if (!table->selectionModel()->selectedIndexes().isEmpty()) {
            int row = table->selectionModel()->selectedIndexes().at(0).row();
            auto index = table->model()->index(row, 0);
            int id = table->model()->data(index).toInt();
            service.modifyState(id, "open");
        }
        });
    this->connect(inProgressButton, &QPushButton::clicked, [this]() {
        if (!table->selectionModel()->selectedIndexes().isEmpty()) {
            int row = table->selectionModel()->selectedIndexes().at(0).row();
            auto index = table->model()->index(row, 0);
            int id = table->model()->data(index).toInt();
            service.modifyState(id, "inprogress");
        }
        });
    this->connect(closedButton, &QPushButton::clicked, [this]() {
        if (!table->selectionModel()->selectedIndexes().isEmpty()) {
            int row = table->selectionModel()->selectedIndexes().at(0).row();
            auto index = table->model()->index(row, 0);
            int id = table->model()->data(index).toInt();
            service.modifyState(id, "closed");
        }
        });
}

void StareWindow::update()
{
    model->setTasks(service.filterByState(stare));
}

StareWindow::~StareWindow()
{
    //service.remove_observer(this);
}
