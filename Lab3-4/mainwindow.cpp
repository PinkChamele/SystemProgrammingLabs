#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <QtSql>
using namespace std;


//MainWindow::MainWindow(QWidget *parent)
// : QMainWindow(parent)




MainWindow::MainWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);
    createActions();
    readSettings();

    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    setCurrentFile(QString());
}


void MainWindow::getFileHistory(){

    int maxRecords = 10;
    list<string> records = {};

    QString result; // = QString::fromUtf8(history);
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("FileHistoryDatabase.sqlite");
    if (!sdb.open())
    {
         result.append(sdb.lastError().text());
         return;
    }

    QString qstr;
    QSqlQuery query;
    string line;
    qstr = "SELECT * FROM HISTORY_TABLE;";
    if(query.exec(qstr))
    {
        while (query.next()) {
            QString fileName = query.value(1).toString() ;
            QString dateOpened = query.value(2).toString();
            line = "File "+fileName.toStdString()+" was opened "+dateOpened.toStdString();
            records.push_front(line);
            cout << line << endl;
            line="";
        }
        //displaying records from the end of the file
        list<string>::iterator ls = records.begin();
        for(int i = 0; i < maxRecords && ls->length() > i; i++){
            line += *ls + "\n";
            ++ls;
        }

    }
    else
    {
        result.append("Select error: " + query.lastError().text());
        result.push_back('\n');
    }

    result = QString::fromUtf8(line);
    QMessageBox::about(this, tr("Resently opened"), result);
    sdb.close();


}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::openPart(){
    open(1);
}

const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void MainWindow::appendHistory(QString fileName)
{

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("FileHistoryDatabase.sqlite");

    if (!sdb.open())
    {
         cout << sdb.lastError().text().toStdString() << endl;
         return;
    }

    QSqlQuery query;
    QString qstr = "CREATE TABLE IF NOT EXISTS HISTORY_TABLE ("
    "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
    "FILENAME VARCHAR(255), "
    "DATEOPENED VARCHAR(16) "
    ");";

    if(query.exec(qstr))
    {
        string file = strippedName(fileName).toStdString() ;
        string dateOpened = currentDateTime() ;

        string toExec = "INSERT INTO HISTORY_TABLE (FILENAME, DATEOPENED) VALUES ('" + file + "', '" + dateOpened +"');";
        qstr = QString::fromUtf8(toExec);
        if(query.exec(qstr))
        {
            cout << "New row inserted!" << endl;
        }
        else
        {
            cout << "Insert error: " + query.lastError().text().toStdString() << endl ;
        }
    }
    sdb.close();

}


void MainWindow::open(int i)
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
        {
            appendHistory(fileName);
            textEdit->clear();
            loadFile(fileName, i);
        }
    }
}

void MainWindow::cut(){
    textEdit->cut();
}

void MainWindow::copy(){
    textEdit->copy();
}

void MainWindow::paste(){
    textEdit->paste();
}

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec() != QDialog::Accepted)
        return false;
    return saveFile(dialog.selectedFiles().first());
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("Notepad killer is presented here."));
}

