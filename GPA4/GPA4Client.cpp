#include <Qt/QtGui>
#include <string>
#include <QString>
#include <QList>
#include <QStringList>

#include <iostream>

#include "GPA4Client.h"
#include "rubik.h"

GPA4Client::GPA4Client(QWidget *parent) //: QtNetworkSession(0)
{
  socket = new QTcpSocket(this);
  blockSize = 0;
  connect(socket, SIGNAL(readyRead()), this, SLOT(getCommand()) );
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));

}

void GPA4Client::updateConnectionData(string port, string server){
  port_data = port;
  server_data = server;
  
  cout << "updateConnectionData"<<endl;
  cout << "port_data: "<< port_data << " server_data: " << server_data<<endl;
  cout << "------------------------------" << endl;
  return;

  }

void GPA4Client::connectToHost()
{
  cout << "trying to connect" <<endl;
  socket->abort();
  emit getConnectionData();
  QString temp = QString::fromStdString(server_data);
  string s = port_data;

  cout<<"In connectToHost:";
  cout<<s<<" "<<server_data<<endl;
  cout<<"--------------"<<endl;

  socket->connectToHost(temp, atoi(s.c_str()));
  
  cout << "Connected to server" << endl;
  cout << "-------------------" << endl;
  
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
  char *data = new char[n+1];
  socket->read(data,n);
  data[n] = '\0';
  string c(data, n);
  QString command = QString::fromStdString(c);
  //command.append("\0");
  delete[] data;

  /*QDataStream in(socket);
  in.setVersion(QDataStream::Qt_4_0);
   
  cout << "In getCommand()" << endl;
 
  if (blockSize == 0) {
    if (socket->bytesAvailable() < (int)sizeof(quint16)){
      return;
    }
        in >> blockSize;
        cout << "blockSize: " << blockSize << endl;
  }
  cout << "blockSize: " << blockSize << endl;
  
  if (socket->bytesAvailable() < blockSize){
    cout << "bytes Available: " << socket->bytesAvailable() << endl;
    return;
  }

  QString command;
  in >> command;
  
  cout << "Got something" << endl;
  cout << command.toStdString() << endl;
  cout << "-------------------"<<endl;
    
  if(oldCommand == command){
    QTimer::singleShot(0, this, SLOT(requestNewFortune()));
    return;
  }else{
    blockSize = 0;
  }*/
  

  cout << "Received Command" << endl;
  cout << command.toStdString() << endl;
  cout << "-------------------"<<endl;

  if(command.contains("ID?")){
    writeToServer("ID=1\n");
  }else if(command.contains("ACCEPTED.")){
  }else if(command.contains("READY?")){
    emit setGUIState(DEFAULT_STATE,"");
    temp_state = DEFAULT_STATE;
    state_cube.setState(DEFAULT_STATE);
    writeToServer("READY\n");
  }else if(command.contains("SOLVE")){
    QStringList commandArgs(command.split(" ",QString::SkipEmptyParts));
    state_cube.setState(commandArgs.at(1).toStdString());
    vector<string> commands;
    if(commandArgs.size() == 3){
	string sol = Search::solution(commandArgs.at(1).toStdString(), 20);
	sol = Search::getFinalSolution(sol, commandArgs.at(2).toStdString());
	vector<int> solutionInt;
        Search::readMoves(sol, solutionInt);
	convertCommands(solutionInt, commands);   
        puzzleSolved(commands);
    }else{
	string sol = Search::solution(commandArgs.at(1).toStdString(), 20);
	vector<int> solutionInt;
        Search::readMoves(sol, solutionInt);    
        convertCommands(solutionInt, commands);
        puzzleSolved(commands);
    }
  }else if(command.contains("g1:WIN")){
    emit weWon(true);
  }else if(command.contains("g1:LOSE")){
    emit weWon(false);
  }else if(command.contains("TIME:")){
  }else{
  }

}

void GPA4Client::convertCommands(vector<int> & coded_cmd, vector<string> & commands){
  string c[18] = {"U", "R", "F", "D", "L", "B", "U'", "R'", "F'", "D'", "L'", "B'", "X", "X'", "Y", "Y'", "Z", "Z'"};
  for (int i = 0 ; i < (int) coded_cmd.size(); i++) {
    commands.push_back(c[coded_cmd.at(i)]);
  }
}

void GPA4Client::puzzleSolved(vector<string> & commands){
  for (vector<string>::iterator iter = commands.begin(); iter != commands.end(); ++iter){
    writeToServer("g1:" + *iter+"\n"); //send command to server 
    //state_cube.process(*iter);         //perform command on local cube
    //temp_state = state_cube.display(); //get current cube state
    //sleep(500);
    //emit setGUIState(temp_state, *iter);
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

  cout << "In writeToServer: length("<<temp_len<<") message("<<message<<")"<<endl;
  cout << "-----------------"<<endl;

  socket->write(temp,temp_len);
} 
