using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;


public partial class 役職エディタ : Form
{
    class BIND用の役職情報型
    {
        役職情報型 役職情報;
        public BIND用の役職情報型(int 役職配列IX)
        {
            役職情報 = new 役職情報型(役職配列IX);
        }

        public int 配列IX
        {
            get { return 役職情報.配列IX; }
        }
        public string 役職名
        {
            get { return 役職情報.役職名; }
            set { 役職情報.役職名 = value; }
        }
        public int 役位
        {
            get { return 役職情報.役位; }
        }
        public int 所有大名配列IX
        {
            get { return 役職情報.所有大名配列IX; }
            set { 役職情報.所有大名配列IX = value; }
        }
    }
}

public partial class 役職エディタ : Form
{
    DataGridView dgv = new DataGridView();

    public 役職エディタ()
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
        this.Text = "役職エディタ";
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

            dvg_DataBinding();

            // データグリッドビューをフォームに乗っける
            this.Controls.Add(dgv);

        }
        catch (Exception) { }
    }

    private void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns["配列IX"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["役位"].DefaultCellStyle.BackColor = Color.LightGray;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        } catch (Exception) { }
    }

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        try
        {
            e.Cancel = false;
        }
        catch (Exception) { }
    }

    void dvg_DataBinding()
    {
        try
        {
            List<BIND用の役職情報型> データ配列 = new();
            for(int i=0; i< 将星録.最大数.役職情報.配列数; i++)
            {
                データ配列.Add(new BIND用の役職情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
}