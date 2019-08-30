using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Overseer
{
    public partial class frmDatafiles : Form
    {
        public frmDatafiles()
        {
            InitializeComponent();
        }

        private void FrmDatafiles_Load(object sender, EventArgs e)
        {
            lstDatafiles.Items.Clear();
            lstFiles.Items.Clear();
            foreach(var p in Engine.ReadPaths())
            {
                var datArchive = p.datArchive.Read();
                lstDatafiles.Items.Add(new ListViewItem(new string[] { p.path, datArchive.numFiles.ToString() }));
                foreach(var f in datArchive.GetFiles())
                {
                    lstFiles.Items.Add(new ListViewItem(new string[] { $"{p.path.Trim('\0')}\\{f.path}", f.compressed ? "Yes" : "No", f.size.ToString(), f.packedSize.ToString(), f.offset.ToString()  }));
                }
            }

        }
    }
}
