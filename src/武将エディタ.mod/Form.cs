using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;

public class 武将エディタ : Form
{
    DataGridView dgv = new DataGridView();

    List<武将情報型> 武将配列 = new();

    public 武将エディタ()
    {
        try
        {
            create武将配列();

            setFormAttribute();
            setDataGridAttribute();
        }
        catch (Exception) { }
    }

    void create武将配列()
    {
        for (int i = 0; i < 将星録.最大数.武将情報.総配列数; i++)
        {
            武将配列.Add(new 武将情報型(i));
        }
    }

    void setFormAttribute()
    {
        this.Text = "武将エディタ";
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

    enum タイトル { 配列IX = 0, 苗字, 名前, 居城配列IX, 性別, 顔番号, 一門, 親武将番号, 状態, 身分, 生年, 元服年, 仕官, 寿命, 義理, 相性, 口調, 勲功, 忠誠, 政治, 戦闘, 智謀, 足軽適性, 騎馬適性, 鉄砲適性, 水軍適性, 内技農業, 内技商業, 内技建設, 内技外交, 内技登用, 戦技抜穴, 戦技騎突, 戦技三段, 戦技焙烙, 戦技騎鉄, 農業経験値, 商業経験値, 建設経験値 };
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

            var 武将情報 = new 将星録.武将情報型(ID);
            // 対象のセル
            var cell = dgv[e.ColumnIndex, e.RowIndex];
            // 対象のセル
            if (e.ColumnIndex == (int)タイトル.苗字)
            {
                try
                {
                    武将情報.苗字 = cell.Value.ToString();
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.苗字;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.名前)
            {
                try
                {
                    武将情報.名前 = cell.Value.ToString();
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.名前;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.居城配列IX)
            {
                try
                {
                    武将情報.居城配列IX = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.居城配列IX;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.性別)
            {
                try
                {
                    武将情報.性別 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.性別;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.顔番号)
            {
                try
                {
                    武将情報.顔番号 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.顔番号;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.一門)
            {
                try
                {
                    武将情報.一門 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.一門;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.親武将番号)
            {
                try
                {
                    武将情報.親武将番号 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.親武将番号;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.状態)
            {
                try
                {
                    武将情報.状態 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.状態;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.身分)
            {
                try
                {
                    武将情報.身分 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.身分;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.生年)
            {
                try
                {
                    武将情報.生年 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.生年;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.元服年)
            {
                try
                {
                    武将情報.元服年 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.元服年;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.仕官)
            {
                try
                {
                    武将情報.仕官 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.仕官;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.寿命)
            {
                try
                {
                    武将情報.寿命 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.寿命;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.義理)
            {
                try
                {
                    武将情報.義理 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.義理;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.相性)
            {
                try
                {
                    武将情報.相性 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.相性;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.勲功)
            {
                try
                {
                    武将情報.勲功 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.勲功;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.口調)
            {
                try
                {
                    武将情報.口調 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.口調;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.忠誠)
            {
                try
                {
                    武将情報.忠誠 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.忠誠;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.政治)
            {
                try
                {
                    武将情報.政治 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.政治;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦闘)
            {
                try
                {
                    武将情報.戦闘 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦闘;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.智謀)
            {
                try
                {
                    武将情報.智謀 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.智謀;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.足軽適性)
            {
                try
                {
                    武将情報.足軽適性 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.足軽適性;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.騎馬適性)
            {
                try
                {
                    武将情報.騎馬適性 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.騎馬適性;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.鉄砲適性)
            {
                try
                {
                    武将情報.鉄砲適性 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.鉄砲適性;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.水軍適性)
            {
                try
                {
                    武将情報.水軍適性 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.水軍適性;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.内技農業)
            {
                try
                {
                    武将情報.内技農業 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.内技農業;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.内技商業)
            {
                try
                {
                    武将情報.内技商業 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.内技商業;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.内技建設)
            {
                try
                {
                    武将情報.内技建設 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.内技建設;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.内技外交)
            {
                try
                {
                    武将情報.内技外交 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.内技外交;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.内技登用)
            {
                try
                {
                    武将情報.内技登用 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.内技登用;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦技抜穴)
            {
                try
                {
                    武将情報.戦技抜穴 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦技抜穴;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦技騎突)
            {
                try
                {
                    武将情報.戦技騎突 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦技騎突;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦技三段)
            {
                try
                {
                    武将情報.戦技三段 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦技三段;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦技焙烙)
            {
                try
                {
                    武将情報.戦技焙烙 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦技焙烙;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.戦技騎鉄)
            {
                try
                {
                    武将情報.戦技騎鉄 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.戦技騎鉄;
                }
            }
            else if (e.ColumnIndex == (int)タイトル.農業経験値)
            {
                try
                {
                    武将情報.農業経験値 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.農業経験値;
                }
            }

            else if (e.ColumnIndex == (int)タイトル.商業経験値)
            {
                try
                {
                    武将情報.商業経験値 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.商業経験値;
                }
            }

            else if (e.ColumnIndex == (int)タイトル.建設経験値)
            {
                try
                {
                    武将情報.建設経験値 = (int)cell.Value;
                }
                catch (Exception)
                {
                    cell.Value = 武将情報.建設経験値;
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
            dgv.Columns[(int)タイトル.苗字].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.名前].ValueType = typeof(string);
            dgv.Columns[(int)タイトル.居城配列IX].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[(int)タイトル.状態].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[(int)タイトル.身分].DefaultCellStyle.BackColor = Color.DarkOrange;

            // 基本的にはint型
            string[] names = Enum.GetNames(typeof(タイトル));
            for (int i = (int)タイトル.居城配列IX; i < names.Length; i++)
            {
                dgv.Columns[i].ValueType = typeof(int);
            }

            // 横列単位で足してゆく、
            foreach (var 武将 in 武将配列)
            {
                dgv.Rows.Add(
                  武将.配列IX,
                  武将.苗字,
                  武将.名前,
                  武将.居城配列IX,
                  武将.性別,
                  武将.顔番号,
                  武将.一門,
                  武将.親武将番号,
                  武将.状態,
                  武将.身分,
                  武将.生年,
                  武将.元服年,
                  武将.仕官,
                  武将.寿命,
                  武将.義理,
                  武将.相性,
                  武将.口調,
                  武将.勲功,
                  武将.忠誠,
                  武将.政治,
                  武将.戦闘,
                  武将.智謀,
                  武将.足軽適性,
                  武将.騎馬適性,
                  武将.鉄砲適性,
                  武将.水軍適性,
                  武将.内技農業,
                  武将.内技商業,
                  武将.内技建設,
                  武将.内技外交,
                  武将.内技登用,
                  武将.戦技抜穴,
                  武将.戦技騎突,
                  武将.戦技三段,
                  武将.戦技焙烙,
                  武将.戦技騎鉄,
                  武将.農業経験値,
                  武将.商業経験値,
                  武将.建設経験値
                  );
            }


            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }
}