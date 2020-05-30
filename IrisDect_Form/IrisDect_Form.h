#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_IrisDect_Form.h"

class IrisDect_Form : public QMainWindow
{
    Q_OBJECT

public:
    IrisDect_Form(QWidget *parent = Q_NULLPTR);

private:
    Ui::IrisDect_FormClass ui;
};
