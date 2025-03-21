#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    //清除数据
    ui->textEdit_before->clear();
    ui->textEdit_after->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    //关闭窗口
    QApplication::quit();
}





void MainWindow::on_pushButton_open_clicked()
{
    QString inputs =ui->lineEdit->text();
    //QString inputs = "D:/remote/data.dat";
    QFile qinput(inputs);
    bool bopen = qinput.open(QIODevice::ReadOnly | QIODevice::Text);
    qDebug() << bopen;
    if (bopen) {
        ui->textEdit_before->clear(); // 清空之前的文本
        while (!qinput.atEnd()) {
            QString strline = qinput.readLine();
            // 去除行末尾的换行符，并检查是否为空行
            strline = strline.trimmed();
            if (!strline.isEmpty()) {
                ui->textEdit_before->append(strline);
            }
        }
        qinput.close(); // 关闭文件
    }

}














//1,C2-018,1497.513,48847.951,2.827

//计算函数（按序号的升序排序，删除重复点号）
void MainWindow::on_pushButton_clicked()
{

    QString strInput = ui->textEdit_before->toPlainText();
    QStringList strListInput = strInput.split('\n');
    //提取出要处理的行数
    int member=strListInput[0].toInt();
    //将点位信息提取至结构体数组
    bool temper;
    int number_after=0;
    for(int i=1;i<=member&& i < strListInput.size();i++)
    {
          QStringList obsData = strListInput[i].split(',');

        temper=true;
         for(int j=0;j<number_after;j++)
        {
              if(obsData[0].toInt() == points[j].number)
            {
                temper=false;
                break;
              }
        }

        if(temper==true)
        {
            points[number_after].number=obsData[0].toInt();
          points[number_after].code=obsData[1];
        points[number_after].x=obsData[2].toDouble();
          points[number_after].y=obsData[3].toDouble();
        points[number_after].h=obsData[4].toDouble();
          number_after++;
        }

    }
    //使用冒泡排序对输入的数据列表进行从小到大排序
    for (int i = 0; i < number_after-1; i++)
    {
        for (int j = 0; j < number_after-i-1; j++)
        {
            if (points[j].number > points[j+1].number)
            {
                int temp;
                temp =points[j].number ;
                points[j].number= points[j+1].number;
                points[j+1].number = temp;
                QString list;
                list =points[j].code ;
                points[j].code= points[j+1].code;
                points[j+1].code = list;
                double x_temp;
                x_temp =points[j].x;
                points[j].x= points[j+1].x;
                points[j+1].x = x_temp;
                double y_temp;
                y_temp =points[j].y;
                points[j].y= points[j+1].y;
                points[j+1].y = y_temp;
                double h_temp;
                h_temp =points[j].h;
                points[j].h= points[j+1].h;
                points[j+1].h = h_temp;
               //  std::swap(points[j], points[j + 1]);
            }
        }
    }
//将排列好的数据写入文本框内
    QString text1 = QString::number(number_after);
    ui->textEdit_after->append(text1);
   for(int k=0;k<number_after;k++)
    {
        // 初始化包含不同类型数据的列表

        QList<QString> dataList;
        dataList << QString::number(points[k].number)
                 << points[k].code
                 << QString::number(points[k].x, 'f', 3)
                 << QString::number(points[k].y, 'f', 3)
                 << QString::number(points[k].h, 'f', 3);

        // 使用dataList生成要追加的文本
        QString text = dataList.join(","); // 使用逗号将列表元素连接成一个字符串

        // 追加到plainTextEdit_after
        ui->textEdit_after->append(text);
    }

}
//使用QFile写入文件
void MainWindow::on_pushButton_save_clicked()
{

        QFile file("D:/remote/data.dat");

        // 尝试打开文件用于写入
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(nullptr, "Error", "Cannot open file for writing.");

        }

        // 使用QTextStream写入文件
        QTextStream out(&file);
        out << ui->textEdit_after->toPlainText();

        // 关闭文件
        file.close();



}

