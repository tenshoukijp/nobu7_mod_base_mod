using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace 将星録;



public partial class 武将エディタ : 基本エディタ
{

    public 武将エディタ() : base()
    {
        this.Text = nameof(武将エディタ);
    }

    class BIND用の武将情報型
    {
        武将情報型 武将情報;
        public BIND用の武将情報型(int 武将配列IX)
        {
            武将情報 = new 武将情報型(武将配列IX);
        }

        public int 配列IX
        {
            get { return 武将情報.配列IX; }
        }

        public string 苗字
        {
            get { return 武将情報.苗字; }
            set { 武将情報.苗字 = value; }
        }

        public string 名前
        {
            get { return 武将情報.名前; }
            set { 武将情報.名前 = value; }
        }

        public int 居城配列IX
        {
            get { return 武将情報.居城配列IX; }
            set { 武将情報.居城配列IX = value; }
        }

        public int 性別
        {
            get { return 武将情報.性別; }
            set { 武将情報.性別 = value; }
        }

        public int 顔番号
        {
            get { return 武将情報.顔番号; }
            set { 武将情報.顔番号 = value; }
        }

        public int 一門
        {
            get { return 武将情報.一門; }
            set { 武将情報.一門 = value; }
        }

        public int 親武将番号
        {
            get { return 武将情報.親武将番号; }
            set { 武将情報.親武将番号 = value; }
        }

        public int 行動済
        {
            get { return 武将情報.行動済; }
            set { 武将情報.行動済 = value; }
        }

        public int 状態
        {
            get { return 武将情報.状態; }
            set { 武将情報.状態 = value; }
        }

        public int 身分
        {
            get { return 武将情報.身分; }
            set { 武将情報.身分 = value; }
        }

        public int 生年
        {
            get { return 武将情報.生年; }
            set { 武将情報.生年 = value; }
        }

        public int 元服年
        {
            get { return 武将情報.元服年; }
            set { 武将情報.元服年 = value; }
        }

        public int 仕官
        {
            get { return 武将情報.仕官; }
            set { 武将情報.仕官 = value; }
        }

        public int 寿命
        {
            get { return 武将情報.寿命; }
            set { 武将情報.寿命 = value; }
        }

        public int 義理
        {
            get { return 武将情報.義理; }
            set { 武将情報.義理 = value; }
        }

        public int 相性
        {
            get { return 武将情報.相性; }
            set { 武将情報.相性 = value; }
        }

        public int 口調
        {
            get { return 武将情報.口調; }
            set { 武将情報.口調 = value; }
        }

        public int 勲功
        {
            get { return 武将情報.勲功; }
            set { 武将情報.勲功 = value; }
        }

        public int 忠誠
        {
            get { return 武将情報.忠誠; }
            set { 武将情報.忠誠 = value; }
        }

        public int 政治
        {
            get { return 武将情報.政治; }
            set { 武将情報.政治 = value; }
        }

        public int 戦闘
        {
            get { return 武将情報.戦闘; }
            set { 武将情報.戦闘 = value; }
        }

        public int 智謀
        {
            get { return 武将情報.智謀; }
            set { 武将情報.智謀 = value; }
        }

        public int 足軽適性
        {
            get { return 武将情報.足軽適性; }
            set { 武将情報.足軽適性 = value; }
        }

        public int 騎馬適性
        {
            get { return 武将情報.騎馬適性; }
            set { 武将情報.騎馬適性 = value; }
        }

        public int 鉄砲適性
        {
            get { return 武将情報.鉄砲適性; }
            set { 武将情報.鉄砲適性 = value; }
        }

        public int 水軍適性
        {
            get { return 武将情報.水軍適性; }
            set { 武将情報.水軍適性 = value; }
        }

        public int 内技農業
        {
            get { return 武将情報.内技農業; }
            set { 武将情報.内技農業 = value; }
        }

        public int 内技商業
        {
            get { return 武将情報.内技商業; }
            set { 武将情報.内技商業 = value; }
        }

        public int 内技建設
        {
            get { return 武将情報.内技建設; }
            set { 武将情報.内技建設 = value; }
        }

        public int 内技外交
        {
            get { return 武将情報.内技外交; }
            set { 武将情報.内技外交 = value; }
        }

        public int 内技登用
        {
            get { return 武将情報.内技登用; }
            set { 武将情報.内技登用 = value; }
        }

        public int 戦技抜穴
        {
            get { return 武将情報.戦技抜穴; }
            set { 武将情報.戦技抜穴 = value; }
        }

        public int 戦技騎突
        {
            get { return 武将情報.戦技騎突; }
            set { 武将情報.戦技騎突 = value; }
        }

        public int 戦技三段
        {
            get { return 武将情報.戦技三段; }
            set { 武将情報.戦技三段 = value; }
        }

        public int 戦技焙烙
        {
            get { return 武将情報.戦技焙烙; }
            set { 武将情報.戦技焙烙 = value; }
        }

        public int 戦技騎鉄
        {
            get { return 武将情報.戦技騎鉄; }
            set { 武将情報.戦技騎鉄 = value; }
        }

        public int 修行中
        {
            get { return 武将情報.修行中; }
            set { 武将情報.修行中 = value; }
        }

        public int 修行済忍者
        {
            get { return 武将情報.修行済忍者; }
            set { 武将情報.修行済忍者 = value; }
        }

        public int 修行済移動力
        {
            get { return 武将情報.修行済移動力; }
            set { 武将情報.修行済移動力 = value; }
        }
    }

    protected override void dvg_DataBinding()
    {
        try
        {
            List<BIND用の武将情報型> データ配列 = new();
            for (int i = 0; i < 将星録.最大数.武将情報.総配列数; i++)
            {
                データ配列.Add(new BIND用の武将情報型(i));
            }
            dgv.DataSource = データ配列;
        }
        catch (Exception) { }
    }
    protected override void dvg_DataBindingComplete(object sender, DataGridViewBindingCompleteEventArgs e)
    {
        try
        {
            dgv.Columns["配列IX"].DefaultCellStyle.BackColor = Color.LightGray;
            dgv.Columns["居城配列IX"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["状態"].DefaultCellStyle.BackColor = Color.DarkOrange;
            dgv.Columns["身分"].DefaultCellStyle.BackColor = Color.DarkOrange;

            dgv.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
        }
        catch (Exception) { }
    }


}



