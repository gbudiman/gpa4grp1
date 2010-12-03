#include <QTcpSocket>
#include <QDialog>
#include <vector>


class GPA4Client : QObject
{

  public:
    GPA4Client(QWidget *parent = 0);

  private slots:
    void connectToHost();
    void solvedPuzzle(vector<string> *);
    void getCommand();
    void writeToServer(string);
    
  
  private:
    QTcpSocket *socket;
    


  signals:
    void setGUIState(string);
    void resetGUIState();
    void solvePuzzle(string);
    void resetSolver();

}
