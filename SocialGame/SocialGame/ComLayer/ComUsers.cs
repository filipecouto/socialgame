using SocialGame.Models;
using System.Collections.Generic;
using System.Data;
using System.Web;
using System.Web.Security;

namespace SocialGame.ComLayer
{
    public class ComUsers
    {
        private ComunicationI comInterface = new ComunicationI();
        private HttpSession session = new HttpSession();

        public bool CreateUserAndAccount(string userName, string email, string password)
        {
            string url = comInterface.comServer + "?Theme=Users&Function=createUser&Params=" + userName + "^" + password + "^" + email;
            string answer = comInterface.GetSingleData(url);
            if (answer == "True")
            {
                return true;
            }
            else if(answer == "DuplicateEmail")
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
            string url = comInterface.comServer + "?Theme=Users&Function=doLogin&Params=" + email + "^" + password;
            string token = comInterface.GetSingleData(url);
            if (token != "-1" && token != "-2")
            {
                //Get UserName
                url = comInterface.comServer + "?Theme=Users&Function=findUserNameByEmail&Params=" + email;
                string userName = comInterface.GetSingleData(url);
                session.addToSession("UserName", userName); //Add username to session
                session.addToSession("Email", email); //Add email to session
                session.addToSession("Token", token); //Add token to session
            }
            return true;
        }

        public void Logout()
        {
            session.removeFromSession("UserName");
            session.removeFromSession("Email");
            session.removeFromSession("Token");
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
            string url = comInterface.comServer + "?Theme=Users&Function=isUserAuthorized&Params=" + token + "^" + type;
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
                string url = comInterface.comServer + "?Theme=Users&Function=isTokenValid&Params=" + token;
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
            //if token empty
            string url = comInterface.comServer + "?Theme=Users&Function=modifyUserPassword&Params=" + token + "^" + oldPassword + "^" + newPassword;
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
                url = comInterface.comServer + "?Theme=Users&Function=returnUser&Params=" + token;
            }
            else
            {
                url = comInterface.comServer + "?Theme=Users&Function=returnUserById&Params=" + id;
            }
            DataTable dataTable = comInterface.GetMultipleData(url);
            DataRow dataRow = dataTable.Rows[0];
            User user = new User();
            user.populateUser(dataRow);
            return user;
        }

        public List<User> GetUsersByName(string userName)
        {
            List<User> users = new List<User>();
            string url = comInterface.comServer + "?Theme=Users&Function=returnUsers&Params=" + userName;
            DataTable dataTable = comInterface.GetMultipleData(url);
            foreach (DataRow row in dataTable.Rows)
            {
                User aux = new User();
                aux.populateUser(row);
                users.Add(aux);
            }
            return users;
        }

        public bool AddFriend(){
            string token = GetSessionToken();
            return false;
        }

        public List<User> GetUserFriends(int id = -1)
        {
            List<User> users = new List<User>();
            /*User aux = new User();
            string token = GetSessionToken();
            string url = comInterface.comServer + "?Theme=Users&Function=returnUsers&Params=" + token;
            DataTable dataTable = comInterface.GetMultipleData(url);
            foreach (DataRow row in dataTable.Rows)
            {
                aux.populateUser(row);
                users.Add(aux);
            }*/
            return users;

        }
    }
}