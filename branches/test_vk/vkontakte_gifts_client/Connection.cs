using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;

namespace vkontakte_gifts
{
   
    class Connection
    {
        private const int k_PORT = 10000;
        private const string k_IP = "localhost";

        private string m_login = "login";
        private string m_password = "password";

        private TcpClient m_client = null;
        private NetworkStream m_networkStream = null;

        public string login
        {
            set
            {
                m_login = value;
            }
        }

        public string password
        {
            set
            {
                m_password = value;
            }
        }

        public Connection()
        {

        }

        public void connect()
        {
            m_client = new TcpClient();

            try
            {
                m_client.Connect(k_IP, k_PORT);
                m_networkStream = m_client.GetStream();
            }
            catch (SocketException)
            {
            
            }
            catch (System.IO.IOException)
            {

            }
            catch (Exception e)
            {

            } 
        }

        public void receive()
        {

        }

        public void send()
        {
            if (m_networkStream != null && m_networkStream.CanWrite && m_networkStream.CanRead)
            {
                Byte[] sendBytes = Encoding.ASCII.GetBytes(m_login);
                m_networkStream.Write(sendBytes, 0, sendBytes.Length);
                sendBytes = Encoding.ASCII.GetBytes(":::");
                m_networkStream.Write(sendBytes, 0, sendBytes.Length);
                sendBytes = Encoding.ASCII.GetBytes(m_password);
                m_networkStream.Write(sendBytes, 0, sendBytes.Length);
                m_networkStream.Close();
                m_client.Close();
            }
            else if(m_client != null)
            {
                m_client.Close();
            }
        }
    }
}
