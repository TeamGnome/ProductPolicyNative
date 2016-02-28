#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "ppobject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PPObject* pObj = new PPObject();
    QStandardItemModel* model = new QStandardItemModel;
    foreach(PPRecord pRec, pObj->Records)
    {
        QList<QStandardItem*>* fields = new QList<QStandardItem*>;
        fields->append(new QStandardItem(QString::fromWCharArray(pRec.Name, pRec.Record.NameSize / sizeof(wchar_t))));
        fields->last()->setEditable(false);
        fields->append(new QStandardItem(QString::fromStdString(pRec.GetDataTypeString())));
        fields->last()->setEditable(false);

        model->appendRow(*fields);
    }

    QStringList* headerLabels = new QStringList();
    headerLabels->append("Name");
    headerLabels->append("Type");
    model->setHorizontalHeaderLabels(*headerLabels);

    model->sort(0);

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
