using System;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Collections;
using System.Threading;


namespace vkontakte_gifts_server
{
    class Program
    {
        private const int m_port = 10000;
        private static Thread m_thread;
        private static ArrayList m_socketList;

        static void Main(string[] args)
        {
            StartListening();
        }


        public static void StartListening()
        {
            m_socketList = new ArrayList();

            m_thread = new Thread(new ThreadStart(process));
            m_thread.Start();

            TcpListener listener = new TcpListener(m_port);
            try
            {
                listener.Start();
                int ClientNbr = 0;

                Console.WriteLine("Waiting for a connection...");
               
                while(true)
                {

                    TcpClient handler = listener.AcceptTcpClient();

                    if (handler != null)
                    {
                        Console.WriteLine("Client#{0} accepted!", ++ClientNbr);
                        lock (m_socketList.SyncRoot)
                        {
                            int i = m_socketList.Add(new ClientHandler(handler));
                            ((ClientHandler)m_socketList[i]).Start();
                        }
                    }
                    else
                        break;
                }

                listener.Stop();

                m_thread.Join();

                foreach (Object Client in m_socketList)
                {
                    ((ClientHandler)Client).Stop();
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

            Console.WriteLine("\nHit enter to continue...");
            Console.Read();
        }

        private static void process()
        {
            while (true)
            {
                lock (m_socketList.SyncRoot)
                {
                    for (int x = m_socketList.Count - 1; x >= 0; x--)
                    {
                        Object Client = m_socketList[x];
                        if (!((ClientHandler)Client).Alive)
                        {
                            m_socketList.Remove(Client);
                            Console.WriteLine("A client left");
                        }
                    }
                }
                Thread.Sleep(200);
            }
        }
    }

    class ClientHandler
    {
        TcpClient m_socket;
        Thread m_thread;

        public ClientHandler(TcpClient ClientSocket)
        {
            this.m_socket = ClientSocket;
        }

        public void Start()
        {
            m_thread = new Thread(new ThreadStart(Process));
            m_thread.Start();
        }

        private void Process()
        {
            string data = null;

            byte[] bytes;

            if (m_socket != null)
            {
                NetworkStream networkStream = m_socket.GetStream();
                m_socket.ReceiveTimeout = 100; 

                while (true)
                {
                    bytes = new byte[m_socket.ReceiveBufferSize];
                    try
                    {
                        int BytesRead = networkStream.Read(bytes, 0, (int)m_socket.ReceiveBufferSize);
                        if (BytesRead > 0)
                        {
                            data = Encoding.ASCII.GetString(bytes, 0, BytesRead);

                            // Show the data on the console.
                            Console.WriteLine("Text received : {0}", data);

                            // Echo the data back to the client.
                            byte[] sendBytes = Encoding.ASCII.GetBytes(data);
                            networkStream.Write(sendBytes, 0, sendBytes.Length);

                            if (data == "quit") break;

                        }
                    }
                    catch (IOException) { } // Timeout
                    catch (SocketException)
                    {
                        Console.WriteLine("Conection is broken!");
                        break;
                    }
                    Thread.Sleep(200);
                } // while ( ContinueProcess )
                networkStream.Close();
                m_socket.Close();
            }
        }  // Process()

        public void Stop()
        {
            if (m_thread != null && m_thread.IsAlive)
                m_thread.Join();
        }

        public bool Alive
        {
            get
            {
                return (m_thread != null && m_thread.IsAlive);
            }
        }

    } 
}
