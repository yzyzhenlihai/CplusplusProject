#include "tcpserver.h"
#include "ui_tcpserver.h"

TcpServer::TcpServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TcpServer),
    m_server(NULL),
    m_client(NULL)
{
    ui->setupUi(this);
    m_server = new QTcpServer(this);
    m_server -> listen(QHostAddress::Any,8000);
    connect(m_server,&QTcpServer::newConnection,this,&TcpServer::newConnection);
    this->hide();
}

TcpServer::~TcpServer()
{
    delete ui;
}


void TcpServer::newConnection()
{
    if(m_client == NULL){
        m_client= m_server->nextPendingConnection();
        connect(m_client, &QTcpSocket::readyRead, this, &TcpServer::readyRead);

        connect(m_client, &QTcpSocket::disconnected, this, &TcpServer::clientDisconnected);
    }
}


void TcpServer::readyRead(){

    if (m_client == NULL) {
        return;
    }
    QByteArray array = m_client->readAll();

    // 检查接收到的数据类型
    if (array.startsWith("ID:")) {
        // 处理学生登录信息
        QString data = QString::fromUtf8(array);
        QString data1 = data.mid(3);
        QStringList dataList = data1.split(" ");
        QString id = dataList[0];
        m_receivedId =id;

        QString password = dataList[1];
        // 处理id的逻辑
        if (connectdatabase("dormitory_manage_system.db")) {
            qDebug() << "Received id: " << id;
            qDebug() << "Received password: " << password;
            QSqlTableModel model;
            model.setTable("studentinfo");
            model.setFilter(QString("id = '%1' AND password = '%2'").arg(id).arg(password));
            model.select();
            if (model.rowCount() > 0) {
                m_client->write("ok"); // 向客户端发送"ok"表示成功登录
                // 添加处理成功登录的代码，比如打开学生窗口

            } else {
                m_client->write("invalid"); // 向客户端发送"invalid"表示登录失败
            }
        }
        m_client->disconnectFromHost();
    }

    else if (array.startsWith("NUM:")) {
        QString data = QString::fromUtf8(array);
        QString data1 = data.mid(4);
        QStringList dataList = data1.split("$");
        QString num = dataList[0]; // 维修编号
        QString repairtype = dataList[1]; // 维修类型
        QString fault = dataList[2]; // 故障描述
        QString phone = dataList[3]; // 电话号码
        QString repairtime = dataList[4]; // 提交时间
        QString state = "待处理";        // 处理num、phone、fault的逻辑
        //if (connectdatabase("dormitory_manage_system.db")) {
        QSqlTableModel model(this);
        model.setTable("repairprocess");
        model.setEditStrategy(QSqlTableModel::OnManualSubmit);

        // 插入新记录
        QSqlRecord record = model.record(); // 创建一个空记录
        record.setValue("RoomNumber", num); // 设置num字段的值
        record.setValue("RepairType", repairtype); // 设置phone字段的值
        record.setValue("RepairContent", fault);// 设置fault字段的值
        record.setValue("PhoneNumber", phone); // 设置phone字段的值
        record.setValue("RepairTime", repairtime);
        record.setValue("RepairResult", state);
        if (model.insertRecord(-1, record)) { // 在最后插入记录
            if (model.submitAll()) {
                // 插入成功
                m_client->write("insertsuccess");
                    // QString dlgTitle="information";
                    // QString strInfo="您有新的报修待处理!";
                    // QMessageBox::information(this,dlgTitle,strInfo);
            } else {
                // 提交失败
                m_client->write("invalid");
            }
        } else {
            m_client->write("invalid");
        }

        // }
        m_client->disconnectFromHost();
    }

    else if (array.startsWith("DOR:")) {//报修查看
        QString data = QString::fromUtf8(array);
        QString dornum = data.mid(4);
        QSqlTableModel model(this);
        model.setTable("repairprocess");
        model.setFilter("RoomNumber = '" + dornum + "'");
        model.select();
            // 构建要发送给客户端的查询结果
        QString resultData;
        if (model.rowCount() > 0) {
            for (int i = 0; i < model.rowCount(); ++i) {
                QSqlRecord record = model.record(i);
                QString num = record.value("RoomNumber").toString();
                QString repairtype = record.value("RepairType").toString();
                QString fault = record.value("RepairContent").toString();
                QString phone = record.value("PhoneNumber").toString();
                QString repairtime = record.value("RepairTime").toString();
                QString state = record.value("RepairResult").toString();
                    // 将查询结果拼接为字符串
                resultData +=  num + "," +repairtype + "," + fault + "," + phone + ","+repairtime + ","  + state + "$";
            }
        } else {
            resultData = "No records found" ;
        }
        m_client->write(resultData.toUtf8());
    }

    else if (array=="Infoview"){//信息查询
        QSqlTableModel model;
        model.setTable("studentinfo");
        model.setFilter(QString("id = '%1'").arg(m_receivedId));
        model.select();
        QString resultData;
        if (model.rowCount() > 0) {
            for (int i = 0; i < model.rowCount(); ++i) {
                QSqlRecord record = model.record(i);
                QString id = record.value("id").toString();
                QString name = record.value("name").toString();
                QString sex = record.value("sex").toString();
                QString age = record.value("age").toString();
                QString major = record.value("major").toString();
                QString classs = record.value("class").toString();
                QString phonenum = record.value("phonenumber").toString();
                QString roomnum = record.value("roomnumber").toString();
                QString bedroom = record.value("bednumber").toString();
                QByteArray pic = record.value("picture").toByteArray();

                // 将查询结果拼接为字符串
                resultData.append("ID: " + id + ", Name: " + name + ", Sex: " + sex + ", Age: " + age + ", Major: " + major + ", Class: " + classs + ", PhoneNum: " + phonenum + ", RoomNum: " + roomnum + ", Bedroom: " + bedroom + ", Picture: " + pic);
            }
        }
        m_client->write(resultData.toUtf8());  // 将查询结果发送回客户端
    }

    else if (array.startsWith("PASS:")){//修改密码
        QString data = QString::fromUtf8(array);
        QString newpassword = data.mid(5);
        if (!newpassword.isEmpty()) {
            QSqlTableModel model;
            model.setTable("studentinfo");
            model.setFilter(QString("id = '%1'").arg(m_receivedId));
            model.select();
            model.setData(model.index(0, model.fieldIndex("password")), newpassword);
            if (model.submitAll()) {
                m_client->write("passwordsuccess");
            } else {
                m_client->write("passwordfail");
            }
        }
    }else if(array.startsWith("PIC:")){
        //qDebug()<<array;
        QByteArray imageData = array.mid(4).toBase64();  // 从数据中提取图片数据部分
        QSqlTableModel model;
        model.setTable("studentinfo");
        model.setFilter(QString("id = '%1'").arg(m_receivedId));
        model.select();
        model.setData(model.index(0, model.fieldIndex("picture")), imageData);
        model.submitAll();

    }


    else {
        // 如果接收到未知类型的数据
        m_client->write("invalid"); // 向客户端发送无效消息
        m_client->disconnectFromHost();
    }


}


void TcpServer::clientDisconnected()
{
    m_client->deleteLater();  // 清理断开连接的客户端对象
    m_client = NULL;  // 重置客户端指针
}


bool TcpServer::connectdatabase(const QString& dbName){
    qDebug() << QSqlDatabase::drivers();//打印数据库驱动
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    bool ok=db.open();
    return ok;

}
