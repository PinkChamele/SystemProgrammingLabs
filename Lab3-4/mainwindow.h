#include <QtWidgets>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void loadFile(const QString &fileName, int lines);
    //void loadByParts(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void newFile();
    void open(int i);
    void openPart();
    bool save();
    bool saveAs();
    void cut();
    void copy();
    void paste();
    void about();
    void getFileHistory();
    void documentWasModified();

private:
    int getFileLength(string fileName);
    void appendHistory(QString fileName);
    void createActions();
    void readSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QPlainTextEdit *textEdit;
    QString curFile;
};
