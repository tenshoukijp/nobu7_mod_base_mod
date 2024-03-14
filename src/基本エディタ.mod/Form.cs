using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;


public abstract class 基本エディタ : Form
{
    protected DataGridView dgv = new DataGridView();

    public 基本エディタ()
    {
        try
        {
            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void setFormAttribute()
    {
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;

        this.KeyPreview = true;
        this.KeyDown += Form_KeyDown;
    }

    void Form_KeyDown(object sender, KeyEventArgs e)
    {
        if (e.KeyCode == Keys.F5 && ActiveForm == this)
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
        catch (Exception) { }
    }

    protected virtual void dvg_DataBinding()
    {

    }
}