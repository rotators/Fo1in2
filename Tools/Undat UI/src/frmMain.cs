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
        bool isDone = false;

        public frmMain()
        {
            InitializeComponent();
        }

        private void BtnExtract_Click(object sender, EventArgs e)
        {
            this.lblExtracting.Visible = true;
            
            if(isDone)
                Environment.Exit(0);

            var extractFiles = File.ReadAllLines(Directory.GetCurrentDirectory() + "\\undat_files.txt");
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

                if(cur==max)
                {
                    this.isDone = true;
                    this.Invoke((MethodInvoker)delegate
                    {
                        this.btnExtract.Text = "Done!";
                    });
                }
            }),
            this.txtMaster.Text,
            this.txtDestination.Text, 
            extractFiles);
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

        bool FalloutExists(string path)
        {
            foreach(var file in Directory.GetFiles(path))
            {
                if (Path.GetFileName(file).ToLower() == "fallout2.exe")
                    return true;
            }
            return false;
        }

        private void BtnBrowseDestination_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
            {
                if(!FalloutExists(folderBrowserDialog.SelectedPath))
                {
                    if (MessageBox.Show("Fallout2.exe was not found in the selected directory, do you want to select it anyway?", "FO1 data extractor", MessageBoxButtons.YesNo, MessageBoxIcon.Warning) == DialogResult.No)
                        return;
                }
                txtDestination.Text = folderBrowserDialog.SelectedPath;
            }
        }
    }
}
