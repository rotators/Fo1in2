using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
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

        private void MsgError(string error)
            => MessageBox.Show(error, "FO1 DAT extractor", MessageBoxButtons.OK, MessageBoxIcon.Error);

        private void BtnExtract_Click(object sender, EventArgs e)
        {
            this.lblExtracting.Visible = true;
            
            if(isDone)
                Environment.Exit(0);

            var undatFilesPath = Directory.GetCurrentDirectory() + "\\undat_files.txt";
            if (!File.Exists(undatFilesPath))
            {
                MsgError("Unable to find " + undatFilesPath);
                return;
            }

            string[] extractFiles=null;
            try
            {
                extractFiles = File.ReadAllLines(undatFilesPath);
            }
            catch(IOException ex)
            {
                MsgError($"IO exception occured while trying to read {undatFilesPath}: " + ex.Message);
            }
            catch(UnauthorizedAccessException ex)
            {
                MsgError($"Unauthorized to read {undatFilesPath}: " + ex.Message);
            }
            catch (Exception ex)
            {
                MsgError($"Exception occured while trying to read {undatFilesPath}: " + ex.Message);
            }

            if (extractFiles == null)
                return;

            this.progressBar.Value = 0;
            this.progressBar.Maximum = extractFiles.Count();
            this.lblExtracting.Text = "";
            this.btnExtract.Enabled = false;
            var extract = new Extractor((err) =>
            {
                MessageBox.Show(err, "FO1 DAT extractor", MessageBoxButtons.OK, MessageBoxIcon.Error);
                this.btnExtract.Enabled = true;
            },
            ((currentFile, cur, max) =>
            {
                this.Invoke((MethodInvoker)delegate
                {
                    this.progressBar.Value = cur;
                    this.lblExtracting.Text = $"[{cur}/{max}] " + currentFile;
                });

                if (cur == max)
                {
                    this.isDone = true;
                    this.Invoke((MethodInvoker)delegate
                    {
                        this.btnExtract.Text = "Done!";
                        this.btnExtract.Enabled = true;
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

        private void lnkRotators_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://github.com/rotators");
        }

        private void lnkSource_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://github.com/rotators/Fo1in2/tree/master/Tools/Undat%20UI/src");
        }

        private void lnkFodev_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            System.Diagnostics.Process.Start("https://fodev.net");
        }
    }
}
