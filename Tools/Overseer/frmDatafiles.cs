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
        FalloutMemory mem;
        MemoryReader reader;
        public frmDatafiles(FalloutMemory mem, MemoryReader reader)
        {
            this.mem = mem;
            this.reader = reader;
            InitializeComponent();
        }

        private void FrmDatafiles_Load(object sender, EventArgs e)
        {
            lstDatafiles.Items.Clear();
            lstFiles.Items.Clear();
            var paths = mem.ReadPaths().ToList();
            foreach(var p in paths)
            {
                var datArchive = p.datArchive.Read();
                lstDatafiles.Items.Add(new ListViewItem(new string[] { p.path, datArchive.numFiles.ToString() }));
                var files = datArchive.GetFiles(reader).ToList();
                foreach(var f in files)
                {
                    lstFiles.Items.Add(new ListViewItem(new string[] { $"{p.path.Trim('\0')}\\{f.path}", f.compressed ? "Yes" : "No", f.size.ToString(), f.packedSize.ToString(), f.offset.ToString()  }));
                }
            }

        }
    }
}
