namespace KController
{
    partial class KController
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(KController));
            this.lblName = new System.Windows.Forms.Label();
            this.txtBoxName = new System.Windows.Forms.TextBox();
            this.lblTCP = new System.Windows.Forms.Label();
            this.lblUDP = new System.Windows.Forms.Label();
            this.btnApply = new System.Windows.Forms.Button();
            this.picState = new System.Windows.Forms.PictureBox();
            this.txtBoxTCP = new System.Windows.Forms.NumericUpDown();
            this.txtBoxUDP = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.picState)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtBoxTCP)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtBoxUDP)).BeginInit();
            this.SuspendLayout();
            // 
            // lblName
            // 
            this.lblName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblName.AutoSize = true;
            this.lblName.Location = new System.Drawing.Point(15, 13);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(86, 13);
            this.lblName.TabIndex = 0;
            this.lblName.Text = "Controller name :";
            // 
            // txtBoxName
            // 
            this.txtBoxName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtBoxName.Location = new System.Drawing.Point(12, 32);
            this.txtBoxName.MaxLength = 250;
            this.txtBoxName.Name = "txtBoxName";
            this.txtBoxName.Size = new System.Drawing.Size(162, 20);
            this.txtBoxName.TabIndex = 1;
            // 
            // lblTCP
            // 
            this.lblTCP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblTCP.AutoSize = true;
            this.lblTCP.Location = new System.Drawing.Point(14, 58);
            this.lblTCP.Name = "lblTCP";
            this.lblTCP.Size = new System.Drawing.Size(56, 13);
            this.lblTCP.TabIndex = 2;
            this.lblTCP.Text = "TCP Port :";
            // 
            // lblUDP
            // 
            this.lblUDP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblUDP.AutoSize = true;
            this.lblUDP.Location = new System.Drawing.Point(15, 105);
            this.lblUDP.Name = "lblUDP";
            this.lblUDP.Size = new System.Drawing.Size(58, 13);
            this.lblUDP.TabIndex = 4;
            this.lblUDP.Text = "UDP Port :";
            // 
            // btnApply
            // 
            this.btnApply.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.btnApply.Location = new System.Drawing.Point(55, 153);
            this.btnApply.Name = "btnApply";
            this.btnApply.Size = new System.Drawing.Size(75, 23);
            this.btnApply.TabIndex = 6;
            this.btnApply.Text = "Apply";
            this.btnApply.UseVisualStyleBackColor = true;
            this.btnApply.Click += new System.EventHandler(this.btnApply_Click);
            // 
            // picState
            // 
            this.picState.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.picState.ErrorImage = global::KController.Properties.Resources.state_red;
            this.picState.Image = global::KController.Properties.Resources.state_red;
            this.picState.InitialImage = global::KController.Properties.Resources.state_red;
            this.picState.Location = new System.Drawing.Point(53, 188);
            this.picState.Name = "picState";
            this.picState.Size = new System.Drawing.Size(79, 42);
            this.picState.TabIndex = 7;
            this.picState.TabStop = false;
            // 
            // txtBoxTCP
            // 
            this.txtBoxTCP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtBoxTCP.Location = new System.Drawing.Point(12, 78);
            this.txtBoxTCP.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.txtBoxTCP.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.txtBoxTCP.Name = "txtBoxTCP";
            this.txtBoxTCP.Size = new System.Drawing.Size(162, 20);
            this.txtBoxTCP.TabIndex = 8;
            this.txtBoxTCP.Value = new decimal(new int[] {
            47371,
            0,
            0,
            0});
            // 
            // txtBoxUDP
            // 
            this.txtBoxUDP.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtBoxUDP.Location = new System.Drawing.Point(12, 125);
            this.txtBoxUDP.Maximum = new decimal(new int[] {
            65535,
            0,
            0,
            0});
            this.txtBoxUDP.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.txtBoxUDP.Name = "txtBoxUDP";
            this.txtBoxUDP.Size = new System.Drawing.Size(162, 20);
            this.txtBoxUDP.TabIndex = 9;
            this.txtBoxUDP.Value = new decimal(new int[] {
            47371,
            0,
            0,
            0});
            // 
            // KController
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(186, 240);
            this.Controls.Add(this.txtBoxUDP);
            this.Controls.Add(this.txtBoxTCP);
            this.Controls.Add(this.picState);
            this.Controls.Add(this.btnApply);
            this.Controls.Add(this.lblUDP);
            this.Controls.Add(this.lblTCP);
            this.Controls.Add(this.txtBoxName);
            this.Controls.Add(this.lblName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(202, 278);
            this.MinimumSize = new System.Drawing.Size(202, 278);
            this.Name = "KController";
            this.Text = "KController";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.KController_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.picState)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtBoxTCP)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.txtBoxUDP)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.TextBox txtBoxName;
        private System.Windows.Forms.Label lblTCP;
        private System.Windows.Forms.Label lblUDP;
        private System.Windows.Forms.Button btnApply;
        private System.Windows.Forms.PictureBox picState;
        private System.Windows.Forms.NumericUpDown txtBoxTCP;
        private System.Windows.Forms.NumericUpDown txtBoxUDP;
    }
}

