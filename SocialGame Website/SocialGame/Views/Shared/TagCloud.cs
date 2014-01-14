using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace SocialGame.Views.Shared
{
    public class TagCloud
    {
        List<TagCloudItem> items;

        public TagCloud()
        {
            items = new List<TagCloudItem>();
        }

        public int Count { get { return items.Count; } }

        public TagCloudItem GetItem(int index)
        {
            return items[index];
        }

        public void Add(TagCloudItem item)
        {
            items.Add(item);
        }
    }

    public class TagCloudItem
    {
        public TagCloudItem()
        {

        }

        public TagCloudItem(string title, float occurrences)
        {
            Title = title;
            Occurrences = occurrences;
        }

        public string Title { get; set; }
        public float Occurrences { get; set; }
    }
}