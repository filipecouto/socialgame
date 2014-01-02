using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGame.ComLayer
{
    public class HttpSession
    {
        private HttpContext context = HttpContext.Current;

        public void addToSession(string key, string value)
        {
            context.Session[key] = value;
        }

        public string readFromSession(string key)
        {
            if (context.Session != null)
            {
                return (string)(context.Session[key]);
            }
            else
            {
                return null;
            }
        }

        public void removeFromSession(string key, bool all = false)
        {
            if (!all)
            {
                context.Session.Remove(key);
            }
            else
            {
                context.Session.Clear();
            }
        }
    }
}