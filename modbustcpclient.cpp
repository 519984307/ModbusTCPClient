#include "modbustcpclient.h"
#include "ui_modbustcpclient.h"




ModbusTCPClient::ModbusTCPClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ModbusTCPClient)
{
    ui->setupUi(this);

    ctx = modbus_new_tcp("192.168.1.11", 502);

    tab_input_bits = (uint8_t*)malloc(INPUT_LEN * sizeof (uint8_t));
    memset(tab_input_bits, 0, INPUT_LEN * sizeof (uint8_t));

    tab_output_bits = (uint8_t*)malloc(OCOIL_LEN * sizeof (uint8_t));
    memset(tab_output_bits, 0, OCOIL_LEN * sizeof (uint8_t));

    tab_holding_regs = (uint16_t*)malloc(OREGS_LEN * sizeof (uint16_t));
    memset(tab_holding_regs, 0, OREGS_LEN * sizeof (uint16_t));
}

ModbusTCPClient::~ModbusTCPClient()
{

    free(tab_input_bits);
    free(tab_output_bits);
    free(tab_holding_regs);

    modbus_close(ctx);
    modbus_free(ctx);
    delete ui;
}



void ModbusTCPClient::on_connect_clicked()
{
    if(modbus_connect(ctx) == (-1))
        ui->textEdit->append(QString("connection failed:%1").arg(errno));
    else ui->textEdit->append("connection success");
}

void ModbusTCPClient::on_read_input_bits_clicked()
{
    int rc = modbus_read_input_bits(ctx, INPUT_ADDR_START, INPUT_LEN, tab_input_bits);

    if(rc == INPUT_LEN) {
        ui->textEdit->append("read input bits successfully.");
        for (int i = 0; i < rc; i++) {
            ui->textEdit->append(QString("I0.%1 : %2").arg(i).arg((tab_input_bits[i]>0) ? "true":"false"));
        }
    }
    else {
        ui->textEdit->append(QString("reading input bits failed:%1").arg(errno));
    }
    memset(tab_input_bits, 0, INPUT_LEN * sizeof (uint8_t));

}

void ModbusTCPClient::on_read_output_bits_clicked()
{
    int rc = modbus_read_bits(ctx, OCOIL_ADDR_START, OCOIL_LEN, tab_output_bits);

    if(rc == OCOIL_LEN) {
        ui->textEdit->append("read output bits successfully.");
        for (int i = 0; i < rc; i++) {
            ui->textEdit->append(QString("Q0.%1 : %2").arg(i).arg((tab_output_bits[i]>0) ? "true":"false"));
        }
    }
    else {
        ui->textEdit->append(QString("reading output bits failed:%1").arg(errno));
    }
    memset(tab_output_bits, 0, OCOIL_LEN * sizeof (uint8_t));
}

void ModbusTCPClient::on_write_holding_regs_clicked()
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    for (int i = 0; i < OREGS_LEN; i++) {
        tab_holding_regs[i] = qrand()%500;
    }

    int rc = modbus_write_registers(ctx, OREGS_ADDR_START, OREGS_LEN, tab_holding_regs);
    if(rc == OREGS_LEN)
        ui->textEdit->append("write holding regs successfully.");
    else
        ui->textEdit->append(QString("writing holding regs failed:%1").arg(errno));

    memset(tab_holding_regs, 0, OREGS_LEN * sizeof (uint16_t));
}

void ModbusTCPClient::on_read_holding_regs_clicked()
{
    int rc = modbus_read_registers(ctx, OREGS_ADDR_START, OREGS_LEN, tab_holding_regs);
    if(rc == OREGS_LEN) {
        ui->textEdit->append("read holding regs successfully.");
        for (int i = 0; i < rc; i++) {
            ui->textEdit->append(QString("MW%1 : %2").arg(i*2).arg(tab_holding_regs[i]));
        }
    }
    else {
        ui->textEdit->append(QString("reading holding regs failed:%1").arg(errno));
    }
    memset(tab_holding_regs, 0, OREGS_LEN * sizeof (uint16_t));
}

void ModbusTCPClient::on_reserve1_clicked()
{

}

void ModbusTCPClient::on_reserve2_clicked()
{

}
