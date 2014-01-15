using SocialGame.ComLayer;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;

namespace SocialGame.Models
{
    public class Mood
    {
        public int? id { set; get; }

        public string description { set; get; }

        private IntExtension intExtension = new IntExtension();

        public Mood getMoodById(DataTable moods, int? moodId)
        {
            Mood mood = new Mood();
            mood.id = null;
            mood.description = "No Mood";
            if (moodId == null)
            {
                return mood;
            }

            foreach (DataRow row in moods.Rows)
            {
                if (row["id"].ToString() == moodId.ToString())
                {
                    mood.id = intExtension.ParseInt(row["id"].ToString());
                    mood.description = row["description"].ToString();
                    return mood;
                }
            }

            return mood;
        }
    }
}