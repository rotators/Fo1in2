namespace Overseer
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
            this.components = new System.ComponentModel.Container();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.btnAttach = new System.Windows.Forms.Button();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.grOffset = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.grName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.grType = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.grValue = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tmrRefresh = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.grOffset,
            this.grName,
            this.grType,
            this.grValue});
            this.dataGridView1.Location = new System.Drawing.Point(12, 49);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(776, 339);
            this.dataGridView1.TabIndex = 1;
            // 
            // btnAttach
            // 
            this.btnAttach.Location = new System.Drawing.Point(12, 13);
            this.btnAttach.Name = "btnAttach";
            this.btnAttach.Size = new System.Drawing.Size(121, 30);
            this.btnAttach.TabIndex = 2;
            this.btnAttach.Text = "Attach";
            this.btnAttach.UseVisualStyleBackColor = true;
            this.btnAttach.Click += new System.EventHandler(this.BtnAttach_Click);
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(214, 13);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(106, 30);
            this.btnRefresh.TabIndex = 3;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.BtnRefresh_Click);
            // 
            // grOffset
            // 
            this.grOffset.HeaderText = "Offset";
            this.grOffset.Name = "grOffset";
            // 
            // grName
            // 
            this.grName.HeaderText = "Name";
            this.grName.Name = "grName";
            // 
            // grType
            // 
            this.grType.HeaderText = "Type";
            this.grType.Name = "grType";
            // 
            // grValue
            // 
            this.grValue.HeaderText = "Value";
            this.grValue.Name = "grValue";
            // 
            // tmrRefresh
            // 
            this.tmrRefresh.Tick += new System.EventHandler(this.TmrRefresh_Tick);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 405);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.btnAttach);
            this.Controls.Add(this.dataGridView1);
            this.Name = "frmMain";
            this.Text = "Overseer";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button btnAttach;
        private System.Windows.Forms.Button btnRefresh;
        private System.Windows.Forms.DataGridViewTextBoxColumn grOffset;
        private System.Windows.Forms.DataGridViewTextBoxColumn grName;
        private System.Windows.Forms.DataGridViewTextBoxColumn grType;
        private System.Windows.Forms.DataGridViewTextBoxColumn grValue;
        private System.Windows.Forms.Timer tmrRefresh;
    }
}

