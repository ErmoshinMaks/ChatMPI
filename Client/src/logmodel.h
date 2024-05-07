#include <QSqlQueryModel>

class LogModel : public QSqlQueryModel
{
public:
    LogModel(QObject *parent = nullptr);
};