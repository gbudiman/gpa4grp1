#ifndef _GPA4Client_H
#define _GPA4Client_H

#include <QtNetwork>
#include <QTcpSocket>
#include <vector>

#include "rubik.h"

#define DEFAULT_STATE "YYYYYYYYYRRRRRRRRRGGGGGGGGGOOOOOOOOOBBBBBBBBBWWWWWWWWW"

class GPA4Client : QObject
{

  public:
    GPA4Client (QWidget *parent = 0);

  private slots:
    void connectToHost();
    void puzzleSolved(vector<string> *commands);
    void getCommand();
    void displayError(QAbstractSocket::SocketError socketError);
    void updateConnectionData(string port, string server);
    
  
  private:
    QTcpSocket *socket;
    rubik *state_cube;   
    string *temp_state;
    string  port_data;
    string  server_data;
 
    //QNetworkSession *networkSession;
    void writeToServer(string message);
     


  signals:
    void setGUIState(string state);
    void solvePuzzle(string state, string allowed = NULL);
    void resetSolver();
    void weWon(bool );
    void getConnectionData();
};

#endif
