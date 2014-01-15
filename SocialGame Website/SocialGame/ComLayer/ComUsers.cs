using SocialGame.Models;
using SocialGame.Views.Shared;
using System.Collections.Generic;
using System.Data;
using System.Web;
using System.Web.Mvc;
using System.Web.Security;

namespace SocialGame.ComLayer
{
    public class ComUsers
    {
        private ComunicationI comInterface = new ComunicationI();
        private HttpSession session = new HttpSession();

        public bool CreateUserAndAccount(string userName, string email, string password)
        {
            string url = comInterface.comServer + "Users/createUser?Params=" + userName + "^" + password + "^" + email;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else if (answer == "DuplicateEmail")
            {
                throw new MembershipCreateUserException(MembershipCreateStatus.DuplicateEmail);
            }
            else
            {
                throw new MembershipCreateUserException(MembershipCreateStatus.ProviderError);
            }
        }

        public bool Login(string email, string password)
        {
            //Get Token
            string url = comInterface.comServer + "Users/doLogin?Params=" + email + "^" + password;
            string token = comInterface.GetSingleData(url);
            System.Diagnostics.Debug.WriteLine(token);
            if (token != "-1" && token != "-2" && token != null)
            {
                session.addToSession("Token", token); //Add token to session
                session.addToSession("Email", email); //Add email to session
                User user = GetUserInformation();
                session.addToSession("UserName", user.username); //Add username to session
                session.addToSession("UserId", user.id.ToString()); //Add id to session
                return true;
            }
            return false;
        }

        public void Logout()
        {
            session.removeFromSession("Token");
            session.removeFromSession("Email");
            session.removeFromSession("UserName");
            session.removeFromSession("UserId");
        }

        public string GetSessionToken()
        {
            string token = session.readFromSession("Token");
            return token;
        }

        public bool IsAuthorized(int type)
        {
            string token = session.readFromSession("Token");
            return IsAuthorizedHelper(token, type);
        }
        public bool IsAuthorized(HttpContextBase httpContext, int type)
        {
            try
            {
                string token = httpContext.Session["Token"].ToString();
                return IsAuthorizedHelper(token, type);
            }
            catch (System.NullReferenceException)
            {
                return false;
            }
        }

