using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public class 年月相場エディタ : Form
{
    DataGridView dgv = new DataGridView();

    年月情報型 年月情報 = new();
    相場情報型 相場情報 = new();

    public 年月相場エディタ()
    {
        setFormAttribute();

        setDataGridAttribute();
    }

    void setFormAttribute()
    {
        this.Text = "年月相場エディタ";
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

    enum タイトル { 年, 月, 兵糧, 軍馬, 鉄砲 };
    void setDataGridAttribute()
    {
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

    // 誤った型データを入れた場合は、元の値へと戻すようにする。
    void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        e.Cancel = false;
    }

    void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        // 対象のセル
        var cell = dgv[e.ColumnIndex, e.RowIndex];
        if (e.ColumnIndex == (int)タイトル.年)
        {
            try
            {
                年月情報.年 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 年月情報.年;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.月)
        {
            try
            {
                年月情報.月 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 年月情報.月;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.兵糧)
        {
            try
            {
                相場情報.兵糧 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 相場情報.兵糧;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.軍馬)
        {
            try
            {
                相場情報.軍馬 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 相場情報.軍馬;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.鉄砲)
        {
            try
            {
                相場情報.鉄砲 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 相場情報.鉄砲;
            }
        }
    }

    void DgvDataImport()
    {
        dgv.Rows.Add(年月情報.年, 年月情報.月, 相場情報.兵糧, 相場情報.軍馬, 相場情報.鉄砲);

        dgv.Columns[(int)タイトル.年].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.月].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.兵糧].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.軍馬].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.鉄砲].ValueType = typeof(int);

        dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
    }
}