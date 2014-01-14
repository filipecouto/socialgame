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

        public ActionResult About()
        {
            ViewBag.Message = "Your app description page.";

            return View();
        }

        public ActionResult Contact()
        {
            ViewBag.Message = "Your contact page.";

            return View();
        }
    }
}
