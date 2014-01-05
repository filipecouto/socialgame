using SocialGame.ComLayer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGame.Controllers
{
    public class ProfileController : Controller
    {
        private ComUsers comUsers = new ComUsers();

        // GET: /Profile/
        public ActionResult Index()
        {
            ViewBag.User = comUsers.GetUserInformation();
            ViewBag.Users = comUsers.GetUserFriends();
            ViewBag.TableTitle = "Friends";
            return View();
        }

        public ActionResult People(string userName)
        {
            ViewBag.Users = comUsers.GetUsersByName(userName);
            ViewBag.TableTitle = "People";
            return View();
        }

        public ActionResult PersonProfile(int id)
        {
            ViewBag.User = comUsers.GetUserInformation(id);
            ViewBag.Users = comUsers.GetUserFriends(id);
            ViewBag.TableTitle = "Friends";
            ViewBag.Friend = "False";
            return View("Index");
        }
    }
}
