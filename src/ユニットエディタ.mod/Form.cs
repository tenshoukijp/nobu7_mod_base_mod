using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public class ユニットエディタ : Form
{
    DataGridView dgv = new DataGridView();

    List<ユニット情報型> ユニット配列 = new();


    public ユニットエディタ()
    {
        createユニット配列();

        setFormAttribute();
        setDataGridAttribute();

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

    void createユニット配列()
    {
        for (int i = 0; i < 将星録.最大数.ユニット情報.配列数; i++)
        {
            ユニット配列.Add(new ユニット情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "ユニットエディタ";
        this.Width = 900;
        this.Height = 800;
        this.StartPosition = FormStartPosition.CenterScreen;
        this.ShowIcon = false;

        this.KeyDown += new KeyEventHandler(Form_KeyDown);
    }

    enum タイトル { 配列IX = 0, ユニット名, ユニット称, 籠ユニット番号, 所属大名配列IX, ユニット主武将配列IX, 規模, 防御, 防御MAX, 兵数, 負傷兵数, 金銭, 兵糧, 軍馬, 鉄砲, 大砲, 商人, 委任状態, 委任攻撃, 委任攻撃目標ユニット配列IX, 開始ユニット配列IX, 後ユニット配列IX };
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
        int iCastleID = e.RowIndex;
        var ユニット情報 = new 将星録.ユニット情報型(iCastleID);
        // 対象のセル
        var cell = dgv[e.ColumnIndex, e.RowIndex];
        if (e.ColumnIndex == (int)タイトル.ユニット名)
        {
            try
            {
                ユニット情報.ユニット名 = cell.Value.ToString();
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.ユニット名;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.籠ユニット番号)
        {
            try
            {
                ユニット情報.籠ユニット番号 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.籠ユニット番号;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.所属大名配列IX)
        {
            try
            {
                ユニット情報.所属大名配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.所属大名配列IX;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.ユニット主武将配列IX)
        {
            try
            {
                ユニット情報.ユニット主武将配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.ユニット主武将配列IX;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.規模)
        {
            try
            {
                ユニット情報.規模 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.規模;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.防御)
        {
            try
            {
                ユニット情報.防御 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.防御;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.兵数)
        {
            try
            {
                ユニット情報.兵数 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.兵数;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.負傷兵数)
        {
            try
            {
                ユニット情報.負傷兵数 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.負傷兵数;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.金銭)
        {
            try
            {
                ユニット情報.金銭 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.金銭;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.兵糧)
        {
            try
            {
                ユニット情報.兵糧 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.兵糧;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.軍馬)
        {
            try
            {
                ユニット情報.軍馬 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.軍馬;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.鉄砲)
        {
            try
            {
                ユニット情報.鉄砲 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.鉄砲;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.大砲)
        {
            try
            {
                ユニット情報.大砲 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.大砲;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.商人)
        {
            try
            {
                ユニット情報.商人 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.商人;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.委任状態)
        {
            try
            {
                ユニット情報.委任状態 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.委任状態;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.委任攻撃)
        {
            try
            {
                ユニット情報.委任攻撃 = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.委任攻撃;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.委任攻撃目標ユニット配列IX)
        {
            try
            {
                ユニット情報.委任攻撃目標ユニット配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.委任攻撃目標ユニット配列IX;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.開始ユニット配列IX)
        {
            try
            {
                ユニット情報.開始ユニット配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.開始ユニット配列IX;
            }
        }
        else if (e.ColumnIndex == (int)タイトル.後ユニット配列IX)
        {
            try
            {
                ユニット情報.後ユニット配列IX = (int)cell.Value;
            }
            catch (Exception)
            {
                cell.Value = ユニット情報.後ユニット配列IX;
            }
        }

    }

    void DgvDataImport()
    {
        // 横列単位で足してゆく、
        foreach (var ユニット in ユニット配列)
        {
            dgv.Rows.Add(
              ユニット.配列IX,
              ユニット.ユニット名,
              ユニット.ユニット称,
              ユニット.籠ユニット番号,
              ユニット.所属大名配列IX,
              ユニット.ユニット主武将配列IX,
              ユニット.規模,
              ユニット.防御,
              ユニット.防御MAX,
              ユニット.兵数,
              ユニット.負傷兵数,
              ユニット.金銭,
              ユニット.兵糧,
              ユニット.軍馬,
              ユニット.鉄砲,
              ユニット.大砲,
              ユニット.商人,
              ユニット.委任状態,
              ユニット.委任攻撃,
              ユニット.委任攻撃目標ユニット配列IX,
              ユニット.開始ユニット配列IX,
              ユニット.後ユニット配列IX
              );
        }

        dgv.Columns[(int)タイトル.配列IX].ValueType = typeof(int);
        dgv.Columns[(int)タイトル.配列IX].ReadOnly = true;
        dgv.Columns[(int)タイトル.配列IX].DefaultCellStyle.BackColor = Color.LightGray;
        dgv.Columns[(int)タイトル.ユニット名].ValueType = typeof(string);

        dgv.Columns[(int)タイトル.ユニット称].ValueType = typeof(string);
        dgv.Columns[(int)タイトル.ユニット称].ReadOnly = true;
        dgv.Columns[(int)タイトル.ユニット称].DefaultCellStyle.BackColor = Color.LightGray;

        dgv.Columns[(int)タイトル.所属大名配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
        dgv.Columns[(int)タイトル.ユニット主武将配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
        dgv.Columns[(int)タイトル.開始ユニット配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
        dgv.Columns[(int)タイトル.後ユニット配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;


        // 基本的にはint型
        string[] names = Enum.GetNames(typeof(タイトル));
        for (int i = (int)タイトル.籠ユニット番号; i < names.Length; i++)
        {
            dgv.Columns[i].ValueType = typeof(int);
        }

        dgv.Columns[(int)タイトル.防御MAX].DefaultCellStyle.BackColor = Color.LightGray;
        dgv.Columns[(int)タイトル.防御MAX].ReadOnly = true;

        dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;

    }
}