#include <QtGui>
#include <QtNetwork>

#include "ClientSocket.h"
#include "rubik.h"

GPA4Client::GPA4Client(QWdiget *parent) : networkSession(0)
{
socket = new QTcpSocket(this);
state_cube = new rubik();
temp_state = new string(54,"Y");

connect(socket, SIGNAL(readyRead()), this, SLOT(getCommand()) );
connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void GPA4Client::connectToHost()
{

connectButton->setEnabled(false);
socket->abort();
socket->connectToHost(serverLineEdit->text(), portLineEdit->text().toInt());

}

/* This private slot based strong on example found in QT4.7.1 Documentation */
void GPA4Client::displayError(QAbstractSocket::SocketError socketError)
{
  switch(socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    break;
  case QAbstractSocket::HostNotFoundError:
    QMessageBox::information(this.parent, tr("GPA4 Group 1 Client"),
			     tr("The host was not found. Please check the "
				"host name and port settings."));
    break;
  case QAbstractSocket::ConnectionRefusedError:
    QMessageBox::information(this.parent,tr("GPA4 Group 1 Client"),
			     tr("The connection was refused by the peer. "
				"Make sure the peer server is running, and"
				"check that the host name and port settings"
				"are correct."));
    break;
  default:
    QMessageBox:information(this.parent,tr("GPA4 Group 1 Client"),
			    tr("The following error occurred: %1.")
			    .arg(socket->errorString()));
  }
  connectButton->setEnabled(true);
}

void GPA4Client::getCommand()
{
  int n = socket->bytesAvailable();
  char* data = new char[n];
  QString command = new QString(); 
  
  socket->read(data,n);
  command.append(data);  
  delete[] data;

  if(command.contains("ID?")){
    writeToServer("ID=1\n");
    break;
  }else if(command.contains("ACCEPTED.")){
    break;
  }else if(command.contains("READY?")){
    emit resetSolver();
    emit setGUIState(DEFAULT_STATE);
    temp_state = DEFAULT_STATE;
    state_cube.setState(DEFAULT_STATE);
    writeToServer("READY.\N");
    break;
  }else if(command.contains("SOLVE")){
    QStringList *commandArgs;
    commandArgs = commands.split(" ",QString::SkipEmptyParts);
    state_cube.setState(commandArgs.at(1));
    if(commandArgs.length() == 3){
      emit solvePuzzle(commandArgs.at(1),commandArgs.at(2));
    }else{
      emit solvePuzzle(commandArgs.at(1));
    }
    break;
  }else if(command.contains("g1:WIN")){
    emit weWon(true);
    break;
  }else if(command.contains("g1:LOSE")){
    emit weWon(false);
    break;
  }else if(command.contains("TIME:")){
    break;
  }else{
    break;
  }

}

void GPA4Client::puzzleSolved(vector<string> *commands){
  for (vector<int>::iterator iter = v.begin(); iter!=v.end(); ++iter){
    writetoServer("g1:" + *iter+"\n"); //send command to server 
    state_cube.process(*iter);         //perform command on local cube
    temp_state = state_cube.display(); //get current cube state
    emit setGUIState(temp_state);
    sleep(500);
  } 

  writetoServer("g1:DONE\n");

}
 
void GPA4Client::writetoServer(string message){
  socket.write(message);
} 
