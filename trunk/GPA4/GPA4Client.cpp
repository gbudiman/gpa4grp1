#include <Qt/QtGui>
#include <string>
#include <QString>
#include <QList>
#include <QStringList>

#include "GPA4Client.h"
#include "rubik.h"

GPA4Client::GPA4Client(QWidget *parent) //: QtNetworkSession(0)
{
socket = new QTcpSocket(this);

connect(socket, SIGNAL(readyRead()), this, SLOT(getCommand()) );
connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void GPA4Client::updateConnectionData(string port, string server){
    port_data = port;
  server_data = server;
  }

void GPA4Client::connectToHost()
{

  socket->abort();
  emit getConnectionData();
  sleep(200);
  QString temp = QString::fromStdString(server_data);
  string s = port_data;
  socket->connectToHost(temp, atoi(s.c_str()));

}

/* This private slot based strong on example found in QT4.7.1 Documentation */
void GPA4Client::displayError(QAbstractSocket::SocketError socketError)
{
  switch(socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    break;
  case QAbstractSocket::HostNotFoundError:
    emit errorConnecting(1);
    break;
  case QAbstractSocket::ConnectionRefusedError:
    emit errorConnecting(2);
    break;
  default:
    break;
  }
}

void GPA4Client::getCommand()
{
  int n = socket->bytesAvailable();
  char* data = new char[n];
  
  socket->read(data,n);
  QString command(data);
  delete[] data;

  if(command.contains("ID?")){
    writeToServer("ID=1\n");
  }else if(command.contains("ACCEPTED.")){
  }else if(command.contains("READY?")){
    emit resetSolver();
    emit setGUIState(DEFAULT_STATE);
    temp_state = DEFAULT_STATE;
    state_cube.setState(DEFAULT_STATE);
    writeToServer("READY.\n");
  }else if(command.contains("SOLVE")){
    QStringList commandArgs(command.split(" ",QString::SkipEmptyParts));
    state_cube.setState(commandArgs.at(1).toStdString());
    if(commandArgs.size() == 3){
      emit solvePuzzle(commandArgs.at(1).toStdString(),commandArgs.at(2).toStdString());
    }else{
      emit solvePuzzle(commandArgs.at(1).toStdString());
    }
  }else if(command.contains("g1:WIN")){
    emit weWon(true);
  }else if(command.contains("g1:LOSE")){
    emit weWon(false);
  }else if(command.contains("TIME:")){
  }else{
  }

}

void GPA4Client::puzzleSolved(vector<string> commands){
  for (vector<string>::iterator iter = commands.begin(); iter != commands.end(); ++iter){
    writeToServer("g1:" + *iter+"\n"); //send command to server 
    state_cube.process(*iter);         //perform command on local cube
    temp_state = state_cube.display(); //get current cube state
    emit setGUIState(temp_state);
    sleep(500);
  } 

  writeToServer("g1:DONE\n");

}
 
void GPA4Client::writeToServer(string message){
  //const char *temp;
  int temp_len = message.length();
  char temp[temp_len];  
  for( int i = 0; i < temp_len; i++) {
    temp[i] = message[i]; 
  } 
  socket->write(temp,temp_len);
} 
