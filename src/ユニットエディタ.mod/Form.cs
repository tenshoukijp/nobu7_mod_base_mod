using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System;

namespace 将星録;



public partial class ユニットエディタ : 基本エディタ
{

    public ユニットエディタ() : base()
    {
        this.Text = nameof(ユニットエディタ);
    }

    class BIND用のユニット情報型
    {
        ユニット情報型 ユニット情報;
        public BIND用のユニット情報型(int ユニット配列IX)
        {
            ユニット情報 = new ユニット情報型(ユニット配列IX);
        }

        public int 配列IX
        {
            get { return ユニット情報.配列IX; }
        }

        public string 指揮武将姓名
        {
            get
            {
                int iBushouID = ユニット情報.指揮武将配列IX;
                String strBushouName = "-";
                if (0 <= iBushouID && iBushouID < 最大数.武将情報.総配列数)
                {
                    var 武将情報 = new 武将情報型(iBushouID);
                    strBushouName = 武将情報.姓名;
                }
                return strBushouName;
            }
        }

        public int 指揮武将配列IX
        {
            get { return ユニット情報.指揮武将配列IX; }
            set { ユニット情報.指揮武将配列IX = value; }
        }

        public int 所属城配列IX
        {
            get { return ユニット情報.所属城配列IX; }
            set { ユニット情報.所属城配列IX = value; }
        }

        public int 種別
        {
            get { return ユニット情報.種別; }
            set { ユニット情報.種別 = value; }
        }

        public int 目的
        {
            get { return ユニット情報.目的; }
            set { ユニット情報.目的 = value; }
        }

        public int 大砲
        {
            get { return ユニット情報.大砲; }
            set { ユニット情報.大砲 = value; }
        }

        public int 鉄甲船
        {
            get { return ユニット情報.鉄甲船; }
            set { ユニット情報.鉄甲船 = value; }
        }

        public int 第１部隊兵数
        {
            get { return ユニット情報.第１部隊兵数; }
            set { ユニット情報.第１部隊兵数 = value; }
        }

        public int 第１部隊兵種
        {
            get { return ユニット情報.第１部隊兵種; }
            set { ユニット情報.第１部隊兵種 = value; }
        }

        public int 第１部隊混乱
        {
            get { return ユニット情報.第１部隊混乱; }
            set { ユニット情報.第１部隊混乱 = value; }
        }

        public int 第１部隊陣形位置
        {
            get { return ユニット情報.第１部隊陣形位置; }
            set { ユニット情報.第１部隊陣形位置 = value; }
        }

        public int 第２部隊兵数
        {
            get { return ユニット情報.第２部隊兵数; }
            set { ユニット情報.第２部隊兵数 = value; }
        }

        public int 第２部隊兵種
        {
            get { return ユニット情報.第２部隊兵種; }
            set { ユニット情報.第２部隊兵種 = value; }
        }

        public int 第２部隊混乱
        {
            get { return ユニット情報.第２部隊混乱; }
            set { ユニット情報.第２部隊混乱 = value; }
        }

        public int 第２部隊陣形位置
        {
            get { return ユニット情報.第２部隊陣形位置; }
            set { ユニット情報.第２部隊陣形位置 = value; }
        }

        public int 第３部隊兵数
        {
            get { return ユニット情報.第３部隊兵数; }
            set { ユニット情報.第３部隊兵数 = value; }
        }

        public int 第３部隊兵種
        {
            get { return ユニット情報.第３部隊兵種; }
            set { ユニット情報.第３部隊兵種 = value; }
        }

        public int 第３部隊混乱
        {
            get { return ユニット情報.第３部隊混乱; }
            set { ユニット情報.第３部隊混乱 = value; }
        }

        public int 第３部隊陣形位置
        {
            get { return ユニット情報.第３部隊陣形位置; }
            set { ユニット情報.第３部隊陣形位置 = value; }
        }

