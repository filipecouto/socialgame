using Newtonsoft.Json;
using System.Data;
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

        public string GetSingleData(string url)
        {
            string jsonRequest = MakeRequest(url);
            string answer = JsonConvert.DeserializeObject<SingleData>(jsonRequest).Data;
            return answer;
        }

        public DataTable GetMultipleData(string url)
        {
            string jsonRequest = MakeRequest(url);
            DataSet dataSet = JsonConvert.DeserializeObject<DataSet>(jsonRequest);
            DataTable dataTable = dataSet.Tables["data"];
            return dataTable;
        }
    }
}