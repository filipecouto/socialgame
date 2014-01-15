
using SocialGame.ComLayer;
using System;
using System.Data;
namespace SocialGame.Models
{
    public class User
    {
        public int id { get; set; }
        public string username { get; set; }
        public int type { get; set; }
        public Mood mood { get; set; }
        public int totalScore { get; set; }
        public int totalStrength { get; set; }
        public string picture { get; set; }

        private IntExtension intExtension = new IntExtension();

        public void populateUser(DataRow dataRow, DataTable moods)
        {
            this.id = Int32.Parse(dataRow["id"].ToString());
            this.username = dataRow["username"].ToString();
            this.type = Int32.Parse(dataRow["type"].ToString());
            this.mood = new Mood().getMoodById(moods, intExtension.ParseInt(dataRow["moodId"].ToString()));
            this.totalScore = Int32.Parse(dataRow["totalScore"].ToString());
            this.totalStrength = Int32.Parse(dataRow["totalStrength"].ToString());
            this.picture = dataRow["picture"].ToString();
        }
    }
}