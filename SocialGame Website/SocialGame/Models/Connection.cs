using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGame.Models
{
    public class Connection
    {
        public User friend { get; set; }
        public int state { get; set; }
        public int strength { get; set; }
        public int totalScore { get; set; }
    }
}