        public int 第４部隊兵数
        {
            get { return ユニット情報.第４部隊兵数; }
            set { ユニット情報.第４部隊兵数 = value; }
        }

        public int 第４部隊兵種
        {
            get { return ユニット情報.第４部隊兵種; }
            set { ユニット情報.第４部隊兵種 = value; }
        }

        public int 第４部隊混乱
        {
            get { return ユニット情報.第４部隊混乱; }
            set { ユニット情報.第４部隊混乱 = value; }
        }

        public int 第４部隊陣形位置
        {
            get { return ユニット情報.第４部隊陣形位置; }
            set { ユニット情報.第４部隊陣形位置 = value; }
        }

        public int 第５部隊兵数
        {
            get { return ユニット情報.第５部隊兵数; }
            set { ユニット情報.第５部隊兵数 = value; }
        }

        public int 第５部隊兵種
        {
            get { return ユニット情報.第５部隊兵種; }
            set { ユニット情報.第５部隊兵種 = value; }
        }

        public int 第５部隊混乱
        {
            get { return ユニット情報.第５部隊混乱; }
            set { ユニット情報.第５部隊混乱 = value; }
        }

        public int 第５部隊陣形位置
        {
            get { return ユニット情報.第５部隊陣形位置; }
            set { ユニット情報.第５部隊陣形位置 = value; }
        }

        public int 輸送金銭
        {
            get { return ユニット情報.輸送金銭; }
            set { ユニット情報.輸送金銭 = value; }
        }

        public int 輸送兵糧
        {
            get { return ユニット情報.輸送兵糧; }
            set { ユニット情報.輸送兵糧 = value; }
        }

        public int 輸送軍馬
        {
            get { return ユニット情報.輸送軍馬; }
            set { ユニット情報.輸送軍馬 = value; }
        }

        public int 輸送鉄砲
        {
            get { return ユニット情報.輸送鉄砲; }
            set { ユニット情報.輸送鉄砲 = value; }
        }

        public int 輸送兵士
        {
            get { return ユニット情報.輸送兵士; }
            set { ユニット情報.輸送兵士 = value; }
        }

        public int 輸送大砲
        {
            get { return ユニット情報.輸送大砲; }
            set { ユニット情報.輸送大砲 = value; }
        }

        public int 現在Ｘ座標
        {
            get { return ユニット情報.現在Ｘ座標; }
        }

        public int 現在Ｙ座標
        {
            get { return ユニット情報.現在Ｙ座標; }
        }

        public int 後ユニット配列IX
        {
            get { return ユニット情報.後ユニット配列IX; }
            set { ユニット情報.後ユニット配列IX = value; }
        }

    }

    protected override void dgv_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
        try
        {
            var 指揮武将IXcolumns = dgv.Columns[nameof(BIND用のユニット情報型.指揮武将配列IX)];
            // 対象のセル
            if (e.ColumnIndex == 指揮武将IXcolumns.Index)
            {
                bindingSource.ResetBindings(false);
            }
        }
        catch (Exception) { }
    }

    BindingSource bindingSource = new();
    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用のユニット情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.ユニット情報.配列数; i++)
            {
                データ配列.Add(new BIND用のユニット情報型(i));
            }

            bindingSource.DataSource = データ配列;
            dgv.DataSource = bindingSource;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns[nameof(BIND用のユニット情報型.配列IX)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用のユニット情報型.指揮武将姓名)].DefaultCellStyle.BackColor = Color.Yellow;
            dgv.Columns[nameof(BIND用のユニット情報型.指揮武将配列IX)].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[nameof(BIND用のユニット情報型.所属城配列IX)].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns[nameof(BIND用のユニット情報型.現在Ｘ座標)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用のユニット情報型.現在Ｙ座標)].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns[nameof(BIND用のユニット情報型.後ユニット配列IX)].DefaultCellStyle.BackColor = Color.DarkOrange;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}

