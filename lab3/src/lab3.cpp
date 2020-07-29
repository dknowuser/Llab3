//============================================================================
// Name        : lab3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
	//Choose and open required output file
	char reportName[256];
	unsigned long delayForMain = 0;
	unsigned long delayForFork = 0;
	unsigned long delayForVfork = 0;
	int pid = getpid();

	//Clear output file
	ofstream report;
	report.open(reportName, ios::out);
	report.close();

	cout << "Введите имя файла, куда будет производиться вывод имён и атрибутов процессов:\n" << endl;
	cin >> reportName;
	cout << "Введите величину задержки для для главного процесса в с: ";
	cin >> delayForMain;
	cout << "Введите величину задержки для процесса-потомка, созданного с помощью fork, в с: ";
	cin >> delayForFork;
	cout << "Введите величину задержки для процесса-потомка, созданного с помощью vfork, в с: ";
	cin >> delayForVfork;

	//Create and manage child processes
	fork();
	if(pid != getpid())
	{
		sleep(delayForFork);

		report.open(reportName, ios::app);
		report << "Запущена программа-потомок с помощью функции fork." << endl;
		report << "Идентификатор процесса: " << getpid() << endl;
		report << "Идентификатор предка: " << getppid() << endl;
		report << "Идентификатор сессии процесса: " << getsid(0) << endl;
		report << "Идентификатор группы процессов: " << getpgid(0) << endl;
		report << "Реальный идентификатор пользователя: " << getuid() << endl;
		report << "Эффективный идентификатор пользователя: " << geteuid() << endl;
		report << "Реальный групповой идентификатор: " << getgid() << endl;
		report << "Эффективный групповой идентификатор: " << getegid() << endl;

		report << endl;
		report.close();
		exit(0);

		while(true);
	};

	vfork();
	if(pid != getpid())
	{
		sleep(delayForVfork);
		char buffer[256];
		sprintf(buffer, "%d", delayForVfork);
		execl("/home/wetfloor/eclipse-workspaces/study/childForVfork/childForVfork/Debug/childForVfork",
			(char*)reportName, buffer, (char*)0);
	};

	sleep(delayForMain);
	report.open(reportName, ios::app);
	report << "Запущена программа-предок." << endl;
	report << "Идентификатор процесса: " << getpid() << endl;
	report << "Идентификатор предка: " << getppid() << endl;
	report << "Идентификатор сессии процесса: " << getsid(0) << endl;
	report << "Идентификатор группы процессов: " << getpgid(0) << endl;
	report << "Реальный идентификатор пользователя: " << getuid() << endl;
	report << "Эффективный идентификатор пользователя: " << geteuid() << endl;
	report << "Реальный групповой идентификатор: " << getgid() << endl;
	report << "Эффективный групповой идентификатор: " << getegid() << endl;

	report << endl;
	report.close();

	while(true);

	return 0;
}
