#ifndef MODBUSTCPCLIENT_H
#define MODBUSTCPCLIENT_H

#include <QMainWindow>
#include <QDateTime>

#include <inc/config.h>
#include <inc/modbus-private.h>
#include <inc/modbus-tcp-private.h>
#include <inc/modbus-tcp.h>
#include <inc/modbus-version.h>
#include <inc/modbus.h>


#pragma execution_character_set("utf-8")

#define OCOIL_ADDR_START 0
#define OCOIL_LEN        8
#define INPUT_ADDR_START 0
#define INPUT_LEN        8
#define OREGS_ADDR_START 0
#define OREGS_LEN        10
#define IREGS_ADDR_START 0
#define IREGS_LEN        10

QT_BEGIN_NAMESPACE
namespace Ui { class ModbusTCPClient; }
QT_END_NAMESPACE

class ModbusTCPClient : public QMainWindow
{
    Q_OBJECT

public:
    ModbusTCPClient(QWidget *parent = nullptr);
    ~ModbusTCPClient();

private slots:


    void on_connect_clicked();

    void on_read_input_bits_clicked();

    void on_read_output_bits_clicked();

    void on_write_holding_regs_clicked();

    void on_read_holding_regs_clicked();

    void on_reserve1_clicked();

    void on_reserve2_clicked();

private:
    Ui::ModbusTCPClient *ui;

    modbus_t *ctx;
    uint8_t *tab_input_bits;
    uint8_t *tab_output_bits;
    uint16_t *tab_holding_regs;


};
#endif // MODBUSTCPCLIENT_H
