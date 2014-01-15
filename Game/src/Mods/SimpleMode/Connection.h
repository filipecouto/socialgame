#ifndef SM_CONNECTION_H
#define SM_CONNECTION_H
#include "../../Models/IConnection.h"
#include "Person.h"
namespace SimpleMode {
	class Connection : public IConnection {
		public:
			Connection(Person * person);
			~Connection();

			virtual int getScore();
			virtual int getStrength();

			virtual int getState();
			virtual void setState(int state);

			virtual IPerson * getPerson();
			
			virtual void reload();
			virtual ITagsList * getTags();

		private:

			int id;
			int personId;
			IPerson * person = NULL;
			int score, strength, state;

			int _from;

			virtual void load();
	};
}
#endif // CONNECTION_H
