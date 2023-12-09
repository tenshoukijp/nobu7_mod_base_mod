using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public class 官位エディタ : Form
{
    DataGridView dgv = new DataGridView();

    List<官位情報型> 官位配列 = new();

    public 官位エディタ()
    {
        create官位配列();

        setFormAttribute();
        setDataGridAttribute();
    }

    private void create官位配列()
    {
        for (int i = 0; i < 将星録.最大数.官位情報.配列数; i++)
        {
            官位配列.Add(new 官位情報型(i));
        }
    }

    private void setFormAttribute()
    {
        this.Text = "官位エディタ";
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;
    }

    enum タイトル { 配列IX = 0, 官位名, 階位, 所有武将配列IX };
    private void setDataGridAttribute()
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
    private void dvg_DataError(object sender, DataGridViewDataErrorEventArgs e)
    {
        e.Cancel = false;
    }

    private void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        int iKanniID = e.RowIndex;
        var 官位情報 = new 将星録.官位情報型(iKanniID);
        // 対象のセル
        var cell = dgv[e.ColumnIndex, e.RowIndex];
        if (e.ColumnIndex == (int)タイトル.官位名)
        {
            try
            {
                官位情報.官位名 = cell.Value.ToString();
            }
            catch (Exception)
            {
                cell.Value = 官位情報.官位名;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.階位)
        {
            try
            {
                System.Diagnostics.Trace.WriteLine(cell.Value.GetType());
                官位情報.階位 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 官位情報.階位;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.所有武将配列IX)
        {
            try
            {
                官位情報.所有武将配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = 官位情報.所有武将配列IX;
            }
        }

    }

    void DgvDataImport()
    {
        // 横列単位で足してゆく、
        foreach (var 官位 in 官位配列)
        {
            dgv.Rows.Add(
                官位.配列IX,
                官位.官位名,
                官位.階位,
                官位.所有武将配列IX
                );
        }

        dgv.Columns[(int)タイトル.配列IX].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
        dgv.Columns[(int)タイトル.配列IX].DefaultCellStyle.BackColor = Color.Gray;
        dgv.Columns[(int)タイトル.官位名].ValueType = typeof(string);
        dgv.Columns[(int)タイトル.階位].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.階位].ReadOnly = true;
        dgv.Columns[(int)タイトル.階位].DefaultCellStyle.BackColor = Color.Gray;
        dgv.Columns[(int)タイトル.所有武将配列IX].ValueType = typeof(int);


        dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
    }
}