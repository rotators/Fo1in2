using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Vree
{
    public partial class frmComment : Form
    {
        public string Comment;
        public frmComment()
        {
            InitializeComponent();
        }

        public void ReadComment(string Comment) { txtComment.Text = Comment; }

        private void BtnComment_Click(object sender, EventArgs e)
        {
            this.Comment = txtComment.Text;
            this.Close();
        }
    }
}
