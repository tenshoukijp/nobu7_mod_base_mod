using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace 将星録;



public abstract partial class 基本エディタ : Form
{
    protected DataGridView dgv = new DataGridView();

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


    bool IsUpdateKeyDown(KeyEventArgs e)
    {
        return e.KeyCode == Keys.F5 && ActiveForm == this;
    }

    void Form_KeyDown(object sender, KeyEventArgs e)
    {
        if (IsUpdateKeyDown(e))
        {
            dgv.Rows.Clear();
            dvg_DataBinding();
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
            dgv.DataError += dvg_DataErrorStatusBar;
            dgv.DataBindingComplete += dvg_DataBindingComplete;
            dgv.CellValueChanged += dgv_CellValueChanged;
            dgv.CellValueChanged += dgv_CellValueChangedStatusBar;

            dvg_DataBinding();

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);

        }
        catch (Exception) { }
    }


    protected virtual void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
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
        }
        catch (Exception) {
        }
    }

    protected virtual void dvg_DataBinding()
    {

    }
}


public abstract partial class 基本エディタ : Form
{
    // ステータスバー
    protected StatusStrip statusStrip = new StatusStrip();
    protected ToolStripStatusLabel toolStrip = new ToolStripStatusLabel("");

    // セルの変更時のエラーを表示・非表示を制御するための変数
    private int lastCellChangeErrorStatus = 0;

    void setStatusBarText(string text)
    {
        try
        {
            text = text.Replace("\r\n", " ");
            text = text.Replace("\n", " ");
            text = text.Replace("\r", " ");
            toolStrip.Text = text;
        }
        catch (Exception) { }
    }
    void setStatusBarAttribute()
    {
        this.KeyDown += Form_KeyDownStatusBar;

        statusStrip.Dock = DockStyle.Bottom;
        statusStrip.Items.Add(toolStrip);
        this.Controls.Add(statusStrip);
    }

    void Form_KeyDownStatusBar(object sender, KeyEventArgs e)
    {
        if (IsUpdateKeyDown(e))
        {
            setStatusBarText("");
        }
    }
    void dgv_CellValueChangedStatusBar(object sender, DataGridViewCellEventArgs e)
    {
        lastCellChangeErrorStatus--;
        if (lastCellChangeErrorStatus < 0)
        {
            setStatusBarText("");
        }
    }

    void dvg_DataErrorStatusBar(object sender, DataGridViewDataErrorEventArgs e)
    {
        try
        {
            lastCellChangeErrorStatus = 1;
            setStatusBarText(e.Exception.Message);
            System.Diagnostics.Trace.Write(e.Exception.Message);
        }
        catch (Exception) { }
    }


}
