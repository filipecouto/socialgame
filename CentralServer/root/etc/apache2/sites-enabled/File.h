#ifndef FILE_GIL_H
#define FILE_GIL_H

#include <string>
#include <fstream>
#include <stdlib.h>
#include <sys/stat.h>

using namespace std;

/**
 * Esta classe é usada pelos plugins check_last_root_login e check_valid_users
 * com o objectivo de facilitar o uso e modificação dos ficheiros usados por estes.
 */
class File {
	public:
		File(string &path);
		File(string path);

		void open(bool write, bool append);

		bool exists();

		/**
		 * Checks what permissions the process has over the file.
		 * canRead(), canWrite() and canExecute() are better options
		 * @returns an int with the permissions
		 */
		int getPermissions();

		bool canRead();
		bool canWrite();
		bool canExecute();

		bool isOpen();

		string * getLine();
		void writeLine(string line);

		void close();

		virtual ~File();
	
	private:
		fstream * mFile;
		string mPath;
		int mPermissions;
		
		void storePermissions();
};

#endif
