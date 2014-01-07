using SocialGame.ComLayer;
using SocialGame.CustomAttributes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGame.Controllers
{
    [SGAuthorize]
    public class ProfileController : Controller
    {
        private ComUsers comUsers = new ComUsers();
        private HttpSession session = new HttpSession();

        // GET: /Profile/
        public ActionResult Index()
        {
            var userInfo = comUsers.GetUserInformation();
            if (userInfo == null) //If session goes down
            {
                comUsers.Logout();
                return RedirectToAction("Login", "Account");
            }
            ViewBag.User = userInfo;
            ViewBag.Connections = comUsers.GetUserFriends();
            ViewBag.TableTitle = "Friends";
            ViewBag.Friend = "Self";
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
            var userInfo = comUsers.GetUserInformation(id);
            var userConnections = comUsers.GetUserFriends(id);
            if (userInfo == null || userConnections == null) //If session goes down
            {
                comUsers.Logout();
                return RedirectToAction("Login", "Account");
            }
            ViewBag.User = userInfo;
            ViewBag.Connections = userConnections;
            ViewBag.TableTitle = "Friends";
            if (userInfo.id.ToString() == session.readFromSession("UserId"))
            {
                ViewBag.Friend = "Self";
            }
            else
            {
                int? state = comUsers.GetUserFriendState(id);
                if (state == null)
                {
                    ViewBag.Friend = "False";
                }
                else
                {
                    ViewBag.Friend = state.ToString();
                }
            }
            return View("Index");
        }

        public JsonResult AddFriend(int id, int strength, string tags)
        {
            bool answer = comUsers.AddFriend(id, strength, tags);
            if (answer)
            {
                return Json("True");
            }
            else
            {
                return Json("False");
            }
        }
    }
}
