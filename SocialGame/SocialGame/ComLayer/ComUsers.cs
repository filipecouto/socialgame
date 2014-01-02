using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Web;

namespace SocialGame.ComLayer
{
    public class ComUsers
    {
        private ComunicationI comInterface = new ComunicationI();
        private HttpSession session = new HttpSession();

        public void CreateUserAndAccount(string userName, string email, string password)
        {
            string url = comInterface.comServer + "?Theme=Users&Function=createUser&Params=" + userName + "^" + password + "^" + email;
            comInterface.MakeRequest(url);
        }

        public bool Login(string email, string password)
        {
            //Get Token
            string url = comInterface.comServer + "?Theme=Users&Function=doLogin&Params=" + email + "^" + password;
            string jsonRequest = comInterface.MakeRequest(url);
            string token = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
            if (token != "-1" && token != "-2")
            {
                //Get UserName
                url = comInterface.comServer + "?Theme=Users&Function=findUserNameByEmail&Params=" + email;
                jsonRequest = comInterface.MakeRequest(url);
                string userName = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
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

        public bool IsAuthorized(int type)
        {
            string token = session.readFromSession("Token");
            return IsAuthorizedHelper(token, type);
        }
        public bool IsAuthorized(HttpContextBase httpContext, int type)
        {
            string token = httpContext.Session["Token"].ToString();
            return IsAuthorizedHelper(token, type);
        }

        private bool IsAuthorizedHelper(string token, int type)
        {
            string url = comInterface.comServer + "?Theme=Users&Function=isUserAuthorized&Params=" + token + "^" + type;
            string jsonRequest = comInterface.MakeRequest(url);
            string answer = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
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
            string token = httpContext.Session["Token"].ToString();
            string url = comInterface.comServer + "?Theme=Users&Function=isTokenValid&Params=" + token;
            string jsonRequest = comInterface.MakeRequest(url);
            string answer = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool ChangePassword(string oldPassword, string newPassword)
        {
            string token = session.readFromSession("Token");
            //if token empty
            string url = comInterface.comServer + "?Theme=Users&Function=modifyUserPassword&Params=" + token + "^" + oldPassword + "^" + newPassword;
            string jsonRequest = comInterface.MakeRequest(url);
            string answer = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
            if (answer == "True")
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}