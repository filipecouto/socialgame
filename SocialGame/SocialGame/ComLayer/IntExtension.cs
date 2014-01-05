using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGame.ComLayer
{
    public class IntExtension
    {
        public int? ParseInt(string val)
        {
            int i;
            return int.TryParse(val, out i) ? (int?)i : null;
        }
    }
}