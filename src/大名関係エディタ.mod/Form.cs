using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace 将星録;

public class 大名関係エディタ : Form
{
    DataGridView dgv = new DataGridView();
    大名関係情報型 大名関係情報 = new();
    int 主格大名配列IX = 0;

    List<大名情報型> 大名配列 = new();
    List<武将情報型> 武将配列 = new();

    public 大名関係エディタ(int 主格大名配列IX)
    {
        this.主格大名配列IX = 主格大名配列IX;

        try
        {
            create大名関係配列();

            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void create大名関係配列()
    {
        for (int i = 0; i < 将星録.最大数.大名情報.配列数; i++)
        {
            大名配列.Add(new 大名情報型(i));
        }

        for (int i = 0; i < 将星録.最大数.武将情報.配列数; i++)
        {
            武将配列.Add(new 武将情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "大名関係エディタ";
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

    enum タイトル { 配列IX = 0, 大名姓名, 友好, 同盟残, 婚姻 };
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

            int 客体大名配列IX = ID;
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];

            if (e.ColumnIndex == (int)タイトル.友好)
            {
                try
                {
                    大名関係情報.友好[主格大名配列IX, 客体大名配列IX] = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名関係情報.友好[主格大名配列IX, 客体大名配列IX];
                }
            }
            else if (e.ColumnIndex == (int)タイトル.同盟残)
            {
                try
                {
                    大名関係情報.同盟残[主格大名配列IX, 客体大名配列IX] = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名関係情報.同盟残[主格大名配列IX, 客体大名配列IX];
                }
            }
            else if (e.ColumnIndex == (int)タイトル.婚姻)
            {
                try
                {
                    大名関係情報.婚姻[主格大名配列IX, 客体大名配列IX] = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 大名関係情報.婚姻[主格大名配列IX, 客体大名配列IX];
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

            dgv.Columns[(int)タイトル.大名姓名].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.大名姓名].ReadOnly = true;
            dgv.Columns[(int)タイトル.大名姓名].DefaultCellStyle.BackColor = Color.Yellow;

            dgv.Columns[(int)タイトル.友好].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.同盟残].ValueType = typeof(int);
            dgv.Columns[(int)タイトル.婚姻].ValueType = typeof(int);

            for (int i = 0; i < 最大数.大名情報.配列数; i++)
            {
                int iBushouID = 大名配列[i].大名武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 武将配列.Count)
                {
                    strBushouName = 武将配列[iBushouID].姓名;
                }

                dgv.Rows.Add(
                  i,
                  strBushouName,
                  大名関係情報.友好[主格大名配列IX, i],
                  大名関係情報.同盟残[主格大名配列IX, i],
                  大名関係情報.婚姻[主格大名配列IX, i]
                  );
            }

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }
}