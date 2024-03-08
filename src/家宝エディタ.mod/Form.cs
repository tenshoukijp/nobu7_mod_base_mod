using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public class 家宝エディタ : Form
{
    DataGridView dgv = new DataGridView();

    List<家宝情報型> 家宝配列 = new();

    public 家宝エディタ()
    {
        try
        {
            create家宝配列();

            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void create家宝配列()
    {
        for (int i = 0; i < 将星録.最大数.家宝情報.配列数; i++)
        {
            家宝配列.Add(new 家宝情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "家宝エディタ";
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
            DgvDataImport();
        }
    }

    enum タイトル { 配列IX = 0, 家宝名, 種類, 画像, 等級, 能力上昇, 政治, 戦闘, 智謀, 南蛮, 抑制, 兵科効果, 所有武将配列IX };
    void setDataGridAttribute()
    {
        try
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
        catch (Exception) { }
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

            var 家宝情報 = new 将星録.家宝情報型(ID);
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];
            if (e.ColumnIndex == (int)タイトル.家宝名)
            {
                try
                {
                    家宝情報.家宝名 = cell.Value.ToString();
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.家宝名;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.種類)
            {
                try
                {
                    System.Diagnostics.Trace.WriteLine(cell.Value.GetType());
                    家宝情報.種類 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.種類;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.画像)
            {
                try
                {
                    家宝情報.画像 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.画像;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.等級)
            {
                try
                {
                    家宝情報.等級 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.等級;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.能力上昇)
            {
                try
                {
                    家宝情報.能力上昇 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.能力上昇;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.政治)
            {
                try
                {
                    家宝情報.政治 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.政治;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦闘)
            {
                try
                {
                    家宝情報.戦闘 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.戦闘;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.智謀)
            {
                try
                {
                    家宝情報.智謀 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.智謀;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.南蛮)
            {
                try
                {
                    家宝情報.南蛮 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.南蛮;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.抑制)
            {
                try
                {
                    家宝情報.抑制 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.抑制;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.兵科効果)
            {
                try
                {
                    家宝情報.兵科効果 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.兵科効果;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.所有武将配列IX)
            {
                try
                {
                    家宝情報.所有武将配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 家宝情報.所有武将配列IX;
                }
            }
        }
        catch (Exception) { }
    }

    void DgvDataImport()
    {
        try
        {
            dgv.Columns[(int)タイトル.配列IX].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
            dgv.Columns[(int)タイトル.配列IX].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[(int)タイトル.家宝名].ValueType = typeof(string);

            string[] names = Enum.GetNames(typeof(タイトル));
            for (int i = (int)タイトル.種類; i < names.Length; i++)
            {
                dgv.Columns[i].ValueType = typeof(int);
            }

            // 横列単位で足してゆく、
            foreach (var 家宝 in 家宝配列)
            {
                dgv.Rows.Add(
                  家宝.配列IX,
                  家宝.家宝名,
                  家宝.種類,
                  家宝.画像,
                  家宝.等級,
                  家宝.能力上昇,
                  家宝.政治,
                  家宝.戦闘,
                  家宝.智謀,
                  家宝.南蛮,
                  家宝.抑制,
                  家宝.兵科効果,
                  家宝.所有武将配列IX
                  );
            }

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }
}