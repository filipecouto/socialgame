using SocialGame.ComLayer;
using SocialGame.Views.Shared;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace SocialGame.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewBag.Message = "Grab your friends now!";
            TagCloud test;
            ComUsers com = new ComUsers();

            if (com.IsTokenValid(HttpContext))
            {
                test = com.GetPublicTagStats(4);
            }
            else
            {
                test = new TagCloud();
                
            }
            return View(test);
        }

        public ActionResult Download()
        {
            ViewBag.Message = "Your all mighty Social Game download page.";

            return View();
        }

        public ActionResult LeaderBoard()
        {
            ComUsers com = new ComUsers();
            ViewBag.Users = com.getLeaderUsers();
            string userPosition = com.getPosition();
            if (userPosition != null && userPosition != "-1") //If not logged in
            {
                ViewBag.Position = userPosition;
            }
            return View();
        }
    }
}
