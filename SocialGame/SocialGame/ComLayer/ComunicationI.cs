using System;
using System.Collections.Generic;
using System.IO;
using System.Net;

namespace SocialGame.ComLayer
{
    public class ComunicationI
    {
        public string comServer = "http://uvm001.dei.isep.ipp.pt/SocialGameCommunicationService/InterfaceToBLL";

        public string MakeRequest(string url)
        {
            WebRequest request = WebRequest.Create(url);
            WebResponse response = request.GetResponse();
            Stream dataStream = response.GetResponseStream();
            StreamReader reader = new StreamReader(dataStream);
            string responseFromServer = reader.ReadToEnd();
            reader.Close();
            response.Close();
            return responseFromServer;
        }
    }
}