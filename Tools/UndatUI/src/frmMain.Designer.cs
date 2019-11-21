namespace undat_ui
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.label1 = new System.Windows.Forms.Label();
            this.txtMaster = new System.Windows.Forms.TextBox();
            this.btnExtract = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.txtDestination = new System.Windows.Forms.TextBox();
            this.btnBrowseMaster = new System.Windows.Forms.Button();
            this.btnBrowseDestination = new System.Windows.Forms.Button();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.lblExtracting = new System.Windows.Forms.Label();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.folderBrowserDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.lblVersion = new System.Windows.Forms.Label();
            this.lnkSource = new System.Windows.Forms.LinkLabel();
            this.lnkRotators = new System.Windows.Forms.LinkLabel();
            this.label4 = new System.Windows.Forms.Label();
            this.lnkFodev = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(254, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Select MASTER.DAT from your Fallout 1 installation:";
            // 
            // txtMaster
            // 
            this.txtMaster.Location = new System.Drawing.Point(9, 53);
            this.txtMaster.Name = "txtMaster";
            this.txtMaster.Size = new System.Drawing.Size(321, 20);
            this.txtMaster.TabIndex = 1;
            // 
            // btnExtract
            // 
            this.btnExtract.Location = new System.Drawing.Point(7, 195);
            this.btnExtract.Name = "btnExtract";
            this.btnExtract.Size = new System.Drawing.Size(355, 33);
            this.btnExtract.TabIndex = 2;
            this.btnExtract.Text = "Extract";
            this.btnExtract.UseVisualStyleBackColor = true;
            this.btnExtract.Click += new System.EventHandler(this.BtnExtract_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(5, 85);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(298, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Select destination mod folder (380 MB of free space required):";
            // 
            // txtDestination
            // 
            this.txtDestination.Location = new System.Drawing.Point(8, 101);
            this.txtDestination.Name = "txtDestination";
            this.txtDestination.Size = new System.Drawing.Size(321, 20);
            this.txtDestination.TabIndex = 4;
            // 
            // btnBrowseMaster
            // 
            this.btnBrowseMaster.Location = new System.Drawing.Point(336, 53);
            this.btnBrowseMaster.Name = "btnBrowseMaster";
            this.btnBrowseMaster.Size = new System.Drawing.Size(26, 20);
            this.btnBrowseMaster.TabIndex = 5;
            this.btnBrowseMaster.Text = "...";
            this.btnBrowseMaster.UseVisualStyleBackColor = true;
            this.btnBrowseMaster.Click += new System.EventHandler(this.BtnBrowseMaster_Click);
            // 
            // btnBrowseDestination
            // 
            this.btnBrowseDestination.Location = new System.Drawing.Point(336, 101);
            this.btnBrowseDestination.Name = "btnBrowseDestination";
            this.btnBrowseDestination.Size = new System.Drawing.Size(26, 21);
            this.btnBrowseDestination.TabIndex = 6;
            this.btnBrowseDestination.Text = "...";
            this.btnBrowseDestination.UseVisualStyleBackColor = true;
            this.btnBrowseDestination.Click += new System.EventHandler(this.BtnBrowseDestination_Click);
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(8, 136);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(354, 23);
            this.progressBar.Step = 1;
            this.progressBar.TabIndex = 7;
            // 
            // lblExtracting
            // 
            this.lblExtracting.AutoSize = true;
            this.lblExtracting.Location = new System.Drawing.Point(7, 165);
            this.lblExtracting.Name = "lblExtracting";
            this.lblExtracting.Size = new System.Drawing.Size(78, 13);
            this.lblExtracting.TabIndex = 8;
            this.lblExtracting.Text = "Extracting file x";
            this.lblExtracting.Visible = false;
            // 
            // openFileDialog
            // 
            this.openFileDialog.FileName = "openFileDialog1";
            // 
            // lblVersion
            // 
            this.lblVersion.AutoSize = true;
            this.lblVersion.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblVersion.Location = new System.Drawing.Point(9, 15);
            this.lblVersion.Name = "lblVersion";
            this.lblVersion.Size = new System.Drawing.Size(57, 12);
            this.lblVersion.TabIndex = 9;
            this.lblVersion.Text = "Version 1.02";
            // 
            // lnkSource
            // 
            this.lnkSource.AutoSize = true;
            this.lnkSource.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lnkSource.Location = new System.Drawing.Point(305, 3);
            this.lnkSource.Name = "lnkSource";
            this.lnkSource.Size = new System.Drawing.Size(58, 12);
            this.lnkSource.TabIndex = 12;
            this.lnkSource.TabStop = true;
            this.lnkSource.Text = "Source Code";
            this.lnkSource.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkSource_LinkClicked);
            // 
            // lnkRotators
            // 
            this.lnkRotators.AutoSize = true;
            this.lnkRotators.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lnkRotators.Location = new System.Drawing.Point(57, 3);
            this.lnkRotators.Name = "lnkRotators";
            this.lnkRotators.Size = new System.Drawing.Size(41, 12);
            this.lnkRotators.TabIndex = 13;
            this.lnkRotators.TabStop = true;
            this.lnkRotators.Text = "Rotators";
            this.lnkRotators.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkRotators_LinkClicked);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(9, 3);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 12);
            this.label4.TabIndex = 14;
            this.label4.Text = "Created by";
            // 
            // lnkFodev
            // 
            this.lnkFodev.AutoSize = true;
            this.lnkFodev.Font = new System.Drawing.Font("Microsoft Sans Serif", 6.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lnkFodev.Location = new System.Drawing.Point(317, 19);
            this.lnkFodev.Name = "lnkFodev";
            this.lnkFodev.Size = new System.Drawing.Size(45, 12);
            this.lnkFodev.TabIndex = 15;
            this.lnkFodev.TabStop = true;
            this.lnkFodev.Text = "fodev.net";
            this.lnkFodev.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkFodev_LinkClicked);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(374, 237);
            this.Controls.Add(this.lnkFodev);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lnkRotators);
            this.Controls.Add(this.lnkSource);
            this.Controls.Add(this.lblVersion);
            this.Controls.Add(this.lblExtracting);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.btnBrowseDestination);
            this.Controls.Add(this.btnBrowseMaster);
            this.Controls.Add(this.txtDestination);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.btnExtract);
            this.Controls.Add(this.txtMaster);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "FO1 DAT extractor";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtMaster;
        private System.Windows.Forms.Button btnExtract;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtDestination;
        private System.Windows.Forms.Button btnBrowseMaster;
        private System.Windows.Forms.Button btnBrowseDestination;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label lblExtracting;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog;
        private System.Windows.Forms.Label lblVersion;
        private System.Windows.Forms.LinkLabel lnkSource;
        private System.Windows.Forms.LinkLabel lnkRotators;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.LinkLabel lnkFodev;
    }
}

