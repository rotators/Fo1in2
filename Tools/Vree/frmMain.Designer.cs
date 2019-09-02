namespace Vree
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
            this.lstViewMain = new System.Windows.Forms.ListView();
            this.btnShowVariables = new System.Windows.Forms.Button();
            this.txtSearch = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.btnShowFunctions = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstViewMain
            // 
            this.lstViewMain.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lstViewMain.FullRowSelect = true;
            this.lstViewMain.GridLines = true;
            this.lstViewMain.HideSelection = false;
            this.lstViewMain.Location = new System.Drawing.Point(12, 122);
            this.lstViewMain.Name = "lstViewMain";
            this.lstViewMain.Size = new System.Drawing.Size(929, 494);
            this.lstViewMain.TabIndex = 0;
            this.lstViewMain.UseCompatibleStateImageBehavior = false;
            this.lstViewMain.View = System.Windows.Forms.View.Details;
            this.lstViewMain.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.LstViewMain_ColumnClick);
            // 
            // btnShowVariables
            // 
            this.btnShowVariables.Location = new System.Drawing.Point(93, 38);
            this.btnShowVariables.Name = "btnShowVariables";
            this.btnShowVariables.Size = new System.Drawing.Size(75, 27);
            this.btnShowVariables.TabIndex = 1;
            this.btnShowVariables.Text = "Variables";
            this.btnShowVariables.UseVisualStyleBackColor = true;
            this.btnShowVariables.Click += new System.EventHandler(this.BtnShowVariables_Click);
            // 
            // txtSearch
            // 
            this.txtSearch.Location = new System.Drawing.Point(53, 96);
            this.txtSearch.Name = "txtSearch";
            this.txtSearch.Size = new System.Drawing.Size(396, 20);
            this.txtSearch.TabIndex = 2;
            this.txtSearch.TextChanged += new System.EventHandler(this.TxtSearch_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 99);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Search";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(953, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // toolsToolStripMenuItem
            // 
            this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
            this.toolsToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
            this.toolsToolStripMenuItem.Text = "Export";
            // 
            // btnShowFunctions
            // 
            this.btnShowFunctions.Location = new System.Drawing.Point(12, 38);
            this.btnShowFunctions.Name = "btnShowFunctions";
            this.btnShowFunctions.Size = new System.Drawing.Size(75, 27);
            this.btnShowFunctions.TabIndex = 5;
            this.btnShowFunctions.Text = "Functions";
            this.btnShowFunctions.UseVisualStyleBackColor = true;
            this.btnShowFunctions.Click += new System.EventHandler(this.BtnShowFunctions_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(953, 628);
            this.Controls.Add(this.btnShowFunctions);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtSearch);
            this.Controls.Add(this.btnShowVariables);
            this.Controls.Add(this.lstViewMain);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmMain";
            this.Text = "Vree";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView lstViewMain;
        private System.Windows.Forms.Button btnShowVariables;
        private System.Windows.Forms.TextBox txtSearch;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolsToolStripMenuItem;
        private System.Windows.Forms.Button btnShowFunctions;
    }
}

