using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace vkontakte_gifts
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            Connection connection = new Connection();
            connection.connect();
            string login = etLogin.Text;
            string password = etPassword.Text;
            if (login.Length > 0 && password.Length > 0)
            {
                connection.login = login;
                connection.password = password;
                connection.send();
            }
        }
    }
}