        private bool IsAuthorizedHelper(string token, int type)
        {
            string url = comInterface.comServer + "Users/isUserAuthorized?Params=" + token + "^" + type;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool IsTokenValid(HttpContextBase httpContext)
        {
            try
            {
                string token = httpContext.Session["Token"].ToString();
                string url = comInterface.comServer + "Users/isTokenValid?Params=" + token;
                string answer = comInterface.GetSingleData(url);
                if (answer == "True")
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            catch (System.NullReferenceException)
            {
                return false;
            }
        }

        public bool ChangePassword(string oldPassword, string newPassword)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Users/modifyUserPassword?Params=" + token + "^" + oldPassword + "^" + newPassword;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public User GetUserInformation(int id = -1)
        {
            string url;
            if (id == -1)
            {
                string token = GetSessionToken();
                if (token == null)
                {
                    return null;
                }
                url = comInterface.comServer + "Users/returnUser?Params=" + token;
            }
            else
            {
                url = comInterface.comServer + "Users/returnUserById?Params=" + id;
            }
            DataTable dataTable = comInterface.GetMultipleData(url);
            DataRow dataRow = dataTable.Rows[0];
            User user = new User();
            user.populateUser(dataRow, GetMoods());
            return user;
        }

        public List<User> GetUsersByName(string userName)
        {
            List<User> users = new List<User>();
            string url = comInterface.comServer + "Users/returnUsers?Params=" + userName;
            DataTable dataTable = comInterface.GetMultipleData(url);
            foreach (DataRow row in dataTable.Rows)
            {
                User aux = new User();
                aux.populateUser(row, GetMoods());
                users.Add(aux);
            }
            return users;
        }

        public bool AddFriend(int friendId, int strength, string tags)
        {
            string token = GetSessionToken();
            string url = comInterface.comServer + "Connections/addFriend?Params=" + token + "^" + friendId + "^" + strength + "^" + tags;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public int? GetUserFriendState(int userId)
        {
            string token = GetSessionToken();
            string url = comInterface.comServer + "Connections/returnConnectionState?Params=" + token + "^" + userId;
            string state = comInterface.GetSingleData(url);
            if (state != "False")
            {
                return int.Parse(state);
            }
            return null;
        }

        public List<Connection> GetUserFriends(int id = -1)
        {
            List<Connection> connections = new List<Connection>();
            string url;
            int userId;
            if (id == -1)
            {
                string token = GetSessionToken();
                if (token == null)
                {
                    return null;
                }
                url = comInterface.comServer + "Connections/returnUserConnectionsWithState?Params=" + token + "^1";
                userId = int.Parse(session.readFromSession("UserId"));
            }
            else
            {
                url = comInterface.comServer + "Connections/returnUserConnectionsWithStateById?Params=" + id + "^1";
                userId = id;
            }

            DataTable dataTable = comInterface.GetMultipleData(url);
            foreach (DataRow row in dataTable.Rows)
            {
                int user1 = int.Parse(row["user1"].ToString());
                int user2 = int.Parse(row["user2"].ToString());
                User aux;
                if (userId == user1)
                {
                    aux = GetUserInformation(user2);
                }
                else
                {
                    aux = GetUserInformation(user1);
                }
                Connection con = new Connection();
                con.friend = aux;
                con.strength = int.Parse(row["strength"].ToString());
                con.totalScore = int.Parse(row["totalScore"].ToString());
                connections.Add(con);
            }
            return connections;

        }

        public bool ChangeUserName(string newUserName)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Users/modifyUserName?Params=" + token + "^" + newUserName;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                session.removeFromSession("UserName");
                session.addToSession("UserName", newUserName);
                return true;
            }
            else
            {
                return false;
            }
        }

        public DataTable GetMoods()
        {
            string url = comInterface.comServer + "Moods/getAllMoods";
            DataTable dataTable = comInterface.GetMultipleData(url);
            return dataTable;
        }

        public List<SelectListItem> GetMoodsSelectList()
        {
            var listMoods = new List<SelectListItem>();

            DataTable dataTable = GetMoods();
            foreach (DataRow row in dataTable.Rows)
            {
                listMoods.Add(new SelectListItem { Text = row["description"].ToString(), Value = row["id"].ToString() });
            }

            return listMoods;
        }

        public bool ChangeUserMood(int moodId)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Users/modifyUserMood?Params=" + token + "^" + moodId;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool ChangeUserPicture(string link)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Users/modifyUserPicture?Params=" + token + "^" + link;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public List<Notification> GetUserNotifications(int state)
        {
            string token = GetSessionToken();
            if (token == null) return null;
            List<Notification> notifications = new List<Notification>();
            string url = comInterface.comServer + "Notifications/findNotificationsByToken?Params=" + token + "^" + state;
            DataTable dataTable = comInterface.GetMultipleData(url);
            foreach (DataRow row in dataTable.Rows)
            {
                Notification aux = new Notification();
                aux.populateNotification(row);
                notifications.Add(aux);
            }
            return notifications;
        }

        public bool ActionToFriend(int notificationId, int action)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Connections/actionToFriend?Params=" + notificationId + "^" + action;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        public Connection GetConnection(int connectionId)
        {
            string url = comInterface.comServer + "Connections/returnConnection?Params=" + connectionId;
            DataTable dataTable = comInterface.GetMultipleData(url);
            DataRow row = dataTable.Rows[0];
            Connection connection = new Connection();
            connection.populateConnection(row);
            return connection;
        }

        public TagCloud GetPublicTagStats(int type)
        {
            TagCloud tc = new TagCloud();
            DataTable dataTable = comInterface.GetMultipleData(comInterface.comServer + "Tags/getTagStats?Params=^" + type);
            foreach (DataRow r in dataTable.Rows)
            {
                tc.Add(new TagCloudItem((string)r["name"], float.Parse((string)r["occurrences"])));
            }
            return tc;
        }
        public List<User> getLeaderUsers() {
            List<User> leaderUsers = new List<User>();

            DataTable dataTable = comInterface.GetMultipleData(comInterface.comServer + "Users/getAllUsers");
            foreach (DataRow row in dataTable.Rows)
            {
                User aux = new User();
                aux.populateUser(row, GetMoods());
                leaderUsers.Add(aux);
            }
            return leaderUsers;
        }

        public string getPosition()
        {
            string token = GetSessionToken();
            if (token == null) return "-1";
            string url = comInterface.comServer + "Users/userPosition?Params=" + token;
            string answer = comInterface.GetSingleData(url);
            return answer;
        }

        public string GetUserTags()
        {
            string token = GetSessionToken();
            if (token == null) return null;
            string tags = "";
            DataTable dataTable = comInterface.GetMultipleData(comInterface.comServer + "Tags/getUserTagsByToken?Params=" + token);
            foreach (DataRow row in dataTable.Rows)
            {
                tags += row["Name"] + ";";
            }
            if(tags != "") tags = tags.Remove(tags.Length - 1);
            return tags;
        }

        public bool ChangeUserTags(string tags)
        {
            string token = GetSessionToken();
            if (token == null) return false;
            string url = comInterface.comServer + "Users/setUserTags?Params=" + token + "^" + tags + "^;";
            string answer = comInterface.GetSingleData(url);
            return true;
        }
    }
}