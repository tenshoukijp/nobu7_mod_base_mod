using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public class 役職エディタ : Form
{
    DataGridView dgv = new DataGridView();

    List<役職情報型> 役職配列 = new();

    public 役職エディタ()
    {
        try { 
        create役職配列();

        setFormAttribute();
        setDataGridAttribute();
            }
        catch (Exception ) { }
    }

    void create役職配列()
    {
        for (int i = 0; i < 将星録.最大数.役職情報.配列数; i++)
        {
            役職配列.Add(new 役職情報型(i));
        }
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
        if (e.KeyCode == Keys.F5)
        {
            dgv.Rows.Clear();
            DgvDataImport();
        }
    }

    enum タイトル { 配列IX = 0, 役職名, 役位, 所有大名配列IX };
    void setDataGridAttribute()
    {
        try { 
        dgv.Dock = DockStyle.Fill;
        dgv.AllowUserToAddRows = false;
        dgv.AllowUserToDeleteRows = false;

        string fontName = 将星録.アプリケーション.フォント.フォント名;
        dgv.DefaultCellStyle.Font = new System.Drawing.Font(fontName, 16, FontStyle.Regular, GraphicsUnit.Pixel);

        string[] names = Enum.GetNames(typeof(タイトル));
        for (int i = 0; i < names.Length; i++)
        {
            // 縦列のオブジェクトを作り
            DataGridViewTextBoxColumn dgvtbc = new DataGridViewTextBoxColumn();
            // タイトル文字列を設定
            dgvtbc.HeaderText = names[i];
            // グリッドビューに縦列として追加。
            dgv.Columns.Add(dgvtbc);
        }

        DgvDataImport();

        // データグリッドのセルを編集した時のイベントハンドラを登録する。
        dgv.DataError += dvg_DataError;
        dgv.CellValueChanged += dgv_CellValueChanged;

        // データグリッドビューをフォームに乗っける
        this.Controls.Add(dgv);

        }
        catch (Exception ) { }
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

    void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            var IDCell = dgv[0, e.RowIndex];
            int ID = (int)IDCell.Value;

            var 役職情報 = new 将星録.役職情報型(ID);
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];
            if (e.ColumnIndex == (int)タイトル.役職名)
            {
                try
                {
                    役職情報.役職名 = cell.Value.ToString();
                }
                catch (Exception)
                {
                    cell.Value = 役職情報.役職名;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.役位)
            {
                try
                {
                    役職情報.役位 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 役職情報.役位;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.所有大名配列IX)
            {
                try
                {
                    役職情報.所有大名配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 役職情報.所有大名配列IX;
                }
            }
        }
        catch (Exception ) { }
    }

    void DgvDataImport()
    {
        try
        {
            dgv.Columns[(int)タイトル.配列IX].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
            dgv.Columns[(int)タイトル.配列IX].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[(int)タイトル.役職名].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.役位].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.役位].ReadOnly = true;
            dgv.Columns[(int)タイトル.役位].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[(int)タイトル.所有大名配列IX].ValueType = typeof(int);

            // 横列単位で足してゆく、
            foreach (var 役職 in 役職配列)
            {
                dgv.Rows.Add(
                  役職.配列IX,
                  役職.役職名,
                  役職.役位,
                  役職.所有大名配列IX
                  );
            }


            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception ) { }
    }
}