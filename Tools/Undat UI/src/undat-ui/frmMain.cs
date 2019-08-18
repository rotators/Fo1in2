using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace undat_ui
{
    
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void BtnExtract_Click(object sender, EventArgs e)
        {
            this.lblExtracting.Visible = true;

            var extractFiles = File.ReadAllLines(Directory.GetCurrentDirectory() + "\\files.txt");
            this.progressBar.Value = 0;
            this.progressBar.Maximum = extractFiles.Count();

            var extract = new Extractor((err) =>
            {
                MessageBox.Show(err, "FO1 data extractor", MessageBoxButtons.OK, MessageBoxIcon.Error);
            },
            ((currentFile, cur, max) =>
            {
                this.Invoke((MethodInvoker)delegate
                {
                    this.progressBar.Value = cur;
                    this.lblExtracting.Text = $"[{cur}/{max}] " + currentFile;
                });
            }),
            this.txtMaster.Text,
            this.txtDestination.Text, 
            extractFiles,
            Config.Threads);
            extract.Begin();
        }
       
        private void BtnBrowseMaster_Click(object sender, EventArgs e)
        {
            openFileDialog.FileName = "";
            openFileDialog.Filter = "Fallout 1 DAT (*.DAT)|*.DAT";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                txtMaster.Text = openFileDialog.FileName;
            }
        }

        private void BtnBrowseDestination_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
                txtDestination.Text = folderBrowserDialog.SelectedPath;
        }
    }
}