void MainWindow::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void MainWindow::createActions(){

    //File
    QMenu *fileMenu = menuBar()->addMenu("&File");

    const QIcon newIcon = QIcon("..\\lab4SP\\images\\new.png");
    QAction *newAct = new QAction(newIcon, "&New", this);
    newAct->setStatusTip("Create a new file");
    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newAct);

    const QIcon openIcon = QIcon("..\\lab4SP\\images\\open.png");
    QAction *openAct = new QAction(openIcon, "&Open...", this);
    openAct->setStatusTip("Open an existing file");
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    const QIcon openPartIcon = QIcon("..\\lab4SP\\images\\openPart.png");
    QAction *openPartAct = new QAction(openPartIcon, "&Open half...", this);
    openPartAct->setStatusTip("Open half of an existing file");
    connect(openPartAct, &QAction::triggered, this, &MainWindow::openPart);
    fileMenu->addAction(openPartAct);

    const QIcon saveIcon = QIcon("..\\lab4SP\\images\\save.png");
    QAction *saveAct = new QAction(saveIcon, "&Save", this);
    saveAct->setStatusTip("Save file");
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);

    const QIcon saveAsIcon = QIcon("..\\lab4SP\\images\\saveAs.png");
    QAction *saveAsAct = new QAction(saveAsIcon, "&SaveAs", this);
    saveAsAct->setStatusTip("Save file as...");
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);
    fileMenu->addAction(saveAsAct);

    const QIcon exitIcon = QIcon("..\\lab4SP\\images\\exit.png");
    QAction *exitAct = new QAction(exitIcon, "&Exit", this);
    exitAct->setStatusTip("Exit");
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);
    fileMenu->addAction(exitAct);
    //



    //Edit
    QMenu *editMenu = menuBar()->addMenu("&Edit");

    const QIcon cutIcon = QIcon("..\\lab4SP\\images\\cut.png");
    QAction *cutAct = new QAction(cutIcon, "&Cut", this);
    cutAct->setStatusTip("Cut text");
    connect(cutAct, &QAction::triggered, this, &MainWindow::cut); //fix this
    editMenu->addAction(cutAct);

    const QIcon copyIcon = QIcon("..\\lab4SP\\images\\copy.png");
    QAction *copyAct = new QAction(copyIcon, "&Copy", this);
    copyAct->setStatusTip("Copy text");
    connect(copyAct, &QAction::triggered, this, &MainWindow::copy); //fix this
    editMenu->addAction(copyAct);

    const QIcon pasteIcon = QIcon("..\\lab4SP\\images\\paste.png");
    QAction *pasteAct = new QAction(pasteIcon, "&Paste", this);
    pasteAct->setStatusTip("Paste text");
    connect(pasteAct, &QAction::triggered, this, &MainWindow::paste); //fix this
    editMenu->addAction(pasteAct);
    //



    //Help
    QMenu *helpMenu = menuBar()->addMenu("&Help");

    const QIcon aboutIcon = QIcon("..\\lab4SP\\images\\about.png");
    QAction *aboutAct = new QAction(aboutIcon, "About", this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    aboutAct->setStatusTip("Show the Qt library's About box");
    helpMenu->addAction(aboutAct);
    //


    //History
    QAction *historyAct = menuBar()->addAction("History");
    connect(historyAct, &QAction::triggered, this, &MainWindow::getFileHistory);
    //

#ifndef QT_NO_CLIPBOARD
    cutAct->setEnabled(false);
    copyAct->setEnabled(false);
    connect(textEdit, &QPlainTextEdit::copyAvailable, cutAct, &QAction::setEnabled);
    connect(textEdit, &QPlainTextEdit::copyAvailable, copyAct, &QAction::setEnabled);
#endif // !QT_NO_CLIPBOARD
}


void MainWindow::readSettings()
{
     const QRect availableGeometry = screen()->availableGeometry();
     resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
     move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
     setWindowIcon(QIcon("..\\lab4SP\\images\\reader.png"));
}


bool MainWindow::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}


void MainWindow::loadFile(const QString &fileName, int lines)
{
    string flName = fileName.toUtf8().constData();
    fstream in(flName);
    string line;
    QString text;
    if(lines == 0){
        while (getline(in, line))
        {
            text = QString::fromStdString(line);
            textEdit->appendPlainText(text);
        }
    } else{
        int length = getFileLength(flName) / 2;
        for(int i = 1; i<length; i++) //!in.eof();
        {
            getline(in, line);
            text = QString::fromStdString(line);
            textEdit->appendPlainText(text);
        }
        in.close();
    }

    setCurrentFile(fileName);
}

int MainWindow::getFileLength(string fileName){
    int length = 0;
    ifstream in(fileName);
    string line;
    if (in.is_open())
    {
        while (getline(in, line))
        {
            length++;
        }
        in.close();
    }
    return length;
}

bool MainWindow::saveFile(const QString &fileName)
{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}













