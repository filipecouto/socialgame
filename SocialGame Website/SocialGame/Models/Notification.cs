using SocialGame.ComLayer;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;

namespace SocialGame.Models
{
    public class Notification
    {
        public int id { get; set; }
        public int type { get; set; }
        public int to { get; set; }
        public int read { get; set; }
        public DateTime date { get; set; }
        public object objectAssigned {get; set; }

        private ComUsers comUsers = new ComUsers();
        public void populateNotification(DataRow dataRow)
        {
            this.id = Int32.Parse(dataRow["id"].ToString());
            this.type = Int32.Parse(dataRow["type"].ToString());
            this.to = Int32.Parse(dataRow["to"].ToString());
            this.read = Int32.Parse(dataRow["read"].ToString());
            this.date = DateTime.Parse(dataRow["date"].ToString());
            this.objectAssigned = comUsers.GetConnection(Int32.Parse(dataRow["object"].ToString()));
        }
    }
}