#ifndef SOAP_CLIENT_WIDGET_H_
#define SOAP_CLIENT_WIDGET_H_

#include <QWidget>

class QLabel;
class QLineEdit;

class SoapClientWidget : public QWidget
{
    Q_OBJECT
public:
    SoapClientWidget(QWidget* parent = nullptr);
    ~SoapClientWidget();

private slots:
    void Save();
    void Load();

private:
    void ShowErrorCode(int);
private:
    QLabel* view_;
    QLineEdit* edit_;
    QLabel* status_;
};

#endif // SOAP_CLIENT_WIDGET_H
