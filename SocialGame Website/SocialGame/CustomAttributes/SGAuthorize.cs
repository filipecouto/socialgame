using SocialGame.ComLayer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGame.CustomAttributes
{
    public class SGAuthorize : AuthorizeAttribute
    {
        private ComUsers comUsers = new ComUsers();
        public int[] Types { get; set; }
        protected override bool AuthorizeCore(HttpContextBase httpContext)
        {
            bool check = false;
            if (Types != null)
            {
                foreach (int i in Types)
                {
                    if (comUsers.IsAuthorized(httpContext, i))
                    {
                        check = true;
                    }
                }
            }
            else
            {
                check = comUsers.IsTokenValid(httpContext);
            }
            return check;
        }
    }
}