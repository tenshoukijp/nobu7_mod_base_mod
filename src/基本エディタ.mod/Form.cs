using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace 将星録;


public abstract class 基本エディタ : Form
{
    protected DataGridView dgv = new DataGridView();
    protected StatusStrip statusStrip = new StatusStrip();
    protected ToolStripStatusLabel toolStrip = new ToolStripStatusLabel("");
    private int isLastCellChangeError = 0;

    public 基本エディタ()
    {
        try
        {
            setFormAttribute();
            setStatusBarAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void setFormAttribute()
    {
        this.TopMost = true;
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;

        this.KeyPreview = true;
        this.KeyDown += Form_KeyDown;
    }

    void setStatusBarAttribute()
    {
        statusStrip.Dock = DockStyle.Bottom;
        statusStrip.Items.Add(toolStrip);
        this.Controls.Add(statusStrip);
    }

    void setStatusBarText(string text)
    {
        try
        {
            text = text.Replace("\n", " ");
            toolStrip.Text = text;
        }
        catch (Exception) { }
    }

    void Form_KeyDown(object sender, KeyEventArgs e)
    {
        if (e.KeyCode == Keys.F5 && ActiveForm == this)
        {
            dgv.Rows.Clear();
            dvg_DataBinding();
            setStatusBarText("");
        }
    }

    void setDataGridAttribute()
    {
        try
        {
            dgv.Dock = DockStyle.Fill;
            dgv.AllowUserToAddRows = false;
            dgv.AllowUserToDeleteRows = false;

            string fontName = 将星録.アプリケーション.フォント.フォント名;
            dgv.DefaultCellStyle.Font = new System.Drawing.Font(fontName, 16, FontStyle.Regular, GraphicsUnit.Pixel);

            // データグリッドのセルを編集した時のイベントハンドラを登録する。
            dgv.DataError += dvg_DataError;
            dgv.DataBindingComplete += dvg_DataBindingComplete;
            dgv.CellValueChanged += dgv_CellValueChanged;

            dvg_DataBinding();

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);

        }
        catch (Exception) { }
    }


    protected virtual void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        isLastCellChangeError--;
        if (isLastCellChangeError < 0)
        {
            setStatusBarText("");
        }
    }

    protected virtual void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        
    }

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    protected virtual void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        try
        {
            e.Cancel = false;
            isLastCellChangeError = 1;
            setStatusBarText(e.Exception.Message);
            System.Diagnostics.Trace.Write(e.Exception.Message);
        }
        catch (Exception) {
        }
    }

    protected virtual void dvg_DataBinding()
    {

    }
}