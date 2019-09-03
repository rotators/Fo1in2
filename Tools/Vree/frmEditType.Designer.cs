namespace Vree
{
    partial class frmEditType
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
            this.btnBool = new System.Windows.Forms.Button();
            this.btnInt32 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.btnInt64 = new System.Windows.Forms.Button();
            this.btnFloat = new System.Windows.Forms.Button();
            this.btnUint32 = new System.Windows.Forms.Button();
            this.btnUint64 = new System.Windows.Forms.Button();
            this.btnCharp = new System.Windows.Forms.Button();
            this.btnUint16 = new System.Windows.Forms.Button();
            this.btnInt16 = new System.Windows.Forms.Button();
            this.btnUint8 = new System.Windows.Forms.Button();
            this.btnInt8 = new System.Windows.Forms.Button();
            this.chkArray = new System.Windows.Forms.CheckBox();
            this.chkPointer = new System.Windows.Forms.CheckBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnBool
            // 
            this.btnBool.Location = new System.Drawing.Point(12, 12);
            this.btnBool.Name = "btnBool";
            this.btnBool.Size = new System.Drawing.Size(45, 31);
            this.btnBool.TabIndex = 0;
            this.btnBool.Text = "Bool";
            this.btnBool.UseVisualStyleBackColor = true;
            this.btnBool.Click += new System.EventHandler(this.BtnBool_Click);
            // 
            // btnInt32
            // 
            this.btnInt32.Location = new System.Drawing.Point(175, 12);
            this.btnInt32.Name = "btnInt32";
            this.btnInt32.Size = new System.Drawing.Size(49, 31);
            this.btnInt32.TabIndex = 2;
            this.btnInt32.Text = "Int32";
            this.btnInt32.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(226, 115);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(179, 22);
            this.button4.TabIndex = 3;
            this.button4.Text = "Set custom type";
            this.button4.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 118);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Custom type:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(80, 115);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(144, 20);
            this.textBox1.TabIndex = 5;
            // 
            // btnInt64
            // 
            this.btnInt64.Location = new System.Drawing.Point(226, 12);
            this.btnInt64.Name = "btnInt64";
            this.btnInt64.Size = new System.Drawing.Size(49, 31);
            this.btnInt64.TabIndex = 6;
            this.btnInt64.Text = "Int64";
            this.btnInt64.UseVisualStyleBackColor = true;
            // 
            // btnFloat
            // 
            this.btnFloat.Location = new System.Drawing.Point(12, 49);
            this.btnFloat.Name = "btnFloat";
            this.btnFloat.Size = new System.Drawing.Size(45, 31);
            this.btnFloat.TabIndex = 7;
            this.btnFloat.Text = "Float";
            this.btnFloat.UseVisualStyleBackColor = true;
            // 
            // btnUint32
            // 
            this.btnUint32.Location = new System.Drawing.Point(175, 49);
            this.btnUint32.Name = "btnUint32";
            this.btnUint32.Size = new System.Drawing.Size(49, 31);
            this.btnUint32.TabIndex = 9;
            this.btnUint32.Text = "Uint32";
            this.btnUint32.UseVisualStyleBackColor = true;
            this.btnUint32.Click += new System.EventHandler(this.BtnUint32_Click);
            // 
            // btnUint64
            // 
            this.btnUint64.Location = new System.Drawing.Point(226, 49);
            this.btnUint64.Name = "btnUint64";
            this.btnUint64.Size = new System.Drawing.Size(49, 31);
            this.btnUint64.TabIndex = 10;
            this.btnUint64.Text = "Uint64";
            this.btnUint64.UseVisualStyleBackColor = true;
            // 
            // btnCharp
            // 
            this.btnCharp.Location = new System.Drawing.Point(281, 12);
            this.btnCharp.Name = "btnCharp";
            this.btnCharp.Size = new System.Drawing.Size(49, 31);
            this.btnCharp.TabIndex = 11;
            this.btnCharp.Text = "char*";
            this.btnCharp.UseVisualStyleBackColor = true;
            this.btnCharp.Click += new System.EventHandler(this.BtnCharp_Click);
            // 
            // btnUint16
            // 
            this.btnUint16.Location = new System.Drawing.Point(117, 49);
            this.btnUint16.Name = "btnUint16";
            this.btnUint16.Size = new System.Drawing.Size(49, 31);
            this.btnUint16.TabIndex = 13;
            this.btnUint16.Text = "Uint16";
            this.btnUint16.UseVisualStyleBackColor = true;
            // 
            // btnInt16
            // 
            this.btnInt16.Location = new System.Drawing.Point(117, 12);
            this.btnInt16.Name = "btnInt16";
            this.btnInt16.Size = new System.Drawing.Size(49, 31);
            this.btnInt16.TabIndex = 12;
            this.btnInt16.Text = "Int16";
            this.btnInt16.UseVisualStyleBackColor = true;
            // 
            // btnUint8
            // 
            this.btnUint8.Location = new System.Drawing.Point(63, 12);
            this.btnUint8.Name = "btnUint8";
            this.btnUint8.Size = new System.Drawing.Size(49, 31);
            this.btnUint8.TabIndex = 14;
            this.btnUint8.Text = "Uint8";
            this.btnUint8.UseVisualStyleBackColor = true;
            // 
            // btnInt8
            // 
            this.btnInt8.Location = new System.Drawing.Point(63, 49);
            this.btnInt8.Name = "btnInt8";
            this.btnInt8.Size = new System.Drawing.Size(49, 31);
            this.btnInt8.TabIndex = 15;
            this.btnInt8.Text = "Int8";
            this.btnInt8.UseVisualStyleBackColor = true;
            // 
            // chkArray
            // 
            this.chkArray.AutoSize = true;
            this.chkArray.Location = new System.Drawing.Point(12, 90);
            this.chkArray.Name = "chkArray";
            this.chkArray.Size = new System.Drawing.Size(50, 17);
            this.chkArray.TabIndex = 16;
            this.chkArray.Text = "Array";
            this.chkArray.UseVisualStyleBackColor = true;
            // 
            // chkPointer
            // 
            this.chkPointer.AutoSize = true;
            this.chkPointer.Location = new System.Drawing.Point(175, 90);
            this.chkPointer.Name = "chkPointer";
            this.chkPointer.Size = new System.Drawing.Size(59, 17);
            this.chkPointer.TabIndex = 17;
            this.chkPointer.Text = "Pointer";
            this.chkPointer.UseVisualStyleBackColor = true;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(63, 90);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(84, 20);
            this.textBox2.TabIndex = 18;
            // 
            // frmEditType
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(417, 147);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.chkPointer);
            this.Controls.Add(this.chkArray);
            this.Controls.Add(this.btnInt8);
            this.Controls.Add(this.btnUint8);
            this.Controls.Add(this.btnUint16);
            this.Controls.Add(this.btnInt16);
            this.Controls.Add(this.btnCharp);
            this.Controls.Add(this.btnUint64);
            this.Controls.Add(this.btnUint32);
            this.Controls.Add(this.btnFloat);
            this.Controls.Add(this.btnInt64);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.btnInt32);
            this.Controls.Add(this.btnBool);
            this.Name = "frmEditType";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Change type";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnBool;
        private System.Windows.Forms.Button btnInt32;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button btnInt64;
        private System.Windows.Forms.Button btnFloat;
        private System.Windows.Forms.Button btnUint32;
        private System.Windows.Forms.Button btnUint64;
        private System.Windows.Forms.Button btnCharp;
        private System.Windows.Forms.Button btnUint16;
        private System.Windows.Forms.Button btnInt16;
        private System.Windows.Forms.Button btnUint8;
        private System.Windows.Forms.Button btnInt8;
        private System.Windows.Forms.CheckBox chkArray;
        private System.Windows.Forms.CheckBox chkPointer;
        private System.Windows.Forms.TextBox textBox2;
    }
}