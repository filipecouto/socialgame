using SocialGame.ComLayer;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;

namespace SocialGame.Models
{
    public class Connection
    {
        public int id { get; set; }
        public User user1 { get; set; }
        public User user2 { get; set; }
        public User friend { get; set; }
        public int state { get; set; }
        public int strength { get; set; }
        public int totalScore { get; set; }
        private ComUsers comUsers = new ComUsers();
        public void populateConnection(DataRow dataRow)
        {
            this.id = Int32.Parse(dataRow["id"].ToString());
            this.user1 = comUsers.GetUserInformation(Int32.Parse(dataRow["user1"].ToString()));
            this.user2 = comUsers.GetUserInformation(Int32.Parse(dataRow["user2"].ToString()));
            this.state = Int32.Parse(dataRow["state"].ToString());
            this.strength = Int32.Parse(dataRow["strength"].ToString());
            this.totalScore = Int32.Parse(dataRow["totalScore"].ToString());
        }
    }
}