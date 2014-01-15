#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "File.h"

using namespace std;

string getNumberOfUsers() {
        string command = "/usr/lib/nagios/plugins/check_mysql_query -q \"Select count(*) From Logins\" -u root -p \"nao sei\" -d SocialGame";
        FILE* comm = popen(command.c_str(), "r");
        if(comm) {
                char buff[128];
                string resultado;

                while (fgets(buff, 128, comm))
                     resultado += buff;

                pclose(comm);
		int pos1 = resultado.find("d");
		int pos2 = resultado.find(".");
               return  resultado.substr(pos1+1,(pos2-pos1 -1));
        }
        return string();
}
int main(int, char**) {
        File ultimo("/tmp/check_users");

        if(ultimo.exists()) {
                ultimo.open(false, false);
                if(ultimo.canWrite()) {
                        string numberUsers = getNumberOfUsers();
                        string * ultimoRegisto = ultimo.getLine();
                        if(ultimoRegisto != NULL && ultimoRegisto->compare(numberUsers) == 0) {
                                cout << "Number of valid users:"<<numberUsers;
                                return 0;
                        } else {
                                cout << "The number of users has changed from "<< *ultimoRegisto <<"  to " <<numberUsers;
                                ultimo.open(true, false);
                                ultimo.writeLine(numberUsers);
                                return 1;
                        }
                } else {
                        cout << "Não há permissão de escrita no fiiro";
                        return 1;
                }
        } else {
                cout << "O ficheiro não existe, a criá-lo..." << endl;
                ultimo.open(true, false);
                ultimo.writeLine(getNumberOfUsers());
                cout << "Ficheiro criado com sucesso" << endl;
                return 0;
        }
}

